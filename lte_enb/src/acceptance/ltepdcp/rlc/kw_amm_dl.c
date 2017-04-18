

/********************************************************************20**
  
        Name:    RLC - AM DL module file
    
        Type:    C source file
  
        Desc:    Source code for Acknowledged Mode Module functions such as, 

                 Transmission of data/control PDUs 
                 Retransmission (Feedback in terms of status)
                 Polling
                 Assemble SDUs
                 Reception - reordering
                 Duplicate detection for byte segments
                 Reassemble SDUs
                  
        File:    gp_amm.c

        Sid:      kw_amm_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:42 2014
 
        Prg:     nm
  
*********************************************************************21*/


/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "lkw.h"           /* LKW defines */
#include "ckw.h"           /* CKW defines */
#include "kwu.h"           /* KWU defines */
#include "rgu.h"           /* RGU defines */
#include "kw_err.h"        /* Err defines */
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
#include "kw_dl.h"
#include "kw_udx.h"

/* extern (.x) include files */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */

#include "cm5.x"           /* common timer library */
#include "cm_tkns.x"       /* common tokens */
#include "cm_mblk.x"       /* common memory allocation */
#include "cm_llist.x"      /* common link list */
#include "cm_hash.x"       /* common hash list */
#include "cm_lte.x"        /* common LTE includes */
#include "cm_lib.x"        /* common memory allocation library */
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */

#include "kw.x"
#include "kw_dl.x"
#include "kw_udx.x"


/* local defines */

/* local externs */

/* forward references */
EXTERN S16 kwDlmHndlStaRsp ARGS (( KwCb  *gCb,KwDlRbCb  *rbCb,
                KwUdxStaPdu *pStaPdu, KwUdxBufLst  *rlsPduLst));

/* public variable declarations */

/* This structure holds all the global structs we need. */

/* private variable declarations */
typedef struct kwCntrlInfo
{
   U16  val;
   U8   len;
   U16  idx;
   U8   emtBits;
   U16  e1Idx;
   U16  e2Idx;   
   U8   e1eb;
}KwCntrlInfo;

typedef struct kwHdrInfo
{
   U16  val;
   U8   len;
   U8   eb;
   U8   *hdr;
   U16  idx;
   U8   pEb;
   U8   pLen;
}KwHdrInfo;

typedef struct kwExtHdr
{
   U16 val;
   U16 len;
   U8  hdr;
   U8  pLen;
}KwExtHdr;

#define KW_AM_SUC_RETX_PDU(_cb,_rbCb, _retx, _rlsPduLst) do { \
   kwAmChkSduMap(_cb,(_rbCb), (_retx)->amHdr.sn, (_retx)->sduMap, \
                 (_retx)->numSdu, _rlsPduLst); \
   kwRemRetxPdu(_cb,(_rbCb), (_retx), _rlsPduLst);\
} while(0)

#define KW_AM_RMV_HDR(_rbCb, _retx) do { \
  if ((_retx)->yetToConst == FALSE) \
  {\
     Buffer    *_tSeg; \
     SSegMsg ((_retx)->seg, (_retx)->hdrSz, &_tSeg); \
     KW_FREE_BUF((_retx)->seg); \
     (_retx)->seg = _tSeg; \
  }\
  (_rbCb)->m.amDl.estHdrSz -= retx->hdrSz;\
} while(0)

/*Pradeep - fix, added if(_bo) check to avoid BO update if BO=0*/   
#define KW_AM_SND_DSTA_RSP(_cb) do {\
   U32        _bo;\
   KW_UPD_AMBO(AMDL, _bo);\
   if (_bo)\
   kwUtlSndDStaRsp(_cb,rbCb, _bo, AMDL.estHdrSz, AMDL.cntrlBo ? TRUE : FALSE); \
} while(0)

#define KW_AM_MIN_HDR_SZ  (KW_MAC_HDR_SZ2 + KW_AM_PDU_FIXED_HDRSZ)

#define KW_ADD_BUF_TO_PDU(_pdu, _buf) do {\
   if (_pdu == NULLP) {_pdu = _buf; _buf = NULLP;}\
   else {SCatMsg(_pdu, _buf, M1M2); SPutMsg(_buf); _buf = NULLP;}\
} while(0)

#define KW_AM_ADD_SDU_TO_SDUMAP(_sdu, _size) do {\
   (_sdu)->mode.am.pduMap[(_sdu)->mode.am.numPdu++].sn = amHdr.sn; \
   sduMap[numSdu].sduId = (_sdu)->mode.am.sduId; \
   sduMap[numSdu].sduSz = (_size); \
   sduMap[numSdu].actSz = (_size);\
   sduMap[numSdu++].isSegmented = (_sdu)->mode.am.isSegmented; \
} while(0)

/* private function declarations */

PRIVATE S16  kwResegRetxPdus ARGS ((KwCb *gCb,KwDlRbCb *rbCb, 
                                          KwDatReq *kwDatReq));
PRIVATE Void kwRemRetxPdu ARGS ((KwCb *gCb, KwDlRbCb *rbCb, KwRetx *retx, KwUdxBufLst *rlsPduLst));
PRIVATE Void kwMrkRetxPdu ARGS ((KwCb *gCb,KwDlRbCb *rbCb,KwRetx *retx, KwUdxBufLst *rlsPduLst));
PRIVATE Void kwAmmSucTxPdu ARGS(( KwCb *gCb, KwDlRbCb *rbCb,KwSn  sn, KwUdxBufLst *rlsPduLst));

#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
PRIVATE Void  kwAmmCalDlIpThrPut ARGS ((KwDlRbCb *rbCb, MsgLen dataVol, S32 initialBo, MsgLen pduSz));
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */
PRIVATE S16  kwAssembleSdus ARGS ((KwCb *gCb,KwDlRbCb *rbCb, 
                                              KwDatReq *kwDatReq));
PRIVATE Bool kwChkandSetPoll ARGS ((KwCb *gCb,KwDlRbCb *rbCb, 
                                    Bool newPdu, MsgLen bufSz));
PRIVATE Bool kwCreatePdu ARGS ((KwCb *gCb,KwDlRbCb *rbCb, 
                                   KwAmHdr *amHdr, Buffer *pdu));
PRIVATE Void kwAmmEstHdrSz ARGS ((KwCb *gCb,KwAmDl *amDl, U8 type));
PRIVATE S16  kwAmmSndStaInd ARGS ((KwCb *gCb,KwDlRbCb *rbCb, KwRetx *retx));
PRIVATE S16 kwAmmSndDatCfm ARGS ((KwCb *gCb,KwDlRbCb *rbCb, U32 sduId));
PRIVATE S16 kwGetNxtRetx ARGS ((KwCb *gCb,KwAmDl *amDl, KwRetx **retx));
PRIVATE Void kwConstructAmHdr ARGS ((KwCb *gCb,KwAmHdr *amHdr, 
                               Bool isSeg, U8 *hdr, U16 *idx));
PRIVATE Void kwFormBits ARGS ((KwHdrInfo *hdrInfo));
PRIVATE Void kwUpdRemPduAck ARGS ((KwCb *gCb,KwDlRbCb *rbCb, KwSn mAckSn,
                                            CmLList *retx, KwUdxBufLst *rlsPduLst));
PRIVATE S16 kwUpdFrmTxtoRetx ARGS ((KwCb *gCb,KwAmDl *amDl, 
                                        KwRetx **retx, KwSn sn, KwUdxBufLst *rlsPduLst));
PRIVATE Void kwAmChkSduMap ARGS((KwCb *gCb,KwDlRbCb *rbCb, KwSn sn,
                                 KwSduMap *sduLst, U8 numSdu, KwUdxBufLst  *rlsPduLst));

#ifdef KW_BG_DL_PROC
PRIVATE Void kwAmmRlsPdusSet ARGS((KwDlRbCb *rbCb));
#endif /* KW_BG_DL_PROC */
/** @file gp_amm.c
@brief RLC Acknowledged Mode Module
*****************************************************************************

  AM Module contains the following funcitons:

  -  kwAmmQSdu 
  -  kwAmmProcessSdus
     -  kwAssembleDlCntrlInfo
     -  kwResegRetxPdus
     -  kwAssembleSdus
     -  kwChkandSetPoll
  -  kwAmmProcessPdus
     -  kwDlmHndlStaRsp
     -  kwTriggerStatus
     -  kwReassembleSdus
   
*******************************************************************************/
/** @addtogroup ammode */
/*@{*/

#ifdef ANSI
PUBLIC S16 kwDlmHndlStaRsp
(
KwCb                *gCb,
KwDlRbCb            *rbCb,
KwUdxStaPdu         *pStaPdu,
KwUdxBufLst         *rlsPduLst
)
#else
PUBLIC S16 kwDlmHndlStaRsp(gCb, rbCb, pStaPdu, rlsPduLst)
KwCb               *gCb;
KwDlRbCb           *rbCb;
KwUdxStaPdu        *pStaPdu;
KwUdxBufLst        *rlsPduLst;
#endif
{
   KwRetx          *retx   = NULLP;
   KwSn            mSn     = 0;
   KwSn            mVtA    = 0;
   KwSn            mAckSn  = 0;
   KwSn            mTxSn   = 0;
   S32             retxBo  = 0;
   U8              nackCnt;
   CmLList         *retxNode;
   KwExtHdr        hdrInfo;

   TRC2(kwHndlStaRsp)

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwHndlStaRsp(rbCb, cntrlPdu, fByte) \n"));

   KW_MEM_ZERO(&hdrInfo, sizeof(KwExtHdr));

   AMDL.numSduPdu = 0;
   AMDL.numSeg    = 0;
   retxBo = AMDL.retxBo;

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
      (gCb->init.prntBuf, "kwDlmHndlStaRsp: ACK SN = %d \n", pStaPdu->ackSn));
   MODAMT(AMDL.vtA, mVtA, AMDL.vtA);
   MODAMT(pStaPdu->ackSn, mAckSn, AMDL.vtA);
   MODAMT(AMDL.txSn, mTxSn, AMDL.vtA);
 
   /* Venki - stopping the poll retx timer */
   /*Stop PollRetx Tmr */
   KW_CHK_FOR_POLLSN(gCb, rbCb, mAckSn);
   /* Set the first node in retx list to retxNode */
   retxNode = AMDL.retxLst.first;

   /* If NACK exists in control PDU */
   if (pStaPdu->nackCnt)
   {
      U8     e2      = 0;
      Bool   first   = TRUE; 
      KwSn   sn      = 0;
      KwSn   soStart = 0;
      KwSn   soEnd   = 0;
      KwSn   nackSn  = 0;
      KwSn   mNackSn = 0;
      KwSn   vtA     = AMDL.vtA;
/*Pradeep - start, fix*/
      U32 idx = 0;
         soEnd   = pStaPdu->nackInfo[idx].soEnd;
/*Pradeep - end, fix*/

      /* For ACKs and NACKs */
      nackCnt = pStaPdu->nackCnt;
      while (nackCnt)
      {
/*Pradeep - start, fix*/
         /*nackSn = pStaPdu->nackInfo[nackCnt].sn;*/
         nackSn = pStaPdu->nackInfo[idx].sn;
         soEnd   = pStaPdu->nackInfo[idx].soEnd;
/*Pradeep - end, fix*/

         if (first)
         {
            vtA   = nackSn;
            first = FALSE;
         }
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                (gCb->init.prntBuf, "kwHndlStaRsp: NACK SN = %d \n", nackSn));

/*Pradeep - start, fix*/
         /*soStart = pStaPdu->nackInfo[nackCnt].soStart;
         soEnd   = pStaPdu->nackInfo[nackCnt].soEnd;*/
         soStart = pStaPdu->nackInfo[idx].soStart;
         soEnd   = pStaPdu->nackInfo[idx].soEnd;
/*Pradeep - end, fix*/

         if (soStart || soEnd)
         {
/*Pradeep - start, In old code updating the retxBo is based on e2 in old code. so introdusing same here.
                   need to remove e2 dipendency*/
            e2 = 1;
/*Pradeep - end, fix*/
            KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                   (gCb->init.prntBuf, "kwHndlStaRsp: soStart and soEnd = %d %d \n", \
                    soStart, soEnd));
         }
/*Pradeep - start, In old code updating the retxBo is based on e2 in old code. so introdusing same here.
                   need to remove e2 dipendency*/
         else
         {
            e2 = 0;
         }
/*Pradeep - end, fix*/

         /* txSn for whatever reason points to the last processed */
         /* PDU and thereby represents as the first PDU to be     */
         /* taken care of from the transmitted PDU array.         */
         sn = AMDL.txSn;
         AMDL.txSn = (nackSn + 1)%1024;;
         MODAMT(nackSn, mNackSn, AMDL.vtA);

         if (mNackSn > mAckSn)
         {
            /* Erroneous NACK_SN, we should raise an error towards L3 */
            continue;
         }
          
         /* Clear the acked SNs from the retx list */
         while (retxNode)
         {
            retx = (KwRetx *)(retxNode->node);
            MODAMT(retx->amHdr.sn, mSn, AMDL.vtA);
            if (mSn < mNackSn)
            {
               retxNode = retxNode->next;
               KW_AM_SUC_RETX_PDU(gCb,rbCb, retx, rlsPduLst);
            }
            else
            {
               break;
            }
         }

         /* For the ACKs */ 
         MODAMT(sn, mSn, AMDL.vtA);
         while (mSn < mNackSn)
         {
            if ((mSn >= mTxSn) && (AMDL.txBuf[sn] != NULLP)) 
            {
               KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                      (gCb->init.prntBuf, "kwHndlStaRsp: Handle ACK for PDU with sn = \
                       %d\n", sn));
               /* Remove pdus from txBuf */
               kwAmmSucTxPdu(gCb,rbCb, sn, rlsPduLst);
            }
            mSn++; sn   = (sn + 1) % 1024;
         }

         /* Now process the NACK_SN received. Now the NACK_SN is    */
         /* either the first element of RETX or is in TX array      */
         /* To remove the remaining acks from the pdu byte segments */
         if (AMDL.txBuf[nackSn] != NULLP)
         {
            KwAmDl *amDl = &(rbCb->m.amDl); 
            /* This is the case of a PDU to be added to retx list       */
            KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
                     (gCb->init.prntBuf, "kwHndlStaRsp: Move PDU from txBuf to \
                      retxLst \n"));
            kwUpdFrmTxtoRetx(gCb,amDl, &retx, sn, rlsPduLst);
            retxNode = retx->lstEnt.next;
            nackCnt--;
            idx++;
            continue;
         }
         while (retxNode)
         {
            retx = (KwRetx *)(retxNode->node);
            if (retx->amHdr.sn != nackSn)
            {
               break;
            }
            if (retx->soEnd < soStart)
            {
               KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                              (gCb->init.prntBuf, "kwHndlStaRsp: Handle ACK for byte \
                               segment, Its sn, soStart and soEnd = %d, %d,\
                               %d\n", sn, retx->amHdr.so, retx->soEnd)); 

               retxNode = retxNode->next;
               KW_AM_SUC_RETX_PDU(gCb,rbCb, retx, rlsPduLst);
            }
            else if (((e2) && (retx->soEnd <= soEnd)) || (!e2))
            {
               /* This case covers the NACKED segments and also the case */
               /* when there are segments and the entire SN is nacked.   */
               /* This case also covers the case of nonsegmented retx PDU*/

               /* Mark the retx PDU we found for further retransmission  */
               retxNode = retxNode->next;
               kwMrkRetxPdu(gCb,rbCb, retx, rlsPduLst);
            }
            else
            {
               break;
            }
         }
         nackCnt--;
         idx++;
      }

      /* For the remaining ACKs  after last nackSn */
      kwUpdRemPduAck(gCb,rbCb, mAckSn, retxNode, rlsPduLst);

      /* Update vtA */ 
      AMDL.vtA = vtA;
      AMDL.vtMs = (AMDL.vtA + 512) % 1024;
      KW_LLIST_FIRST_RETX(AMDL.retxLst, AMDL.nxtRetx);
   }
   else
   {
      /* For All ACKs */
      KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
            (gCb->init.prntBuf, "kwHndlStaRsp: Received All ACKS \n"));

      /* For the remaining ACKs  after last nackSn */
      kwUpdRemPduAck(gCb,rbCb, mAckSn, retxNode, rlsPduLst);
      AMDL.vtA = pStaPdu->ackSn;
      AMDL.vtMs = (AMDL.vtA + 512) % 1024;
   }

   AMDL.txSn = pStaPdu->ackSn;

   /* BO update */
   if (retxBo != AMDL.retxBo)
   {
      KW_AM_SND_DSTA_RSP(gCb);
   }

   RETVALUE(ROK);
}

