
/********************************************************************20**

     Name:    EGTP 

     Type:    C source file

     Desc:    C code for controlling acceptance tests execution.

     File:    egac_egtreg.c

     Sid:      smeg_ieutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:19:09 2015

     Prg:     pc

*********************************************************************21*/

/* header include files (.h) */
#include "envopt.h"         /* environment options          */
#include "envdep.h"         /* environment dependent        */
#include "envind.h"         /* environment independent      */
#include "gen.h"            /* general layer                */
#include "ssi.h"            /* system services              */
#include "cm5.h"            /* common timer module          */
#include "cm_hash.h"        /* common hash list             */
#include "cm_tkns.h"        /* common tokens                */
#include "cm_tpt.h"         /* Transport  header file       */
#include "cm_mblk.h"        /* common memory allocation     */
#include "cm_llist.h"      /* common link list */

#include "eg_util.h"       /* Egtpeter Utility library */
#include "egt.h"           /* Egtpeter Upper Interface */
#include "eg.h"           /* Egtpeter Upper Interface */
#include "eg_edm.h"
#include "egac_edm.h"           /* Egtpeter Upper Interface */
#include "leg.h"           /* Egtpeter Layer Manager   */

/* header/extern include files (.x) */
#include "gen.x"            /* general layer                */
#include "ssi.x"            /* system services              */
#include "cm5.x"            /* common timer module          */
#include "cm_lib.x"         /* common library               */
#include "cm_hash.x"        /* common hash list             */
#include "cm_tkns.x"        /* common tokens                */
#include "cm_mblk.x"        /* common memory allocation     */
#include "cm_inet.x"        /* Inet header file             */
#include "cm_tpt.x"         /* Transport  header file       */
#include "cm_llist.x"      /* common link list */
#include "cm_dns.h"
#include "cm_dns.x"

#include "egt.x"           /* Eg Upper Interface */
#include "leg.x"           /* Eg layer manager  */
/*eg004.201 Header files added for eGTPC PSF Upgrade*/
#ifdef HW
#include "cm_ftha.h"
#include "cm_psf.h"
#include "cm_psfft.h"
#include "cm_ftha.x"
#include "cm_psfft.x"
#include "cm_psf.x"
#endif
#include "cm_xta.h"
#include "egac_acc.h"
#include "eg_edm.x"        /* EDM Module structures            */
#include "eg.x"
#include "cm_xta.x"
#include "egac_acc.x"
#include "egac_edm.x"
#include "eg_util.x"       /* Eg Utility library */
#include "smeg_ieutl.x" 


#ifdef EGTP_C
EXTERN Void  makeAndAddTransIdIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddPktFlowIdIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));

EXTERN Void  makeAndAddFqdnIe ARGS
((
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
));


/*
*
*       Fun:   egAcEgtBuildEgIeHeader
*
*       Desc:  This function is used to Build CSR message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  egAcEgtBuildEgIeHeader
(
EgIe         *egIe,
U8           ieType,
U8           ieInst,
U8           dataType
)
#else
PUBLIC Void egAcEgtBuildEgIeHeader(egIe,ieType, ieInst, dataType)
EgIe         *egIe;
U8           ieType;
U8           ieInst;
U8           dataType;
#endif /* ANSI */
{
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcEgtBuildEgIeHeader)

   egIe->ieType = ieType;
   egIe->ieInst = ieInst;
   egIe->dataType = dataType;

   RETVOID;
}


/*
*
*       Fun:   egAcEgtBuildEgHeader
*
*       Desc:  This function is used to Build CSR message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  egAcEgtBuildEgHeader
(
CmXtaTCCb         *tcCb,
CmXtaSpCb         *spCb,
EgMsgHdr         *egHdr,
U8                msgType
)
#else
PUBLIC Void egAcEgtBuildEgHeader(tcCb,spCb,egHdr,msgType)
CmXtaTCCb         *tcCb;
CmXtaSpCb         *spCb;
EgMsgHdr         *egHdr;
U8              msgType;
#endif /* ANSI */
{
   S16   retVal  = ROK;
   S16   retVal1  = ROK;
   U32   transId = 0;
   ProcId procId = 0;
   U8    version = 2;
   U32   teid    = 0;
   U32   seqNo   = 0;
   Bool  teidPres = TRUE;

   /* eg011:201 : piggyback changes */
#ifdef EG_PIGGYBACK_SUPP
   Bool piggyBack = 0;
#endif
   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(egAcEgtBuildEgHeader)

   egHdr->version = 2;
   egHdr->msgType = msgType;
   egHdr->teidPres = teidPres;
   egHdr->teid = 0;
   egHdr->seqNumber =0;

   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8, (Txt *)"version",  &version);
   if(retVal != CMXTA_ERR_NO_VALUE)
   {
      egHdr->version = version;
   }

   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *)"egMsgType",  &msgType);
   if(retVal != CMXTA_ERR_NO_VALUE)
   {
      egHdr->msgType = msgType;
   }

   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8,(Txt *) "teidPres",  &teidPres);
   if(retVal != CMXTA_ERR_NO_VALUE)
   {
      egHdr->teidPres = teidPres;
   }

   if(egHdr->teidPres)
   {
      retVal  = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,(Txt *)"transId",&(transId));
      retVal1 = cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,(Txt *)"procId",&(procId));
      if ( retVal != CMXTA_ERR_NO_VALUE &&  retVal1 != CMXTA_ERR_NO_VALUE)
      {
         teid = egAccCb.egAcMsgInfo[procId][transId].rmTeid;
      }
      cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, (Txt *)"teidValue",  &teid);
      if ( teid)
      {
         egHdr->teid= teid;
      }
   }

   if ( retVal != CMXTA_ERR_NO_VALUE &&  retVal1 != CMXTA_ERR_NO_VALUE)
   {
      seqNo = egAccCb.egAcMsgInfo[procId][transId].seqNo;
      egHdr->seqNumber = seqNo;
   }

   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, (Txt *)"seqNo",  &seqNo);
   if(retVal != CMXTA_ERR_NO_VALUE)
   {
      egHdr->seqNumber = seqNo;
   }
   /*eg011.201: Added for piggyback support */
#ifdef EG_PIGGYBACK_SUPP
   retVal = cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U32, (Txt *)"piggyBack",  &piggyBack);
   if(retVal != CMXTA_ERR_NO_VALUE)
   {
       egHdr->pMsgPres = TRUE;
   }
#endif
   RETVOID;
}


/*
*
*       Fun:   makeAndAddGutiIe
*
*       Desc:  This function is used to Build eGTP GUTI IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddGutiIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddGutiIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     gutiPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddGutiIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_GUTI_IETYPE, ieProp.ieInst, EG_GUTI);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"gutiPresent",  &gutiPresent);

   if (gutiPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"gutiIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"gutiIeInst",  &egIe.ieInst);

      egIe.t.guti.sNwk.mccDigit1 = 1;
      egIe.t.guti.sNwk.mccDigit2 = 1;
      egIe.t.guti.sNwk.mccDigit3 = 1;
      egIe.t.guti.sNwk.mncDigit1 = 1;
      egIe.t.guti.sNwk.mncDigit2 = 1;
      egIe.t.guti.sNwk.mncDigit3 = 1;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ServNwMccDigit1", &egIe.t.guti.sNwk.mccDigit1);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ServNwMccDigit2", &egIe.t.guti.sNwk.mccDigit2);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ServNwMccDigit3", &egIe.t.guti.sNwk.mccDigit3);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ServNwMacDigit1", &egIe.t.guti.sNwk.mncDigit1);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ServNwMacDigit2", &egIe.t.guti.sNwk.mncDigit2);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ServNwMacDigit3", &egIe.t.guti.sNwk.mncDigit3);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                     (Txt *)"mmeGrpId", &egIe.t.guti.mmeGrpId);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"mmeCode", &egIe.t.guti.mmeCode);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                     (Txt *)"mTmsi", &egIe.t.guti.mTmsi);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap,"makeAndAddGutiIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddGutiIe */


/*
*
*       Fun:   makeAndAddPTmsiIe
*
*       Desc:  This function is used to Build eGTP P-TMSI IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPTmsiIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPTmsiIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     pTmsiPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPTmsiIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_PTMSI_IETYPE, ieProp.ieInst, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"pTmsiPresent",  &pTmsiPresent);

   if (pTmsiPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"pTmsiIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"pTmsiIeInst",  &egIe.ieInst);

      egIe.t.valUnSgnd32 = DFLT_PTMSI_VAL;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                     (Txt *)"pTmsi", &egIe.t.valUnSgnd32);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddPTmsiIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddPTmsiIe */

/*
*
*       Fun:   makeAndAddTmsiIe
*
*       Desc:  This function is used to Build eGTP TMSI IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddTmsiIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddTmsiIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     TmsiPresent = TRUE;
   EgIe   egIe;

   TRC2(makeAndAddTmsiIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_PTMSI_IETYPE, ieProp.ieInst, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"TmsiPresent",  &TmsiPresent);

   if (TmsiPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"TmsiIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"TmsiIeInst",  &egIe.ieInst);

      egIe.t.valUnSgnd32 = DFLT_PTMSI_VAL;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                     (Txt *)"Tmsi", &egIe.t.valUnSgnd32);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddTmsiIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddTmsiIe */


/*
*
*       Fun:   makeAndAddPTmsiSigIe
*
*       Desc:  This function is used to Build eGTP P-TMSI SIGNATURE IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPTmsiSigIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPTmsiSigIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     pTmsiSigPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPTmsiSigIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_PTMSI_SIG_IETYPE, ieProp.ieInst, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"pTmsiSigPresent",  &pTmsiSigPresent);

   if (pTmsiSigPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"pTmsiSigIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"pTmsiSigIeInst",  &egIe.ieInst);

      egIe.t.valUnSgnd32 = DFLT_PTMSI_SIG_VAL;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                     (Txt *)"pTmsiSig", &egIe.t.valUnSgnd32);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddPTmsiSigIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddPTmsiSigIe */


/*
*
*       Fun:   makeAndAddCompReqMsgIe
*
*       Desc:  This function is used to Build eGTP Complete Request Message IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddCompReqMsgIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddCompReqMsgIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   crm[100] = DFLT_CRM;
   U8     crmPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddCompReqMsgIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_COMP_REQ_MSG_IETYPE, ieProp.ieInst, EG_CMP_REQ);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"crmPresent",  &crmPresent);

   if (crmPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"crmIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"crmIeInst",  &egIe.ieInst);

      egIe.t.crm.crmType = DFLT_CRM_TYPE_VAL;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"crmType", &egIe.t.crm.crmType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"crm", crm);

      egIe.t.crm.crm.length = cmStrlen((U8 *)crm);
      cmMemcpy( (U8 *) egIe.t.crm.crm.val, (U8 *)crm, egIe.t.crm.crm.length);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddCompReqMsgIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddCompReqMsgIe */


/*
*
*       Fun:   makeAndAddIpAddrIe
*
*       Desc:  This function is used to Build eGTP IP-Address IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddIpAddrIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddIpAddrIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Txt    ipAddr[100] = DFLT_IP_ADDRESS;
   U8     ipAddrPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddIpAddrIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_IPADDR_IETYPE, ieProp.ieInst, EG_IP_ADDR);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"ipAddrPresent",  &ipAddrPresent);

   if (ipAddrPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ipAddrIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ipAddrIeInst",  &egIe.ieInst);

      egIe.t.ipAddr.type = DFLT_IPADDR_TYPE_VAL;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                     (Txt *)"type", &egIe.t.ipAddr.type);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ipAddr", &ipAddr);

      switch (egIe.t.ipAddr.type)
      {
         case CM_NETADDR_IPV4:
         {
            cmInetAddr ( (S8 *)ipAddr, &(egIe.t.ipAddr.u.ipv4));
            break;
         } /* end of case */

#ifdef IPV6_SUPPORTED
         case CM_NETADDR_IPV6:
         {
            cmInetPton6(&egIe.t.ipAddr.u.ipv6, (S8*)ipAddr);
            break;
         } /* end of case */
#endif /* end of IPV6_SUPPORTED */

         default:
         {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddIpAddrIe: Invalid IP Address Type\n"));
            RETVOID;
         } /* end of case */
      } /* end of switch */

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddIpAddrIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddIpAddrIe */


/*
*
*       Fun:   makeAndAddPortIe
*
*       Desc:  This function is used to Build eGTP Port IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPortIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPortIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     portPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPortIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_PORT_IETYPE, ieProp.ieInst, EG_UNSIGNED_16);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"portPresent",  &portPresent);

   if (portPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"portIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"portIeInst",  &egIe.ieInst);

      egIe.t.valUnSgnd16 = DFLT_PORT;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                     (Txt *)"port", &egIe.t.valUnSgnd16);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddPortIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddPortIe */


/*
*
*       Fun:   makeAndAddHopCntrIe
*
*       Desc:  This function is used to Build eGTP Hop Counter IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddHopCntrIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddHopCntrIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     hopCntrPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddHopCntrIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_HOP_CNTR_IETYPE, ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"hopCntrPresent",  &hopCntrPresent);

   if (hopCntrPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"hopCntrIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"hopCntrIeInst",  &egIe.ieInst);

      egIe.t.valUnSgnd8 = DFLT_HOP_CNTR;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"hopCntr", &egIe.t.valUnSgnd8);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddHopCntrIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddHopCntrIe */

/*
*
*       Fun:   makeAndAddGsmKeyTripIe
*
*       Desc:  This function is used to Build eGTP GSM Key Triplet IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddGsmKeyTripIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddGsmKeyTripIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   data[64] = {0};
   U8     present  = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddGsmKeyTripIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_GSM_KEY_TRIP_IETYPE, ieProp.ieInst, EG_GSM_KEY_TRIP);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"gsmKeyTripPresent", &present);

   if (present)
   {
      egIe.t.gsmKeyT.secMode = DFLT_SECMODE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"secMode",  &egIe.t.gsmKeyT.secMode);

      egIe.t.gsmKeyT.isDRXIPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
             (Txt *)"isDRXIPres",  &egIe.t.gsmKeyT.isDRXIPres);

     egIe.t.gsmKeyT.isUAMBRIPres = TRUE;
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
     (Txt *)"isUAMBRIPres",  &egIe.t.gsmKeyT.isUAMBRIPres);

     egIe.t.gsmKeyT.isSAMBRIPres = TRUE;
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
     (Txt *)"isSAMBRIPres",  &egIe.t.gsmKeyT.isSAMBRIPres);

     egIe.t.gsmKeyT.upSubsUEAMBR = DFLT_UPSUBSUEAMBR;
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
     (Txt *)"upSubsUEAMBR",  &egIe.t.gsmKeyT.upSubsUEAMBR);

     egIe.t.gsmKeyT.dnSubsUEAMBR = DFLT_DNSUBSUEAMBR;
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
     (Txt *)"dnSubsUEAMBR",  &egIe.t.gsmKeyT.dnSubsUEAMBR);

     egIe.t.gsmKeyT.upUsedUEAMBR = DFLT_UPUSEDUEAMBR;
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
     (Txt *)"upUsedUEAMBR",  &egIe.t.gsmKeyT.upUsedUEAMBR);

     egIe.t.gsmKeyT.dnUsedUEAMBR = DFLT_DNUSEDUEAMBR;
     cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
     (Txt *)"dnUsedUEAMBR",  &egIe.t.gsmKeyT.dnUsedUEAMBR);

      egIe.t.gsmKeyT.cksn = DFLT_CKSN;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"cksn",  &egIe.t.gsmKeyT.cksn);

   
      egIe.t.gsmKeyT.usedCipher = DFLT_USED_CIPHER;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"usedCipher",  &egIe.t.gsmKeyT.usedCipher);

      cmMemcpy( (U8* )egIe.t.gsmKeyT.kc, (U8* )DFLT_KC, DFLT_KC_LEN);
      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"kc", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy( (U8 *)egIe.t.gsmKeyT.kc, (U8 *)data, cmStrlen(data));
      } /* end of if */

      egIe.t.gsmKeyT.nmbTrip = DFLT_NMBTRIP;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nmbTrip",  &egIe.t.gsmKeyT.nmbTrip);

      cmMemcpy( (U8* )egIe.t.gsmKeyT.authTrip[0].rand, (U8* )DFLT_AUTH_TRIP_RAND_VAL,DFLT_AUTH_TRIP_RAND_LEN);
      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"authTrip_rand", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy((U8 *)egIe.t.gsmKeyT.authTrip[0].rand, (U8 *)data,cmStrlen((U8 *)data));
      } /* end of if */

      cmMemcpy( (U8* )egIe.t.gsmKeyT.authTrip[0].sres, (U8*)DFLT_AUTH_TRIP_SRES_VAL,DFLT_AUTH_TRIP_SRES_LEN);
      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"authTrip_sres", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy((U8 *)egIe.t.gsmKeyT.authTrip[0].sres, (U8 *)data,cmStrlen((U8 *)data));
      } /* end of if */

      cmMemcpy( (U8* )egIe.t.gsmKeyT.authTrip[0].kc, (U8* )DFLT_AUTH_TRIP_KC_VAL,DFLT_AUTH_TRIP_KC_LEN);
      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"authTrip_kc", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy((U8 *)egIe.t.gsmKeyT.authTrip[0].kc, (U8 *)data,cmStrlen((U8 *)data));
      } /* end of if */

      cmMemcpy( (U8* )egIe.t.gsmKeyT.drxParam, (U8* )DFLT_DRXPARAM, DFLT_DRXPARAM_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"drxParam", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy( (U8 *)egIe.t.gsmKeyT.drxParam, (U8 *)data, cmStrlen(data));
      } /* end of if */

      egIe.t.gsmKeyT.ueNtwrkCapb.length = DFLT_UE_NTWRK_CAPB_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyT.ueNtwrkCapb.val, (U8* )DFLT_UE_NTWRK_CAPB, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ueNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyT.ueNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyT.ueNtwrkCapb.val, (U8 *)data, egIe.t.gsmKeyT.ueNtwrkCapb.length);
      } /* end of if */


      egIe.t.gsmKeyT.msNtwrkCapb.length = DFLT_MS_NTWRK_CAPB_LEN;
      cmMemcpy((U8* )egIe.t.gsmKeyT.msNtwrkCapb.val, (U8*)DFLT_MS_NTWRK_CAPB_VAL,DFLT_MS_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"msNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyT.msNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyT.msNtwrkCapb.val, (U8 *)data,egIe.t.gsmKeyT.msNtwrkCapb.length);
      } /* end of if */


      egIe.t.gsmKeyT.meId.length = DFLT_MEID_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyT.meId.val, (U8* )DFLT_MEID, DFLT_MEID_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"meId", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyT.meId.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyT.meId.val, (U8 *)data, egIe.t.gsmKeyT.meId.length);
      } /* end of if */

      egIe.t.gsmKeyT.isUNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isUNA",  &egIe.t.gsmKeyT.isUNA);

      egIe.t.gsmKeyT.isGENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isGENA",  &egIe.t.gsmKeyT.isGENA);

      egIe.t.gsmKeyT.isGANA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
            (Txt *)"isGANA",  &egIe.t.gsmKeyT.isGANA);

      egIe.t.gsmKeyT.isINA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isINA",  &egIe.t.gsmKeyT.isINA);

      egIe.t.gsmKeyT.isENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isENA",  &egIe.t.gsmKeyT.isENA);

      egIe.t.gsmKeyT.isHNNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isHNNA",  &egIe.t.gsmKeyT.isHNNA);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddGsmKeyTripIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddGsmKeyTripIe */


