

/**********************************************************************

     Name:     LTE-UE Simulator 
  
     Type:     C Source file
  
     Desc:     Code for UE Simulator RRC functions.

     File:     ue_rrc.c

     Sid:      ue_rrc.c@@/main/1 - Sun Mar 28 22:59:26 2010

     Prg:      vp

**********************************************************************/

/* Header include files */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */

#include "gen.h"           /* General */
#include "ssi.h"           /* System services */

#include "cm_tkns.h"       /* Common Token defines */
#include "cm_mblk.h"       /* Common Mem Allocation defines */
#include "cm_llist.h"      /* Common Link list defines */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_hash.h"       /* Common Hashlist defines */
#include "cm_lte.h"        /* Common Umts defines */
#include "cm_pasn.h"       /* Common Pasn defines */
#include "cm_lte.h"       /* Common LTE defines */
#ifndef SS_CAVIUM
#include "pcap.h"       /* common tokens */
#endif /* SS_CAVIUM */
/* ue007.101: cavium compile warning fix */
#ifdef SS_CAVIUM
#include "cvmx.h"
#include "cvmx-wqe.h"
#endif /* SS_CAVIUM */

#include "nhu_asn.h"
#include "ue_nhu_app.h"    /* UE App Interface with RRC */
#include "cm_emm_esm.h"    /* EMM-ESM Defines */
#include "cm_emm.h"        /* EMM Defines */
#include "cm_esm.h"        /* ESM Defines */
#include "ue_app.h"        /* UE application includes */
#include "tfu.h"
#include "ue.h"           /* NHU Interface includes */
#include "ue_err.h"


/* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
#include "LtePhyL2Api.h" /* Phy api file */
#include "apidefs.h"     /* Phy api file */
#include "resultcodes.h" /* Phy api file */
#endif /* YS_MSPD*/
/* header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm5.x"           /* Timer services */
#include "cm_tkns.x"       /* Common Token definitions */
#include "cm_mblk.x"       /* Common Memory Allocation */
#include "cm_llist.x"      /* Common Linklist definitions */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_hash.x"       /* Common Hashlist definitions */
#include "cm_pasn.x"       /* Common Pasn definitions */
#include "cm_lte.x"        /* Common LTE definitions */
#include "cm_lib.x"        /* Common Library */
#include "ue_nh_db.x"
#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* UE App Interface with RRC */
#include "cm_emm.x"        /* EMM Defines */
#include "cm_esm.x"        /* ESM Defines */
#include "cm_emm_esm.x"    /* EMM-ESM Defines */
#include "ue_app.x"        /* UE application includes */
#include "tfu.x"
#include "ue.x"            /* NHU Interface includes */
/* ue010.101 : Enhanced measurement feature */
extern UeNetWorkParam   *uenetworkparam;   

PUBLIC Txt   pbuf[255];
#define UE_RRC_ALLOC_MBUF(_region, _pool, _buf)\
{\
   if(SGetMsg(_region, _pool, (Buffer **) _buf) != ROK)\
   {                                                                       \
      (*_buf) = NULLP;                                                     \
   }                                                                       \
}
#define UE_RRC_FREE_MBUF(_mBuf) \
if (_mBuf != (Buffer*) NULLP)      \
{                                   \
   (Void)SPutMsg(_mBuf);            \
   _mBuf = NULLP;                   \
}

#define UE_RRC_ALLOC_EVNT(_evntPtr, _size, _mem, _maxBlkSize)   \
{                                                              \
   (*_evntPtr) = NULLP;                                        \
   (Void)cmAllocEvnt((Size) _size, _maxBlkSize, _mem,          \
                     (Ptr *)_evntPtr);                         \
}

#define UE_RRC_GET_MEM(_memPtr, _size, _allocPtr)               \
{                                                              \
   (*_allocPtr) = NULLP;                                       \
   (Void)cmGetMem(_memPtr, _size, (Ptr *)_allocPtr);           \
}

#define UE_RRC_FREE_EVNT(_evntPtr)       \
{                                      \
   cmFreeMem((_evntPtr));              \
   (_evntPtr) = NULLP;                 \
}

#define FILL_U8_U32_TKN(_ie, _pres, _val) {\
   _ie.pres = _pres;\
   _ie.val = _val;\
}

#define FILL_BIT_STR(_ptr, _len, _val, _pdu) {\
   U8      i;                                    \
   U16     _tmpLen;                             \
   _ptr.pres = PRSNT_NODEF;                     \
   _ptr.len =  _len;                            \
\
   _tmpLen = _len;                              \
   if((_len%8) > 0)                              \
   {                                             \
      _tmpLen = (_len/8)+1;                         \
   }                                             \
   else                                          \
   {                                             \
      _tmpLen = _len/8;                             \
   }                                             \
   UE_RRC_GET_MEM(_pdu, _tmpLen * sizeof(U8), (Ptr *)&(_ptr.val));  \
                   \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = 0; i < _tmpLen; i++)                  \
      {                                          \
         _ptr.val[i] = _val;                  \
      }                                          \
   }                                             \
}

/* ue003.101: Bitstring filling */
#define FILL_BIT_STR1(_ptr, _len, _val, _pdu) {\
   U8      i, tmpVal;                           \
   U16     _tmpLen;                             \
   _ptr.pres = PRSNT_NODEF;                     \
   _ptr.len =  _len;                            \
\
   _tmpLen = _len;                              \
   if((_len%8) > 0)                              \
   {                                             \
      _tmpLen = (_len/8)+1;                         \
   }                                             \
   else                                          \
   {                                             \
      _tmpLen = _len/8;                             \
   }                                             \
   UE_RRC_GET_MEM(_pdu, _tmpLen * sizeof(U8), (Ptr *)&(_ptr.val));  \
                   \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = 0; i < _tmpLen; i++)               \
      {                                          \
         tmpVal = (U8 )(_val >> (8 * (_tmpLen - (i + 1))));      \
         _ptr.val[i] = tmpVal;                   \
      }                                          \
   }                                             \
}

#define FILL_OCT_STR(_ptr, _len, _val, _pdu) {\
   U8      i;                                    \
   _ptr.pres = PRSNT_NODEF;                      \
   _ptr.len =  _len;                             \
                   \
   UE_RRC_GET_MEM(_pdu, _len * sizeof(U8), (Ptr *)&(_ptr.val));  \
                   \
   if(_ptr.val != NULLP)                         \
   {                                             \
      for(i = 0; i < _len; i++)                  \
      {                                          \
         _ptr.val[i] = _val;                  \
      }                                          \
   }                                             \
}

EXTERN UeMsSrCfgInfo        ueSrCfgDb[UE_NUM_SR_CFG];
EXTERN UeMsSrsCfgInfo       ueSrsCfgDb[UE_NUM_SRS_CFG];
EXTERN UeMsCqiPmiCfgIdxInfo ueCqiPmiCfgDb[UE_NUM_CQI_CFG];
EXTERN UeRiCfgIdxInfo       ueRiCfgDb[UE_NUM_RI_CFG];
EXTERN S16 ueRrcDecRRCMsgs
   ARGS((U8      lcId,NhuDatIndSdus *datIndSdu, Void *pdu, Buffer  *mBuf));
PRIVATE S16 ueRrcProcessSrb0(UeCb *ueCb,Buffer *mBuf);
PRIVATE S16 ueRrcProcessSrb12(UeCb *ueCb,Buffer *mBuf);

/*
 *
 *       Fun:    ueRrcBuildRRCConReq
 *
 *       Desc:   Build RRC Conn. Req
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueRrcBuildRRCConReq
(
/* ue003.101: Passing UeCb and stmsi flag */
Buffer **mBuf, 
UeCb    *ueCb,
Bool   sTmsiPres
)
#else
PUBLIC S16  ueRrcBuildRRCConReq(mBuf, ueCb, sTmsiPres)
Buffer **mBuf;
UeCb    *ueCb;
Bool   sTmsiPres;
#endif
{
   NhuDatReqSdus  *pdu;
   NhuUL_CCCH_Msg *conReqMsg=NULLP;
   NhuRRCConRqstcriticalExtns *critex=NULLP;
   
   Mem  sMem; 
   S16 ret = 0;

   Bool dbgFlag = TRUE;  /* Debug Flag */ 
   U32  fLen;      /* Length of static buffer, if applicable */
   CmPAsnErr err;  /* error to be returned back to the caller */ 
/* ue003.101: Conn req ueid changes */
   UeAppCb     *ueAppCb = NULLP;

   TRC2(ueRrcBuildRRCConReq)

   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;
   fLen = 0;

   UE_RRC_ALLOC_MBUF(DFLT_REGION, DFLT_POOL, mBuf);
   /* ue002.101: kworks_fix */
   if(mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }

   UE_RRC_ALLOC_EVNT(&pdu, sizeof(NhuDatReqSdus), &sMem, UE_RRC_BLKSZ);
   if (NULLP == pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE105, (ErrVal)0,
         "ueRrcBuildRRCConReq: cmAllocEvnt failed for RRC ConReq\n"); 
      RETVALUE(RFAILED);
   }

   conReqMsg = &(pdu->sdu.m.ulCcchMsg.ccchMsg);

   FILL_U8_U32_TKN(conReqMsg->pres, TRUE, 1);
   FILL_U8_U32_TKN(conReqMsg->message.choice,TRUE, 0);
   if(!(conReqMsg->message.choice.val))
   {
      FILL_U8_U32_TKN(conReqMsg->message.val.c1.choice,TRUE, 1);
      
      /* If choice=0, then it is for Conn Re Est Req, Need not fill here */

      FILL_U8_U32_TKN(conReqMsg->message.val.c1.val.rrcConRqst.pres, TRUE, 1);
      critex = &(conReqMsg->message.val.c1.val.rrcConRqst.criticalExtns);
      FILL_U8_U32_TKN(critex->choice, TRUE,0);
      if(!(critex->choice.val))
      {
         FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.pres,TRUE,1);
         
/* ue003.101: UeId encoding changes */
         if(sTmsiPres == TRUE)
         {
            FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.ue_Identity.choice,TRUE,0);
           if(ueCb)
           {
              /* ue008.101: Update ueAppCb with ueCb->rnti*/
              //UE_GET_APPCB(ueAppCb,ueCb->ueId);
              UE_GET_APPCB(ueCb->cellId,ueAppCb,ueCb->rnti);
              if(ueAppCb != NULLP)
              {

                 FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.pres,TRUE,1);
                 FILL_BIT_STR(critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.mmec,
                          8, ueAppCb->ueCtxt.ueGuti.mmeCode, pdu);
                 FILL_BIT_STR1(critex->val.rrcConRqst_r8.ue_Identity.val.s_TMSI.m_TMSI, 32, ueAppCb->ueCtxt.ueGuti.mTMSI, pdu);
             }
             else
             {
                UELOGERROR(ERRCLS_ADD_RES, EUE105, (ErrVal)0,
                 "ueRrcBuildRRCConReq: Unable to get UE AppCb\n"); 
                RETVALUE(RFAILED);
             } /* end of else part */

         FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.establishmentCause,TRUE,2);

           } /* end of if statement */
           else
           {
                UELOGERROR(ERRCLS_ADD_RES, EUE105, (ErrVal)0,
                 "ueRrcBuildRRCConReq: UeCb is Missing\n"); 
               RETVALUE(RFAILED);
           }
              
         } /* end of if part */
         else
         {
            FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.ue_Identity.choice,TRUE,1);
           /* Fill the Random Value */
            FILL_BIT_STR(critex->val.rrcConRqst_r8.ue_Identity.val.randomValue, 40, 3, pdu);