/**
 *
 * @brief Handler to queue the SDUs received from PDCP
 *       
 *
 * @b Description
 *  This function is invoked by UIM to queue the SDU received from PDCP in the 
 *  SDU queue of the corresponding RbCb. It also updates the BO and report the 
 *  same to MAC.
 *  -  Allocate memory for and assign received buffer to the SDU
 *  -  Add SDU in the sduQ of KwAmDl 
 *  -  Calculate bo with the buffer received
 *  -  Accumulate bo with retransmission bo and control pdu's bo if available
 *  -  Estimate the header size for the bo; Fill in StaRspInfo and send it 
 *     to MAC
 *
 *  @param[in] rbCb RB control block 
 *  @param[in] mBuf Sdu to be queued 
 *
 *
 *  @return Void
 *      -# RETVOID
*/
#ifdef ANSI
PUBLIC S16 kwAmmQSdu
(
KwCb     *gCb,
KwDlRbCb *rbCb,
Buffer *mBuf,
U32    sduId
)
#else
PUBLIC S16 kwAmmQSdu(gCb, rbCb, mBuf, sduId)
KwCb     *gCb;
KwDlRbCb *rbCb;
Buffer *mBuf;
U32    sduId;
#endif
{
   KwSdu      *sdu;

   TRC2(kwAmmQSdu)

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmQSdu(rbCb, mBuf, sduId) \n"));

   /* Allocate sdu */
   KW_ALLOC (gCb,sdu, sizeof(KwSdu)); 

#if (ERRCLASS & ERRCLS_ADD_RES)
   if (sdu == NULLP)
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW001, (ErrVal)0,
            "kwAmmQSdu: Allocation failed for sdu \n");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_RES */

   /* Assign values to sdu */
   SFndLenMsg(mBuf, &sdu->sduSz);

   sdu->mBuf = mBuf; 
   sdu->mode.am.sduId = sduId;
   sdu->actSz = sdu->sduSz;

   /* Update nxtTx to point to the added sdu if this is the first SDU in the
    * queue */
   if (AMDL.nxtTx == NULLP)
   {
      KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
            (gCb->init.prntBuf, "kwAmmQSdu: Update received sdu as the next one \
                       to be transmitted \n"));
      AMDL.nxtTx = sdu;
   }

   /* Add sdu to the sdu list */
   cmLListAdd2Tail(&AMDL.sduQ, &sdu->lstEnt);
   sdu->lstEnt.node = (PTR)sdu;
   AMDL.numSduPdu = 1;
   AMDL.numSeg    = 0;

   /* Update BO and estimate header size for the current BO */ 
   AMDL.bo = AMDL.bo + sdu->sduSz;
   AMDL.estHdrSz += 2;
#ifdef LTE_L2_MEAS_RLC
   /* Update numActUe if it is not active */
   if((rbCb->rbL2Cb.measOn & LKW_L2MEAS_ACT_UE) &&
      (rbCb->ueCb->numActRb[rbCb->qci] == 0))
   {
      rbCb->ueCb->numActRb[rbCb->qci]++;
      gCb.kwL2Cb.numActUe[rbCb->qci]++;
   }
#endif

   KW_AM_SND_DSTA_RSP(gCb);

   RETVALUE(ROK);
} /* kwAmmQSdu */



#if 0
#ifdef ANSI
PRIVATE S16 kwAssembleCntrlInfo 
(
KwCb                      *gCb,
KwDlRbCb                  *rbCb,
KwDatReq                  *kwDatReq
)
#else
PRIVATE S16 kwAssembleCntrlInfo(rbCb, kwDatReq)
KwCb                      *gCb;
KwUlRbCb                  *rbCb;
KwDatReq                  *kwDatReq;
#endif
{

   CmLListCp  *lst    = NULLP;

   TRC2(kwAssembleCntrlInfo)

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAssembleCntrlInfo(rbCb, kwDatReq) \n"));

   lst = AMDL.cntrlPduLst;
   while (lst->first)
   {
      staPdu = lst->first->node; 
      if (kwDatReq->pduSz > staPdu->pduSz)
      {
         kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = staPdu->mBuf; 
         kwDatReq->pduInfo.numPdu++;
         cmLListDelFrm(lst, lst->first);
         KW_FREE(gCb,staPdu,sizeof(staPdu));
      } /* Control Pdu Fits grant*/
      else
      {
         break;
      } /* Control Message exceeds grant */
   } /* while all cntrol Pdus */

#if 0
   gCbOckwSap.sts.statMsgs += kwDatReq->pduInfo.numPdu;
#endif
   RETVALUE(ROK);
}
#endif

/**
 *
 * @brief Private handler to construct control PDU
 *
 * @b Description
 *        Its a private function called by kwProcessSdus, to create the 
 *        control PDU if it needs to be sent. With the PDU size indicated 
 *        by MAC, it constructs the Status PDU.
 *
 *        - Eliminate fixed header size and ACK_SN with E1 from the pduSz
 *        - Update ACK_SN with the sn of vrMr, to indicate the next not 
 *          received PDU  
 *        - Scan through PDUs in the reception buffer, starting from vrR 
 *          till vrMs and include NACK_SN for missing PDUs and NACK_SN 
 *          along with soStart and soEnd for missing byte segments.
 *
 * @param[in]  rbCb     RB control block 
 * @param[in]  kwdatReq DatReq to be sent to MAC 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwAssembleDlCntrlInfo 
(
KwCb                    *gCb,
KwDlRbCb                *rbCb,
KwDatReq                *kwDatReq
)
#else
PRIVATE S16 kwAssembleDlCntrlInfo(gCb, rbCb, kwDatReq)
KwCb                    *gCb;
KwDlRbCb                *rbCb;
KwDatReq                *kwDatReq;
#endif
{

   Buffer     *mBuf = NULLP;           /* control pdu buffer */

   TRC2(kwAssembleDlCntrlInfo)

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAssembleDlCntrlInfo(rbCb, kwDatReq) \n"));

   /* Eliminate fixed hdr size (14bits including ACK_SN) */
   if (kwDatReq->pduSz >= (KW_CNTRL_PDU_FIXED_HDRSZ + KW_MAC_HDR_SZ3))
   {
      kwDatReq->pduSz -= KW_CNTRL_PDU_FIXED_HDRSZ;
  
      /* Eliminate MAC header */
      kwDatReq->pduSz -= KW_MAC_HDR_SZ3;

      mBuf = (Buffer*)AMDL.mBuf;

/*Pradeep - commenting the kwStartTmrKW_EVT_AMUL_STA_PROH_TMR), it is not required in RLC-DL*/
#if 0
      /* Start staProhTmr */
      kwStartTmr(gCb, (PTR)rbCb, KW_EVT_AMUL_STA_PROH_TMR);
#endif
      /* Update number of pdus in pduInfo */
      kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = mBuf; 
      kwDatReq->pduInfo.numPdu++;

      AMDL.mBuf = NULLP;
   }

   RETVALUE(ROK);
}

/**
 *
 * @brief Handler to form the PDUs with the size indicated by MAC
 *
 * @b Description
 *        This function is invoked by UTL with the PDU size indicated by 
 *        MAC (after eliminating MAC header size). It assembles control 
 *        Info / data (New SDUs / Retx PDUs), check if polling needs to be 
 *        set for the data PDU and returns PDU(s) and updated BO with 
 *        estimated header size to be sent to MAC.
 *
 *        - Check if the control BO is available and call kwAssembleCntrlInfo 
 *          to assemble control Information
 *        - Check if the pdu size is available to form PDUs from retransmission 
 *          buffer and call kwResegRetxPdus
 *        - Check if the pdu size is available and assemble SDUs from sduQ 
 *          if exist, using kwAssembleSdus
 *        - PDU Info and bo are filled in and then sent to MAC from the 
 *          utility function
 *
 * @param[in]  rbCb     RB control block 
 * @param[in]  kwdatReq DatReq to be sent to MAC 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 kwAmmProcessSdus
(
KwCb                      *gCb,
KwDlRbCb                   *rbCb,
KwDatReq                 *kwDatReq
)
#else
PUBLIC S16 kwAmmProcessSdus(gCb, rbCb, kwDatReq)
KwCb                      *gCb;
KwDlRbCb                   *rbCb;
KwDatReq                 *kwDatReq;
#endif    
{
   S16                   ret = ROK;
#ifdef LTE_L2_MEAS_RLC
   Bool dataWasPrsnt = FALSE;
#endif /*  LTE_L2_MEAS_RLC */

   TRC2(kwAmmProcessSdus)

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmProcessSdus(rbCb, kwDatReq) \n"));

#ifdef LTE_L2_MEAS_RLC
   dataWasPrsnt = (AMDL.cntrlBo || AMDL.retxBo  || AMDL.bo)?TRUE:FALSE;
#endif /*  LTE_L2_MEAS_RLC */
#ifdef KW_BG_DL_PROC
   kwAmmRlsPdusSet(rbCb);
#endif

#if 1
   /* Assemble control information */ 
   if (AMDL.cntrlBo != 0)
   {
      kwDatReq->boRep.staPduPrsnt = TRUE;
      if (AMDL.mBuf != NULLP)
      {
         kwAssembleDlCntrlInfo (gCb,rbCb, kwDatReq);
      }
      else
      {
         KWLOGERROR(gCb,ERRCLS_DEBUG, EKW002, (ErrVal) ret,
                  "kwAmmProcessSdus: Miscomputation of control Bo.\n");
      }
      AMDL.cntrlBo = 0;
   }   
#endif

   /* For estHdrSz */
   AMDL.numSeg    = 0;
   AMDL.numSduPdu = 0;

   /* Retransmit PDUs /portions of PDUs available in retxLst */
   if ( (kwDatReq->pduSz > 0) && (AMDL.nxtRetx != NULLP) )
   {
      ret = kwResegRetxPdus (gCb,rbCb, kwDatReq);
#if (ERRCLASS & ERRCLS_DEBUG)
         if (ret != ROK)
         {
            KWLOGERROR(gCb,ERRCLS_DEBUG, EKW002, (ErrVal) ret,
                  "kwAmmProcessSdus: Resegmentation failed.\n");
         }
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }

   /* Assemble SDUs to form new PDUs */ 
   if ( (kwDatReq->pduSz > 0) && (AMDL.nxtTx != 0) )
   {
      ret = kwAssembleSdus(gCb,rbCb, kwDatReq); 
#if (ERRCLASS & ERRCLS_DEBUG)
         if (ret != ROK)
         {
            KWLOGERROR(gCb,ERRCLS_DEBUG, EKW003, (ErrVal) ret,
                  "kwAmmProcessSdus: AssembleSdus failed.\n");
         }
#endif /* ERRCLASS & ERRCLS_DEBUG */
   }
  
   /* Accumulate bo */
   KW_UPD_AMBO(AMDL, kwDatReq->boRep.bo);

#ifdef LTE_L2_MEAS_RLC
   if((rbCb->rbL2Cb.measOn & LKW_L2MEAS_ACT_UE) &&
      (dataWasPrsnt) &&
      !((AMDL.cntrlBo) ||
        (AMDL.retxBo)  ||
        (AMDL.bo)))
   {
      if(--(rbCb->ueCb->numActRb[rbCb->qci]) == 0)
      {
         gCb.kwL2Cb.numActUe[rbCb->qci]--;
      }
   }
#endif /* LTE_L2_MEAS_RLC */
   /* Estimate hdr size for boReport */
   kwAmmEstHdrSz (gCb,&AMDL, KW_DEL_SDU);
   kwDatReq->boRep.estHdrSz = AMDL.estHdrSz;

   RETVALUE(ROK);
} /* kwAmmProcessSdus */

