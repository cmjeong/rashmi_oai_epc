
/********************************************************************20**

     Name:    X2AP - acc test file

     Type:    C Include file

     Desc:    This file contains the acc source code

     File:    czac_cztutl.c

     Sid:      czac_cztutl_r9.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:17 2015

     Prg:     aj 
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
#include "cm_pasn.h"        /* common transport defines */
#include "cm_dns.h"         /* common DNS libraru defines */

#include "cz.h"            /* defines and macros for CZ */
#include "lcz.h"            /* defines and macros for CZ */
#include "sct.h"            /* defines and macros for CZ */
#include "czac_asn.h"            /* defines and macros for CZ */
#include "czt.h"            /* defines and macros for CZ */
#include "cz_err.h"        /* CZ error defines */
#include "czac_acc.h"        /* defines for CZ acceptance tests */
#include "cm_xta.h" 
#ifdef SB
#include "lsb.h"            /* SCTP layer managment defines */
#endif /*SB*/
#ifdef HI
#include "lhi.h"            /* TUCL layer managment defines */
#endif /*hi*/

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
#include "cm_pasn.x"        /* common transport defines */
#include "cm_dns.x"         /* common DNS libraru defines */

#include "cm_xta.x" 
#include "sct.x"           /* typedefs for STCP */
#include "lcz.x"           /* layer management typedefs for CZCP */
#include "czac_asn.x"
using namespace CZ_LTEX2AP_REL9;
#include "czac_czt_inf.x"           /* typedefs for CZCP */
#include "cz.x"            /* typedefs for CZCP */
#ifdef SB
#include "lsb.x"           /* SCTP layer managment structures */
#endif /*SB*/
#ifdef HI
#include "lhi.x"           /* TUCL layer managment structures */
#endif /*hi*/
#include "czac_acc.x"      /* typedefs for CZCP acceptance tests */
#include "czac_czt.x"

EXTERN CzAcCztPduInfo czacPduInfo[CZAC_MAX_PROCS][CZAC_LCZ_MAX_CONN];

PRIVATE S16 czFillTknBStr32 ARGS ((TknBStr32 *ptr, U16 len, U32 val));


/* cz001.101 : CR Fixes. */


/*
*
*       Fun:   czAcUtlCztFillGpReqPdu
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillGpReqPdu_R9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt      **cztEvent
)
#else
PUBLIC S16 czAcUtlCztFillGpReqPdu_R9(tcCb, spCb, cztEvent)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CztEvnt      **cztEvent;
#endif
{

   U8 evntType = 0;

   TRC2(czAcUtlCztFillGpReqPdu);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztFillGpReqPdu(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztFillGpReqPdu(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(evntType));

   switch(evntType)
   {
      case CZT_MSG_LOAD_IND:
         {
            if(czAcUtlCztFillLoadInd_R9(tcCb, spCb, cztEvent)!=ROK)
            RETVALUE(RFAILED);

            break;
         }
      case CZT_MSG_X2_SETUP:
         {
            if(czAcUtlCztFillX2SetupReq_R9(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }
      case CZT_MSG_RESET:
         {
            if(czAcUtlCztFillReset(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }
      case CZT_MSG_CFG_UPD_REQ:
         {
            if(czAcUtlCztFillENBConfigUpd(tcCb, spCb, cztEvent)!=ROK)    
               RETVALUE(RFAILED);
            break;
         }
      case CZT_MSG_RSRC_ST_REQ:
         {
            if(czAcUtlCztFillResStatusRqst_R9(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }
      case CZT_MSG_RSRC_ST_UPD:
         {
            if(czAcUtlCztFillResStatusUpd_R9(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }
      case CZT_MSG_MOB_CHANGE_REQ:
         {
            if(czAcUtlCztFillMobChgReq(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }

       case CZT_MSG_RLF_INDICATION:
         {
            if(czAcUtlCztFillRlfInd_R9(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }

       case CZT_MSG_HO_REPORT:
         {
            if(czAcUtlCztFillHOReport(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }

       case CZT_MSG_CELL_ACTIVATION_REQ:
         {
             if(czAcUtlCztFillCellActReq(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }
      case CZT_MSG_PRIV_MSG:
         {
            if(czAcUtlCztFillPrivateMsg(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }
      default:
         CMXTA_DBG_ERR((_cmxtap,"czAcUtlCztFillGpReqPdu: Invalid Msg, msg = %d line =  %d\n",
                  evntType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);

} /* czAcUtlCztFillGpReqPdu */

/*
*
*       Fun:   czAcUtlCztFillGpRspPdu
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillGpRspPdu_R9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt      **cztEvent
)
#else
PUBLIC S16 czAcUtlCztFillGpRspPdu_R9(tcCb, spCb, cztEvent)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CztEvnt    **cztEvent;
#endif
{

   U8 eventType;

   TRC2(czAcUtlCztFillGpRspPdu);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztFillGpRspPdu(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztFillGpRspPdu(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(eventType));

   switch(eventType)
   {
      case CZT_MSG_X2_SETUP_RSP:
      {
         if(czAcUtlCztFillX2SetupRsp(tcCb, spCb, cztEvent)!=ROK)
              RETVALUE(RFAILED);
         break;
      }
      case CZT_MSG_X2_SETUP_FAIL:
         {
            if(czAcUtlCztFillX2SetupFail(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
            break;
         }
      case CZT_MSG_RESET_RSP:
      {
         if((czAcUtlCztFillResetAck(tcCb, spCb, cztEvent)) != ROK)
          RETVALUE(RFAILED);
         break;
      }
      case CZT_MSG_CFG_UPD_ACK:
      {
         if(czAcUtlCztFillENBConfigUpdAckg(tcCb, spCb, (cztEvent)) != ROK)
            RETVALUE(RFAILED);
         break;
      }
      case CZT_MSG_CFG_UPD_FAIL:
      {
         if(czAcUtlCztFillENBConfigUpdFail(tcCb, spCb, cztEvent)!=ROK)
           RETVALUE(RFAILED);
         break;
      }
      case CZT_MSG_RSRC_ST_RSP:
      {
        if(czAcUtlCztResStatusResp_R9(tcCb, spCb, (cztEvent)) != ROK)
               RETVALUE(RFAILED);
        break;
      }     
      case CZT_MSG_RSRC_ST_FAIL:
      {
         if(czAcUtlCztFillResStatusFail_R9(tcCb, spCb, cztEvent)!=ROK)
               RETVALUE(RFAILED);
         break;
      }
      case CZT_MSG_MOB_CHANGE_ACK:
      {
         if(czAcUtlCztFillMobChgAck(tcCb, spCb, cztEvent)!=ROK)
                 RETVALUE(RFAILED);
         break;
      }
      case CZT_MSG_MOB_CHANGE_FAIL:
      {
         if(czAcUtlCztFillMobChgFail(tcCb, spCb, cztEvent)!=ROK)
                 RETVALUE(RFAILED);
         break;
      }

       case CZT_MSG_CELL_ACTIVATION_RES:
      {
         if(czAcUtlCztFillCellActRes(tcCb, spCb, cztEvent)!=ROK)
                 RETVALUE(RFAILED);
         break;
      }
      case CZT_MSG_CELL_ACTIVATION_FAIL:
      {
         if(czAcUtlCztFillCellActFail(tcCb, spCb, cztEvent)!=ROK)
                 RETVALUE(RFAILED);
         break;
      }
      default:
         CMXTA_DBG_ERR((_cmxtap,"czAcUtlCztFillGpRspPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK);
} /* czAcUtlCztFillGpRspPdu */

/*
*
*       Fun:   czAcUtlCztFillBmpReqPdu
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillBmpReqPdu_R9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt    **evnt
)
#else
PUBLIC S16 czAcUtlCztFillBmpReqPdu_R9(tcCb, spCb, evnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CztEvnt    **evnt;
#endif
{
   U8    eventType;

   TRC2(czAcUtlCztFillBmpReqPdu);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztFillBmpReqPdu(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztFillBmpReqPdu(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType", &(eventType));

   switch(eventType)
   {
      case CZT_MSG_HO_REQ:
         {
            if(czAcUtlCztFillHovrRqst_R9(tcCb, spCb, (evnt)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case CZT_MSG_HO_CANCEL:
         {
            if(czAcUtlCztFillHovrCancel(tcCb, spCb, (evnt)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case CZT_MSG_SN_STATUS_TRFR:
         {
            if(czAcUtlCztFillSnStatusTrfr(tcCb, spCb, (evnt)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case CZT_MSG_UE_CXT_RELEASE:
         {
            if(czAcUtlCztFillUeCxtRls(tcCb, spCb, (evnt)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
       default:
         CMXTA_DBG_ERR((_cmxtap,"czAcUtlCztFillBmpReqPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }

   
   RETVALUE(ROK);

} /* czAcUtlCztFillBmpReqPdu */

/*
*
*       Fun:   czAcUtlCztFillBmpRspPdu
*
*       Desc:  Call handler to fill common field
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillBmpRspPdu_R9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt     **evnt
)
#else
PUBLIC S16 czAcUtlCztFillBmpRspPdu_R9(tcCb, spCb, evnt)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CztEvnt     **evnt;
#endif
{
   U8 eventType;

   TRC2(czAcUtlCztFillBmpRspPdu);

#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztFillBmpRspPdu(), tcId (%d)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "czAcUtlCztFillBmpRspPdu(), tcId (%ld)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"eventType",&(eventType));

   switch(eventType)
   {
      case CZT_MSG_HO_ACK:
         {
            if(czAcUtlCztFillHovrRqstAck(tcCb, spCb, (evnt)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      case CZT_MSG_HO_FAIL:
         {
            if(czAcUtlCztFillHovrPrepFail(tcCb, spCb, (evnt)) != ROK)
               RETVALUE(RFAILED);
         }
         break;
      default:
         CMXTA_DBG_ERR((_cmxtap,"czAcUtlCztFillBmpRspPdu: Invalid Msg, msg = %d line =  %d\n",
                        eventType,__LINE__));
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);

} /* czAcUtlCztFillBmpRspPdu */

/*
*
*       Fun:   czFillTknStr4
*
*       Desc:  Call handler to fill Octet string of length less than 4
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czFillTknStr4
(
TknStr4 *ptr,     /* Pointer to the structure */
U8      len,      /* length to be filled */
U8      val       /* byte to be repetitively filled in */
)
#else
PUBLIC S16 czFillTknStr4(ptr, len, val)
TknStr4 *ptr;     /* Pointer to the structure */
U8      len;      /* length to be filled */
U8      val;      /* byte to be repetitively filled in */
#endif
{
   U8      i;     /* counter */

   TRC2(czFillTknStr4)

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

} /* end of czFillTknStr4 */

/*
*
*       Fun:   czFillTknStrOSXL
*
*       Desc:  Call handler to fill Octet string
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czFillTknStrOSXL
(
TknStrOSXL *ptr,     /* Pointer to the structure */
U16         len,     /* length to be filled */
Data       *val,     /* byte to be repetitively filled in */
CztEvnt    **pdu
)
#else
PUBLIC S16 czFillTknStrOSXL(ptr, len, val, pdu)
TknStrOSXL *ptr;  /* Pointer to the structure */
U16         len;  /* lenrah to be filled */
Data       *val;  /* byte to be repetitively filled in */
CztEvnt    **pdu;
#endif
{
   U16     i;     /* counter */

   TRC2(czFillTknStrOSXL)

   /* make the element as present */
   ptr->pres = TRUE;
   ptr->len =  len;

   if (cmGetMem(pdu[0], len * sizeof(U8), (Ptr *)&ptr->val) != ROK)
   {
      CMXTA_DBG_ERR((_cmxtap,"czFillTknStrOSXL: cmGetMem failed, line %d\n",__LINE__));
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
*       Fun:   czFillTknBStr32
*
*       Desc:  Call handler to fill Bit String of length less than 32 
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czFillTknBStr32
(
TknBStr32  *ptr,     /* Pointer to the structure */
U16         len,     /* length to be filled */
U32         val      /* value to be filled in */
)
#else
PUBLIC S16 czFillTknBStr32(ptr, len, val)
TknBStr32  *ptr;  /* Pointer to the structure */
U16         len;  /* length to be filled */
U32         val;  /* value to be filled in */
#endif
{
   U32 valMask = 0;
   U8 indx;

   TRC2(czFillTknBStr32)

   if (len > 32)
   {
      RETVALUE(RFAILED);
   }

   /* make the element as present */
   ptr->pres = TRUE;
   ptr->len = (U8) len;

   /* *(U32*)ptr->val = (val << (32 - len)); */
   *(U32*)ptr->val = (val);
   valMask = 0x000000FF;
   for (indx = 0; indx <(len/8); indx++)
   { 
      ptr->val[indx] = val & valMask; 
      valMask = valMask << 8;
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillX2SetupReq
*
*       Desc:  Call handler to fill X2 setup request message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillX2SetupReq_R9
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt      **pdu
)
#else
PUBLIC S16 czAcUtlCztFillX2SetupReq_R9(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CztEvnt      **pdu;
#endif
{  
   CztEvnt *x2SetupRqstPdu=NULLP;
   U16      numComp;
   U8         tAC[10];
   S16      ret;
   U8         pLMNId[10];
   U8         choice;
   U8         cellId[28];
   U16        len;
   S16        idx;
   Mem  mem; 
   U32 val = 100;
   CztProtIE_Field_X2SetupRqst_IEs *ie;
   CztSrvdCellsMember *ie1;
   Bool encodeFail = FALSE;

   mem.region = 0;
   mem.pool   = 0;
   TRC2(czAcUtlCztFillX2SetupReq_R9); 
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&x2SetupRqstPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(x2SetupRqstPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(x2SetupRqstPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(x2SetupRqstPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(x2SetupRqstPdu->pdu.val.initiatingMsg.procedureCode), Cztid_x2Setup);
   czAcUtlFillTknU32(&(x2SetupRqstPdu->pdu.val.initiatingMsg.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(x2SetupRqstPdu->pdu.val.initiatingMsg.value.u.cztX2SetupRqst.pres), PRSNT_NODEF);

   /* Filling 2 mandatory IEs */
   numComp = 2;
   czAcUtlFillTknU16(&(x2SetupRqstPdu->pdu.val.initiatingMsg.value.u.cztX2SetupRqst.protocolIEs.noComp), numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(x2SetupRqstPdu, (numComp * sizeof(CztProtIE_Field_X2SetupRqst_IEs)),
               (Ptr*)&x2SetupRqstPdu->pdu.val.initiatingMsg.value.u.cztX2SetupRqst.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

      ie = &x2SetupRqstPdu->pdu.val.initiatingMsg.value.u.cztX2SetupRqst.protocolIEs.member[0];
   /* IE1 - Filling ENB Global Id */
   if(encodeFail == FALSE)
   {
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_GlobalENB_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
      czAcUtlFillTknU8(&(ie->value.u.cztGlobalENB_ID.pres), PRSNT_NODEF);

      /* Fill the PLMN ID in target Cell Id */
      cmMemset(pLMNId, 0, sizeof(pLMNId));
      strcpy((char *)pLMNId, "111");
      len = 3;

      /* Fill the PLMN ID */
      czFillTknStrOSXL(&(ie->value.u.cztGlobalENB_ID.pLMN_Identity), 
            len, pLMNId, &x2SetupRqstPdu);


      choice= ENB_ID_HOME_ENB_ID;

      switch (choice)
      {
         case ENB_ID_MACRO_ENB_ID:
            czAcUtlFillTknU8(&(ie->value.u.cztGlobalENB_ID.eNB_ID.choice), choice);
            czFillTknStr4(&(ie->value.u.cztGlobalENB_ID.eNB_ID.val.macro_eNB_ID),4,ENB_ID_MACRO_ENB_ID);
            break;
         case ENB_ID_HOME_ENB_ID:
            czAcUtlFillTknU8(&(ie->value.u.cztGlobalENB_ID.eNB_ID.choice), choice);

            cmMemset(cellId ,0, sizeof(cellId));
            for (idx = 0; idx < 28; idx++)
               cellId[idx] = 0xFF;
            len = 28;
            czFillTknBStr32(&(ie->value.u.cztGlobalENB_ID.eNB_ID.val.home_eNB_ID), len, val);

            /*
               czFillTknStr4(&(ie->value.u.cztGlobalENB_ID.eNB_ID.val.home_eNB_ID),4,ENB_ID_HOME_ENB_ID);
               */

            break;
         default:
            czAcUtlFillTknU8(&(ie->value.u.cztGlobalENB_ID.eNB_ID.choice), ENB_ID_HOME_ENB_ID);
            czFillTknStr4(&(ie->value.u.cztGlobalENB_ID.eNB_ID.val.macro_eNB_ID),4,ENB_ID_MACRO_ENB_ID);
            break;
      }

      ie->value.u.cztGlobalENB_ID.iE_Extns.noComp.pres = NOTPRSNT;
   
      /* IE2 - Filling Served Cells */
   ie = &x2SetupRqstPdu->pdu.val.initiatingMsg.value.u.cztX2SetupRqst.protocolIEs.member[1];

   czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->id), Cztid_SrvdCells);
   czAcUtlFillTknU32(&(ie->criticality),CztCriticalityrejectEnum);
   numComp = 1;
   czAcUtlFillTknU16(&(ie->value.u.cztSrvdCells.noComp), numComp);

   if ((cmGetMem(x2SetupRqstPdu,(numComp * sizeof(CztSrvdCellsMember)),
               (Ptr *)&ie->value.u.cztSrvdCells.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }
   ie1 = &ie->value.u.cztSrvdCells.member[0];

   czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);
   czAcUtlFillTknU8(&(ie1->servedCellInfo.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie1->servedCellInfo.pCI), val);
   czAcUtlFillTknU8(&(ie1->servedCellInfo.cellId.pres), PRSNT_NODEF);
   /* Fill the PLMN ID in target Cell Id */
   cmMemset(pLMNId, 0, sizeof(pLMNId));
   strcpy((char *)pLMNId, "111");
   len = 3;

   /* Fill the PLMN ID */
   czFillTknStrOSXL(&(ie1->servedCellInfo.cellId.pLMN_Identity), 
         len, pLMNId, &x2SetupRqstPdu);

   cmMemset(cellId ,0, sizeof(cellId));
   for (idx = 0; idx < 28; idx++)
      cellId[idx] = 0xFF;
   len = 28;
   czFillTknBStr32(&(ie1->servedCellInfo.cellId.eUTRANcellIdentifier), len, val);

   /*      
   czFillTknStrOSXL(&(ie1->servedCellInfo.cellId.pLMN_Identity),3, 'p', &x2SetupRqstPdu);
   czAcUtlFillTknU32(&(ie1->servedCellInfo.cellId.eUTRANcellIdentifier),cellId);

   czFillTknStrOSXL(&(ie1->servedCellInfo.tAC), 2, 11, &x2SetupRqstPdu);     
   */

            /* Fill the mmeGepId ID */
         cmMemset(tAC, 0, sizeof(tAC));
         strcpy((char *)tAC, "11");
         len = 2;

         czFillTknStr4(&(ie1->servedCellInfo.tAC), len, 1);

   /*  Filling broadcastPLMNs */
   numComp = 1;
   /* Allocate memory for broadcast PLMNs */
   if ((cmGetMem(x2SetupRqstPdu, numComp*sizeof(CztPLMN_Identity),
               (Ptr*)&ie1->servedCellInfo.broadcastPLMNs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }
   czAcUtlFillTknU16(&(ie1->servedCellInfo.broadcastPLMNs.noComp),numComp);

            cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;

   czFillTknStrOSXL(&(ie1->servedCellInfo.broadcastPLMNs.member[0]), len, pLMNId, &x2SetupRqstPdu);
   choice= EUTRA_MODE_INFO_FDD;

   switch (choice)
   {
      case EUTRA_MODE_INFO_FDD:
         czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
         czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.pres),PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_EARFCN),22);
         czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_EARFCN),11);
         break;
      case EUTRA_MODE_INFO_TDD:
         czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
         czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.tDD.eARFCN),22);
         break;
      default:
         czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
         czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.pres),PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_EARFCN),22);
         czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_EARFCN),11);
         break;
   }


   czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_Transmission_Bandwidth),
         CztTransmission_Bandwidthbw6Enum);
   czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_Transmission_Bandwidth),
         CztTransmission_Bandwidthbw100Enum);
#ifdef NOT_USED
   /* Removed in 8.5.0 */
   czAcUtlFillTknU32(&(ie1->servedCellInfo.subframeAssignment),
         CztSubframeAssignmentsa0Enum);