/* ue003.101: UeId encoding changes */
         FILL_U8_U32_TKN(critex->val.rrcConRqst_r8.establishmentCause,TRUE,2);

         }

         FILL_BIT_STR(critex->val.rrcConRqst_r8.spare, 1,1, pdu);
      }
      else
      {
         FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE,1);
      }
   }
   else
   {
       FILL_U8_U32_TKN(conReqMsg->message.val.messageClassExtn.pres,TRUE, 1)
   }

   /* Encode the message */
   ret = cmPAsnEncMsgUalign ((TknU8*)(conReqMsg), CM_PASN_USE_MBUF, 
            (Void *)(*mBuf),0, nhUL_CCCH_Pdu, &err, &fLen, dbgFlag, TRUE);
   if (ret != ROK) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE106, (ErrVal)0,
         "ueRrcBuildRRCConReq: PASN lib Encoding Failed\n"); 
      UE_RRC_FREE_MBUF(*mBuf);
      UE_RRC_FREE_EVNT(pdu);
      RETVALUE(RFAILED);
   } 
   else 
   {
      UE_DBGP_INFO((UE_PRNTBUF, 
         "ueRrcBuildRRCConReq: PASN lib Encoding Done"));
   }

   UE_RRC_FREE_EVNT(pdu);
   RETVALUE (ROK);
}

/*
 *
 *       Fun:    ueRrcBuildRRCConSetupComplete
 *
 *       Desc:   Build RRC Conn. Setup Complete
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueRrcBuildRRCConSetupComplete
(
 Buffer **mBuf
)
#else
PUBLIC S16  ueRrcBuildRRCConSetupComplete(mBuf)
Buffer **mBuf;
#endif
{
   NhuDatReqSdus  *pdu;
   NhuUL_DCCH_Msg *conSetupCompMsg=NULLP;
   NhuRRCConSetupComplcriticalExtns *critex=NULLP;
   NhuMCC_MNC_Digit *member = NULLP;
   NhuMCC_MNC_Digit *member1 = NULLP;

   U8 noComp = 0, idx = 0;
   U8 optional = 0;

   Mem  sMem; 
   S16 ret = 0;

   Bool dbgFlag = TRUE;  /* Debug Flag */ 
   U32  fLen;      /* Length of static buffer, if applicable */
   CmPAsnErr err;  /* error to be returned back to the caller */ 

   TRC2(ueRrcBuildRRCConSetupComplete)

   sMem.region = 0;
   sMem.pool = 0;
   fLen = 0;

   UE_RRC_ALLOC_MBUF(DFLT_REGION, DFLT_POOL, mBuf);
   /* ue002.101: kworks_fix */
   if(mBuf == NULLP)
      RETVALUE(RFAILED);

   UE_RRC_ALLOC_EVNT(&pdu, sizeof(NhuDatReqSdus),&sMem, UE_RRC_BLKSZ);
   if (NULLP == pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE107, (ErrVal)0,
         "ueRrcBuildRRCConSetupComplete: cmAllocEvnt failed \
         for RRC ConSetUpCom\n"); 
      RETVALUE(RFAILED);
   }

   conSetupCompMsg = &(pdu->sdu.m.ulDcchMsg.dcchMsg);

   FILL_U8_U32_TKN(conSetupCompMsg->pres, TRUE, 1);
   FILL_U8_U32_TKN(conSetupCompMsg->message.choice,TRUE, 0);
   /* To fill c1 */
   if(!(conSetupCompMsg->message.choice.val))
   {
      /* this is for Conn setup Complete */
      FILL_U8_U32_TKN(conSetupCompMsg->message.val.c1.choice,TRUE, 4);
      if(conSetupCompMsg->message.val.c1.choice.val == 4)
      {
         FILL_U8_U32_TKN(conSetupCompMsg->message.val.c1.val.rrcConSetupCompl.pres,TRUE, 1);
         /* RRC TransID */
         FILL_U8_U32_TKN(conSetupCompMsg->message.val.c1.val.rrcConSetupCompl.rrc_TrnsxnId,TRUE, 1);

         critex = &(conSetupCompMsg->message.val.c1.val.rrcConSetupCompl.criticalExtns);

         FILL_U8_U32_TKN(critex->choice,TRUE, 0);
         if (!(critex->choice.val))
         {
            FILL_U8_U32_TKN(critex->val.c1.choice,TRUE, 0);
            FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.pres,TRUE, 1);
            FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.selectedPLMN_Identity,TRUE, 3);

            FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.pres,
                  optional, 1);
            if(optional)
            {
               /* Fill It */
               FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.pres,TRUE, 1);

               /* Fill MCC */
               FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mcc.noComp,TRUE,
                     3);
               noComp = (U8) critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mcc.noComp.val;
               UE_RRC_GET_MEM(pdu, (noComp * sizeof(NhuMCC_MNC_Digit)), &member);
               for (idx=0; idx < noComp; idx++)
               {
                  member[idx].pres = TRUE;
                  member[idx].val = 1;
               }
               critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mcc.member = member;

               /* Fill MNC */
               FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mnc.noComp,TRUE,
                     3);
               noComp = (U8) critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mnc.noComp.val;
               UE_RRC_GET_MEM(pdu, (noComp * sizeof(NhuMCC_MNC_Digit)), &member1);
               for (idx=0; idx < noComp; idx++)
               {
                  member1[idx].pres = TRUE;
                  member1[idx].val = 1;
               }
               critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.plmn_Identity.mnc.member = member1;

               /* Bit String */
               FILL_BIT_STR(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.mmegi,16,1,pdu);
               FILL_BIT_STR(critex->val.c1.val.rrcConSetupCompl_r8.registeredMME.mmec,8,1,pdu);
            }

            /* Octet String -- 1 Octet*/
            FILL_OCT_STR(critex->val.c1.val.rrcConSetupCompl_r8.dedicatedInfoNAS,1,1,pdu);
            FILL_U8_U32_TKN(critex->val.c1.val.rrcConSetupCompl_r8.nonCriticalExtn.pres,TRUE, 1);
         }
         else
         {
            FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres, FALSE, 0);
         }
      }
      else
      {
         /* Invalid message type */
      }
   }
   else
   {
      FILL_U8_U32_TKN(conSetupCompMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

   /* Encode the message */
   ret = cmPAsnEncMsgUalign ((TknU8*)(conSetupCompMsg), CM_PASN_USE_MBUF, 
            (Void *)(*mBuf),0, nhUL_DCCH_Pdu, &err, &fLen, dbgFlag, TRUE);
   if (ret != ROK) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE108, (ErrVal)0,
         "ueRrcBuildRRCConSetupComplete:PASN lib Encoding Failed \n");
      UE_RRC_FREE_MBUF(*mBuf);
      UE_RRC_FREE_EVNT(pdu);
      RETVALUE(RFAILED);
   } 
   else 
   {
      UE_DBGP_INFO((UE_PRNTBUF, 
        "ueRrcBuildRRCConSetupComplete: PASN lib Encoding Done"));
      
   }

   UE_RRC_FREE_EVNT(pdu);
   RETVALUE (ROK);
}