/**
 *
 * @brief Private handler split a PDU/segment into two
 *
 * @b Description
 *        Its a private function called by kwResegRetxPdu to split a segment
 *        or a retransmit PDU into two segments splitting at the passed size.
 *        This function is called only for those PDUs that dont have any LIs.
 *
 * @param[in]  rbCb     RB control block 
 * @param[in]  kwdatReq DatReq to be sent to MAC 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwSplitPdu
(
KwCb             *gCb,
KwDlRbCb         *rbCb,
KwRetx           *crnt,
KwRetx           *next,
U16              size
)
#else
PRIVATE S16 kwSplitPdu(gCb, rbCb, crnt, next, size)
KwCb             *gCb;
KwDlRbCb         *rbCb;
KwRetx           *crnt;
KwRetx           *next;
U16              size;
#endif
{
   U8            fi;

   TRC2(kwSplitPdu)
   /* Set the SN for the new segment */
   next->amHdr.sn = crnt->amHdr.sn;

   /* Set the protocol specific fields appropriately */
   fi = crnt->amHdr.fi;
   crnt->amHdr.fi  = crnt->amHdr.fi | KW_FI_LAST_SEG;
   next->amHdr.fi  = fi | KW_FI_FIRST_SEG;
   crnt->amHdr.rf  = next->amHdr.rf = 1;
   next->amHdr.lsf = crnt->amHdr.lsf;
   crnt->amHdr.lsf = 0;
   crnt->amHdr.p   = 0;

   /* Update seg size */
   next->segSz = crnt->segSz - size;
   crnt->segSz = size;
   crnt->hdrSz = KW_AM_SEG_FIXED_HDRSZ;

   /* Set the SO fields appropriately */
   crnt->soEnd = crnt->amHdr.so + crnt->segSz - 1;
   next->amHdr.so = crnt->amHdr.so + crnt->segSz;

   /* This is a special case of single LI and hence set that to 1 */
   crnt->amHdr.numLi = next->amHdr.numLi = 1;

   /* This macro is called for No LI case - one SDU */
   /* Update the size of SDU in each node's sduMap  */
   next->sduMap[0].sduId = crnt->sduMap[0].sduId;
   crnt->sduMap[0].sduSz = crnt->segSz;
   next->sduMap[0].sduSz = next->segSz;
   next->sduMap[0].actSz = crnt->sduMap[0].actSz;
   next->sduMap[0].isSegmented = crnt->sduMap[0].isSegmented = TRUE;;
   next->numSdu = crnt->numSdu;

   /* Segment the payload into two parts based on the size passed */
   SSegMsg(crnt->seg, size, &next->seg);
   next->retxCnt     = crnt->retxCnt;
   next->yetToConst  = TRUE;
   next->wtForAck    = TRUE;

   /* Compute the header size and update the BO appropriately */
   KW_AM_EXTN_HDRSZ(next->amHdr.numLi, next->hdrSz);
   next->hdrSz += KW_AM_SEG_FIXED_HDRSZ;
   AMDL.estHdrSz += next->hdrSz;

   /* Add the next to the retx list */
   AMDL.retxLst.crnt = &crnt->lstEnt;
   CM_LLIST_INS_AFT_CRNT(AMDL.retxLst, next); 
   AMDL.nxtRetx = next;
   RETVALUE(ROK);
}

/**
 *
 * @brief Private handler split a PDU/segment into two
 *
 * @b Description
 *        Its a private function called by kwResegRetxPdu to split a segment
 *        or a retransmit PDU into two segments splitting at the passed size.
 *        This function is called only for those PDUs that have valid LIs.
 *
 * @param[in]  rbCb     RB control block 
 * @param[in]  kwdatReq DatReq to be sent to MAC 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwSplitPduWithLi
(
KwCb             *gCb,
KwDlRbCb         *rbCb,
KwRetx           *crnt,
KwRetx           *next,
U16              size
)
#else
PRIVATE S16 kwSplitPduWithLi(gCb, rbCb, crnt, next, size)
KwCb             *gCb;
KwDlRbCb         *rbCb;
KwRetx           *crnt;
KwRetx           *next;
U16              size;
#endif
{
   U16           segSz = 0;
   U16           tSz   = size;
   U32           liCnt = 0;
   U32           liIdx; 
   KwAmHdr       *oldHdr;
   KwAmHdr       *newHdr;

   TRC2(kwSplitPduWithLi)
   /* Set the SN for the new segment */
   next->amHdr.sn = crnt->amHdr.sn;

   /* Figure out how many SDUs from the original may be included in */
   /* the current one based on the size passed                      */
   oldHdr = &crnt->amHdr;
   newHdr = &next->amHdr;
   while ((tSz >= oldHdr->li[liCnt]) && (liCnt < oldHdr->numLi))  
   {
       KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
              (gCb->init.prntBuf, "kwSplitPduWithLi: numLi of in PDU = %d \n",
              crnt->amHdr.numLi));

       segSz      += oldHdr->li[liCnt];
       tSz        -= oldHdr->li[liCnt];

       /* Eliminate extension header size */
       if (tSz > 2)
       {
          /* kw003.201 - Do this only if we have enough space */
          tSz -= ((liCnt + 1) % 2) ? 2 : 1; 
       }
       else
       {
          /* kw003.201 - Even though a few bits (1 or 2) may be left, they */
          /*             are useless as we cant fit any into it            */
          tSz = 0;
       }
       liCnt++;
   }
   next->segSz = crnt->segSz - (segSz + tSz);
   crnt->segSz = (segSz + tSz);

   /* Transfer the remaining LIs to the subsequent segment */
   if (tSz)
   {
      newHdr->li[0] = oldHdr->li[liCnt] - tSz;
      oldHdr->li[liCnt] = tSz;
      crnt->sduMap[liCnt].isSegmented = TRUE;
      next->sduMap[0] = crnt->sduMap[liCnt];
      next->sduMap[0].sduSz -= tSz;
      crnt->sduMap[liCnt].sduSz = tSz;
      newHdr->numLi++;
      next->numSdu++;
      crnt->numSdu = liCnt + 1;
      liCnt++;
   }

   liIdx = 0;
   while ((liCnt + liIdx) < oldHdr->numLi)
   {
      newHdr->li[newHdr->numLi] = oldHdr->li[liCnt + liIdx];
      next->sduMap[next->numSdu++] = crnt->sduMap[liCnt + liIdx];
      liIdx++; 
      newHdr->numLi++;
   }
   oldHdr->numLi  = liCnt;
   crnt->numSdu = liCnt;

   /* Manage header sizes and also updating the BO on RB CB */
   KW_AM_EXTN_HDRSZ(next->amHdr.numLi, next->hdrSz);
   next->hdrSz += KW_AM_SEG_FIXED_HDRSZ;
   AMDL.estHdrSz += next->hdrSz;

   /* Set the frame indicator field for both the segments */
   next->amHdr.fi  = crnt->amHdr.fi;
   if (tSz == 0)
   {
      /* We exactly finished an SDU with this segment. We want to set FI */
      /* appropriately. The current one should have last (un)set and the */
      /* the next one should have first (un)set                          */
      crnt->amHdr.fi &= 0x02;
      next->amHdr.fi &= 0x01;
   }
   else
   {
      /* We exactly finished an SDU with this segment */
      crnt->amHdr.fi |= 0x01;
      next->amHdr.fi |= 0x02;
      
   }
   crnt->amHdr.p   = 0;
   crnt->amHdr.rf  = next->amHdr.rf = 1;
   next->amHdr.lsf = crnt->amHdr.lsf;
   crnt->amHdr.lsf = 0;

   /* Set the SO fields appropriately */
   crnt->soEnd = crnt->amHdr.so + crnt->segSz - 1;
   next->amHdr.so = crnt->amHdr.so + crnt->segSz;

   /* Segment the payload into two parts based on the size passed */
   SSegMsg(crnt->seg, crnt->segSz, &next->seg);
   next->retxCnt     = crnt->retxCnt;
   next->yetToConst  = TRUE;
   next->wtForAck    = TRUE;

   /* Add the next to the retx list */
   AMDL.retxLst.crnt = &crnt->lstEnt;
   CM_LLIST_INS_AFT_CRNT(AMDL.retxLst, next); 
   AMDL.nxtRetx = next;
   RETVALUE(ROK);
}

/**
 *
 * @brief Private handler to retransmit PDUs or PDU segments
 *
 * @b Description
 *        Its a private function called by kwProcessSdus, to create the 
 *        PDUs / its segments from the retransmission buffer available in RbCb.
 *       
 *        - Eliminate the fixed header size and MAC header size while 
 *          forming PDUs/segments
 *        - While pdusize is available and retxBuf has data (pdu or portion 
 *          of pdu) to be sent, form the pdu as it is if it matches with the 
 *          pdusize else segment the PDUs/portion of PDUs
 *        - Call kwChkandSetPoll function to check and set the poll bit as 
 *          required 
 *        - Concatenate data and header info and fill pduInfo 
 *        - Update retxCnt and send indication to PDCP if it reaches maxRetx 
 *          threshold
 *
 * @param[in]  rbCb     RB control block
 * @param[in]  kwdatReq DatReq to be sent to MAC 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwResegRetxPdus 
(
KwCb                   *gCb,
KwDlRbCb               *rbCb,
KwDatReq               *kwDatReq
)
#else
PRIVATE S16 kwResegRetxPdus(gCb, rbCb, kwDatReq)
KwCb                   *gCb;
KwDlRbCb               *rbCb;
KwDatReq               *kwDatReq;
#endif
{
   KwAmDl *amDl   = NULLP;
   MsgLen *pduSz  = 0;
   KwRetx *retx   = NULLP;
   KwRetx *tNode  = NULLP;
   U8     hdr[KW_MAX_HDRSZ];
   U16    idx     = 0; 
   U8     pollBit = 0;
   Bool   segFlg  = TRUE;
   Buffer *pdu = NULLP;

   TRC2(kwResegRetxPdus)

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwResegRetxPdus(rbCb, kwDatReq) \n"));

   pduSz = &kwDatReq->pduSz;
   amDl  = &AMDL;
   retx  = amDl->nxtRetx;

   /* Scan through the retxLst for retransmission */
   while ((*pduSz > 0) && (amDl->nxtRetx != NULLP))
   {
      U16     tmpSz;

      retx = amDl->nxtRetx;
      /* kw003.201 : Add header size to seg size to determine if the      */
      /*             the segment can be completed within the allocation   */
      /* kw003.201 - Eliminate MAC Header Size based on bites needed      */
      tmpSz = KW_MIN((retx->segSz + retx->hdrSz), *pduSz);
      (*pduSz) -= (tmpSz <= 128) ?  KW_MAC_HDR_SZ2 : KW_MAC_HDR_SZ3;

      /* kw003.201 - We should have at least one more than basic header */
      if (*pduSz <= retx->hdrSz)
      {
         RETVALUE(ROK);
      }
      kwGetNxtRetx(gCb,amDl, &(amDl->nxtRetx));

      /* Send retx buf without segmentation */
      if (*pduSz >= (retx->segSz + retx->hdrSz))
      {
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
                (gCb->init.prntBuf, "kwResegRetxPdus: Send retx buf without \
                 segmentation \n")); 

         if (retx->yetToConst)
         {
            /* Construct hdr with the available hdr values */ 
            kwConstructAmHdr(gCb,&retx->amHdr, segFlg, hdr, &idx);
            KW_ADD_PRE_MSG_AM(retx->seg, hdr, idx + 1);
            retx->yetToConst = FALSE;
         } 

         /* kw003.201 - Check if poll bit needs to be set. Retx size does */
         /* not affect the poll bit so it is being passed as zero         */ 
         pollBit = kwChkandSetPoll(gCb,rbCb, FALSE, 0);
         KW_UPD_POLL_BIT(retx, pollBit);

         *pduSz        -= retx->hdrSz;
         *pduSz        -= retx->segSz;
         AMDL.estHdrSz -= retx->hdrSz;
      }
      else
      {
         /* Segment this pdu / portion of pdu. Insert this segment into */
         /* retxLst and update offset                                   */
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
                (gCb->init.prntBuf, "kwResegRetxPdus: Segment retx buf \n"));

         /* Eliminate fixed header size if the pdu is segmented for the */
         /* first time                                                  */
         *pduSz -= KW_AM_SEG_FIXED_HDRSZ;
         if (*pduSz <= 0)
         {
            RETVALUE(ROK);
         }

         /* Allocate memory for tracking a new segment */
         KW_ALLOC(gCb,tNode, sizeof(KwRetx)); 
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (tNode == NULLP)
         {
            KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW004, (ErrVal)0,
                  "kwResegRetxPdus: Allocation failed for tNode \n");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_RES */

         /* Segment header and data */
         KW_AM_RMV_HDR(rbCb, retx);

         /* No LI, segment the data filed, update hdr Info */ 
         if ((retx->amHdr.numLi - 1) == 0)
         {
            KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
                   (gCb->init.prntBuf, "kwResegRetxPdus: No LI for segmentation \n"));
            /* kw003.201 - Split the payload and update other fields */
            kwSplitPdu(gCb,rbCb, retx, tNode, *pduSz); 

         }
         else
         {
            KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
                   (gCb->init.prntBuf, "kwResegRetxPdus: LIs for segmentation \n"));
            /* With LI, segment the data field, update hdr Info */    
            /* Remove the header if it exists as it would be reconstructed */
            kwSplitPduWithLi(gCb,rbCb, retx, tNode, *pduSz);
         }
         /* Construct hdr with the available hdr values */
         kwConstructAmHdr(gCb,&retx->amHdr, segFlg, hdr, &idx);
         KW_ADD_PRE_MSG_AM(retx->seg, hdr, idx + 1);
         retx->hdrSz = idx + 1;

         /* Poll bit need not be set for this seg, since its second  */
         /* half remains in retxLst                                  */
         KW_UPD_POLL_BIT(retx, FALSE);
         retx->yetToConst = FALSE;
         *pduSz = 0; 
      }

      kwCpyMsg(gCb,retx->seg, &pdu);

      /* Update pduInfo */
      kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = pdu;
      kwDatReq->pduInfo.numPdu++;
      /* kw005.201 ccpu00117318, updating the statistics */
      gCb->genSts.pdusRetx += 1;
      retx->soEnd = retx->amHdr.so + retx->segSz - 1;
      retx->wtForAck = TRUE;
      amDl->retxBo -= retx->segSz;
   }

#ifndef ALIGN_64BIT
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
         (gCb->init.prntBuf, "kwResegRetxPdus: retxBo after resegmentation = %ld \n", 
          amDl->retxBo));
#else
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
         (gCb->init.prntBuf, "kwResegRetxPdus: retxBo after resegmentation = %d \n",
          amDl->retxBo));
#endif

   amDl->numSduPdu = 0;
   amDl->numSeg    = 0;

   RETVALUE(ROK);
}

#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
/**
 *
 * @brief Private handler to calculate DL IP throughput.
 *
 * @b Description
 *      It is called from kwAssembleSdus.
 *      If the RLC bo is more than allocation from MAC, 
 *        T2 time stamp is taken and stored in KwDlRbCb.
 *        Variable "isBurstSplitted" flag in KwTbSnMap set to TRUE.
 *        Variable "count" is incremented.
 *        Volume of data for this PDU is stored.
 *      If the allocation from MAC is emptying the RLC buffer,
 *        Burst is said to be COMPLETED.
 *        T1 time stamp is calculated in kwUtlProcHarqInd
 *
 * @param[in]  rbCb     RB control block
 * @param[in]  dataVol  Data volume
 * @param[in]  pduSz    pdu size
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE Void kwAmmCalDlIpThrPut
(
KwCb            *gCb,
KwDlRbCb        *rbCb,
MsgLen          dataVol,
S32             initialBo,
MsgLen          pduSz
)
#else
PRIVATE Void  kwAmmCalDlIpThrPut (gCb, rbCb, dataVol, initialBo, pduSz)
KwCb            *gCb;
KwDlRbCb        *rbCb;
MsgLen          dataVol;
S32             initialBo;
MsgLen          pduSz;
#endif
{
   KwTbSnMap         *curTbSnMap = NULLP;   /*Holds the current TbSnMap*/
   KwL2MeasIpThruput *l2MeasIpThruput = NULLP;
   EpcTime           timeSt;

   TRC2(kwAmmCalDlIpThrPut)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmCalDlIpThrPut(rbCb, dataVol, initialBo, pduSz)\n"));