/*
*
*       Fun:   makeAndAddUmtsKeyCiphQuinIe
*
*       Desc:  This function is used to Build eGTP UMTS Key Cipher Quintuplet IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddUmtsKeyCiphQuinIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddUmtsKeyCiphQuinIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   data[17] = {0};
   U8     present  = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddUmtsKeyCiphQuinIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_UMTS_KEY_CIPH_QUIN_IETYPE, ieProp.ieInst, EG_UMTS_KEY_CIPH_QUIN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"umtsKeyCQPresent", &present);

   if (present)
   {
      egIe.t.umtsKeyUCQt.secMode = DFLT_SECMODE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"secMode",  &egIe.t.umtsKeyUCQt.secMode);

      egIe.t.umtsKeyUCQt.cksn = DFLT_CKSN;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"cksn",  &egIe.t.umtsKeyUCQt.cksn);

      egIe.t.umtsKeyUCQt.nmbQuin = DFLT_NMBQUIN;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nmbQuin",  &egIe.t.umtsKeyUCQt.nmbQuin);

      egIe.t.umtsKeyUCQt.usedCipher = DFLT_USED_CIPHER;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"usedCipher",  &egIe.t.umtsKeyUCQt.usedCipher);

      egIe.t.umtsKeyUCQt.ck.length = DFLT_CK_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.ck.val, (U8* )DFLT_CK, DFLT_CK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ck", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.ck.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.ck.val, (U8 *)data, egIe.t.umtsKeyUCQt.ck.length);
      } /* end of if */

      egIe.t.umtsKeyUCQt.ik.length = DFLT_IK_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.ik.val, (U8* )DFLT_IK, DFLT_IK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ik", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.ik.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.ik.val, (U8 *)data, egIe.t.umtsKeyUCQt.ik.length);
      } /* end of if */

      egIe.t.umtsKeyUCQt.authQuin[0].rand.length = DFLT_RAND_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.authQuin[0].rand.val, (U8* )DFLT_RAND, DFLT_RAND_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"rand", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.authQuin[0].rand.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.authQuin[0].rand.val, (U8 *)data, egIe.t.umtsKeyUCQt.authQuin[0].rand.length);
      } /* end of if */

      egIe.t.umtsKeyUCQt.authQuin[0].xresLen = DFLT_XRES_LEN;
      egIe.t.umtsKeyUCQt.authQuin[0].xres.length = DFLT_XRES_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.authQuin[0].xres.val, (U8* )DFLT_XRES, DFLT_XRES_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"xresLen",  &egIe.t.umtsKeyUCQt.authQuin[0].xresLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"xres", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.authQuin[0].xres.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.authQuin[0].xres.val, (U8 *)data, egIe.t.umtsKeyUCQt.authQuin[0].xres.length);
      } /* end of if */

      egIe.t.umtsKeyUCQt.authQuin[0].ck.length = DFLT_CK_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.authQuin[0].ck.val, (U8* )DFLT_CK, DFLT_CK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ck", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.authQuin[0].ck.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.ck.val, (U8 *)data, egIe.t.umtsKeyUCQt.authQuin[0].ck.length);
      } /* end of if */

      egIe.t.umtsKeyUCQt.authQuin[0].ik.length = DFLT_IK_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.authQuin[0].ik.val, (U8* )DFLT_IK, DFLT_IK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ik", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.authQuin[0].ik.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.ik.val, (U8 *)data, egIe.t.umtsKeyUCQt.authQuin[0].ik.length);
      } /* end of if */

      egIe.t.umtsKeyUCQt.authQuin[0].autnLen = DFLT_AUTN_LEN;
      egIe.t.umtsKeyUCQt.authQuin[0].autn.length = DFLT_AUTN_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.authQuin[0].autn.val, (U8* )DFLT_AUTN, DFLT_AUTN_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"autnLen",  &egIe.t.umtsKeyUCQt.authQuin[0].autnLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"autn", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.authQuin[0].autn.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.authQuin[0].autn.val, (U8 *)data, egIe.t.umtsKeyUCQt.authQuin[0].autn.length);
      } /* end of if */

      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.drxParam, (U8* )DFLT_DRXPARAM, DFLT_DRXPARAM_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"drxParam", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.drxParam, (U8 *)data, cmStrlen(data));
      } /* end of if */

      egIe.t.umtsKeyUCQt.upSubsUEAMBR = DFLT_UPSUBSUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"upSubsUEAMBR",  &egIe.t.umtsKeyUCQt.upSubsUEAMBR);

      egIe.t.umtsKeyUCQt.dnSubsUEAMBR = DFLT_DNSUBSUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"dnSubsUEAMBR",  &egIe.t.umtsKeyUCQt.dnSubsUEAMBR);

      egIe.t.umtsKeyUCQt.upUsedUEAMBR = DFLT_UPUSEDUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"upUsedUEAMBR",  &egIe.t.umtsKeyUCQt.upUsedUEAMBR);

      egIe.t.umtsKeyUCQt.dnUsedUEAMBR = DFLT_DNUSEDUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"dnUsedUEAMBR",  &egIe.t.umtsKeyUCQt.dnUsedUEAMBR);

      egIe.t.umtsKeyUCQt.ueNtwrkCapb.length = DFLT_UE_NTWRK_CAPB_LEN;

      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.ueNtwrkCapb.val, (U8* )DFLT_UE_NTWRK_CAPB, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ueNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.ueNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.ueNtwrkCapb.val, (U8 *)data, egIe.t.umtsKeyUCQt.ueNtwrkCapb.length);
      } /* end of if */

      egIe.t.umtsKeyUCQt.msNtwrkCapb.length = DFLT_MS_NTWRK_CAPB_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.msNtwrkCapb.val, (U8* )DFLT_MS_NTWRK_CAPB_VAL, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"msNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.msNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.msNtwrkCapb.val, (U8 *)data, egIe.t.umtsKeyUCQt.msNtwrkCapb.length);
      } /* end of if */


      egIe.t.umtsKeyUCQt.meId.length = DFLT_MEID_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyUCQt.meId.val, (U8* )DFLT_MEID, DFLT_MEID_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"meId", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyUCQt.meId.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyUCQt.meId.val, (U8 *)data, egIe.t.umtsKeyUCQt.meId.length);
      } /* end of if */

      egIe.t.umtsKeyUCQt.isUNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isUNA",  &egIe.t.umtsKeyUCQt.isUNA);

      egIe.t.umtsKeyUCQt.isGENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isGENA",  &egIe.t.umtsKeyUCQt.isGENA);

      egIe.t.umtsKeyUCQt.isGANA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
            (Txt *)"isGANA",  &egIe.t.umtsKeyUCQt.isGANA);

      egIe.t.umtsKeyUCQt.isINA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isINA",  &egIe.t.umtsKeyUCQt.isINA);

      egIe.t.umtsKeyUCQt.isENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isENA",  &egIe.t.umtsKeyUCQt.isENA);

      egIe.t.umtsKeyUCQt.isHNNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isHNNA",  &egIe.t.umtsKeyUCQt.isHNNA);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddUmtsKeyCiphQuinIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddUmtsKeyCiphQuinIe */


/*
*
*       Fun:   makeAndAddGsmKeyCiphQuinIe
*
*       Desc:  This function is used to Build eGTP GSM Key Cipher Quintuplet IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddGsmKeyCiphQuinIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddGsmKeyCiphQuinIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   data[1024] = {0};
   U8     present  = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddGsmKeyCiphQuinIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_GSM_KEY_CIPH_QUIN_IETYPE, ieProp.ieInst, EG_GSM_KEY_CIPH_QUIN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"gsmKeyCQPresent", &present);

   if (present)
   {
      egIe.t.gsmKeyUCQt.secMode = DFLT_SECMODE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"secMode",  &egIe.t.gsmKeyUCQt.secMode);

      egIe.t.gsmKeyUCQt.isDRXIPres = TRUE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"DRXIPres",  &egIe.t.gsmKeyUCQt.isDRXIPres);


      egIe.t.gsmKeyUCQt.cksn = DFLT_CKSN;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"cksn",  &egIe.t.gsmKeyUCQt.cksn);

      egIe.t.gsmKeyUCQt.nmbQuin = DFLT_NMBQUIN;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nmbQuin",  &egIe.t.gsmKeyUCQt.nmbQuin);

      egIe.t.gsmKeyUCQt.isUAMBRIPres = TRUE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"UAMBRIPres",  &egIe.t.gsmKeyUCQt.isUAMBRIPres);

      egIe.t.gsmKeyUCQt.isSAMBRIPres = TRUE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"SAMBRIPres",  &egIe.t.gsmKeyUCQt.isSAMBRIPres);

      egIe.t.gsmKeyUCQt.usedCipher = DFLT_USED_CIPHER;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"usedCipher",  &egIe.t.gsmKeyUCQt.usedCipher);

      cmMemcpy(egIe.t.gsmKeyUCQt.kc, (U8* )DFLT_KC, DFLT_KC_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"kc", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy(egIe.t.gsmKeyUCQt.kc, (U8 *)data, cmStrlen(data));
      } /* end of if */

      egIe.t.gsmKeyUCQt.authQuin[0].rand.length = DFLT_RAND_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.authQuin[0].rand.val, (U8* )DFLT_RAND, DFLT_RAND_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"rand", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyUCQt.authQuin[0].rand.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.authQuin[0].rand.val, (U8 *)data,egIe.t.gsmKeyUCQt.authQuin[0].rand.length);
      } /* end of if */

      egIe.t.gsmKeyUCQt.authQuin[0].xresLen = DFLT_XRES_LEN;
      egIe.t.gsmKeyUCQt.authQuin[0].xres.length = DFLT_XRES_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.authQuin[0].xres.val, (U8* )DFLT_XRES, DFLT_XRES_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"xresLen",  &egIe.t.gsmKeyUCQt.authQuin[0].xresLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"xres", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyUCQt.authQuin[0].xres.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.authQuin[0].xres.val, (U8 *)data,egIe.t.gsmKeyUCQt.authQuin[0].xres.length);
      } /* end of if */

      egIe.t.gsmKeyUCQt.authQuin[0].ck.length = DFLT_CK_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.authQuin[0].ck.val, (U8* )DFLT_CK, DFLT_CK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ck", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyUCQt.authQuin[0].ck.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.authQuin[0].ck.val, (U8 *)data,egIe.t.gsmKeyUCQt.authQuin[0].ck.length);
      } /* end of if */

      egIe.t.gsmKeyUCQt.authQuin[0].ik.length = DFLT_IK_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.authQuin[0].ik.val, (U8* )DFLT_IK, DFLT_IK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ik", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyUCQt.authQuin[0].ik.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.authQuin[0].ik.val, (U8 *)data,egIe.t.gsmKeyUCQt.authQuin[0].ik.length);
      } /* end of if */

      egIe.t.gsmKeyUCQt.authQuin[0].autnLen = DFLT_AUTN_LEN;
      egIe.t.gsmKeyUCQt.authQuin[0].autn.length = DFLT_AUTN_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.authQuin[0].autn.val, (U8* )DFLT_AUTN, DFLT_AUTN_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"autnLen",  &egIe.t.gsmKeyUCQt.authQuin[0].autnLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"autn", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyUCQt.authQuin[0].autn.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.authQuin[0].autn.val, (U8 *)data,egIe.t.gsmKeyUCQt.authQuin[0].autn.length);
      } /* end of if */

      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.drxParam, (U8* )DFLT_DRXPARAM, DFLT_DRXPARAM_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"drxParam", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.drxParam, (U8 *)data, cmStrlen(data));
      } /* end of if */

      egIe.t.gsmKeyUCQt.upSubsUEAMBR = DFLT_UPSUBSUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"upSubsUEAMBR",  &egIe.t.gsmKeyUCQt.upSubsUEAMBR);

      egIe.t.gsmKeyUCQt.dnSubsUEAMBR = DFLT_DNSUBSUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"dnSubsUEAMBR",  &egIe.t.gsmKeyUCQt.dnSubsUEAMBR);

      egIe.t.gsmKeyUCQt.upUsedUEAMBR = DFLT_UPUSEDUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"upUsedUEAMBR",  &egIe.t.gsmKeyUCQt.upUsedUEAMBR);

      egIe.t.gsmKeyUCQt.dnUsedUEAMBR = DFLT_DNUSEDUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"dnUsedUEAMBR",  &egIe.t.gsmKeyUCQt.dnUsedUEAMBR);

      egIe.t.gsmKeyUCQt.ueNtwrkCapb.length = DFLT_UE_NTWRK_CAPB_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.ueNtwrkCapb.val, (U8* )DFLT_UE_NTWRK_CAPB, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ueNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyUCQt.ueNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.ueNtwrkCapb.val, (U8 *)data, egIe.t.gsmKeyUCQt.ueNtwrkCapb.length);
      } /* end of if */

      egIe.t.gsmKeyUCQt.msNtwrkCapb.length = DFLT_MS_NTWRK_CAPB_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.msNtwrkCapb.val, (U8* )DFLT_MS_NTWRK_CAPB_VAL, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"msNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyUCQt.msNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.ueNtwrkCapb.val, (U8 *)data, egIe.t.gsmKeyUCQt.ueNtwrkCapb.length);
      } /* end of if */

      egIe.t.gsmKeyUCQt.meId.length = DFLT_MEID_LEN;
      cmMemcpy( (U8* )egIe.t.gsmKeyUCQt.meId.val, (U8* )DFLT_MEID, DFLT_MEID_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"meId", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.gsmKeyUCQt.meId.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.gsmKeyUCQt.meId.val, (U8 *)data, egIe.t.gsmKeyUCQt.meId.length);
      } /* end of if */


      egIe.t.gsmKeyUCQt.isUNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isUNA",  &egIe.t.gsmKeyUCQt.isUNA);

      egIe.t.gsmKeyUCQt.isGENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isGENA",  &egIe.t.gsmKeyUCQt.isGENA);

      egIe.t.gsmKeyUCQt.isGANA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
            (Txt *)"isGANA",  &egIe.t.gsmKeyUCQt.isGANA);

      egIe.t.gsmKeyUCQt.isINA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isINA",  &egIe.t.gsmKeyUCQt.isINA);

      egIe.t.gsmKeyUCQt.isENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isENA",  &egIe.t.gsmKeyUCQt.isENA);

      egIe.t.gsmKeyUCQt.isHNNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isHNNA",  &egIe.t.gsmKeyUCQt.isHNNA);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddGsmKeyCiphQuinIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddGsmKeyCiphQuinIe */


/*
*
*       Fun:   makeAndAddUmtsKeyQuinIe
*
*       Desc:  This function is used to Build eGTP UMTS Key Quintuplet IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddUmtsKeyQuinIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddUmtsKeyQuinIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   data[1024] = {0};
   U8     present  = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddUmtsKeyQuinIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_UMTS_KEY_QUIN_IETYPE, ieProp.ieInst, EG_UMTS_KEY_QUIN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"umtsKeyQPresent", &present);

   if (present)
   {
      egIe.t.umtsKeyQt.secMode = DFLT_SECMODE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"secMode",  &egIe.t.umtsKeyQt.secMode);

      egIe.t.umtsKeyQt.isDRXIPres = TRUE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"DRXIPres",  &egIe.t.umtsKeyQt.isDRXIPres);

      egIe.t.umtsKeyQt.ksi = DFLT_KSI;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ksi",  &egIe.t.umtsKeyQt.ksi);

      egIe.t.umtsKeyQt.nmbQuin = DFLT_NMBQUIN;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nmbQuin",  &egIe.t.umtsKeyQt.nmbQuin);

      egIe.t.umtsKeyQt.isUAMBRIPres = TRUE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"UAMBRIPres",  &egIe.t.umtsKeyQt.isUAMBRIPres);

      egIe.t.umtsKeyQt.isSAMBRIPres = TRUE;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"SAMBRIPres",  &egIe.t.umtsKeyQt.isSAMBRIPres);

      egIe.t.umtsKeyQt.ck.length = DFLT_CK_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.ck.val, (U8* )DFLT_CK, DFLT_CK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ck", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.ck.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.ck.val, (U8 *)data, egIe.t.umtsKeyQt.ck.length);
      } /* end of if */

      egIe.t.umtsKeyQt.ik.length = DFLT_IK_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.ik.val, (U8* )DFLT_IK, DFLT_IK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ik", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.ik.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.ik.val, (U8 *)data, egIe.t.umtsKeyQt.ik.length);
      } /* end of if */

      egIe.t.umtsKeyQt.authQuin[0].rand.length = DFLT_RAND_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.authQuin[0].rand.val, (U8* )DFLT_RAND, DFLT_RAND_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"rand", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.authQuin[0].rand.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.authQuin[0].rand.val, (U8 *)data, egIe.t.umtsKeyQt.authQuin[0].rand.length);
      } /* end of if */

      egIe.t.umtsKeyQt.authQuin[0].xresLen = DFLT_XRES_LEN;
      egIe.t.umtsKeyQt.authQuin[0].xres.length = DFLT_XRES_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.authQuin[0].xres.val, (U8* )DFLT_XRES, DFLT_XRES_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"xresLen",  &egIe.t.umtsKeyQt.authQuin[0].xresLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"xres", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.authQuin[0].xres.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.authQuin[0].xres.val, (U8 *)data, egIe.t.umtsKeyQt.authQuin[0].xres.length);
      } /* end of if */

      egIe.t.umtsKeyQt.authQuin[0].ck.length = DFLT_CK_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.authQuin[0].ck.val, (U8* )DFLT_CK, DFLT_CK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ck", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.authQuin[0].ck.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.ck.val, (U8 *)data, egIe.t.umtsKeyQt.authQuin[0].ck.length);
      } /* end of if */

      egIe.t.umtsKeyQt.authQuin[0].ik.length = DFLT_IK_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.authQuin[0].ik.val, (U8* )DFLT_IK, DFLT_IK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ik", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.authQuin[0].ik.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.ik.val, (U8 *)data, egIe.t.umtsKeyQt.authQuin[0].ik.length);
      } /* end of if */

      egIe.t.umtsKeyQt.authQuin[0].autnLen = DFLT_AUTN_LEN;
      egIe.t.umtsKeyQt.authQuin[0].autn.length = DFLT_AUTN_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.authQuin[0].autn.val, (U8* )DFLT_AUTN, DFLT_AUTN_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"autnLen",  &egIe.t.umtsKeyQt.authQuin[0].autnLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"autn", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.authQuin[0].autn.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.authQuin[0].autn.val, (U8 *)data, egIe.t.umtsKeyQt.authQuin[0].autn.length);
      } /* end of if */

      cmMemcpy( (U8* )egIe.t.umtsKeyQt.drxParam, (U8* )DFLT_DRXPARAM, DFLT_DRXPARAM_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"drxParam", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.drxParam, (U8 *)data, cmStrlen(data));
      } /* end of if */

      egIe.t.umtsKeyQt.upSubsUEAMBR = DFLT_UPSUBSUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"upSubsUEAMBR",  &egIe.t.umtsKeyQt.upSubsUEAMBR);

      egIe.t.umtsKeyQt.dnSubsUEAMBR = DFLT_DNSUBSUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"dnSubsUEAMBR",  &egIe.t.umtsKeyQt.dnSubsUEAMBR);

      egIe.t.umtsKeyQt.upUsedUEAMBR = DFLT_UPUSEDUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"upUsedUEAMBR",  &egIe.t.umtsKeyQt.upUsedUEAMBR);

      egIe.t.umtsKeyQt.dnUsedUEAMBR = DFLT_DNUSEDUEAMBR;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
      (Txt *)"dnUsedUEAMBR",  &egIe.t.umtsKeyQt.dnUsedUEAMBR);

      egIe.t.umtsKeyQt.ueNtwrkCapb.length = DFLT_UE_NTWRK_CAPB_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.ueNtwrkCapb.val, (U8* )DFLT_UE_NTWRK_CAPB, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ueNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.ueNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.ueNtwrkCapb.val, (U8 *)data, egIe.t.umtsKeyQt.ueNtwrkCapb.length);
      } /* end of if */

      egIe.t.umtsKeyQt.msNtwrkCapb.length = DFLT_MS_NTWRK_CAPB_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.msNtwrkCapb.val, (U8* )DFLT_MS_NTWRK_CAPB_VAL, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"msNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.msNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.msNtwrkCapb.val, (U8 *)data,egIe.t.umtsKeyQt.msNtwrkCapb.length);
      } /* end of if */

      egIe.t.umtsKeyQt.meId.length = DFLT_MEID_LEN;
      cmMemcpy( (U8* )egIe.t.umtsKeyQt.meId.val, (U8* )DFLT_MEID, DFLT_MEID_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"meId", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.umtsKeyQt.meId.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.umtsKeyQt.meId.val, (U8 *)data, egIe.t.umtsKeyQt.meId.length);
      } /* end of if */

      egIe.t.umtsKeyQt.isUNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isUNA",  &egIe.t.umtsKeyQt.isUNA);

      egIe.t.umtsKeyQt.isGENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isGENA",  &egIe.t.umtsKeyQt.isGENA);

      egIe.t.umtsKeyQt.isGANA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
            (Txt *)"isGANA",  &egIe.t.umtsKeyQt.isGANA);

      egIe.t.umtsKeyQt.isINA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isINA",  &egIe.t.umtsKeyQt.isINA);

      egIe.t.umtsKeyQt.isENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isENA",  &egIe.t.umtsKeyQt.isENA);

      egIe.t.umtsKeyQt.isHNNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isHNNA",  &egIe.t.umtsKeyQt.isHNNA);


      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddUmtsKeyQuinIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddUmtsKeyQuinIe */


/*
*
*       Fun:   makeAndAddEpsSecQdQtIe
*
*       Desc:  This function is used to Build eGTP EPS Security Context
*              Quadruplets Quintuplets IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddEpsSecQdQtIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddEpsSecQdQtIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   data[1024] = {0};
   U8     present  = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddEpsSecQdQtIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_EPS_SEC_QUAD_QUIN_IETYPE, ieProp.ieInst, EG_EPS_SEC_QUAD_QUIN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"epsSecQdQtPresent", &present);

   if (present)
   {
      egIe.t.eSecCxtQdQt.secMode = DFLT_SECMODE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"secMode",  &egIe.t.eSecCxtQdQt.secMode);

      egIe.t.eSecCxtQdQt.isDRXIPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"DRXIPres",  &egIe.t.eSecCxtQdQt.isDRXIPres);

      egIe.t.eSecCxtQdQt.isNHIPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"NHIPres",  &egIe.t.eSecCxtQdQt.isNHIPres);

      egIe.t.eSecCxtQdQt.ksi = DFLT_KSI;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"ksi",  &egIe.t.eSecCxtQdQt.ksi);

      egIe.t.eSecCxtQdQt.nmbQuin = DFLT_NMBQUIN;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nmbQuin",  &egIe.t.eSecCxtQdQt.nmbQuin);

      egIe.t.eSecCxtQdQt.nmbQuadru = DFLT_NMBQUAD;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nmbQuadru",  &egIe.t.eSecCxtQdQt.nmbQuadru);

      egIe.t.eSecCxtQdQt.isUAMBRIPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"UAMBRIPres",  &egIe.t.eSecCxtQdQt.isUAMBRIPres);

      egIe.t.eSecCxtQdQt.isOCSIPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"OCSIPres",  &egIe.t.eSecCxtQdQt.isOCSIPres);

      egIe.t.eSecCxtQdQt.isSAMBRIPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"SAMBRIPres",  &egIe.t.eSecCxtQdQt.isSAMBRIPres);

      egIe.t.eSecCxtQdQt.nasProtAlgo = DFLT_USED_NAS_PROT_ALGO;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nasProtAlgo",  &egIe.t.eSecCxtQdQt.nasProtAlgo);

      egIe.t.eSecCxtQdQt.usedNasCipher = DFLT_USED_NAS_CIPHER;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"usedNasCipher",  &egIe.t.eSecCxtQdQt.usedNasCipher);

      egIe.t.eSecCxtQdQt.nasDlCount = DFLT_NAS_DLCOUNT;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nasDlCount",  &egIe.t.eSecCxtQdQt.nasDlCount);

      egIe.t.eSecCxtQdQt.nasUlCount = DFLT_NAS_ULCOUNT;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nasUlCount",  &egIe.t.eSecCxtQdQt.nasUlCount);

      egIe.t.eSecCxtQdQt.kasme.length = DFLT_KASME_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.kasme.val, (U8* )DFLT_KASME, DFLT_KASME_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"kasme", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.kasme.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.kasme.val, (U8 *)data, egIe.t.eSecCxtQdQt.kasme.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuadru[0].rand.length = DFLT_RAND_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuadru[0].rand.val, (U8* )DFLT_RAND, DFLT_RAND_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"rand", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuadru[0].rand.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuadru[0].rand.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuadru[0].rand.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuadru[0].xresLen = DFLT_XRES_LEN;
      egIe.t.eSecCxtQdQt.authQuadru[0].xres.length = DFLT_XRES_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuadru[0].xres.val, (U8* )DFLT_XRES, DFLT_XRES_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"xresLen",  &egIe.t.eSecCxtQdQt.authQuadru[0].xresLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"xres", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuadru[0].xres.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuadru[0].xres.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuadru[0].xres.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuadru[0].autnLen = DFLT_AUTN_LEN;
      egIe.t.eSecCxtQdQt.authQuadru[0].autn.length = DFLT_AUTN_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuadru[0].autn.val, (U8* )DFLT_AUTN, DFLT_AUTN_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"autnLen",  &egIe.t.eSecCxtQdQt.authQuadru[0].autnLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"autn", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuadru[0].autn.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuadru[0].autn.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuadru[0].autn.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuadru[0].kasme.length = DFLT_KASME_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuadru[0].kasme.val, (U8* )DFLT_KASME, DFLT_KASME_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"kasme", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuadru[0].kasme.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuadru[0].kasme.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuadru[0].kasme.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuin[0].rand.length = DFLT_RAND_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuin[0].rand.val, (U8* )DFLT_RAND, DFLT_RAND_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"rand", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuin[0].rand.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuin[0].rand.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuin[0].rand.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuin[0].xresLen = DFLT_XRES_LEN;
      egIe.t.eSecCxtQdQt.authQuin[0].xres.length = DFLT_XRES_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuin[0].xres.val, (U8* )DFLT_XRES, DFLT_XRES_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"xresLen",  &egIe.t.eSecCxtQdQt.authQuin[0].xresLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"xres", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuin[0].xres.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuin[0].xres.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuin[0].xres.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuin[0].ck.length = DFLT_CK_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuin[0].ck.val, (U8* )DFLT_CK, DFLT_CK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ck", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuin[0].ck.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuin[0].ck.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuin[0].ck.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuin[0].ik.length = DFLT_IK_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuin[0].ik.val, (U8* )DFLT_IK, DFLT_IK_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ik", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuin[0].ik.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuin[0].ik.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuin[0].ik.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.authQuin[0].autnLen = DFLT_AUTN_LEN;
      egIe.t.eSecCxtQdQt.authQuin[0].autn.length = DFLT_AUTN_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.authQuin[0].autn.val, (U8* )DFLT_AUTN, DFLT_AUTN_LEN);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"autnLen",  &egIe.t.eSecCxtQdQt.authQuin[0].autnLen);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"autn", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.authQuin[0].autn.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.authQuin[0].autn.val, (U8 *)data, egIe.t.eSecCxtQdQt.authQuin[0].autn.length);
      } /* end of if */

      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.drxParam, (U8* )DFLT_DRXPARAM, DFLT_DRXPARAM_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"drxParam", data) != CMXTA_ERR_NO_VALUE)
      {
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.drxParam, (U8 *)data, cmStrlen(data));
      } /* end of if */

      egIe.t.eSecCxtQdQt.ueNtwrkCapb.length = DFLT_UE_NTWRK_CAPB_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.ueNtwrkCapb.val, (U8* )DFLT_UE_NTWRK_CAPB, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ueNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.ueNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.ueNtwrkCapb.val, (U8 *)data, egIe.t.eSecCxtQdQt.ueNtwrkCapb.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.msNtwrkCapb.length = DFLT_MS_NTWRK_CAPB_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.msNtwrkCapb.val, (U8* )DFLT_MS_NTWRK_CAPB_VAL, DFLT_UE_NTWRK_CAPB_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"ueNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.msNtwrkCapb.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.msNtwrkCapb.val, (U8 *)data, egIe.t.eSecCxtQdQt.msNtwrkCapb.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.meId.length = DFLT_MEID_LEN;
      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.meId.val, (U8* )DFLT_MEID, DFLT_MEID_LEN);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"meId", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.eSecCxtQdQt.meId.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.meId.val, (U8 *)data, egIe.t.eSecCxtQdQt.meId.length);
      } /* end of if */

      egIe.t.eSecCxtQdQt.isUNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isUNA",  &egIe.t.eSecCxtQdQt.isUNA);

      egIe.t.eSecCxtQdQt.isGENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isGENA",  &egIe.t.eSecCxtQdQt.isGENA);

      egIe.t.eSecCxtQdQt.isGANA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
            (Txt *)"isGANA",  &egIe.t.eSecCxtQdQt.isGANA);

      egIe.t.eSecCxtQdQt.isINA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isINA",  &egIe.t.eSecCxtQdQt.isINA);

      egIe.t.eSecCxtQdQt.isENA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isENA",  &egIe.t.eSecCxtQdQt.isENA);

      egIe.t.eSecCxtQdQt.isHNNA = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"isHNNA",  &egIe.t.eSecCxtQdQt.isHNNA);

      /* Old NCC */
      egIe.t.eSecCxtQdQt.nccOld = DFLT_NCCOLD;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"nccOld",  &egIe.t.eSecCxtQdQt.nccOld);

      /* Old KSI */
      egIe.t.eSecCxtQdQt.ksiOld = DFLT_KSIOLD;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"ksiOld",  &egIe.t.eSecCxtQdQt.ksiOld);

      egIe.t.eSecCxtQdQt.isNHIOldPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
               (Txt *)"NHIOldPres",  &egIe.t.eSecCxtQdQt.isNHIOldPres);

      if(egIe.t.eSecCxtQdQt.isNHIOldPres)
      {
          egIe.t.eSecCxtQdQt.kasmeOld.length = DFLT_KASME_LEN;
          cmMemcpy((U8* )egIe.t.eSecCxtQdQt.kasmeOld.val, (U8*)DFLT_KASME, DFLT_KASME_LEN);
          if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                         (Txt *)"kasme", data) != CMXTA_ERR_NO_VALUE)
          {
             egIe.t.eSecCxtQdQt.kasmeOld.length = cmStrlen( (U8 *)data);
             cmMemcpy( (U8 *)egIe.t.eSecCxtQdQt.kasmeOld.val, (U8 *)data, egIe.t.eSecCxtQdQt.kasmeOld.length);
          } /* end of if */
      }

      cmMemcpy( (U8* )egIe.t.eSecCxtQdQt.nxtHopOld, (U8* )DFLT_NXT_HOP_OLD, DFLT_NXT_HOP_OLD_LEN);
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"nxtHopOld",egIe.t.eSecCxtQdQt.nxtHopOld);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddEpsSecQdQtIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddEpsSecQdQtIe */


/*
*
*       Fun:   makeAndAddPdnConnIe
*
*       Desc:  This function is used to Build eGTP EPS Security Context
*              Quadruplets Quintuplets IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPdnConnIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPdnConnIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     present  = TRUE;
   S16    idx  = 0;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPdnConnIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_PDN_CONN_IETYPE, ieProp.ieInst, EG_GROUPED);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"pdnConnPresent", &present);

   if (present)
   {
      /* append the parent ie */
      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddPdnConnIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }

      egLvlInfo->ieInfo[egLvlInfo->level].ieTypePres = TRUE;
      egLvlInfo->ieInfo[egLvlInfo->level].ieType     = EG_PDN_CONN_IETYPE;
      egLvlInfo->ieInfo[egLvlInfo->level].ieInst     = ieProp.ieInst;
      egLvlInfo->level = egLvlInfo->level + 1;

      for(idx = 0; idx < ieProp.groupedIe->nmbGrpIe; idx++)
      {
         switch(ieProp.groupedIe->ieProperties[idx].ieType)
         {
            case EG_APN_IETYPE:
            {
               makeAndAddAccessPntNameIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_IPADDR_IETYPE:
            {
               makeAndAddIpAddrIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_FTEID_IETYPE:
            {
               makeAndAddFTeidIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
               break;
            } /* end of case */

            case EG_BEARER_CNTX_IETYPE:
            {
               makeAndAddBrerCntxIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
               egLvlInfo->level = egLvlInfo->level - 1;
               break;
            } /* end of case */

				case EG_APN_RESTRICT_IETYPE:
				{
					makeAndAddMaxApnRestIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
					break;
				}

				case EG_SEL_MODE_IETYPE:
				{
					makeAndAddSelModeIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
					break;
				}

				case EG_FQDN_IETYPE:
				{
					makeAndAddFqdnIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
					break;
				}

				case EG_AMBR_IETYPE:
				{
					makeAndAddAmbrIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
					break;
				}

				case EG_CHARGING_CHAR_IETYPE:
				{
					makeAndAddChargCharIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
					break;
				}

				case EG_CNG_RPT_ACT_IETYPE:
				{
					makeAndAddCngRptActIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
					break;
				}

				case EG_EBI_IETYPE:
				{
					makeAndAddEbiIe(tcCb, spCb, egMsg, egLvlInfo, ieProp.groupedIe->ieProperties[idx]);
					break;
				}

            default:
            {
               break;
            } /* end of case */
         } /* end of switch case */
      } /* end of loop */
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddPdnConnIe */

/*
*
*       Fun:   makeAndAddImsiIe
*
*       Desc:  This function is used to Build eGTP Session Id AVP Header
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddImsiIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddImsiIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   Data   imsiVal[100] = DFLT_IMSI_VAL;
   U8     imsiPresent = TRUE;
   U8     imsiIeRepeat = FALSE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddImsiIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_IMSI_IETYPE,ieProp.ieInst, EG_STRING_16);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"imsiValue", imsiVal);
   egIe.t.valStr16.spare1 = 0;
   egIe.t.valStr16.length = cmStrlen((U8 *)imsiVal);
   cmMemcpy((U8 *) egIe.t.valStr16.val, (U8 *)imsiVal, egIe.t.valStr16.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"imsiPresent",  &imsiPresent);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"imsiIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"imsiIeInst",  &egIe.ieInst);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"imsiIeRepeat",  &imsiIeRepeat);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                  (Txt *)"imsiIeLen", &egIe.t.valStr16.length);

   if (imsiPresent == TRUE)
   {
      if(EgUtilGmAppendIe(egMsg,egLvlInfo,&egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddImsiAvblIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }

      if (imsiIeRepeat)
      {
         if(EgUtilGmAppendIe(egMsg,egLvlInfo,&egIe) != ROK)
         {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddImsiAvblIe: Unable to Append IE to eGTP message\n"));
            RETVOID;
         }
      }
   }

   RETVOID;
} /* end of makeAndAddImsiIe */


/*
*
*       Fun:   makeAndAddMsisdnIe
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddMsisdnIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddMsisdnIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   msisdnDat[100] = DFLT_MSISDN_VAL;
   U8     MsisdnPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddMsisdnIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_MSISDN_IETYPE,ieProp.ieInst, EG_STRING_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"MsisdnValue", msisdnDat);

   egIe.t.valStr32.length = cmStrlen((U8 *)msisdnDat);
   cmMemcpy((U8 *) egIe.t.valStr32.val, (U8 *)msisdnDat, egIe.t.valStr32.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"MsisdnIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"MsisdnPresent",  &MsisdnPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"MsisdnIeInst",  &egIe.ieInst);

/*
    cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"MsisdnIeCr",  &egIe.ieCr);
*/

   if( MsisdnPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddMsisdnIe() : Unable to Append IE to eGGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddMsisdnIe  */


/*
*
*       Fun:   makeAndAddMeiIe
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddMeiIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddMeiIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   meiDat[100] = DFLT_MEI_VAL;
   U8     MeiPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddMeiIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_MEI_IETYPE,ieProp.ieInst, EG_STRING_16);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"MeiValue", meiDat);

   egIe.t.valStr16.length = cmStrlen((U8 *)meiDat);
   cmMemcpy((U8 *) egIe.t.valStr16.val, (U8 *)meiDat, egIe.t.valStr16.length);
   egIe.t.valStr16.spare1 = 0;
#ifdef ALIGN_64BIT
   egIe.t.valStr16.spare2 = 0;
#endif

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"MeiIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"MeiPresent",  &MeiPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"MeiIeInst",  &egIe.ieInst);

   /*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"MeiIeCr",  &egIe.ieCr);
   */
   if( MeiPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddMeiIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddMeiIe  */


/*
*
*       Fun:   makeAndAddUsrLocInfoIe
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddUsrLocInfoIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddUsrLocInfoIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     usrLocInfoCgiPresent = TRUE;
   U8     usrLocInfoPres = TRUE;
   U8     usrLocInfoSaiPresent = TRUE;
   U8     usrLocInfoRaiPresent = TRUE;
   U8     usrLocInfoTaiPresent = TRUE;
   U8     usrLocInfoEcgiPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddUsrLocInfoIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_ULI_IETYPE, ieProp.ieInst, EG_ULI_DATA);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"UsrLocInfoCGIPres", &usrLocInfoCgiPresent);
   egIe.t.uli.isCGIPres = usrLocInfoCgiPresent;
   if (egIe.t.uli.isCGIPres)
   {
      egIe.t.uli.cgi.sNwk.mccDigit1 = 1;
      egIe.t.uli.cgi.sNwk.mccDigit2 = 1;
      egIe.t.uli.cgi.sNwk.mccDigit3 = 1;
      egIe.t.uli.cgi.sNwk.mncDigit1 = 1;
      egIe.t.uli.cgi.sNwk.mncDigit2 = 1;
      egIe.t.uli.cgi.sNwk.mncDigit3 = 1;
      egIe.t.uli.cgi.lac = EGAC_DFLT_LAC_VAL;
      egIe.t.uli.cgi.ci = EGAC_DFLT_CI_VAL;
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"UsrLocInfoSAIPres", &usrLocInfoSaiPresent);
   egIe.t.uli.isSAIPres = usrLocInfoSaiPresent;
   if( egIe.t.uli.isSAIPres )
   {
      egIe.t.uli.sai.sNwk.mccDigit1 = 1;
      egIe.t.uli.sai.sNwk.mccDigit2 = 1;
      egIe.t.uli.sai.sNwk.mccDigit3 = 1;
      egIe.t.uli.sai.sNwk.mncDigit1 = 1;
      egIe.t.uli.sai.sNwk.mncDigit2 = 1;
      egIe.t.uli.sai.sNwk.mncDigit3 = 1;
      egIe.t.uli.sai.lac = EGAC_DFLT_LAC_VAL;
      egIe.t.uli.sai.sac = EGAC_DFLT_SAI_VAL;
   }
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"UsrLocInfoRAIPres", &usrLocInfoRaiPresent);
   egIe.t.uli.isRAIPres = usrLocInfoRaiPresent;
   if( egIe.t.uli.isRAIPres )
   {
      egIe.t.uli.rai.sNwk.mccDigit1 = 1;
      egIe.t.uli.rai.sNwk.mccDigit2 = 1;
      egIe.t.uli.rai.sNwk.mccDigit3 = 1;
      egIe.t.uli.rai.sNwk.mncDigit1 = 1;
      egIe.t.uli.rai.sNwk.mncDigit2 = 1;
      egIe.t.uli.rai.sNwk.mncDigit3 = 1;
      egIe.t.uli.rai.lac = EGAC_DFLT_LAC_VAL;
      egIe.t.uli.rai.rac = EGAC_DFLT_RAC_VAL;
   }
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"UsrLocInfoTAIPres", &usrLocInfoTaiPresent);
   egIe.t.uli.isTAIPres = usrLocInfoTaiPresent;
   if( egIe.t.uli.isTAIPres )
   {
      egIe.t.uli.tai.sNwk.mccDigit1 = 1;
      egIe.t.uli.tai.sNwk.mccDigit2 = 1;
      egIe.t.uli.tai.sNwk.mccDigit3 = 1;
      egIe.t.uli.tai.sNwk.mncDigit1 = 1;
      egIe.t.uli.tai.sNwk.mncDigit2 = 1;
      egIe.t.uli.tai.sNwk.mncDigit3 = 1;
      egIe.t.uli.tai.tac = EGAC_DFLT_TAC_VAL;
   }
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"UsrLocInfoECGIPres", &usrLocInfoEcgiPresent);
   egIe.t.uli.isECGIPres = usrLocInfoEcgiPresent;
   if( egIe.t.uli.isECGIPres )
   {
      egIe.t.uli.ecgi.sNwk.mccDigit1 = 1;
      egIe.t.uli.ecgi.sNwk.mccDigit2 = 1;
      egIe.t.uli.ecgi.sNwk.mccDigit3 = 1;
      egIe.t.uli.ecgi.sNwk.mncDigit1 = 1;
      egIe.t.uli.ecgi.sNwk.mncDigit2 = 1;
      egIe.t.uli.ecgi.sNwk.mncDigit3 = 1;
      egIe.t.uli.ecgi.ecId = EGAC_DFLT_ECID_VAL;
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"usrLocInfoIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"usrLocInfoPres", &usrLocInfoPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"usrLocInfoIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"usrLocInfoIeCr",  &egIe.ieCr);
*/

   if (usrLocInfoPres == TRUE)
   {
      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddUsrLocInfoIe() : Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }

   RETVOID;
}  /* makeAndAddUsrLocInfoIe  */

/*
*
*       Fun:   makeAndAddServNwIe
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddServNwIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddServNwIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     servNwPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddServNwIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_SERVING_NWK_IETYPE,ieProp.ieInst, EG_SNETWORK);

   egIe.t.sNwk.mccDigit1 = 1;
   egIe.t.sNwk.mccDigit2 = 1;
   egIe.t.sNwk.mccDigit3 = 1;
   egIe.t.sNwk.mncDigit1 = 1;
   egIe.t.sNwk.mncDigit2 = 1;
   egIe.t.sNwk.mncDigit3 = 1;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ServNwMccDigit1", &egIe.t.sNwk.mccDigit1);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ServNwMccDigit2", &egIe.t.sNwk.mccDigit2);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ServNwMccDigit3", &egIe.t.sNwk.mccDigit3);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ServNwMacDigit1", &egIe.t.sNwk.mncDigit1);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ServNwMacDigit2", &egIe.t.sNwk.mncDigit2);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ServNwMacDigit3", &egIe.t.sNwk.mncDigit3);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addServNwIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"servNwPresent",  &servNwPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addServNwIeInst",  &egIe.ieInst);


   if( servNwPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddServNwIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddServNwIe  */


/*
*
*       Fun:   makeAndAddRatTypeIe
*
*       Desc:  This function is used to Build RAT-Type Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddRatTypeIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddRatTypeIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   U8   ratTypeDat = DFLT_RAT_TYPE_VAL;
   U8   ratTypePresent = TRUE;
   EgIe egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddRatTypeIe)

   /* Fill the ie properties */
   cmMemset( (U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_RAT_TYPE_IETYPE, ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ratTypeValue", &ratTypeDat);

   egIe.t.valUnSgnd8 = ratTypeDat;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ratTypeIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"ratTypePresent",  &ratTypePresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ratTypeIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ratTypeIeCr",  &egIe.ieCr);
*/

   if( ratTypePresent == TRUE)
   {
      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddratTypeIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }

   RETVOID;
}  /* end of makeAndAddratTypeIe */


/*
*
*       Fun:   makeAndAddIndicationIe
*
*       Desc:  This function is used to Build Indication Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddIndicationIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddIndicationIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   U8     indPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddIndicationIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_INDICATION_IETYPE, ieProp.ieInst, EG_INDICATION);

   egIe.t.indication.isSGWCIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isSGWCIPres",
                                         &egIe.t.indication.isSGWCIPres);

   egIe.t.indication.isISRAIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isISRAIPres",
                                         &egIe.t.indication.isISRAIPres);

   egIe.t.indication.isISRSIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isISRSIPres",
                                         &egIe.t.indication.isISRSIPres);

   egIe.t.indication.isOIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isOIPres",
                                         &egIe.t.indication.isOIPres);

   egIe.t.indication.isDFIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isDFIPres",
                                         &egIe.t.indication.isDFIPres);

   egIe.t.indication.isHIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isHIPres",
                                         &egIe.t.indication.isHIPres);

   egIe.t.indication.isDTFPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isDTFPres",
                                         &egIe.t.indication.isDTFPres);

   egIe.t.indication.isDAFPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isDAFPres",
                                         &egIe.t.indication.isDAFPres);

   egIe.t.indication.isMSVPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isMSVPres",
                                         &egIe.t.indication.isMSVPres);

   egIe.t.indication.isSIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isSIPres",
                                         &egIe.t.indication.isSIPres);
   egIe.t.indication.isPTPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isPTPres",
                                         &egIe.t.indication.isPTPres);

   egIe.t.indication.isPPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isPPres",
                                         &egIe.t.indication.isPPres);

   egIe.t.indication.isCRSIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isCRSIPres",
                                         &egIe.t.indication.isCRSIPres);

   egIe.t.indication.isCFSIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"isCFSIPres",
                                         &egIe.t.indication.isCFSIPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"indFlgsIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"indFlgsPresent",  &indPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"indFlgsIeInst",  &egIe.ieInst);
/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"indFlgsIeCr",  &egIe.ieCr);
*/

   if (indPresent == TRUE)
   {
      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddIndicationIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }

   RETVOID;
} /* end of makeAndAddIndicationIe */

/*
*
*       Fun:   makeAndAddAccessPntNameIe
*
*       Desc:  This function is used to Build Access Point Name Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddAccessPntNameIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddAccessPntNameIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Txt   accessPntNameVal[200] = DFLT_ACCESS_POINT_NAME_VAL;
   U8     accessPntNamePresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddAccessPntNameIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_APN_IETYPE, ieProp.ieInst,
                             EG_STRING_132);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"addAccessPntNameValue", accessPntNameVal);

   egIe.t.valStr132.length = cmStrlen((U8 *)accessPntNameVal);
   cmMemcpy((U8 *)egIe.t.valStr132.val, (U8 *)accessPntNameVal, egIe.t.valStr132.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addAccessPntNameIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"AccessPntNamePresent",  &accessPntNamePresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addAccessPntNameIeInst",  &egIe.ieInst);


   if( accessPntNamePresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddAccessPntNameIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}


/*
*
*       Fun:   makeAndAddFTeidIe
*
*       Desc:  This function is used to Build FTEID Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddFTeidIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddFTeidIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   Bool isIPv4Pres = TRUE;
   U8   intfType  = EGT_INT_S11_MME_GTP_C;
   U32  teidVal   = DFLT_TEID_VAL;
   Txt  ipAddr[100] = DFLT_IP_ADDRESS;
   U8   fTeidPresent = TRUE;
   U16  length =0;
	U8  addFTeidIeInst = 0; 
   EgIe egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddFTeidIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_FTEID_IETYPE, ieProp.ieInst, EG_FTEID);

   egIe.t.fTeid.isIPv4Pres = isIPv4Pres;
   egIe.t.fTeid.intfType = (U8 )intfType;
   egIe.t.fTeid.teid = (U32 )teidVal;
   length = cmStrlen((U8 *)ipAddr);

   if (egIe.t.fTeid.isIPv4Pres)
   {
      cmMemcpy((U8 *)egIe.t.fTeid.u.ip4Addr, (U8 *) ipAddr, length);
   }
   else
   {
      cmMemcpy((U8 *)egIe.t.fTeid.u.ipv6Address, (U8 *) ipAddr, length);
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addFTeidIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"FTeidPresent",  &fTeidPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addFTeidIeInst",  &addFTeidIeInst);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"FTeidIntfType",  &intfType);
   egIe.t.fTeid.intfType = intfType;

   if( fTeidPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddFTeidIe: Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

   RETVOID;
} /* end of makeAndAddFTeidIe */


/*
*
*       Fun:   makeAndAddEbiIe
*
*       Desc:  This function is used to Build EBI Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddEbiIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddEbiIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     ebiVal = DFLT_EBI;
   U8     ebiPresent = TRUE;
   U8     ebiDataTypeChange = FALSE;
   U8     ebiIeRepeat = FALSE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddEbiIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"ebiDataTypeChange",  &ebiDataTypeChange);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"ebiIeRepeat",  &ebiIeRepeat);

/*
   if(!ebiDataTypeChange)
   {
*/
    egAcEgtBuildEgIeHeader(&egIe,EG_EBI_IETYPE,ieProp.ieInst,
                             EG_UNSIGNED_8);
/*
   }
   else
   {

    egAcEgtBuildEgIeHeader(&egIe,EG_EBI_IETYPE,ieProp.ieInst,
                             EG_UNSIGNED_16);
   }
*/

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ebiValue", &ebiVal);
   egIe.t.valUnSgnd8 = ebiVal;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ebiIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"ebiPresent",  &ebiPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ebiIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ebiIeCr",  &egIe.ieCr);
*/

   if( ebiPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddEbiIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }

       if(ebiIeRepeat == TRUE)
       {
           if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
           {
                CMXTA_DBG_ERR((_cmxtap, "makeAndAddEbiIe() : Unable to Append IE to eGTP message\n"));
                RETVOID;
           }
      }
  }
}  /* makeAndAddEbiIe  */

/*
*
*       Fun:   makeAndAddBQosIe
*
*       Desc:  This function is used to Build BQos Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddBQosIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddBQosIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   flowQosUpMbrDat[100] = DFLT_QOS_UMBR_VAL;
   Data   flowQosDnMbrDat[100] = DFLT_QOS_DMBR_VAL;
   Data   flowQosUpGbrDat[100] = DFLT_QOSUGBR_VAL;
   Data   flowQosDnGbrDat[100] = DFLT_QOSDGBR_VAL;
   U8     bQosPres = TRUE;
   U16     length  = 1;
   EgIe   egIe;

   TRC2(makeAndAddBQosIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_BEARER_QOS_IETYPE,ieProp.ieInst, EG_BQOS_IEDATA);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"flowQosUpMbrDat", flowQosUpMbrDat);

   length = cmStrlen((U8 *)flowQosUpMbrDat);
   cmMemcpy((U8 *)egIe.t.bQos.upMBR.val, (U8 *) flowQosUpMbrDat, length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"flowQosDnMbrDat", flowQosDnMbrDat);

   length = cmStrlen((U8 *)flowQosDnMbrDat);
   cmMemcpy((U8 *)egIe.t.bQos.dnMBR.val, (U8 *) flowQosDnMbrDat, length);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"flowQosUpGbrDat", flowQosUpGbrDat);

   length = cmStrlen((U8 *)flowQosUpGbrDat);
   cmMemcpy((U8 *)egIe.t.bQos.upGBR.val, (U8 *) flowQosUpGbrDat, length);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"flowQosDnGbrDat", flowQosDnGbrDat);

   length = cmStrlen((U8 *)flowQosDnGbrDat);
   cmMemcpy((U8 *)egIe.t.bQos.dnGBR.val, (U8 *) flowQosDnGbrDat, length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"Qci", &egIe.t.bQos.qci);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"prityLvl", &egIe.t.bQos.prityLvl);

   egIe.t.bQos.isPCIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isPCIPres", &egIe.t.bQos.isPCIPres);

   egIe.t.bQos.isPVIPres = TRUE;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"bQosIeType", &egIe.t.bQos.isPVIPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"bQosIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"bQosIePres",  &bQosPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"bQosIeInst",  &egIe.ieInst);

   if( bQosPres == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddBQosIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddBQosIe */



/*
*
*       Fun:   makeAndAddBTFTIe
*
*       Desc:  This function is used to Build ProtCfgOpt Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddBTFTIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddBTFTIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   bearerTftData[100] = DFLT_BEARERTFT_VAL;
   U8     bearerTftPres = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddBTFTIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_BEARER_TFT_IETYPE,ieProp.ieInst, EG_STRING_MAX);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"bearerTftData", bearerTftData);

   egIe.t.valStr.length = cmStrlen((U8 *)bearerTftData);
   cmMemcpy( (U8 *) egIe.t.valStr.val, (U8 *)bearerTftData, egIe.t.valStr.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"bearerTftIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                  (Txt *)"bearerTftIeLen", &egIe.t.valStr.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"bearerTftIePres",  &bearerTftPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"bearerTftIeInst",  &egIe.ieInst);

   /*
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"bQosIeCr",  &egIe.ieCr);
   */


   if( bearerTftPres == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddBTFTIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddBTFTIe */

/*
*
*       Fun:   makeAndAddChargIdIe
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_s5utl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddChargIdIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddChargIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U32   chargIdData = DFLT_ID_ID;
   U8     chargIdPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddChargIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_CHARGING_ID_IETYPE,ieProp.ieInst, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                  (Txt *)"chargIdValue", &chargIdData);

   egIe.t.valUnSgnd16 = chargIdData;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"chargIdIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"chargIdPresent",  &chargIdPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"chargIdIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"chargIdIeCr",  &egIe.ieCr);
*/

   if( chargIdPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddChargIdIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddChargIdIe  */


/*
*
*       Fun:   makeAndChargChar
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddChargCharIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddChargCharIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U16   chargCharData = DFLT_CHARG_CHAR_VAL;
   U8     chargCharPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndChargChar)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_CHARGING_CHAR_IETYPE,ieProp.ieInst, EG_UNSIGNED_16);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                  (Txt *)"chargCharValue", &chargCharData);

   egIe.t.valUnSgnd16 = chargCharData;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"chargCharIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"chargCharPresent",  &chargCharPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"chargCharIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"chargCharIeCr",  &egIe.ieCr);
*/

   if( chargCharPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndChargChar() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndChargChar  */


/*
*
*       Fun:   makeAndAddBearerFlgIe
*
*       Desc:  This function is used to Build makeAndAddBearerFlgIe
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddBearerFlgIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddBearerFlgIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8   bearerFlgVal = DFLT_BEARER_FLAG_VAL;
   U8   bearerFlgPres = TRUE;
   U8   VBearerFlgVal = DFLT_VBEARER_FLAG_VAL;
   U8   VBearerFlgPres = TRUE;

   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddBearerFlgIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_BEARER_FLAGS_IETYPE,ieProp.ieInst, EG_BEARER_FLAG);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"bearerFlgVal", &bearerFlgVal);
   egIe.t.bearFlags.isPPCPres = bearerFlgVal;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"bearerFlgVal", &VBearerFlgVal);
   egIe.t.bearFlags.isVBPres = VBearerFlgVal;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"bearerFlgIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"bearerFlgPres",  &bearerFlgPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"bearerFlgPres",  &VBearerFlgPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"bearerFlgInst",  &egIe.ieInst);

   if(bearerFlgPres == TRUE && VBearerFlgPres == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddBearerFlgIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }
}  /* makeAndAddBearerFlgIe  */



/*
*
*       Fun:  makeAndAddBrerCntxIe
*
*       Desc:  This function is used to Build BearerCntx Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddBrerCntxIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddBrerCntxIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     bearCntxtPres = TRUE;
   U8     unknownChildIe = FALSE;
   U8     noChildIEs= FALSE;
   U8     nmbChildIe = 0;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddBrerCntxIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_BEARER_CNTX_IETYPE,ieProp.ieInst, EG_GROUPED);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"brerCntxIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"brerCntxPresent",  &bearCntxtPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"brerCntxIeInst",  &egIe.ieInst);

   /*
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"bQosIeCr",  &egIe.ieCr);
   */


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"noChildIEs",  &noChildIEs);

   if( bearCntxtPres == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddBrerCntxIe() : Unable to Append IE to eGGTP message\n"));
            RETVOID;
       }
       egLvlInfo->ieInfo[egLvlInfo->level].ieTypePres = TRUE;
       egLvlInfo->ieInfo[egLvlInfo->level].ieType     = EG_BEARER_CNTX_IETYPE;
       egLvlInfo->ieInfo[egLvlInfo->level].ieInst     = ieProp.ieInst;
       egLvlInfo->level = egLvlInfo->level + 1;
       if(!noChildIEs)
		 {
			for (nmbChildIe = 0; nmbChildIe < ieProp.groupedIe->nmbGrpIe; nmbChildIe++)
			{
			  if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_EBI_IETYPE)
			  {
				 makeAndAddEbiIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_BEARER_TFT_IETYPE)
			  {
				 makeAndAddBTFTIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_FTEID_IETYPE)
			  {
				 makeAndAddFTeidIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_BEARER_QOS_IETYPE)
			  {
				 makeAndAddBQosIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_BEARER_FLAGS_IETYPE)
			  {
				 makeAndAddBearerFlgIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_F_CONTAINER_IETYPE)
			  {
				 makeAndAddFContainerIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_CHARGING_ID_IETYPE)
			  {
				 makeAndAddChargIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_CAUSE_IETYPE)
			  {
				 makeAndAddCauseIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_TRANS_ID_IETYPE)
			  {
				 makeAndAddTransIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			  else if ( ieProp.groupedIe->ieProperties[nmbChildIe].ieType == EG_PKT_FLOW_ID_IETYPE)
			  {
				 makeAndAddPktFlowIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp.groupedIe->ieProperties[nmbChildIe]);
			  }
			}
		 }

    cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_ENUM_U8, (Txt *)"unknownChildIe", &unknownChildIe);
    if (unknownChildIe)
    {
        /* Common function which frame message based on instance value */
        makeAndAddUnknownIe(tcCb,spCb,egMsg,egLvlInfo);
    }

   }

} /* makeAndAddBrerCntxIe */



/*
*
*       Fun:   makeAndAddSelModeIe
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddSelModeIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddSelModeIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8   selModeDat = DFLT_SEL_MODE_VAL;
   U8     selModePresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddSelModeIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_SEL_MODE_IETYPE,ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addSelModeValue", &selModeDat);
   egIe.t.valUnSgnd8 = selModeDat;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addSelModeIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"SelModePresent",  &selModePresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addSelModeIeInst",  &egIe.ieInst);


   if( selModePresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddSelModeIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddSelModeIe  */


/*
*
*       Fun:   makeAndAddPdnTypeIe
*
*       Desc:  This function is used to Build PDN Type Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPdnTypeIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPdnTypeIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     pdnTypeDat = DFLT_PDNTYPE_VAL;
   U8     pdnTypePresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPdnTypeIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_PDN_TYPE_IETYPE,ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addPdnTypeValue", &pdnTypeDat);
   egIe.t.valUnSgnd8 = pdnTypeDat;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addPdnTypeIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"PdnTypePresent",  &pdnTypePresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addPdnTypeIeInst",  &egIe.ieInst);

   if( pdnTypePresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddPdnTypeIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddPdnTypeIe  */

/*
*
*       Fun:   makeAndAddMaxApnRestIe
*
*       Desc:  This function is used to Build APN_RESTRICT Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddMaxApnRestIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddMaxApnRestIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     apnRestVal = DFLT_APN_RESTRICT_VAL;
   U8     maxApnRestPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddMaxApnRestIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_APN_RESTRICT_IETYPE,ieProp.ieInst,
                             EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addMaxApnRestValue", &apnRestVal);
   egIe.t.valUnSgnd8 = apnRestVal;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addMaxApnRestIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"MaxApnRestPresent",  &maxApnRestPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"addMaxApnRestIeInst",  &egIe.ieInst);

   if( maxApnRestPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddMaxApnRestIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddMaxApnRestIe */

/*
*
*       Fun:   makeAndAddUnknownIe
*
*       Desc:  This function is used to Build Unknown IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddUnknownIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo
)
#else
PUBLIC Void makeAndAddUnknownIe(tcCb,spCb,egMsg,egLvlInfo)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
#endif /* ANSI */
{
   U8     unknownPres = TRUE;
   S16    ret = ROK;
   U8     unknownDataType = DFLT_UNKNOWN_DATATYPE;
   Data   unknownVal[100] = DFLT_UNKNOWN_VAL;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddUnknownIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"unknownVal", unknownVal);
   egIe.t.valStr8.spare1 = 0;
   egIe.t.valStr8.length = cmStrlen((U8 *)unknownVal);
   cmMemcpy((U8 *) egIe.t.valStr8.val, (U8 *)unknownVal, egIe.t.valStr8.length);

   egIe.ieType = 142;
   ret = cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"unknownIeType", &egIe.ieType);
   if ( ret != CMXTA_ERR_NO_VALUE)
   {
      CMXTA_DBG_ERR((_cmxtap,"unknown Ie Type is needed from XML\n"));
      RETVOID;
   }
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"unknownPres",  &unknownPres);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"unknownDataType",  &unknownDataType);
   egIe.ieInst = 0;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"unknownIeInst",  &egIe.ieInst);
   /*
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"bQosIeCr",  &egIe.ieCr);
   */


   egAcEgtBuildEgIeHeader(&egIe, egIe.ieType,egIe.ieInst,unknownDataType);

   if( unknownPres == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,"makeAndAddUnknownIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddMaxApnRestIe */


/*
*
*       Fun:   makeAndAddPaaIe
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPaaIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPaaIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     pdnType           = DFLT_PDN_TYPE;
   U8     pdnPrefix         = DFLT_PDN_PREFIX;
   Data   pdnIpv4Addr[100]     = DFLT__PDN_IPV4_ADDR;
   Data   pdnIpv6Addr[100]     = DFLT__PDN_IPV6_ADDR;
   U8     paaPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPaaIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_PAA_IETYPE,ieProp.ieInst, EG_PAA_IEDATA);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"paaIePdnType", &pdnType);
   egIe.t.paa.pdnType = pdnType;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"paaPdnPrefix", &pdnPrefix);
   egIe.t.paa.pdnPrefix = pdnPrefix;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"paaIPV4Val", pdnIpv4Addr);
   cmMemcpy((U8 *) egIe.t.paa.u.pdnIpv4Addr, (U8 *)pdnIpv4Addr, 4);
   cmMemcpy((U8 *) egIe.t.paa.u.pdnBoth.pdnIpv4Addr, (U8 *)pdnIpv4Addr, 4);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"paaIPV6Val", pdnIpv6Addr);
   cmMemcpy((U8 *) egIe.t.paa.u.pdnIpv6Addr, (U8 *)pdnIpv6Addr, 16);
   cmMemcpy((U8 *) egIe.t.paa.u.pdnBoth.pdnIpv6Addr, (U8 *)pdnIpv6Addr, 16);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"paaIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"paaPresent",  &paaPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"paaIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"paaIeCr",  &egIe.ieCr);
*/

   if( paaPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddPaaIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddPaaIe  */


/*
*
*       Fun:   makeAndAddPxtExtnIe
*
*       Desc:  This function is used to Build MSISDN Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPvtExtnIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPvtExtnIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   pvtExtnPropVal[200] = DFLT_PVTEXT_PRY_VAL;
   U16    pvtExtnEntId = DFLT_PVTEXT_ENT_ID;
   U8     pvtExtnPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPvtExtnIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_PRIVATE_EXT_IETYPE,ieProp.ieInst, EG_PVT_EXTN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U16,
                  (Txt *)"pvtExtnEntId",  &pvtExtnEntId);
   egIe.t.pvtExt.entId = pvtExtnEntId;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"pvtExtnPropVal", pvtExtnPropVal);

   egIe.t.pvtExt.propVal.length = cmStrlen((U8 *)pvtExtnPropVal);
   cmMemcpy((U8 *) egIe.t.pvtExt.propVal.val, (U8 *)pvtExtnPropVal, egIe.t.pvtExt.propVal.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pvtExtnIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"pvtExtnPresent",  &pvtExtnPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pvtExtnIeInst",  &egIe.ieInst);

   /*
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"bQosIeCr",  &egIe.ieCr);
   */


   if( pvtExtnPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddPvtExtnIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddPvtExtnIe  */

/*
*
*       Fun:   makeAndAddPTidIe
*
*       Desc:  This function is used to Build PTI Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPTidIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPTidIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     pTidValue  = DFLT_PTID;
   U8     pTidPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPTidIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_PROCEDURE_TID_IETYPE,ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pTidVal", &pTidValue);
   egIe.t.valUnSgnd8 = pTidValue;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pTidIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"pTidPresent",  &pTidPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pTidIeInst",  &egIe.ieInst);

   /*
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"bQosIeCr",  &egIe.ieCr);
   */


   if( pTidPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddPTidIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddPTidIe  */


/*
*
*       Fun:   makeAndAddFlowQosIe
*
*       Desc:  This function is used to Build FlowQos Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddFlowQosIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddFlowQosIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     qci =  DFLT_FLOW_QOS_QCI;
   Data   upMBRVal[100] = DFLT_FLOW_QOS_UP_MBR_VAL;
   Data   dnMBRVal[100] = DFLT_FLOW_QOS_DN_MBR_VAL;
   Data   upGBRVal[100] = DFLT_FLOW_QOS_UP_GBR_VAL;
   Data   dnGBRVal[100] = DFLT_FLOW_QOS_DN_GBR_VAL;
   U8     flowQosPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddFlowQosIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_FLOW_QOS_IETYPE,ieProp.ieInst, EG_FQOS);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"flowQosQciVal", &qci);
   egIe.t.fQos.qci = qci;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"flowQosUpMBRVal",upMBRVal);

   egIe.t.fQos.upMBR.length = cmStrlen((U8 *)upMBRVal);
   cmMemcpy((U8 *) egIe.t.fQos.upMBR.val, (U8 *)upMBRVal, egIe.t.fQos.upMBR.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"flowQosDnMBRVal", dnMBRVal);

   egIe.t.fQos.dnMBR.length = cmStrlen((U8 *)dnMBRVal);
   cmMemcpy((U8 *) egIe.t.fQos.dnMBR.val, (U8 *)dnMBRVal, egIe.t.fQos.dnMBR.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"flowQosUpGBRVal", upGBRVal);

   egIe.t.fQos.upGBR.length = cmStrlen((U8 *)upGBRVal);
   cmMemcpy((U8 *) egIe.t.fQos.upGBR.val, (U8 *)upGBRVal,  egIe.t.fQos.upGBR.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"flowQosDnGBRVal", dnGBRVal);

   egIe.t.fQos.dnGBR.length = cmStrlen((U8 *)dnGBRVal);
   cmMemcpy((U8 *) egIe.t.fQos.dnGBR.val, (U8 *)dnGBRVal,  egIe.t.fQos.dnGBR.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"flowQosIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"flowQosPresent",  &flowQosPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"flowQosIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"flowQosIeCr",  &egIe.ieCr);
*/

   if( flowQosPresent == TRUE)
   {
      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddFlowQosIe() : Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }
}  /* makeAndAddFlowQosIe  */


/*
*
*       Fun:   makeAndAddTadIe
*
*       Desc:  This function is used to Build Tad Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddTadIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddTadIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   tadVal[EG_MAX_STRING_LEN] = DFLT_TAD_VAL;
   U8     tadPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddTadIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_TAD_IETYPE,ieProp.ieInst, EG_STRING_MAX);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"tadVal", tadVal);

   egIe.t.valStr16.length = cmStrlen((U8 *)tadVal);
   cmMemcpy( (U8 *)egIe.t.valStr.val, (U8 *)tadVal ,egIe.t.valStr.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"tadIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"tadPresent",  &tadPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"tadIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"tadIeCr",  &egIe.ieCr);
*/

   if(tadPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddTadIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddTadIe  */


/*
*
*       Fun:   makeAndAddDelayIe
*
*       Desc:  This function is used to Build Delay Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddDelayIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddDelayIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     delayVal =  DFLT_DELAY;
   U8     delayPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddDelayIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_DELAY_IETYPE,ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"delayVal", &delayVal);
   egIe.t.valUnSgnd8 = delayVal;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"delayIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"delayPresent",  &delayPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"delayIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"delayIeCr",  &egIe.ieCr);
*/

   if( delayPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddDelayDelayIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
  }
}  /* makeAndAddDelayIe  */


/*
*
*       Fun:   makeAndAddApnRestIe
*
*       Desc:  This function is used to Build  Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddApnRestIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddApnRestIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     apnRestVal = DFLT_APN_RESTRICTION_VAL;
   U8     apnRestPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddApnRestIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_APN_RESTRICT_IETYPE,ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"apnRestVal", &apnRestVal);
   egIe.t.valUnSgnd8 = apnRestVal;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"apnRestIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"apnRestPresent",  &apnRestPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"apnRestIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"apnRestIeCr",  &egIe.ieCr);
*/

   if( apnRestPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddApnRestIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddApnRestIe */


/*
*
*       Fun:   makeAndAddAmbrIe
*
*       Desc:  This function is used to Build Ambr Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddAmbrIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddAmbrIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     ambrPresent = TRUE;
   EgIe   egIe;
   U32  uplAPNAMBR = DFLT_UPLINK_APNAMBR;  /**<  APN-AMBR for uplink */
   U32  dnlAPNAMBR = DFLT_DWLINK_APNAMBR;  /**<  APN-AMBR for downlink */

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddAmbrIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_AMBR_IETYPE,ieProp.ieInst, EG_AMBR);

   /**<  APN-AMBR for uplink */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                  (Txt *)"APN_AMBR_Uplink", &uplAPNAMBR);
   egIe.t.ambr.uplAPNAMBR = uplAPNAMBR;

   /**<  APN-AMBR for downlink */
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                  (Txt *)"APN-AMBR_Downlink", &dnlAPNAMBR);
   egIe.t.ambr.dnlAPNAMBR = dnlAPNAMBR;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ambrIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"ambrPresent",  &ambrPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ambrIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"ambrIeCr",  &egIe.ieCr);
*/
	ambrPresent = TRUE;
   if( ambrPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddAmbrIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddAmbrIe */

/*
*
*       Fun:   makeAndAddPCOIe
*
*       Desc:  This function is used to Build PCO Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddPCOIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPCOIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   pcoVal[EG_MAX_STRING_LEN] = DFLT_PCO_VAL;
   U8     pcoPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddPCOIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_PCO_IETYPE,ieProp.ieInst, EG_STRING_MAX);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"pcoVal", pcoVal);

   egIe.t.valStr.length = cmStrlen((U8 *)pcoVal);
   cmMemcpy((U8 *) egIe.t.valStr.val, (U8 *)pcoVal,egIe.t.valStr.length);
   egIe.t.valStr.spare1 = 0;
#ifdef ALIGN_64BIT
   egIe.t.valStr.spare2 = 0;
#endif

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pcoIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"pcoPresent",  &pcoPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pcoIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"pcoIeCr",  &egIe.ieCr);
*/

   if( pcoPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddPCOIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddPCOIe */

/*
*
*       Fun:   makeAndAddTrcIe
*
*       Desc:  This function is used to Build TRC Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddTrcIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddTrcIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     trcPresent = TRUE;
   EgIe   egIe;
   Txt    ipAddr[100] = DFLT_IP_ADDRESS;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddTrcIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_TRACE_INFO_IETYPE,ieProp.ieInst, EG_TRC_INFO);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"trcIeType", &egIe.ieType);

   egIe.t.trcInfo.sNwk.mccDigit1 = 1;
   egIe.t.trcInfo.sNwk.mccDigit2 = 1;
   egIe.t.trcInfo.sNwk.mccDigit3 = 1;
   egIe.t.trcInfo.sNwk.mncDigit1 = 1;
   egIe.t.trcInfo.sNwk.mncDigit2 = 1;
   egIe.t.trcInfo.sNwk.mncDigit3 = 1;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt *)"ServNwMccDigit1", &egIe.t.trcInfo.sNwk.mccDigit1);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt *)"ServNwMccDigit2", &egIe.t.trcInfo.sNwk.mccDigit2);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt *)"ServNwMccDigit3", &egIe.t.trcInfo.sNwk.mccDigit3);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt *)"ServNwMacDigit1", &egIe.t.trcInfo.sNwk.mncDigit1);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt *)"ServNwMacDigit2", &egIe.t.trcInfo.sNwk.mncDigit2);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt *)"ServNwMacDigit3", &egIe.t.trcInfo.sNwk.mncDigit3);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                 (Txt *)"trcId", &egIe.t.trcInfo.trcId);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                 (Txt *)"lstNETypes", &egIe.t.trcInfo.lstNETypes);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                 (Txt *)"sesnTrcDep", &egIe.t.trcInfo.sesnTrcDep);
/* eg009.201 - Added for S2B and S2A */
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
   cmMemcpy( (U8* )egIe.t.trcInfo.lstOfIntfs, (U8* )DFLT_INTF_LIST,DFLT_INTF_LEN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                 (Txt *)"lstOfIntfs", &egIe.t.trcInfo.lstOfIntfs);
#else
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                 (Txt *)"lstOfIntfs", &egIe.t.trcInfo.lstOfIntfs);
#endif

   egIe.t.trcInfo.trcColEntAddr.type = DFLT_IPADDR_TYPE_VAL;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                (Txt *)"type", &egIe.t.trcInfo.trcColEntAddr.type);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                (Txt *)"ipAddr", &ipAddr);

   switch (egIe.t.trcInfo.trcColEntAddr.type)
   {
      case CM_NETADDR_IPV4:
      {
         cmInetAddr ( (S8 *)ipAddr, &(egIe.t.trcInfo.trcColEntAddr.u.ipv4));
         break;
      } /* end of case */

#ifdef IPV6_SUPPORTED
      case CM_NETADDR_IPV6:
      {
         cmInetPton6(&egIe.t.trcInfo.trcColEntAddr.u.ipv6, (S8*)ipAddr);
         break;
      } /* end of case */
#endif /* end of IPV6_SUPPORTED */

      default:
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddIpAddrIe: Invalid IP Address Type\n"));
         RETVOID;
      } /* end of case */
   } /* end of switch */

/* eg009.201 - Added for S2B and S2A */
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
   cmMemcpy( (U8* )egIe.t.trcInfo.trigEvnts, (U8* )DFLT_TRIG_EVT_LIST,DFLT_TRIG_EVT_LEN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                 (Txt *)"lstOfIntfs", &egIe.t.trcInfo.lstOfIntfs);
#endif
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                (Txt *)"trigEvnts", egIe.t.trcInfo.trigEvnts);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"trcIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"trcPresent",  &trcPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"trcIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"trcIeCr",  &egIe.ieCr);
*/

   if( trcPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddTrcIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddTrcIe */


/*
*
*       Fun:   makeAndAddCsidIe
*
*       Desc:  This function is used to Build CSID Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddCsidIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddCsidIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   csidVal[EG_MAX_STRING_LEN] = DFLT_CSID_VAL;
   Data   nodeId[EG_MAX_STRING_LEN] = DFLT_NODE_ID;
   U8     csidPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddCsidIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_CSID_IETYPE, ieProp.ieInst, EG_PDN_CONN_SET_ID);

   egIe.t.csid.nodeIdType = 0x00;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"nodeIdType", &egIe.t.csid.nodeIdType);

   egIe.t.csid.noOfCSIDs =  0x01;
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"nodeIdType", &egIe.t.csid.noOfCSIDs);

   egIe.t.csid.nodeId.length = 0x04;
   cmMemcpy((U8 *) egIe.t.csid.nodeId.val,(U8 *)nodeId,egIe.t.csid.nodeId.length);
#if 0 
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"nodeId", nodeId);
   egIe.t.csid.nodeId.length = cmStrlen((U8 *)nodeId);
#endif
   cmMemcpy((U8 *) egIe.t.csid.nodeId.val,(U8 *)nodeId,egIe.t.csid.nodeId.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"csidVal", csidVal);
   /*egIe.t.csid.csid.length = cmStrlen((U8 *)csidVal);*/
   egIe.t.csid.csid.length = 0x02 ;
   cmMemcpy((U8 *) egIe.t.csid.csid.val, (U8 *)csidVal,egIe.t.csid.csid.length);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"csidIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"csidPresent",  &csidPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"csidIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"csidIeCr",  &egIe.ieCr);
*/
   if(csidPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddCsidIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddCsidIe */


/*
*
*       Fun:   makeAndAddFCauseIe
*
*       Desc:  This function is used to Build F-Cause Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddFCauseIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddFCauseIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   U8     fCausePresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddFCauseIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_F_CAUSE_IETYPE, ieProp.ieInst, EG_F_CAUSE);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"fCausePresent",  &fCausePresent);

   if (fCausePresent == TRUE)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"fCauseIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"fCauseIeInst",  &egIe.ieInst);

      egIe.t.fCause.causeType = DFLT_FCAUSE_TYPE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"fCauseType", &egIe.t.fCause.causeType);

      egIe.t.fCause.cause = DFLT_CAUSE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                     (Txt *)"fCauseType", &egIe.t.fCause.cause);

      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddFCauseIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }

   RETVOID;
} /* end of makeAndAddFCauseIe */


/*
*
*       Fun:   makeAndAddFContainerIe
*
*       Desc:  This function is used to Build F-Container Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddFContainerIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddFContainerIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   Data   data[1024] = {0};
   U8     fContainerPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddFContainerIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_F_CONTAINER_IETYPE, ieProp.ieInst, EG_F_CONT);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"fContainerPresent",  &fContainerPresent);

   if (fContainerPresent == TRUE)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"fContainerIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"fContainerIeInst",  &egIe.ieInst);

      /*
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                        (Txt *)"bQosIeCr",  &egIe.ieCr);
      */


      egIe.t.fContainer.containerType = DFLT_FCONTAINER_TYPE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"fContainerType", &egIe.t.fContainer.containerType);

      egIe.t.fContainer.fContainer.length = DFLT_FCONTAINER_LENGTH;
      cmMemcpy( (U8* )egIe.t.fContainer.fContainer.val, (U8* )DFLT_FCONTAINER, DFLT_FCONTAINER_LENGTH);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"fContainer", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.fContainer.fContainer.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.fContainer.fContainer.val, (U8 *)data, egIe.t.fContainer.fContainer.length);
      } /* end of if */

      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddFContainerIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }

   RETVOID;
} /* end of makeAndAddFContainerIe */


/*
*
*       Fun:   makeAndAddTargetIdIe
*
*       Desc:  This function is used to Build Target Id Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddTargetIdIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddTargetIdIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   Data   data[1024] = {0};
   U8     targetIdPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddTargetIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_TARGET_ID_IETYPE, ieProp.ieInst, EG_TRGTID);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"targetIdPresent",  &targetIdPresent);

   if (targetIdPresent == TRUE)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"targetIdIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"targetIdIeInst",  &egIe.ieInst);

      /*
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                        (Txt *)"bQosIeCr",  &egIe.ieCr);
      */


      egIe.t.targetId.targetType = DFLT_TARGET_ID_TYPE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"targetIdType", &egIe.t.targetId.targetType);

      egIe.t.targetId.targetId.length = DFLT_TARGET_ID_LENGTH;
      cmMemcpy( (U8* )egIe.t.targetId.targetId.val, (U8* )DFLT_TARGET_ID, DFLT_TARGET_ID_LENGTH);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"targetId", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.targetId.targetId.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.targetId.targetId.val, (U8 *)data, egIe.t.targetId.targetId.length);
      } /* end of if */

      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddTargetIdIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }

   RETVOID;
} /* end of makeAndAddTargetIdIe */


/*
*
*       Fun:   makeAndAddSelPlmnIdIe
*
*       Desc:  This function is used to Build Selected PLMN Id Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddSelPlmnIdIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddSelPlmnIdIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   Data   data[1024] = {0};
   U8     selPlmnIdPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddSelPlmnIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_SEL_PLMN_ID_IETYPE, ieProp.ieInst, EG_STRING_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"selPlmnIdPresent",  &selPlmnIdPresent);

   if (selPlmnIdPresent == TRUE)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"selPlmnIdIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"selPlmnIdIeInst",  &egIe.ieInst);

      /*
         cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                        (Txt *)"bQosIeCr",  &egIe.ieCr);
      */


      egIe.t.valStr8.length = DFLT_SEL_PLMN_ID_LENGTH;
      cmMemcpy( (U8* )egIe.t.valStr8.val, (U8* )DFLT_SEL_PLMN_ID, DFLT_SEL_PLMN_ID_LENGTH);

      if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"selPlmnId", data) != CMXTA_ERR_NO_VALUE)
      {
         egIe.t.valStr8.length = cmStrlen( (U8 *)data);
         cmMemcpy( (U8 *)egIe.t.valStr8.val, (U8 *)data, egIe.t.valStr8.length);
      } /* end of if */

      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap, "makeAndAddSelPlmnIdIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }

   RETVOID;
} /* end of makeAndAddSelPlmnIdIe */

/*
*
*       Fun:   makeAndAddCauseIe
*
*       Desc:  This function is used to Build Cause Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddCauseIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddCauseIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   U8     causeVal = DFLT_CAUSE_VAL;
   U8     causePresent = 1;
   Bool   CauseSource;
   U8     Type;                            /**<  Ie Type of the offending IE */
   U16    Length;                          /**<  offending IE length */
   U8     ieInst;                            /**<  Inst value of the offending IE */
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddCauseIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_CAUSE_IETYPE, ieProp.ieInst, EG_CAUSE);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"causeVal", &causeVal);
   egIe.t.cause.causeVal = causeVal;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_BOOL,
                  (Txt *)"CauseSource", &CauseSource);
   egIe.t.cause.ieCS = CauseSource;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"IeType", &Type);
   egIe.t.cause.ieType = Type;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
              (Txt *)"IeLength", &Length);

   egIe.t.cause.ieLength = Length;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
              (Txt *)"IeInst", &ieInst);
   egIe.t.cause.ieInst = ieInst;

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"causeIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"causePresent",  &causePresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"causeIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"causeIeCr",  &egIe.ieCr);
*/

   if (causePresent)
   {
      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap,
                       "makeAndAddCauseIe() : Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   }

   RETVOID;
} /* end of makeAndAddCauseIe */
/*
*
*       Fun:   makeAndAddRecoveryIe
*
*       Desc:  This function is used to Build RECOVERY Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddRecoveryIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddRecoveryIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     recvVal = DFLT_RECOVERY_VAL;
   U8     recvPresent = TRUE;
   EgIe   egIe;
   U8     recoveryDataTypeChange = FALSE;
   U8     InvalidLenRecoveryIe = FALSE;


   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddRecoveryIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_RECOVERY_IETYPE,ieProp.ieInst,EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                 (Txt *)"recoveryDataTypeChange",  &recoveryDataTypeChange);


   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                 (Txt *)"InvalidLenRecoveryIe",  &InvalidLenRecoveryIe);

   if(InvalidLenRecoveryIe)
   {
        cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                       (Txt *)"recvVal", &recvVal);
        egIe.t.valUnSgnd8 = recvVal;
   }
   else
   {
        cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                       (Txt *)"recvVal", &recvVal);
        egIe.t.valUnSgnd8 = recvVal;
   }

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"recvIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"recvPresent",  &recvPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"recvIeInst",  &egIe.ieInst);

/*
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"recvIeCr",  &egIe.ieCr);
*/

   if( recvPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,
        "makeAndAddRecoveryIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddRecoveryIe */

/*
*
*       Fun:   makeAndAddCngRptActIe
*
*       Desc:  This function is used to Build eGTP Hop Counter IE
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddCngRptActIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddCngRptActIe(tcCb, spCb, egMsg, egLvlInfo, ieProp)
CmXtaTCCb       *tcCb;
CmXtaSpCb       *spCb;
EgMsg           *egMsg;
EgIeLevelInfo   *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   U8     cngRptActPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddCngRptActIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_CNG_RPT_ACT_IETYPE, ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"cngRptActPresent",  &cngRptActPresent);

   if (cngRptActPresent)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"cngRptActIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"cngRptActIeInst",  &egIe.ieInst);

      egIe.t.valUnSgnd8 = DFLT_CNG_RPT_ACT;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"cngRptAct", &egIe.t.valUnSgnd8);

      if (EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
         CMXTA_DBG_ERR((_cmxtap,
                 "makeAndAddCngRptActIe: Unable to Append IE to eGTP message\n"));
         RETVOID;
      }
   } /* end of if present */

   RETVOID;
} /* end of makeAndAddCngRptActIe */