/*
 *
 *       Fun:    ueRrcBuildRRCSecModeComplete
 *
 *       Desc:   Build RRC Security Mode Complete
 *
 *       Ret:    Void 
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueRrcBuildRRCSecModeComplete
(
Buffer **mBuf
)
#else
PUBLIC S16  ueRrcBuildRRCSecModeComplete(mBuf)
Buffer **mBuf;
#endif
{
   NhuDatReqSdus  *pdu;
   NhuUL_DCCH_Msg *secModeCompMsg=NULLP;
   NhuSecModeComplcriticalExtns *critex=NULLP;

   Mem  sMem; 
   S16 ret = 0;

   Bool dbgFlag = TRUE;  /* Debug Flag */ 
   U32  fLen;      /* Length of static buffer, if applicable */
   CmPAsnErr err;  /* error to be returned back to the caller */ 

   TRC2(ueRrcBuildRRCSecModeComplete)

   sMem.region = 0;
   sMem.pool = 0;
   fLen = 0;

   UE_RRC_ALLOC_MBUF(DFLT_REGION, DFLT_POOL, mBuf);
   /* ue002.101: kworks_fix */
   if(mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }

   UE_RRC_ALLOC_EVNT(&pdu, sizeof(NhuDatReqSdus),&sMem, UE_RRC_BLKSZ);
   if (NULLP == pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE109, (ErrVal)0,
        "ueRrcBuildRRCSecModeComplete:cmAllocEvnt failed for RRCSecModeCmp\n");
      RETVALUE(RFAILED);
   }

   secModeCompMsg = &(pdu->sdu.m.ulDcchMsg.dcchMsg);

   FILL_U8_U32_TKN(secModeCompMsg->pres, TRUE, 1);
   FILL_U8_U32_TKN(secModeCompMsg->message.choice,TRUE, 0);
   /* To fill c1 */
   if(!(secModeCompMsg->message.choice.val))
   {
      /* this is for Security mode Complete */
      FILL_U8_U32_TKN(secModeCompMsg->message.val.c1.choice,TRUE, 5);
      if(secModeCompMsg->message.val.c1.choice.val == 5)
      {
         FILL_U8_U32_TKN(secModeCompMsg->message.val.c1.val.securityModeCompl.pres,TRUE, 1);
         /* RRC TransID */
         FILL_U8_U32_TKN(secModeCompMsg->message.val.c1.val.securityModeCompl.rrc_TrnsxnId,TRUE, 1);
         critex = &(secModeCompMsg->message.val.c1.val.securityModeCompl.criticalExtns);

         FILL_U8_U32_TKN(critex->choice,TRUE, 0);
         if (!(critex->choice.val))
         {
            FILL_U8_U32_TKN(critex->val.securityModeCompl_r8.pres,TRUE, 1);
            FILL_U8_U32_TKN(critex->val.securityModeCompl_r8.nonCriticalExtn.pres,TRUE, 1);
         }
         else
         {
            FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE, 1);
         }
      }
      else
      {
         /* Invalid message type */
      }
   }
   else
   {
      FILL_U8_U32_TKN(secModeCompMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

   /* Encode the message */
   ret = cmPAsnEncMsgUalign ((TknU8*)(secModeCompMsg), CM_PASN_USE_MBUF, 
            (Void *)(*mBuf),0, nhUL_DCCH_Pdu, &err, &fLen, dbgFlag, TRUE);
   if (ret != ROK) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE110, (ErrVal)0,
        "ueRrcBuildRRCSecModeComplete: PASN lib Encoding Failed\n");
      UE_RRC_FREE_MBUF(*mBuf);
      UE_RRC_FREE_EVNT(pdu);
      RETVALUE(RFAILED);
   } 
   else 
   {
      UE_DBGP_INFO((UE_PRNTBUF,
       "ueRrcBuildRRCSecModeComplete:  PASN lib Encoding Done")); 
   }

   UE_RRC_FREE_EVNT(pdu);
   RETVALUE (ROK);
}

/*
 *
 *       Fun:    ueRrcBuildRRCConReCfgComplete
 *
 *       Desc:   Build RRC Conn. ReCfg Complete
 *
 *       Ret:    ROK - ok RFAILED- for any error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */

#ifdef ANSI
PUBLIC S16  ueRrcBuildRRCConReCfgComplete
(
Buffer **mBuf
)
#else
PUBLIC S16  ueRrcBuildRRCConReCfgComplete(mBuf)
Buffer **mBuf;
#endif
{
   NhuDatReqSdus  *pdu;
   NhuUL_DCCH_Msg *conReCfgCompMsg=NULLP;
   NhuRRCConRecfgnComplcriticalExtns *critex=NULLP;

   Mem  sMem; 
   S16 ret = 0;

   Bool dbgFlag = TRUE;  /* Debug Flag */ 
   U32  fLen;      /* Length of static buffer, if applicable */
   CmPAsnErr err;  /* error to be returned back to the caller */ 
   U8 rrcTransIdPres=1;
   U32 rrc_transId=1;

   TRC2(ueRrcBuildRRCConReCfgComplete)

   sMem.region = 0;
   sMem.pool = 0;
   fLen = 0;

   UE_RRC_ALLOC_MBUF(DFLT_REGION, DFLT_POOL, mBuf);
   /* ue002.101: kworks_fix */
   if(mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }

   UE_RRC_ALLOC_EVNT(&pdu, sizeof(NhuDatReqSdus),&sMem, UE_RRC_BLKSZ);
   if (NULLP == pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE111, (ErrVal)0,
        "ueRrcBuildRRCConReCfgComplete: cmAllocEvnt failed for RRC ReCfgCmp\n");
      RETVALUE(RFAILED);
   }

   conReCfgCompMsg = &(pdu->sdu.m.ulDcchMsg.dcchMsg);

   FILL_U8_U32_TKN(conReCfgCompMsg->pres, TRUE, 1);
   FILL_U8_U32_TKN(conReCfgCompMsg->message.choice,TRUE, 0);
   /* To fill c1 */
   if(!(conReCfgCompMsg->message.choice.val))
   {
      /* this is for Conn Recfg Complete */
      FILL_U8_U32_TKN(conReCfgCompMsg->message.val.c1.choice,TRUE, 2);
      if(conReCfgCompMsg->message.val.c1.choice.val == 2)
      {
         FILL_U8_U32_TKN(conReCfgCompMsg->message.val.c1.val.rrcConRecfgnCompl.pres,TRUE, 1);
         /* RRC TransID */
         if (rrcTransIdPres)
         {
            FILL_U8_U32_TKN(conReCfgCompMsg->message.val.c1.val.rrcConRecfgnCompl.rrc_TrnsxnId,TRUE, rrc_transId);
         }
         else
         {
             FILL_U8_U32_TKN(conReCfgCompMsg->message.val.c1.val.rrcConRecfgnCompl.rrc_TrnsxnId,FALSE, 0);
         }
         
         critex = &(conReCfgCompMsg->message.val.c1.val.rrcConRecfgnCompl.criticalExtns);
         FILL_U8_U32_TKN(critex->choice,TRUE, 0);
         if (!(critex->choice.val))
         {
            FILL_U8_U32_TKN(critex->val.rrcConRecfgnCompl_r8.pres,TRUE, 1);
            FILL_U8_U32_TKN(critex->val.rrcConRecfgnCompl_r8.nonCriticalExtn.pres,TRUE, 1);
         }
         else
         {
            FILL_U8_U32_TKN(critex->val.criticalExtnsFuture.pres,TRUE, 1);
         }
      }
      else
      {
         /* Invalid message type */
      }
   }
   else
   {
      FILL_U8_U32_TKN(conReCfgCompMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

   /* Encode the message */
   ret = cmPAsnEncMsgUalign ((TknU8*)(conReCfgCompMsg), CM_PASN_USE_MBUF, 
            (Void *)(*mBuf), 0, nhUL_DCCH_Pdu, &err, &fLen, dbgFlag, TRUE);
   if (ret != ROK) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE112, (ErrVal)0,
        "ueRrcBuildRRCConReCfgComplete: PASN lib Encoding Failed\n");
      UE_RRC_FREE_MBUF(*mBuf);
      UE_RRC_FREE_EVNT(pdu);
      
      RETVALUE(RFAILED);
   } 
   else 
   {
      UE_DBGP_INFO((UE_PRNTBUF, 
       "ueRrcBuildRRCConReCfgComplete:  PASN lib Encoding Done"));
      
   }

   UE_RRC_FREE_EVNT(pdu);
   RETVALUE (ROK);
}

/*
 *
 *       Fun:    ueRRCBuildUpLinkTrfr
 *
 *       Desc:   Build RRC Up Link Transfer
 *
 *       Ret:    ROK -ok RFAILED- in case of an error
 *
 *       Notes:  None
 *
 *       File:   
 *
 */

#ifdef ANSI
PUBLIC S16  ueRRCBuildUpLinkTrfr
(
 Buffer **mBuf
 )
#else
PUBLIC S16  ueRRCBuildUpLinkTrfr(mBuf)
   Buffer **mBuf;
#endif
{

   NhuDatReqSdus  *pdu;

   NhuUL_DCCH_Msg *upLinkTrfrMsg=NULLP;
   NhuULInfoTfrcriticalExtns *critex=NULLP;
   Mem  sMem; 
   S16 ret = 0;
   Bool dbgFlag = TRUE;  /* Debug Flag */ 
   U32  fLen;      /* Length of static buffer, if applicable */
   CmPAsnErr err;  /* error to be returned back to the caller */ 

   TRC2(nhAcBuildUpLinkTrfr)

   sMem.region = 0;
   sMem.pool = 0;
   fLen = 0;

   UE_RRC_ALLOC_MBUF(DFLT_REGION, DFLT_POOL, mBuf);
   /* ue002.101: kworks_fix */
   if(mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }

   UE_RRC_ALLOC_EVNT(&pdu, sizeof(NhuDatReqSdus),&sMem, UE_RRC_BLKSZ);
   if (NULLP == pdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE113, (ErrVal)0,
        "ueRRCBuildUpLinkTrfr: cmAllocEvnt Failed \n");
      RETVALUE(RFAILED);
   }

   upLinkTrfrMsg = &(pdu->sdu.m.ulDcchMsg.dcchMsg);

   FILL_U8_U32_TKN(upLinkTrfrMsg->pres, TRUE, 1);
   FILL_U8_U32_TKN(upLinkTrfrMsg->message.choice,TRUE, 0);
   /* To fill c1 */
   if(!(upLinkTrfrMsg->message.choice.val))
   {
      /* this is for Uplink Transfer */
      FILL_U8_U32_TKN(upLinkTrfrMsg->message.val.c1.choice,TRUE, C1_ULINFOTFR);
      if(upLinkTrfrMsg->message.val.c1.choice.val == C1_ULINFOTFR)
      {
         FILL_U8_U32_TKN(upLinkTrfrMsg->message.val.c1.val.ulInfoTfr.pres,TRUE, 1);
         critex = &(upLinkTrfrMsg->message.val.c1.val.ulInfoTfr.criticalExtns);

         FILL_U8_U32_TKN(critex->choice,TRUE, 0);
         if (!(critex->choice.val))
         {
            FILL_U8_U32_TKN(critex->val.c1.choice,TRUE, 0);
            FILL_U8_U32_TKN(critex->val.c1.val.ulInfoTfr_r8.pres,TRUE, 1);

            FILL_U8_U32_TKN(critex->val.c1.val.ulInfoTfr_r8.dedicatedInfoTyp.choice,TRUE, 0);
            if (!(critex->val.c1.val.ulInfoTfr_r8.dedicatedInfoTyp.choice.val))
            {
                FILL_OCT_STR(critex->val.c1.val.ulInfoTfr_r8.dedicatedInfoTyp.val.dedicatedInfoNAS,1,1,pdu);
            }
            else
            {
               /* CDMA 2000 */
               /* Octet String */
            }

            FILL_U8_U32_TKN(critex->val.c1.val.ulInfoTfr_r8.nonCriticalExtn.pres,TRUE, 1);
         }
         else
         {
         }
      }
      else
      {
         /* Invalid message type */
      }
   }
   else
   {
      FILL_U8_U32_TKN(upLinkTrfrMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }




   /* Encode the message */
   ret = cmPAsnEncMsgUalign ((TknU8*)(upLinkTrfrMsg), CM_PASN_USE_MBUF, 
            (Void *)(*mBuf),0, nhUL_DCCH_Pdu, &err, &fLen, dbgFlag, TRUE);
   if (ret != ROK) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE114, (ErrVal)0,
        "ueRRCBuildUpLinkTrfr: PASN Lib encoding failed\n");
      SPrint(  pbuf  );
      RETVALUE(RFAILED);
   } 
   else 
   {
      UE_DBGP_INFO((UE_PRNTBUF,
       "ueRRCBuildUpLinkTrfr :  PASN Lib encoding done"));
   }

   RETVALUE (ROK);
}