#endif

   /*Get the current TbSnMap*/
   curTbSnMap = gCb.kwL2Cb.curTbSnMap;

   l2MeasIpThruput = &rbCb->l2MeasIpThruput;

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
   (gCb->init.prntBuf, "kwAmmCalDlIpThrPut: Log for dl ip throughput:\n \
   RB_MeasOn: %d\n curTbSnMap->numSn: %d\n State: %d\n      \
   Count: %d\n dataVol: %lu\n prevTbSnMap: %p\n initialBo: %ld\n\
   Alloc from MAC: %d\n", rbCb->rbL2Cb.measOn, curTbSnMap->numSn,
   l2MeasIpThruput->dlIpThrputSt, l2MeasIpThruput->count,
   l2MeasIpThruput->dataVol, (Void*)l2MeasIpThruput->prevTbSnMap,
   initialBo, pduSz));

   /*Check if DL ip throughput measurement is going on or not AND at least*
    *one new data PDU is formed.                                          */
   if( (0 != (rbCb->rbL2Cb.measOn & LKW_L2MEAS_DL_IP)) && 
             (curTbSnMap->numSn > 0) )
   {
      if(KW_DL_IPTHRU_BURST_CONTINUE == l2MeasIpThruput->dlIpThrputSt)
      {
         if(initialBo > dataVol)
         {
            /*It means data burst is splitted across TTI. So set the*
             *isBurstSplitted flag to TRUE.                         */
            curTbSnMap->snSduMap[curTbSnMap->numSn -1].isBurstSplitted = TRUE;

            /*This count will be decremented when HARQ Ack will be received*
              for this TbId. It is done in kwUtlProcHarqInd.               */
            l2MeasIpThruput->count++;

            l2MeasIpThruput->dataVol += dataVol;
         }
         else
         {
            /*Change state to BURST_COMPLETED since current allocation has*
             *emptied the data buffer.                                    */
            l2MeasIpThruput->dlIpThrputSt = KW_DL_IPTHRU_BURST_COMPLETED;

            /*If count is 0, then it means that RLC has already received  *
             *all the ACKs for burst transmitted. So, state can be changed*
             * to RESET.                                                  */
            if(0 == l2MeasIpThruput->count)
            {
               /*Update Volume and time difference in kwL2MeasRbCb. Use*
                *tempTimeT1 which was stamped when all the part of     *
                *the burst(till that time) were ACK-ed.                        */
               rbCb->rbL2Cb.l2Sts[KW_L2MEAS_DL_IP]->dlIpThruput.volSummation
               += l2MeasIpThruput->dataVol;
               rbCb->rbL2Cb.l2Sts[KW_L2MEAS_DL_IP]->dlIpThruput.timeSummation
               += l2MeasIpThruput->tempTimeT1 - l2MeasIpThruput->timeT2;

               /*Reset the IP throughput related parameters*/
               kwUtlResetKwRbL2Meas(rbCb);
            }
         }
      }
      else if (KW_DL_IPTHRU_BURST_STARTED == l2MeasIpThruput->dlIpThrputSt) /*2nd allocation, T2 already stamped*/
      {
         if(initialBo > dataVol)
         {
            /*Change the state to CONTINUE since T2 is confirmed now*/
            l2MeasIpThruput->dlIpThrputSt = KW_DL_IPTHRU_BURST_CONTINUE;

            /*It means data burst is splitted across TTI. So set the*
             *isBurstSplitted flag to TRUE.                         */
            curTbSnMap->snSduMap[curTbSnMap->numSn -1].isBurstSplitted = TRUE;

            /*This count will be decremented when HARQ Ack will be received*
             *for this TbId. It is done in kwUtlProcHarqInd.               */
            l2MeasIpThruput->count++;

            l2MeasIpThruput->dataVol += dataVol;
         }
         else
         {
            /*Since 2nd allocation is emptying the buffer, isBurstSplitted *
             *is set to FALSE. If count is 0, then it means that the ACK or*
             *NACK has been received and the corresponding KwTbSnMap is    *
             *freed(in KwUtlProcHarqInd) and so prevTbSnMap has become a   *
             *dangling pointer and so it is set to NULLP.                  */
            if(l2MeasIpThruput->count == 1)
            {
               l2MeasIpThruput->prevTbSnMap->snSduMap[l2MeasIpThruput->
                                prevTbSnMap->numSn - 1].isBurstSplitted = FALSE;
            }
            else if(l2MeasIpThruput->count == 0)
            {
               l2MeasIpThruput->prevTbSnMap = NULLP;
            }
            else
            {
#ifndef ALIGN_64BIT
               KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_ERROR | KW_DBGMASK_DL),
               (gCb->init.prntBuf, "kwAssembleSdus: count can be either 1 or 0.\
                L2Mcount = %d \n", l2MeasIpThruput->count));
#else
               KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_ERROR | KW_DBGMASK_DL),
               (gCb->init.prntBuf, "kwAssembleSdus: count can be either 1 or 0.\
                L2Mcount = %d \n", l2MeasIpThruput->count));
#endif
            }

            /*Change state back to RESET*/
            kwUtlResetKwRbL2Meas(rbCb);
         }
      }
      /*1st allocation for the current burst*/
      else if(KW_DL_IPTHRU_RESET == l2MeasIpThruput->dlIpThrputSt)
      {
         if(initialBo > dataVol)
         {
            /*Change state from RESET to BURST_STARTED*/
            l2MeasIpThruput->dlIpThrputSt = KW_DL_IPTHRU_BURST_STARTED;

            /*Take timestamp for T2.*/
            SGetEpcTime(&timeSt);

            /*Store in KwDlRbCb.*/
            l2MeasIpThruput->timeT2 = timeSt;

            /*Preserve the curent TbSnMap in KwDlRbCb upto next allocation.*/
            l2MeasIpThruput->prevTbSnMap = curTbSnMap;

            /*It means data burst is splitted across TTI. So set the*
             *isBurstSplitted flag to TRUE.                         */
            curTbSnMap->snSduMap[curTbSnMap->numSn -1].isBurstSplitted = TRUE;

            /*This count will be decremented when HARQ Ack will be received*
              for this TbId. It is done in kwUtlProcHarqInd.               */
            l2MeasIpThruput->count++;

            l2MeasIpThruput->dataVol += dataVol;
         }
         else
         {
            /* NOP */
         }
      }
      /*If a subsequent burst is split across TTI but the previous burst is*
       *not fully Ack-ed by MAC, then the subsequent bursts will be        *
       *considered as part of previous burst and so state is changed to    *
       *CONTINUE.                                                          */
      else /*dlIpThrputSt is KW_DL_IPTHRU_BURST_COMPLETED*/
      {
         if((initialBo > dataVol) && (l2MeasIpThruput->count > 0))
         {
            /*Change state from RESET to BURST_CONTINUE*/
            l2MeasIpThruput->dlIpThrputSt = KW_DL_IPTHRU_BURST_CONTINUE;

            l2MeasIpThruput->count++;

            l2MeasIpThruput->dataVol += dataVol;
         }
      }
   }

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
   (gCb->init.prntBuf, "kwAmmCalDlIpThrPut: Log for dl ip throughput:\n \
   RB_MeasOn: %d\n curTbSnMap->numSn: %d\n State: %d\n      \
   Count: %d\n dataVol: %lu\n prevTbSnMap: %p\n initialBo: %ld\n\
   Alloc from MAC: %d\n", rbCb->rbL2Cb.measOn, curTbSnMap->numSn,
   l2MeasIpThruput->dlIpThrputSt, l2MeasIpThruput->count,
   l2MeasIpThruput->dataVol, (Void*)l2MeasIpThruput->prevTbSnMap,
   initialBo, pduSz));
}/* end of function kwAmmCalDlIpThrPut */
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */

/**
 *
 * @brief Private handler to assemble SDUs to form new data PDU(s)
 *
 * @b Description
 *        Its a private function called by kwProcessSdus, to create the new data PDUs 
 *        from the SDU queue of RbCb.
 *
 *        - While pdusize is available, segment/concatenate SDUs or else if it
 *          matches the pdu size form PDUs accordingly.
 *        - RLC header and MAC header size are eliminated while forming the PDUs
 *        - Call kwChkandSetPoll function to check and set the poll bit as required 
 *        - Concatenate data and header info and fill pduInfo  
 *
 * @param[in]  rbCb     RB control block
 * @param[in]  kwdatReq DatReq to be sent to MAC 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwAssembleSdus 
(
KwCb            *gCb,
KwDlRbCb        *rbCb,
KwDatReq        *kwDatReq
)
#else
PRIVATE S16 kwAssembleSdus (gCb, rbCb, kwDatReq)
KwCb            *gCb;
KwDlRbCb        *rbCb;
KwDatReq        *kwDatReq;
#endif
{
   Buffer       *pdu    = NULLP;
   MsgLen       pduSz   = kwDatReq->pduSz;
   KwAmDl       *amDl   = &AMDL;
   KwAmHdr      amHdr;
   KwSdu        *sdu    = amDl->nxtTx;
   Bool         pduCompleted = FALSE;
   U8           numSdu  = 0;
   KwSduMap     sduMap[KW_MAX_LI + 1];
   Bool         nxtTxUpd = FALSE;
   KwKwuSapCb   *kwuSapCb;
   MsgLen       sduSz;
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
   MsgLen       dataVol   = 0;
   S32          initialBo = amDl->bo;  /*Used to compare with DL allocation*/
#endif
#endif

   TRC2(kwAssembleSdus)

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAssembleSdus(rbCb, kwDatReq) \n"));

   amDl->sduQ.crnt =  &sdu->lstEnt;

   /* kw005.201 ccpu00117318, updating the statistics */
   kwuSapCb = (KwKwuSapCb *)(gCb->u.dlCb->kwuDlSap + rbCb->kwuSapId);

   while ((pduSz > 0) && 
          (sdu != NULLP) && 
          (kwDatReq->pduInfo.numPdu < KW_MAX_PDU))
   {
      nxtTxUpd = FALSE;
      sduSz    = sdu->sduSz;
#ifdef PRADEEP_DBG     
/*Pradeep - dubug*/
if (0 == sdu->mode.am.sduId)
{
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] sduId[%d] ###############\n",sdu->mBuf,sdu->mode.am.sduId);
}
#endif 
      /* kw005.201 fix for ccpu00118973 */
      if (pdu == NULLP)
      {
         /* kw003.201 - Check for window stall when you are */
         /*             creating a new PDU                  */
         if (amDl->vtS == amDl->vtMs)
         {
            break;
         }

         /* Eliminate MAC header */
         /* Bug fix: ccpu00119438, 128 is replaced with 127 */
         pduSz -= (pduSz <= 127) ? KW_MAC_HDR_SZ2 : KW_MAC_HDR_SZ3;

         /* Eliminate fixed header size */
         pduSz -= KW_AM_PDU_FIXED_HDRSZ;
        
         /* kw005.201 Check for PDU Size is large enough.
          * Fix for ccpu00118973 
          * */
         if( pduSz <= 0 )
         {
            break;
         }

         /* Initialize the datReq structure */
         cmMemset( (U8 *)&amHdr, 0, sizeof(KwAmHdr) );
         amHdr.sn = amDl->vtS;

         /* Update Framing Info */
         if (sdu->mode.am.isSegmented) 
         {
            amHdr.fi = KW_FI_FIRST_SEG; /* binary 10 */
            sdu->mode.am.isSegmented = FALSE;
         }
         pduCompleted = FALSE;
      }

      /* Eliminate extension hdr size */
      KW_AM_ELIMINATE_EXTN_HDR(pduSz, sduSz, amHdr.numLi);
      amHdr.li[amHdr.numLi++] = sduSz;

      if (pduSz == sduSz)
      {
         /* Exact fit : Either one sdu equals pdu or the last sdu of a pdu */
#ifndef ALIGN_64BIT
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                (gCb->init.prntBuf, "kwAssembleSdus: PduSz matches SduSz for \
                 sduId = %ld \n", sdu->mode.am.sduId));
#else
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                (gCb->init.prntBuf, "kwAssembleSdus: PduSz matches SduSz for \
                 sduId = %d \n", sdu->mode.am.sduId));
#endif

         /* Concatenate sdu to pdu */
         if (pdu == NULLP)
         {
            pdu = sdu->mBuf;     
            sdu->mBuf = NULLP; 
#ifdef PRADEEP_DBG			
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] %s:%d###############\n",pdu,__FUNCTION__,__LINE__);
#endif
         }
         else
         {
            SCatMsg (pdu, sdu->mBuf, M1M2); 
#ifdef PRADEEP_DBG			 
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] after SCatMsg() %s:%d ###############\n",pdu,__FUNCTION__,__LINE__);
#endif
         }

#ifdef LTE_L2_MEAS_RLC
         kwUtlUpdSduSnMap(rbCb, sdu, kwDatReq, TRUE);
#endif /*  LTE_L2_MEAS_RLC */
         /* Create PDU with hdr and data */
         pduCompleted = kwCreatePdu(gCb,rbCb, &amHdr, pdu);
#ifdef PRADEEP_DBG		 
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] after kwCreatePdu() %s:%d ###############\n",pdu,__FUNCTION__,__LINE__);
#endif
         /* For estHdrSz */
         amDl->numSduPdu++; 
         /* kw005.201 ccpu00117318, updating the statistics */
         kwuSapCb->sts.sduTx++;
      }
      else if (pduSz > sduSz)
      {
         /* Concatenation: Join SDU to PDU */
#ifndef ALIGN_64BIT
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                (gCb->init.prntBuf, "kwAssembleSdus: Concatenation for \
                 sduId = %ld \n", sdu->mode.am.sduId));
#else
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                (gCb->init.prntBuf, "kwAssembleSdus: Concatenation for \
                 sduId = %d \n", sdu->mode.am.sduId));
#endif

         /* SGetMsg (*gCb.rguSap.pst.region, *gCb.rguSap.pst.pool, &mBuf); */

         /* Concatenate sdu to pdu */
         if (pdu == NULLP)
         {
            pdu = sdu->mBuf;      
            sdu->mBuf = NULLP; 
#ifdef PRADEEP_DBG			
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] %s:%d###############\n",pdu,__FUNCTION__,__LINE__);
#endif
         }
         else
         {
            SCatMsg(pdu, sdu->mBuf, M1M2);
#ifdef PRADEEP_DBG			
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] after SCatMsg() %s:%d ###############\n",pdu,__FUNCTION__,__LINE__);
#endif
         }