#endif /* NOT_USED*/

   ie1->servedCellInfo.iE_Extns.noComp.pres = NOTPRSNT;
   }
else
   {
      czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
      czAcUtlFillTknU32(&(ie->id), Cztid_GlobalENB_ID);
      czAcUtlFillTknU32(&(ie->criticality), 100);
   }

   *pdu = x2SetupRqstPdu;

   RETVALUE(ROK);
   
} /* End  of czAcUtlCztFillX2SetupReq */

/*
*
*       Fun:   czAcUtlCztFillX2SetupRsp
*
*       Desc:  Call handler to fill X2 Setup Response message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillX2SetupRsp
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt      **pdu
)
#else
PUBLIC S16 czAcUtlCztFillX2SetupRsp(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CztEvnt      **pdu;
#endif
{
   CztEvnt *x2SetupRespPdu=NULLP;
   U16     numComp;
   S16     ret;
   U8         tAC[10];
   U8      pLMNId[10];
   U8         choice;
   U8         cellId[28];
   U16        len;
   S16        idx;
   Mem  mem; 

   CztProtIE_Field_X2SetupResp_IEs *ie;
   CztSrvdCellsMember *ie1;
   Bool encodeFail = FALSE;

   mem.region = 0;
   mem.pool   = 0;
   TRC2(czAcUtlCztFillX2SetupRsp);  
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&x2SetupRespPdu);

   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(x2SetupRespPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(x2SetupRespPdu->pdu.choice), X2AP_PDU_SUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(x2SetupRespPdu->pdu.val.successfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(x2SetupRespPdu->pdu.val.successfulOutcome.procedureCode),Cztid_x2Setup);
   czAcUtlFillTknU32(&(x2SetupRespPdu->pdu.val.successfulOutcome.criticality),CztCriticalityignoreEnum);
   czAcUtlFillTknU8(&(x2SetupRespPdu->pdu.val.successfulOutcome.value.u.cztX2SetupResp.pres),PRSNT_NODEF);

   /* Filling 2 mandatory headers */

      numComp = 2;
      czAcUtlFillTknU16(&(x2SetupRespPdu->pdu.val.successfulOutcome.value.u.cztX2SetupResp.protocolIEs.noComp),numComp);

      /* Allocte memory for 2 IEs */
      if ((cmGetMem(x2SetupRespPdu, (numComp * sizeof(CztProtIE_Field_X2SetupResp_IEs)),
                  (Ptr*)&x2SetupRespPdu->pdu.val.successfulOutcome.value.u.cztX2SetupResp.protocolIEs.member)) !=ROK)
      {
         printf("cmGetMem failed, line %d\n", __LINE__); 
         RETVALUE(RFAILED);
      }

      ie = &x2SetupRespPdu->pdu.val.successfulOutcome.value.u.cztX2SetupResp.protocolIEs.member[0];
      /* IE1 - Filling ENB Global Id */
   if(encodeFail == FALSE)
   {
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_GlobalENB_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
      czAcUtlFillTknU8(&(ie->value.u.cztGlobalENB_ID.pres), PRSNT_NODEF);

      /* Fill the PLMN ID in target Cell Id */
      cmMemset(pLMNId, 0, sizeof(pLMNId));
      strcpy((char *)pLMNId, "111");
      len = 3;

      /* Fill the PLMN ID */
      czFillTknStrOSXL(&(ie->value.u.cztGlobalENB_ID.pLMN_Identity), 
            len, pLMNId, &x2SetupRespPdu);

      choice= ENB_ID_HOME_ENB_ID;

      switch (choice)
      {
         case ENB_ID_MACRO_ENB_ID:
            czAcUtlFillTknU8(&(ie->value.u.cztGlobalENB_ID.eNB_ID.choice), choice);
            czFillTknStr4(&(ie->value.u.cztGlobalENB_ID.eNB_ID.val.macro_eNB_ID),4,ENB_ID_MACRO_ENB_ID);
            break;
         case ENB_ID_HOME_ENB_ID:
            czAcUtlFillTknU8(&(ie->value.u.cztGlobalENB_ID.eNB_ID.choice), choice);

            cmMemset(cellId ,0, sizeof(cellId));
            for (idx = 0; idx < 28; idx++)
               cellId[idx] = 0xFF;
            len = 28;
            czFillTknBStr32(&(ie->value.u.cztGlobalENB_ID.eNB_ID.val.home_eNB_ID), len, 100);               

            /*
               czFillTknStr4(&(ie->value.u.cztGlobalENB_ID.eNB_ID.val.home_eNB_ID),4,ENB_ID_HOME_ENB_ID);
               */
            break;
         default:
            czAcUtlFillTknU8(&(ie->value.u.cztGlobalENB_ID.eNB_ID.choice), ENB_ID_HOME_ENB_ID);
            czFillTknStr4(&(ie->value.u.cztGlobalENB_ID.eNB_ID.val.macro_eNB_ID),4,ENB_ID_MACRO_ENB_ID);
            break;
      }

      ie->value.u.cztGlobalENB_ID.iE_Extns.noComp.pres = NOTPRSNT;

      ie = &x2SetupRespPdu->pdu.val.successfulOutcome.value.u.cztX2SetupResp.protocolIEs.member[1];
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_SrvdCells);
      czAcUtlFillTknU32(&(ie->criticality),CztCriticalityignoreEnum);

      numComp = 1;
      czAcUtlFillTknU16(&(ie->value.u.cztSrvdCells.noComp), numComp);
      if ((cmGetMem(x2SetupRespPdu,(numComp * sizeof(CztSrvdCellsMember)),
                  (Ptr *)&ie->value.u.cztSrvdCells.member)) !=ROK)
      {
         printf("cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }
      ie1 = &ie->value.u.cztSrvdCells.member[0];

      czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);
      czAcUtlFillTknU8(&(ie1->servedCellInfo.pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie1->servedCellInfo.pCI), 100);
      czAcUtlFillTknU8(&(ie1->servedCellInfo.cellId.pres), PRSNT_NODEF);
      /* Fill the PLMN ID in target Cell Id */
      cmMemset(pLMNId, 0, sizeof(pLMNId));
      strcpy((char *)pLMNId, "111");
      len = 3;

      /* Fill the PLMN ID */
      czFillTknStrOSXL(&(ie1->servedCellInfo.cellId.pLMN_Identity), 
            len, pLMNId, &x2SetupRespPdu);

      cmMemset(cellId ,0, sizeof(cellId));
      for (idx = 0; idx < 28; idx++)
         cellId[idx] = 0xFF;
      len = 28;
      czFillTknBStr32(&(ie1->servedCellInfo.cellId.eUTRANcellIdentifier), len, 100);


      /*
         czFillTknStrOSXL(&(ie1->servedCellInfo.cellId.pLMN_Identity),3, 'p', &x2SetupRespPdu);
         czAcUtlFillTknU32(&(ie1->servedCellInfo.cellId.eUTRANcellIdentifier),cellId);
         czFillTknStrOSXL(&(ie1->servedCellInfo.tAC), 2, 11, &x2SetupRespPdu);    
         */ 

      cmMemset(tAC, 0, sizeof(tAC));
      strcpy((char *)tAC, "11");
      len = 2;

      czFillTknStr4(&(ie1->servedCellInfo.tAC), (U8)len, 1); /* windows warning fixed by typecasting from U16 to U8 */

      /* IE3 - Filling broadcastPLMNs */
      numComp = 1;
      /* Allocate memory for broadcast PLMNs */
      if ((cmGetMem(x2SetupRespPdu, numComp*sizeof(CztPLMN_Identity),
                  (Ptr*)&ie1->servedCellInfo.broadcastPLMNs.member)) !=ROK)
      {
         printf("cmGetMem failed, line %d\n", __LINE__);
         RETVALUE(RFAILED);
      }
      czAcUtlFillTknU16(&(ie1->servedCellInfo.broadcastPLMNs.noComp),numComp);
      cmMemset(pLMNId, 0, sizeof(pLMNId));
      strcpy((char *)pLMNId, "111");
      len = 3;

      czFillTknStrOSXL(&(ie1->servedCellInfo.broadcastPLMNs.member[0]), len, pLMNId, &x2SetupRespPdu);

      /*
         czFillTknStrOSXL(&(ie1->servedCellInfo.broadcastPLMNs.member[0]), 3, 5, &x2SetupRespPdu);
         */

      choice= EUTRA_MODE_INFO_FDD;

      switch (choice)
      {
         case EUTRA_MODE_INFO_FDD:
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.pres),PRSNT_NODEF);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_EARFCN),22);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_EARFCN),11);
            break;
         case EUTRA_MODE_INFO_TDD:
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.tDD.eARFCN),22);
            break;
         default:
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.pres),PRSNT_NODEF);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_EARFCN),22);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_EARFCN),11);
            break;
      }


      czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_Transmission_Bandwidth),
            CztTransmission_Bandwidthbw6Enum);
      czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_Transmission_Bandwidth),
            CztTransmission_Bandwidthbw100Enum);
#ifdef NOT_USED
      /* Removed in 8.5.0 */
      czAcUtlFillTknU32(&(ie1->servedCellInfo.subframeAssignment),
            CztSubframeAssignmentsa0Enum);
#endif /* NOT_USED */

      ie1->servedCellInfo.iE_Extns.noComp.pres = NOTPRSNT;
   }
   else
   {
      czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
      czAcUtlFillTknU32(&(ie->id), Cztid_GlobalENB_ID);
      czAcUtlFillTknU32(&(ie->criticality), 100);
   }

   *pdu = x2SetupRespPdu;

   RETVALUE(ROK);
} /* End of czAcUtlCztFillX2SetupRsp */

/*
*
*       Fun:   czAcUtlCztFillX2SetupFail
*
*       Desc:  Call handler to fill X2 Setup Failure message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillX2SetupFail
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CztEvnt      **pdu
)
#else
PUBLIC S16 czAcUtlCztFillX2SetupFail(tcCb, spCb, pdu)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CztEvnt      **pdu;
#endif
{
   CztEvnt *x2SetupFailPdu=NULLP;
   U16     numComp;
   S16     ret;
   U8      choice;
   U32     cause;
   CztProtIE_Field_X2SetupFail_IEs *ie;
   Bool encodeFail = FALSE;
   Mem  mem;
   U8   timeToWait = 0, cnt = 0, critDiagPres = 0;
   mem.region = 0;
   mem.pool   = 0;
   TRC2(czAcUtlCztFillX2SetupFail);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&x2SetupFailPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(x2SetupFailPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(x2SetupFailPdu->pdu.choice), X2AP_PDU_UNSUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(x2SetupFailPdu->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(x2SetupFailPdu->pdu.val.unsuccessfulOutcome.procedureCode),Cztid_x2Setup);
   if(encodeFail == FALSE)
   {
      czAcUtlFillTknU32(&(x2SetupFailPdu->pdu.val.unsuccessfulOutcome.criticality),CztCriticalityignoreEnum);
   }
   else
   {
      czAcUtlFillTknU32(&(x2SetupFailPdu->pdu.val.unsuccessfulOutcome.criticality),5);
   }
   czAcUtlFillTknU8(&(x2SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztX2SetupFail.pres),PRSNT_NODEF);

   if(encodeFail == FALSE)
   {
      numComp = 1;
   }
   else
   {
      numComp = 0;
   }
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "timeToWait",
         &timeToWait);
   if(timeToWait)
      numComp++;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "critDiagPres",
         &critDiagPres);
   if(critDiagPres)
      numComp++;

   czAcUtlFillTknU16(&(x2SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztX2SetupFail.protocolIEs.noComp),numComp);

   if ((cmGetMem(x2SetupFailPdu, numComp*sizeof(CztProtIE_Field_X2SetupFail_IEs),
                 (Ptr*)&x2SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztX2SetupFail.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   if(encodeFail == FALSE)
   {
   /* IE1 - Filling cause */
   ie =
      &x2SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztX2SetupFail.protocolIEs.member[cnt];

   czAcUtlFillTknU8(&(ie->pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->id),Cztid_Cause);
   czAcUtlFillTknU32(&(ie->criticality),CztCriticalityignoreEnum);

   choice = CAUSE_RADIONW;
   cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
   czAcUtlFillTknU8(&(ie->value.u.cztCause.choice),choice);
   czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw),cause);

   cnt++;
   }

   if(timeToWait)
   {
     ie =
        &x2SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztX2SetupFail.protocolIEs.member[cnt];
     czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
     czAcUtlFillTknU32(&(ie->id), Cztid_TimeToWait);
     czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
     czAcUtlFillTknU32(&(ie->value.u.cztTimeToWait),timeToWait); 
     cnt++; 
   }
   if(critDiagPres)
   {
     ie =
        &x2SetupFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztX2SetupFail.protocolIEs.member[cnt];
     czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
     czAcUtlFillTknU32(&(ie->id), Cztid_CriticalityDiag);
     czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
     /* Fill According to need during testing */
     cnt++; 
   }

 

   *pdu = x2SetupFailPdu;

   RETVALUE(ROK);
} /* End of czAcUtlCztFillX2SetupFail */

/*
*
*       Fun:   czAcUtlCztFillUeCxtRls
*
*       Desc:  Call handler to fill UE context release
*              message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillUeCxtRls
(
CmXtaTCCb      *tcCb,
CmXtaSpCb      *spCb,
CztEvnt        **pdu
)
#else
PUBLIC S16 czAcUtlCztFillUeCxtRls(tcCb, spCb, pdu)
CmXtaTCCb      *tcCb;
CmXtaSpCb      *spCb;
CztEvnt        **pdu;
#endif
{
   CztEvnt *ueCntxtRlsPdu = NULLP;
   S16        numComp;
   S16        ret;
   U32        oldENBId = 100;
   U32        newENBId = 100;
   CztProtIE_Field_UECntxtRls_IEs *ie;

   Mem  mem; 
   Bool encodeFail = FALSE; 

   TRC2(encdecUECntxtRls);

   mem.region = 0;
   mem.pool   = 0;
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&ueCntxtRlsPdu);
   if(ret != ROK)
   {
      printf("encdecUECntxtRls: cmAllocEvnt failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(ueCntxtRlsPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(ueCntxtRlsPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(ueCntxtRlsPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ueCntxtRlsPdu->pdu.val.initiatingMsg.procedureCode), Cztid_uECntxtRls);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));
   
  if(encodeFail == FALSE)
   czAcUtlFillTknU32(&(ueCntxtRlsPdu->pdu.val.initiatingMsg.criticality), 
         CztCriticalityrejectEnum);
  else
   czAcUtlFillTknU32(&(ueCntxtRlsPdu->pdu.val.initiatingMsg.criticality), 
         10);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "oldUEX2APId", &oldENBId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "newUEX2APId", &newENBId);
   /* Fill the requested IEs */
   {
      numComp = 2;
      czAcUtlFillTknU8(&(ueCntxtRlsPdu->pdu.val.initiatingMsg.value.u.cztUECntxtRls.pres), 
            PRSNT_NODEF);
      czAcUtlFillTknU16(
        &(ueCntxtRlsPdu->pdu.val.initiatingMsg.value.u.cztUECntxtRls.protocolIEs.noComp),
        numComp);

      if ((cmGetMem(ueCntxtRlsPdu, (numComp * sizeof(CztProtIE_Field_UECntxtRls_IEs)), 
             (Ptr *)&ueCntxtRlsPdu->pdu.val.initiatingMsg.value.u.cztUECntxtRls.protocolIEs.member)) !=ROK)
      {
         printf("encdecUECntxtRls:: cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

      {
         /* Fill the Old EnB UE X2AP ID */
         ie = &ueCntxtRlsPdu->pdu.val.initiatingMsg.value.u.cztUECntxtRls.protocolIEs.member[0];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Old_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_Old), oldENBId); /* Fix for ccpu00117267 */


         /* Fill the New EnB UE X2AP ID */
         ie = &ueCntxtRlsPdu->pdu.val.initiatingMsg.value.u.cztUECntxtRls.protocolIEs.member[1];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_New_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_New), newENBId); /*Fix for ccpu00117267 */

      }
   }
  

   *pdu = ueCntxtRlsPdu; 

   RETVALUE(ROK);

} /* End of  czAcUtlCztFillUeCxtRls */

/*
*
*       Fun:   czAcUtlCztFillReset 
*
*       Desc:  Call handler to fill reset message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillReset
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillReset(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *czRstPdu=NULLP;
   S16  ret;
   U16  numComp;
    U8         choice;
   U32        cause;
   Mem  mem; 
   Bool encodeFail = FALSE;

   CztProtIE_Field_ResetRqst_IEs *ie;

   TRC2(encdecResetRqst);

   mem.region = 0;
   mem.pool   = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem,(Ptr *)&czRstPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(czRstPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(czRstPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(czRstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(czRstPdu->pdu.val.initiatingMsg.procedureCode),Cztid_reset);
   if(encodeFail == FALSE)
   {
      czAcUtlFillTknU32(&(czRstPdu->pdu.val.initiatingMsg.criticality),
            CztCriticalityignoreEnum);
   }
   else
   {
      czAcUtlFillTknU32(&(czRstPdu->pdu.val.initiatingMsg.criticality),
            10);
   }


   /* Filling 1 mandatory headers */
   czAcUtlFillTknU8(&(czRstPdu->pdu.val.initiatingMsg.value.u.cztResetRqst.pres),PRSNT_NODEF);

      numComp = 1;
      czAcUtlFillTknU16(&(czRstPdu->pdu.val.initiatingMsg.value.u.cztResetRqst.protocolIEs.noComp), numComp);

      if ((cmGetMem(czRstPdu, (numComp * sizeof(CztProtIE_Field_ResetRqst_IEs)), 
                  (Ptr *)&czRstPdu->pdu.val.initiatingMsg.value.u.cztResetRqst.
                  protocolIEs.member)) 
            !=ROK)
      {
         printf("encdecResetRqst:: cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

      ie = &czRstPdu->pdu.val.initiatingMsg.value.u.cztResetRqst.protocolIEs.member[0];

   if(encodeFail == FALSE)
   {
      /* Fill the Cause IE */
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
   }
   else
   {
      czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
   }
      czAcUtlFillTknU32(&(ie->id), Cztid_Cause);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
      choice = CAUSE_RADIONW;
      cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
      switch (choice)
      {
         case CAUSE_RADIONW:
            czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
            czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);
            break;
         case CAUSE_TRANSPORT:
            czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
            czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);
            break;
         case CAUSE_PROTOCOL:
            czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
            czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);
            break;
         case CAUSE_MISC:
            czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
            czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);
            break;
         default:
            czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), CAUSE_RADIONW);
            czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw),
                  CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum);
            break;
      }

   *pdu = czRstPdu; 

   RETVALUE(ROK);

} /* End of czAcUtlCztFillReset */

/*
*
*       Fun:   czAcUtlCztFillResetAck
*
*       Desc:  Call handler to fill reset Ack message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillResetAck
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillResetAck(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *czRstRspPdu=NULLP;
   U16     numComp;
   S16     ret;
   CztProtIE_Field_ResetResp_IEs *ie;
   Mem  mem; 
   Bool encodeFail = FALSE;

   mem.region = 0;
   mem.pool   = 0;
   TRC2(czAcUtlCztFillResetAck);
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&czRstRspPdu);

   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(czRstRspPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(czRstRspPdu->pdu.choice), X2AP_PDU_SUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(czRstRspPdu->pdu.val.successfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(czRstRspPdu->pdu.val.successfulOutcome.procedureCode),Cztid_reset);
   if(encodeFail==FALSE)
   {
      czAcUtlFillTknU32(&(czRstRspPdu->pdu.val.successfulOutcome.criticality),
            CztCriticalityignoreEnum);
   }
   else
   {
      czAcUtlFillTknU32(&(czRstRspPdu->pdu.val.successfulOutcome.criticality),
            8);
   }

      czAcUtlFillTknU8(&(czRstRspPdu->pdu.val.successfulOutcome.value.u.cztResetResp.pres), PRSNT_NODEF);
   if(encodeFail == FALSE)
   {
      numComp = 1;
      czAcUtlFillTknU16(&(czRstRspPdu->pdu.val.successfulOutcome.value.u.cztResetResp.protocolIEs.noComp), numComp);

      if ((cmGetMem(czRstRspPdu, (numComp * sizeof(CztProtIE_Field_ResetResp_IEs)), 
             (Ptr *)&czRstRspPdu->pdu.val.successfulOutcome.value.u.cztResetResp.protocolIEs.member)) !=ROK)
      {
         printf("encdecResetResp:: cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

         /* Fill the Diagonostic Value */
         ie = &czRstRspPdu->pdu.val.successfulOutcome.value.u.cztResetResp.protocolIEs.member[0];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_CriticalityDiag);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);

         czAcUtlFillTknU8(&(ie->value.u.cztCriticalityDiag.pres), NOTPRSNT);
      
   }
   else
   {
      czAcUtlFillTknU16(&(czRstRspPdu->pdu.val.successfulOutcome.value.u.cztResetResp.protocolIEs.noComp), 0);
   }
   

   *pdu = czRstRspPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillErrInd 