/**
 * @brief Decodes the RRC message using the cm_pasn library.
 * 
 * @details 
 *   
 *
 * This function decodes the buffer received from the lower layer
 * into RRC message to be sent RRC user. 
 * 
 * @param[in] mBuf         Buffer to be decoded
 * @param[in] lcId         lcId
 *
 * @return S16
 *  -# ROK
 *  -# RFAILED
*/
#ifdef ANSI
PUBLIC S16 ueRrcDecRRCMsgs
(
U8      lcId,
NhuDatIndSdus  *datIndSdu,
Void    *pdu,
Buffer  *mBuf
)
#else
PUBLIC S16 ueRrcDecRRCMsgs(lcId,datIndSdu, pdu, mBuf)
U8        lcId;
NhuDatIndSdus  *datIndSdu;
Void    *pdu;
Buffer    *mBuf;
#endif
{
   S16            ret=ROK;
   U32            numDecOct; /* Number of octets decoded */
   U8             dbgFlag=TRUE; /* Debug flag encode/decode library */
   CmPAsnErr      err;      /* PASN error code */
   CmPAsnElmDef   **elmDef=NULLP;

   TRC2(ueRrcDecRRCMsgs)


   /* Initialize PASN error code */
   err.errCode = 0;

   switch(lcId)
   {
      case 1:
         elmDef = nhDL_DCCH_Pdu;
         pdu = (Void *)(&(datIndSdu->sdu.m.dlDcchMsg.dcchMsg));
         break;

/* ue003.101: Drb1 and Drb2 handling */
      case UE_LC_DRB1:
      case UE_LC_DRB2:
         elmDef = nhDL_CCCH_Pdu;
         pdu = (Void *)(&(datIndSdu->sdu.m.dlCcchMsg.ccchMsg));
         break;

     
      default:
         RETVALUE(RFAILED);
   }

   /* Calling PASN library decode function */
   ret = cmPAsnDecMsgUalign ((Void*)pdu, CM_PASN_USE_MBUF, (Void **)&mBuf,
                            &numDecOct, 0, elmDef, CM_PASN_GEN_ERR, &err, 
                            UE_RRC_BLKSZ, (CmMemListCp *)datIndSdu, 
                            dbgFlag);
    
   if (ROK != ret)
   {
      UE_RRC_FREE_EVNT(datIndSdu);
      RETVALUE(ret);
   }

   RETVALUE(ROK);

} /* ueRrcDecRRCMsgs */
#ifdef TOTAL_ENB
U16 send_measu_report = TRUE;
/* ue009.101 : Added support to send Measurement report */
/*
 *
 *       Fun:    ueRrcPrcMeasCfg
 *
 *       Desc:   Process the incoming Measurement Configuration
 *
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PUBLIC S16  ueRrcPrcMeasCfg
(
UeAppCb       *ueAppCb,
NhuMeasConfig *measCfg
)
#else
PUBLIC S16  ueRrcPrcMeasCfg(ueAppCb, measCfg)
UeAppCb       *ueAppCb;
NhuMeasConfig *measCfg;
#endif
{
   U16          idx;
   U32          noComp;
   UeMeasCfg    *ueMeasCfg;
   NhuMeasIdToAddModLst *addModLst = &(measCfg->measIdToAddModLst);
   NhuMeasIdToRemoveLst *remLst    = &(measCfg->measIdToRemoveLst);
   U32          noMeasIds;
   U32          *newMeasIdLst;

   noComp = addModLst->noComp.val;
   if(noComp)
   {
      ueMeasCfg = measCfg; 
      NhuDatReqSdus *pdu;
      if(ROK != ueRrcBuildMeasRpt(ueAppCb, &pdu, measCfg))
      {
         printf("\n Building of measurement report failed \n");
         RETVALUE(RFAILED);
      }
      if (send_measu_report == TRUE)
      {
         printf("\nSending Measurement report...\n");
         ueAppLimSndRRCMsg(pdu, ueAppCb);
      }
      else
      {
         /* discard config if remove list is present */
         if(remLst->noComp.val)
         {
            printf("\nremove list prsnt in first measurement configuration\n");
            /* freeing the parsed info */
            UE_FREE(newMeasIdLst, noComp * sizeof(U32));
         }
         printf("\nupdating meas config for the first time\n");
         ueMeasCfg->cfgPres    = TRUE;
         ueMeasCfg->noMeasIds  = noComp;
         ueMeasCfg->measIdLst  = newMeasIdLst;
      }
   }
RETVALUE(ROK);
}
#endif /* ifdef TOTAL_ENB */