#ifdef LTE_L2_MEAS_RLC
         kwUtlUpdSduSnMap(rbCb, sdu, kwDatReq, TRUE);
#endif /*  LTE_L2_MEAS_RLC */

         /* This sdu completes the PDU with the following condition */
         /* kw005.201: Fix for ccpu00117216 and ccpu00118284 */
         if ( (sduSz > 2048) || (amHdr.numLi >= KW_MAX_LI) )
         {
            /* Create PDU with hdr and data */
            pduCompleted = kwCreatePdu(gCb,rbCb, &amHdr, pdu);
#ifdef PRADEEP_DBG			
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] after kwCreatePdu() %s:%d ###############\n",pdu,__FUNCTION__,__LINE__);
#endif
         }
         
         /* For estHdrSz */
         amDl->numSduPdu++; 
         /* kw005.201 ccpu00117318, updating the statistics */
         kwuSapCb->sts.sduTx++;
      }
      else 
      {
         /* Segmentation
          * Allocate buffer for next PDU
          * Remove the segmented portion from SDUQ 
          * Calculate the hdr with LI for SDU */
         Buffer  *remSeg = NULLP;
#ifndef ALIGN_64BIT
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                (gCb->init.prntBuf, "kwAssembleSdus: Segmentation for \
                 sduId = %ld \n", sdu->mode.am.sduId));
#else
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                (gCb->init.prntBuf, "kwAssembleSdus: Segmentation for \
                 sduId = %d \n", sdu->mode.am.sduId));
#endif

         /* SGetMsg (*gCb.rguSap.pst.region, *gCb.rguSap.pst.pool, &mBuf); */

         /* Segment the SDU to the size of the PDU and update header Info */
         SSegMsg (sdu->mBuf, pduSz, &remSeg);
         if (pdu == NULLP)
         {
            pdu = sdu->mBuf;  
#ifdef PRADEEP_DBG			    
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] %s:%d###############\n",pdu,__FUNCTION__,__LINE__);
#endif
         }
         else
         {
            SCatMsg (pdu, sdu->mBuf, M1M2);  
#ifdef PRADEEP_DBG			
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] after SCatMsg() %s:%d ###############\n",pdu,__FUNCTION__,__LINE__);
#endif 
            KW_FREE_BUF(sdu->mBuf);
         }
         /* KW_FREE_BUF(sdu->mBuf); */
         sdu->mBuf = remSeg;
         sdu->sduSz -= pduSz;
         sduSz = pduSz;
         sdu->mode.am.isSegmented = TRUE;

         /* Update FI and Li */
         amHdr.fi |= KW_FI_LAST_SEG; /* 01 */

#ifdef LTE_L2_MEAS_RLC
         kwUtlUpdSduSnMap(rbCb, sdu, kwDatReq, FALSE);
#endif /*  LTE_L2_MEAS_RLC */
         /* Create PDU with hdr and data */
         pduCompleted = kwCreatePdu(gCb,rbCb, &amHdr, pdu);
#ifdef PRADEEP_DBG		 
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] after kwCreatePdu() %s:%d ###############\n",pdu,__FUNCTION__,__LINE__);
#endif
         amDl->nxtTx = sdu;
         nxtTxUpd    = TRUE;
      }

      /* Update bo for boReport */
      amDl->bo -= sduSz;

      sdu->mode.am.pduMap[sdu->mode.am.numPdu++].sn = amHdr.sn;
      sduMap[numSdu].sduId = sdu->mode.am.sduId;
      sduMap[numSdu].sduSz = sduSz;
      sduMap[numSdu].actSz = sduSz;
      sduMap[numSdu++].isSegmented = sdu->mode.am.isSegmented;

      if (pduCompleted)
      {
         U8 i;
         KwTx *txBuf;

         /* Update pduInfo */
         kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = pdu; 
         kwDatReq->pduInfo.numPdu++;
         /* kw005.201 ccpu00117318, updating the statistics */
         gCb->genSts.pdusSent++;

         /* Update the RLC Tx buffer with the new PDU info */
         txBuf = amDl->txBuf[amHdr.sn];
         txBuf->numSdu = numSdu;
         for (i = 0; i < numSdu; i++)
         {
            txBuf->sduMap[i] = sduMap[i];
         }

         /* initialize the loop variables that are per PDU */
         pdu = NULLP;
         numSdu = 0;
      }

      pduSz -= sduSz;

#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
      dataVol += sduSz;
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */

      /* Get next sdu for assembly */
      KW_LLIST_NEXT_SDU(amDl->sduQ, sdu);
   }

#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
   /* Calculate DL IP throughput */
   kwAmmCalDlIpThrPut(rbCb, dataVol, initialBo, kwDatReq->pduSz);
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */

#ifdef PRADEEP_DBG
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] %s:%d###############\n",pdu,__FUNCTION__,__LINE__);
#endif
   /* Updating nxtTx to sdu in the Q */
   if (!nxtTxUpd)
      amDl->nxtTx = sdu;

   if ((pdu != NULLP) && (pduSz > 0) && (sdu == NULLP)) 
   {
      U8 i;

      if (!pduCompleted)
      {
         KwTx *txBuf;

         /* Create PDU with hdr and data */
         pduCompleted = kwCreatePdu(gCb,rbCb, &amHdr, pdu);
#ifdef PRADEEP_DBG		 
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] %s:%d###############\n",pdu,__FUNCTION__,__LINE__);
#endif 
#if (ERRCLASS & ERRCLS_DEBUG)
         if (pduCompleted == FALSE)
         {
            KWLOGERROR(gCb,ERRCLS_DEBUG, EKW005, (ErrVal) pduCompleted,
                  "kwAssembleSdus: kwCreatePdu Failed.\n");
         }
#endif /* ERRCLASS & ERRCLS_DEBUG */

         kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = pdu; 
         kwDatReq->pduInfo.numPdu++;
         /* kw005.201 ccpu00117318, updating the statistics */
         gCb->genSts.pdusSent++;
#ifdef PRADEEP_DBG		 
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] %s:%d###############\n",pdu,__FUNCTION__,__LINE__);
#endif 
         pdu = NULLP;


         /* Update PDU /SDU Map */
         KW_LLIST_LAST_SDU(amDl->sduQ, sdu); 
         
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (sdu == NULLP)
         {
            KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW006, (ErrVal)0,
                  "kwAssembleSdus: sdu is NULL\n");
            RETVALUE(RFAILED);
         }
#endif /* ERRCLASS & ERRCLS_RES */

         sdu->mode.am.pduMap[sdu->mode.am.numPdu].sn = amHdr.sn;
         txBuf = amDl->txBuf[amHdr.sn];
         txBuf->numSdu = numSdu;

         for (i = 0; i < numSdu; i++)
         {
            txBuf->sduMap[i] = sduMap[i];
         }
      }
   }
   
#ifndef ALIGN_64BIT
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
         (gCb->init.prntBuf, "kwAssembleSdus: BO after assembly = %ld \n",\
          amDl->bo));
#else
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
         (gCb->init.prntBuf, "kwAssembleSdus: BO after assembly = %d \n",\
          amDl->bo));
#endif


   RETVALUE(ROK);
} /* kwAssembleSdus */

/**
 *
 * @brief Private handler to check if the poll bit needs to be set for data PDU
 *
 * @b Description
 *        Its a private function called by kwProcessSdus, to checks if the 
 *        polling bit needs to be set for any RLC data PDU and updates the 
 *        same.
 *        - For the new PDUs, if the counters exceed the configured 
 *          pduWoPoll/byteWoPoll values, return poll bit.
 *        - For the PDUs/portion of PDUs, if the SDU list / retxBuf is 
 *          empty, return poll bit.
 *        - Update the pollPdu, pollByte counters and Poll_SN; start staProhTmr 
 *
 * @param[in]  rbCb     RB control block 
 * @param[in]  newPdu   Flag to indicate if its a new AMD PDU. 
 *
 *  @return  Bool 
 *      -# 1 - To set the poll bit
 *      -# 0 - Poll bit is not set
 *
 */
#ifdef ANSI
PRIVATE Bool kwChkandSetPoll
(
KwCb                   *gCb,
KwDlRbCb               *rbCb,
Bool                   newPdu,
MsgLen                 bufSz
)
#else
PRIVATE Bool kwChkandSetPoll(gCb, rbCb, newPdu, bufSz)
KwCb                   *gCb;
KwDlRbCb               *rbCb;
Bool                   newPdu;
MsgLen                 bufSz;
#endif
{ 
   KwSn                mSn;
   KwSn                vtA;
   KwSn                vtMs;
   Bool                pollBit = FALSE;
   KwAmDl              *amDl = &(rbCb->m.amDl);

   TRC2(kwChkandSetPoll)

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwChkandSetPoll(rbCb, newPdu, bufSz) \n"));
 
   /* Check if its a new PDU */ 
   if (newPdu)
   {
      amDl->pduWoPoll++;
      /* Patch kw004.201 */
      amDl->byteWoPoll += bufSz;

     if (((amDl->pollPdu != -1) && (amDl->pduWoPoll >= amDl->pollPdu)) || 
         ((amDl->pollByte != -1) && (amDl->byteWoPoll >= amDl->pollByte))) 
     {
        pollBit = TRUE;
     }
   }
   MODAMT(amDl->vtA, vtA, amDl->vtA); 
   MODAMT(amDl->vtS, mSn, amDl->vtA);
   MODAMT(amDl->vtMs, vtMs, amDl->vtA);

   /* Check if both tx/retx buffer are empty or if tx window is stalled */
   if (((amDl->nxtTx == NULLP) && (amDl->nxtRetx == NULLP)) ||
       (!((vtA <= mSn) && (mSn < vtMs))))
   {
      pollBit = TRUE;
   }
   

   if (pollBit)
   {
      amDl->pduWoPoll  = 0;
      amDl->byteWoPoll = 0;

      amDl->pollSn = (amDl->vtS) ? amDl->vtS - 1 : 1023;

      KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
            (gCb->init.prntBuf, "kwChkandSetPoll: Poll SN = %d \n", amDl->pollSn));

      /* kw005.201: Fix for poll retransmission timer. 
       * Timer is stopped if it is already running and 
       * then starting the timer. Fixes crs 
       * ccpu00117216 and ccpu00118284 .
       * */
      if( TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_AMDL_POLL_RETX_TMR) )
      {
         kwStopTmr(gCb,(PTR)rbCb, KW_EVT_AMDL_POLL_RETX_TMR);
      }

      kwStartTmr(gCb,(PTR)rbCb, KW_EVT_AMDL_POLL_RETX_TMR);
   }

   RETVALUE(pollBit);
}

/**
 *
 * @brief Private handler to create AMD PDU 
 *
 * @b Description 
 *        This function constructs header and concatenate it with the data for
 *        the PDU. It also updates the txBuf with the created PDU.
 *
 * @param[in]  amDl     AM Downlink Information 
 * @param[in]  amHdr    AM header
 * @param[in]  pdu      PDU buffer 
 *
 *  @return  Bool 
 *      -# 1 - to set the poll bit
 *      -# 0 - poll bit will not be set
 *
 */
#ifdef ANSI
PRIVATE Bool kwCreatePdu
(  
KwCb                 *gCb,
KwDlRbCb             *rbCb,
KwAmHdr              *amHdr,
Buffer               *pdu
)
#else
PRIVATE Bool kwCreatePdu(gCb, rbCb, amHdr, pdu)
KwCb                 *gCb;
KwDlRbCb             *rbCb;
KwAmHdr              *amHdr;
Buffer               *pdu;
#endif
{
   U8                hdr[KW_MAX_HDRSZ];
   U16               idx     = 0;
   Bool              segFlg = FALSE;
   KwTx              *txBuf = NULLP;
   MsgLen            pduSz  = 0;
   /* kw005.201 removed redundant code */
   KwAmDl            *amDl = &(rbCb->m.amDl);

   TRC2(kwCreatePdu)

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwCreatePdu(rbCb, amHdr, pdu) \n"));

   /* Update sn */
   amHdr->sn = amDl->vtS;

   /* Increment vtS */
   amDl->vtS = (amDl->vtS + 1) % 1024;

   /* Update hdr Info */
   amHdr->rf = 0;
   SFndLenMsg(pdu, &pduSz);

   amHdr->p = kwChkandSetPoll(gCb,rbCb, TRUE, pduSz);

   /* Construct header with the available hdr Info */
   kwConstructAmHdr(gCb,amHdr, segFlg, hdr, &idx);

   /* Concatenate hdr and data */
   KW_ADD_PRE_MSG_AM(pdu, hdr, idx+1);
   /* kw005.201 removed redundant code */

   /* Update txBuf */
   KW_ALLOC(gCb,txBuf, sizeof(KwTx));

#if (ERRCLASS & ERRCLS_ADD_RES)
   if (txBuf == NULLP)
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW007, (ErrVal)0,
            "kwCreatePdu: Allocation failed for txBuf \n");
      RETVALUE(FALSE);
   }
#endif /* ERRCLASS & ERRCLS_RES */

   amDl->txBuf[amHdr->sn] = txBuf;

   kwCpyMsg(gCb,pdu,&(txBuf->pdu));
#ifdef PRADEEP_DBG   
 printf("\nRLC Pradeep:kwAssembleSdus() pdu[%x] txBuf->pdu[%x] %s:%d###############\n",pdu,txBuf->pdu,__FUNCTION__,__LINE__);
#endif 
   txBuf->pduSz = pduSz;
   txBuf->hdrSz = idx+1;
   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.bytesSent += pduSz;
   
   KW_MEM_CPY(&txBuf->amHdr, amHdr, sizeof(KwAmHdr));    

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwCreatePdu: Created PDU with SN = %d \n", amHdr->sn));

   RETVALUE(TRUE);
}


/**
 *
 * @brief Private handler to remove the retx PDU from the rbCb
 *
 * @b Description 
 *        This function releases a retx PDU stored on DL portion of rbCb.
 *        It also updates the BO if wtForAck flag is not set which implies
 *        that it is not sent out yet.
 *
 *        fByte - is the first byte removed from the PDU as part of calling
 *                functions
 *
 * @param[in]  retx     retransmit PDU to be removed
 * @param[in]  rbCb     Radio Bearer Control Block
 *
 *  @return Void 
 *
 */