*
*       Desc:  Call handler to fill Error indication
*              message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillErrInd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillErrInd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *errIndPdu=NULLP;
   S16        numComp = 0;
   S16        ret, indx=0;
   U32        oldENBId = 0;
   U32        newENBId = 0;
   U8         causeType = CAUSE_RADIONW, causeVal= 0;
   U8         procCode, trigMsg, criticality;
   S8        msgType = -1;
   CztProtIE_Field_ErrInd_IEs *ie;
   Mem  mem; 

   TRC2(encdecErrInd);

   mem.region = 0;
   mem.pool   = 0;
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&errIndPdu);
   if(ret != ROK)
   {
      printf("encdecErrInd: cmAllocEvnt failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(errIndPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(errIndPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(errIndPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(errIndPdu->pdu.val.initiatingMsg.procedureCode), Cztid_errorInd);
   czAcUtlFillTknU32(&(errIndPdu->pdu.val.initiatingMsg.criticality), CztCriticalityignoreEnum);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "oldUEX2APId", &oldENBId);
   if(oldENBId)
      numComp++;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "newUEX2APId", &newENBId);
   if(newENBId)
      numComp++;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "causeVal", &causeVal);
   if(causeVal)
      numComp++;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "trigMsgType", &msgType);
   if(msgType >=CZT_MSG_HO_REQ)
      numComp++;

   czAcUtlFillTknU8(&(errIndPdu->pdu.val.initiatingMsg.value.u.cztErrInd.pres), PRSNT_NODEF);
   czAcUtlFillTknU16(&(errIndPdu->pdu.val.initiatingMsg.value.u.cztErrInd.protocolIEs.noComp), numComp);

   if ((cmGetMem(errIndPdu, (numComp * sizeof(CztProtIE_Field_ErrInd_IEs)), 
             (Ptr *)&errIndPdu->pdu.val.initiatingMsg.value.u.cztErrInd.protocolIEs.member)) !=ROK)
   {
      printf("encdecErrInd:: cmGetMem failed, line %d\n",__LINE__);
      CZ_FREEEVNT(errIndPdu);
      RETVALUE(RFAILED);
   }

   if(oldENBId)
   {
      ie = &errIndPdu->pdu.val.initiatingMsg.value.u.cztErrInd.protocolIEs.member[indx];

      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_Old_eNB_UE_X2AP_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_Old), oldENBId); /* Fix for ccpu00117267 */
      indx++;
   }
   if(newENBId)
   {
      ie = &errIndPdu->pdu.val.initiatingMsg.value.u.cztErrInd.protocolIEs.member[indx];

      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_New_eNB_UE_X2AP_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_New), newENBId); /* Fix for ccpu00117267 */
      indx++;
   }
   if(causeVal)
   {
      cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "causeType", &causeType);
      ie = &errIndPdu->pdu.val.initiatingMsg.value.u.cztErrInd.protocolIEs.member[indx];

      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_Cause);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
      czUtlFillCauseIe(&(ie->value.u.cztCause), causeType, causeVal);
      indx++;
   }
   if(msgType >=CZT_MSG_HO_REQ)
   {
      if(ROK == czAcUtlGetProcInfo(msgType, &procCode, &trigMsg, &criticality))
      {
         ie = &errIndPdu->pdu.val.initiatingMsg.value.u.cztErrInd.protocolIEs.member[indx];
      
         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_CriticalityDiag);
         czAcUtlFillTknU32(&(ie->criticality),CztCriticalityignoreEnum);
         czAcUtlFillTknU8(&(ie->value.u.cztCriticalityDiag.pres),PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.procedureCode),procCode);
         czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.triggeringMsg),trigMsg);
         czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.procedureCriticality),criticality);

        /* Well not filling IE Criticality Diag Info here; Let us check the scope of it */
      }
   }


   *pdu = errIndPdu; 

   RETVALUE(ROK);

} /* End of czAcUtlCztFillErrInd */

/*
*
*       Fun:   czAcUtlCztFillHovrRqst 
*
*       Desc:  Call handler to fill Handover Request message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillHovrRqst_R9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillHovrRqst_R9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *hovrRqstPdu=NULLP;
   S16        numComp;
   S16        ret;
   U32        oldENBId = 0;
   U8         choice;
   U32        cause;
   U8         bitrate[8];
   U8         gTPId[10];
   U8         tptAddr[10];
   U8         tprntCont[10];
   U8         eNBKeyVal[256]; 
   U16        len;
   S16        idx;
   U8         cellId[28];
   U8         pLMNId[10];
   U8         mmeGrpId[10];
   U8         rRCCntxt[8];
   CztProtIE_Field_HovrRqst_IEs *ie;
   CztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs *ie1;
   CztLastVisitedCell_Item       *ie2;
   Mem  mem; 
   U32     encryptionAlgorithms = 1; 
   U32     IPAlgorithms= 2; 

   /* CztProtIE_SingleCont_E_RABToBeSetupItemHOReqIEs *ie1; */

   TRC2(encdecHovrRqst);

   mem.region = 0;
   mem.pool   = 0;
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&hovrRqstPdu);
   if(ret != ROK)
   {
      printf("encdecHovrRqst: cmAllocEvnt failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   /*Fill the Old and new X2AP ID from test case */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "oldUEX2APId", &oldENBId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "EAValue", &encryptionAlgorithms);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "IAValue", &IPAlgorithms);

   cmMemset((U8 *)&(hovrRqstPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(hovrRqstPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(hovrRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(hovrRqstPdu->pdu.val.initiatingMsg.procedureCode), Cztid_handoverPrep);
   czAcUtlFillTknU32(&(hovrRqstPdu->pdu.val.initiatingMsg.criticality), 
         CztCriticalityrejectEnum);

   {
      numComp = 6;
      czAcUtlFillTknU8(&(hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.pres), 
            PRSNT_NODEF);
      czAcUtlFillTknU16(
            &(hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.protocolIEs.noComp), 
            numComp);

      if ((cmGetMem(hovrRqstPdu, (numComp * sizeof(CztProtIE_Field_HovrRqst_IEs)), 
                  (Ptr *)&hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.
                  protocolIEs.member)) 
            !=ROK)
      {
         printf("encdecHovrRqst:: cmGetMem failed, line %d\n",__LINE__);
         CZ_FREEEVNT(hovrRqstPdu);
         RETVALUE(RFAILED);
      }

      {


         /* Fill the OLD ENB UE X2AP ID */
         ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.protocolIEs.member[0];

         /* This is done intentionally to check at stack if this ID is not present */
         if(oldENBId)
         {
         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Old_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID), oldENBId);
         }

         /* Fill the Cause IE */
         ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.protocolIEs.member[1];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Cause);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
         switch (choice)
         {
            case CAUSE_RADIONW:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);
               break;
            case CAUSE_TRANSPORT:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.transport), cause);
               break;
            case CAUSE_PROTOCOL:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.protocol), cause);
               break;
            case CAUSE_MISC:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.misc), cause);
               break;
            default:
               /*  Existing */
              /* czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);*/
/* removed the #if 0 for chksrc tool error
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), CAUSE_RADIONW);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), 
               CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum);
*/
               break;
         }

         /* Fill the target Cell Id */
         ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.protocolIEs.member[2];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_TgetCell_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);

         czAcUtlFillTknU8(&(ie->value.u.cztECGI.pres), PRSNT_NODEF);

         /* Fill the PLMN ID in target Cell Id */
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;

         /* Fill the PLMN ID */
         czFillTknStrOSXL(&(ie->value.u.cztECGI.pLMN_Identity), 
               len, pLMNId, &hovrRqstPdu);

         cmMemset(cellId ,0, sizeof(cellId));
         for (idx = 0; idx < 28; idx++)
            cellId[idx] = 0xFF;
         len = 28;
         czFillTknBStr32(&(ie->value.u.cztECGI.eUTRANcellIdentifier), len, 100);

         /* 
            czFillTknStrOSXL(&(ie->value.u.cztECGI.eUTRANcellIdentifier), 
            len, cellId, &hovrRqstPdu);
          */

         /* 
           czAcUtlFillTknU32(&(ie->value.u.cztECGI.eUTRANcellIdentifier), 
           cellId);
          */

         /* Fill the target Cell Id */
         ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.protocolIEs.member[3];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_GUMMEI_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);

         czAcUtlFillTknU8(&(ie->value.u.cztGUMMEI.pres), PRSNT_NODEF);

         czAcUtlFillTknU8(&(ie->value.u.cztGUMMEI.gU_Group_ID.pres), PRSNT_NODEF);

         /* Fill the PLMN ID */
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;
         czFillTknStrOSXL(&(ie->value.u.cztGUMMEI.gU_Group_ID.pLMN_Identity), 
               len, pLMNId, &hovrRqstPdu);

         /* Fill the mmeGepId ID */
         cmMemset(mmeGrpId, 0, sizeof(mmeGrpId));
         strcpy((char *)mmeGrpId, "11");
         len = 2;

         czFillTknStr4(&(ie->value.u.cztGUMMEI.gU_Group_ID.mME_Group_ID), (U8)len, 1); /* windows warning fixed by typecasting from U16 to U8 */

         /*
            czFillTknStrOSXL(&(ie->value.u.cztGUMMEI.gU_Group_ID.mME_Group_ID), 
            len, mmeGrpId, &hovrRqstPdu);
          */

         /* Fill the mmeGepId ID */
         cmMemset(mmeGrpId, 0, sizeof(mmeGrpId));
         strcpy((char *)mmeGrpId, "1");
         len = 1;

         czFillTknStr4(&(ie->value.u.cztGUMMEI.mMME_Code), (U8)len, 1); /* windows warning fixed by typecasting from U16 to U8 */

         /* 
            czFillTknStrOSXL(&(ie->value.u.cztGUMMEI.mMME_Code), len, mmeGrpId, &hovrRqstPdu);
          */


         /* Fill the UE Context Information */
         ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.protocolIEs.member[4];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_UE_CntxtInform);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);

         czAcUtlFillTknU8(&(ie->value.u.cztUE_CntxtInform.pres), PRSNT_NODEF);
         /* Fill the rest of the Values in UE Context Information */
         czAcUtlFillTknU32(&(ie->value.u.cztUE_CntxtInform.mME_UE_S1AP_ID), 200);

         czAcUtlFillTknU8(&(ie->value.u.cztUE_CntxtInform.uESecurCapabilities.pres), 
               PRSNT_NODEF);  

         len = 16;
         czFillTknBStr32(&(ie->value.u.cztUE_CntxtInform.uESecurCapabilities.encryptionAlgorithms), len, encryptionAlgorithms);
         len = 16;
         czFillTknBStr32(&(ie->value.u.cztUE_CntxtInform.uESecurCapabilities.integrityProtectionAlgorithms), len, IPAlgorithms);

         ie->value.u.cztUE_CntxtInform.uESecurCapabilities.iE_Extns.noComp.pres = NOTPRSNT;

         /* AS Security Information */
         czAcUtlFillTknU8(&(ie->value.u.cztUE_CntxtInform.aS_SecurInform.pres), PRSNT_NODEF);

         cmMemset(eNBKeyVal,0,sizeof(eNBKeyVal));
         for (idx = 0; idx < 256; idx++)
            eNBKeyVal[idx] = 0xFF;
         len = 256;
         czFillTknStrOSXL(&(ie->value.u.cztUE_CntxtInform.aS_SecurInform.key_eNodeB_star), len, eNBKeyVal, &hovrRqstPdu);

         czAcUtlFillTknU32(&(ie->value.u.cztUE_CntxtInform.aS_SecurInform.nextHopChainingCount), 5);

#ifdef NOT_USED         
         len=3;
         czFillTknBStr32(&(ie->value.u.cztUE_CntxtInform.aS_SecurInform.nextHopChainingCount), len, 5);

         /* Removed in 8.5.0 */
         len=3;
         czFillTknBStr32(&(ie->value.u.cztUE_CntxtInform.aS_SecurInform.keySetIdentifier), len, 5);
#endif 

         ie->value.u.cztUE_CntxtInform.aS_SecurInform.iE_Extns.noComp.pres = NOTPRSNT;

         /* Max Bit Rate */
         czAcUtlFillTknU8(&(ie->value.u.cztUE_CntxtInform.uEaggregateMaxBitRate.pres), PRSNT_NODEF);
         cmMemset(bitrate, 0, sizeof(bitrate));
         strcpy((char *)bitrate, "11");
         len = 4;

         czFillTknStrOSXL(
         &(ie->value.u.cztUE_CntxtInform.uEaggregateMaxBitRate.uEaggregateMaxBitRateDlnk), 
         len, bitrate, &hovrRqstPdu);

         czFillTknStrOSXL(&(ie->value.u.cztUE_CntxtInform.uEaggregateMaxBitRate.uEaggregateMaxBitRateUlnk), len, bitrate, &hovrRqstPdu);


         ie->value.u.cztUE_CntxtInform.uEaggregateMaxBitRate.iE_Extns.noComp.pres = NOTPRSNT;

         /* RAB Setup list */
         numComp = 1;
         czAcUtlFillTknU16(&(ie->value.u.cztUE_CntxtInform.e_RABs_ToBeSetup_Lst.noComp), numComp);
         if ((cmGetMem(hovrRqstPdu, 
                     (numComp * sizeof(CztProtIE_Single_Cont_E_RABs_ToBeSetup_ItemIEs)), 
                     (Ptr *)&ie->value.u.cztUE_CntxtInform.e_RABs_ToBeSetup_Lst.member)) !=ROK)
         {
            printf("encdecHovrRqst:: cmGetMem failed, line %d\n",__LINE__);
            CZ_FREEEVNT(hovrRqstPdu);
            RETVALUE(RFAILED);
         }

         ie1 = &ie->value.u.cztUE_CntxtInform.e_RABs_ToBeSetup_Lst.member[0];

         czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->id), Cztid_E_RABs_ToBeSetup_Item);
         czAcUtlFillTknU32(&(ie1->criticality), CztCriticalityignoreEnum);
         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_ToBeSetup_Item.pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_ID), 15);


         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_Lvl_QoS_Params.pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_Lvl_QoS_Params.qCI), 15);

         czAcUtlFillTknU8(
         &(ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_Lvl_QoS_Params.allocationAndRetentionPriority.pres), PRSNT_NODEF);

         czAcUtlFillTknU32(&(ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_Lvl_QoS_Params.allocationAndRetentionPriority.priorityLvl), 15);

         czAcUtlFillTknU32(&(ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_Lvl_QoS_Params.allocationAndRetentionPriority.pre_emptionCapblty), 1);

         czAcUtlFillTknU32(&(ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_Lvl_QoS_Params.allocationAndRetentionPriority.pre_emptionVulnerability), 1);

         ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_Lvl_QoS_Params.allocationAndRetentionPriority.iE_Extns.noComp.pres = NOTPRSNT;

         ie1->value.u.cztE_RABs_ToBeSetup_Item.e_RAB_Lvl_QoS_Params.iE_Extns.noComp.pres = NOTPRSNT;

         /* Fill the ULink GTP Tunnel */
         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_ToBeSetup_Item.uL_GTPtunnelEndpoint.pres), 
               PRSNT_NODEF);
          cmMemset(tptAddr, 0, sizeof(tptAddr));
          strcpy((char *)tptAddr, "11");
         len = 2;
          czFillTknStrOSXL(
           &(ie1->value.u.cztE_RABs_ToBeSetup_Item.uL_GTPtunnelEndpoint.transportLyrAddr),
           len, tptAddr, &hovrRqstPdu);

          cmMemset(gTPId, 0, sizeof(gTPId));
         strcpy((char *)gTPId, "1111");
          len = 4;
         czFillTknStrOSXL(
               &(ie1->value.u.cztE_RABs_ToBeSetup_Item.uL_GTPtunnelEndpoint.gTP_TEID), 
                  len, gTPId, &hovrRqstPdu);

         ie1->value.u.cztE_RABs_ToBeSetup_Item.uL_GTPtunnelEndpoint.iE_Extns.noComp.pres = NOTPRSNT;

         ie1->value.u.cztE_RABs_ToBeSetup_Item.iE_Extns.noComp.pres = NOTPRSNT;


         /* Fill the RRC Context */
         cmMemset(rRCCntxt, 0, sizeof(rRCCntxt));
         strcpy((char *)rRCCntxt, "11");
         len = 2;

         czFillTknStrOSXL(
         &(ie->value.u.cztUE_CntxtInform.rRC_Cntxt), 
         len, rRCCntxt, &hovrRqstPdu);
         


         ie->value.u.cztUE_CntxtInform.iE_Extns.noComp.pres = NOTPRSNT;

         /* Fill the UE History Information */
         ie = &hovrRqstPdu->pdu.val.initiatingMsg.value.u.cztHovrRqst.protocolIEs.member[5];
         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_UE_HistoryInform);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);

         numComp = 1;
         czAcUtlFillTknU16(&(ie->value.u.cztUE_HistoryInform.noComp), numComp);
         if ((cmGetMem(hovrRqstPdu, 
                     (numComp * sizeof(CztLastVisitedCell_Item)), 
                     (Ptr *)&ie->value.u.cztUE_HistoryInform.member)) !=ROK)
         {
            printf("encdecHovrRqst:: cmGetMem failed, line %d\n",__LINE__);
            CZ_FREEEVNT(hovrRqstPdu);
            RETVALUE(RFAILED);
         }
         

         ie2 = &ie->value.u.cztUE_HistoryInform.member[0];

         choice = LASTVISITEDCELL_ITEM_UTRAN_CELL;
         czAcUtlFillTknU8(&(ie2->choice), choice);

         switch (choice)
         {
            case LASTVISITEDCELL_ITEM_E_UTRAN_CELL:
            case LASTVISITEDCELL_ITEM_GERAN_CELL:
               /* Add if required */
               break;

            case LASTVISITEDCELL_ITEM_UTRAN_CELL:
               cmMemset(tprntCont, 0, sizeof(tprntCont));
               strcpy((char *)tprntCont,"111");
               len = 3;
               czFillTknStrOSXL(&(ie2->val.uTRAN_Cell), len, 
                     tprntCont, &hovrRqstPdu);                  
               break;
            default:
               /* Add if required */
               break;
         }
               

#ifdef NOT_USED         
         cmMemset(tprntCont, 0, sizeof(tprntCont));
         strcpy((char *)tprntCont,"111");
         len = 3;
         czFillTknStrOSXL(&(ie->value.u.cztUE_HistoryInform), len, 
               tprntCont, &hovrRqstPdu);     
#endif /* NOT_USED */
      }
   }

   *pdu = hovrRqstPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillHovrRqstAck 