/* ue008.101: Modified function ueRrcBuildMeasRpt(). */
/*
 *
 *       Fun:    ueRrcBuildMeasRpt
 *
 *       Desc:   Build RRC CMeasurement Report
 *
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef TOTAL_ENB
#ifdef ANSI
PUBLIC S16  ueRrcBuildMeasRpt
(
UeAppCb       *ueAppCb,
NhuDatReqSdus **pdu,
NhuMeasConfig *measCfg
)
#else
PUBLIC S16  ueRrcBuildMeasRpt(ueAppCb, pdu, measCfg)
UeAppCb       *ueAppCb;
NhuDatReqSdus **pdu;
NhuMeasConfig *measCfg;
#endif
#else /* #ifdef TOTAL_ENB */
#ifdef ANSI
PUBLIC S16  ueRrcBuildMeasRpt
(
NhuDatReqSdus **pdu
)
#else
PUBLIC S16  ueRrcBuildMeasRpt(pdu)
NhuDatReqSdus **pdu;
#endif
#endif /* #ifdef TOTAL_ENB */
{
   NhuDatReqSdus  *tmpPdu           = NULLP;
   NhuUL_DCCH_Msg       *ulDcchMsg     = NULLP;
   NhuMeasurementReport_r8_IEs  *r8Ie    = NULLP;
   /* ue010.101 : Enhanced measurement feature */
   NhuMeasurementReport_r8_IEs  *r8Ie1    = NULLP; 

   Mem  sMem;
#ifdef TOTAL_ENB
   NhuMeasResultLstEUTRA *eutraMeasRes;
#endif
   U32  fLen;      /* Length of static buffer, if applicable */

   TRC2(ueRrcBuildMeasRpt)

   sMem.region = 0;
   sMem.pool = 0;
   fLen = 0;


   UE_RRC_ALLOC_EVNT(&tmpPdu, sizeof(NhuDatReqSdus), &sMem, UE_RRC_BLKSZ);
   /* ue002.101: kworks_fix */
   if(pdu == NULLP)
   {
      RETVALUE(RFAILED);
   }

   tmpPdu->sdu.msgCategory = NHU_MSG_ULDCCH;

   ulDcchMsg = &(tmpPdu->sdu.m.ulDcchMsg.dcchMsg);
   FILL_U8_U32_TKN(ulDcchMsg->pres, TRUE, PRSNT_DEF);
   FILL_U8_U32_TKN(ulDcchMsg->message.choice, TRUE, UL_DCCH_MSGTYP_C1);

   r8Ie = &(ulDcchMsg->message.val.c1.val.measurementReport.criticalExtns.\
         val.c1.val.measurementReport_r8);

/* ue010.101: Enhanced measurement feature */
#ifdef TOTAL_ENB 
   /* ue010.101 : Enhanced measurement feature */
   r8Ie1 = &(ulDcchMsg->message.val.c1.val.measurementReport.criticalExtns.\
         val.c1.val.measurementReport_r8);

   /* Fill c1 */
   if(ulDcchMsg->message.choice.val == UL_DCCH_MSGTYP_C1)
   {
      FILL_U8_U32_TKN(ulDcchMsg->message.val.c1.choice,TRUE,
            C1_MEASUREMENTREPORT);
      FILL_U8_U32_TKN(ulDcchMsg->message.val.c1.val.\
            measurementReport.pres, PRSNT_NODEF, TRUE);

      FILL_U8_U32_TKN(ulDcchMsg->message.val.c1.val.measurementReport.\
            criticalExtns.choice, TRUE, CRITICALEXTNS_C1);
      FILL_U8_U32_TKN(ulDcchMsg->message.val.c1.val.measurementReport.\
            criticalExtns.val.c1.choice, TRUE, C1_MEASUREMENTREPORT_R8);

      if(measCfg->pres.pres == TRUE)
      {
         U16 temp_noComp;
         U32 measid = 0;
         U16 measidcounter = 0;
         U16 idx = 0;
         NhuReportConfigToAddModreportConfig  *reportConfig;
         NhuMeasObjectToAddModmeasObject *measObject;

         if(measCfg->measIdToAddModLst.noComp.pres == TRUE)
         {
            for(measidcounter = 0; measidcounter < measCfg->measIdToAddModLst.noComp.val; measidcounter++)
            {
               if(measCfg->measIdToAddModLst.member[measidcounter].pres.pres == TRUE)
               {
                  measid = measCfg->measIdToAddModLst.member[measidcounter].measId.val;

                  if(measCfg->reportConfigToAddModLst.noComp.pres == TRUE)
                  {
                     temp_noComp = measCfg->reportConfigToAddModLst.noComp.val;

                     for (idx = 0; idx < temp_noComp; idx++)
                     {
                        reportConfig = ueExtractReportCfgObj(measCfg->measIdToAddModLst. \
                              member[measidcounter].reportConfigId.val, &measCfg->reportConfigToAddModLst);
                        if(reportConfig == NULL)
                        {
                           printf("UESIM->ERROR: measCfg->reportConfigToAddModLst structure is NULL\n"); 
                           RETVALUE(RFAILED);
                        }

                        if((reportConfig->choice.pres == TRUE) &&  
                              reportConfig->choice.val == REPORTCONFIG_REPORTCONFIGEUTRA)
                        {
                           if(reportConfig->val.reportConfigEUTRA.triggerTyp.choice.val == TRIGGERTYP_PERIODICAL)
                           {
                              if( reportConfig->val.reportConfigEUTRA.triggerTyp.val.periodical.
                                    purpose.val == NhuReportConfigEUTRAtriggerTypperiodicalpurposereportStrongestCellsEnum)
                              {
                                 if((uefillrrcMeasurementIE(r8Ie1, &reportConfig->val.reportConfigEUTRA, measid,
                                             NhuReportConfigEUTRAtriggerTypperiodicalpurposereportStrongestCellsEnum,
                                             1, tmpPdu)) != ROK)
                                 {
                                    printf("Failed to build measurement report for strongest cell purpose\n");
                                    RETVALUE(RFAILED);
                                 } 
                              }
                              else if( reportConfig->val.reportConfigEUTRA.triggerTyp.val.periodical.
                                    purpose.val == NhuReportConfigEUTRAtriggerTypperiodicalpurposereportCGIEnum )
                              {

                                 measObject= ueExtractmeasObj(measCfg->measIdToAddModLst. \
                                       member[measidcounter].measObjectId.val, &measCfg->measObjectToAddModLst);
                                 if(measObject == NULL)
                                 {
                                    printf("UESIM->ERROR: measCfg->measObjectToAddModLst structure is null\n");
                                    RETVALUE(RFAILED);
                                 }

                                 if((uefillrrcMeasurementIE(r8Ie1, &reportConfig->val.reportConfigEUTRA, measid, 
                                             NhuReportConfigEUTRAtriggerTypperiodicalpurposereportCGIEnum,
                                             measObject->val.measObjectEUTRA.cellForWhichToReportCGI.val, tmpPdu )) != ROK)
                                 {
                                    printf("Failed to fill measurement report for CGI purpose\n");
                                    RETVALUE(RFAILED);
                                 }
                              }
                           } /* if(reportConfig->reportConfigEUTRA....== TRIGGERTYP_PERIODICAL)  */
                           else if(reportConfig->val.reportConfigEUTRA.triggerTyp.choice.val == TRIGGERTYP_EVENT)
                           {
                              /* if send_measu_report variable is TRUE than only send measurement report */
                              send_measu_report = FALSE;
                              printf("\n currently events A1, A2, A3,,,,, A5 not supported \n");
                              RETVALUE(ROK);
                           }
                        } /* if(reportConfig->choice.val == REPORTCONFIG_REPORTCONFIGEUTRA)  */
                        else
                        {
                           printf("\n UESIM: Report Config Inter RAT not supported \n");
                           RETVALUE(RFAILED);
                        }
                     } /* for (idx = 0; idx < temp_noComp; idx++)  */

                  } /* if(measCfg->reportConfigToAddModLst.noComp.pres == TRUE) */

               }/* if(measCfg->measIdToAddModLst.member[measidcounter]->pres.pres == TRUE) */

            } /* for(measidcounter = 0; measidcounter < measCfg->noComp.val;   */

         } /* if(measCfg->noComp.pres == TRUE)  */
      }
      else 
      {
         printf("No measurement ID's are present in Measurement configuration structure \n");
         RETVALUE(RFAILED);
      }
   }
   else
   {
      FILL_U8_U32_TKN(ulDcchMsg->message.choice,TRUE,
            UL_DCCH_MSGTYP_MESSAGECLASSEXTN);
      FILL_U8_U32_TKN(ulDcchMsg->message.val.messageClassExtn.choice, FALSE, 0);
   }

#else 
   if(ulDcchMsg->message.choice.val == UL_DCCH_MSGTYP_C1)
   {
      FILL_U8_U32_TKN(ulDcchMsg->message.val.c1.choice,TRUE,
            C1_MEASUREMENTREPORT);
      FILL_U8_U32_TKN(ulDcchMsg->message.val.c1.val.\
            measurementReport.pres,TRUE, PRSNT_DEF);
      //measurementReport.pres,TRUE, PRSNT_NODEF);

      FILL_U8_U32_TKN(ulDcchMsg->message.val.c1.val.measurementReport.\
            criticalExtns.choice, TRUE, CRITICALEXTNS_C10);
      FILL_U8_U32_TKN(ulDcchMsg->message.val.c1.val.measurementReport.\
            criticalExtns.val.c1.choice, TRUE, C10_MEASUREMENTREPORT_R8);

      FILL_U8_U32_TKN(r8Ie->pres, TRUE, PRSNT_DEF);
      FILL_U8_U32_TKN(r8Ie->measResults.pres, TRUE, PRSNT_DEF);
      FILL_U8_U32_TKN(r8Ie->measResults.measId, TRUE, 1);

      FILL_U8_U32_TKN(r8Ie->measResults.measResultPCell.pres, TRUE,
            PRSNT_DEF);
      //PRSNT_NODEF);
      FILL_U8_U32_TKN(r8Ie->measResults.measResultPCell.rsrpResult, TRUE,
            20);
      FILL_U8_U32_TKN(r8Ie->measResults.measResultPCell.rsrqResult, TRUE,
            30);
   }
   else
   {
      FILL_U8_U32_TKN(ulDcchMsg->message.choice,TRUE,
            UL_DCCH_MSGTYP_MESSAGECLASSEXTN);
      FILL_U8_U32_TKN(ulDcchMsg->message.val.messageClassExtn.pres,TRUE,
            PRSNT_NODEF);
   }

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.choice,TRUE,MEASRESULTNEIGHCELLS_MEASRESULTLSTEUTRA);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.measResultLstEUTRA.noComp,TRUE,2);

   UE_RRC_GET_MEM(tmpPdu, (r8Ie->measResults.measResultNeighCells.val.
            measResultLstEUTRA.noComp.val * sizeof(NhuMeasResultEUTRA)), 
         &r8Ie->measResults.measResultNeighCells.val.measResultLstEUTRA.member);

   /* TEST_FIX */
   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[0].pres, TRUE, PRSNT_NODEF);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[0].physCellId,TRUE,2);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         //easResultLstEUTRA.member[0].cgi_Info.pres,FALSE,NOTPRSNT);
      measResultLstEUTRA.member[0].cgi_Info.pres,FALSE,NOTPRSNT);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[0].measResult.pres,TRUE,PRSNT_NODEF);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[0].measResult.rsrpResult,TRUE,45);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[0].measResult.rsrqResult,TRUE,25);

   /* TEST_FIX */
   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[1].pres, TRUE, PRSNT_NODEF);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[1].physCellId,TRUE,101);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[1].cgi_Info.pres,FALSE,NOTPRSNT);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[1].measResult.pres,TRUE,PRSNT_NODEF);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[1].measResult.rsrpResult,TRUE,44);

   FILL_U8_U32_TKN(r8Ie->measResults.measResultNeighCells.val.
         measResultLstEUTRA.member[1].measResult.rsrqResult,TRUE,24);