#ifdef ANSI
PRIVATE Void kwRemRetxPdu
(  
KwCb          *gCb,
KwDlRbCb      *rbCb,
KwRetx        *retx,
KwUdxBufLst   *rlsPduLst
)
#else
PRIVATE Void kwRemRetxPdu(gCb, rbcb, retx, rlsPduLst)
KwCb          *gCb;
KwDlRbCb      *rbCb;
KwRetx        *retx;
KwUdxBufLst   *rlsPduLst;
#endif
{
   TRC2(kwRemRetxPdu)
   cmLListDelFrm(&AMDL.retxLst, &retx->lstEnt); 
   /* kw005.201: fix for ccpu00117216 and ccpu00118284 */
   if( AMDL.retxLst.count == 0)
   {
      AMDL.nxtRetx = NULLP;
   }
   if (retx->wtForAck == FALSE)
   {
      AMDL.retxBo   -= retx->segSz;
      AMDL.estHdrSz -= retx->hdrSz;
   }
#if 0/* UDX */
   KW_FREE_BUF(retx->seg);
   KW_FREE(retx, sizeof(KwRetx));
#else
   cmLListAdd2Tail(&(rlsPduLst->rlsRetxLst), &(retx->lstEnt));
#endif
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief Private handler to mark a retx PDU for further retransmission
 *
 * @b Description 
 *        This function sets a retx PDU that has not been ACKed in the   
 *        received Status PDU for futher retransmission. If the retransmission
 *        limit is reached, it releases the retx PDU and informs the higher
 *        layers about the same.
 *
 * @param[in]  retx     retransmit PDU to be removed
 * @param[in]  rbCb     Radio Bearer Control Block
 *
 *  @return Void 
 *
 */
#ifdef ANSI
PRIVATE Void kwMrkRetxPdu
(
KwCb          *gCb,
KwDlRbCb      *rbCb,
KwRetx        *retx,
KwUdxBufLst   *rlsPduLst
)
#else
PRIVATE Void kwMrkRetxPdu(*gCb, rbcb, retx, rlsPduLst)
KwCb          *gCb;
KwDlRbCb      *rbCb;
KwRetx        *retx;
KwUdxBufLst   *rlsPduLst;
#endif
{
   TRC2(kwMrkRetxPdu)
   if (retx->wtForAck == TRUE)
   {
      if (++retx->retxCnt > AMDL.maxRetx)
      {
         kwAmmSndStaInd(gCb,rbCb, retx);
         kwRemRetxPdu(gCb,rbCb, retx, rlsPduLst);
         RETVOID;
      }
      retx->wtForAck = FALSE;
      AMDL.retxBo   += retx->segSz;
printf("\n+++++++++++++++++++++++++++++++++\n");
printf("sn[%d] segSz[%d] retxBo[%d]",retx->amHdr.sn,retx->segSz,AMDL.retxBo);
printf("\n+++++++++++++++++++++++++++++++++\n");
      AMDL.estHdrSz += retx->hdrSz;
      /* kw003.201 - Needs to be improved */
      if (AMDL.nxtRetx == NULLP)
      {
         AMDL.nxtRetx = retx;
      }
   }
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief Private handler to send higher layers data confirmation
 *
 * @b Description 
 *        This function sends higher layers data confirmation for SDUs which
 *        have been successfully delivered to the peer RLC entity.
 *
 * @param[in]  rbCb     Radio Bearer Control Block
 * @param[in]  sn       SN that is successfully delivered to the peer
 * @param[in]  sduLst   List of SDUs that were part of the PDU
 * @param[in]  numSdu   Number of SDUs in the list
 *
 *  @return Void 
 *
 */
#ifdef ANSI
PRIVATE Void kwAmChkSduMap
(
KwCb                 *gCb,
KwDlRbCb             *rbCb,
KwSn                 sn,
KwSduMap             *sduLst,
U8                   numSdu,
KwUdxBufLst          *rlsPduLst
)
#else
PRIVATE Void kwAmChkSduMap(gCb, rbCb, sn, sduLst, numSdu, rlsPduLst)
KwCb                *gCb;
KwDlRbCb            *rbCb;
KwSn                 sn;
KwSduMap             *sduLst;
U8                   numSdu;
KwUdxBufLst          *rlsPduLst;
#endif
{
   U8    i;
   Bool  notRcvd = FALSE;
   KwSdu *sdu    = NULLP;
   U32   sduId;
   U8    j;
   
   TRC2(kwAmChkSduMap)
   
   for (i = 0; i < numSdu; i++)
   {
      sduId = sduLst[i].sduId;
      KW_LLIST_FIRST_SDU(AMDL.sduQ, sdu);
      while ( (sdu != NULLP) && (sdu->mode.am.sduId != sduId) )
      {
         KW_LLIST_NEXT_SDU(AMDL.sduQ, sdu);
      }
      if (sdu != NULLP)
      {
         for (j = 0; j < sdu->mode.am.numPdu; j++)
         {
            if (sdu->mode.am.pduMap[j].sn == sn)
            {
               sdu->mode.am.pduMap[j].rcvd = TRUE;
               sdu->mode.am.rcvdSz += sduLst[i].sduSz;
            }
            if ((sdu->mode.am.rcvdSz <= sdu->actSz) ||
                (sdu->mode.am.pduMap[j].rcvd == FALSE) ||
                (sdu->mode.am.isSegmented))
            {
               if (sdu->mode.am.rcvdSz == sdu->actSz)
               {
                  notRcvd = FALSE;
               }
               else
               {
                  notRcvd = TRUE;
               }
            }
         }
         if (!notRcvd)
         {
            CmLList *tNode = NULLP;
            /* Send DatCfm for this sdu */
            kwAmmSndDatCfm(gCb,rbCb, sduId);

            /* Remove SDU from the sduQ */
            tNode = &sdu->lstEnt;
            KW_RMV_SDU_LST(gCb,&AMDL.sduQ, sdu, rlsPduLst);
         }
         else
         {
            notRcvd = FALSE;
         }
      }
   }
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

#ifdef KW_BG_DL_PROC
/**
 *
 * @brief Private handler to release a set of PDUs that are queued for release
 *
 * @b Description 
 *        This function should be called up on a trigger at which it is safe
 *        to release a set of PDUs without affecting the TTI response.
 *
 *  @return Void 
 *
 */
#ifdef ANSI
PRIVATE Void kwAmmRlsPdusSet
(
KwCb                  *gCb,
KwDlRbCb              *rbCb
)
#else
PRIVATE Void kwAmmRlsPdusSet(gCb, rbCb)
KwCb                  *gCb;
KwDlRbCb              *rbCb;
#endif
{
#if 0
   S32              idx    = KW_AM_MAX_PDUS_RLS;
   KwTx             *pdu;
   CmLListCp        *lst;

   TRC2(kwAmmRlsPdusSet)

   /* Patch kw004.201 - Release is made at the RB level */
   lst  = &AMDL.toBeRlsLst;
   while((lst->first) && (idx > 0))
   {
      pdu = (KwTx *)(lst->first->node);
      cmLListDelFrm(lst, lst->first);
      kwAmChkSduMap(gCb,rbCb, pdu->amHdr.sn, pdu->sduMap, pdu->numSdu, rlsPduLst);
      KW_FREE_BUF(pdu->pdu);
      KW_FREE(gCb,pdu, sizeof(KwTx));
      idx--;
   }
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
#endif
}
#endif /* KW_BG_DL_PROC */

/**
 *
 * @brief Private handler to mark a PDU successful.
 *
 * @b Description 
 *        This function is called when we receive a STATUS pdu that marks
 *        a PDU as successful. It releases the PDU from RLC entity and 
 *        informs PDCP of successful SDUs delivered as a result of this PDU.
 *
 * @param[in]  rbCb     Radio Bearer Control Block
 * @param[in]  sn       SN that is successfully delivered to the peer
 *
 *  @return Void 
 *
 */
#ifdef ANSI
PRIVATE Void kwAmmSucTxPdu
(
KwCb              *gCb,
KwDlRbCb          *rbCb,
KwSn              sn,
KwUdxBufLst       *rlsPduLst
)
#else
PRIVATE Void kwAmmSucTxPdu(gCb, rbCb, sn, rlsPduLst)
KwCb              *gCb;
KwDlRbCb          *rbCb;
KwSn              sn;
KwUdxBufLst       *rlsPduLst;
#endif
{
#ifdef PRADEEP_DBG
printf("\n################################### RLC Pradeep: freeing pdu[%x] \n",AMDL.txBuf[(sn)]->pdu);
int x = 0;
while (x < AMDL.txBuf[(sn)]->numSdu)
{
   printf("   sduId[%d]",AMDL.txBuf[(sn)]->sduMap[x++].sduId);
}
#endif
   TRC2(kwAmmSucTxPdu)
#ifndef KW_UDX
   kwAmChkSduMap(gCb,rbCb, sn, AMDL.txBuf[(sn)]->sduMap, AMDL.txBuf[(sn)]->numSdu, rlsPduLst);
   KW_FREE_BUF(AMDL.txBuf[(sn)]->pdu);
   KW_FREE(gCb,AMDL.txBuf[sn], sizeof(KwTx));
#else
/* kw005.201 fix for ccpu00118778 */
#if 0
   if(rbCb->rlcId.rbId > 3) /* Enqueue the packet only for DRBs*/
   {
      cmLListAdd2Tail(&AMDL.udxBufLst.rlsTxLst, &(AMDL.txBuf[(sn)]->rlsLnk));
      AMDL.txBuf[(sn)]->rlsLnk.node = (PTR)(AMDL.txBuf[(sn)]);
      AMDL.txBuf[(sn)] = NULLP;
   }
   else
   {
      kwAmChkSduMap(rbCb, sn, AMDL.txBuf[(sn)]->sduMap, 
                                              AMDL.txBuf[(sn)]->numSdu);
      KW_FREE_BUF(AMDL.txBuf[(sn)]->pdu);
      KW_FREE(AMDL.txBuf[sn], sizeof(KwTx));
   }

#else
   kwAmChkSduMap(gCb,rbCb, sn, AMDL.txBuf[(sn)]->sduMap, 
                               AMDL.txBuf[(sn)]->numSdu, rlsPduLst);
   cmLListAdd2Tail(&(rlsPduLst->rlsTxLst), &(AMDL.txBuf[(sn)]->rlsLnk));
   AMDL.txBuf[(sn)]->rlsLnk.node = (PTR)(AMDL.txBuf[(sn)]);
   AMDL.txBuf[(sn)]              = NULLP;
#endif
#endif
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}


/**
 *
 * @brief 
 *
 *        Handler to estimate the header size of the RLC SDUs
 *
 * @b Description: 
 *
 *        This function is used to update the estimated Header size for the BO
 *        report. This function is called when a SDU is queued and also when 
 *        a PDU is formed and sent to the lower layer.
 *            
 *  @param[in] amDl     AM DL Information 
 *  @param[in] type     Type of Operation (Addition or Deletion of SDU)
 *  @param[in] sduCount Number of SDUs which are Added/Deleted.
 *  @return  Void
 *
 */
#ifdef ANSI
PRIVATE Void kwAmmEstHdrSz
(
KwCb             *gCb,
KwAmDl           *amDl,
U8               type
)
#else
PRIVATE Void kwAmmEstHdrSz(gCb, amDl, type, rlsPduLst)
KwCb             *gCb;
KwAmDl           *amDl;
U8               type;
#endif
{
   TRC2(kwAmmEstHdrSz);

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmEstHdrSz(amDl, type)\n"));

   if (type == KW_ADD_SDU)
   {
      amDl->estHdrSz += (amDl->numSduPdu * 2) + (amDl->numSeg * 4);

   }
   else if (type == KW_DEL_SDU)
   {
      amDl->estHdrSz -= (amDl->numSduPdu * 2) + (amDl->numSeg * 4);
   }   
#ifndef ALIGN_64BIT
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmEstHdrSz: estHdrSz = %ld \n", amDl->estHdrSz));
#else
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmEstHdrSz: estHdrSz = %d \n", amDl->estHdrSz));
#endif
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief 
 *
 *        Handler to send Status Indication to PDCP
 *
 * @b Description: 
 *
 *        This function is used to send status indication to PDCP when the 
 *        maximum retransmission threshold value is reached for a PDU.
 *            
 *  @param[in] rbCb     RB control block 
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PRIVATE S16 kwAmmSndStaInd
(
KwCb             *gCb,
KwDlRbCb         *rbCb,
KwRetx           *retx
)
#else
PRIVATE S16 kwAmmSndStaInd(gCb, rbCb, retx)
KwCb             *gCb;
KwDlRbCb         *rbCb;
KwRetx           *retx;
#endif
{
   KwuStaIndInfo *staInd;
   KwKwuSapCb    *kwuSap;
   U8 i;


   TRC2(kwAmmSndStaInd);

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmSndStaInd(rbCb, retx)\n"));

   /* Sap control block */
   kwuSap = gCb->u.dlCb->kwuDlSap + KW_UI_PDCP;

   /* Allocate memory for staInd Info */
   KW_ALLOC(gCb,staInd, sizeof(KwuStaIndInfo));

#if (ERRCLASS & ERRCLS_ADD_RES)
   if (staInd == NULLP)
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW012, (ErrVal)0,
            "kwAmmSndStaInd: Allocation failed for staInd \n");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_RES */

   /* Fill staInd Info */ 
   KW_MEM_CPY(&staInd->rlcId, &rbCb->rlcId, sizeof(CmLteRlcId));    

   staInd->numSdu = retx->numSdu;
   for (i = 0; i < retx->numSdu; i++) 
   {
      staInd->sduId[i] = retx->sduMap[i].sduId;
   }

#ifdef KW_PDCP
#else
   KwUiKwuStaInd(&kwuSap->pst, kwuSap->suId, staInd);
#endif /* KW_PDCP */

   RETVALUE(ROK);
}

/**
 *
 * @brief 
 *
 *        Handler to send Data Confirmation to PDCP
 *
 * @b Description: 
 *
 *        This function is used to send data confirmation to PDCP for each SDU
 *        after an acknowledgment is received for the same. 
 *            
 *  @param[in] rbCb     RB control block 
 *  @param[in] type     Type of Operation( Addition or Deletion of SDU)
 *  @param[in] sduCount Number of SDUs which are Added/Deleted.
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PRIVATE S16 kwAmmSndDatCfm
(
KwCb       *gCb,
KwDlRbCb   *rbCb,                          /* RB context */
U32        sduId                           /* SDU for which datCfm is to be sent */
)
#else
PRIVATE S16 kwAmmSndDatCfm(*gCb, rbCb, sduId)
KwCb       *gCb;
KwDlRbCb *rbCb;                          /* RB context */
U32    sduId;                          /* SDU for which datCfm is to be sent*/
#endif
{
#ifndef KW_PDCP
   KwuDatCfmInfo *datCfm;
#endif
   KwKwuSapCb    *kwuSap;

   TRC2(kwAmmSndDatCfm);

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmSndDatCfm(rbCb, sduId)\n"));

   /* Sap control block */
   kwuSap = gCb->u.dlCb->kwuDlSap + KW_UI_PDCP;

#ifndef KW_PDCP
   /* Allocate memory for datCfm Info */
   KW_ALLOC(gCb,datCfm, sizeof(KwuDatCfmInfo));

#if (ERRCLASS & ERRCLS_ADD_RES)
   if (datCfm == NULLP)
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW015, (ErrVal)0,
            "kwAmmSndDatCfm: Allocation failed for datCfm\n");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_RES */

   /* Fill datCfm Info */ 
   KW_MEM_CPY(&datCfm->rlcId, &rbCb->rlcId, sizeof(CmLteRlcId));    

   datCfm->numSduIds = 1;
   datCfm->sduIds[0] = sduId;
#ifdef PRADEEP_DBG   
printf("\n################## RLC Pradeep kwAmmSndDatCfm(): ueId[%d] rbId[%d] rbType[%d] ############\n",datCfm->rlcId.ueId,datCfm->rlcId.rbId,datCfm->rlcId.rbType);
#endif
#ifndef ALIGN_64BIT
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmSndDatCfm: sduId = %ld \n", sduId));
#else
   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmSndDatCfm: sduId = %d \n", sduId));
#endif
#endif
   /* If trace flag is enabled send the trace indication */
   if(gCb->init.trc == TRUE)
   {
      /* Populate the trace params */
      kwLmmSendTrc(gCb,KWU_EVT_DAT_CFM, NULLP);
   }

#ifdef KW_PDCP
#else
   KwUiKwuDatCfm(&kwuSap->pst, kwuSap->suId, datCfm);
#endif /* KW_PDCP */

   RETVALUE(ROK);
}

/**
 *
 * @brief 
 *
 *        Handler to get the next node to be retransmitted from retxLst
 *
 * @b Description: 
 *
 *        This function is used to get the next node to be retransmitted 
 *        from the retxLst
 *            
 *  @param[in] rbCb     RB control block. 
 *  @param[in] type     Type of Operation( Addition or Deletion of SDU)
 *  @param[in] sduCount Number of SDUs which are Added/Deleted.
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PRIVATE S16 kwGetNxtRetx 
(
KwCb       *gCb,
KwAmDl     *amDl,                          /* AM DL Info */
KwRetx    **retx                           /* Next node to be retransmitted */
)
#else
PRIVATE S16 kwGetNxtRetx(amDl, retx)
KwCb       *gCb;
KwAmDl     *amDl;                          /* AM DL Info */
KwRetx     **retx;                          /* Next node to be retransmitted */
#endif
{
   CmLList *tNode = NULLP;

   TRC2(kwGetNxtRetx);
   /* kw005.201 removed warning */
   UNUSED(amDl);

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwGetNxtRetx(amDl, retx)\n"));
   do
   {
      tNode = &((*retx)->lstEnt);
      tNode = tNode->next;
      
      if (tNode)
      {
         *retx = (KwRetx *)tNode->node;
      }
      else
      {
         *retx = NULLP;
      }

      if (*retx == NULLP) 
      {
         RETVALUE(ROK);
      }

   } while((*retx)->wtForAck);

   RETVALUE(ROK);
}