#ifdef ANSI
PUBLIC Void  makeAndAddApnIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddApnIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isApnPres;
   Data   ApnVal[EG_MAX_STRING_LEN] = DFLT_APN_VAL;

   TRC2(makeAndAddApnIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_APN_IETYPE, ieProp.ieInst, EG_STRING_132);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isApnPres", &isApnPres);

   if(isApnPres)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,(Txt *)"ApnVal", ApnVal);

      egIe.t.valStr132.length = cmStrlen((U8 *)ApnVal);
      cmMemcpy( (U8 *)egIe.t.valStr132.val, (U8 *)ApnVal ,egIe.t.valStr132.length);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"addApnIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"addApnIeInst",  &egIe.ieInst);

      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
		     CMXTA_DBG_ERR((_cmxtap,"makeAndAddApnIe() : Unable to Append IE to eGTP message\n"));
           RETVOID;
      }
   }
}

#ifdef ANSI
PUBLIC Void  makeAndAddSrcRncPdcpCtxIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddSrcRncPdcpCtxIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   Data   SrcRncPdcpCtxVal[EG_MAX_STRING_LEN] = DFLT_SRCRNCPDCPCTX_VAL;
   U8     isSrcRncPdcpCtxPres;

   TRC2(makeAndAddSrcRncPdcpCtxIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_SRC_RNC_PDCP_CTX_IETYPE, ieProp.ieInst, EG_STRING_MAX);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,(Txt *)"isSrcRncPdcpCtxPres", &isSrcRncPdcpCtxPres);

   if(isSrcRncPdcpCtxPres)
   {
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"SrcRncPdcpCtxVal", SrcRncPdcpCtxVal);

       egIe.t.valStr.length = cmStrlen((U8 *)SrcRncPdcpCtxVal);
       cmMemcpy( (U8 *)egIe.t.valStr.val, (U8 *)SrcRncPdcpCtxVal,egIe.t.valStr.length);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addSrcRncPdcpCtxIeType", &egIe.ieType);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addSrcRncPdcpCtxIeInst",  &egIe.ieInst);
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,"makeAndAddSrcRncPdcpCtxIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
    }
}

#ifdef ANSI
PUBLIC Void  makeAndAddFqdnIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddFqdnIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isFqdnPres;
   Data   FqdnVal[EG_MAX_STRING_LEN] = DFLT_FQDN_VAL;

   TRC2(makeAndAddFqdnIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_FQDN_IETYPE, ieProp.ieInst,EG_STRING_MAX);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                     (Txt *)"isFqdnPres", &isFqdnPres);

   if(isFqdnPres)
   {
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addFqdnIeType", &egIe.ieType);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addFqdnIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                    (Txt *)"FqdnVal", FqdnVal);

       egIe.t.valStr.length = cmStrlen((U8 *)FqdnVal);
       cmMemcpy( (U8 *)egIe.t.valStr.val, (U8 *)FqdnVal ,egIe.t.valStr.length);

       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,"makeAndAddFqdnIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
    }
}


#ifdef ANSI
PUBLIC Void  makeAndAddUeNtwrkCapbIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddUeNtwrkCapbIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isUeNtwrkCapbPres;
   Data   UeNtwrkCapbVal[EG_MAX_STRING_LEN] = DFLT_UENTWRKCAPB_VAL;


   TRC2(makeAndAddUeNtwrkCapbIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_UE_NTWRK_CAPB_IETYPE, ieProp.ieInst,EG_STRING_16);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isUeNtwrkCapbPres", &isUeNtwrkCapbPres);

    if(isUeNtwrkCapbPres)
    {
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addUeNtwrkCapbIeType", &egIe.ieType);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addUeNtwrkCapbIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                    (Txt *)"tadVal", UeNtwrkCapbVal);

       egIe.t.valStr16.length = cmStrlen((U8 *)UeNtwrkCapbVal);
       cmMemcpy( (U8 *)egIe.t.valStr16.val, (U8 *)UeNtwrkCapbVal ,egIe.t.valStr16.length);

       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,"makeAndAddUeNtwrkCapbIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
    }
}

#ifdef EG_REL_930
/*
*
*       Fun:   makeAndAddRfspIdIe
*
*       Desc:  This function is used to Build eGTP RFSP(RAT/Frequency Selection Priority idx)
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/
#ifdef ANSI
PUBLIC Void  makeAndAddRfspIdIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddRfspIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isRfspIdPres;
   U16    RfspIdVal = DFLT_RFSPID;


   TRC2(makeAndAddRfspIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_RFSP_ID_IETYPE,ieProp.ieInst,EG_UNSIGNED_16);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isRfspIdPres", &isRfspIdPres);

    if(isRfspIdPres)
    {

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addRfspIdIeType", &egIe.ieType);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addRfspIdIeInst",  &egIe.ieInst);


       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                      (Txt *)"RfspIdVal", &RfspIdVal);
       egIe.t.valUnSgnd16 = RfspIdVal;

       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,"makeAndAddRfspIdIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
    }
}
/*
*
*       Fun:   makeAndAddCsgIdIe
*
*       Desc:  This function is used to Build eGTP CSG Id ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/
#ifdef ANSI
PUBLIC Void  makeAndAddCsgIdIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddCsgIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isCsgIdPres;
   U32    CsgIdVal = DFLT_CSGID;

   TRC2(makeAndAddCsgIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_CSG_ID_IETYPE, ieProp.ieInst, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isCsgIdPres", &isCsgIdPres);

	if(isCsgIdPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addCsgIdIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addCsgIdIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                      (Txt *)"CsgIdValue", &CsgIdVal);
       egIe.t.valUnSgnd32 = CsgIdVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddCsgIdIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}
/*
*
*       Fun:   makeAndAddMbmsDistAckIe
*
*       Desc:  This function is used to Build eGTP MBMS Distribution Acknowledge
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/
#ifdef ANSI
PUBLIC Void  makeAndAddMbmsDistAckIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddMbmsDistAckIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isMbmsDistAckPres = TRUE;
   U8    MbmsDistAckVal = DFLT_MBMSDISTACK;

   TRC2(makeAndAddMbmsDistAckIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_MBMS_DIST_ACK_IETYPE, ieProp.ieInst,EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isMbmsDistAckPres", &isMbmsDistAckPres);

	if(isMbmsDistAckPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMbmsDistAckIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMbmsDistAckIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"MbmsDistAckValue", &MbmsDistAckVal);
       egIe.t.valUnSgnd8 = MbmsDistAckVal;


	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddMbmsDistAckIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}
/*
*
*       Fun:   makeAndAddCmiIe
*
*       Desc:  This function is used to Build eGTP CMI(CSG Membership Indication)
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/
#ifdef ANSI
PUBLIC Void  makeAndAddCmiIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddCmiIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isCmiPres;
   U8     CmiVal = DFLT_CMI;

   TRC2(makeAndAddCmiIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_CMI_IETYPE, ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isCmiPres", &isCmiPres);

	if(isCmiPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addCmiIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addCmiIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"CmiValue", &CmiVal);
       egIe.t.valUnSgnd8 = CmiVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddCmiIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}
/*
*
*       Fun:   makeAndAddMbmsFlowIdIe
*
*       Desc:  This function is used to Build eGTP MBMS Flow Identifier
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/
#ifdef ANSI
PUBLIC Void  makeAndAddMbmsFlowIdIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddMbmsFlowIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isMbmsFlowIdPres;
   U16    MbmsFlowIdVal = DFLT_MBMSFLOWID;

   TRC2(makeAndAddMbmsFlowIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_MBMS_FLOW_ID_IETYPE, ieProp.ieInst,EG_UNSIGNED_16);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isMbmsFlowIdPres", &isMbmsFlowIdPres);

	if(isMbmsFlowIdPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMbmsFlowIdIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMbmsFlowIdIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
                      (Txt *)"MbmsFlowIdValue", &MbmsFlowIdVal);
       egIe.t.valUnSgnd16 = MbmsFlowIdVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddMbmsFlowIdIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}
/*
*
*       Fun:   makeAndAddMbmsServAreaIe
*
*       Desc:  This function is used to Build eGTP MBMS Serving Area
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddMbmsServAreaIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddMbmsServAreaIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isMbmsServAreaPres = TRUE;
   U32     MbmsServAreaVal = DFLT_MBMSSERVAREA;

   TRC2(makeAndAddMbmsServAreaIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_MBMS_SERV_AREA_IETYPE, ieProp.ieInst,EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isMbmsServAreaPres", &isMbmsServAreaPres);

	if(isMbmsServAreaPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMbmsServAreaIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMbmsServAreaIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                      (Txt *)"MbmsServAreaValue", &MbmsServAreaVal);
       egIe.t.valUnSgnd32 = MbmsServAreaVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddMbmsServAreaIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}
/*
*
*       Fun:   makeAndAddMbmsSessIdIe
*
*       Desc:  This function is used to Build eGTP MBMS Session Identifier
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddMbmsSessIdIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddMbmsSessIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isMbmsSessIdPres;
   U8     MbmsSessIdVal = DFLT_MBMSSESSID;

   TRC2(makeAndAddMbmsSessIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_MBMS_SESS_ID_IETYPE, ieProp.ieInst,EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isMbmsSessIdPres", &isMbmsSessIdPres);

	if(isMbmsSessIdPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMbmsSessIdIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMbmsSessIdIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"MbmsSessIdValue", &MbmsSessIdVal);
       egIe.t.valUnSgnd8 = MbmsSessIdVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddMbmsSessIdIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}
/*
*
*       Fun:   makeAndAddMbmsIpMultDistIe
*
*       Desc:  This function is used to Build eGTP MBMS IP Multicast Distribution
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/
#ifdef ANSI
PUBLIC Void  makeAndAddMbmsIpMultDistIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddMbmsIpMultDistIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isMmsIpMultDistPres = TRUE;

   Txt    ipAddr[100] = DFLT_IP_ADDRESS;

   TRC2(makeAndAddMbmsIpMultDistIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_MBMS_IP_MULT_DIST_IETYPE, ieProp.ieInst,EG_MBMS_IPMCAST_DIST);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isMmsIpMultDistPres", &isMmsIpMultDistPres);

	if(isMmsIpMultDistPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addMmsIpMultDistIeType", &egIe.ieType);

		cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
			 (Txt *)"addMmsIpMultDistIeInst",  &egIe.ieInst);

		egIe.t.mbmsIPMCastDist.cteidDat = 0xFF;
		egIe.t.mbmsIPMCastDist.cteidDat = 1;

		egIe.t.mbmsIPMCastDist.ipMCastDistAddr.type = CM_NETADDR_IPV4;

		switch (egIe.t.mbmsIPMCastDist.ipMCastDistAddr.type)
		{
		  case CM_NETADDR_IPV4:
			 {
				cmInetAddr ( (S8 *)ipAddr, &(egIe.t.mbmsIPMCastDist.ipMCastDistAddr.u.ipv4));
				break;
			 } /* end of case */

#ifdef IPV6_SUPPORTED
		  case CM_NETADDR_IPV6:
			 {
				cmInetPton6(&egIe.t.mbmsIPMCastDist.ipMCastDistAddr.u.ipv6, (S8*)ipAddr);
				break;
			 } /* end of case */
#endif /* end of IPV6_SUPPORTED */

		  default:
			 {
				CMXTA_DBG_ERR((_cmxtap,"makeAndAddMbmsIpMultDistIe: Invalid IP Address Type\n"));
				RETVOID;
			 } /* end of case */
		} /* end of switch */

		egIe.t.mbmsIPMCastDist.ipMCastSrcAddr.type = CM_NETADDR_IPV4;

		switch (egIe.t.mbmsIPMCastDist.ipMCastSrcAddr.type)
		{
		  case CM_NETADDR_IPV4:
			 {
				cmInetAddr ( (S8 *)ipAddr, &(egIe.t.mbmsIPMCastDist.ipMCastSrcAddr.u.ipv4));
				break;
			 } /* end of case */

#ifdef IPV6_SUPPORTED
		  case CM_NETADDR_IPV6:
			 {
				cmInetPton6(&egIe.t.mbmsIPMCastDist.ipMCastSrcAddr.u.ipv6, (S8*)ipAddr);
				break;
			 } /* end of case */
#endif /* end of IPV6_SUPPORTED */

		  default:
			 {
				CMXTA_DBG_ERR((_cmxtap,"makeAndAddMbmsIpMultDistIe: Invalid IP Address Type\n"));
				RETVOID;
			 } /* end of case */
		} /* end of switch */


	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddMbmsIpMultDistIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}

#endif /* EG_REL_930 */

#ifdef ANSI
PUBLIC Void  makeAndAddChnlNeededIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddChnlNeededIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isChnlNeededPres;
   U32    ChnlNeededVal = DFLT_CHNLNEEDED;


   TRC2(makeAndAddChnlNeededIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_CHNL_NEEDED_IETYPE, ieProp.ieInst,EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isChnlNeededPres", &isChnlNeededPres);

	if(isChnlNeededPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addChnlNeededIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addChnlNeededIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                      (Txt *)"ChnlNeededVal", &ChnlNeededVal);
       egIe.t.valUnSgnd32 = ChnlNeededVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddChnlNeededIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}


#ifdef ANSI
PUBLIC Void  makeAndAddEmlppPriorIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddEmlppPriorIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isEmlppPriorPres;
   U32    EmlppPriorVal = DFLT_EMLPPPRIOR;

   TRC2(makeAndAddEmlppPriorIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_EMLPP_PRIOR_IETYPE, ieProp.ieInst,EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isEmlppPriorPres", &isEmlppPriorPres);

    if(isEmlppPriorPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addEmlppPriorIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addEmlppPriorIeInst",  &egIe.ieInst);

        cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                       (Txt *)"EmlppPriorValue", &EmlppPriorVal);
        egIe.t.valUnSgnd32 = EmlppPriorVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddEmlppPriorIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}


#ifdef ANSI
PUBLIC Void  makeAndAddTransIdIe
(
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddTransIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb        *tcCb;
CmXtaSpCb        *spCb;
EgMsg            *egMsg;
EgIeLevelInfo    *egLvlInfo;
LegIeProperties  ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isTransIdPres;
   U32    TransIdVal = DFLT_TRANSID;

   TRC2(makeAndAddTransIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_TRANS_ID_IETYPE, ieProp.ieInst, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isTransIdPres", &isTransIdPres);

	if(isTransIdPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addTransIdIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addTransIdIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
                      (Txt *)"TransIdValue", &TransIdVal);
       egIe.t.valUnSgnd32 = TransIdVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddTransIdIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
       }
	}
}




#ifdef ANSI
PUBLIC Void  makeAndAddProcedureTidIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddProcedureTidIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe egIe;
   U8   isProcedureTidPres;
   U8   ProcedureTidVal = DFLT_PROCEDURETID;

   TRC2(makeAndAddProcedureTidIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_PROCEDURE_TID_IETYPE, ieProp.ieInst,  EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isProcedureTidPres", &isProcedureTidPres);

	if(isProcedureTidPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addProcedureTidIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addProcedureTidIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ProcedureTidValue", &ProcedureTidVal);
       egIe.t.valUnSgnd8 = ProcedureTidVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddProcedureTidIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}



#ifdef ANSI
PUBLIC Void  makeAndAddNodeTypeIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddNodeTypeIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isNodeTypePres;
   U8    NodeTypeVal = DFLT_NODETYPE;

   TRC2(makeAndAddNodeTypeIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_NODE_TYPE_IETYPE, ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isNodeTypePres", &isNodeTypePres);

	if(isNodeTypePres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addNodeTypeIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addNodeTypeIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"NodeTypeValue", &NodeTypeVal);
       egIe.t.valUnSgnd8 = NodeTypeVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddNodeTypeIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}

#if EG_REL_930

#ifdef ANSI
PUBLIC Void  makeAndAddCsgInfoRepActIe
(
 CmXtaTCCb      *tcCb,
 CmXtaSpCb      *spCb,
 EgMsg      *egMsg,
 EgIeLevelInfo *egLvlInfo,
 LegIeProperties  ieProp
 )
#else
PUBLIC Void makeAndAddCsgInfoRepActIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
   CmXtaTCCb      *tcCb;
   CmXtaSpCb      *spCb;
   EgMsg      *egMsg;
   EgIeLevelInfo *egLvlInfo;
   LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isCsgInfoRepActPres;


   TRC2(makeAndAddCsgInfoRepActIe)

      /* Fill the ie properties */
      cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_CSG_INFO_REP_ACT_IETYPE, ieProp.ieInst, EG_CSG_INFO_REP_ACT);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	 (Txt *)"isCsgInfoRepActPres", &isCsgInfoRepActPres);

   if(isCsgInfoRepActPres)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"addCsgInfoRepActIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"addCsgInfoRepActIeInst",  &egIe.ieInst);

      egIe.t.csgInfoReqAct.isUCICSGPres  = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"isUCICSGPres",  &egIe.t.csgInfoReqAct.isUCICSGPres);

      egIe.t.csgInfoReqAct.isUCISHCPres  = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"isUCISHCPres",  & egIe.t.csgInfoReqAct.isUCISHCPres);

      egIe.t.csgInfoReqAct.isUCIUHCPres  = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"isUCIUHCPres",  &egIe.t.csgInfoReqAct.isUCIUHCPres);

      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
	 CMXTA_DBG_ERR((_cmxtap,"makeAndAddCsgInfoRepActIe() : Unable to Append IE to eGTP message\n"));
	 RETVOID;
      }
   }
}
#endif /* EG_REL_930 */


#ifdef ANSI
PUBLIC Void  makeAndAddServIndIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddServIndIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe  egIe;
   U8    isServIndPres;
   U8    ServIndVal = DFLT_SERVIND;

   TRC2(makeAndAddServIndIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_SERV_IND_IETYPE, ieProp.ieInst, EG_UNSIGNED_8);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isServIndPres", &isServIndPres);

	if(isServIndPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addServIndIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addServIndIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServIndValue", &ServIndVal);
       egIe.t.valUnSgnd8 = ServIndVal;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddServIndIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}


#ifdef ANSI
PUBLIC Void  makeAndAddBearerCntxIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddBearerCntxIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isBearerCntxPres;


   TRC2(makeAndAddBearerCntxie)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_BEARER_CNTX_IETYPE, ieProp.ieInst,EG_GROUPED);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isBearerCntxPres", &isBearerCntxPres);

	if(isBearerCntxPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addXXXIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addXXXIeInst",  &egIe.ieInst);


	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddBearerCntxie() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}



#ifdef ANSI
PUBLIC Void  makeAndAddSrcIdIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddSrcIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isSrcIdPres;
   U8     SourceType = DFLT_SOURCETYPE;
   Data   TargetCellIdVal[EG_MAX_STRING_LEN] = DFLT_TARGETCELLID_VAL;
   Data   SourceIdVal[EG_MAX_STRING_LEN] = DFLT_SOURCEID_VAL;

   TRC2(makeAndAddSrcIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe,EG_SRC_ID_IETYPE, ieProp.ieInst,EG_SRCID);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isSrcIdPres", &isSrcIdPres);

	if(isSrcIdPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addSrcIdIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addSrcIdIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                        (Txt *)"TargetCellIdVal", TargetCellIdVal);
       egIe.t.srcId.targetCellId.length = cmStrlen((U8 *)TargetCellIdVal);
       cmMemcpy( (U8 *)egIe.t.srcId.targetCellId.val, (U8 *)TargetCellIdVal, egIe.t.srcId.targetCellId.length);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                        (Txt *)"SourceIdVal", SourceIdVal);
       egIe.t.srcId.sourceId.length = cmStrlen((U8 *)SourceIdVal);
       cmMemcpy( (U8 *)egIe.t.srcId.sourceId.val, (U8 *)SourceIdVal ,egIe.t.srcId.sourceId.length);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                        (Txt *)"SourceIdVal", &SourceType);
       egIe.t.srcId.sourceType = SourceType;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddSrcIdIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}