#endif
   *pdu = tmpPdu; 
   send_measu_report = TRUE; 
   printf("\n ---------Meas Rprt buit-------\n");
  RETVALUE(ROK);  
}
/*
 *
 *       Fun:   ueExtractReportCfgObj 
 *
 *       Desc:  Extract reportconfig object using reportconfigID 
 *
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PUBLIC NhuReportConfigToAddModreportConfig* ueExtractReportCfgObj
(
 U32 reportConfigID, 
 NhuReportConfigToAddModLst *reportConfigToAddModLst
) 
#else
PUBLIC NhuReportConfigToAddModreportConfig* ueExtractReportCfgObj(reportConfigID, reportConfigToAddModLst)
U32 reportConfigID;
NhuReportConfigToAddModLst *reportConfigToAddModLst;
#endif
{
   U8 i = 0;

   for (i = 0; i < reportConfigToAddModLst->noComp.val; i++)
   {
      if((reportConfigToAddModLst->member[i].pres.pres == TRUE)&& 
            (reportConfigID == reportConfigToAddModLst->member[i].reportConfigId.val))
      {
              return(&reportConfigToAddModLst->member[i].reportConfig);
      }
      else
      {
         printf("\n ERROR: Requested reportConfigId not present in the list \n");
         RETVALUE(NULL);
      }
   }

}
/*
 *
 *       Fun: ueExtractmeasObj  
 *
 *       Desc:  Extract measurement object using measurement config ID 
 *
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PUBLIC NhuMeasObjectToAddModmeasObject* ueExtractmeasObj 
(
 U32 measObjectId, 
 NhuMeasObjectToAddModLst *measObjectToAddModLst 
) 
#else
PUBLIC NhuMeasObjectToAddModmeasObject* ueExtractmeasObj(measObjectId, measObjectToAddModLst)
U32 measObjectId;
NhuMeasObjectToAddModLst *measObjectToAddModLst; 
#endif
{
   U8 i = 0;

   for (i = 0; i < measObjectToAddModLst->noComp.val; i++)
   {
      if((measObjectToAddModLst->member[i].pres.pres == TRUE)&& 
            (measObjectId ==  measObjectToAddModLst->member[i].measObjectId.val))
      {
         return(&measObjectToAddModLst->member[i].measObject);
      }
      else
      {
         printf("\n ERROR: Requested reportConfigId not present in the list \n");
         RETVALUE(NULL);
      }
   }
}
/*
 *
 *       Fun:    uefillrrcMeasurementIE 
 *
 *       Desc:   Build RRC CMeasurement Report
 *
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef TOTAL_ENB 
#ifdef ANSI
PUBLIC U16 uefillrrcMeasurementIE
(
 NhuMeasurementReport_r8_IEs  *r8Ie1,
 NhuReportConfigEUTRA  *reportConfigEUTRA,
 U32 measId,
 U8 purpose,
 U32 PhyCellid,
 NhuDatReqSdus  *tmpPdu
)
#else
PUBLIC U16 uefillrrcMeasurementIE(r8Ie1, reportConfigEUTRA, measId, purpose)
NhuMeasurementReport_r8_IEs  *r8Ie1;
NhuReportConfigEUTRA  *reportConfigEUTRA;
U32 measId;
U8 purpose;
U32 PhyCellid;
NhuDatReqSdus  *tmpPdu;
#endif
{
	NhuMeasResultEUTRA  *member      = NULLP;
	NhuMCC_MNC_Digit    *member1_mcc     = NULLP;
	NhuMCC_MNC_Digit    *member2_mcc     = NULLP;
	NhuMCC_MNC_Digit    *member1_mnc     = NULLP;
	NhuMCC_MNC_Digit    *member2_mnc     = NULLP;
	NhuPLMN_Identity    *member1 = NULLP; 
	U16 idx = 0;
	U32 mcc_bits[3], mcc = 0;
	U32 mnc_bits[3], mnc = 0;

	printf("\nuefillrrcMeasurementIE: Building mesuremnt report\n");  
	/* if purpose is strongest cells build PCI, RSRP and RSRQ value in measurement report */
	if(purpose == NhuReportConfigEUTRAtriggerTypperiodicalpurposereportStrongestCellsEnum)
	{
		/* Currently we are sipporting for 10 cells */
		if (reportConfigEUTRA->maxReportCells.val > 10)
		{
			printf("\n configratuion file does not have requested no of cell information\n");
			RETVALUE(RFAILED);
		}
		else
		{
			printf("\nuefillrrcMeasurementIE: Building mesuremnt report for strongest cells \n");  
			/* Filling serving cell RSRP and RSRQ */
			FILL_U8_U32_TKN(r8Ie1->pres, PRSNT_NODEF, 1);
			FILL_U8_U32_TKN(r8Ie1->measResults.pres, PRSNT_NODEF, 1);
			FILL_U8_U32_TKN(r8Ie1->measResults.measId, PRSNT_NODEF, measId);
			FILL_U8_U32_TKN(r8Ie1->measResults.measResultPCell.pres, PRSNT_NODEF, 1);
			FILL_U8_U32_TKN(r8Ie1->measResults.measResultPCell.rsrpResult, 
					PRSNT_NODEF, uenetworkparam->ueenbrsrp.ys_enb1_rsrp);
			FILL_U8_U32_TKN(r8Ie1->measResults.measResultPCell.rsrqResult, 
					PRSNT_NODEF, uenetworkparam->ueenbrsrq.ys_enb1_rsrq);
			FILL_U8_U32_TKN(r8Ie1->nonCriticalExtn.pres, NOTPRSNT, 0);
			FILL_U8_U32_TKN(r8Ie1->measResults.extaddgrp_1.pres, NOTPRSNT, 0);
			/*
			   UE_RRC_ALLOC_EVNT(&tmpPdu, sizeof(NhuDatReqSdus), &sMem, UE_RRC_BLKSZ);
			   tmpPdu->sdu.msgCategory = NHU_MSG_ULDCCH; */
			UE_RRC_GET_MEM(tmpPdu, (reportConfigEUTRA->maxReportCells.val * sizeof(NhuMeasResultEUTRA)),
					&r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member);

			member = r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member;

			FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.choice, PRSNT_NODEF, 
					REPORTCONFIG_REPORTCONFIGEUTRA);
			/* Nocomp */
			FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.noComp, PRSNT_NODEF, 
					1/*reportConfigEUTRA->maxReportCells.val*/);
			/* Filling neighbouring cell information */
			for (idx = 0; idx < 1 ;/*reportConfigEUTRA->maxReportCells.val;*/ idx++)
			{
				/* filling phsysical cell ID */
				FILL_U8_U32_TKN(member[idx].pres, PRSNT_NODEF, 1);
				FILL_U8_U32_TKN(member[idx].physCellId, PRSNT_NODEF, PhyCellid);
				FILL_U8_U32_TKN(member[idx].measResult.pres, PRSNT_NODEF, 1);
				FILL_U8_U32_TKN(member[idx].measResult.rsrpResult, PRSNT_NODEF, uenetworkparam->ueenbrsrp.ys_enb2_rsrp);
				FILL_U8_U32_TKN(member[idx].measResult.rsrqResult, PRSNT_NODEF, uenetworkparam->ueenbrsrq.ys_enb2_rsrq);
				FILL_U8_U32_TKN(member[idx].measResult.extaddgrp_1.pres, NOTPRSNT, 0);
			} 
		}
	}
	/* if Purpose is CGI build add PCI and ECGI info in the measurement report */
	else if (purpose == NhuReportConfigEUTRAtriggerTypperiodicalpurposereportCGIEnum )
	{
		printf("\nuefillrrcMeasurementIE: Building mesuremnt report CGI \n");  
		FILL_U8_U32_TKN(r8Ie1->pres, PRSNT_NODEF, 1);
		FILL_U8_U32_TKN(r8Ie1->nonCriticalExtn.pres, NOTPRSNT, 0);
		FILL_U8_U32_TKN(r8Ie1->measResults.pres, PRSNT_NODEF, 1);
		FILL_U8_U32_TKN(r8Ie1->measResults.measId, PRSNT_NODEF, measId);
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultPCell.pres, PRSNT_NODEF, 1);
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultPCell.rsrpResult, 
				PRSNT_NODEF, uenetworkparam->ueenbrsrp.ys_enb1_rsrp);
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultPCell.rsrqResult, 
				PRSNT_NODEF, uenetworkparam->ueenbrsrq.ys_enb1_rsrq);

		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.choice, PRSNT_NODEF, REPORTCONFIG_REPORTCONFIGEUTRA);
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.noComp, PRSNT_NODEF,1);

		UE_RRC_GET_MEM(tmpPdu, (r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.noComp.val * 
					sizeof(NhuMeasResultEUTRA)), &r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member);
		/* filling Physical cell ID */
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].pres, PRSNT_NODEF,1);
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].physCellId, PRSNT_NODEF, 1);
		/* Filling CGI info */
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].cgi_Info.pres, PRSNT_NODEF,1);
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].cgi_Info.cellGlobalId.pres , PRSNT_NODEF,1);

		/* filling CGI info */
		/* filling plmn_identity inside cellglobal ID */
		/**** start cell Global ID ******/
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].cgi_Info.cellGlobalId.plmn_Identity.pres, PRSNT_NODEF,1);

		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].cgi_Info.cellGlobalId.plmn_Identity.mcc.noComp, PRSNT_NODEF,3);

		UE_RRC_GET_MEM(tmpPdu, ((r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
						cgi_Info.cellGlobalId.plmn_Identity.mcc.noComp.val) * sizeof(NhuMCC_MNC_Digit)) , &(r8Ie1->measResults.
						measResultNeighCells.val.measResultLstEUTRA.member[0].cgi_Info.cellGlobalId.plmn_Identity.mcc.member));

		member1_mcc = r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
			cgi_Info.cellGlobalId.plmn_Identity.mcc.member; 

		mcc = uenetworkparam->ueenbmcc.ys_enb1_mcc;

		for (idx = 0; idx < 3; idx++)
		{
			mcc_bits[idx] = (mcc%10);
			mcc = mcc/10;
		}
		member1_mcc[0].pres = PRSNT_NODEF;
		member1_mcc[0].val = mcc_bits[2];
		member1_mcc[1].pres = PRSNT_NODEF;
		member1_mcc[1].val = mcc_bits[1];
		member1_mcc[2].pres = PRSNT_NODEF;
		member1_mcc[2].val = mcc_bits[0];

		/* Filling mnc value */
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].cgi_Info.cellGlobalId.plmn_Identity.mnc.noComp, PRSNT_NODEF,2);

		UE_RRC_GET_MEM(tmpPdu, ((r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
						cgi_Info.cellGlobalId.plmn_Identity.mnc.noComp.val)* sizeof(NhuMCC_MNC_Digit)) , &r8Ie1->measResults.
				measResultNeighCells.val.measResultLstEUTRA.member[0].cgi_Info.cellGlobalId.plmn_Identity.mnc.member);

		member1_mnc = r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
			cgi_Info.cellGlobalId.plmn_Identity.mnc.member;

		mnc  = uenetworkparam->ueenbmnc.ys_enb1_mnc;

		for (idx = 0; idx < 2; idx++)
		{
			mnc_bits[idx] = (mnc%10);
			mnc = mnc/10;
		}
		member1_mnc[0].pres = PRSNT_NODEF;
		member1_mnc[0].val = mnc_bits[1];
		member1_mnc[1].pres = PRSNT_NODEF;
		member1_mnc[1].val = mnc_bits[0];

		/* filling cell identity */
		ueAppUtlFillTknStrBSXL(&r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.
				member[0].cgi_Info.cellGlobalId.cellIdentity, 28, 
				uenetworkparam->ueenbeci.ys_enb1_eci, tmpPdu);
		printf("\n filled Cell identity \n");
		/*** End of cell global ID */

		/*** Start TRacking area code ***/
		/* Tracking area code */
		ueAppUtlFillTknStrBSXL(&r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.
				member[0].cgi_Info.trackingAreaCode, 16, 
				uenetworkparam->ueenbtac.ys_enb1_tac , tmpPdu);

		printf("\n filled Tracking area code \n");

		/**** END tracking area code */
		/*** start measresult->extaddgrp_1  ***/
		/* PLMN Identity list */ 
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].measResult.pres, PRSNT_NODEF ,1);

		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].measResult.extaddgrp_1.pres , NOTPRSNT,0);
		/**** END measresult->extaddgrp_1 ***/

		/****** Start PLMN Idnetity List*********/

		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].cgi_Info.plmn_IdentityLst.noComp, PRSNT_NODEF, 2);

		UE_RRC_GET_MEM(tmpPdu, (r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
					cgi_Info.plmn_IdentityLst.noComp.val * sizeof(NhuPLMN_Identity)), &(r8Ie1->measResults.
					measResultNeighCells.val.measResultLstEUTRA.member[0].cgi_Info.plmn_IdentityLst.member));

		/* filling mcc value */ 
		for (idx = 0; idx < 2; idx++)
		{
			FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.
					member[0].cgi_Info.plmn_IdentityLst.member[idx].pres, PRSNT_NODEF, 1);

			FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
					val.measResultLstEUTRA.member[0].cgi_Info.plmn_IdentityLst.member[idx].mcc.noComp, PRSNT_NODEF,3);

			UE_RRC_GET_MEM(tmpPdu, ((r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
							cgi_Info.plmn_IdentityLst.member[idx].mcc.noComp.val) * sizeof(NhuMCC_MNC_Digit)) , 
					&(r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
						cgi_Info.plmn_IdentityLst.member[idx].mcc.member));

		}
		member1 = r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
			cgi_Info.plmn_IdentityLst.member;

		mcc = uenetworkparam->ueenbmcc.ys_enb2_mcc;
		for (idx = 0; idx < 3; idx++)
		{
			mcc_bits[idx] = (mcc%10);
			mcc = mcc/10;
		}
		member1[0].mcc.member[0].pres = PRSNT_NODEF;
		member1[0].mcc.member[0].val  = mcc_bits[2];
		member1[0].mcc.member[1].pres = PRSNT_NODEF;
		member1[0].mcc.member[1].val  = mcc_bits[1];
		member1[0].mcc.member[2].pres = PRSNT_NODEF;
		member1[0].mcc.member[2].val  = mcc_bits[0];

		mcc  = uenetworkparam->ueenbmcc.ys_enb3_mcc;
		for (idx = 0; idx < 3; idx++)
		{
			mcc_bits[idx] = (mcc%10);
			mcc = mcc/10;
		}
		member1[1].mcc.member[0].pres = PRSNT_NODEF;
		member1[1].mcc.member[0].val  = mcc_bits[2];
		member1[1].mcc.member[1].pres = PRSNT_NODEF;
		member1[1].mcc.member[1].val  = mcc_bits[1];
		member1[1].mcc.member[2].pres = PRSNT_NODEF;
		member1[1].mcc.member[2].val  = mcc_bits[0];

		/* Filling mnc value */
		for (idx = 0; idx < 2; idx++)
		{

			FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
					val.measResultLstEUTRA.member[0].cgi_Info.plmn_IdentityLst.member[idx].pres, PRSNT_NODEF,2);

			FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
					val.measResultLstEUTRA.member[0].cgi_Info.plmn_IdentityLst.member[idx].mnc.noComp, PRSNT_NODEF,2);

			UE_RRC_GET_MEM(tmpPdu, ((r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
							cgi_Info.plmn_IdentityLst.member[idx].mnc.noComp.val) * sizeof(NhuMCC_MNC_Digit)) , 
					&(r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
						cgi_Info.plmn_IdentityLst.member[idx].mnc.member));
		}
		member1 = r8Ie1->measResults.measResultNeighCells.val.measResultLstEUTRA.member[0].
			cgi_Info.plmn_IdentityLst.member; 
		mnc = uenetworkparam->ueenbmnc.ys_enb2_mnc;
		for (idx = 0; idx < 2; idx++)
		{
			mnc_bits[idx] = (mnc%10);
			mnc = mnc/10;
		}
		member1[0].mnc.member[0].pres = PRSNT_NODEF;
		member1[0].mnc.member[0].val  = mnc_bits[1];
		member1[0].mnc.member[1].pres = PRSNT_NODEF;
		member1[0].mnc.member[1].val  = mnc_bits[0];

		mnc = uenetworkparam->ueenbmnc.ys_enb3_mnc;
		for (idx = 0; idx < 2; idx++)
		{
			mnc_bits[idx] = (mnc%10);
			mnc = mnc/10;
		}
		member1[1].mnc.member[0].pres = PRSNT_NODEF;
		member1[1].mnc.member[0].val  = mnc_bits[1];
		member1[1].mnc.member[1].pres = PRSNT_NODEF;
		member1[1].mnc.member[1].val  = mnc_bits[0];

		/***  End of PLMN identity list */

		/* NOTE: Filling some random RSRP and RSRQ value, 
       * This RSRP and RSRQ value has to come from the uesim_cfg.txt file */	
		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].measResult.rsrpResult , PRSNT_NODEF , 20);

		FILL_U8_U32_TKN(r8Ie1->measResults.measResultNeighCells.
				val.measResultLstEUTRA.member[0].measResult.rsrqResult , PRSNT_NODEF , 30);

	}
	RETVALUE(ROK);
}
#endif
/* 
 *
 *       Fun:    ueRrcEncRRCMsg
 *
 *       Desc:   Encodes the RRC Message.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRrcEncRRCMsg
(
U8               msgCategory,
NhuDatReqSdus   *datReqSdu,
Buffer         **mBuf
)
#else
PUBLIC S16 ueRrcEncRRCMsg(msgCategory, datReqSdu, mBuf)
U8               msgCategory;
NhuDatReqSdus   *datReqSdu;
Buffer         **mBuf;
#endif
{
   CmPAsnElmDef   **elmDef=NULLP;
   CmPAsnErr        err;  /* error to be returned back to the caller */ 
   Void            *pdu = NULLP;
   Bool             dbgFlag = TRUE;  /* Debug Flag */ 
   U32              fLen;      /* Length of static buffer, if applicable */
   S16              ret;
   
   TRC2(ueRrcEncRRCMsg)

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueRrcEncRRCMsg:   Received message of category %d",msgCategory));

   switch(msgCategory)
   {
      case NHU_MSG_ULCCCH:
      {
         elmDef = nhUL_CCCH_Pdu;
         pdu = (Void *)(&(datReqSdu->sdu.m.ulCcchMsg.ccchMsg));
         break;
      }
      case NHU_MSG_ULDCCH:
      {
         elmDef = nhUL_DCCH_Pdu;
         pdu = (Void *)(&(datReqSdu->sdu.m.ulDcchMsg.dcchMsg));
         break;
      }
      default:
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE116, (ErrVal)msgCategory,
            "ueRrcEncRRCMsg: Unrecognized message categeory to encode\n");
         RETVALUE(RFAILED);
      }
   }

   UE_RRC_ALLOC_MBUF(DFLT_REGION, DFLT_POOL, mBuf);
   if(NULLP == mBuf) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE117, (ErrVal)msgCategory,
         "ueRrcEncRRCMsg: Allocation of encoding buffer failed \
         for msgCategory\n");

      RETVALUE(RFAILED);
   }

   /* Encode the message */
   ret = cmPAsnEncMsgUalign ((TknU8*)(pdu), CM_PASN_USE_MBUF, 
            (Void *)(*mBuf),0, elmDef, &err, &fLen, dbgFlag, TRUE);
   SPrntMsg(*mBuf, 0 , 0);
   if (ret != ROK) 
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE118, (ErrVal)msgCategory,
         "ueRrcEncRRCMsg: PASN lib Encoding Failed for msgCategory\n");
      
      UE_RRC_FREE_MBUF(*mBuf);
   } 
   RETVALUE(ret);
}
/* 
 *
 *       Fun:    ueRrcDatInd
 * 
 *       Desc:   Processes the Message from Lower layer.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRrcDatInd
(
UeCb   *ueCb, 
U8     lcId, 
Buffer *mBuf
)
#else
PUBLIC S16 ueRrcDatInd(ueCb, lcId, mBuf)
UeCb   *ueCb; 
U8     lcId; 
Buffer *mBuf;
#endif

{
   TRC2(ueRrcDatInd)

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueRrcDatInd:   Processing the data indication for lcId %d ",lcId));

   if(lcId == 0) /* common channel SRB0 */
   {
      ueRrcProcessSrb0(ueCb, mBuf);
   } 
   if(lcId == 1 || lcId == 2 )
   {
      ueRrcProcessSrb12(ueCb, mBuf);
   } /* end of if statement */

  RETVALUE(ROK);
}


