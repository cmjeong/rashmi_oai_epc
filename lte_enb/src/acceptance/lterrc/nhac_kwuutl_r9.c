
/********************************************************************20**

     Name:    RRC - acc test file

     Type:    C file

     Desc:    

     File:   nhac_kwuutl_r9.c 

     Sid:      nhac_kwuutl_r9.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:51:23 2016

     Prg:     rer

*********************************************************************21*/

/* header include files (.h) */
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
#include "ctf.h"           /* PHY Interface */
#include "cm_xta.h"
#include "nhac_acc.h"
/*#include "nh.h"*/
#include "lnh.h"
#include "cm_pasn.h"
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
#include "nhac_asn.x"
using namespace NH_LTERRC_REL9; 
#include "nhac_nhu.x"
#include "ctf.x"           /* PHY interface */
#include "lnh.x"
#include "cm_pasn.x"
#include "nhac_db.x"
#include "nh_3gdb.x"
#include "nhac_acc.x"

/*
 *
 *       Fun:    nhAcKwuTstCbFind -
 *
 *       Desc:   Find the test Case Control Block 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   nhac_kwuutl.c
 *
 */

#ifdef ANSI
PUBLIC CmXtaTCCb*  nhAcKwuTstCbFind
(
)
#else
PUBLIC CmXtaTCCb*  nhAcKwuTstCbFind ()
#endif
{
   TRC2(nhAcKwuTstCbFind)

   /*-- Optimization, check if only one TC running --*/
#ifdef CMXTA_EXTENSION
   if (cmXtaCb.curTCCb != NULLP)
      RETVALUE(cmXtaCb.curTCCb);
#else
   if ((cmXtaCb.curTCCb != NULLP)   &&
       (cmXtaCb.curTCCb->state != CMXTA_END_SHUTDOWN))
      RETVALUE(cmXtaCb.curTCCb);
#endif

   RETVALUE(NULLP);
}

/*
*
*       Fun:   nhAcUtlKwuCb
*
*       Desc:  This function is used to free the Queue Element
*
*       Ret:   None
*
*       Notes: None
*
*       File:  nhac_kwuutl.c
*
*/
#ifdef ANSI
PUBLIC S16 nhAcUtlKwuCb
(
CmXtaMsgQElm *qElm
)
#else
PUBLIC S16 nhAcUtlKwuCb(qElm)
CmXtaMsgQElm *qElm;
#endif /* ANSI */
{
   NhAccMsgQElm  *rrcMsg = NULLP;

   TRC2(nhAcUtlKwuCb)

   CMXTA_DBG_PARAM((_cmxtap, "nhAcUtlKwuCb(): \n"));

   rrcMsg = (NhAccMsgQElm *)qElm->data;

   switch (qElm->pst.event)
   {
      case KWU_EVT_BND_REQ:
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;
  
      case KWU_EVT_UBND_REQ:
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;
  
      case KWU_EVT_DAT_REQ:
         CMXTA_FREE(rrcMsg, sizeof(NhAccMsgQElm));
         break;
   } /* end of switch case */

   RETVALUE(CMXTA_ERR_NONE);
} /* End of nhAcUtlKwuCb() */


/*
 *
 *       Fun:    nhAcConstructAndEncodeCcchMsg
 *
 *       Desc:   Construct the message and encode
 *
 *       Ret:    Integer
 *
 *       Notes:  None
 *
 *       File:   nhac_kwuutl.c
 *
 */

#ifdef ANSI
PUBLIC S16  nhAcConstructAndEncodeCcchMsg
(
Pst *pst,
U16 msgType,
Buffer **mBuf,
CmXtaSpCb    *spCb,
CmXtaTCCb    *tcCb
)
#else
PUBLIC S16  nhAcConstructAndEncodeCcchMsg(pst,msgType,mBuf,spCb,tcCb)
Pst *pst;
U16 msgType;
Buffer  **mBuf;
CmXtaSpCb    *spCb;
CmXtaTCCb    *tcCb;
#endif
{
  U8 cause=1;
  U8 rlcRel=9;

   TRC2(nhAcConstructAndEncodeCcchMsg)
   
   cmXtaXmlGetVal(NULLP, spCb->childStep, CMXTA_ATTRIB_U8, "rlcRel",
                                       &rlcRel);
   if(rlcRel == 9)
   {  
   switch(msgType)
   {
      case C1_RRCCONRQST:
         nhAcBuildRRCConReq_r9(mBuf);
         break;

      case C1_RRCCONREESTBRQST:
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"cause",&cause);
         nhAcBuildRRCConReEstReq_r9(mBuf,cause);
         break;

      /* moved DCCH messages to nhac_pjuutl.c */

      default:
         break;
   }/* End of switch */
   }
   else
   {
   switch(msgType)
   {
      case C1_RRCCONRQST:
         nhAcBuildRRCConReq_r11(mBuf);
         break;

      case C1_RRCCONREESTBRQST:
         cmXtaXmlGetVal(NULLP,spCb->childStep, CMXTA_ATTRIB_U8,"cause",&cause);
         nhAcBuildRRCConReEstReq_r11(mBuf,cause);
         break;

      /* moved DCCH messages to nhac_pjuutl.c */

      default:
         break;

   }
   }
   RETVALUE(CMXTA_ERR_NONE);
}