#ifdef ANSI
PUBLIC Void  makeAndAddBearerQosIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddBearerQosIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isBearerQosPres = TRUE;
   U8        prityLvl  = DFLT_PRIRTLVL;          /**<  Priority Level */
   U8        qci       = DFLT_QCI;               /**<  QCI */
   Bool      isPVIPres = TRUE;                   /**<  PVI */
   Bool      isPCIPres = TRUE;                   /**<  PCI */
   Data   upMBRVal[EG_MAX_STRING_LEN] = DFLT_UPMBR_VAL;  /**<  Maximum bit rate for uplink */
   Data   dnMBRVal[EG_MAX_STRING_LEN] = DFLT_DNMBR_VAL;  /**<  Maximum bit rate for downlink */
   Data   upGBRVal[EG_MAX_STRING_LEN] = DFLT_UPGBR_VAL;  /**<  Guaranteed bit rate for uplink */
   Data   dnGBRVal[EG_MAX_STRING_LEN] = DFLT_DNGBR_VAL;  /**<  Guaranteed bit rate for downlink */


   TRC2(makeAndAddBearerQosIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_BEARER_QOS_IETYPE, ieProp.ieInst, EG_BQOS_IEDATA);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isBearerQosPres", &isBearerQosPres);

	if(isBearerQosPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addBearerQosIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addBearerQosIeInst",  &egIe.ieInst);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"prityLvl", &prityLvl);
	   egIe.t.bQos.prityLvl = prityLvl;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"qci",  &qci);
       egIe.t.bQos.qci = qci;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"isPVIPres", &isPVIPres);
       egIe.t.bQos.isPVIPres = isPVIPres;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"isPCIPres",  &isPCIPres);
       egIe.t.bQos.isPCIPres = isPCIPres;

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"upMBRVal", upMBRVal);
       egIe.t.bQos.upMBR.length = cmStrlen((U8 *)upMBRVal);
       cmMemcpy( (U8 *)egIe.t.bQos.upMBR.val, (U8 *)upMBRVal ,egIe.t.bQos.upMBR.length);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"dnMBRVal", dnMBRVal);
       egIe.t.bQos.dnMBR.length = cmStrlen((U8 *)dnMBRVal);
       cmMemcpy( (U8 *)egIe.t.bQos.dnMBR.val, (U8 *)dnMBRVal ,egIe.t.bQos.dnMBR.length);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"upGBRVal", upGBRVal);
       egIe.t.bQos.upGBR.length = cmStrlen((U8 *)upGBRVal);
       cmMemcpy( (U8 *)egIe.t.bQos.upGBR.val, (U8 *)upGBRVal ,egIe.t.bQos.upGBR.length);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"dnGBRVal", dnGBRVal);
       egIe.t.bQos.dnGBR.length = cmStrlen((U8 *)dnGBRVal);
       cmMemcpy( (U8 *)egIe.t.bQos.dnGBR.val, (U8 *)dnGBRVal ,egIe.t.bQos.dnGBR.length);

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddBearerQosIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}


#ifdef ANSI
PUBLIC Void  makeAndAddGblCnIdIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddGblCnIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isGblCnIdPres;

   Data   GblCnIdVal[EG_MAX_STRING_LEN] = DFLT_GBLCNID_VAL;

   TRC2(makeAndAddGblCnIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_GBL_CN_ID_IETYPE, ieProp.ieInst, EG_GLOBAL_CNID);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isGblCnIdPres", &isGblCnIdPres);

	if(isGblCnIdPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addGblCnIdIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addGblCnIdIeInst",  &egIe.ieInst);

       egIe.t.gblCnId.sNwk.mccDigit1 = 1;
       egIe.t.gblCnId.sNwk.mccDigit2 = 1;
       egIe.t.gblCnId.sNwk.mccDigit3 = 1;
       egIe.t.gblCnId.sNwk.mncDigit1 = 1;
       egIe.t.gblCnId.sNwk.mncDigit2 = 1;
       egIe.t.gblCnId.sNwk.mncDigit3 = 1;

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMccDigit1", &egIe.t.gblCnId.sNwk.mccDigit1);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMccDigit2", &egIe.t.gblCnId.sNwk.mccDigit2);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMccDigit3", &egIe.t.gblCnId.sNwk.mccDigit3);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMacDigit1", &egIe.t.gblCnId.sNwk.mncDigit1);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMacDigit2", &egIe.t.gblCnId.sNwk.mncDigit2);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMacDigit3", &egIe.t.gblCnId.sNwk.mncDigit3);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"GblCnIdVal", GblCnIdVal);

       egIe.t.gblCnId.cnId.length = cmStrlen((U8 *)GblCnIdVal);
       cmMemcpy( (U8 *)egIe.t.gblCnId.cnId.val, (U8 *)GblCnIdVal ,egIe.t.gblCnId.cnId.length);

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddGblCnIdIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}

#ifdef ANSI
PUBLIC Void  makeAndAddPduNumberIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPduNumberIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isPduNumberPres;

   U8  nsapi = DFLT_NSAPI;               /**< NSAPI */
   U16 dnLinkSeqNo = DFLT_DNLNKSEQNO;    /**< DownLink GTP-U Sequence Number */
   U16 upLinkSeqNo = DFLT_UPLNKSEQNO;    /**< UpLink GTP-U Sequence Number */
   U16 SNPduNo = DFLT_SNPDUNO;           /**< Send N-PDU Number */
   U16 RNPduNo = DFLT_RNPDUNO;           /**< Receive N-PDU Number */


   TRC2(makeAndAddPduNumberIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_PDU_NUMBER_IETYPE, ieProp.ieInst,EG_PDUNUM);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isPduNumberPres", &isPduNumberPres);

	if(isPduNumberPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addPduNumberIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addPduNumberIeInst",  &egIe.ieInst);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"nsapi",  &nsapi);
       egIe.t.pduNum.nsapi = nsapi;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
					  (Txt *)"dnLinkSeqNo",  &dnLinkSeqNo);
       egIe.t.pduNum.dnLinkSeqNo = dnLinkSeqNo;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
					  (Txt *)"upLinkSeqNo",  &upLinkSeqNo);
       egIe.t.pduNum.upLinkSeqNo = upLinkSeqNo;


	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
					  (Txt *)"SNPduNo",  &SNPduNo);
       egIe.t.pduNum.SNPduNo = SNPduNo;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
					  (Txt *)"RNPduNo",  &RNPduNo);
       egIe.t.pduNum.RNPduNo = RNPduNo;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddPduNumberIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}

#ifdef ANSI
PUBLIC Void  makeAndAddPktFlowIdIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddPktFlowIdIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isPktFlowIdPres;
   U8     ebi = DFLT_EBI;              /**< EBI */
   U8     pktFlowId = DFLT_PKTFLOWID;/**< Packet Flow ID */

   TRC2(makeAndAddPktFlowIdIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_PKT_FLOW_ID_IETYPE, ieProp.ieInst,EG_PKTFLOWID);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isPktFlowIdPres", &isPktFlowIdPres);

	if(isPktFlowIdPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addPktFlowIdIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addPktFlowIdIeInst",  &egIe.ieInst);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"ebi", &ebi);
	   egIe.t.pktFlowId.ebi = ebi;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"pktFlowId", &pktFlowId);
       egIe.t.pktFlowId.pktFlowId = pktFlowId;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddPktFlowIdIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}

#ifdef ANSI
PUBLIC Void  makeAndAddRabContextIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddRabContextIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isRabContextPres;
   U8     nsapi = DFLT_NSAPI;              /**< NSAPI */
   U16    dnlEgUSeqNo = DFLT_DNLEGUSEQNO;  /**< Downlink GTP-U Sequence Number */
   U16    uplEgUSeqNo = DFLT_UPLEGUSEQNO;  /**< Uplink GTP-U Sequence Number */
   U16    dnlPdcpSeqNo = DFLT_DNLPDCPSEQNO;/**< Downlink GTP-U Sequence Number */
   U16    uplPdcpSeqNo = DFLT_UPLPDCPSEQNO;/**< Uplink GTP-U Sequence Number */



   TRC2(makeAndAddRabContextIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_RAB_CONTEXT_IETYPE, ieProp.ieInst, EG_RAB_CONTEXT);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isRabContextPres", &isRabContextPres);

	if(isRabContextPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addRabContextIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addRabContextIeInst",  &egIe.ieInst);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"nsapi",  &nsapi);
	   egIe.t.rabCntxt.nsapi = nsapi;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
					  (Txt *)"dnlEgUSeqNo",  &dnlEgUSeqNo);
	   egIe.t.rabCntxt.dnlEgUSeqNo = dnlEgUSeqNo;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
					  (Txt *)"uplEgUSeqNo",  &dnlEgUSeqNo);
	   egIe.t.rabCntxt.uplEgUSeqNo = uplEgUSeqNo;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
					  (Txt *)"dnlPdcpSeqNo",  &dnlPdcpSeqNo);
	   egIe.t.rabCntxt.dnlPdcpSeqNo = dnlPdcpSeqNo;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U16,
					  (Txt *)"uplPdcpSeqNo",  &uplPdcpSeqNo);
	   egIe.t.rabCntxt.uplPdcpSeqNo = uplPdcpSeqNo;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddRabContextIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}

#ifdef ANSI
PUBLIC Void  makeAndAddS1UDatFwIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddS1UDatFwIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isS1UDatFwPres = TRUE;
	U8     ebi = DFLT_EBINUM;
	U32    sgwS1UTEID = DFLT_SGW_S1UTEID;
   Txt    ipAddr[100] = DFLT_IP_ADDRESS;

   TRC2(makeAndAddSUDatFwIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_S1U_DATA_FW_IETYPE , ieProp.ieInst, EG_S1U_DATA_FW);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isisS1UDatFwPres", &isS1UDatFwPres);

	if(isS1UDatFwPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addS1UDatFwIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"add1UDatFwIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"ebi",  &ebi);
		  egIe.t.s1UDF.ebi = ebi;

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                    (Txt *)"type", &egIe.t.s1UDF.sgwAddr.type);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                    (Txt *)"ipAddr", &ipAddr);

       egIe.t.s1UDF.sgwAddrLen = cmStrlen((U8 *)ipAddr);
       egIe.t.s1UDF.sgwAddr.type = CM_NETADDR_IPV4;

       switch (egIe.t.s1UDF.sgwAddr.type)
       {
          case CM_NETADDR_IPV4:
          {
             cmInetAddr ( (S8 *)ipAddr, &(egIe.t.s1UDF.sgwAddr.u.ipv4));
             break;
          } /* end of case */

#ifdef IPV6_SUPPORTED
          case CM_NETADDR_IPV6:
          {
             cmInetPton6(&egIe.t.s1UDF.sgwAddr.u.ipv6, (S8*)ipAddr);
             break;
          } /* end of case */
#endif /* end of IPV6_SUPPORTED */

          default:
          {
             CMXTA_DBG_ERR((_cmxtap,"makeAndAddS1UDatFwIe: Invalid IP Address Type\n"));
             RETVOID;
          } /* end of case */
       } /* end of switch */

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
					  (Txt *)"sgwS1UTEID",  &sgwS1UTEID);
	   egIe.t.s1UDF.sgwS1UTEID = sgwS1UTEID;


	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddS1UDatFwIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }

	}
}

#ifdef ANSI
PUBLIC Void  makeAndAddS103PdnFwInfoIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddS103PdnFwInfoIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isS103PdnFwInfoPres = TRUE;
   U32    greKey = DFLT_GREKEY;
   U8     ebiNumber = DFLT_EBINUM;
   Txt    ipAddr[100] = DFLT_IP_ADDRESS;
	U8     ebi[10] = {1,2,3,4,5,6},i;

   TRC2(makeAndAddS103PdnFwInfoIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_S103_PDN_FW_INFO_IETYPE, ieProp.ieInst, EG_S103_PDN_FW_INFO);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isS103PdnFwInfoPres", &isS103PdnFwInfoPres);

	if(isS103PdnFwInfoPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addS103PdnFwInfoIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addS103PdnFwInfoIeInst",  &egIe.ieInst);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
					  (Txt *)"greKey",  &greKey);
	   egIe.t.s103PDF.greKey = greKey;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"ebiNumber",  &ebiNumber);

	   egIe.t.s103PDF.ebiNumber = ebiNumber;
		

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                    (Txt *)"Ebi", egIe.t.s103PDF.ebi);
		for(i=0;i<ebiNumber;i++)
		{
			 egIe.t.s103PDF.ebi[i] = ebi[i];
		}


		 egIe.t.s103PDF.hsgwAddr.type = CM_NETADDR_IPV4;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                    (Txt *)"type", &egIe.t.s103PDF.hsgwAddr.type);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                    (Txt *)"ipAddr", &ipAddr);

       egIe.t.s103PDF.hsgwAddrLen = cmStrlen((U8 *)ipAddr);

       switch (egIe.t.s103PDF.hsgwAddr.type)
       {
          case CM_NETADDR_IPV4:
          {
             cmInetAddr ( (S8 *)ipAddr, &(egIe.t.s103PDF.hsgwAddr.u.ipv4));
             break;
          } /* end of case */

#ifdef IPV6_SUPPORTED
          case CM_NETADDR_IPV6:
          {
             cmInetPton6(&egIe.t.s103PDF.hsgwAddr.u.ipv6, (S8*)ipAddr);
             break;
          } /* end of case */
#endif /* end of IPV6_SUPPORTED */

          default:
          {
             CMXTA_DBG_ERR((_cmxtap,"makeAndAddS103PdnFwInfoIe: Invalid IP Address Type\n"));
             RETVOID;
          } /* end of case */
       } /* end of switch */

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddS103PdnFwInfoIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}


#ifdef ANSI
PUBLIC Void  makeAndAddUeTimeZoneIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddUeTimeZoneIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe egIe;
   U8   isUeTimeZonePres;
   U8   timezone1 = DFLT_TIMEZONE;              /**< Time Zone */
   U8   dayLiteSavTime = DFLT_DAYLITESAVTIME;  /**< Day Light Saving Time */


   TRC2(makeAndAddUeTimeZoneIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_UE_TIME_ZONE_IETYPE, ieProp.ieInst, EG_UE_TIME_ZONE);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isUeTimeZonePres", &isUeTimeZonePres);

	if(isUeTimeZonePres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addUeTimeZoneIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addUeTimeZoneIeInst",  &egIe.ieInst);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"timezone1", &timezone1);
		egIe.t.timeZone.timezone = timezone1;

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"dayLiteSavTime",  &dayLiteSavTime);
      egIe.t.timeZone.dayLiteSavTime = dayLiteSavTime;

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddUeTimeZoneIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}


#ifdef ANSI
PUBLIC Void  makeAndAddTraceRefIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddTraceRefIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isTraceRefPres;
   U32    trcId = DFLT_TRCID; /**< Trace Id */

   TRC2(makeAndAddTraceRefIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_TRACE_REF_IETYPE, ieProp.ieInst, EG_TRACE_REF);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isTraceRefPres", &isTraceRefPres);

	if(isTraceRefPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addTraceRefIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addTraceRefIeInst",  &egIe.ieInst);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addTraceRefIeInst",  &trcId);
       egIe.t.trcRef.trcId = trcId;

       egIe.t.trcRef.sNwk.mccDigit1 = 1;
       egIe.t.trcRef.sNwk.mccDigit2 = 1;
       egIe.t.trcRef.sNwk.mccDigit3 = 1;
       egIe.t.trcRef.sNwk.mncDigit1 = 1;
       egIe.t.trcRef.sNwk.mncDigit2 = 1;
       egIe.t.trcRef.sNwk.mncDigit3 = 1;

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMccDigit1", &egIe.t.trcRef.sNwk.mccDigit1);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMccDigit2", &egIe.t.trcRef.sNwk.mccDigit2);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMccDigit3", &egIe.t.trcRef.sNwk.mccDigit3);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMacDigit1", &egIe.t.trcRef.sNwk.mncDigit1);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMacDigit2", &egIe.t.trcRef.sNwk.mncDigit2);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ServNwMacDigit3", &egIe.t.trcRef.sNwk.mncDigit3);

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddTraceRefIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}



#ifdef ANSI
PUBLIC Void  makeAndAddUliIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddUliIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   Bool  isUliPres;
   Bool  isCGIPres = TRUE;    /**< CGI */
   Bool  isSAIPres = TRUE;    /**< SAI */
   Bool  isRAIPres = TRUE;    /**< RAI */
   Bool  isTAIPres = TRUE;    /**< TAI */
   Bool  isECGIPres = TRUE;   /**< ECGI */

   TRC2(makeAndAddUliIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_ULI_IETYPE, ieProp.ieInst, EG_ULI_DATA);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"isXXUliXPres", &isUliPres);

	if(isUliPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addUliIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addUliIeType", &egIe.ieInst);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"isCGIPres",  &isCGIPres);
	   egIe.t.uli.isCGIPres = isCGIPres;

	   if(egIe.t.uli.isCGIPres)
	   {
           egIe.t.uli.cgi.sNwk.mccDigit1 = 1;
           egIe.t.uli.cgi.sNwk.mccDigit2 = 1;
           egIe.t.uli.cgi.sNwk.mccDigit3 = 1;
           egIe.t.uli.cgi.sNwk.mncDigit1 = 1;
           egIe.t.uli.cgi.sNwk.mncDigit2 = 1;
           egIe.t.uli.cgi.sNwk.mncDigit3 = 1;

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit1", &egIe.t.uli.cgi.sNwk.mccDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit2", &egIe.t.uli.cgi.sNwk.mccDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit3", &egIe.t.uli.cgi.sNwk.mccDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit1", &egIe.t.uli.cgi.sNwk.mncDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit2", &egIe.t.uli.cgi.sNwk.mncDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit3", &egIe.t.uli.cgi.sNwk.mncDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"Lac", &egIe.t.uli.cgi.lac);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"Ci", &egIe.t.uli.cgi.ci);
	   }


	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"isSAIPres", &isSAIPres);
       egIe.t.uli.isSAIPres = isSAIPres;

       if(egIe.t.uli.isSAIPres)
       {
           egIe.t.uli.sai.sNwk.mccDigit1 = 1;
           egIe.t.uli.sai.sNwk.mccDigit2 = 1;
           egIe.t.uli.sai.sNwk.mccDigit3 = 1;
           egIe.t.uli.sai.sNwk.mncDigit1 = 1;
           egIe.t.uli.sai.sNwk.mncDigit2 = 1;
           egIe.t.uli.sai.sNwk.mncDigit3 = 1;

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit1", &egIe.t.uli.sai.sNwk.mccDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit2", &egIe.t.uli.sai.sNwk.mccDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit3", &egIe.t.uli.sai.sNwk.mccDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit1", &egIe.t.uli.sai.sNwk.mncDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit2", &egIe.t.uli.sai.sNwk.mncDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit3", &egIe.t.uli.sai.sNwk.mncDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"Lac", &egIe.t.uli.sai.lac);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"Sac", &egIe.t.uli.sai.sac);
	   }

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"isRAIPres",  &isRAIPres);
	   egIe.t.uli.isRAIPres = isRAIPres;

	   if(egIe.t.uli.isRAIPres)
	   {
           egIe.t.uli.rai.sNwk.mccDigit1 = 1;
           egIe.t.uli.rai.sNwk.mccDigit2 = 1;
           egIe.t.uli.rai.sNwk.mccDigit3 = 1;
           egIe.t.uli.rai.sNwk.mncDigit1 = 1;
           egIe.t.uli.rai.sNwk.mncDigit2 = 1;
           egIe.t.uli.rai.sNwk.mncDigit3 = 1;

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit1", &egIe.t.uli.rai.sNwk.mccDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit2", &egIe.t.uli.rai.sNwk.mccDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit3", &egIe.t.uli.rai.sNwk.mccDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit1", &egIe.t.uli.rai.sNwk.mncDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit2", &egIe.t.uli.rai.sNwk.mncDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit3", &egIe.t.uli.rai.sNwk.mncDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"Lac", &egIe.t.uli.rai.lac);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"Rac", &egIe.t.uli.rai.rac);
	   }

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"isTAIPres", &isTAIPres);
	   egIe.t.uli.isTAIPres = isTAIPres;

	   if(egIe.t.uli.isTAIPres)
	   {
           egIe.t.uli.tai.sNwk.mccDigit1 = 1;
           egIe.t.uli.tai.sNwk.mccDigit2 = 1;
           egIe.t.uli.tai.sNwk.mccDigit3 = 1;
           egIe.t.uli.tai.sNwk.mncDigit1 = 1;
           egIe.t.uli.tai.sNwk.mncDigit2 = 1;
           egIe.t.uli.tai.sNwk.mncDigit3 = 1;

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit1", &egIe.t.uli.tai.sNwk.mccDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit2", &egIe.t.uli.tai.sNwk.mccDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit3", &egIe.t.uli.tai.sNwk.mccDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit1", &egIe.t.uli.tai.sNwk.mncDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit2", &egIe.t.uli.tai.sNwk.mncDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit3", &egIe.t.uli.tai.sNwk.mncDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"Tac", &egIe.t.uli.tai.tac);
	   }

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"isECGIPres",  &isECGIPres);
	   egIe.t.uli.isECGIPres = isECGIPres;

	   if(egIe.t.uli.isECGIPres)
	   {
           egIe.t.uli.ecgi.sNwk.mccDigit1 = 1;
           egIe.t.uli.ecgi.sNwk.mccDigit2 = 1;
           egIe.t.uli.ecgi.sNwk.mccDigit3 = 1;
           egIe.t.uli.ecgi.sNwk.mncDigit1 = 1;
           egIe.t.uli.ecgi.sNwk.mncDigit2 = 1;
           egIe.t.uli.ecgi.sNwk.mncDigit3 = 1;

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit1", &egIe.t.uli.ecgi.sNwk.mccDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit2", &egIe.t.uli.ecgi.sNwk.mccDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMccDigit3", &egIe.t.uli.ecgi.sNwk.mccDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit1", &egIe.t.uli.ecgi.sNwk.mncDigit1);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit2", &egIe.t.uli.ecgi.sNwk.mncDigit2);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"ServNwMacDigit3", &egIe.t.uli.ecgi.sNwk.mncDigit3);

           cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                          (Txt *)"Ecid", &egIe.t.uli.ecgi.ecId);
	   }

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddUliIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}