/* ue003.101: Paging Indication handling */
/* 
 *
 *       Fun:    ueRrcPagingInd
 * 
 *       Desc:   Processes the Paging Message from Lower layer.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRrcPagingInd
(
CellCb *cell,
Buffer *mBuf
)
#else
PUBLIC S16 ueRrcPagingInd(cell,mBuf)
CellCb *cell;
Buffer *mBuf;
#endif

{
   Mem  sMem;
   NhuDatReqSdus   *datReqSdus = NULLP;
   U32            numDecOct; /* Number of octets decoded */
   Void            *pdu       = NULLP;
   Bool dbgFlag = TRUE;  /* Debug Flag */ 
   S16           ret = ROK;
   CmPAsnErr err;  /* error to be returned back to the caller */ 
   
   TRC2(ueRrcPagingInd)

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueRrcPagingInd:   Processing the Paging Message "));

   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;

   UE_DBGP_INFO((UE_PRNTBUF, 
         "ueRrcPagingInd: Processing the DL PCCH messages "));
   UE_ALLOCEVNT((Ptr *)&datReqSdus, sizeof(NhuDatReqSdus), &sMem);
   if (NULLP == datReqSdus)
   {
      RETVALUE(RFAILED);
   }


   pdu = (Void *)(&(datReqSdus->sdu.m.pcchMsg));
 

   /* Calling PASN library decode function */
   ret = cmPAsnDecMsgUalign ((Void*)pdu, CM_PASN_USE_MBUF, (Void **)&mBuf,
                            &numDecOct, 0,(CmPAsnElmDef **)nhPCCH_Pdu, CM_PASN_GEN_ERR, &err, 
                            UE_RRC_BLKSZ, (CmMemListCp *)datReqSdus, 
                            dbgFlag);
   if(ret != ROK)
   {
      /* ue007.101: Fix to ccpu00117388 */
      /*Compilation error after ERRCLS defined in make file*/
      UELOGERROR(ERRCLS_ADD_RES, EUE118, (ErrVal)0,
         "ueRrcPagingInd: Decoding of Paging Message failed\n");
      RETVALUE(RFAILED);
   } /* end of if statement */


   ueAppRcvRRCPaging(cell->cellId,&(datReqSdus->sdu.m.pcchMsg));

   SPutMsg(mBuf);


  RETVALUE(ret);
}
/* 
 *
 *       Fun:    ueRrcSIBInd
 * 
 *       Desc:   Processes the SI Messages.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRrcSIBInd
(
Buffer *mBuf
)
#else
PUBLIC S16 ueRrcSIBInd(mBuf)
Buffer *mBuf;
#endif

{
   Mem            sMem;
   NhuDatReqSdus  *datReqSdus;
   U32            numDecOct; /* Number of octets decoded */
   Void           *pdu;
   Bool           dbgFlag = FALSE;  /* Debug Flag */ 
   S16            ret = ROK;
   CmPAsnErr      err;  /* error to be returned back to the caller */ 
   
   TRC2(ueRrcSIBInd)

   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;

   UE_RRC_ALLOC_EVNT(&datReqSdus, sizeof(NhuDatReqSdus), &sMem, UE_RRC_BLKSZ);
   if (NULLP == datReqSdus)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE105, (ErrVal)0,
         "ueRrcSIBInd: cmAllocEvnt failed for BCCH on DLSCH\n"); 
      RETVALUE(RFAILED);
   }
   pdu = (Void *) &(datReqSdus->sdu.m.bcchDlSchMsg);

   /* Decode and fill BCCH-DLSCH Structure */
   ret = cmPAsnDecMsgUalign((Void*)pdu, CM_PASN_USE_MBUF, (Void **)&mBuf,
                            &numDecOct, 0, nhBCCH_DL_SCH_Pdu, CM_PASN_GEN_ERR, &err, 
                            UE_RRC_BLKSZ, (CmMemListCp *)datReqSdus, 
                            dbgFlag);
 
   if (ret != ROK)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE105, (ErrVal)0,
         "ueRrcSIBInd: cmPAsnDecMsgUalign failed for BCCH on DLSCH\n"); 
      RETVALUE(RFAILED);
   }

   ueAppSibInd(&(datReqSdus->sdu.m.bcchDlSchMsg));

   UE_RRC_FREE_EVNT(datReqSdus);
   SPutMsg(mBuf);


  RETVALUE(ret);
}
/* 
 *
 *       Fun:    ueRrcProcessSrb0
 * 
 *       Desc:   Processes the message of SRB0.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueRrcProcessSrb0
(
UeCb          *ueCb,
Buffer        *mBuf
)
#else
PRIVATE S16 ueRrcProcessSrb0(cell,ueCb, mBuf)
UeCb   *ueCb;
Buffer *mBuf;
#endif
{

   Mem  sMem;
   NhuDatIndSdus   *datIndSdu = NULLP;  /* RRU Data Indication structure */
   Void            *pdu       = NULLP;
   Pst           appPst;


   TRC2(ueRrcProcessSrb0)