/**
 *
 * @brief 
 *
 *        Handler to process the re-establishment request received from UIM
 *
 * @b Description:
 *
 * @param [in]    ueId     -  UE Identifier
 * @param [in]    cellId   -  CELL Identifier
 * @param[in]     rbCb     -  RB control block 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 kwDlAmmReEstablish
(
KwCb                *gCb,
CmLteRlcId          rlcId,
Bool                sendReEst,
KwDlRbCb            *rbCb
)
#else
PUBLIC S16 kwDlAmmReEstablish(gCb, rlcId, rbCb)
KwCb              *gCb;
CmLteRlcId        rlcId;
Bool                sendReEst;
KwDlRbCb            *rbCb;
#endif
{
   KwSn   sn    = 0;
   KwSn   mSn   = 0;
   KwSn   mVtS  = 0;
   KwRetx *retx = NULLP;

   KwKwuSapCb *kwKwSap = NULLP;         /* KWU SAP Information */

   TRC2(kwAmmReEstablish);

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmReEstablish(rbCb)\n"));

   AMDL.nxtTx = NULLP;

   /* Discard PDUs / byte segments from the txBuf / retxBuf */
   sn = AMDL.txSn;
   MODAMR(sn, mSn, AMDL.vtA);
   MODAMR(AMDL.vtS, mVtS, AMDL.vtA);

   while (mSn < AMDL.vtS)
   {
      if (AMDL.txBuf[sn])
      {
         KW_FREE_BUF(AMDL.txBuf[sn]->pdu);
         KW_FREE(gCb,AMDL.txBuf[sn], sizeof(KwTx));
      }
 
      sn = (sn + 1) % 1024;
      MODAMR(sn, mSn, AMDL.vtA);   
   }  
   AMDL.txSn = 0;
   AMDL.vtA  = 0;
   AMDL.vtS  = 0;
   AMDL.vtMs = (AMDL.vtA + 512) % 1024;
   AMDL.pollSn  = 0;
   AMDL.bo      = 0;
   AMDL.retxBo  = 0;
   AMDL.cntrlBo = 0;
   AMDL.estHdrSz = 0;
   AMDL.numSduPdu = 0;
   AMDL.numSeg    = 0;
   AMDL.pduWoPoll = 0;
   AMDL.byteWoPoll = 0;

   KW_LLIST_FIRST_RETX(AMDL.retxLst, retx);
   while (retx)
   {

      cmLListDelFrm(&AMDL.retxLst, &retx->lstEnt); 
      KW_FREE_BUF(retx->seg);
      KW_FREE(gCb,retx, sizeof(KwRetx)); 

      KW_LLIST_FIRST_RETX(AMDL.retxLst, retx);
   }
   AMDL.nxtRetx = NULLP;

   kwKwSap = gCb->u.dlCb->kwuDlSap + KW_UI_PDCP;
  
   /* Venki */
#ifndef KW_PDCP
   if (sendReEst)
   {
      KwUiKwuReEstCmpInd(&kwKwSap->pst, kwKwSap->suId, rlcId);
   }
#endif
   RETVALUE(ROK);
} /* kwAmmReEstablish */

/**
 *
 * @brief 
 *
 *        Handler to discard a SDU.
 *
 * @b Description: 
 *
 *        This function is used to discard a SDU after receiving
 *        the Discard Request from UIM. The SDU is discarded if its 
 *        available and is not mapped to any PDU yet.
 *            
 *  @param[in] rbCb   RB control block 
 *  @param[in] sduId  Sdu ID of the SDU to be discarded
 *  @return  S16
 *      -# ROK 
 *
 */

#ifdef ANSI
PUBLIC S16 kwAmmDiscSdu
(
KwCb        *gCb,
KwDlRbCb    *rbCb,                        /* RB Control Block */
U32       sduId                        /* SDU ID */
)
#else
PUBLIC S16 kwAmmDiscSdu(gCb, rbCb, sduId)
KwCb        *gCb;
KwDlRbCb    *rbCb;                        /* RB Control Block */
U32       sduId;                        /* SDU ID */
#endif
{

   KwSdu *sdu = NULLP;
   U32   tSduId = 0; /* nxtTx SDUs sdu Id */

   TRC2(kwAmmDiscSdu);

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmDiscSdu(rbCb, sduId)\n"));

   /* No SDUs available in the queue */
   if (AMDL.nxtTx == NULLP)
      RETVALUE(ROK);

   KW_LLIST_FIRST_SDU(AMDL.sduQ, sdu);

   while (sdu != NULLP)
   {
      if (AMDL.nxtTx == sdu)
      {
         tSduId = sdu->mode.am.sduId;
         break;
      }
      KW_LLIST_NEXT_SDU(AMDL.sduQ, sdu);
   }

   /* SDU has been considered for PDU construction */
   while (sdu != NULLP) 
   {
      if ( (sdu->mode.am.sduId == sduId) && (!sdu->mode.am.isSegmented) )
      {
         CmLList *tNode = NULLP;
         KwSdu *tmpSdu = NULLP;
         if (AMDL.nxtTx == sdu)
         {
            KW_LLIST_NEXT_SDU(AMDL.sduQ, tmpSdu);
            AMDL.nxtTx = tmpSdu; 
         }

#ifdef LTE_L2_MEAS_RLC
         if(rbCb->rbL2Cb.measOn & LKW_L2MEAS_DL_DISC)
         {
            kwUtlSndDiscSduCfm(rbCb, sdu->mode.am.sduId);
         }
#endif /*  LTE_L2_MEAS_RLC */
         tNode = &sdu->lstEnt;
         rbCb->m.amDl.bo -= sdu->sduSz;
         KW_RMV_SDU(gCb,&AMDL.sduQ, sdu);
         /* kw005.201 ccpu00117318, updating the statistics */
         gCb->genSts.numSduDisc++;         
         AMDL.numSduPdu = 1;
         AMDL.numSeg    = 0;
         kwAmmEstHdrSz (gCb,&AMDL, KW_DEL_SDU); 
         break;
      }

      KW_LLIST_NEXT_SDU(AMDL.sduQ, sdu);
   }
   
   RETVALUE(ROK);
} /* kwAmmDiscSdu */

#ifdef ANSI
PUBLIC Void kwSndRlsPduCfm
(
KwCb                *gCb,
KwDlRbCb            *rbCb,
KwUdxBufLst         *rlsPduLst
)
#else
PUBLIC Void kwSndRlsPduCfm(gCb, rbCb, rlsPduLst)
KwCb                *gCb;
KwDlRbCb            *rbCb;
KwUdxBufLst         *rlsPduLst;
#endif
{
   KwUdxDlSapCb   *sapCb;
   Pst            *pst       = NULLP;

   if (rlsPduLst->rlsTxLst.count > 0 || \
       rlsPduLst->rlsRetxLst.count > 0 || \
       rlsPduLst->rlsSduLst.count > 0)
   {
      pst = &(gCb->u.dlCb->udxDlSap->pst);
      if (pst == NULLP)
      {
#if (ERRCLASS & ERRCLS_ADD_RES)
         KWLOGERROR(gCb, ERRCLS_ADD_RES, EKWXXX, (ErrVal)0,
         "kwHndlStaRsp: Failed to find relevant post structure\n");
#endif /* ERRCLASS & ERRCLS_RES */
         KW_FREE(gCb, rlsPduLst, sizeof(KwUdxBufLst));
         RETVOID;
      }

      sapCb = KW_GET_DL_SAPCB(gCb, rbCb);
      KwDlUdxStaUpdCfm(pst, sapCb->suId, &(rbCb->rlcId), rlsPduLst);
   }
   else
   {
      KW_FREE(gCb, rlsPduLst, sizeof(KwUdxBufLst));
   }

 
}

/**
 *
 * @brief 
 *        Handler for Poll retransmit timer expiry
 *
 * @b Description: 
 *
 *        This function is used to handle events upon expiry of Poll
 *        retransmit timer.
 *            
 *  @param[in] rbCb   RB control block 
 *  @return  Void 
 */
#ifdef ANSI
PUBLIC Void kwAmmPollRetxTmrExp
(
KwCb                *gCb,
KwDlRbCb            *rbCb
)
#else
PUBLIC Void kwAmmPollRetxTmrExp(gCb, rbCb)
KwCb                *gCb;
KwDlRbCb            *rbCb;
#endif
{
   S16            ret        = ROK;
   KwRetx         *retx      = NULLP; 
   KwAmDl         *amDl      = &(rbCb->m.amDl);
   KwSn           sn         = 0;
   KwUdxBufLst    *rlsPduLst = NULLP;
   /* kw005.201 ccpu00117495, removed redundant code */

   TRC2(kwAmmPollRetxTmrExp);

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmPollRetxTmrExp(rbCb)\n"));

   KW_ALLOC(gCb, rlsPduLst, sizeof(KwUdxBufLst));
   KW_MEM_ZERO(rlsPduLst, sizeof(KwUdxBufLst));
   if(rlsPduLst == NULLP)
   {
#if (ERRCLASS & ERRCLS_INT_PAR)
      KWLOGERROR(gCb, ERRCLS_INT_PAR, EKW043, (ErrVal) rlsPduLst,
               "kwAmmPollRetxTmrExp: SgetSBuf Failed for rlsPduLst ...!");
#endif /* ERRCLASS & ERRCLS_INT_PAR */
      RETVOID;
   }
   
   /* kw005.201 ccpu00117495, removed redundant code */
   /* kw003.201 - Correcting the logic for determmining whether to do   */
   /*             any transmission of PDU. As per the spec section      */
   /*             5.2.2.3, if there is any to transmit or retransmit,   */
   /*             do nothing. Else, pick up the VT(S) -1 for retx       */
   /*             We have nothing to transmit if window is stalled or   */
   /*             there are no SDUs to be transmitted or if there are   */
   /*             PDUs to be retransmitted.                             */
   if (((amDl->nxtTx == NULLP) || (amDl->vtS == amDl->vtMs)) &&
       (amDl->nxtRetx == NULLP))
   {
      sn = (amDl->vtS - 1) & 0x3ff;
      if (amDl->txBuf[sn] != NULLP)
      {
         ret = kwUpdFrmTxtoRetx(gCb,amDl, &retx, sn, rlsPduLst); 
         if (AMDL.nxtRetx == NULLP)
         {
            AMDL.nxtRetx = retx;
         }
         KW_AM_SND_DSTA_RSP(gCb);
         kwSndRlsPduCfm(gCb, rbCb, rlsPduLst);
         RETVOID;
      }
      /* Get the last node in retxLst */
      KW_LLIST_LAST_RETX(amDl->retxLst, retx);

      /* Unset wtForAck flag for the NACK PDUs */ 
      if (retx != NULLP)
      {
         kwMrkRetxPdu(gCb,rbCb, retx, rlsPduLst);
         KW_AM_SND_DSTA_RSP(gCb);
      }
   }

   kwSndRlsPduCfm(gCb, rbCb, rlsPduLst);

   RETVOID;
} /* kwAmmPollRetxTmrExp*/

/**
 *
 * @brief 
 *
 *        Handler to update Acks for the remaining PDUs after the last accessed
 *        NACK PDU.
 *
 * @b Description: 
 *
 *        This function is used to handle ACKs for the PDUs remaining after the 
 *        last accessed NACK PDU, It updates the txBuf/retxBuf for the ACKs and 
 *        sends DatCfm to PDCP for the same.
 *            
 *
 */