#ifdef ANSI
PUBLIC Void  makeAndAddUmtsKeyQuadQuinIe
(
	CmXtaTCCb      *tcCb,
	CmXtaSpCb      *spCb,
	EgMsg      *egMsg,
	EgIeLevelInfo *egLvlInfo,
	LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddUmtsKeyQuadQuinIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
	CmXtaTCCb      *tcCb;
	CmXtaSpCb      *spCb;
	EgMsg      *egMsg;
	EgIeLevelInfo *egLvlInfo;
	LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isUmtsKeyQuadQuinPres = TRUE;
   Data   CkVal[EG_MAX_STRING_LEN] = DFLT_CK_VAL;
   Data   IkVal[EG_MAX_STRING_LEN] = DFLT_IK_VAL;
   Data   data[EG_MAX_STRING_LEN];

   TRC2(makeAndAddUmtsKeyQuadQuinIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_UMTS_KEY_QUAD_QUIN_IETYPE, ieProp.ieInst, EG_UMTS_KEY_QUAD_QUIN);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"UmtsKeyQuadQuinPres", &isUmtsKeyQuadQuinPres);

	if(isUmtsKeyQuadQuinPres)
	{
	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addUmtsKeyQuadQuinIeType", &egIe.ieType);

	   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
					  (Txt *)"addUmtsKeyQuadQuinIeInst",  &egIe.ieInst);

       egIe.t.eSecCxtQdQt.secMode = DFLT_SECMODE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"secMode",  &egIe.t.umtsKeyQdQt.secMode);

       egIe.t.eSecCxtQdQt.isDRXIPres = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"DRXIPres",  &egIe.t.umtsKeyQdQt.isDRXIPres);

       egIe.t.eSecCxtQdQt.ksi = DFLT_KSI;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"ksi",  &egIe.t.umtsKeyQdQt.ksi);

       egIe.t.eSecCxtQdQt.nmbQuin = DFLT_NMBQUIN;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"nmbQuin",  &egIe.t.umtsKeyQdQt.nmbQuin);

       egIe.t.eSecCxtQdQt.nmbQuadru = DFLT_NMBQUAD;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"nmbQuadru",  &egIe.t.umtsKeyQdQt.nmbQuadru);

       egIe.t.eSecCxtQdQt.isUAMBRIPres = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"UAMBRIPres",  &egIe.t.umtsKeyQdQt.isUAMBRIPres);

       egIe.t.eSecCxtQdQt.isSAMBRIPres = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"SAMBRIPres",  &egIe.t.umtsKeyQdQt.isSAMBRIPres);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"CkVal", CkVal);

       egIe.t.umtsKeyQdQt.ck.length = cmStrlen((U8 *)CkVal);
       cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.ck.val, (U8 *)CkVal ,egIe.t.umtsKeyQdQt.ck.length);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                     (Txt *)"IkVal", IkVal);

       egIe.t.umtsKeyQdQt.ik.length = cmStrlen((U8 *)IkVal);
       cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.ik.val, (U8 *)IkVal ,egIe.t.umtsKeyQdQt.ik.length);

       egIe.t.umtsKeyQdQt.authQuadru[0].rand.length = DFLT_RAND_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuadru[0].rand.val, (U8* )DFLT_RAND, DFLT_RAND_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"rand", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuadru[0].rand.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuadru[0].rand.val, (U8 *)data,egIe.t.umtsKeyQdQt.authQuadru[0].rand.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.authQuadru[0].xresLen = DFLT_XRES_LEN;
       egIe.t.umtsKeyQdQt.authQuadru[0].xres.length = DFLT_XRES_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuadru[0].xres.val, (U8* )DFLT_XRES, DFLT_XRES_LEN);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"xresLen",  &egIe.t.umtsKeyQdQt.authQuadru[0].xresLen);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"xres", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuadru[0].xres.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuadru[0].xres.val, (U8 *)data,egIe.t.umtsKeyQdQt.authQuadru[0].xres.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.authQuadru[0].autnLen = DFLT_AUTN_LEN;
       egIe.t.umtsKeyQdQt.authQuadru[0].autn.length = DFLT_AUTN_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuadru[0].autn.val, (U8* )DFLT_AUTN, DFLT_AUTN_LEN);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"autnLen",  &egIe.t.umtsKeyQdQt.authQuadru[0].autnLen);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"autn", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuadru[0].autn.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuadru[0].autn.val, (U8 *)data,egIe.t.umtsKeyQdQt.authQuadru[0].autn.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.authQuadru[0].kasme.length = DFLT_KASME_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuadru[0].kasme.val, (U8* )DFLT_KASME, DFLT_KASME_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"kasme", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuadru[0].kasme.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuadru[0].kasme.val, (U8 *)data,egIe.t.umtsKeyQdQt.authQuadru[0].kasme.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.authQuin[0].rand.length = DFLT_RAND_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuin[0].rand.val, (U8* )DFLT_RAND,DFLT_RAND_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"rand", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuin[0].rand.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuin[0].rand.val, (U8 *)data,egIe.t.umtsKeyQdQt.authQuin[0].rand.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.authQuin[0].xresLen = DFLT_XRES_LEN;
       egIe.t.umtsKeyQdQt.authQuin[0].xres.length = DFLT_XRES_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuin[0].xres.val, (U8* )DFLT_XRES,DFLT_XRES_LEN);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"xresLen",  &egIe.t.umtsKeyQdQt.authQuin[0].xresLen);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"xres", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuin[0].xres.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuin[0].xres.val, (U8 *)data,egIe.t.umtsKeyQdQt.authQuin[0].xres.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.authQuin[0].ck.length = DFLT_CK_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuin[0].ck.val, (U8* )DFLT_CK,DFLT_CK_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"ck", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuin[0].ck.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuin[0].ck.val, (U8 *)data, egIe.t.umtsKeyQdQt.authQuin[0].ck.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.authQuin[0].ik.length = DFLT_IK_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuin[0].ik.val, (U8* )DFLT_IK,DFLT_IK_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"ik", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuin[0].ik.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuin[0].ik.val, (U8 *)data, egIe.t.umtsKeyQdQt.authQuin[0].ik.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.authQuin[0].autnLen = DFLT_AUTN_LEN;
       egIe.t.umtsKeyQdQt.authQuin[0].autn.length = DFLT_AUTN_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.authQuin[0].autn.val, (U8* )DFLT_AUTN,DFLT_AUTN_LEN);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"autnLen",  &egIe.t.umtsKeyQdQt.authQuin[0].autnLen);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"autn", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.authQuin[0].autn.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.authQuin[0].autn.val, (U8 *)data,egIe.t.umtsKeyQdQt.authQuin[0].autn.length);
       } /* end of if */

       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.drxParam, (U8* )DFLT_DRXPARAM,DFLT_DRXPARAM_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"drxParam", data) != CMXTA_ERR_NO_VALUE)
       {
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.drxParam, (U8 *)data, cmStrlen(data));
       } /* end of if */

       egIe.t.umtsKeyQdQt.ueNtwrkCapb.length = DFLT_UE_NTWRK_CAPB_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.ueNtwrkCapb.val, (U8* )DFLT_UE_NTWRK_CAPB, DFLT_UE_NTWRK_CAPB_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"ueNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.ueNtwrkCapb.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.ueNtwrkCapb.val, (U8 *)data, egIe.t.umtsKeyQdQt.ueNtwrkCapb.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.msNtwrkCapb.length = DFLT_MS_NTWRK_CAPB_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.msNtwrkCapb.val, (U8* )DFLT_MS_NTWRK_CAPB_VAL, DFLT_UE_NTWRK_CAPB_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"ueNtwrkCapb", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.msNtwrkCapb.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.msNtwrkCapb.val, (U8 *)data, egIe.t.umtsKeyQdQt.msNtwrkCapb.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.meId.length = DFLT_MEID_LEN;
       cmMemcpy( (U8* )egIe.t.umtsKeyQdQt.meId.val, (U8* )DFLT_MEID,DFLT_MEID_LEN);

       if (cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                      (Txt *)"meId", data) != CMXTA_ERR_NO_VALUE)
       {
          egIe.t.umtsKeyQdQt.meId.length = cmStrlen( (U8 *)data);
          cmMemcpy( (U8 *)egIe.t.umtsKeyQdQt.meId.val, (U8 *)data, egIe.t.umtsKeyQdQt.meId.length);
       } /* end of if */

       egIe.t.umtsKeyQdQt.isUNA = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                (Txt *)"isUNA",  &egIe.t.umtsKeyQdQt.isUNA);

       egIe.t.umtsKeyQdQt.isGENA = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                (Txt *)"isGENA",  &egIe.t.umtsKeyQdQt.isGENA);

       egIe.t.umtsKeyQdQt.isGANA = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
             (Txt *)"isGANA",  &egIe.t.umtsKeyQdQt.isGANA);

       egIe.t.umtsKeyQdQt.isINA = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                (Txt *)"isINA",  &egIe.t.umtsKeyQdQt.isINA);

       egIe.t.umtsKeyQdQt.isENA = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                (Txt *)"isENA",  &egIe.t.umtsKeyQdQt.isENA);

       egIe.t.umtsKeyQdQt.isHNNA = TRUE;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                (Txt *)"isHNNA",  &egIe.t.umtsKeyQdQt.isHNNA);

       egIe.t.umtsKeyQdQt.upSubsUEAMBR = DFLT_UPSUBSUEAMBR;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
       (Txt *)"upSubsUEAMBR",  &egIe.t.umtsKeyQdQt.upSubsUEAMBR);

       egIe.t.umtsKeyQdQt.dnSubsUEAMBR = DFLT_DNSUBSUEAMBR;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
       (Txt *)"dnSubsUEAMBR",  &egIe.t.umtsKeyQdQt.dnSubsUEAMBR);

       egIe.t.umtsKeyQdQt.upUsedUEAMBR = DFLT_UPUSEDUEAMBR;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
       (Txt *)"upUsedUEAMBR",  &egIe.t.umtsKeyQdQt.upUsedUEAMBR);

       egIe.t.umtsKeyQdQt.dnUsedUEAMBR = DFLT_DNUSEDUEAMBR;
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
       (Txt *)"dnUsedUEAMBR",  &egIe.t.umtsKeyQdQt.dnUsedUEAMBR);

	   if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
	   {
			CMXTA_DBG_ERR((_cmxtap,"makeAndAddUmtsKeyQuadQuinIe() : Unable to Append IE to eGTP message\n"));
			RETVOID;
	   }
	}
}

#ifdef EG_REL_930

#ifdef ANSI
PUBLIC Void  makeAndAddMbmsSessDurationIe
(
 CmXtaTCCb      *tcCb,
 CmXtaSpCb      *spCb,
 EgMsg      *egMsg,
 EgIeLevelInfo *egLvlInfo,
 LegIeProperties  ieProp
 )
#else
PUBLIC Void makeAndAddMbmsSessDurationIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
   CmXtaTCCb      *tcCb;
   CmXtaSpCb      *spCb;
   EgMsg      *egMsg;
   EgIeLevelInfo *egLvlInfo;
   LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isMbmsSessDurationPres = TRUE;


   TRC2(makeAndAddMbmsSessDurationIe)

      /* Fill the ie properties */
      cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_MBMS_SESS_DURATION_IETYPE, ieProp.ieInst, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	 (Txt *)"isMbmsSessDurationPres", &isMbmsSessDurationPres);

   if(isMbmsSessDurationPres)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"addMbmsSessDurationIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"addMbmsSessDurationIeInst",  &egIe.ieInst);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
	    (Txt *)"MbmsSessDuration", &egIe.t.valUnSgnd32);

      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
	 CMXTA_DBG_ERR((_cmxtap,"makeAndAddMbmsSessDurationIe() : Unable to Append IE to eGTP message\n"));
	 RETVOID;
      }
   }
}

#ifdef ANSI
PUBLIC Void  makeAndAddUciIe
(
 CmXtaTCCb      *tcCb,
 CmXtaSpCb      *spCb,
 EgMsg      *egMsg,
 EgIeLevelInfo *egLvlInfo,
 LegIeProperties  ieProp
 )
#else
PUBLIC Void makeAndAddUciIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
   CmXtaTCCb      *tcCb;
   CmXtaSpCb      *spCb;
   EgMsg      *egMsg;
   EgIeLevelInfo *egLvlInfo;
   LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isUciPres;


   TRC2(makeAndAddUciIe)

      /* Fill the ie properties */
      cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_UCI_IETYPE, ieProp.ieInst, EG_UCI);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	 (Txt *)"isUciPres", &isUciPres);

   if(isUciPres)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"addUciIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"addUciIeInst",  &egIe.ieInst);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U32,
	    (Txt *)"csgId",  &egIe.t.uci.csgId);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"accMode",  &egIe.t.uci.accMode);

      egIe.t.uci.isLCSGPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"isLCSGPres",  &egIe.t.uci.isLCSGPres);

      egIe.t.uci.isCMIPres = TRUE;
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"isCMIPres",  &egIe.t.uci.isCMIPres);

      egIe.t.uci.sNwk.mccDigit1 = 1;
      egIe.t.uci.sNwk.mccDigit2 = 1;
      egIe.t.uci.sNwk.mccDigit3 = 1;
      egIe.t.uci.sNwk.mncDigit1 = 1;
      egIe.t.uci.sNwk.mncDigit2 = 1;
      egIe.t.uci.sNwk.mncDigit3 = 1;

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"ServNwMccDigit1", &egIe.t.uci.sNwk.mccDigit1);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"ServNwMccDigit2", &egIe.t.uci.sNwk.mccDigit2);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"ServNwMccDigit3", &egIe.t.uci.sNwk.mccDigit3);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"ServNwMacDigit1", &egIe.t.uci.sNwk.mncDigit1);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"ServNwMacDigit2", &egIe.t.uci.sNwk.mncDigit2);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"ServNwMacDigit3", &egIe.t.uci.sNwk.mncDigit3);

      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
	 CMXTA_DBG_ERR((_cmxtap,"makeAndAddUciIe() : Unable to Append IE to eGTP message\n"));
	 RETVOID;
      }
   }
}

#ifdef ANSI
PUBLIC Void  makeAndAddTmgIe
(
 CmXtaTCCb      *tcCb,
 CmXtaSpCb      *spCb,
 EgMsg      *egMsg,
 EgIeLevelInfo *egLvlInfo,
 LegIeProperties  ieProp
 )
#else
PUBLIC Void makeAndAddTmgIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
   CmXtaTCCb      *tcCb;
   CmXtaSpCb      *spCb;
   EgMsg      *egMsg;
   EgIeLevelInfo *egLvlInfo;
   LegIeProperties ieProp;
#endif /* ANSI */
{
   EgIe   egIe;
   U8     isTmgPres = TRUE;
	Txt tmgi[]="tmgidatatmgidatatmgidata";



   TRC2(makeAndAddTmgIe)

      /* Fill the ie properties */
      cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));


   egAcEgtBuildEgIeHeader(&egIe, EG_TMGI_IETYPE, ieProp.ieInst, EG_UNSIGNED_32);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	 (Txt *)"isTmgPres", &isTmgPres);

   if(isTmgPres)
   {
      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"addTmgIeType", &egIe.ieType);

      cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	    (Txt *)"addTmgIeInst",  &egIe.ieInst);

		 egIe.t.valStr32.length = cmStrlen((U8 *)tmgi);
		    cmMemcpy((U8 *) egIe.t.valStr32.val, (U8 *)tmgi, egIe.t.valStr32.length);


      if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
      {
	 CMXTA_DBG_ERR((_cmxtap,"makeAndAddTmgIe() : Unable to Append IE to eGTP message\n"));
	 RETVOID;
      }
   }
}

#endif /*EG_REL_930*/

/* eg012.201 : flag dependencies added */
#if defined(EG_S2B_SUPP) || defined(EG_S2A_SUPP)
/* eg009.201 - Added for S2B and S2A */
PUBLIC Void  makeAndAddLdnIe ARGS ((
CmXtaTCCb        *tcCb,
CmXtaSpCb        *spCb,
EgMsg            *egMsg,
EgIeLevelInfo    *egLvlInfo,
LegIeProperties  ieProp
))
{
   EgIe   egIe;
   U8     isLdnPres = TRUE;
   Data   ldnVal[EG_MAX_STRING_LEN] = DFLT_LDN_VAL;
   TRC2(makeAndAddLdnIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe, EG_LDN_IETYPE, ieProp.ieInst, EG_STRING_MAX);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
	 (Txt *)"isLdnPres", &isLdnPres);

   if(isLdnPres)
   {
       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addLdnIeType", &egIe.ieType);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                      (Txt *)"addLdnIeInst",  &egIe.ieInst);

       cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                    (Txt *)"ldnVal", ldnVal);

       egIe.t.valStr.length = cmStrlen((U8 *)ldnVal);
       cmMemcpy( (U8 *)egIe.t.valStr.val, (U8 *)ldnVal ,egIe.t.valStr.length);

       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap,"makeAndAddFqdnIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
    }

}

/*
*
*       Fun:   makeAndAddApcoIe
*
*       Desc:  This function is used to Build APCO Ie
*
*       Ret:   None
*
*       Notes: None
*
*       File: smeg_ieutl.c
*
*/

#ifdef ANSI
PUBLIC Void  makeAndAddApcoIe
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
EgMsg      *egMsg,
EgIeLevelInfo *egLvlInfo,
LegIeProperties  ieProp
)
#else
PUBLIC Void makeAndAddApcoIe(tcCb,spCb,egMsg,egLvlInfo, ieProp)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
EgMsg      *egMsg;
EgIeLevelInfo *egLvlInfo;
LegIeProperties ieProp;
#endif /* ANSI */
{
   Data   apcoVal[EG_MAX_STRING_LEN] = DFLT_APCO_VAL;
   U8     apcoPresent = TRUE;
   EgIe   egIe;

   /*-- eg003.201 : TRC changes from eg006.102 --*/
   EG_TRC2(makeAndAddApcoIe)

   /* Fill the ie properties */
   cmMemset((U8 *)&egIe, 0 , sizeof(EgIe));

   egAcEgtBuildEgIeHeader(&egIe,EG_APCO_IETYPE,ieProp.ieInst, EG_STRING_MAX);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_TXT,
                  (Txt *)"apcoVal", apcoVal);

   egIe.t.valStr.length = cmStrlen((U8 *)apcoVal);
   cmMemcpy((U8 *) egIe.t.valStr.val, (U8 *)apcoVal,egIe.t.valStr.length);
   egIe.t.valStr.spare1 = 0;
#ifdef ALIGN_64BIT
   egIe.t.valStr.spare2 = 0;
#endif

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"apcoIeType", &egIe.ieType);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  (Txt *)"apcoPresent",  &apcoPresent);

   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8,
                  (Txt *)"apcoIeInst",  &egIe.ieInst);


   if( apcoPresent == TRUE)
   {
       if(EgUtilGmAppendIe(egMsg, egLvlInfo, &egIe) != ROK)
       {
            CMXTA_DBG_ERR((_cmxtap, "makeAndAddApcoIe() : Unable to Append IE to eGTP message\n"));
            RETVOID;
       }
   }

} /* makeAndAddApcoIe */

/* eg012.201 : flag dependency end */
#endif /* EG_S2B_SUPP || EG_S2A_SUPP */
#endif /* EGTP_C */
/**********************************************************************

         End of file:     smeg_ieutl.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:19:09 2015

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
/main/1      ---      nk   1. Initial Release
/main/1      ---      svenkat   1. Initial for eGTP 1.2 Release
/main/2      ---      pmacharla         Initial for eGTP release 2.1
/main/2     eg003.201 psingh    1. Merged code from eg006.102 to Fix 
                                   TRACE5 macro related issue
/main/2     eg004.201 magnihotri 1. Header files added for eGTPC PSF Upgrade
            eg009.201 asaurabh   1. Added for S2B and S2A .
/main/2     eg011.201 avenugop   1. Added xml support for piggyback feature
/main/2     eg012.201 shpandey   1. Added Flags for conditional compilation
*********************************************************************91*/