*
*       Desc:  Call handler to fill Handover Request Acknowledge message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillHovrRqstAck
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillHovrRqstAck(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
 
   CztEvnt *hovrRqstAckgPdu=NULLP;
   S16        numComp;
   S16        ret;
  
   U32        oENBUEX2apId = 100;
   U32        nENBUEX2apId = 0;
   U16        len;
   U8         tprntCont[10];
   CztProtIE_Field_HovrRqstAckg_IEs *ie;
   CztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs *ie1;
   Mem  mem; 

   TRC2(encdecHovrRqstAckg);

   mem.region = 0;
   mem.pool   = 0;
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&hovrRqstAckgPdu);
   if(ret != ROK)
   {
      printf("encdecHovrRqstAckg: cmAllocEvnt failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   /*Fill the Old and new X2AP ID from test case */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "oldUEX2APId", &oENBUEX2apId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "newUEX2APId", &nENBUEX2apId);
   cmMemset((U8 *)&(hovrRqstAckgPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(hovrRqstAckgPdu->pdu.choice), X2AP_PDU_SUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.procedureCode), Cztid_handoverPrep);
   czAcUtlFillTknU32(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.criticality), CztCriticalityrejectEnum);

   {
      numComp = 4;
      czAcUtlFillTknU8(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.cztHovrRqstAckg.pres), PRSNT_NODEF);
      czAcUtlFillTknU16(&(hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.cztHovrRqstAckg.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrRqstAckgPdu, (numComp * sizeof(CztProtIE_Field_HovrRqstAckg_IEs)), 
             (Ptr *)&hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.cztHovrRqstAckg.protocolIEs.member)) !=ROK)
      {
         printf("encdecHovrRqstAckg:: cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

      {
/*
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"usrConnId",&(suConnId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,"procId",&(procId));
         enbId = czacPduInfo[procId][suConnId].enbId;
         mmeId = czacPduInfo[procId][suConnId].mmeId;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"enbId",&(enbId));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"mmeId",&(mmeId));
*/

         /* Fill the Old ENB UE X2AP ID */
         ie = &hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.cztHovrRqstAckg.protocolIEs.member[0];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Old_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_Old), oENBUEX2apId); /* Fix for ccpu00117267 */

         /* Fill the New ENB UE X2AP ID */
         ie = &hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.cztHovrRqstAckg.protocolIEs.member[1];

         /* This is done intentionally to check at stack if this ID is not present */
         if(nENBUEX2apId)
         { 
         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_New_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_New), nENBUEX2apId); /* Fix for ccpu00117267 */
         } 

         /* Fill the E-RABs Admitted list */
         ie = &hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.cztHovrRqstAckg.protocolIEs.member[2];
         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_E_RABs_Admtd_Lst);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);

         numComp = 1;
         czAcUtlFillTknU16(&(ie->value.u.cztE_RABs_Admtd_Lst.noComp), numComp);

         if ((cmGetMem(hovrRqstAckgPdu, 
                     (numComp * sizeof(CztProtIE_Single_Cont_E_RABs_Admtd_ItemIEs)), 
                (Ptr *)&ie->value.u.cztE_RABs_Admtd_Lst.member)) !=ROK)
         {
            printf("encdecHovrRqstAckg:: cmGetMem failed, line %d\n",__LINE__);
            RETVALUE(RFAILED);
         }

         ie1 = &ie->value.u.cztE_RABs_Admtd_Lst.member[0];

         czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->id), Cztid_E_RABs_Admtd_Item);
         czAcUtlFillTknU32(&(ie1->criticality), CztCriticalityignoreEnum);
         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_Admtd_Item.pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->value.u.cztE_RABs_Admtd_Item.e_RAB_ID), 15);

#ifdef NOT_USED

         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_Admtd_Item.uL_GTP_TunnelEndpoint.pres), 
               PRSNT_NODEF);
          cmMemset(tptAddr, 0, sizeof(tptAddr));
          strcpy((char *)tptAddr, "11");
         len = 2;
          czFillTknStrOSXL(
           &(ie1->value.u.cztE_RABs_Admtd_Item.uL_GTP_TunnelEndpoint.transportLyrAddr),
           len, tptAddr, &hovrRqstAckgPdu);
          cmMemset(gTPId, 0, sizeof(gTPId));
         strcpy((char *)gTPId, "1111");
          len = 4;
         czFillTknStrOSXL(
               &(ie1->value.u.cztE_RABs_Admtd_Item.uL_GTP_TunnelEndpoint.gTP_TEID), 
                  len, gTPId, &hovrRqstAckgPdu);


         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_Admtd_Item.dL_GTP_TunnelEndpoint.pres), 
               PRSNT_NODEF);
          cmMemset(tptAddr, 0, sizeof(tptAddr));
          strcpy((char *)tptAddr, "11");
         len = 2;
          czFillTknStrOSXL(
           &(ie1->value.u.cztE_RABs_Admtd_Item.dL_GTP_TunnelEndpoint.transportLyrAddr),
           len, tptAddr, &hovrRqstAckgPdu);
          cmMemset(gTPId, 0, sizeof(gTPId));
         strcpy((char *)gTPId, "1111");
          len = 4;
         czFillTknStrOSXL(
               &(ie1->value.u.cztE_RABs_Admtd_Item.dL_GTP_TunnelEndpoint.gTP_TEID), 
                  len, gTPId, &hovrRqstAckgPdu);
#endif /* NOT_USED */

         ie1->value.u.cztE_RABs_Admtd_Item.iE_Extns.noComp.pres = NOTPRSNT;

         /* Fill target to Source Transparant container */
         ie = &hovrRqstAckgPdu->pdu.val.successfulOutcome.value.u.cztHovrRqstAckg.protocolIEs.member[3];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_TgeteNBtoSrc_eNBTprntCont);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
         cmMemset(tprntCont, 0, sizeof(tprntCont));
         strcpy((char *)tprntCont,"111");
         len = 3;
         czFillTknStrOSXL(&(ie->value.u.cztTgeteNBtoSrc_eNBTprntCont), len, tprntCont, &hovrRqstAckgPdu);     
      }
   }
 
   *pdu = hovrRqstAckgPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillHovrPrepFail 
*
*       Desc:  Call handler to fill Handover Failure message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillHovrPrepFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillHovrPrepFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   
   CztEvnt *hovrPrepFailPdu=NULLP;
   S16        numComp;
   S16        ret;
   U32        oENBUEX2apId = 100;
   U8         choice;
   U32        cause;
   CztProtIE_Field_HovrPrepFail_IEs *ie;
   Mem  mem; 

   TRC2(encdecHovrPrepFail);

   mem.region = 0;
   mem.pool   = 0;
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&hovrPrepFailPdu);
   if(ret != ROK)
   {
      printf("encdecHovrPrepFail: cmAllocEvnt failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrPrepFailPdu->pdu), 0, sizeof(CztX2AP_PDU));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "oldUEX2APId", &oENBUEX2apId);

   czAcUtlFillTknU8(&(hovrPrepFailPdu->pdu.choice), X2AP_PDU_UNSUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.procedureCode), 
         Cztid_handoverPrep);
   czAcUtlFillTknU32(&(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.criticality), 
         CztCriticalityrejectEnum);

   /* Fill the required IEs*/
   {
      numComp = 2;
      czAcUtlFillTknU8(
       &(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztHovrPrepFail.pres), 
       PRSNT_NODEF);
      
      czAcUtlFillTknU16(
      &(hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztHovrPrepFail.protocolIEs.noComp), numComp);

      if ((cmGetMem(hovrPrepFailPdu, (numComp * sizeof(CztProtIE_Field_HovrPrepFail_IEs)), 
          (Ptr *)&hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztHovrPrepFail.protocolIEs.member)) !=ROK)
      {
         printf("encdecHovrPrepFail:: cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

      {
         /* Fill Old EnB UE X2AP ID */
         ie = &hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztHovrPrepFail.protocolIEs.member[0];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Old_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID), oENBUEX2apId);

         ie = &hovrPrepFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztHovrPrepFail.protocolIEs.member[1];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Cause);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;

         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));

         switch (choice)
         {
            case CAUSE_RADIONW:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);
               break;
            case CAUSE_TRANSPORT:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.transport), cause);
               break;
            case CAUSE_PROTOCOL:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.protocol), cause);
               break;
            case CAUSE_MISC:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.misc), cause);
               break;
           default:
               /*  existing */
             /*  czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);*/
               break;
         }
      }
   }

   *pdu = hovrPrepFailPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillHovrCancel 
*
*       Desc:  Call handler to fill Handover Cancel message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillHovrCancel
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillHovrCancel(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *hovrCancelPdu=NULLP;
   S16        numComp;
   S16        ret;
   U32        oENBUEX2apId = 100;
   U32        nENBUEX2apId = 0xffff;
   U8         choice;
   U32        cause;
   Bool       newX2APIdPres = FALSE; 
   CztProtIE_Field_HovrCancel_IEs *ie;
   Mem  mem; 

   TRC2(encdecHovrCancel);

   mem.region = 0;
   mem.pool   = 0;
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&hovrCancelPdu);
   if(ret != ROK)
   {
      printf("encdecHovrCancel: cmAllocEvnt failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hovrCancelPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(hovrCancelPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(hovrCancelPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(hovrCancelPdu->pdu.val.initiatingMsg.procedureCode), 
         Cztid_handoverCancel);
   czAcUtlFillTknU32(&(hovrCancelPdu->pdu.val.initiatingMsg.criticality), 
         CztCriticalityrejectEnum);

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "oldUEX2APId", &oENBUEX2apId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "newUEX2APId", &nENBUEX2apId);
   if(nENBUEX2apId != 0xffff)
      newX2APIdPres = TRUE;
   /* Fill the required IEs */
   {
      if(newX2APIdPres)
         numComp = 3;
      else
         numComp = 2;
      czAcUtlFillTknU8(&(hovrCancelPdu->pdu.val.initiatingMsg.value.u.cztHovrCancel.pres), 
            PRSNT_NODEF);
      czAcUtlFillTknU16(
        &(hovrCancelPdu->pdu.val.initiatingMsg.value.u.cztHovrCancel.protocolIEs.noComp), 
        numComp);

      if ((cmGetMem(hovrCancelPdu, (numComp * sizeof(CztProtIE_Field_HovrCancel_IEs)), 
         (Ptr *)&hovrCancelPdu->pdu.val.initiatingMsg.value.u.cztHovrCancel.protocolIEs.member)) !=ROK)
      {
         printf("encdecHovrCancel:: cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

      {
         /* Fill the Old EnB UE X2AP Id */
         ie = &hovrCancelPdu->pdu.val.initiatingMsg.value.u.cztHovrCancel.protocolIEs.member[0];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Old_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_Old), oENBUEX2apId); /* Fix for ccpu00117267 */


         /* Fill the Cause Value */
         ie = &hovrCancelPdu->pdu.val.initiatingMsg.value.u.cztHovrCancel.protocolIEs.member[1];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Cause);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
         choice = CAUSE_RADIONW;
         cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,"choice", &(choice));
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32,"cause", &(cause));
         switch (choice)
         {
            case CAUSE_RADIONW:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause);
               break;
            case CAUSE_TRANSPORT:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.transport), cause);
               break;
            case CAUSE_PROTOCOL:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.protocol), cause);
               break;
            case CAUSE_MISC:
               czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.misc), cause);
               break;
           default:
               /*  existing */
              /* czAcUtlFillTknU8(&(ie->value.u.cztCause.choice), choice);
               czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw), cause); */
               break;
         }
         if(newX2APIdPres)
         {
            /* Fill the Old EnB UE X2AP Id */
            ie = &hovrCancelPdu->pdu.val.initiatingMsg.value.u.cztHovrCancel.protocolIEs.member[2];

            czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
            czAcUtlFillTknU32(&(ie->id), Cztid_New_eNB_UE_X2AP_ID);
            czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
            czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_Old), nENBUEX2apId); /* Fix for ccpu00117267 */
         }
      }
   }

   *pdu = hovrCancelPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillSnStatusTrfr 
*
*       Desc:  Call handler to fill SN Status Transfer message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillSnStatusTrfr
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillSnStatusTrfr(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *eNBStatusTfrPdu=NULLP;
    S16        numComp;
   S16        ret;
   U32        oENBUEX2apId = 100;
   U32        nENBUEX2apId = 100;
   CztProtIE_Field_SNStatusTfr_IEs *ie;
   CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs *ie1;
   Mem  mem; 
   Bool encodeFail = FALSE; 

   TRC2(encdecSNStatusTfr);

   mem.region = 0;
   mem.pool   = 0;
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&eNBStatusTfrPdu);
   if(ret != ROK)
   {
      printf("encdecSNStatusTfr: cmAllocEvnt failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(eNBStatusTfrPdu->pdu), 0, sizeof(CztX2AP_PDU));

   /*Fill the Old and new X2AP ID from test case */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "oldUEX2APId", &oENBUEX2apId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "newUEX2APId", &nENBUEX2apId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   czAcUtlFillTknU8(&(eNBStatusTfrPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.procedureCode), 
         Cztid_snStatusTfr);
   czAcUtlFillTknU32(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.criticality), 
         CztCriticalityignoreEnum);

   /* Fill the required IEs */
   {
      numComp = 3;
      czAcUtlFillTknU8(&(eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.cztSNStatusTfr.pres), 
            PRSNT_NODEF);
      czAcUtlFillTknU16(
       &(eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.cztSNStatusTfr.protocolIEs.noComp),
      numComp);

      if ((cmGetMem(eNBStatusTfrPdu, (numComp * sizeof(CztProtIE_Field_SNStatusTfr_IEs)), 
             (Ptr *)&eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.cztSNStatusTfr.protocolIEs.member)) !=ROK)
      {
         printf("encdecSNStatusTfr:: cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

      {

         /* Fill the Old EnB UE X2AP ID */
         ie = &eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.cztSNStatusTfr.protocolIEs.member[0];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Old_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_Old), oENBUEX2apId); /* Fix for ccpu00117267 */

         /* Fill the New EnB UE X2AP ID */
         ie = &eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.cztSNStatusTfr.protocolIEs.member[1];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_New_eNB_UE_X2AP_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztUE_X2AP_ID_New), nENBUEX2apId); /* Fix for ccpu00117267 */

         /* Fill the E-RABs list */
         ie = &eNBStatusTfrPdu->pdu.val.initiatingMsg.value.u.cztSNStatusTfr.protocolIEs.member[2];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_E_RABs_SubjToStatusTfr_Lst);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);

         numComp = 1;
         czAcUtlFillTknU16(
               &(ie->value.u.cztE_RABs_SubjToStatusTfr_Lst.noComp),
               numComp);

         if ((cmGetMem(eNBStatusTfrPdu, 
                     (numComp * sizeof(CztProtIE_Field_E_RABs_SubjToStatusTfr_ItemIEs)), 
                (Ptr *)&ie->value.u.cztE_RABs_SubjToStatusTfr_Lst.member)) !=ROK)
         {
            printf("encdecHovrRqstAckg:: cmGetMem failed, line %d\n",__LINE__);
            RETVALUE(RFAILED);
         }

         ie1 = &ie->value.u.cztE_RABs_SubjToStatusTfr_Lst.member[0];
         
         if(encodeFail == FALSE) 
         {
         czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->id), Cztid_E_RABs_SubjToStatusTfr_Item);
         czAcUtlFillTknU32(&(ie1->criticality), CztCriticalityignoreEnum);
         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.e_RAB_ID), 15);

         /* Fill the UL Count Value */
         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.uL_COUNTvalue.pres),
                  PRSNT_NODEF);
         czAcUtlFillTknU32(
           &(ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.uL_COUNTvalue.pDCP_SN), 5);
         czAcUtlFillTknU32(
           &(ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.uL_COUNTvalue.hFN), 5);
         ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.uL_COUNTvalue.iE_Extns.noComp.pres =
            NOTPRSNT;

         /* Fill the DL Count Value */
         czAcUtlFillTknU8(&(ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.dL_COUNTvalue.pres),
                  PRSNT_NODEF);
         czAcUtlFillTknU32(
           &(ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.dL_COUNTvalue.pDCP_SN), 5);
         czAcUtlFillTknU32(
           &(ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.dL_COUNTvalue.hFN), 5);
         ie1->value.u.cztE_RABs_SubjToStatusTfr_Item.dL_COUNTvalue.iE_Extns.noComp.pres =
            NOTPRSNT;
         }
      }
   } 
   *pdu = eNBStatusTfrPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillENBConfigUpd
*
*       Desc:  Call handler to fill ENB Configuration Update message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillENBConfigUpd
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillENBConfigUpd(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cztCfgUpdRqstPdu=NULLP;
   S16  ret;
   U16  numComp;
   U8         pLMNId[10];
   U8         cellId[28];
   U8         tAC[10];
   U16        len;
   S16        idx;
   U8 choice;
   CztProtIE_Field_ENBConfigUpd_IEs *ie=NULLP;
   Bool encodeFail = FALSE;

   CztSrvdCellsMember *ie1=NULLP;
   Mem  mem; 

   TRC2(encdecENBConfigUpd)

   mem.region = 0;
   mem.pool   = 0;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

      ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem,(Ptr *)&cztCfgUpdRqstPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cztCfgUpdRqstPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(cztCfgUpdRqstPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(cztCfgUpdRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(cztCfgUpdRqstPdu->pdu.val.initiatingMsg.procedureCode),Cztid_eNBConfigUpd);
   czAcUtlFillTknU32(&(cztCfgUpdRqstPdu->pdu.val.initiatingMsg.criticality),CztCriticalityignoreEnum);

   czAcUtlFillTknU8(&(cztCfgUpdRqstPdu->pdu.val.initiatingMsg.value.u.cztENBConfigUpd.pres),PRSNT_NODEF);

   if(encodeFail == FALSE)
   {
      /* Filling 1 option IE */

      numComp = 1;

      czAcUtlFillTknU16(&(cztCfgUpdRqstPdu->pdu.val.initiatingMsg.value.u.cztENBConfigUpd.protocolIEs.noComp), numComp);
      if ((cmGetMem(cztCfgUpdRqstPdu,(numComp * sizeof(CztProtIE_Field_ENBConfigUpd_IEs)),
                  (Ptr *)&cztCfgUpdRqstPdu->pdu.val.initiatingMsg.value.u.cztENBConfigUpd.protocolIEs.member)) !=ROK)
      {
         printf("cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

      ie=&cztCfgUpdRqstPdu->pdu.val.initiatingMsg.value.u.cztENBConfigUpd.
         protocolIEs.member[0];
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_SrvdCellsToAdd);
      czAcUtlFillTknU32(&(ie->criticality),CztCriticalityrejectEnum);

      czAcUtlFillTknU16(&(ie->value.u.cztSrvdCells.noComp),1);
      if ((cmGetMem(cztCfgUpdRqstPdu,(1 * sizeof(CztSrvdCellsMember)),
                  (Ptr *)&ie->value.u.cztSrvdCells.member)) !=ROK)
      {
         printf("cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }
      ie1 = &ie->value.u.cztSrvdCells.member[0];
      czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);
      czAcUtlFillTknU8(&(ie1->servedCellInfo.pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie1->servedCellInfo.pCI), 100);
      czAcUtlFillTknU8(&(ie1->servedCellInfo.cellId.pres), PRSNT_NODEF);
      /* Fill the PLMN ID in target Cell Id */

      cmMemset(pLMNId, 0, sizeof(pLMNId));
      strcpy((char *)pLMNId, "111");
      len = 3;

      czFillTknStrOSXL(&(ie1->servedCellInfo.cellId.pLMN_Identity), 
            len, pLMNId, &cztCfgUpdRqstPdu);
      cmMemset(cellId ,0, sizeof(cellId));
      for (idx = 0; idx < 28; idx++)
         cellId[idx] = 0xFF;
      len = 28;

      czFillTknBStr32(&(ie1->servedCellInfo.cellId.eUTRANcellIdentifier), len, 100);

      ie1->servedCellInfo.cellId.iE_Extns.noComp.pres=NOTPRSNT;

      /* Fill the mmeGepId ID */
      cmMemset(tAC, 0, sizeof(tAC));
      strcpy((char *)tAC, "11");
      len = 2;

      czFillTknStr4(&(ie1->servedCellInfo.tAC), (U8)len, 1); /* windows warning fixed by typecasting from U16 to U8 */

      /*            
                    czFillTknStrOSXL(&(ie1->servedCellInfo.cellId.pLMN_Identity),
                    3, 'p', &cztCfgUpdRqstPdu);
                    czAcUtlFillTknU32(&(ie1->servedCellInfo.cellId.eUTRANcellIdentifier),
                    cellId);
                    czFillTknStrOSXL(&(ie1->servedCellInfo.tAC), 2, 11, &cztCfgUpdRqstPdu);     
                    */

      /*Filling broadcastPLMNs */
      /* Allocate memory for broadcast PLMNs */
      numComp = 1;
      czAcUtlFillTknU16(&(ie1->servedCellInfo.broadcastPLMNs.noComp),numComp);

      if ((cmGetMem(cztCfgUpdRqstPdu, numComp*sizeof(CztPLMN_Identity),
                  (Ptr*)&ie1->servedCellInfo.broadcastPLMNs.member)) !=ROK)
      {
         printf("cmGetMem failed, line %d\n", __LINE__);
         RETVALUE(RFAILED);
      }
      cmMemset(pLMNId, 0, sizeof(pLMNId));
      strcpy((char *)pLMNId, "111");
      len = 3;

      czFillTknStrOSXL(&(ie1->servedCellInfo.broadcastPLMNs.member[0]), len, pLMNId, &cztCfgUpdRqstPdu);

      /*
         czFillTknStrOSXL(&(ie1->servedCellInfo.broadcastPLMNs.member[0]), 3, 5, &cztCfgUpdRqstPdu); 
         */

      choice= EUTRA_MODE_INFO_FDD;

      switch (choice)
      {
         case EUTRA_MODE_INFO_FDD:
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.pres),PRSNT_NODEF);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_EARFCN),22);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_EARFCN),11);
            break;
         case EUTRA_MODE_INFO_TDD:
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.tDD.pres),0);
            break;
         default:
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.choice), choice);
            czAcUtlFillTknU8(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.pres),PRSNT_NODEF);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_EARFCN),22);
            czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_EARFCN),11);
            break;
      }


      czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.uL_Transmission_Bandwidth),
            CztTransmission_Bandwidthbw6Enum);
      czAcUtlFillTknU32(&(ie1->servedCellInfo.eUTRA_Mode_Info.val.fDD.dL_Transmission_Bandwidth),
            CztTransmission_Bandwidthbw100Enum);