#ifdef ANSI
PRIVATE Void kwUpdRemPduAck
(
KwCb        *gCb,
KwDlRbCb    *rbCb,
KwSn        mAckSn,
CmLList     *retxNode,
KwUdxBufLst *rlsPduLst
)
#else
PRIVATE Void kwUpdRemPduAck(gCb, rbCb, mAckSn, retxNode, rlsPduLst)
KwCb        *gCb;
KwDlRbCb    *rbCb;
KwSn      mAckSn;
CmLList   *retxNode;
KwUdxBufLst *rlsPduLst;
#endif
{
   KwSn    mSn = 0;
   KwSn    sn  = 0;
   KwRetx  *retx;

   TRC2(kwUpdRemPduAck);

   /* Remove pdus/segs from retxLst */ 
   while (retxNode)
   {
      retx = (KwRetx *)(retxNode->node);
      retxNode = retxNode->next;
      MODAMT(retx->amHdr.sn, mSn, AMDL.vtA);
      if (mSn < mAckSn) 
      {
         KW_AM_SUC_RETX_PDU(gCb,rbCb, retx, rlsPduLst);
      }
   }

   /* For the remaining ACKs  after last nackSn */
   MODAMT(AMDL.txSn, mSn, AMDL.vtA);
   sn = AMDL.txSn;
   while(mSn < mAckSn)
   {
      if ((AMDL.txBuf[sn] != NULLP) )
      {
         KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                  (gCb->init.prntBuf, "kwUpdRemPduAck: Handle ACK for PDU with sn = \
                   %d\n", sn));

         /* Remove pdus from txBuf */
         kwAmmSucTxPdu(gCb,rbCb, sn, rlsPduLst);
      }
      mSn++; sn = (sn + 1)%1024;
   }

   RETVOID;
}


/**
 *
 * @brief 
 *
 *        Handler to form construct AM header
 *
 * @b Description: 
 *
 *        This function is used to construct am header with the available header
 *        elements.
 *
 *  @param[in]  amHdr  AM Header
 *  @param[in]  isSeg  Check for Segmentation of PDU
 *  @param[in]  hdr    Header field
 *  @param[in]  idx    Index
 *  
 *  @return Void            
 *
 */

#ifdef ANSI
PRIVATE Void kwConstructAmHdr
(
KwCb        *gCb,
KwAmHdr     *amHdr,
Bool        isSeg,
U8          *hdr,
U16         *idx
)
#else
PRIVATE Void kwConstructAmHdr(gCb, amHdr, isSeg, hdr, idx)
KwCb        *gCb;
KwAmHdr     *amHdr;
Bool        isSeg;
U8          *hdr;
U16         *idx;
#endif
{
   KwHdrInfo hdrInfo;
   U8  e;                                                   
   S16 numLi;                                               
   U8  eb   = 0;                                              

   TRC2(kwConstructAmHdr);
                                                            
   KW_MEM_ZERO(&hdrInfo, sizeof(KwHdrInfo)); 

   hdrInfo.pEb  = 1;
   hdrInfo.pLen = 0;
   /* kw003.201 - Setting it to 0 as it should start at zero */
   hdrInfo.idx  = *idx = 0;

   numLi = amHdr->numLi - 1;                                

   /* For fixed part of the header */                       
   hdr[0] = KW_DATA_PDU;                                    
   hdr[0] = hdr[0] << (KW_BYTE_LEN - KW_DC_LEN);            
   eb = KW_BYTE_LEN - KW_DC_LEN;                            
 
   hdrInfo.hdr = hdr;
   hdrInfo.eb  = eb;

   KW_FILL_HDR_ARGS(hdrInfo, amHdr->rf, KW_RF_LEN); 
   kwFormBits(&hdrInfo);           

   KW_FILL_HDR_ARGS(hdrInfo, amHdr->p, KW_P_LEN);            
   kwFormBits(&hdrInfo);

   KW_FILL_HDR_ARGS(hdrInfo, amHdr->fi, KW_FI_LEN);
   kwFormBits(&hdrInfo);

   e = (numLi > 0) ? 1 : 0;
   KW_FILL_HDR_ARGS(hdrInfo, e, KW_E_LEN);
   kwFormBits(&hdrInfo);

   KW_FILL_HDR_ARGS(hdrInfo, amHdr->sn, KW_SN_LEN);
   kwFormBits(&hdrInfo);

   if (isSeg == TRUE)                                      
   {                                                        
      KW_FILL_HDR_ARGS(hdrInfo, amHdr->lsf, KW_LSF_LEN);
      kwFormBits(&hdrInfo);

      KW_FILL_HDR_ARGS(hdrInfo, amHdr->so, KW_SO_LEN);
      kwFormBits(&hdrInfo);
   }                                                        

   /* For extension part of the header */                   
   if (numLi > 0)                                           
   {                                                        
      U8 count = 0;                                         
      while (count < (amHdr->numLi-1))                                
      {                                                     
         e = (numLi > 1) ? 1 : 0;                           
         KW_FILL_HDR_ARGS(hdrInfo, e, KW_E_LEN);
         kwFormBits(&hdrInfo);

         KW_FILL_HDR_ARGS(hdrInfo, amHdr->li[count], KW_LI_LEN);
         kwFormBits(&hdrInfo);

         count++;
         numLi--;
      }                                                    
   }                                                       

   hdr  = hdrInfo.hdr;
   *idx = hdrInfo.idx;
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief 
 *
 *        Handler to form am header Info
 *
 * @b Description: 
 *
 *        This function is used to assemble AM header Information
 *            
 * @param[in] hdrInfo  Header Information
 * @return Void
 */

#ifdef ANSI
PRIVATE Void kwFormBits
(
KwHdrInfo *hdrInfo
)
#else
PRIVATE Void kwFormBits( hdrInfo)
KwHdrInfo *hdrInfo;
#endif
{
   U16  val  = hdrInfo->val;
   U8   len  = hdrInfo->len;
   U8   eb   = hdrInfo->eb;
   U8   *hdr = NULLP;
   U16  idx  = hdrInfo->idx;
   U8   pEb  = hdrInfo->pEb;
   U8   pLen = hdrInfo->pLen;

   U16 pIdx = idx;                                         
   U16 cIdx = idx + 1;                                     
   U8  tPdu;                                                
   U16 tVal;                                                

   TRC2(kwFormBits);

   hdr = hdrInfo->hdr;

   if (eb >= len)                                         
   {                                                        
      if (pEb - pLen == 0)
      {                                                    
         idx++;
         pIdx = idx;
      }                                                    
      tPdu = (val << (eb - len)) | hdr[pIdx]; 
      hdr[pIdx] = tPdu;                                   
      pEb = eb;                                           
      pLen = len;                                         
      eb = eb - len;       
   }                                                        
   else if (eb < len)                                     
   {                                                        
      tVal = val;                                          
      if (eb != 0)                                         
      {                                                     
         tPdu = (tVal >> (len - eb)) | hdr[pIdx];       
         hdr[pIdx] = tPdu;                                
      }                                                     
      if (len - eb == KW_BYTE_LEN)                        
      {                                                     
         hdr[cIdx] = (U8)tVal;                                
         idx = cIdx;                                       
         pEb = eb;
         pLen = len;                                      
         eb = KW_BYTE_LEN - (len - eb);                  
      }                                                     
      else if (len - eb < KW_BYTE_LEN)                    
      {                                                     
         if (eb == 0)                                     
            hdr[cIdx] = tVal << (KW_BYTE_LEN - len);     
         else                                              
           hdr[cIdx] = tVal << (len - eb);    
         idx = cIdx;                                       
         pEb = eb;                                        
         pLen = len;
         eb = KW_BYTE_LEN - (len - eb);                  
      }                                                     
      else                                                  
      {                                                     
         hdr[cIdx++] = tVal >> ((len - eb) - KW_BYTE_LEN); 
         hdr[cIdx] = tVal << KW_BYTE_LEN; 
         idx = cIdx;                                      
         pEb = eb;
         pLen = len;
         eb = KW_BYTE_LEN - ((len - eb) - KW_BYTE_LEN); 
      }                                                    
   }                                                       

   hdrInfo->val  = val;
   hdrInfo->len  = len;
   hdrInfo->eb   = eb;
   hdrInfo->hdr  = hdr;
   hdrInfo->idx  = idx;
   hdrInfo->pEb  = pEb;
   hdrInfo->pLen = pLen;
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}


/**
 *
 * @brief 
 *
 *        This function adds a retx PDU to list of retx PDUs
 *
 * @b Description: 
 *       kw003.201 - Poll expiry may cause an SN to be added to retx 
 *                   out of sequence and hence all additions to retx 
 *                   must validate that they are added in sequence   
 *
 * @param[in]  amDl  AM Downlink Control Block
 * @param[in]  retx  Retransmit PDU
 * 
 * @return Void
 *            
 *
 */
#ifdef ANSI
PRIVATE Void kwAmmAddPduToRetxLst
(
KwAmDl               *amDl,
KwRetx               *retx
)
#else
PRIVATE Void kwAmmAddPduToRetxLst(amDl, retx)
KwAmDl               *amDl;
KwRetx               *retx;
#endif
{
   CmLList           *node;
   KwRetx            *tRetx;
   KwSn              tMSn;
   KwSn              retxMSn;
   TRC2(kwAmmAddPduToRetxLst);
 
   node = amDl->retxLst.last;
   MODAMT(retx->amHdr.sn, retxMSn, amDl->vtA);
   while(node != NULLP)
   {
      tRetx = (KwRetx *)(node->node);
      MODAMT(tRetx->amHdr.sn, tMSn, amDl->vtA);
      if (tMSn > retxMSn)
      {
         node = node->prev;
      }
      else
      {
         break;
      }
   }
   if (node)
   {
      amDl->retxLst.crnt = node;
      cmLListInsAfterCrnt(&amDl->retxLst, &retx->lstEnt);
      retx->lstEnt.node = (PTR)retx;
   }
   else
   {
      amDl->retxLst.crnt = amDl->retxLst.first;
      cmLListInsCrnt(&amDl->retxLst, &retx->lstEnt);
      retx->lstEnt.node = (PTR)retx;
   }

   if (amDl->nxtRetx == NULLP)
   {
      amDl->nxtRetx = retx;
   }
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief 
 *
 *        Handler to Move the PDU from txBuf to retxLst 
 *
 * @b Description: 
 *
 *        This function is used to move the PDU from the txBuf to retxLst
 *
 * @param[in]  amDl  AM Downlink Control Block
 * 
 * @return Void
 *            
 *
 */

#ifdef ANSI
PRIVATE S16 kwUpdFrmTxtoRetx
(
KwCb   *gCb,
KwAmDl *amDl,           /* AM DL Info */
KwRetx **retx,          /* Retransmission buffer for the PDU */
KwSn   sn,              /* PDU's SN to be moved to retxLst */
KwUdxBufLst *rlsPduLst
)
#else
PRIVATE S16 kwUpdFrmTxtoRetx(gCb,amDl, retx, sn, rlsPduLst)
KwCb   *gCb;
KwAmDl *amDl;           /* AM DL Info */
KwRetx **retx;          /* Retransmission buffer for the PDU */
KwSn   sn;              /* PDU's SN to be moved to retxLst */
KwUdxBufLst *rlsPduLst;
#endif
{
   U8 i;

   TRC2(kwUpdFrmTxtoRetx);

   KWDBGP(gCb,(KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwUpdFrmTxtoRetx(amUl, sn, so)\n"));

   KW_ALLOC(gCb,*retx, sizeof(KwRetx));

#if (ERRCLASS & ERRCLS_ADD_RES)
   if (*retx == NULLP)
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW018, (ErrVal)0,
            "kwUpdFrmTxtoRetx: Allocation failed for retxBuf \n");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_RES */

   (*retx)->seg = amDl->txBuf[sn]->pdu;
   (*retx)->segSz = amDl->txBuf[sn]->pduSz;
   (*retx)->hdrSz = amDl->txBuf[sn]->hdrSz;
   (*retx)->numSdu = amDl->txBuf[sn]->numSdu;
   (*retx)->retxCnt = 1;

   for (i = 0; i < (*retx)->numSdu; i++)
   {
      (*retx)->sduMap[i].sduId = amDl->txBuf[sn]->sduMap[i].sduId;
      (*retx)->sduMap[i].sduSz = amDl->txBuf[sn]->sduMap[i].sduSz;
      (*retx)->sduMap[i].actSz = amDl->txBuf[sn]->sduMap[i].actSz;
      (*retx)->sduMap[i].isSegmented = amDl->txBuf[sn]->sduMap[i].isSegmented;
   }

   KW_MEM_CPY(&((*retx)->amHdr), &amDl->txBuf[sn]->amHdr, sizeof(KwAmHdr));
   (*retx)->amHdr.lsf = 1;
   kwAmmAddPduToRetxLst(amDl, (*retx));

   /* Remove PDU from txBuf */
#if 1 /* UDX */
   KW_FREE(gCb, amDl->txBuf[sn], sizeof(KwTx));
#else
   cmLListAdd2Tail(&(rlsPduLst->rlsTxLst), &(amDl->txBuf[(sn)]->rlsLnk));
   amDl->txBuf[(sn)]->rlsLnk.node = (PTR)(amDl->txBuf[(sn)]);
   amDl->txBuf[(sn)] = NULLP;

#endif

   /* Update the BO appropriately */
   amDl->retxBo   += (*retx)->segSz;
   amDl->estHdrSz += (*retx)->hdrSz;

   RETVALUE(ROK);
}

/*@}*/

  
/********************************************************************30**
  
         End of file:     kw_amm_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:42 2014
  
*********************************************************************31*/


/********************************************************************40**
  
        Notes:
  
*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/

   
/********************************************************************60**
  
        Revision history:
  
*********************************************************************61*/
  
/********************************************************************90**

     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---       nm         1. Initial release.
/main/2      ---       nm         1. LTERLC Release 2.1.
/main/3      kw001.201 vp         1. Patch  for HENB, changes for max RBs
                                  in cell and avoidance of float variables.
/main/4      kw002.201 vp         1. Patch for optimization,fixes for multi-region
                                     and retransmission.
/main/5      kw003.201 vp         1. Fixes for re-segmentation, segement offset
                                     value and optimization
/main/6      kw004.201 av         1. Adding of missing trace in RLC PDCP
                                  2. Modified the definition of kwAmmRlsPdusSet
                                  3. byteWoPoll assignement have been corrected in 
                                     the function kwChkandSetPoll.
/main/7      kw005.201 ap         1. Removed redundant code from function kwCreatePdu and
                                     kwAmmPollRetxTmrExp.
                                  2. Removed warning from the code.
                                  3. Updated statistics in the code.
                                  4. Added L2 Measurement feature.
                                  5. Fixed the problem in AssembleSdu function when pduSz is
                                     less than minimum rlc header size. Fix for ccpu00118973
                       rd         6. Added changes in function kwAmmProcessPdus for RLC
                                     R9 upgrade corresponding to CR0083 and CR0090.
                                     Added a condition for stopping the t-reordering 
                                     timer. Updation of VR(H) is moved before the 
                                     updation of VR(MS).
                                  7. The "=" in the condition for triggering the status
                                     report is removed according to product CR 
                                     ccpu00117114 in function kwTriggerStatus.
                                  8. Added code for L2 Meas DL/UL ip throughput.
                                  9. Incorporated the important Avtecs comments.
                                 10. Bug fix: ccpu00119438.
*********************************************************************91*/