/* 1. Decode the mBuf.
   2. Inform the UE Application.
*/

   sMem.region = DFLT_REGION;
   sMem.pool = DFLT_POOL;

   UE_ALLOCEVNT((Ptr *)&datIndSdu, sizeof(NhuDatIndSdus), &sMem);
   if (NULLP == datIndSdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE119, (ErrVal)0,
         "ueRrcProcessSrb0 : cmAllocEvnt failed\n");
      RETVALUE(RFAILED);
   }

   datIndSdu->sdu.msgCategory = NHU_MSG_DLCCCH;

   UE_DBGP_INFO((UE_PRNTBUF, 
         "ueRrcProcessSrb0: Processing the DL CCCH messages "));

   pdu = (Void *)(&(datIndSdu->sdu.m.dlCcchMsg.ccchMsg));

   /* Decode RRC Message received */
   /* ue008.101: MOD: Fixed warnings for g++ compilation on Linux*/
   if ((ROK != (ueRrcDecRRCMsgs(NHU_MSG_DLCCCH, (NhuDatIndSdus *)datIndSdu, pdu, mBuf))))
   /* ue008.101: MOD_END: Fixed warnings for g++ compilation on Linux*/
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE120, (ErrVal)0,
         "ueRrcProcessSrb0 : Decoding of RRC messages failed\n");
      UE_RRC_FREE_EVNT(datIndSdu);
      RETVALUE(RFAILED);
   }

   datIndSdu->hdr.ueId = ueCb->rnti;
   datIndSdu->hdr.cellId = ueCb->cellId;

/* ue002.101: Changes to support MSPD CL */
   if((datIndSdu->sdu.msgCategory == NHU_MSG_DLCCCH) &&
      (datIndSdu->sdu.m.dlCcchMsg.ccchMsg.\
         message.val.c1.choice.val == C1_RRCCONSETUP))
   {
      NhuRadioResourceConfigDedicated *resCfgDed;
      NhuRRCConSetup *conSetUp;
      NhuPhysicalConfigDedicated  *dedCfg;

      conSetUp = &datIndSdu->sdu.m.dlCcchMsg.ccchMsg.\
                  message.val.c1.val.rrcConSetup;
      resCfgDed = &(conSetUp->criticalExtns.val.c1.val.rrcConSetup_r8.\
         radioResourceConfigDedicated);                  

      dedCfg = &resCfgDed->physicalConfigDedicated;

#if 0
      ueCb->rrcCfg = *dedCfg;
#endif

      if(dedCfg->pres.pres != NOTPRSNT)
      {
         if((dedCfg->schedulingRqstConfig.choice.pres != NOTPRSNT) &&
            (dedCfg->schedulingRqstConfig.val.setup.pres.pres != NOTPRSNT))
         {
            ueCb->srCfgInfo = &ueSrCfgDb
               [dedCfg->schedulingRqstConfig.val.setup.sr_ConfigIdx.val];
         }

         if((dedCfg->soundingRS_UL_ConfigDedicated.choice.pres != NOTPRSNT) &&
            (dedCfg->soundingRS_UL_ConfigDedicated.val.setup.pres.pres != NOTPRSNT))
         {
            ueCb->srsCfgInfo = &ueSrsCfgDb
               [dedCfg->soundingRS_UL_ConfigDedicated.val.setup.srs_ConfigIdx.val];
         }

         if((dedCfg->cqi_ReportConfig.pres.pres != NOTPRSNT) &&
            (dedCfg->cqi_ReportConfig.cqi_ReportPeriodic.val. \
               setup.pres.pres != NOTPRSNT))
         {
            ueCb->cqiCfgInfo = &ueCqiPmiCfgDb
               [dedCfg->cqi_ReportConfig.cqi_ReportPeriodic. \
                    val.setup.cqi_pmi_ConfigIdx.val];
         }

         if((dedCfg->cqi_ReportConfig.pres.pres != NOTPRSNT) &&
            (dedCfg->cqi_ReportConfig.cqi_ReportPeriodic.val. \
               setup.pres.pres != NOTPRSNT))
         {
            ueCb->riCfgInfo = &ueCqiPmiCfgDb
               [dedCfg->cqi_ReportConfig.cqi_ReportPeriodic. \
                    val.setup.ri_ConfigIdx.val];
         }
      }
   }

   /* Post a message to UE Application */
   cmMemset((U8*)&appPst, 0, sizeof(Pst));

    /* Invoking tightly coupled function directly here */
#ifndef ENB_PERF_MEAS
   UeAppLiNhuDatInd(&appPst, 0, datIndSdu);
#else
   UePerfAppLiNhuDatInd(&appPst, 0, datIndSdu);
#endif
   SPutMsg(mBuf);
   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueRrcProcessSrb12
 * 
 *       Desc:   Processes the messages of SRB1 and SRB2.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 *
 *       Notes:  None
 *
 *       File:   ue_rrc.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueRrcProcessSrb12
(
UeCb        *ueCb,
Buffer      *mBuf
)
#else
PRIVATE S16 ueRrcProcessSrb12(ueCb, mBuf)
UeCb   *ueCb;
Buffer *mBuf;
#endif

{
   Void            *pdu       = NULLP;
   NhuDatIndSdus   *datIndSdu = NULLP;  /* RRU Data Indication structure */

   /* RRC transaction identifier within UE msg */
   Mem             sMem;
   struct timespec ts;
   Pst appPst;


   TRC2(ueRrcProcessSrb12)
   ts.tv_sec  = 0;
   ts.tv_nsec = 1000000;

   sMem.region = DFLT_REGION;
   sMem.pool = UE_POOL;

   UE_ALLOCEVNT((Ptr *)&datIndSdu, sizeof(NhuDatIndSdus), &sMem);

   if (NULLP == datIndSdu)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE121, (ErrVal)0,
         "ueRrcProcessSrb12 : cmAllocEvnt failed\n");
      RETVALUE(RFAILED);
   }

   datIndSdu->sdu.msgCategory = NHU_MSG_DLDCCH;

   pdu = (Void *)(&(datIndSdu->sdu.m.dlDcchMsg.dcchMsg));

   UE_DBGP_INFO((UE_PRNTBUF, 
         "ueRrcProcessSrb12: Processing the DL DCCH messages "));

   /* ue008.101: MOD: Fixed warnings for g++ compilation on Linux*/
   if ((ROK != (ueRrcDecRRCMsgs(NHU_MSG_DLDCCH, (NhuDatIndSdus *)datIndSdu, pdu, mBuf))))
   /* ue008.101: MOD_END: Fixed warnings for g++ compilation on Linux*/
   {
      /* error handling */
      UE_RRC_FREE_EVNT(datIndSdu);
      UELOGERROR(ERRCLS_ADD_RES, EUE122, (ErrVal)0,
         "ueRrcProcessSrb12 :  Decoding Error for PDCP DatInd\n");
      RETVALUE(RFAILED);

   }
   /* ue002.101: Multi ue support changes */
   datIndSdu->hdr.ueId = ueCb->rnti;
   datIndSdu->hdr.cellId = ueCb->cellId;

   /* Inform the application to handle further */

   cmMemset((U8*)&appPst, 0, sizeof(Pst));

    SPutMsg(mBuf);

   /* Invoking tightly coupled function directly here */
#ifndef ENB_PERF_MEAS
   UeAppLiNhuDatInd(&appPst, 0, datIndSdu);
#else
   UePerfAppLiNhuDatInd(&appPst, 0, datIndSdu);
#endif

   RETVALUE(ROK);
}


/** @} */
/**********************************************************************
  
         End of file:     ue_rrc.c@@/main/1 - Sun Mar 28 22:59:26 2010
   
**********************************************************************/
 
/**********************************************************************
        Revision History:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vp      1.Initial Release.
/main/1+   ue002.101  sv      1. Multi ue support changes.
                              2. Changes to support MSPD CL.
/main/1+   ue003.101  rp      1. Paging support changes.
                              2. Changes to Connection Req Msg Building.
/main/1+   ue007.101  rk      1. Fix for DefectId: ccpu00117388
                                 Compilation error fix if ERRCLS defined.
                      ms      1. Compilation error after ERRCLS defined
                                 in make file.                              
/main/1+   ue008.101  psb     1. Fixed error for g++ compilation on Linux
                              2. Update ueAppCb with ueCb->rnti 
                              3. Modified function ueRrcBuildMeasRpt().
/main/1+   ue009.101  akaranth 1. Added support to send Measurement report.
/main/1+   ue010.101  akaranth 1. Enhanced Measurement report feature.
*********************************************************************91*/