#ifdef NOT_USED
      /* Removed in 8.5.0 */
      czAcUtlFillTknU32(&(ie1->servedCellInfo.subframeAssignment),
            CztSubframeAssignmentsa0Enum);
#endif /* NOT_USED */
      ie1->servedCellInfo.iE_Extns.noComp.pres = NOTPRSNT;
   }
   else
   {
      czAcUtlFillTknU16(&(cztCfgUpdRqstPdu->pdu.val.initiatingMsg.value.u.cztENBConfigUpd.protocolIEs.noComp), 0);
   }
   *pdu = cztCfgUpdRqstPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillENBConfigUpdAckg
*
*       Desc:  Call handler to fill ENB Configuration Update Ackg message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillENBConfigUpdAckg
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillENBConfigUpdAckg(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cztCfgUpdAckPdu=NULLP;
     S16  ret;
   U16  numComp;
   CztProtIE_Field_ENBConfigUpdAckg_IEs *ie=NULLP;
   CztCriticalityDiag_IE_LstMember  *ie2=NULLP;
   Mem  mem; 
   Bool encodeFail = FALSE;

   TRC2(encdecENBConfigUpd);

   mem.region = 0;
   mem.pool   = 0;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem,(Ptr *)&cztCfgUpdAckPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cztCfgUpdAckPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(cztCfgUpdAckPdu->pdu.choice), X2AP_PDU_SUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(cztCfgUpdAckPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(cztCfgUpdAckPdu->pdu.val.successfulOutcome.procedureCode),Cztid_eNBConfigUpd);
   if(encodeFail == FALSE)
   {
      czAcUtlFillTknU32(&(cztCfgUpdAckPdu->pdu.val.successfulOutcome.criticality),
            CztCriticalityignoreEnum);
   }
   else
   {
      czAcUtlFillTknU32(&(cztCfgUpdAckPdu->pdu.val.successfulOutcome.criticality),
            8);
   }
   czAcUtlFillTknU8(&(cztCfgUpdAckPdu->pdu.val.successfulOutcome.value.u.cztENBConfigUpdAckg.pres),PRSNT_NODEF);

   /* Filling 1 option IE */

   numComp = 1;
   czAcUtlFillTknU16(&(cztCfgUpdAckPdu->pdu.val.successfulOutcome.value.u.cztENBConfigUpdAckg.protocolIEs.noComp), numComp);
   if ((cmGetMem(cztCfgUpdAckPdu,(numComp * sizeof(CztProtIE_Field_ENBConfigUpdAckg_IEs)),
               (Ptr *)&cztCfgUpdAckPdu->pdu.val.successfulOutcome.value.u.cztENBConfigUpdAckg.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   ie=&cztCfgUpdAckPdu->pdu.val.successfulOutcome.value.u.cztENBConfigUpdAckg.protocolIEs.member[0];
   czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->id), Cztid_CriticalityDiag);
   czAcUtlFillTknU32(&(ie->criticality),CztCriticalityrejectEnum);
   czAcUtlFillTknU8(&(ie->value.u.cztCriticalityDiag.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.procedureCode),Cztid_eNBConfigUpd);
   czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.triggeringMsg),CztTrgMsginitiating_messageEnum);


   /* Fill the Sub ie */
   czAcUtlFillTknU16(&(ie->value.u.cztCriticalityDiag.iEsCriticalityDiag.noComp), 1);
   if ((cmGetMem(cztCfgUpdAckPdu,(1* sizeof(CztCriticalityDiag_IE_LstMember)),
               (Ptr *)&ie->value.u.cztCriticalityDiag.iEsCriticalityDiag.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   ie2=&ie->value.u.cztCriticalityDiag.iEsCriticalityDiag.member[0];
   czAcUtlFillTknU8(&(ie2->pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie2->iECriticality),CztCriticalityrejectEnum);
   czAcUtlFillTknU32(&(ie2->iE_ID), Cztid_CriticalityDiag);
   czAcUtlFillTknU32(&(ie2->typeOfErr),CztTypOfErrnot_understoodEnum);
   ie2->iE_Extns.noComp.pres = NOTPRSNT;

   czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.procedureCriticality),CztCriticalityignoreEnum);

   ie->value.u.cztCriticalityDiag.iE_Extns.noComp.pres = NOTPRSNT;


   *pdu = cztCfgUpdAckPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillENBConfigUpdFail
*
*       Desc:  Call handler to fill ENB Configuration Fail message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillENBConfigUpdFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillENBConfigUpdFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cztCfgUpdFailPdu=NULLP;
    U16     numComp;
   S16     ret;
   U8      choice;
   U32     cause;
   CztProtIE_Field_ENBConfigUpdFail_IEs *ie;
   Mem  mem; 
   U8   timeToWait = 0, cnt = 0, critDiagPres = 0;

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillENBConfigUpdFail);
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&cztCfgUpdFailPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cztCfgUpdFailPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(cztCfgUpdFailPdu->pdu.choice), X2AP_PDU_UNSUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.procedureCode),Cztid_eNBConfigUpd);
   czAcUtlFillTknU32(&(cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.criticality),CztCriticalityignoreEnum);
   czAcUtlFillTknU8(&(cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztENBConfigUpdFail.pres),PRSNT_NODEF);

   numComp = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "timeToWait",
         &timeToWait);
   if(timeToWait)
      numComp++;
   
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "critDiagPres",
         &critDiagPres);
   if(critDiagPres)
      numComp++;
   czAcUtlFillTknU16(&(cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztENBConfigUpdFail.protocolIEs.noComp),numComp);

   if ((cmGetMem(cztCfgUpdFailPdu, numComp*sizeof(CztProtIE_Field_ENBConfigUpdFail_IEs),
                 (Ptr*)&cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztENBConfigUpdFail.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   /* IE1 - Filling cause */
   ie =
      &cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztENBConfigUpdFail.protocolIEs.member[cnt];

   czAcUtlFillTknU8(&(ie->pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->id),Cztid_Cause);
   czAcUtlFillTknU32(&(ie->criticality),CztCriticalityignoreEnum);

   choice = CAUSE_RADIONW;
   cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
   czAcUtlFillTknU8(&(ie->value.u.cztCause.choice),choice);
   czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw),cause);
   cnt++;

   if(timeToWait)
   {
     ie =
        &cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztENBConfigUpdFail.protocolIEs.member[cnt];
     czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
     czAcUtlFillTknU32(&(ie->id), Cztid_TimeToWait);
     czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
     czAcUtlFillTknU32(&(ie->value.u.cztTimeToWait),timeToWait); 
     cnt++; 
   }
   if(critDiagPres)
   {
     ie =
        &cztCfgUpdFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztENBConfigUpdFail.protocolIEs.member[cnt];
     czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
     czAcUtlFillTknU32(&(ie->id), Cztid_CriticalityDiag);
     czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
     /* Fill According to need during testing */
     cnt++; 
   }
   *pdu = cztCfgUpdFailPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillLoadInd
*
*       Desc:  Call handler to fill Load Indication message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillLoadInd_R9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillLoadInd_R9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *loadInformPdu=NULLP;
   S16        numComp;
   S16        ret;
   U8         pLMNId[10];
   U8         cellId[28]; 
   U16        len;
   S16        idx;
   CztProtIE_Field_LoadInform_IEs *ie;
   CztProtIE_Single_Cont_CellInform_ItemIEs *ie1;
   Mem  mem; 

   TRC2(encdecLoadInform);

   mem.region = 0;
   mem.pool   = 0;
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&loadInformPdu);
   if(ret != ROK)
   {
      printf("encdecLoadInform: cmAllocEvnt failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(loadInformPdu->pdu), 0, sizeof(CztX2AP_PDU));


   czAcUtlFillTknU8(&(loadInformPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(loadInformPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(loadInformPdu->pdu.val.initiatingMsg.procedureCode), Cztid_loadInd);
   czAcUtlFillTknU32(&(loadInformPdu->pdu.val.initiatingMsg.criticality), 
         CztCriticalityrejectEnum);

   /* Fill the requested IEs */
   {
      numComp = 1;
      czAcUtlFillTknU8(&(loadInformPdu->pdu.val.initiatingMsg.value.u.cztLoadInform.pres), 
            PRSNT_NODEF);
      czAcUtlFillTknU16(
        &(loadInformPdu->pdu.val.initiatingMsg.value.u.cztLoadInform.protocolIEs.noComp),
        numComp);

      if ((cmGetMem(loadInformPdu, (numComp * sizeof(CztProtIE_Field_LoadInform_IEs)), 
             (Ptr *)&loadInformPdu->pdu.val.initiatingMsg.value.u.cztLoadInform.protocolIEs.member)) !=ROK)
      {
         printf("encdecLoadInform:: cmGetMem failed, line %d\n",__LINE__);
         RETVALUE(RFAILED);
      }

      {
         /* Fill the Old EnB UE X2AP ID */
         ie = &loadInformPdu->pdu.val.initiatingMsg.value.u.cztLoadInform.protocolIEs.member[0];

         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_CellInform);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);

         numComp = 1;
         czAcUtlFillTknU16(&(ie->value.u.cztCellInform_Lst.noComp), numComp);

         if ((cmGetMem(loadInformPdu, 
                     (numComp * sizeof(CztProtIE_Single_Cont_CellInform_ItemIEs)), 
                (Ptr *)&ie->value.u.cztCellInform_Lst.member)) !=ROK)
         {
            printf("encdecLoadInform:: cmGetMem failed, line %d\n",__LINE__);
            RETVALUE(RFAILED);
         }

         ie1 = &ie->value.u.cztCellInform_Lst.member[0];

         czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie1->id), Cztid_CellInform_Item);
         czAcUtlFillTknU32(&(ie1->criticality), CztCriticalityignoreEnum);

         czAcUtlFillTknU8(&(ie1->value.u.cztCellInform_Item.pres), PRSNT_NODEF);

         czAcUtlFillTknU8(&(ie1->value.u.cztCellInform_Item.cell_ID.pres), PRSNT_NODEF);

         /* Fill the PLMN ID in target Cell Id */
         cmMemset(pLMNId, 0, sizeof(pLMNId));
         strcpy((char *)pLMNId, "111");
         len = 3;
         
         czFillTknStrOSXL(&(ie1->value.u.cztCellInform_Item.cell_ID.pLMN_Identity), 
                           len, pLMNId, &loadInformPdu);
         cmMemset(cellId ,0, sizeof(cellId));
         for (idx = 0; idx < 28; idx++)
            cellId[idx] = 0xFF;
         len = 28;
         
         czFillTknBStr32(&(ie1->value.u.cztCellInform_Item.cell_ID.eUTRANcellIdentifier), len, 100);
         /*
         czFillTknStrOSXL(&(ie1->value.u.cztCellInform_Item.cell_ID.eUTRANcellIdentifier), 
                             len, cellId, &loadInformPdu);
                             */

        ie1->value.u.cztCellInform_Item.cell_ID.iE_Extns.noComp.pres = NOTPRSNT; 

        ie1->value.u.cztCellInform_Item.relativeNarrowbandTxPower.pres.pres = NOTPRSNT; 

        ie1->value.u.cztCellInform_Item.iE_Extns.noComp.pres = NOTPRSNT; 

      }
   }

  *pdu = loadInformPdu;

   RETVALUE(ROK);
}
/*
*
*       Fun:   czAcUtlCztFillResStatusRqst
*
*       Desc:  Call handler to fill Resource Status Response message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillResStatusRqst_R9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillResStatusRqst_R9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cztResStatusRqstPdu=NULLP;
   S16  ret;
   U16  numComp = 0;
   U16  idx = 0;
   CztProtIE_Field_ResStatusRqst_IEs *ie=NULLP;
   CzAcCztRsrcInfo rsrcInfo = {0};
   Bool encodeFail = FALSE;
   Mem  mem; 

   TRC2(encdecResStatusRqst)

   mem.region = 0;
   mem.pool   = 0;
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem,(Ptr *)&cztResStatusRqstPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cztResStatusRqstPdu->pdu), 0, sizeof(CztX2AP_PDU));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   czAcUtlFillTknU8(&(cztResStatusRqstPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(cztResStatusRqstPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(cztResStatusRqstPdu->pdu.val.initiatingMsg.procedureCode),Cztid_resourceStatusRprtngInitiation);
   if(encodeFail == FALSE)
   {
      czAcUtlFillTknU32(&(cztResStatusRqstPdu->pdu.val.initiatingMsg.criticality),CztCriticalityignoreEnum);
   }
   else
   {
      czAcUtlFillTknU32(&(cztResStatusRqstPdu->pdu.val.initiatingMsg.criticality),5);
   }
   czAcUtlFillTknU8(&(cztResStatusRqstPdu->pdu.val.initiatingMsg.value.u.cztResStatusRqst.pres),PRSNT_NODEF);

   /* Filling 1 option IE */

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "regReqType", &rsrcInfo.regReq);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb1MeasId", &rsrcInfo.eNb1MeasId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb2MeasId", &rsrcInfo.eNb2MeasId);

      if (rsrcInfo.eNb1MeasId)
      {
         numComp++;
      }
      if (rsrcInfo.eNb2MeasId)
      {
         numComp++;
      }
      if (rsrcInfo.regReq)
      {
         numComp++;
      }
      czAcUtlFillTknU16(&(cztResStatusRqstPdu->pdu.val.initiatingMsg.value.u.cztResStatusRqst.protocolIEs.noComp), numComp);
            if ((cmGetMem(cztResStatusRqstPdu,(numComp * sizeof(CztProtIE_Field_ResStatusRqst_IEs)),
                (Ptr *)&cztResStatusRqstPdu->pdu.val.initiatingMsg.value.u.cztResStatusRqst.protocolIEs.member)) !=ROK)
            {
                  printf("cmGetMem failed, line %d\n",__LINE__);
                  RETVALUE(RFAILED);
            }

      if (rsrcInfo.eNb1MeasId)
      {
         ie=&cztResStatusRqstPdu->pdu.val.initiatingMsg.value.u.cztResStatusRqst.protocolIEs.member[idx];
         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Measurement_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztMeasurement_ID), rsrcInfo.eNb1MeasId); 
         idx++;
      }


      if (rsrcInfo.eNb2MeasId)
      {
         ie=&cztResStatusRqstPdu->pdu.val.initiatingMsg.value.u.cztResStatusRqst.protocolIEs.member[idx];
         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_ENB2_Measurement_ID);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
         czAcUtlFillTknU32(&(ie->value.u.cztMeasurement_ID), rsrcInfo.eNb2MeasId ); 
         idx++;
      }


      if (rsrcInfo.regReq)
      {
         ie=&cztResStatusRqstPdu->pdu.val.initiatingMsg.value.u.cztResStatusRqst.protocolIEs.member[idx];
         czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
         czAcUtlFillTknU32(&(ie->id), Cztid_Registration_Rqst);
         czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
         if (rsrcInfo.regReq == CZAC_START)
         {
            czAcUtlFillTknU32(&(ie->value.u.cztRegistration_Rqst), CztRegistration_RqststartEnum); /* START */
         }
         else
         {
            czAcUtlFillTknU32(&(ie->value.u.cztRegistration_Rqst), CztRegistration_RqststopEnum); /* STOP */
         }
      }

   *pdu = cztResStatusRqstPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztResStatusResp
*
*       Desc:  Call handler to fill Resource Status Response message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztResStatusResp_R9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztResStatusResp_R9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cztResStatusRespPdu=NULLP;
    S16  ret;
   U16  numComp = 1;
   CztProtIE_Field_ResStatusResp_IEs *ie=NULLP;
   CztCriticalityDiag_IE_LstMember  *ie2=NULLP;
   Mem  mem; 
   CzAcCztRsrcInfo rsrcInfo = {0};
   U16 idx = 0;
   Bool encodeFail = FALSE; 

   TRC2(encdecResStatusResp);

   mem.region = 0;
   mem.pool   = 0;
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem,(Ptr *)&cztResStatusRespPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cztResStatusRespPdu->pdu), 0, sizeof(CztX2AP_PDU));

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));
   
   czAcUtlFillTknU8(&(cztResStatusRespPdu->pdu.choice), X2AP_PDU_SUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(cztResStatusRespPdu->pdu.val.successfulOutcome.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(cztResStatusRespPdu->pdu.val.successfulOutcome.procedureCode),Cztid_resourceStatusRprtngInitiation);
   if(encodeFail == FALSE)
      czAcUtlFillTknU32(&(cztResStatusRespPdu->pdu.val.successfulOutcome.criticality),CztCriticalityignoreEnum);
   else
      czAcUtlFillTknU32(&(cztResStatusRespPdu->pdu.val.successfulOutcome.criticality),10);
   czAcUtlFillTknU8(&(cztResStatusRespPdu->pdu.val.successfulOutcome.value.u.cztResStatusResp.pres),PRSNT_NODEF);

   /* Filling 1 option IE */
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb1MeasId", &rsrcInfo.eNb1MeasId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb2MeasId", &rsrcInfo.eNb2MeasId);

   if (rsrcInfo.eNb1MeasId)
   {
      numComp++;
   }
   if (rsrcInfo.eNb2MeasId)
   {
      numComp++;
   }

   czAcUtlFillTknU16(&(cztResStatusRespPdu->pdu.val.successfulOutcome.value.u.cztResStatusResp.protocolIEs.noComp), numComp);
    if ((cmGetMem(cztResStatusRespPdu,(numComp * sizeof(CztProtIE_Field_ResStatusResp_IEs)),
                (Ptr *)&cztResStatusRespPdu->pdu.val.successfulOutcome.value.u.cztResStatusResp.protocolIEs.member)) !=ROK)
         {
            printf("cmGetMem failed, line %d\n",__LINE__);
            RETVALUE(RFAILED);
         }


   if (rsrcInfo.eNb1MeasId)
   {
      ie=&cztResStatusRespPdu->pdu.val.successfulOutcome.value.u.cztResStatusResp.protocolIEs.member[idx];
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Measurement_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztMeasurement_ID), rsrcInfo.eNb1MeasId); 
      idx++;
   }


   if (rsrcInfo.eNb2MeasId)
   {
      ie=&cztResStatusRespPdu->pdu.val.successfulOutcome.value.u.cztResStatusResp.protocolIEs.member[idx];
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_ENB2_Measurement_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztMeasurement_ID), rsrcInfo.eNb2MeasId ); 
      idx++;
   }

   ie=&cztResStatusRespPdu->pdu.val.successfulOutcome.value.u.cztResStatusResp.protocolIEs.member[idx];
   czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->id), Cztid_CriticalityDiag);
   czAcUtlFillTknU32(&(ie->criticality),CztCriticalityrejectEnum);
   czAcUtlFillTknU8(&(ie->value.u.cztCriticalityDiag.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.procedureCode),Cztid_resourceStatusRprtngInitiation);
   czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.triggeringMsg),CztTrgMsginitiating_messageEnum);


    /* Fill the Sub ie */
      czAcUtlFillTknU16(&(ie->value.u.cztCriticalityDiag.iEsCriticalityDiag.noComp), 1);
       if ((cmGetMem(cztResStatusRespPdu,(1* sizeof(CztCriticalityDiag_IE_LstMember)),
                (Ptr *)&ie->value.u.cztCriticalityDiag.iEsCriticalityDiag.member)) !=ROK)
         {
            printf("cmGetMem failed, line %d\n",__LINE__);
            RETVALUE(RFAILED);
         }
        ie2=&ie->value.u.cztCriticalityDiag.iEsCriticalityDiag.member[0];
      czAcUtlFillTknU8(&(ie2->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie2->iECriticality),CztCriticalityrejectEnum);
      czAcUtlFillTknU32(&(ie2->iE_ID), Cztid_CriticalityDiag);
      czAcUtlFillTknU32(&(ie2->typeOfErr),CztTypOfErrnot_understoodEnum);
        ie2->iE_Extns.noComp.pres = NOTPRSNT;
   
   czAcUtlFillTknU32(&(ie->value.u.cztCriticalityDiag.procedureCriticality),CztCriticalityignoreEnum);
     
   ie->value.u.cztCriticalityDiag.iE_Extns.noComp.pres = NOTPRSNT;

   *pdu = cztResStatusRespPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillResStatusFail
*
*       Desc:  Call handler to fill Resource Status Failure message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillResStatusFail_R9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillResStatusFail_R9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cztResStatusFailPdu=NULLP;
   U16     numComp;
   U16     compIdx = 0;
   S16     ret;
   U8      choice;
   U8     cause;
   Mem  mem; 
   CztProtIE_Field_ResStatusFail_IEs *ie;
   CzAcCztRsrcInfo rsrcInfo = {0};

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillResStatusFail_R9);
   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&cztResStatusFailPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cztResStatusFailPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(cztResStatusFailPdu->pdu.choice), X2AP_PDU_UNSUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.procedureCode),Cztid_resourceStatusRprtngInitiation);
   czAcUtlFillTknU32(&(cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.criticality),CztCriticalityignoreEnum);
   czAcUtlFillTknU8(&(cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztResStatusFail.pres),PRSNT_NODEF);

   numComp = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb1MeasId", &rsrcInfo.eNb1MeasId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb2MeasId", &rsrcInfo.eNb2MeasId);
   if (rsrcInfo.eNb1MeasId)
   {
      numComp++;
   }
   if (rsrcInfo.eNb2MeasId)
   {
      numComp++;
   }
   czAcUtlFillTknU16(&(cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztResStatusFail.protocolIEs.noComp),numComp);

   if ((cmGetMem(cztResStatusFailPdu, numComp*sizeof(CztProtIE_Field_ResStatusFail_IEs),
                 (Ptr*)&cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztResStatusFail.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   choice = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "causeType", &choice);
   cause = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "causeVal", &cause);

   if (rsrcInfo.eNb1MeasId)
   {
      ie=&cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztResStatusFail.protocolIEs.member[compIdx];
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Measurement_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztMeasurement_ID), rsrcInfo.eNb1MeasId); 
      compIdx++;
   }

   if (rsrcInfo.eNb2MeasId)
   {
      ie=&cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztResStatusFail.protocolIEs.member[compIdx];
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_ENB2_Measurement_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztMeasurement_ID), rsrcInfo.eNb2MeasId ); 
      compIdx++;
   }

   /* IE1 - Filling cause */
   ie = &cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztResStatusFail.protocolIEs.member[compIdx];

   czAcUtlFillTknU8(&(ie->pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->id),Cztid_Cause);
   czAcUtlFillTknU32(&(ie->criticality),CztCriticalityignoreEnum);
   czAcUtlFillTknU8(&(ie->value.u.cztCause.choice),choice);
   czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw),cause);

#ifdef NOT_USED
   /* IE2 - Filling TimeToWait */
   ie = &cztResStatusFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztResStatusFail.protocolIEs.member[1];
   czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->id), Cztid_TimeToWait);
   czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
   czFillTknStrOSXL(&(ie->value.u.cztTimeToWait), 2, 9, &cztResStatusFailPdu);
#endif 

   *pdu = cztResStatusFailPdu;

   RETVALUE(ROK);
}

/*
*
*       Fun:   czAcUtlCztFillResStatusUpd
*
*       Desc:  Call handler to fill Resource Status Update message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillResStatusUpd_R9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillResStatusUpd_R9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cztResStatusUpdPdu=NULLP;
   S16  ret;
   U16  numComp;
   U16  compIdx = 0;
   U8         pLMNId[10];   
   U8         cellId[28];
   U16        len;
   S16        idx;

   CztProtIE_Field_ResStatusUpd_IEs *ie=NULLP;
   CztProtIE_Single_Cont_CellMeasurementResult_ItemIEs *ie1=NULLP;
   Mem  mem; 
   CzAcCztRsrcInfo rsrcInfo = {0};

      TRC2(encdecResStatusRqst);

   mem.region = 0;
   mem.pool   = 0;
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem,(Ptr *)&cztResStatusUpdPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cztResStatusUpdPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(cztResStatusUpdPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(cztResStatusUpdPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(cztResStatusUpdPdu->pdu.val.initiatingMsg.procedureCode),Cztid_resourceStatusRprtng);
   czAcUtlFillTknU32(&(cztResStatusUpdPdu->pdu.val.initiatingMsg.criticality),CztCriticalityignoreEnum);
   czAcUtlFillTknU8(&(cztResStatusUpdPdu->pdu.val.initiatingMsg.value.u.cztResStatusUpd.pres),PRSNT_NODEF);

   /* Filling 1 option IE */

   numComp = 1;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb1MeasId", &rsrcInfo.eNb1MeasId);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "eNb2MeasId", &rsrcInfo.eNb2MeasId);

   if (rsrcInfo.eNb1MeasId)
   {
      numComp++;
   }
   if (rsrcInfo.eNb2MeasId)
   {
      numComp++;
   }

   czAcUtlFillTknU16(&(cztResStatusUpdPdu->pdu.val.initiatingMsg.value.u.cztResStatusUpd.protocolIEs.noComp), numComp);
   if ((cmGetMem(cztResStatusUpdPdu,(numComp * sizeof(CztProtIE_Field_ResStatusUpd_IEs)),
               (Ptr *)&cztResStatusUpdPdu->pdu.val.initiatingMsg.value.u.cztResStatusUpd.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   if (rsrcInfo.eNb1MeasId)
   {
      ie=&cztResStatusUpdPdu->pdu.val.initiatingMsg.value.u.cztResStatusUpd.protocolIEs.member[compIdx];
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Measurement_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztMeasurement_ID), rsrcInfo.eNb1MeasId); 
      compIdx++;
   }


   if (rsrcInfo.eNb2MeasId)
   {
      ie=&cztResStatusUpdPdu->pdu.val.initiatingMsg.value.u.cztResStatusUpd.protocolIEs.member[compIdx];
      czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
      czAcUtlFillTknU32(&(ie->id), Cztid_ENB2_Measurement_ID);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztMeasurement_ID), rsrcInfo.eNb2MeasId ); 
      compIdx++;
   }

   ie=&cztResStatusUpdPdu->pdu.val.initiatingMsg.value.u.cztResStatusUpd.protocolIEs.member[compIdx];
   czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie->id), Cztid_CellMeasurementResult);
   czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);

   czAcUtlFillTknU16(&(ie->value.u.cztCellMeasurementResult_Lst.noComp),1); 
   if ((cmGetMem(cztResStatusUpdPdu,(1 * sizeof(CztProtIE_Single_Cont_CellMeasurementResult_ItemIEs)),
               (Ptr *)&ie->value.u.cztCellMeasurementResult_Lst.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n",__LINE__);
      RETVALUE(RFAILED);
   }

   ie1= &ie->value.u.cztCellMeasurementResult_Lst.member[0];
   czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(ie1->id), Cztid_CellMeasurementResult_Item);
   czAcUtlFillTknU32(&(ie1->criticality), CztCriticalityignoreEnum);
   czAcUtlFillTknU8(&(ie1->value.u.cztCellMeasurementResult_Item.pres),PRSNT_NODEF);
   czAcUtlFillTknU8(&(ie1->value.u.cztCellMeasurementResult_Item.cell_ID.pres), PRSNT_NODEF);

   /* Fill the PLMN ID in target Cell Id */

   cmMemset(pLMNId, 0, sizeof(pLMNId));
   strcpy((char *)pLMNId, "111");
   len = 3;

   czFillTknStrOSXL(&(ie1->value.u.cztCellMeasurementResult_Item.cell_ID.pLMN_Identity), 
         len, pLMNId, &cztResStatusUpdPdu);
   cmMemset(cellId ,0, sizeof(cellId));
   for (idx = 0; idx < 28; idx++)
      cellId[idx] = 0xFF;
   len = 28;

   czFillTknBStr32(&(ie1->value.u.cztCellMeasurementResult_Item.cell_ID.eUTRANcellIdentifier), len, 100);

   ie1->value.u.cztCellMeasurementResult_Item.cell_ID.iE_Extns.noComp.pres=NOTPRSNT;   

   /*
   czAcUtlFillTknU32(&(ie1->value.u.cztCellMeasurementResult_Item.resoureStatus),1);
   */

   ie1->value.u.cztCellMeasurementResult_Item.iE_Extns.noComp.pres=NOTPRSNT;   

   *pdu = cztResStatusUpdPdu;

   RETVALUE(ROK);
}
#ifdef ANSI
PUBLIC U8 czAcUtlGetMsgType
(
CztX2AP_PDU   *pdu                    
)
#else
PUBLIC U8 czAcUtlGetMsgType(pdu)
CztX2AP_PDU   *pdu;                  
#endif
{
   S16 czMsgVal = CZT_MSG_UNKNOWN;
   S16 msgChoice = -1;
   U8  procCode;

   TRC2(czAcUtlGetMsgType)

   if(pdu == NULLP)
      RETVALUE(RFAILED);

   if(pdu->choice.pres == TRUE)
   {
      msgChoice  = pdu->choice.val;
   }
   switch(msgChoice)
   {
      case X2AP_PDU_INITIATINGMSG:
      {
         if(TRUE == pdu->val.initiatingMsg.pres.pres)
         {
            procCode = pdu->val.initiatingMsg.procedureCode.val;
            czMsgVal = czX2MsgMap[procCode][msgChoice];
         }
         break;
      }
      case X2AP_PDU_SUCCESSFULOUTCOME:
      {
         if(TRUE == pdu->val.successfulOutcome.pres.pres)
         {
            procCode = pdu->val.successfulOutcome.procedureCode.val;
            czMsgVal = czX2MsgMap[procCode][msgChoice];
         }
         break;
      }
      case X2AP_PDU_UNSUCCESSFULOUTCOME:
      {
         if(TRUE == pdu->val.unsuccessfulOutcome.pres.pres)
         {
            procCode = pdu->val.unsuccessfulOutcome.procedureCode.val;
            czMsgVal = czX2MsgMap[procCode][msgChoice];
         }
         break;
      }
      default:
         break;
   }

   RETVALUE((U8)czMsgVal); /* windows warning fixed by typecasting from U16 to U8 */

}