/*
 *
 *       Fun:    nhAcBuildRRCConReEstReq_r9
 *
 *       Desc:   Build RRC Conn. Reestablish Req
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   nhac_kwuutl_r9.c
 *
 */

#ifdef ANSI
PUBLIC S16  nhAcBuildRRCConReEstReq_r9
(
Buffer **mBuf,
U8 cause
)
#else
PUBLIC S16  nhAcBuildRRCConReEstReq_r9(mBuf,cause)
Buffer **mBuf;
U8 cause;
#endif
{
   NhuDatIndSdus  *pdu;
   NhuUL_CCCH_Msg *conReEstReqMsg=NULLP;
   NhuRRCConReestbRqstcriticalExtns *critex=NULLP;
   
   Mem  sMem; 
   S16 ret = 0;

   Bool dbgFlag = TRUE;  /* Debug Flag */ 
   U32  fLen;      /* Length of static buffer, if applicable */
   CmPAsnErr err;  /* error to be returned back to the caller */

   TRC2(nhAcBuildRRCConReEstReq_r9)

   sMem.region = 0;
   sMem.pool = 0;
   fLen = 0;

   CMXTA_ALLOCMBUF(mBuf);

   CMXTA_ALLOC_EVNT(&pdu, sizeof(NhuDatIndSdus),&sMem, NHAC_MEM_PDU_SIZE);

   conReEstReqMsg = (NhuUL_CCCH_Msg *)&(pdu->sdu.m.ulCcchMsg);
   

   NHAC_FILL_U8_U32_TKN(conReEstReqMsg->pres, TRUE, 1);
   NHAC_FILL_U8_U32_TKN(conReEstReqMsg->message.choice,TRUE, 0);
   if(!(conReEstReqMsg->message.choice.val))
   {
      /* this is for Conn Re Est Req */
      NHAC_FILL_U8_U32_TKN(conReEstReqMsg->message.val.c1.choice,TRUE, 0);
      if(!(conReEstReqMsg->message.val.c1.choice.val))
      {
         NHAC_FILL_U8_U32_TKN(conReEstReqMsg->message.val.c1.val.rrcConReestbRqst.pres,TRUE, 1);
         critex = &(conReEstReqMsg->message.val.c1.val.rrcConReestbRqst.criticalExtns);
         NHAC_FILL_U8_U32_TKN(critex->choice,TRUE, 0);

         if (!(critex->choice.val))
         {
            NHAC_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.pres ,TRUE, 1);
            NHAC_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.ue_Identity.pres ,TRUE, 1);
            /* Bit String */
            FILL_BIT_STR(critex->val.rrcConReestbRqst_r8.ue_Identity.c_RNTI, 16, 1, pdu);
            NHAC_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.ue_Identity.physCellId ,TRUE, 1);
            /* Bit String */
            FILL_BIT_STR(critex->val.rrcConReestbRqst_r8.ue_Identity.shortMAC_I, 16, 1, pdu);

            NHAC_FILL_U8_U32_TKN(critex->val.rrcConReestbRqst_r8.reestablishmentCause, TRUE, cause);
            /* Bit String */
            FILL_BIT_STR(critex->val.rrcConReestbRqst_r8.spare, 2, 1, pdu);
         }
         else
         {
            NHAC_FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres ,TRUE, 1);
         }
      }
      else
      {
         /* this is for Conn Req, Need not fill here */
      }
   }
   else
   {
       NHAC_FILL_U8_U32_TKN(conReEstReqMsg->message.val.messageClassExtn.pres,TRUE, 1)
   }

   /* Encode the message */
   ret = cmPAsnEncMsgUalign ((TknU8*)(conReEstReqMsg), CM_PASN_USE_MBUF, 
            (Void *)(*mBuf), 0, nhUL_CCCH_Pdu_r9, &err, &fLen, dbgFlag, FALSE);
   if (ret != ROK) 
   {
      sprintf( pbuf,"\n PASN lib Encoding Failed!\n");
      SPrint(  pbuf  );
      CMXTA_FREEMBUF(*mBuf);
      CMXTA_FREEEVNT(pdu);
      RETVALUE(CMXTA_ERR_INT);
   } 
   else 
   {
      sprintf( pbuf,"\n PASN lib Encoding OK\n");
      SPrint(  pbuf  );
   }

   CMXTA_FREEEVNT(pdu);
   RETVALUE (CMXTA_ERR_NONE);
}