#ifdef ANSI
PUBLIC S16 czAcUtlCztFillMobChgReq
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillMobChgReq(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *mobChangeReqPdu=NULLP;
   U16      numComp;
   S16      ret;
   Mem  mem;
   CztProtIE_Field_MobilityChangeRqst_IEs *ie;
   Bool encodeFail = FALSE;
   U8 choice;
   U32 cause;
   U8 pLMNId1[10], pLMNId2[10];
   U16 len;
   U32  eUTRANcellId = 200;

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillMobChgReq);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

    /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&mobChangeReqPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(mobChangeReqPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(mobChangeReqPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(mobChangeReqPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(mobChangeReqPdu->pdu.val.initiatingMsg.procedureCode), Cztid_mobilitySettingsChange);
   czAcUtlFillTknU32(&(mobChangeReqPdu->pdu.val.initiatingMsg.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(mobChangeReqPdu->pdu.val.initiatingMsg.value.u.cztMobilityChangeRqst.pres), PRSNT_NODEF);

    numComp = 5;

   czAcUtlFillTknU16(&(mobChangeReqPdu->pdu.val.initiatingMsg.value.u.cztMobilityChangeRqst.protocolIEs.noComp), numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(mobChangeReqPdu, (numComp * sizeof(CztProtIE_Field_MobilityChangeRqst_IEs)),
               (Ptr*)&mobChangeReqPdu->pdu.val.initiatingMsg.value.u.cztMobilityChangeRqst.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   ie = &mobChangeReqPdu->pdu.val.initiatingMsg.value.u.cztMobilityChangeRqst.protocolIEs.member[0];

   if(encodeFail == FALSE)
   {

       /* IE1 - eNB1 Cell ID */
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Cell_ID);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czAcUtlFillTknU8(&(ie->value.u.czteNB1ECGI.pres), PRSNT_NODEF);

       /* Fill the PLMN ID in target Cell Id */
       cmMemset(pLMNId1, 0, sizeof(pLMNId1));
       strcpy((char *)pLMNId1, "111");
       len = 3;

       /* Fill the PLMN ID */
       czFillTknStrOSXL(&(ie->value.u.czteNB1ECGI.pLMN_Identity),
                len, pLMNId1, &mobChangeReqPdu);

       /* czAcUtlFillTknU32(&(ie->value.u.czteNB1ECGI.eUTRANcellIdentifier), eUTRANcellId ); */
       czFillTknBStr32(&(ie->value.u.czteNB1ECGI.eUTRANcellIdentifier), 28, eUTRANcellId );

       ie->value.u.czteNB1ECGI.iE_Extns.noComp.pres = NOTPRSNT;


       /* IE2 - eNB2 Cell ID */
       ie = &mobChangeReqPdu->pdu.val.initiatingMsg.value.u.cztMobilityChangeRqst.protocolIEs.member[1];

       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_ENB2_Cell_ID);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czAcUtlFillTknU8(&(ie->value.u.czteNB2ECGI.pres), PRSNT_NODEF);

       /* Fill the PLMN ID in target Cell Id */
       cmMemset(pLMNId2, 0, sizeof(pLMNId2));
       strcpy((char *)pLMNId2, "222");
       len = 3;

       /* Fill the PLMN ID */
       czFillTknStrOSXL(&(ie->value.u.czteNB2ECGI.pLMN_Identity),
               len, pLMNId2, &mobChangeReqPdu);

       czFillTknBStr32(&(ie->value.u.czteNB2ECGI.eUTRANcellIdentifier), 28, eUTRANcellId );

       ie->value.u.czteNB2ECGI.iE_Extns.noComp.pres = NOTPRSNT;


       ie = &mobChangeReqPdu->pdu.val.initiatingMsg.value.u.cztMobilityChangeRqst.protocolIEs.member[2];
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Mobility_Params);
       czAcUtlFillTknU32(&(ie->criticality),CztCriticalityignoreEnum);
       czAcUtlFillTknU8(&(ie->value.u.czteNB1MobilityParamsInform.pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->value.u.czteNB1MobilityParamsInform.handoverTriggerChange), 2);

        /* IE3 - eNB2 Proposed Mobility Param */
        ie = &mobChangeReqPdu->pdu.val.initiatingMsg.value.u.cztMobilityChangeRqst.protocolIEs.member[3];

        czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
        czAcUtlFillTknU32(&(ie->id), Cztid_ENB2_Proposed_Mobility_Params);
        czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
        czAcUtlFillTknU8(&(ie->value.u.czteNB2MobilityParamsInform.pres), PRSNT_NODEF);
        czAcUtlFillTknU32(&(ie->value.u.czteNB2MobilityParamsInform.handoverTriggerChange), 5);

        /* IE4 - Cause */
        ie = &mobChangeReqPdu->pdu.val.initiatingMsg.value.u.cztMobilityChangeRqst.protocolIEs.member[4];

        czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
        czAcUtlFillTknU32(&(ie->id), Cztid_Cause);
        czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
        choice = CAUSE_RADIONW;
        cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
        czAcUtlFillTknU8(&(ie->value.u.cztCause.choice),choice);
        czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw),cause);
     } /* end if encodeFail==FALSE */
     else
     {
        czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
        czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Cell_ID);
        czAcUtlFillTknU32(&(ie->criticality), 100);
     }

    *pdu = mobChangeReqPdu;

    RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 czAcUtlCztFillMobChgAck
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillMobChgAck(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *mobChangeAckPdu=NULLP;
   U16      numComp;
   S16      ret;
   Mem  mem;
   CztProtIE_Field_MobilityChangeAckg_IEs *ie; 
   Bool encodeFail = FALSE;
   U8 criticalityDiag = 0;
   U8 pLMNId1[10], pLMNId2[10];
   U16        len;
   U32  eUTRANcellId = 200;

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillMobChgAck);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

    /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&mobChangeAckPdu);
  if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(mobChangeAckPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(mobChangeAckPdu->pdu.choice), X2AP_PDU_SUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(mobChangeAckPdu->pdu.val.successfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(mobChangeAckPdu->pdu.val.successfulOutcome.procedureCode), Cztid_mobilitySettingsChange);
   czAcUtlFillTknU32(&(mobChangeAckPdu->pdu.val.successfulOutcome.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(mobChangeAckPdu->pdu.val.successfulOutcome.value.u.cztMobilityChangeAckg.pres), PRSNT_NODEF);

   /* Filling 2 mandatory IEs */
   numComp = 2;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "criticalityDiag",
         &criticalityDiag);
   if(criticalityDiag)
      numComp++;

   czAcUtlFillTknU16(&(mobChangeAckPdu->pdu.val.successfulOutcome.value.u.cztMobilityChangeAckg.protocolIEs.noComp), numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(mobChangeAckPdu, (numComp * sizeof(CztProtIE_Field_MobilityChangeAckg_IEs)),
               (Ptr*)&mobChangeAckPdu->pdu.val.successfulOutcome.value.u.cztMobilityChangeAckg.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   ie = &mobChangeAckPdu->pdu.val.successfulOutcome.value.u.cztMobilityChangeAckg.protocolIEs.member[0];

   if(encodeFail == FALSE)
   {

       /* IE1 - eNB1 Cell ID */
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Cell_ID);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czAcUtlFillTknU8(&(ie->value.u.czteNB1ECGI.pres), PRSNT_NODEF);

       /* Fill the PLMN ID in target Cell Id */
       cmMemset(pLMNId1, 0, sizeof(pLMNId1));
       strcpy((char *)pLMNId1, "111");
       len = 3;

       /* Fill the PLMN ID */
       czFillTknStrOSXL(&(ie->value.u.czteNB1ECGI.pLMN_Identity),
                len, pLMNId1, &mobChangeAckPdu);

       czFillTknBStr32(&(ie->value.u.czteNB1ECGI.eUTRANcellIdentifier), 28, eUTRANcellId );

       ie->value.u.czteNB1ECGI.iE_Extns.noComp.pres = NOTPRSNT;


       /* IE2 - eNB2 Cell ID */
       ie = &mobChangeAckPdu->pdu.val.successfulOutcome.value.u.cztMobilityChangeAckg.protocolIEs.member[1];

       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_ENB2_Cell_ID);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czAcUtlFillTknU8(&(ie->value.u.czteNB2ECGI.pres), PRSNT_NODEF);

       /* Fill the PLMN ID in target Cell Id */
       cmMemset(pLMNId2, 0, sizeof(pLMNId2));
       strcpy((char *)pLMNId2, "222");
       len = 3;

       /* Fill the PLMN ID */
       czFillTknStrOSXL(&(ie->value.u.czteNB2ECGI.pLMN_Identity),
               len, pLMNId2, &mobChangeAckPdu);

       czFillTknBStr32(&(ie->value.u.czteNB2ECGI.eUTRANcellIdentifier), 28, eUTRANcellId );

       ie->value.u.czteNB2ECGI.iE_Extns.noComp.pres = NOTPRSNT;
 
    }/*end if encodeFail == FALSE */
    else
    {
        czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
        czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Cell_ID);
        czAcUtlFillTknU32(&(ie->criticality), 100);
    }

   *pdu = mobChangeAckPdu;

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 czAcUtlCztFillMobChgFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillMobChgFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *mobChangeFailPdu=NULLP;
   U16 numComp;
   S16 ret;
   Mem mem;
   CztProtIE_Field_MobilityChangeFail_IEs *ie; 
   Bool encodeFail = FALSE;
   U8  choice;
   U32 cause;
   U8 eNB1MobilityParamModRange = 0, criticalityDiag = 0;
   U8 pLMNId1[10], pLMNId2[10];
   U16 len;
   U32 eUTRANcellId = 200;

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillMobChgFail);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

    /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&mobChangeFailPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(mobChangeFailPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(mobChangeFailPdu->pdu.choice), X2AP_PDU_UNSUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(mobChangeFailPdu->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(mobChangeFailPdu->pdu.val.unsuccessfulOutcome.procedureCode), Cztid_mobilitySettingsChange);
   czAcUtlFillTknU32(&(mobChangeFailPdu->pdu.val.unsuccessfulOutcome.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(mobChangeFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztMobilityChangeFail.pres), PRSNT_NODEF);

    /* Filling 3 mandatory IEs */
   numComp = 3;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "eNB2MobilityParamModRange",
         &eNB1MobilityParamModRange);
   if(eNB1MobilityParamModRange)
      numComp++;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "criticalityDiag",
         &criticalityDiag);
   if(criticalityDiag)
      numComp++;

   czAcUtlFillTknU16(&(mobChangeFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztMobilityChangeFail.protocolIEs.noComp), numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(mobChangeFailPdu, (numComp * sizeof(CztProtIE_Field_MobilityChangeFail_IEs)),
               (Ptr*)&mobChangeFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztMobilityChangeFail.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   ie = &mobChangeFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztMobilityChangeFail.protocolIEs.member[0];

   if(encodeFail == FALSE)
   {
       /* IE1 - eNB1 Cell ID */
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Cell_ID);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czAcUtlFillTknU8(&(ie->value.u.czteNB1ECGI.pres), PRSNT_NODEF);

       /* Fill the PLMN ID in target Cell Id */
       cmMemset(pLMNId1, 0, sizeof(pLMNId1));
       strcpy((char *)pLMNId1, "111");
       len = 3;

       /* Fill the PLMN ID */
       czFillTknStrOSXL(&(ie->value.u.czteNB1ECGI.pLMN_Identity),
                len, pLMNId1, &mobChangeFailPdu);

       czFillTknBStr32(&(ie->value.u.czteNB1ECGI.eUTRANcellIdentifier), 28, eUTRANcellId );

       ie->value.u.czteNB1ECGI.iE_Extns.noComp.pres = NOTPRSNT;

       /* IE2 - eNB2 Cell ID */
       ie = &mobChangeFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztMobilityChangeFail.protocolIEs.member[1];

       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_ENB2_Cell_ID);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czAcUtlFillTknU8(&(ie->value.u.czteNB2ECGI.pres), PRSNT_NODEF);

       /* Fill the PLMN ID in target Cell Id */
       cmMemset(pLMNId2, 0, sizeof(pLMNId2));
       strcpy((char *)pLMNId2, "222");
       len = 3;

       /* Fill the PLMN ID */
       czFillTknStrOSXL(&(ie->value.u.czteNB2ECGI.pLMN_Identity),
                len, pLMNId2, &mobChangeFailPdu);

       czFillTknBStr32(&(ie->value.u.czteNB2ECGI.eUTRANcellIdentifier), 28, eUTRANcellId );

       ie->value.u.czteNB2ECGI.iE_Extns.noComp.pres = NOTPRSNT;

       /* IE3 - Cause */
       ie = &mobChangeFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztMobilityChangeFail.protocolIEs.member[2];

       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_Cause);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       choice = CAUSE_RADIONW;
       cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
       czAcUtlFillTknU8(&(ie->value.u.cztCause.choice),choice);
       czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw),cause);

   } /* end if encodeFail == FALSE */
   else
   {
      czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
      czAcUtlFillTknU32(&(ie->id), Cztid_ENB1_Cell_ID);
      czAcUtlFillTknU32(&(ie->criticality), 100);
   }

  *pdu = mobChangeFailPdu;

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 czAcUtlCztFillRlfInd_R9
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillRlfInd_R9(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *rlfIndPdu=NULLP;
   U16 numComp;
   S16 ret;
   Mem mem;
   CztProtIE_Field_RLFInd_IEs *ie; 
   Bool encodeFail = FALSE;
   U32 cztCRnti = 1;
   U32 cztPci = 2;
   U8 shortMAC = 0, ueRlfReportContainer = 0;
   U8 pLMNId1[10];
   U16 len;
   U32 eUTRANcellId = 200;

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillRlfInd_R9);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&rlfIndPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(rlfIndPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(rlfIndPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(rlfIndPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(rlfIndPdu->pdu.val.initiatingMsg.procedureCode), Cztid_rLFInd);
   czAcUtlFillTknU32(&(rlfIndPdu->pdu.val.initiatingMsg.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(rlfIndPdu->pdu.val.initiatingMsg.value.u.cztRLFInd.pres), PRSNT_NODEF);

   /* Filling 3 mandatory IEs */
   numComp = 3;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "shortMAC",
         &shortMAC);
   if(shortMAC)
      numComp++;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "ueRlfReportContainer",
         &ueRlfReportContainer);
   if(ueRlfReportContainer)
      numComp++;

   czAcUtlFillTknU16(&(rlfIndPdu->pdu.val.initiatingMsg.value.u.cztRLFInd.protocolIEs.noComp), numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(rlfIndPdu, (numComp * sizeof(CztProtIE_Field_RLFInd_IEs)),
               (Ptr*)&rlfIndPdu->pdu.val.initiatingMsg.value.u.cztRLFInd.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   ie = &rlfIndPdu->pdu.val.initiatingMsg.value.u.cztRLFInd.protocolIEs.member[0];

   if(encodeFail == FALSE)
   {

       /* IE1 - Failure Cell PCI */
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_FailCellPCI);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czAcUtlFillTknU32(&(ie->value.u.cztPCI), cztPci);

       ie = &rlfIndPdu->pdu.val.initiatingMsg.value.u.cztRLFInd.protocolIEs.member[1];
       /* IE2 - Re-establishment cell ECGI */
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_Re_establishmentCellECGI);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czAcUtlFillTknU8(&(ie->value.u.cztECGI.pres), PRSNT_NODEF);

       /* Fill the PLMN ID in target Cell Id */
       cmMemset(pLMNId1, 0, sizeof(pLMNId1));
       strcpy((char *)pLMNId1, "111");
       len = 3;

       /* Fill the PLMN ID */
       czFillTknStrOSXL(&(ie->value.u.cztECGI.pLMN_Identity),
               len, pLMNId1, &rlfIndPdu);

       czFillTknBStr32(&(ie->value.u.cztECGI.eUTRANcellIdentifier), 28, eUTRANcellId );
       ie->value.u.cztECGI.iE_Extns.noComp.pres = NOTPRSNT;


       ie = &rlfIndPdu->pdu.val.initiatingMsg.value.u.cztRLFInd.protocolIEs.member[2];
       /* IE3 - C-RNTI */
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_FailCellCRNTI);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
       czFillTknBStr32(&(ie->value.u.cztCRNTI), 16, cztCRnti );

   } /* end if encodeFail == FALSE */
   else
   {
      czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
      czAcUtlFillTknU32(&(ie->id), Cztid_FailCellPCI);
      czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
      czAcUtlFillTknU32(&(ie->value.u.cztPCI), 100);
   }

  *pdu = rlfIndPdu;

   RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 czAcUtlCztFillHOReport
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillHOReport(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *hoReportPdu=NULLP;
   U16 numComp;
   S16 ret;
   Mem  mem;
   U8 choice;
   U32 cause;
   CztProtIE_Field_HovrReport_IEs *ie; 
   Bool encodeFail = FALSE;
   U32 cztHoReportType = 1;
   U8 pLMNId1[10], pLMNId2[10], pLMNId3[10];
   U16 len;
   U32 eUTRANcellId = 2;

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillHoReport);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

    /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&hoReportPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(hoReportPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(hoReportPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(hoReportPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(hoReportPdu->pdu.val.initiatingMsg.procedureCode), Cztid_handoverReport);
   czAcUtlFillTknU32(&(hoReportPdu->pdu.val.initiatingMsg.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(hoReportPdu->pdu.val.initiatingMsg.value.u.cztHovrReport.pres), PRSNT_NODEF);

   numComp = 5;

   czAcUtlFillTknU16(&(hoReportPdu->pdu.val.initiatingMsg.value.u.cztHovrReport.protocolIEs.noComp), numComp);
   /* Get memory for numComp IEs */
   if ((cmGetMem(hoReportPdu, (numComp * sizeof(CztProtIE_Field_HovrReport_IEs)),
               (Ptr*)&hoReportPdu->pdu.val.initiatingMsg.value.u.cztHovrReport.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

    ie = &hoReportPdu->pdu.val.initiatingMsg.value.u.cztHovrReport.protocolIEs.member[0];
    
   if(encodeFail == FALSE)
   {

        /* IE1 - Handover Report Type */
        czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
        czAcUtlFillTknU32(&(ie->id), Cztid_HovrReportTyp);
        czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
        czAcUtlFillTknU32(&(ie->value.u.cztHovrReportTyp), cztHoReportType);

        ie = &hoReportPdu->pdu.val.initiatingMsg.value.u.cztHovrReport.protocolIEs.member[1];
        /* IE2 - Handover Cause */
        czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
        czAcUtlFillTknU32(&(ie->id), Cztid_Cause );
        czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
        choice = CAUSE_RADIONW;
        cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
        czAcUtlFillTknU8(&(ie->value.u.cztCause.choice),choice);
        czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw),cause);
 
        ie = &hoReportPdu->pdu.val.initiatingMsg.value.u.cztHovrReport.protocolIEs.member[2];
        /* IE3 - Source Cell ECGI */
        czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
        czAcUtlFillTknU32(&(ie->id), Cztid_SrcCellECGI);
        czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
        czAcUtlFillTknU8(&(ie->value.u.cztSrcCellECGI.pres), PRSNT_NODEF);

        /* Fill the PLMN ID in target Cell Id */
        cmMemset(pLMNId1, 0, sizeof(pLMNId1));
        strcpy((char *)pLMNId1, "111");
        len = 3;

        /* Fill the PLMN ID */
        czFillTknStrOSXL(&(ie->value.u.cztSrcCellECGI.pLMN_Identity),
                len, pLMNId1, &hoReportPdu);

        czFillTknBStr32(&(ie->value.u.cztSrcCellECGI.eUTRANcellIdentifier), 28, eUTRANcellId );
        ie->value.u.cztSrcCellECGI.iE_Extns.noComp.pres = NOTPRSNT;

        ie = &hoReportPdu->pdu.val.initiatingMsg.value.u.cztHovrReport.protocolIEs.member[3];
        /* IE4 - Failure Cell ECGI */
        czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
        czAcUtlFillTknU32(&(ie->id), Cztid_FailCellECGI);
        czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
        czAcUtlFillTknU8(&(ie->value.u.cztFailCellECGI.pres), PRSNT_NODEF);

        /* Fill the PLMN ID in target Cell Id */
        cmMemset(pLMNId2, 0, sizeof(pLMNId2));
        strcpy((char *)pLMNId2, "222");
        len = 3;
 
        /* Fill the PLMN ID */
        czFillTknStrOSXL(&(ie->value.u.cztFailCellECGI.pLMN_Identity),
                len, pLMNId2, &hoReportPdu);

        czFillTknBStr32(&(ie->value.u.cztFailCellECGI.eUTRANcellIdentifier), 28, eUTRANcellId );
        ie->value.u.cztFailCellECGI.iE_Extns.noComp.pres = NOTPRSNT;

        /*    if(reEstablishmentCellECGI)*/ /* need to check when this ie is required */
        /* {*/
               ie = &hoReportPdu->pdu.val.initiatingMsg.value.u.cztHovrReport.protocolIEs.member[4];
               /* IE5 - Re-establishment Cell ECGI */
               czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
               czAcUtlFillTknU32(&(ie->id), Cztid_Re_establishmentCellECGI);
               czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
               czAcUtlFillTknU8(&(ie->value.u.cztreEstCellECGI.pres), PRSNT_NODEF);

               /* Fill the PLMN ID in target Cell Id */
               cmMemset(pLMNId3, 0, sizeof(pLMNId3));
               strcpy((char *)pLMNId3, "333");
               len = 3;

               /* Fill the PLMN ID */
               czFillTknStrOSXL(&(ie->value.u.cztreEstCellECGI.pLMN_Identity),
                       len, pLMNId3, &hoReportPdu);

               czFillTknBStr32(&(ie->value.u.cztreEstCellECGI.eUTRANcellIdentifier), 28, eUTRANcellId );
               ie->value.u.cztreEstCellECGI.iE_Extns.noComp.pres = NOTPRSNT;
       /*  } */
     } /* end if encodeFail == FALSE */
     else
     {
        czAcUtlFillTknU8(&(ie->pres), NOTPRSNT); 
        /* IE1 - Handover Report Type */
        czAcUtlFillTknU32(&(ie->id), Cztid_HovrReportTyp);
        czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);
        czAcUtlFillTknU32(&(ie->value.u.cztHovrReportTyp), 100);
     }

    *pdu = hoReportPdu;

    RETVALUE(ROK);
}


#ifdef ANSI
PUBLIC S16 czAcUtlCztFillCellActReq
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillCellActReq(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cellActReqPdu=NULLP;
   U16      numComp;
   S16      ret;
   Mem  mem;
   CztProtIE_Field_CellActvnRqst_IEs *ie = NULLP; 
   CztSrvdCellsToActivate_Item *ie1 = NULLP;
   Bool encodeFail = FALSE;
   U8 pLMNId1[10];
   U16        len;
   U32  eUTRANcellId = 2;

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillCellActReq);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&cellActReqPdu);
  if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cellActReqPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(cellActReqPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(cellActReqPdu->pdu.val.initiatingMsg.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(cellActReqPdu->pdu.val.initiatingMsg.procedureCode), Cztid_cellActvn);
   czAcUtlFillTknU32(&(cellActReqPdu->pdu.val.initiatingMsg.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(cellActReqPdu->pdu.val.initiatingMsg.value.u.cztCellActvnRqst.pres), PRSNT_NODEF);

   /* Filling 1 mandatory IE */
   numComp = 1;

   czAcUtlFillTknU16(&(cellActReqPdu->pdu.val.initiatingMsg.value.u.cztCellActvnRqst.protocolIEs.noComp), numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(cellActReqPdu, (numComp * sizeof(CztProtIE_Field_CellActvnRqst_IEs)),
               (Ptr*)&cellActReqPdu->pdu.val.initiatingMsg.value.u.cztCellActvnRqst.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

    ie = &cellActReqPdu->pdu.val.initiatingMsg.value.u.cztCellActvnRqst.protocolIEs.member[0];

   if(encodeFail == FALSE)
   {

       /* IE1 - Activated Cell List */
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_SrvdCellsToActivate);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);

       czAcUtlFillTknU16(&(ie->value.u.cztSrvdCellsToActivate.noComp),1);

       if ((cmGetMem(cellActReqPdu,(1 * sizeof(CztSrvdCellsToActivate_Item)),
                   (Ptr *)&ie->value.u.cztSrvdCellsToActivate.member)) !=ROK)
       {
           printf("cmGetMem failed, line %d\n",__LINE__);
           RETVALUE(RFAILED);
       }

       ie1= &ie->value.u.cztSrvdCellsToActivate.member[0];

       czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);

       /* Sub IE -  Cell ECGI */
       czAcUtlFillTknU8(&(ie1->ecgi.pres),PRSNT_NODEF);

       /* Fill the PLMN ID in target Cell Id */
       cmMemset(pLMNId1, 0, sizeof(pLMNId1));
       strcpy((char *)pLMNId1, "111");
       len = 3;

       /* Fill the PLMN ID */
       czFillTknStrOSXL(&(ie1->ecgi.pLMN_Identity),
                len, pLMNId1, &cellActReqPdu);

       czFillTknBStr32(&(ie1->ecgi.eUTRANcellIdentifier), 28, eUTRANcellId );
       ie1->ecgi.iE_Extns.noComp.pres = NOTPRSNT;
       ie1->iE_Extns.noComp.pres = NOTPRSNT;
    }
    else
    {
       czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
    }

    *pdu = cellActReqPdu;

     RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 czAcUtlCztFillCellActRes
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillCellActRes(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cellActResPdu=NULLP;
   U16 numComp;
   S16 ret;
   Mem  mem;
   CztProtIE_Field_CellActvnResp_IEs *ie; 
   CztActivatedCellLst_Item *ie1 = NULLP;
   Bool encodeFail = FALSE;
   U8 criticalityDiag = 0;
   U8 pLMNId1[10];
   U16 len;
   U32 eUTRANcellId = 2;

   mem.region = 0;
   mem.pool   = 0;

   TRC2(czAcUtlCztFillCellActRes);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
                  &(encodeFail));

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&cellActResPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cellActResPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(cellActResPdu->pdu.choice), X2AP_PDU_SUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(cellActResPdu->pdu.val.successfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(cellActResPdu->pdu.val.successfulOutcome.procedureCode), Cztid_cellActvn);
   czAcUtlFillTknU32(&(cellActResPdu->pdu.val.successfulOutcome.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(cellActResPdu->pdu.val.successfulOutcome.value.u.cztCellActvnResp.pres), PRSNT_NODEF);

  /* Filling 1 mandatory IE */
   numComp = 1;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "criticalityDiag",
         &criticalityDiag);
   if(criticalityDiag)
      numComp++;

   czAcUtlFillTknU16(&(cellActResPdu->pdu.val.successfulOutcome.value.u.cztCellActvnResp.protocolIEs.noComp), numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(cellActResPdu, (numComp * sizeof(CztProtIE_Field_CellActvnResp_IEs)),
               (Ptr*)&cellActResPdu->pdu.val.successfulOutcome.value.u.cztCellActvnResp.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   ie = &cellActResPdu->pdu.val.successfulOutcome.value.u.cztCellActvnResp.protocolIEs.member[0];
   
  if(encodeFail == FALSE)
   {

       /* IE1 - Activated Cell List */
       czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
       czAcUtlFillTknU32(&(ie->id), Cztid_ActivatedCellLst);
       czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);

       czAcUtlFillTknU16(&(ie->value.u.cztActivatedCellLst.noComp),1);

       if ((cmGetMem(cellActResPdu,(1 * sizeof(CztSrvdCellsToActivate_Item)),
                    (Ptr *)&ie->value.u.cztActivatedCellLst.member)) !=ROK)
       {
          printf("cmGetMem failed, line %d\n",__LINE__);
          RETVALUE(RFAILED);
       }

       ie1= &ie->value.u.cztActivatedCellLst.member[0];

       czAcUtlFillTknU8(&(ie1->pres), PRSNT_NODEF);

       /* Sub IE -  Cell ECGI */
       czAcUtlFillTknU8(&(ie1->ecgi.pres),PRSNT_NODEF);

      /* Fill the PLMN ID in target Cell Id */
      cmMemset(pLMNId1, 0, sizeof(pLMNId1));
      strcpy((char *)pLMNId1, "111");
      len = 3;

      /* Fill the PLMN ID */
      czFillTknStrOSXL(&(ie1->ecgi.pLMN_Identity),
               len, pLMNId1, &cellActResPdu);

      czFillTknBStr32(&(ie1->ecgi.eUTRANcellIdentifier), 28, eUTRANcellId );
      ie1->ecgi.iE_Extns.noComp.pres = NOTPRSNT;
      ie1->iE_Extns.noComp.pres = NOTPRSNT;

   } /* end if ecodeFail==FALSE */
   else
   {
      czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
   }

   *pdu = cellActResPdu;

    RETVALUE(ROK);
}



#ifdef ANSI
PUBLIC S16 czAcUtlCztFillCellActFail
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillCellActFail(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *cellActFailPdu=NULLP;
   U16 numComp;
   S16 ret;
   Mem mem;
   CztProtIE_Field_CellActvnFail_IEs *ie;
   Bool encodeFail = FALSE;
   U8 criticalityDiag = 0;
   U8 choice;
   U32 cause;

   mem.region = 0;
   mem.pool = 0;

   TRC2(czAcUtlCztFillCellActFail);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
                  &(encodeFail));

   /* Initialize memory control point */
   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem, (Ptr *)&cellActFailPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(cellActFailPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(cellActFailPdu->pdu.choice), X2AP_PDU_UNSUCCESSFULOUTCOME);
   czAcUtlFillTknU8(&(cellActFailPdu->pdu.val.unsuccessfulOutcome.pres),PRSNT_NODEF);
   czAcUtlFillTknU32(&(cellActFailPdu->pdu.val.unsuccessfulOutcome.procedureCode), Cztid_cellActvn);
   czAcUtlFillTknU32(&(cellActFailPdu->pdu.val.unsuccessfulOutcome.criticality), CztCriticalityrejectEnum);

   czAcUtlFillTknU8(&(cellActFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztCellActvnFail.pres), PRSNT_NODEF);

   /* Filling 1 mandatory IE */
   numComp = 1;

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "criticalityDiag",
         &criticalityDiag);
   if(criticalityDiag)
      numComp++;

   czAcUtlFillTknU16(&(cellActFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztCellActvnFail.protocolIEs.noComp), numComp);

   /* Get memory for numComp IEs */
   if ((cmGetMem(cellActFailPdu, (numComp * sizeof(CztProtIE_Field_CellActvnFail_IEs)),
               (Ptr*)&cellActFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztCellActvnFail.protocolIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__);
      RETVALUE(RFAILED);
   }


   ie = &cellActFailPdu->pdu.val.unsuccessfulOutcome.value.u.cztCellActvnFail.protocolIEs.member[0];
    
   if(encodeFail == FALSE)
   {
        /* IE1 - Cause */
        czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
        czAcUtlFillTknU32(&(ie->id), Cztid_Cause );
        czAcUtlFillTknU32(&(ie->criticality), CztCriticalityrejectEnum);
        choice = CAUSE_RADIONW;
        cause  = CztCauseRadioNwhandover_desirable_for_radio_reasonsEnum;
        czAcUtlFillTknU8(&(ie->value.u.cztCause.choice),choice);
        czAcUtlFillTknU32(&(ie->value.u.cztCause.val.radioNw),cause);

   } /*end if encodeFail == FALSE */
   else
   {
      czAcUtlFillTknU8(&(ie->pres), NOTPRSNT);
   }

   *pdu = cellActFailPdu;

    RETVALUE(ROK);
}




/*
*
*       Fun:   czAcUtlCztFillPrivateMsg 
*
*       Desc:  Call handler to fill reset message
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztutl.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztFillPrivateMsg
(
CmXtaTCCb  *tcCb,
CmXtaSpCb  *spCb,
CztEvnt    **pdu
)
#else
PUBLIC S16 czAcUtlCztFillPrivateMsg(tcCb, spCb, pdu)
CmXtaTCCb  *tcCb;
CmXtaSpCb  *spCb;
CztEvnt    **pdu;
#endif
{
   CztEvnt *czPvtPdu=NULLP;
   S16  ret;
   U16  numComp;
   Mem  mem; 
   Bool encodeFail = FALSE;
   CztPrivIE_Field_PrivMsg_IEs *ie;

   TRC2(encdecResetRqst);

   mem.region = 0;
   mem.pool   = 0;
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_BOOL, "encodeFail",
         &(encodeFail));

   ret = cmAllocEvnt(sizeof(CztEvnt), CZ_MEM_PDU_SIZE, &mem,(Ptr *)&czPvtPdu);
   if(ret != ROK)
   {
      printf("cmAllocEvnt failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }

   cmMemset((U8 *)&(czPvtPdu->pdu), 0, sizeof(CztX2AP_PDU));

   czAcUtlFillTknU8(&(czPvtPdu->pdu.choice), X2AP_PDU_INITIATINGMSG);
   czAcUtlFillTknU8(&(czPvtPdu->pdu.val.initiatingMsg.pres), PRSNT_NODEF);
   czAcUtlFillTknU32(&(czPvtPdu->pdu.val.initiatingMsg.procedureCode),Cztid_privateMsg);
   czAcUtlFillTknU32(&(czPvtPdu->pdu.val.initiatingMsg.criticality),CztCriticalityignoreEnum);

#ifdef NOT_USED
czPvtPdu->pdu.val.initiatingMsg.value.u.cztPrivMsg.pres.pres = NOTPRSNT; 
#endif 

   /* Filling 1 mandatory headers */
   czAcUtlFillTknU8(&(czPvtPdu->pdu.val.initiatingMsg.value.u.cztPrivMsg.pres), PRSNT_NODEF);

   numComp = 1;
   czAcUtlFillTknU16(&(czPvtPdu->pdu.val.initiatingMsg.value.u.cztPrivMsg.privateIEs.noComp), numComp);

   if ((cmGetMem(czPvtPdu, (numComp * sizeof(CztPrivIE_Field_PrivMsg_IEs)),
               (Ptr*)&czPvtPdu->pdu.val.initiatingMsg.value.u.
               cztPrivMsg.privateIEs.member)) !=ROK)
   {
      printf("cmGetMem failed, line %d\n", __LINE__); 
      RETVALUE(RFAILED);
   }
   ie = &(czPvtPdu->pdu.val.initiatingMsg.value.u.
         cztPrivMsg.privateIEs.member[0]);


   /*
   ie->pres.pres = PRSNT_NODEF;
   ie->id.choice.pres = PRSNT_NODEF;
   ie->id.choice.val = 1;
   ie->id.val.local.pres = PRSNT_NODEF;
   ie->id.val.local.val = 1;
   ie->criticality.pres = PRSNT_NODEF;
   ie->criticality.val = CztCriticalityignoreEnum;
   ie->value.u.unused.pres = PRSNT_NODEF;
   ie->value.u.unused.val = 1;

   */

   czAcUtlFillTknU8(&(ie->pres), PRSNT_NODEF);
   
   czAcUtlFillTknU8(&(ie->id.choice), PRIVIE_ID_LOCAL);
   czAcUtlFillTknU32(&(ie->id.val.local), 1);
   
   czAcUtlFillTknU32(&(ie->criticality), CztCriticalityignoreEnum);

   /*
   czAcUtlFillTknU8(&(ie->value.u.unused), PRSNT_NODEF);
   */

   ie->value.u.unused.pres = NOTPRSNT;

   *pdu = czPvtPdu; 

   RETVALUE(ROK);

} /* End of czAcUtlCztFillPrivateMsg */


#ifdef ANSI
PUBLIC S16 czAcUtlValidateMsg
(
CmXtaTCCb    *tcCb,
CmXtaSpCb    *spCb,
CzAccMsgQElm *czMsg,
S16           event /* windows warning fixed by changing from U8 to S16 */
)
#else
PUBLIC S16 czAcUtlValidateMsg(tcCb, spCb, czMsg, event)
CmXtaTCCb    *tcCb;
CmXtaSpCb    *spCb;
CzAccMsgQElm *czMsg;
S16           event; /* windows warning fixed by changing from U8 to S16 */
#endif
{
   U8  msgType = 0;
   U8  causeType = 0;
   U8  causeVal = 0;
   U8  procCode = 0;
   U8  critVal = 0;
   U8  trigMsg = 0;
   U16 eNb1MeasId = 0;
   U16 eNb2MeasId = 0;
   U16 oldUEX2APId = 0;
   U16 newUEX2APId = 0;
   S8 trigMsgId = -1;

   CzAcCztInfo *cztInfo;

   TRC2(czAcUtlValidateMsg);

   cztInfo = &(czMsg->u.cztInfo);
   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8, "eventType",
         &msgType);
   if(msgType != czMsg->u.cztInfo.msgType)
   {
      CMXTA_DBG_CALLIND((_cmxtap,"Failed : msgType mismatch: exp (%d) rcvd (%d) \
               \n", msgType, czMsg->u.cztInfo.msgType), 2);
      RETVALUE(RFAILED); 
   }
   
   if(event == CZAC_GP)
   {
      if(msgType == CZT_MSG_X2_SETUP ||
         msgType == CZT_MSG_X2_SETUP_RSP)
      {  
/*
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U32, "eNbId",
             &eNbId);
         if(eNbId != czMsg->u.cztInfo.enbId)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : ENODEB ID mismatch: exp (%ld) \
                     rcvd (%ld) \n", eNbId, czMsg->u.cztInfo.enbId), 2);
            RETVALUE(RFAILED); 
         }
*/
      }

      if(msgType == CZT_MSG_RSRC_ST_REQ ||
         msgType == CZT_MSG_RSRC_ST_UPD ||
         msgType == CZT_MSG_RSRC_ST_FAIL)
      {  
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
               "eNb1MeasId",  &eNb1MeasId);
         if(eNb1MeasId != czMsg->u.cztInfo.u.rsrcInfo.eNb1MeasId)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : Enb1 measurement ID mismatch: \
                exp (%d) rcvd (%d)  \n", eNb1MeasId, czMsg->u.cztInfo.u.rsrcInfo.eNb1MeasId), 2);
            RETVALUE(RFAILED); 
         }
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16,
               "eNb2MeasId",  &eNb2MeasId);
         if(eNb2MeasId != cztInfo->u.rsrcInfo.eNb2MeasId)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : Enb2 measurement ID  \
             mismatch: exp (%d) rcvd (%d) \n", eNb1MeasId, cztInfo->u.rsrcInfo.eNb2MeasId), 2);
            RETVALUE(RFAILED); 
         }
      }
      
      if(msgType == CZT_MSG_X2_SETUP_FAIL ||
         msgType == CZT_MSG_CFG_UPD_FAIL ||
         msgType == CZT_MSG_RSRC_ST_FAIL ||
         msgType == CZT_MSG_RESET)
      {  
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
               "causeType",  &causeType);
         if(causeType != cztInfo->cause.causeType)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : CauseType mismatch: \
                     exp (%d) rcvd (%d) \n", causeType, cztInfo->cause.causeType), 2);
            RETVALUE(RFAILED); 
         }
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
               "causeVal",  &causeVal);
         if(causeVal != cztInfo->cause.causeVal)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : CauseVal mismatch: \
                     exp (%d) rcvd (%d) \n", causeVal, cztInfo->cause.causeVal), 2);
            RETVALUE(RFAILED); 
         }
         if(msgType != CZT_MSG_RESET)
         {
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
                  "critProcCode",  &procCode);
            if(procCode != cztInfo->crit.procCode)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : Criticality Diag: \
                  procCode mismatch: exp (%d) rcvd (%d) \n", 
                  procCode, cztInfo->crit.procCode), 2);
               RETVALUE(RFAILED); 
            }
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
                  "trigMsg",  &trigMsg);
            if(trigMsg != cztInfo->crit.trigMsg)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : Criticality Diag: \
                        trigerring Msg mismatch: exp (%d) rcvd (%d) \n", 
                        trigMsg, cztInfo->crit.trigMsg), 2);
               RETVALUE(RFAILED); 
            }
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
                  "critVal",  &critVal);
            if(critVal != cztInfo->crit.crit)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : Criticality Diag: \
                        criticality value mismatch: exp (%d) rcvd (%d) \n", 
                        critVal, cztInfo->crit.crit), 2);
               RETVALUE(RFAILED); 
            }
            
         }
      }
       
   }
   else
   {
      /* cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "oldUEX2APId",
          &oldUEX2APId);
      if(oldUEX2APId != czMsg->u.cztInfo.u.ueInfo.oldX2APUEId)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "Failed : oldUEX2APId mismatch: exp (%d) \
               rcvd (%d) \n", oldUEX2APId, czMsg->u.cztInfo.u.ueInfo.oldX2APUEId), 2);
         RETVALUE(RFAILED); 
      }
      if(msgType != CZT_MSG_HO_REQ &&
         msgType != CZT_MSG_HO_FAIL)
      {
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "newUEX2APId",
             &newUEX2APId);
         if(newUEX2APId != czMsg->u.cztInfo.u.ueInfo.newX2APUEId)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : newUEX2APId mismatch:  \
                     exp (%d) rcvd (%d)\n", 
                     newUEX2APId, czMsg->u.cztInfo.u.ueInfo.newX2APUEId), 2);
            RETVALUE(RFAILED); 
         }
      }
*/
      if(msgType == CZT_MSG_HO_FAIL ||
         msgType == CZT_MSG_HO_CANCEL ||
         msgType == CZT_MSG_ERR_IND)
      {
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
               "causeType",  &causeType);
         if(causeType>0 && (causeType != cztInfo->cause.causeType))
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : CauseType mismatch: \
                     exp (%d) rcvd (%d) \n", 
                     causeType, cztInfo->cause.causeType), 2);
            RETVALUE(RFAILED); 
         }
         cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8,
               "causeVal",  &causeVal);
         if((causeVal >0) && 
            ((causeType != cztInfo->cause.causeType) ||
             (causeVal != cztInfo->cause.causeVal)))
         {
            CMXTA_DBG_CALLIND((_cmxtap, "Failed : CauseType mismatch: \
                     exp(%d) rcvd(%d), CauseVal mismatch: \
                     exp (%d) rcvd (%d) \n", causeType, cztInfo->cause.causeType, 
                     causeVal, cztInfo->cause.causeVal), 2);
            RETVALUE(RFAILED); 
         }
         if(msgType != CZT_MSG_HO_CANCEL)
         {
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "oldUEX2APId",
                            &oldUEX2APId);
            if(oldUEX2APId >0 && oldUEX2APId != czMsg->u.cztInfo.u.ueInfo.oldX2APUEId)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : oldUEX2APId mismatch: exp (%d) \
               rcvd (%d) \n", oldUEX2APId, czMsg->u.cztInfo.u.ueInfo.oldX2APUEId), 2);
               RETVALUE(RFAILED); 
            }
            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U16, "newUEX2APId",
                              &newUEX2APId);
            if(newUEX2APId >0 && newUEX2APId != czMsg->u.cztInfo.u.ueInfo.newX2APUEId)
            {
               CMXTA_DBG_CALLIND((_cmxtap, "Failed : newUEX2APId mismatch:  \
                     exp (%d) rcvd (%d)\n", 
                     newUEX2APId, czMsg->u.cztInfo.u.ueInfo.newX2APUEId), 2);
               RETVALUE(RFAILED); 
            }

            cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_ENUM_U8,
                  "trigMsgType",  &trigMsgId);
            if(trigMsgId>=CZT_MSG_HO_REQ)
            {
               if(ROK != (czAcUtlGetProcInfo(trigMsgId, &procCode, &trigMsg, &critVal)))
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : Criticality Diag: \
                        unknown triggering message exp (%d) rcvd (%d) \n", 
                        trigMsgId, cztInfo->crit.trigMsg), 2);
                  RETVALUE(RFAILED); 
               }
               if(procCode != cztInfo->crit.procCode)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : Criticality Diag: \
                        procCode mismatch: exp (%d) rcvd (%d) \n", 
                        procCode, cztInfo->crit.procCode), 2);
                  RETVALUE(RFAILED); 
               }
               if(trigMsg != cztInfo->crit.trigMsg)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : Criticality Diag: \
                        trigerring Msg mismatch: exp (%d) rcvd (%d) \n", 
                        trigMsg, cztInfo->crit.trigMsg), 2);
                  RETVALUE(RFAILED); 
               }
               if(critVal != cztInfo->crit.crit)
               {
                  CMXTA_DBG_CALLIND((_cmxtap, "Failed : Criticality Diag:\
                        criticality value mismatch: exp (%d) rcvd (%d) \n", 
                        critVal, cztInfo->crit.crit), 2);
                  RETVALUE(RFAILED); 
               }
            }
         }
       }

    }
    RETVALUE(ROK); 

}

/*
*
*
*       Desc:  This function gets cause type and cause value
*              from error message.
*
*       Ret:   ROK
*
*       Notes: None
*              
*       File:  czac_cztcb.c
*
*/
#ifdef ANSI
PUBLIC S16 czAcUtlCztGetErrCause
(
CztX2AP_PDU    *pdu,
U8             *causeType,
U8             *causeVal
)
#else
PUBLIC S16 czAcUtlCztGetErrCause(pdu,causeType,causeVal)
CztX2AP_PDU    *pdu;
U8             *causeType;
U8             *causeVal;
#endif
{
   TknU8  *ie;

   TRC2(zAcUtlCztGetErrCause);

   ie = NULLP;

   czUtlGetIE(pdu, Cztid_Cause, (TknU8 **)&ie);
   if(ie == NULLP)
   {
       RETVALUE(RFAILED);
   }
   
   *causeType   = ((CztCause *)ie)->choice.val;
   *causeVal    = czUtlGetCause((CztCause *)ie);

   RETVALUE(ROK);
}
#ifdef ANSI
PUBLIC S16 czAcUtlCztGetCritDiag
(
CztEvnt   *evnt,                    
CzAcCztCrit *critInfo
)
#else
PUBLIC S16 czAcUtlCztGetCritDiag(evnt, critInfo)
CztEvnt   *evnt;                   
CzAcCztCrit *critInfo;
#endif
{

   CztCriticalityDiag *criticalityDiag = NULLP;

   TRC2(czAcUtlCztGetCritDiag);

/* Start with Criticality Diagnostics IE value to get message 
   procedure code value */
   czUtlGetIE(&evnt->pdu, Cztid_CriticalityDiag, (TknU8 **)&criticalityDiag);
   if(NULLP != criticalityDiag)
   {
      if(criticalityDiag->procedureCode.pres == PRSNT_NODEF)
      {
         critInfo->procCode = criticalityDiag->procedureCode.val;
         if(criticalityDiag->triggeringMsg.pres == PRSNT_NODEF)
         {
            critInfo->trigMsg = criticalityDiag->triggeringMsg.val;
            if(criticalityDiag->procedureCriticality.pres == PRSNT_NODEF)
              critInfo->crit = criticalityDiag->procedureCriticality.val;
         }
      }
   }

   RETVALUE(ROK);
}   

#ifdef ANSI
PUBLIC S16  czAcUtlGetProcInfo
(
U8  msgId,
U8 *procCode, 
U8 *msgType, 
U8 *criticality
)
#else
PUBLIC S16 czAcUtlGetProcInfo(msgId, procCode, msgType, criticality)
U8  msgId;
U8 *procCode; 
U8 *msgType;
U8 *criticality;
#endif
{
   switch(msgId)
   {
      case CZT_MSG_HO_REQ:
      {
         *procCode = 0;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_HO_ACK:
      {
         *procCode = 0;
         *msgType = X2AP_PDU_SUCCESSFULOUTCOME;
         break;
      }
      case CZT_MSG_HO_FAIL:
      {
         *procCode = 0;
         *msgType = X2AP_PDU_UNSUCCESSFULOUTCOME;
         break;
      }
      case CZT_MSG_HO_CANCEL:
      {
         *procCode = 1;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }

      case CZT_MSG_SN_STATUS_TRFR:
      {
         *procCode = 4;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_UE_CXT_RELEASE:
      {
         *procCode = 5;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_LOAD_IND:
      {
         *procCode = 2;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_ERR_IND:
      {
         /* cz001.301: test case fix */
         *procCode = 7;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_X2_SETUP:
      {
         *procCode = 6;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_X2_SETUP_RSP:
      {
         *procCode = 6;
         *msgType = X2AP_PDU_SUCCESSFULOUTCOME;
         break;
      }
      case CZT_MSG_X2_SETUP_FAIL:
      {
         *procCode = 6;
         *msgType = X2AP_PDU_UNSUCCESSFULOUTCOME;
         break;
      }
     case CZT_MSG_RESET:
      {
         *procCode = 7;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_RESET_RSP:
      {
         *procCode = 7;
         *msgType = X2AP_PDU_SUCCESSFULOUTCOME;
         break;
      }
      case CZT_MSG_CFG_UPD_REQ:
      {
         *procCode = 8;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_CFG_UPD_ACK:
      {
         *procCode = 8;
         *msgType = X2AP_PDU_SUCCESSFULOUTCOME;
         break;
      }
      case CZT_MSG_CFG_UPD_FAIL:
      {
         *procCode = 8;
         *msgType = X2AP_PDU_UNSUCCESSFULOUTCOME;
         break;
      }
      case CZT_MSG_RSRC_ST_REQ:
      {
         *procCode = 9;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      case CZT_MSG_RSRC_ST_RSP:
      {
         *procCode = 9;
         *msgType = X2AP_PDU_SUCCESSFULOUTCOME;
         break;
      }
      case CZT_MSG_RSRC_ST_FAIL:
      {
         *procCode = 9;
         *msgType = X2AP_PDU_UNSUCCESSFULOUTCOME;
         break;
      }
      case CZT_MSG_RSRC_ST_UPD:
      {
         *procCode = 10;
         *msgType = X2AP_PDU_INITIATINGMSG;
         break;
      }
      default:
      {
         RETVALUE(RFAILED);
      }
         
   }
   *criticality = czGetProcCrit[*procCode];
   RETVALUE(ROK);

}




#ifdef ANSI
PUBLIC S16  czAcUtlFillTknU8
(
TknU8  *encParam,
U8     val
)
#else
PUBLIC S16 czAcUtlFillTknU8(encParam, val)
TknU8  *encParam;
U8     val;
#endif
{
  TRC2(czAcUtlFillTknU8)
  encParam->pres = PRSNT_NODEF;
  encParam->val  = val;
  RETVALUE(ROK);
} /* end of czAcUtlFillTknU8 */


#ifdef ANSI
PUBLIC S16  czAcUtlFillTknU16
(
TknU16  *encParam,
U16     val
)
#else
PUBLIC S16 czAcUtlFillTknU16(encParam, val)
TknU16  *encParam;
U16     val;
#endif
{
  TRC2(czAcUtlFillTknU16)
  encParam->pres = PRSNT_NODEF;
  encParam->val  = val;
  RETVALUE(ROK);
} /* end of czAcUtlFillTknU16 */

#ifdef ANSI
PUBLIC S16  czAcUtlFillTknU32
(
TknU32  *encParam,
U32     val
)
#else
PUBLIC S16 czAcUtlFillTknU32(encParam, val)
TknU32  *encParam;
U32     val;
#endif
{
   TRC2(czAcUtlFillTknU32)
   encParam->pres = PRSNT_NODEF;
   encParam->val  = val;
   RETVALUE(ROK);
} /* end of czAcUtlFillTknU32 */



/********************************************************************30**

         End of file:     czac_cztutl_r9.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:08:17 2015

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
/main/1      ---      aj       1. LTE-X2AP Initial Release.
/main/1+   cz001.101  mm       1. CR Fixes.
/main/2      ---     pt        1. LTE-X2AP 3.1 release.
*********************************************************************91*/