/*
 *
 *       Fun:    nhAcBuildRRCConReq_r9
 *
 *       Desc:   Build RRC Conn. Req
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   nhac_kwuutl.c
 *
 */

#ifdef ANSI
PUBLIC S16  nhAcBuildRRCConReq_r9
(
Buffer **mBuf
)
#else
PUBLIC S16  nhAcBuildRRCConReq_r9(mBuf)
Buffer **mBuf;
#endif
{
   NhuDatIndSdus  *pdu;
   NhuUL_CCCH_Msg *conReqMsg=NULLP;
   NhuRRCConRqstcriticalExtns *critex=NULLP;
   
   Mem  sMem; 
   S16 ret = 0;

   Bool dbgFlag = TRUE;  /* Debug Flag */ 
   U32  fLen;      /* Length of static buffer, if applicable */
   CmPAsnErr err;  /* error to be returned back to the caller */ 

   TRC2(nhAcBuildRRCConReq_r9)

   sMem.region = 0;
   sMem.pool = 0;
   fLen = 0;

   CMXTA_ALLOCMBUF(mBuf);

   CMXTA_ALLOC_EVNT(&pdu, sizeof(NhuDatIndSdus),&sMem,NHAC_MEM_PDU_SIZE);

   conReqMsg = (NhuUL_CCCH_Msg *)&(pdu->sdu.m.ulCcchMsg);

   NHAC_FILL_U8_U32_TKN(conReqMsg->pres, TRUE, 1);
   NHAC_FILL_U8_U32_TKN(conReqMsg->message.choice,TRUE, 0);
   if(!(conReqMsg->message.choice.val))
   {
      NHAC_FILL_U8_U32_TKN(conReqMsg->message.val.c1.choice,TRUE, 1);
      
      /* If choice=0, then it is for Conn Re Est Req, Need not fill here */

      NHAC_FILL_U8_U32_TKN(conReqMsg->message.val.c1.val.rrcConRqst.pres, TRUE, 1);
      critex = &(conReqMsg->message.val.c1.val.rrcConRqst.criticalExtns);
      NHAC_FILL_U8_U32_TKN(critex->choice, TRUE,0);
      if(!(critex->choice.val))
      {
         NHAC_FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.pres,TRUE,1);
         NHAC_FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.ue_Identity.choice,TRUE,0);
         if(!(critex->val.rrcConRqst_r8.ue_Identity.choice.val))
         {
            NHAC_FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.pres,TRUE,1);
            FILL_BIT_STR(critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.mmec,
                          8, 1, pdu);
            FILL_BIT_STR(critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.m_TMSI, 32, 1, pdu);
         }
         else
         {
            FILL_BIT_STR(critex->val.rrcConRqst_r8.ue_Identity.val.randomValue, 40, 1, pdu);
         }

         NHAC_FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.establishmentCause,TRUE,1);
         FILL_BIT_STR(critex->val.rrcConRqst_r8.spare, 1,1, pdu);
      }
      else
      {
         NHAC_FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE,1);
      }
   }
   else
   {
       NHAC_FILL_U8_U32_TKN(conReqMsg->message.val.messageClassExtn.pres,TRUE, 1)
   }

   /* Encode the message */
   ret = cmPAsnEncMsgUalign ((TknU8*)(conReqMsg), CM_PASN_USE_MBUF, 
            (Void *)(*mBuf),0, nhUL_CCCH_Pdu_r9, &err, &fLen, dbgFlag, FALSE);
   if (ret != ROK) 
   {
      sprintf( pbuf,"\n PASN lib Encoding Failed!\n");
      SPrint(  pbuf  );
      CMXTA_FREEMBUF(*mBuf);
      CMXTA_FREEEVNT(pdu);
      RETVALUE(CMXTA_ERR_INT);
   } 
   else 
   {
      sprintf( pbuf,"\n PASN lib Encoding OK\n");
      SPrint(  pbuf  );
   }

   CMXTA_FREEEVNT(pdu);
   RETVALUE (CMXTA_ERR_NONE);
}

/**********************************************************************
         End of file:     nhac_kwuutl_r9.c@@/main/TeNB_Main_BR/tenb_main_ccb/tenb_5.0_RIB/tenb_5.0_RIB_GA/10 - Mon Feb 15 12:51:23 2016
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat     init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---     rer              1. LTE RRC Initial Release.
/main/2      ---     chebli           1. RRC Release 2.1.
/main/3      ---     sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

