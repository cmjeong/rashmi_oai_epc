

/********************************************************************20**
  
        Name:    RLC - AM module file
    
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

        Sid:      kw_amm_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:43 2014
 
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
#include "kw_udx.h"
#include "kw_err.h"        /* Err defines */
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
#include "kw_ul.h"

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
#include "kw_ul.x"
#include "kw_udx.x"


/* local defines */

/* local externs */

/* forward references */

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

#define KW_AM_SUC_RETX_PDU(_rbCb, _retx) do { \
   kwAmChkSduMap((_rbCb), (_retx)->amHdr.sn, (_retx)->sduMap, \
                 (_retx)->numSdu); \
   kwRemRetxPdu((_rbCb), (_retx));\
} while(0)

#define KW_AM_RMV_HDR(_rbCb, _retx) do { \
  if ((_retx)->yetToConst == FALSE) \
  {\
     Buffer    *_tSeg; \
     SSegMsg ((_retx)->seg, (_retx)->hdrSz, &_tSeg); \
     KW_FREE_BUF((_retx)->seg); \
     (_retx)->seg = _tSeg; \
  }\
  (_rbCb)->m.am.amDl.estHdrSz -= retx->hdrSz;\
} while(0)

#define KW_AM_SND_DSTA_RSP() do {\
   U32        _bo;\
   KW_UPD_AMBO(AMDL, _bo);\
   kwUtlSndDStaRsp(rbCb, _bo, AMDL.estHdrSz, AMDL.cntrlBo ? TRUE : FALSE); \
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

#if 0
PRIVATE S16  kwAssembleCntrlInfo ARGS ((KwCb *gCb, KwUlRbCb *rbCb, KwDatReq *kwDatReq));
#endif
PRIVATE S16  kwAssembleCntrlInfo ARGS ((KwCb *gCb, KwUlRbCb *rbCb));
PRIVATE Void kwFormCntrlBits ARGS ((KwCb *gCb,KwCntrlInfo *cntrlInfo,
                                    U16  *staPdu,U16  *maxCPduLen));
PRIVATE S16  kwExtractHdr ARGS ((KwCb *gCb,KwUlRbCb *rbCb, 
                          Buffer *pdu, KwAmHdr *amHdr, U8 *fByte));
PRIVATE Bool kwPlcPduInRecBuf ARGS ((KwCb *gCb,Buffer *pdu, KwUlRbCb *rbCb, 
                                 KwAmHdr *amHdr));
PRIVATE Void kwTriggerStatus ARGS ((KwCb *gCb,KwUlRbCb *rbCb, KwSn sn, Bool discFlg));
PRIVATE Void kwUpdCntrlBo ARGS ((KwCb *gCb,KwAmUl *amUl));
PRIVATE S16  kwReassembleSdus ARGS ((KwCb *gCb,KwUlRbCb *rbCb, 
                                              KwAmRecBuf **recBuf));
PRIVATE Void kwAmmUpdExpByteSeg ARGS ((KwCb *gCb,KwAmUl *amUl, KwSeg* newSeg));
PRIVATE Void kwExtractElmnt ARGS ((KwCb *gCb,Buffer *pdu, KwExtHdr *hdrInfo));

PRIVATE S16 kwHndlStaRsp ARGS (( KwCb *gCb, KwUlRbCb *rbCb, Buffer *cntrlPdu, U8 *fByte));

#ifdef KW_BG_DL_PROC
PRIVATE Void kwAmmRlsPdusSet ARGS((KwUlRbCb *rbCb));
#endif /* KW_BG_DL_PROC */
/** @file gp_amm.c
@brief RLC Acknowledged Mode Module
*****************************************************************************

  AM Module contains the following funcitons:

  -  kwAmmQSdu 
  -  kwAmmProcessSdus
     -  kwAssembleCntrlInfo
     -  kwResegRetxPdus
     -  kwAssembleSdus
     -  kwChkandSetPoll
  -  kwAmmProcessPdus
     -  kwHndlStaRsp
     -  kwTriggerStatus
     -  kwReassembleSdus
   
*******************************************************************************/
/** @addtogroup ammode */
/*@{*/

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
#if 0
#ifdef ANSI
PRIVATE S16 kwAssembleUlCntrlInfo 
(
KwUlRbCb                  *rbCb
)
#else
PRIVATE S16 kwAssembleUlCntrlInfo(rbCb)
KwUlRbCb                  *rbCb;
#endif
{

   KwSn       sn;                      /* sequence number */
   KwSn       mSn;                     /* Mod val of sequence number */
   KwSn       vrMs;                    /* Mod val of vrMs */
   KwSn       ack_sn;                  /* Ack sequence number */
   Buffer     *mBuf = NULLP;           /* control pdu buffer */
   MsgLen     cntrlPduSz = 0;          /* control pdu size */
   KwSeg      *seg    = NULLP;         /* pdu segment */ 
   Bool       partSeg  = FALSE;         /* Flag to indicate partial segment
                                           construction in cntrl PDU */
   U16        staPdu[(KW_MAX_CNTRL_FIELDS + 1)/2];     /* status pdu array */
   U8         cntrlPdu[KW_MAX_CNTRL_FIELDS];   /* control pdu to be added to mBuf */
   U16        idx     = 0;             /* Index for staPdu */
   U8         emtBits = 0;             /* empty bits */
   U16        e1      = 0;             /* E1 */
   U16        e1Idx   = 0;             /* E1 Index */
   U16        e2Idx   = 0;             /* E2 Index */
   U8         e1eb    = 0;             /* empty bits after E1 */
   U16        soStart = 0;             /* segment offset start */
   U16        soEnd   = 0;             /* segment offset end */
   U16        seqSo   = 0;             /* segmment offset */
   U16        i       = 0;             /* Index for staPdu */
   U16        j       = 0;             /* Index for controlPdu */
   KwSn       tSn     = 0;
   U16        cntrlIdx= 0;
   KwUdxCntrlInfo  *cntrlInfo;

   TRC2(kwAssembleCntrlInfo)

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAssembleCntrlInfo(rbCb, kwDatReq) \n"));

   KW_MEM_ZERO(&cntrlInfo, sizeof(KwCntrlInfo)); 

   KW_ALLOC(cntrlInfo, sizeof(KwUdxCntrlInfo));
   KW_MEM_ZERO(cntrlInfo, sizeof(KwUdxCntrlInfo)); 

   /* Add E1 to ACK_SN */
   KW_FILL_UL_CNTRL_INFO(cntrlInfo, e1, KW_E1_LEN, cntrlIdx);

   sn = AMUL.vrR;
   MODAMR(sn, mSn, AMUL.vrR);
   MODAMR(AMUL.vrMs, vrMs, AMUL.vrR);

   while (mSn < vrMs)
   {
      /* For missing PDUs */
      if (AMUL.recBuf[sn] == NULLP)
      {
         tSn = sn; 

         KWDBGP((KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
               (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing PDU's SN = %d\n", sn));

         
         /* For NACK_E1E2, lsh by 2 to append e1, e2 value */
         tSn = sn << 2;
         KW_FILL_ULCNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, cntrlIdx);  
      }   
      else
      {
         if ( (AMUL.recBuf[sn]->pdu == NULLP) && 
              (AMUL.recBuf[sn]->segLst.count > 0) )
         {
            /* Scan through the byte segments of PDU and add this sn 
               with soStart and soEnd info to staPdu */

            seqSo  = 0;
            KW_LLIST_FIRST_SEG(AMUL.recBuf[sn]->segLst, seg); 
            while (seg != NULLP)
            {
               /* For missing byte segments */
               if (seg->amHdr.so != seqSo)
               {
                  tSn = sn;

                  /* set E2 */
                  tSn = sn << 2;
                  tSn |= 1;  

                  /* Add NACK_SN, E1 and E2 to staPdu */
                  KW_FILL_CNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, cntrlIdx); 
                  cntrlInfo->isSegment = TRUE;

                  /* Add soStart and soEnd */
                  soStart = seqSo;
                  soEnd = seg->amHdr.so - 1; 
                  KW_FILL_UL_CNTRL_INFO(cntrlInfo, soStart, KW_SO_LEN, cntrlIdx);
                  KW_FILL_UL_CNTRL_INFO(cntrlInfo, soEnd, KW_SO_LEN, cntrlIdx);

                  KWDBGP((KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                        (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing byte segment's"
                         " SN, soStart and soEnd = %d, %d, %d \n", sn, soStart,
                         soEnd));
               }
               seqSo = seg->soEnd + 1;
               KW_LLIST_NEXT_SEG(AMUL.recBuf[sn]->segLst, seg);
            } 

            /* Check if the last segment is missing */
            KW_LLIST_LAST_SEG(AMUL.recBuf[sn]->segLst, seg);
            if ((seg != NULLP) && (seg->amHdr.lsf != 1))
            {
               tSn = sn;

               /* set E2 */
               tSn = sn << 2;
               tSn |= 1;  

               /* Add NACK_SN, E1 and E2 to staPdu */
               KW_FILL_CNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, cntrlIdx);  
               cntrlInfo->isSegment = TRUE;

               soStart = seqSo;
               soEnd = AMUL.recBuf[sn]->pduSz;
               soEnd = KW_ALL_BYTES_MISSING;
               KW_FILL_CNTRL_INFO(cntrlInfo, soStart, KW_SO_LEN, cntrlIdx);
               KW_FILL_CNTRL_INFO(cntrlInfo, soEnd, KW_SO_LEN, cntrlIdx);

               KWDBGP((KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                     (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing (last) byte "
                      "segment's SN, soStart and soEnd = %d, %d, %d \n",
                      sn, soStart, soEnd));
            }

         }
      }
      sn = (sn + 1) % 1024;
      MODAMR(sn, mSn, AMUL.vrR);
   }

   /* Update ack_sn with the last sn for which feedback is not assembled */
   if (mSn == vrMs)
   {
      ack_sn = AMUL.vrMs;
   }
   else if (partSeg)
   {
      ack_sn = sn - 1;
   }
   else
   {
      ack_sn = sn;
   }


   KWDBGP((KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
         (gCb->init.prntBuf, "kwAssembleCntrlInfo: ACK PDU's SN = %d\n", ack_sn));

   AMUL.staTrg = FALSE;
   cntrlInfo->cntrlBo = AMUL.cntrlBo;

   KwUdxUlmDlmUlStaPdu(pst, cntrlInfo);

   RETVALUE(ROK);
}
#endif

#if 1
#ifdef ANSI
PRIVATE S16 kwAssembleCntrlInfo 
(
KwCb                      *gCb,
KwUlRbCb                  *rbCb
)
#else
PRIVATE S16 kwAssembleCntrlInfo(gCb, rbCb)
KwCb                      *gCb;
KwUlRbCb                  *rbCb;
#endif
{

   KwCntrlInfo   cntrlInfo;
   KwSn          sn;                      /* sequence number */
   KwSn          mSn;                     /* Mod val of sequence number */
   KwSn          vrMs;                    /* Mod val of vrMs */
   KwSn          ack_sn;                  /* Ack sequence number */
   Buffer        *mBuf = NULLP;           /* control pdu buffer */
   MsgLen        cntrlPduSz = 0;          /* control pdu size */
   KwSeg         *seg    = NULLP;         /* pdu segment */ 
   Bool          partSeg  = FALSE;         /* Flag to indicate partial segment
                                              construction in cntrl PDU */
   U16           staPdu[(KW_MAX_CNTRL_FIELDS + 1)/2];     /* status pdu array */
   U8            cntrlPdu[KW_MAX_CNTRL_FIELDS];   /* control pdu to be added to mBuf */
   U16           idx     = 0;             /* Index for staPdu */
   U8            emtBits = 0;             /* empty bits */
   U16           e1      = 0;             /* E1 */
   U16           e1Idx   = 0;             /* E1 Index */
   U16           e2Idx   = 0;             /* E2 Index */
   U8            e1eb    = 0;             /* empty bits after E1 */
   U16           soStart = 0;             /* segment offset start */
   U16           soEnd   = 0;             /* segment offset end */
   U16           seqSo   = 0;             /* segmment offset */
   U16           i       = 0;             /* Index for staPdu */
   U16           j       = 0;             /* Index for controlPdu */
   KwSn          tSn     = 0;
   U16           maxCPduLen = KW_MAX_CNTRL_FIELDS;
   KwUdxDlStaPdu *dlStaPdu;
   S16           ret;
   KwUdxUlSapCb  *sapCb;

   TRC2(kwAssembleCntrlInfo)

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAssembleCntrlInfo(rbCb) \n"));

   sapCb = KW_GET_UDX_SAP(gCb); 

   KW_MEM_ZERO(&cntrlInfo, sizeof(KwCntrlInfo)); 

   KW_ALLOC(gCb, dlStaPdu, sizeof(KwUdxDlStaPdu));
   /* Add ACK_SN */
   ack_sn = 0;
   staPdu[idx] = ack_sn;

   /* Empty bits left after ACK_SN -  2 bits */
   emtBits = 2;

   /* Add E1 to ACK_SN */
   KW_FILL_CNTRL_INFO(cntrlInfo, e1, KW_E1_LEN, idx, emtBits);
   kwFormCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
   idx = cntrlInfo.idx;
   emtBits = cntrlInfo.emtBits;

   e1Idx = 0;
   e2Idx = 0;
   e1eb = 0;

   sn = AMUL.vrR;
   MODAMR(sn, mSn, AMUL.vrR);
   MODAMR(AMUL.vrMs, vrMs, AMUL.vrR);

   while (mSn < vrMs)
   {
      /* For missing PDUs */
      if (AMUL.recBuf[sn] == NULLP)
      {
         tSn = sn; 

         KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
               (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing PDU's SN = %d\n", sn));

         /* set prev E1 */
         staPdu[e1Idx] = staPdu[e1Idx] | KW_POWER(2, (e1eb+1));
         
         /* Add NACK_SN, E1 and E2 to staPdu */

         /* For NACK_E1E2, lsh by 2 to append e1, e2 value */
         tSn = sn << 2;
         KW_FILL_CNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, idx, emtBits);  
         kwFormCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
         KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, emtBits);
      }   
      else
      {
         if ( (AMUL.recBuf[sn]->pdu == NULLP) && 
              (AMUL.recBuf[sn]->segLst.count > 0) )
         {
            U16 tIdx = idx; 
            U8  teb = emtBits;

            /* Scan through the byte segments of PDU and add this sn 
               with soStart and soEnd info to staPdu */

            seqSo  = 0;
            KW_LLIST_FIRST_SEG(AMUL.recBuf[sn]->segLst, seg); 
            while (seg != NULLP && maxCPduLen > 0 )
            {
               /* For missing byte segments */
               if (seg->amHdr.so != seqSo)
               {
                  tSn = sn;
                  /* set prev E1 */
                  staPdu[e1Idx] = staPdu[e1Idx] | KW_POWER(2, (e1eb+1));

                  /* set E2 */
                  tSn = sn << 2;
                  tSn |= 1;  

                  /* Add NACK_SN, E1 and E2 to staPdu */
                  KW_FILL_CNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, idx, 
                                     emtBits);  
                  kwFormCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
                  KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, 
                                   emtBits); 

                  /* Add soStart and soEnd */
                  soStart = seqSo;
                  soEnd = seg->amHdr.so - 1; 
                  KW_FILL_CNTRL_INFO(cntrlInfo, soStart, KW_SO_LEN, idx, 
                                     emtBits);
                  kwFormCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
                  KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, 
                                   emtBits); 

                  KW_FILL_CNTRL_INFO(cntrlInfo, soEnd, KW_SO_LEN, idx, 
                                     emtBits);
                  kwFormCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
                  KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, 
                                   emtBits);

                  KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                        (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing byte segment's"
                         " SN, soStart and soEnd = %d, %d, %d \n", sn, soStart,
                         soEnd));
               }
               seqSo = seg->soEnd + 1;
               KW_LLIST_NEXT_SEG(AMUL.recBuf[sn]->segLst, seg);
            } 

            /* Check if the last segment is missing */
            KW_LLIST_LAST_SEG(AMUL.recBuf[sn]->segLst, seg);
            if ((seg != NULLP) && (seg->amHdr.lsf != 1 && maxCPduLen > 0))
            {
               tSn = sn;
               /* set prev E1 */
               staPdu[e1Idx] = staPdu[e1Idx] | KW_POWER(2, (e1eb+1));

               /* set E2 */
               tSn = sn << 2;
               tSn |= 1;  

               /* Add NACK_SN, E1 and E2 to staPdu */
               KW_FILL_CNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, idx, 
                                  emtBits);  
               kwFormCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
               KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, emtBits);

               soStart = seqSo;
               soEnd = AMUL.recBuf[sn]->pduSz;
               soEnd = KW_ALL_BYTES_MISSING;
               KW_FILL_CNTRL_INFO(cntrlInfo, soStart, KW_SO_LEN, idx, emtBits);
               kwFormCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
               KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, emtBits);

               KW_FILL_CNTRL_INFO(cntrlInfo, soEnd, KW_SO_LEN, idx, emtBits);
               kwFormCntrlBits(gCb,&cntrlInfo, staPdu, &maxCPduLen);
               KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, emtBits);

               KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                     (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing (last) byte "
                      "segment's SN, soStart and soEnd = %d, %d, %d \n",
                      sn, soStart, soEnd));
            }

            if (seg != NULLP && maxCPduLen <= 0)
            {
               partSeg = TRUE;
               idx = tIdx;
               if (teb)
               {
                  idx = idx >> teb;
                  idx = idx << teb;
               }
               cntrlInfo.idx = idx;
            }
         }
      }
      sn = (sn + 1) % 1024;
      MODAMR(sn, mSn, AMUL.vrR);
   }

   /* Update ack_sn with the last sn for which feedback is not assembled */
   if (maxCPduLen>=0 && mSn == vrMs)
   {
      ack_sn = AMUL.vrMs;
   }
   else if (partSeg)
   {
      ack_sn = sn - 1;
   }
   else
   {
      ack_sn = sn;
   }

   idx = cntrlInfo.idx;
   emtBits = cntrlInfo.emtBits;

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
         (gCb->init.prntBuf, "kwAssembleCntrlInfo: ACK PDU's SN = %d\n", ack_sn));

   staPdu[0] = staPdu[0] | (ack_sn << 2);
   if (sn == AMUL.vrR)
   {
      idx = 0;
   }
 
   /* Add staPdu to mBuf */  
   for (i = 0, j = 0; i <= idx; i++)
   {
      KW_COPY_STAPDU(i, j);
   }

   SGetMsg (sapCb->pst.region, 
            sapCb->pst.pool, &mBuf);

   cntrlPduSz = (emtBits >= 8) ? j-1 : j;
   SAddPstMsgMult (cntrlPdu, cntrlPduSz, mBuf); 

   /* Start staProhTmr */
   kwStartTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_STA_PROH_TMR);
   AMUL.staTrg = FALSE;

   dlStaPdu->mBuf = mBuf;
   dlStaPdu->pduSz = cntrlPduSz;


   ret = KwUlUdxStaPduReq(&sapCb->pst, sapCb->spId, &rbCb->rlcId, dlStaPdu);
   if (ret != ROK)
   {
      KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
         (gCb->init.prntBuf, "kwAmmProcessPdus: Failed to Send Sta Pdu\n"));
 
      KW_FREE_BUF(mBuf);
      KW_FREE(gCb, dlStaPdu, sizeof(KwUdxStaPdu));
   }

   /*Pradeep - resetting the cntrlBo*/
   rbCb->m.amUl.cntrlBo = 0;
   printf("\n########Pradeep: resetting the cntrlBo to 0\n");
   
   RETVALUE(ROK);
}
#else
#ifdef ANSI
PRIVATE S16 kwAssembleCntrlInfo 
(
KwCb                      *gCb,
KwUlRbCb                  *rbCb,
KwDatReq                *kwDatReq
)
#else
PRIVATE S16 kwAssembleCntrlInfo(gCb, rbCb, kwDatReq)
KwCb                      *gCb;
KwUlRbCb                  *rbCb;
KwDatReq                *kwDatReq;
#endif
{

   KwCntrlInfo cntrlInfo;
   KwSn       sn;                      /* sequence number */
   KwSn       mSn;                     /* Mod val of sequence number */
   KwSn       vrMs;                    /* Mod val of vrMs */
   KwSn       ack_sn;                  /* Ack sequence number */
   Buffer     *mBuf = NULLP;           /* control pdu buffer */
   MsgLen     cntrlPduSz = 0;          /* control pdu size */
   KwSeg      *seg    = NULLP;         /* pdu segment */ 
   Bool       partSeg  = FALSE;         /* Flag to indicate partial segment
                                           construction in cntrl PDU */
   U16        staPdu[(KW_MAX_CNTRL_FIELDS + 1)/2];     /* status pdu array */
   U8         cntrlPdu[KW_MAX_CNTRL_FIELDS];   /* control pdu to be added to mBuf */
   U16        idx     = 0;             /* Index for staPdu */
   U8         emtBits = 0;             /* empty bits */
   U16        e1      = 0;             /* E1 */
   U16        e1Idx   = 0;             /* E1 Index */
   U16        e2Idx   = 0;             /* E2 Index */
   U8         e1eb    = 0;             /* empty bits after E1 */
   U16        soStart = 0;             /* segment offset start */
   U16        soEnd   = 0;             /* segment offset end */
   U16        seqSo   = 0;             /* segmment offset */
   U16        i       = 0;             /* Index for staPdu */
   U16        j       = 0;             /* Index for controlPdu */
   KwSn       tSn     = 0;

   TRC2(kwAssembleCntrlInfo)

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAssembleCntrlInfo(rbCb, kwDatReq) \n"));

   KW_MEM_ZERO(&cntrlInfo, sizeof(KwCntrlInfo)); 

   /* Eliminate fixed hdr size (14bits including ACK_SN) */
   kwDatReq->pduSz -= KW_CNTRL_PDU_FIXED_HDRSZ;
  
   /* Eliminate MAC header */
   kwDatReq->pduSz -= KW_MAC_HDR_SZ3;

   /* Add ACK_SN */
   ack_sn = 0;
   staPdu[idx] = ack_sn;

   /* Empty bits left after ACK_SN -  2 bits */
   emtBits = 2;

   /* Add E1 to ACK_SN */
   KW_FILL_CNTRL_INFO(cntrlInfo, e1, KW_E1_LEN, idx, emtBits);
   kwFormCntrlBits(gCb,&cntrlInfo, staPdu, kwDatReq);
   idx = cntrlInfo.idx;
   emtBits = cntrlInfo.emtBits;

   e1Idx = 0;
   e2Idx = 0;
   e1eb = 0;

   sn = AMUL.vrR;
   MODAMR(sn, mSn, AMUL.vrR);
   MODAMR(AMUL.vrMs, vrMs, AMUL.vrR);

   while (mSn < vrMs)
   {
      /* For missing PDUs */
      if (AMUL.recBuf[sn] == NULLP)
      {
         tSn = sn; 

         KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
               (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing PDU's SN = %d\n", sn));

         /* set prev E1 */
         staPdu[e1Idx] = staPdu[e1Idx] | KW_POWER(2, (e1eb+1));
         
         /* Add NACK_SN, E1 and E2 to staPdu */

         /* For NACK_E1E2, lsh by 2 to append e1, e2 value */
         tSn = sn << 2;
         KW_FILL_CNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, idx, emtBits);  
         kwFormCntrlBits(gCb,&cntrlInfo, staPdu, kwDatReq);
         KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, emtBits);
      }   
      else
      {
         if ( (AMUL.recBuf[sn]->pdu == NULLP) && 
              (AMUL.recBuf[sn]->segLst.count > 0) )
         {
            U16 tIdx = idx; 
            U8  teb = emtBits;

            /* Scan through the byte segments of PDU and add this sn 
               with soStart and soEnd info to staPdu */

            seqSo  = 0;
            KW_LLIST_FIRST_SEG(AMUL.recBuf[sn]->segLst, seg); 
            while (seg != NULLP && kwDatReq->pduSz > 0 )
            {
               /* For missing byte segments */
               if (seg->amHdr.so != seqSo)
               {
                  tSn = sn;
                  /* set prev E1 */
                  staPdu[e1Idx] = staPdu[e1Idx] | KW_POWER(2, (e1eb+1));

                  /* set E2 */
                  tSn = sn << 2;
                  tSn |= 1;  

                  /* Add NACK_SN, E1 and E2 to staPdu */
                  KW_FILL_CNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, idx, 
                                     emtBits);  
                  kwFormCntrlBits(gCb,&cntrlInfo, staPdu, kwDatReq);
                  KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, 
                                   emtBits); 

                  /* Add soStart and soEnd */
                  soStart = seqSo;
                  soEnd = seg->amHdr.so - 1; 
                  KW_FILL_CNTRL_INFO(cntrlInfo, soStart, KW_SO_LEN, idx, 
                                     emtBits);
                  kwFormCntrlBits(gCb,&cntrlInfo, staPdu, kwDatReq);
                  KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, 
                                   emtBits); 

                  KW_FILL_CNTRL_INFO(cntrlInfo, soEnd, KW_SO_LEN, idx, 
                                     emtBits);
                  kwFormCntrlBits(gCb,&cntrlInfo, staPdu, kwDatReq);
                  KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, 
                                   emtBits);

                  KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                        (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing byte segment's"
                         " SN, soStart and soEnd = %d, %d, %d \n", sn, soStart,
                         soEnd));
               }
               seqSo = seg->soEnd + 1;
               KW_LLIST_NEXT_SEG(AMUL.recBuf[sn]->segLst, seg);
            } 

            /* Check if the last segment is missing */
            KW_LLIST_LAST_SEG(AMUL.recBuf[sn]->segLst, seg);
            if ((seg != NULLP) && (seg->amHdr.lsf != 1 && kwDatReq->pduSz > 0))
            {
               tSn = sn;
               /* set prev E1 */
               staPdu[e1Idx] = staPdu[e1Idx] | KW_POWER(2, (e1eb+1));

               /* set E2 */
               tSn = sn << 2;
               tSn |= 1;  

               /* Add NACK_SN, E1 and E2 to staPdu */
               KW_FILL_CNTRL_INFO(cntrlInfo, tSn, KW_NACK_E1E2_LEN, idx, 
                                  emtBits);  
               kwFormCntrlBits(gCb,&cntrlInfo, staPdu, kwDatReq);
               KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, emtBits);

               soStart = seqSo;
               soEnd = AMUL.recBuf[sn]->pduSz;
               soEnd = KW_ALL_BYTES_MISSING;
               KW_FILL_CNTRL_INFO(cntrlInfo, soStart, KW_SO_LEN, idx, emtBits);
               kwFormCntrlBits(gCb,&cntrlInfo, staPdu, kwDatReq);
               KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, emtBits);

               KW_FILL_CNTRL_INFO(cntrlInfo, soEnd, KW_SO_LEN, idx, emtBits);
               kwFormCntrlBits(gCb,&cntrlInfo, staPdu, kwDatReq);
               KW_FILL_PREV_IDX(cntrlInfo, e1Idx, e2Idx, e1eb, idx, emtBits);

               KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
                     (gCb->init.prntBuf, "kwAssembleCntrlInfo: Missing (last) byte "
                      "segment's SN, soStart and soEnd = %d, %d, %d \n",
                      sn, soStart, soEnd));
            }

            if (seg != NULLP && kwDatReq->pduSz <= 0)
            {
               partSeg = TRUE;
               idx = tIdx;
               if (teb)
               {
                  idx = idx >> teb;
                  idx = idx << teb;
               }
               cntrlInfo.idx = idx;
            }
         }
      }
      sn = (sn + 1) % 1024;
      MODAMR(sn, mSn, AMUL.vrR);
   }

   /* Update ack_sn with the last sn for which feedback is not assembled */
   if (kwDatReq->pduSz >=0 && mSn == vrMs)
   {
      ack_sn = AMUL.vrMs;
   }
   else if (partSeg)
   {
      ack_sn = sn - 1;
   }
   else
   {
      ack_sn = sn;
   }

   idx = cntrlInfo.idx;
   emtBits = cntrlInfo.emtBits;

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
         (gCb->init.prntBuf, "kwAssembleCntrlInfo: ACK PDU's SN = %d\n", ack_sn));

   staPdu[0] = staPdu[0] | (ack_sn << 2);
   if (sn == AMUL.vrR)
   {
      idx = 0;
   }
 
   /* Add staPdu to mBuf */  
   for (i = 0, j = 0; i <= idx; i++)
   {
      KW_COPY_STAPDU(i, j);
   }

   SGetMsg (kwCb.rguSap.pst.region, 
            kwCb.rguSap.pst.pool, &mBuf);

   cntrlPduSz = (emtBits >= 8) ? j-1 : j;
   SAddPstMsgMult (cntrlPdu, cntrlPduSz, mBuf); 

   /* Start staProhTmr */
   kwStartTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_STA_PROH_TMR);
   AMUL.staTrg = FALSE;

   /* Update number of pdus in pduInfo */
   kwDatReq->pduInfo.mBuf[kwDatReq->pduInfo.numPdu] = mBuf; 
   kwDatReq->pduInfo.numPdu++;

   /* kw005.201 ccpu00117318, updating the statistics */
   kwCb.ckwSap.sts.statMsgs += kwDatReq->pduInfo.numPdu;
   RETVALUE(ROK);
}
#endif

#ifdef KW_UDX
#ifdef ANSI
PRIVATE Void kwAmmProcUlPdus
(
KwCb                   *gCb,
KwUlRbCb               *rbCb
)
#else
PRIVATE Void kwAmmProcUlPdus(gCb, rbCb)
KwCb                   *gCb;
KwUlRbCb               *rbCb;
#endif
{
#if 0
   CmLListCp         *lst = &AMUL.pduLst;
   KwAmRecBuf        *pdu;
   S32               idx = KW_AM_MAX_UL_PDUS;

   TRC2(kwAmmProcUlPdus)

   while(lst->first)
   {
      pdu = (KwAmRecBuf *)(lst->first->node);
      cmLListDelFrm(lst, lst->first);
      kwReassembleSdus(rbCb, &pdu);
      KW_FREE(gCb,pdu, sizeof(KwAmRecBuf));
      if (--idx <= 0)
      {
         RETVOID;
      }
   }
#endif
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}
#endif

/**
 *
 * @brief Handler to process the PDUs received from MAC and send it to PDCP 
 *
 * @b Description
 *        This function is invoked by UTL with the PDU(s) received from MAC. 
 *        It reorders the received data PDUs and trigger status report as 
 *        needed. Reassembles the SDUs in sequence and send it to PDCP. 
 *        It also processes the control PDU and updates PDCP with the 
 *        successful delivery of an SDU if it receives ACK for all the PDUs 
 *        mapped with that SDU.
 *
 * @param[in]  rbCb     RB control block 
 * @param[out] pduInfo  PDU Info received from MAC
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
#ifdef ANSI
PUBLIC S16 kwAmmProcessPdus
(
KwCb                  *gCb,
KwUlRbCb                *rbCb,
KwPduInfo             *pduInfo,
KwL2MeasUlThrpTimInfo *ulTimeInfo
)
#else
PUBLIC S16 kwAmmProcessPdus(gCb, rbCb, pduInfo, ulTimeInfo)
KwCb                  *gCb;
KwUlRbCb                *rbCb;
KwPduInfo             *pduInfo;
KwL2MeasUlThrpTimInfo *ulTimeInfo;
#endif
#else
#ifdef ANSI
PUBLIC S16 kwAmmProcessPdus
(
KwCb                  *gCb,
KwUlRbCb              *rbCb,
KwPduInfo             *pduInfo
)
#else
PUBLIC S16 kwAmmProcessPdus(gCb, rbCb, pduInfo)
KwCb                  *gCb;
KwUlRbCb              *rbCb;
KwPduInfo             *pduInfo;
#endif
#endif
#else
#ifdef ANSI
PUBLIC S16 kwAmmProcessPdus
(
KwCb                  *gCb,
KwUlRbCb              *rbCb,
KwPduInfo             *pduInfo
)
#else
PUBLIC S16 kwAmmProcessPdus(gCb, rbCb, pduInfo)
KwCb                  *gCb;
KwUlRbCb              *rbCb;
KwPduInfo             *pduInfo;
#endif
#endif
{
   
   Buffer              *pdu   = NULLP;
   KwAmUl              *amUl  = &AMUL;
   /* kw001.201 : Changing the usage to a local var instead of pointer */
   KwAmHdr             amHdr;
   U8                  numPdu = 0;    
   KwSn                sn    = 0;
   KwSn                tSn   = 0;
   KwSn                mSn   = 0;
   U8                  fByte = 0;
   Bool                discFlg;
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
   MsgLen              rlcSduSz = 0;  /*Holds length of Rlc Sdu*/
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */

   TRC2(kwAmmProcessPdus)

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwAmmProcessPdus(rbCb, pduInfo) \n"));

   amUl = &AMUL;

   while ((numPdu < pduInfo->numPdu) &&
          (numPdu < RGU_MAX_PDU))
   {
      S16     ret   = ROK;

      discFlg = FALSE;
      pdu = pduInfo->mBuf[numPdu++];
      
      /* Extract AM PDU/SEG header Info */
      KW_MEM_ZERO(&amHdr, sizeof(KwAmHdr));
      /* Avoided the allocation of amHdr and sending
         a single pointer */
      ret = kwExtractHdr(gCb,rbCb, pdu, &amHdr, &fByte);

      if ( ret != ROK )
      {
         KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                (gCb->init.prntBuf, "kwAmmProcessPdus: Failed to extract hdr \n"));
         /* kw005.201 ccpu00117318, updating the statistics */
         gCb->genSts.errorPdusRecv++;
         continue;
      }
      /* Check if its a control PDU */
      if (amHdr.dc == 0)
      {
         kwHndlStaRsp(gCb, rbCb, pdu, &fByte);
         KW_FREE_BUF(pdu);
         continue;
      }   
       
      /* Reordering data PDU */ 
      sn = amHdr.sn;
      if ( (ret = kwPlcPduInRecBuf(gCb,pdu, rbCb, &amHdr) == TRUE) )
      {
         Bool    tmrRunning = FALSE;
         KwSn    tVrMr      = 0;
         KwSn    mVrH       = 0;
	
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
         KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
         (gCb->init.prntBuf, "kwAmmProcessPdus: Log for ul ip throughput:\n \
         RB_MeasOn:%d SegInd:%d thrpTimeUl:%lu\n", rbCb->rbL2Cb.measOn, \
         ulTimeInfo->firstLastSegInd, ulTimeInfo->thrpTimeUl));

         /*Check if UL IP throughput measurement is ON for this RB or not*/
         if(0 != (rbCb->rbL2Cb.measOn & LKW_L2MEAS_UL_IP) )
         {
            /*If the indication is first and interim, then calculate the RLC SDU *
             *size and add it to the ulDataVol. If it is last, then its data size*
             *should not be added.                                               */
            if( (RGU_L2M_ULTHRP_FIRST == ulTimeInfo->firstLastSegInd) || 
                (RGU_L2M_ULTHRP_INTERIM == ulTimeInfo->firstLastSegInd))
            {
               SFndLenMsg(pdu, &rlcSduSz);
               rbCb->l2MeasIpThruput.ulDataVol += rlcSduSz;
            }
            /*If the indication is last*/
            if(RGU_L2M_ULTHRP_LAST == ulTimeInfo->firstLastSegInd)
            {
               /*If the indication is last and time difference is 0, then it means*
               *that ul burst for this LCH is split across 2 TTIs and so UL IP   *
               *measurement can not be taken. So reset the data volume.          */
               if(0 == ulTimeInfo->thrpTimeUl)
               {
                  rbCb->l2MeasIpThruput.ulDataVol = 0;
               }
               /*Else save the total data volume and time difference in KwL2Cntr*/
               else
               {
                  rbCb->rbL2Cb.l2Sts[KW_L2MEAS_UL_IP]->ulIpThruput.volSummation 
                     += rbCb->l2MeasIpThruput.ulDataVol;
                  rbCb->rbL2Cb.l2Sts[KW_L2MEAS_UL_IP]->ulIpThruput.timeSummation 
                     += ulTimeInfo->thrpTimeUl;
                  /*Reset ulDataVol in rbCb since it has been saved in l2Sts*/
                  rbCb->l2MeasIpThruput.ulDataVol = 0;
               }
            }
         }
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */

         /* kw005.201 R9 Upgrade 3gpp spec 36.322 ver9.3.0 CR0090 *
          * Removed unused local variable vrR.                    */
 
         /* kw005.201 R9 Upgrade 3gpp spec 36.322 ver9.3.0 CR0090 *
          * Added VR(H) updation at the beginning.		  */

         /* Update vrH */
         MODAMR(sn, mSn, amUl->vrR);
         MODAMR(amUl->vrH, mVrH, amUl->vrR);
         if (mSn >= mVrH)
         {
            amUl->vrH = (sn + 1) % 1024;

            KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                  (gCb->init.prntBuf, "kwAmmProcessPdus: Updated vrH = %d \n", \
                   amUl->vrH));
         }

         MODAMR(amUl->vrMr, tVrMr, amUl->vrR);

         /* Update vrMs */
         if (sn == amUl->vrMs)
         {
            /* Check if all byte segments are received */
            if (amUl->recBuf[sn]->allRcvd)
            {
               tSn = (sn + 1) % 1024;

               /* Scan through till the upper edge of the window */
               MODAMR(tSn, mSn, amUl->vrR);
               while (mSn <= tVrMr) 
               {
                 if ((amUl->recBuf[tSn] == NULLP) || 
                     (!amUl->recBuf[tSn]->allRcvd))
                 {
                    KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                           (gCb->init.prntBuf, "kwAmmProcessPdus: Updated vrMs = %d \n", \
                            tSn));

                    amUl->vrMs = tSn;
                    break;
                 }
                 tSn = (tSn + 1) % 1024; mSn++;
               }
            }
         }

         /* kw005.201 R9 Upgrade 3gpp spec 36.322 ver9.3.0 CR0090 *
          * Removed the Retaining of VR(R) for VR(H) updation.	  */

         /* Update vrR */
         if (sn == amUl->vrR)
         {
            /* Check if all byte segments are received */
            if (amUl->recBuf[sn]->allRcvd)
            {
               tSn = sn;
               MODAMR(tSn, mSn, amUl->vrR);
               /* Scan through till the upper edge of the window */
               while (mSn <= tVrMr)
               {
                  if ((amUl->recBuf[tSn] != NULLP) && 
                      (amUl->recBuf[tSn]->allRcvd))
                  {
#ifndef KW_BG_UL_PROC 
                     kwReassembleSdus(gCb,rbCb, &amUl->recBuf[tSn]);
                     KW_FREE(gCb,AMUL.recBuf[tSn], sizeof(KwAmRecBuf));
#else
                     cmLListAdd2Tail(&amUl->pduLst, &amUl->recBuf[tSn]->pduLnk);
                     amUl->recBuf[tSn]->pduLnk.node = (PTR)amUl->recBuf[tSn];
#endif
                     amUl->recBuf[tSn] = NULLP;
                  }
                  else
                  {
                     amUl->vrR = tSn;
                     amUl->vrMr = (amUl->vrR + KW_AM_WIN_SZ) % 1024; 
                     break;
                  }
                  tSn = (tSn + 1) % 1024; mSn++;
               }
            }
         }

         /* kw005.201 R9 Upgrade 3gpp spec 36.322 ver9.3.0 CR0090 *
          * Removed VR(H) update from here and moved it at the    *
          * beginning.						  */

         /* Check if reOrdTmr is running and update vrX accordingly */
         tmrRunning = kwChkTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_REORD_TMR);
         if (tmrRunning)
         {
            Bool    snInWin = FALSE;
            KW_AM_CHK_SN_IN_WINDOW(amUl->vrX, amUl, snInWin);
	    
            /* kw005.201 R9 Upgrade 3gpp spec 36.322 ver9.3.0 CR0083 *
             * The 3rd condition in "if" statement is added.	     */
            if ( (amUl->vrX == amUl->vrR) || ( (!snInWin) && 
                                             (amUl->vrX != amUl->vrMr) ) )
            {
               kwStopTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_REORD_TMR);
               tmrRunning = FALSE;
            }
         }
         if (!tmrRunning)
         {
            /* kw003.201 - If VR(H) != VR(R), it will always be greater */
            if (amUl->vrR != amUl->vrH)
            {
               kwStartTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_REORD_TMR);
               amUl->vrX = amUl->vrH;

               KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                     (gCb->init.prntBuf, "kwAmmProcessPdus: Updated vrX = %d \n", \
                      amUl->vrX));
            }
         }
         
/*Pradeep - start*/
printf("\n******************************************************************\n");
printf("UEID[%d] LchId[%d] RbId[%d] SN[%d]\n",rbCb->rlcId.ueId,rbCb->lch.lChId,rbCb->rlcId.rbId,amHdr.sn);
printf("VR(R)[%d] VR(H)[%d] VR(X)[%d] VR(MS)[%d] VR(MR)[%d]",amUl->vrR,amUl->vrH,amUl->vrX,amUl->vrMs,amUl->vrMr);
printf("\n******************************************************************\n");
/*Pradeep - end*/
      if(amUl->vrMr == 767)
      {
          printf("\n amUl->vrMr = %d break point reached \n", amUl->vrMr);
      }
      
      }
      else
      {
         discFlg = TRUE;
      }

      if (amHdr.p)
      {
         kwTriggerStatus (gCb,rbCb, sn, discFlg);
      } 
   }
   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.pdusRecv += pduInfo->numPdu;
#ifdef KW_BG_UL_PROC
   kwAmmProcUlPdus(rbCb);
#endif
   if (amUl->cntrlBo)
   {
#if 0
      AMDL.cntrlBo = amUl->cntrlBo;
#endif
      printf("#### Sending status BO for sq num: %d ",sn);
      kwAssembleCntrlInfo(gCb,rbCb);
#if 0
      KW_AM_SND_DSTA_RSP();
#endif
   }

   RETVALUE(ROK);
} /* kwAmmProcessPdus */

/**
 *
 * @brief Private handler to extract header Information of the PDU
 *
 * @b Description 
 *        This function extracts the header elements of the PDU and store them 
 *        in db for future reference.
 *
 *        fByte - is the first byte removed from the PDU as part of calling
 *                functions
 *
 * @param[in]  pdu      Received PDU
 * @param[out] amUl     AM UL Info 
 *
 *  @return S16 
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwExtractHdr 
(
KwCb       *gCb,
KwUlRbCb    *rbCb,
Buffer    *pdu,
KwAmHdr   *amHdr,
U8        *fByte
)
#else
PRIVATE S16 kwExtractHdr(gCb,rbCb, pdu, amHdr, fByte)
KwCb       *gCb;
KwUlRbCb    *rbCb;
Buffer    *pdu;
KwAmHdr   *amHdr;
U8        *fByte;
#endif
{
   Buffer *tPdu = NULLP;
   U8     e = 0;
   U8     snByte = 0;
   U16    li = 0;
   U16    liCnt = 0;
   U16    sn = 0;
   MsgLen pduSz = 0;
   MsgLen totalSz = 0;
   KwExtHdr hdrInfo;

   TRC2(kwExtractHdr)
   /* kw005.201 removed warning */
   UNUSED(rbCb);

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwExtractHdr(rbCb, pdu, amHdr, fByte) \n"));

   KW_MEM_ZERO(&hdrInfo, sizeof(KwExtHdr)); 

   tPdu = pdu;

   /* Extract fixed part of the header */ 
   SFndLenMsg(pdu,&pduSz);
   SRemPreMsg(fByte, pdu);
   amHdr->dc = (*fByte & KW_DC_POS)? KW_DATA_PDU : KW_CNTRL_PDU;
   if (amHdr->dc == KW_CNTRL_PDU)
   {
      RETVALUE(ROK);
   }
   /* kw002.201 : Changed the extraction of hdr elements to avoid */
   /*             function calls                                  */
   amHdr->rf = (*fByte & KW_RF_POS) ? TRUE: FALSE;
   amHdr->p  = (*fByte & KW_POLL_POS) ? TRUE:FALSE;
   amHdr->fi = (*fByte & KW_FI_POS) >> 3;
   e = amHdr->e  = (*fByte & KW_E_POS)? TRUE:FALSE;

   SRemPreMsg(&snByte, pdu);
   sn = (U16)(((*fByte & KW_SN_POS) << KW_BYTE_LEN ) | snByte);
   amHdr->sn = sn;
   if (amHdr->rf == 1)
   {
      /* Extract extn part of the header */
      hdrInfo.len = KW_LSF_LEN;
      kwExtractElmnt(gCb,pdu, &hdrInfo);
      amHdr->lsf = (U8)hdrInfo.val;

      hdrInfo.len = KW_SO_LEN;
      kwExtractElmnt(gCb,pdu, &hdrInfo); 
      amHdr->so = hdrInfo.val;
      pduSz -= 2;
   }

   /* Extract LIs */ 
   while (e && pdu)
   {
      hdrInfo.len = KW_E_LEN;
      kwExtractElmnt(gCb,pdu, &hdrInfo); 
      e = amHdr->e = (U8)hdrInfo.val;

      if ( pdu )
      {
         hdrInfo.len = KW_LI_LEN;
         kwExtractElmnt(gCb,pdu, &hdrInfo);
         li = hdrInfo.val;

         if (li == 0)
         {
            KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf, "kwExtractHdr: Received LI with 0 \n"));
            KW_FREE_BUF(pdu);
            RETVALUE(RFAILED);
         }

         amHdr->li[liCnt++] = li;
         totalSz += li;
      }
      else
      {
         RETVALUE(RFAILED);
      }
   }

   if (liCnt)
      amHdr->numLi = liCnt;

   if (liCnt % 2)
   {
      /* kw001.201: Changed the liCnt to avoid float variables */
      pduSz -= ( liCnt + ((liCnt -1)/2) + 1 +2);
   }
   else
   {
      pduSz -= ( liCnt + (liCnt/2)+ 2);
   }

   if ( totalSz >= pduSz )
   {
      KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
             (gCb->init.prntBuf, "kwExtractHdr: Corrupted PDU received from the lower\
              layer \n"));
      KW_FREE_BUF(pdu);
      RETVALUE(RFAILED);
   }
printf("\n#########Prdeep: pollBit [%d] \n",amHdr->p);
   RETVALUE(ROK);
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
KwCb                  *gCb;
KwUlRbCb              *rbCb
)
#else
PRIVATE Void kwAmmRlsPdusSet(rbCb)
KwCb                  *gCb;
KwUlRbCb              *rbCb;
#endif
{
   S32              idx    = KW_AM_MAX_PDUS_RLS;
   KwDlTx             *pdu;
   CmLListCp        *lst;

   TRC2(kwAmmRlsPdusSet)

   /* Patch kw004.201 - Release is made at the RB level */
   lst  = &AMDL.toBeRlsLst;
   while((lst->first) && (idx > 0))
   {
      pdu = (KwTx *)(lst->first->node);
      cmLListDelFrm(lst, lst->first);
      kwAmChkSduMap(rbCb, pdu->amHdr.sn, pdu->sduMap, pdu->numSdu);
      KW_FREE_BUF(pdu->pdu);
      KW_FREE(gCb,pdu, sizeof(KwTx));
      idx--;
   }
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}
#endif /* KW_BG_DL_PROC */

#if 1
/**
 *
 * @brief Private handler to process the status PDU
 *
 * @b Description
 *        Private handler invokded by kwAmmProcessPdus to process the 
 *        control PDU (status report) received from its peer RLC entity.
 *
 *        - Decode the values from the received control pdu and flush pdu 
 *          from txBuf if it receives ack for the pdu, else move it to the 
 *          retxBuf.
 *        - Flush the pdu from retxBuf if ack is received for all byte 
 *          segments of the pdu else it remains in retx buffer until it 
 *          receives ack / it reaches maxRetx threashold value.
 *        - Before cleaning up the PDUs from txBuf/retxBuf, DatCfm will be 
 *          sent to PDCP for each SDU using the SDU to pdu (SN) mapping 
 *          available in the sduQ 
 *
 * @param[in]  rbCb     RB control block 
 * @param[out] cntrlPdu Control PDU received from MAC
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwHndlStaRsp
(
KwCb               *gCb,
KwUlRbCb           *rbCb,
Buffer             *cntrlPdu,
U8                 *fByte
)
#else
PRIVATE S16 kwHndlStaRsp(gCb, rbCb, cntrlPdu, fByte)
KwCb               *gCb;
KwUlRbCb           *rbCb;
Buffer             *cntrlPdu;
U8                 *fByte;
#endif
{
   U8              e1      = 0;
   KwSn            ackSn   = 0;
#if 0
   KwSn            mSn     = 0;
   KwSn            mVtA    = 0;
   KwSn            mAckSn  = 0;
   KwSn            mTxSn   = 0;
   S32             retxBo  = 0;
   CmLList         *retxNode;
#endif
   KwExtHdr        hdrInfo;
   KwUdxStaPdu     staPdu;
   KwUdxStaPdu     *pStaPdu;
#if 0
   S16             ret;
#endif
   Pst             *pst   = NULLP;
   KwUdxUlSapCb    *sapCb;

   TRC2(kwHndlStaRsp)

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwHndlStaRsp(rbCb, cntrlPdu, fByte) \n"));

   KW_ALLOC(gCb, pStaPdu, sizeof(KwUdxStaPdu));
   KW_MEM_ZERO(&hdrInfo, sizeof(KwExtHdr));
#if 0
   KW_MEM_ZERO(&staPdu, sizeof(KwUdxStaPdu));
#endif

   /* Extract the Control PDU */ 
   hdrInfo.hdr  = (*fByte << 1);
   hdrInfo.pLen = 4;

   /* D/C has been shifted in the calling function */
   if (hdrInfo.hdr & 0xE0)
   {
      KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
            (gCb->init.prntBuf, "kwHndlStaRsp: Reserved value for CPT, \
             discarded cntrlPDU) \n"));
      RETVALUE(ROK);
   }

   /* For CPT */
   hdrInfo.hdr = hdrInfo.hdr << KW_CPT_LEN; 

   /* ACK Sn */
   hdrInfo.len = KW_SN_LEN;
   kwExtractElmnt(gCb, cntrlPdu, &hdrInfo);
   pStaPdu->ackSn = hdrInfo.val;

   /* Check if NACK Exists */
   hdrInfo.len = KW_E1_LEN;
   kwExtractElmnt(gCb, cntrlPdu, &hdrInfo); 
   e1 = (U8)hdrInfo.val; 
   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwHndlStaRsp: ACK SN = %d \n", ackSn));

   /* If NACK exists in control PDU */
   if (e1)
   {
      U8     e2      = 0;

      /* For ACKs and NACKs */
      while (e1 && (pStaPdu->nackCnt < KW_UDX_MAX_NACK_CNT))
      {
         hdrInfo.len = KW_SN_LEN;
         kwExtractElmnt(gCb, cntrlPdu, &hdrInfo);
         pStaPdu->nackInfo[pStaPdu->nackCnt].sn = hdrInfo.val;

         hdrInfo.len = KW_E1_LEN;
         kwExtractElmnt(gCb, cntrlPdu, &hdrInfo); 
         e1 = (U8)hdrInfo.val;

         hdrInfo.len = KW_E1_LEN;
         kwExtractElmnt(gCb, cntrlPdu, &hdrInfo);
         e2 = (U8) hdrInfo.val;

         /* Test for resegmentation */
         if (e2)
         {
            hdrInfo.len = KW_SO_LEN;
            kwExtractElmnt(gCb, cntrlPdu, &hdrInfo);
            pStaPdu->nackInfo[pStaPdu->nackCnt].soStart = hdrInfo.val;

            kwExtractElmnt(gCb, cntrlPdu, &hdrInfo);
            pStaPdu->nackInfo[pStaPdu->nackCnt].soEnd   = hdrInfo.val;

            KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                   (gCb->init.prntBuf, "kwHndlStaRsp: soStart and soEnd = %d %d \n", \
                    pStaPdu->nackInfo[pStaPdu->nackCnt].soStart, \
                    pStaPdu->nackInfo[pStaPdu->nackCnt].soEnd));
/*Pradeep - start, commented for fix*/         
         /*pStaPdu->nackCnt++;*/
/*Pradeep - end, commented for fix*/         
         }
/*Pradeep - start, fix*/         
         pStaPdu->nackCnt++;
/*Pradeep - end, fix*/         
      }  
   }

   sapCb = KW_GET_UDX_SAP(gCb);

   KwUlUdxStaUpdReq(&(sapCb->pst), sapCb->spId, &rbCb->rlcId, pStaPdu);

   RETVALUE(ROK);
   
}
#endif

/**
 *
 * @brief Private handler to release all stored segments
 *
 * @b Description
 *        Private handler invokded by kwPlcPduInRecBuf to release the 
 *        stored segements in case a complete PDU is received later.
 *
 * @param[in]  recBuf   Buffer that stores a received PDU or segments
 *
 *  @return  Void
 *
 */
#ifdef ANSI
PRIVATE Void kwAmmRlsAllSegs
(
KwCb               *gCb,
KwAmRecBuf        *recBuf
)
#else
PRIVATE Void kwAmmRlsAllSegs(recBuf)
KwCb               *gCb;
KwAmRecBuf        *recBuf;
#endif
{
   KwSeg          *seg;

   TRC2(kwAmmRlsAllSegs)

   KW_LLIST_FIRST_SEG(recBuf->segLst, seg);
   while (seg != NULLP)
   {
      KW_FREE_BUF(seg->seg);
      cmLListDelFrm(&(recBuf->segLst),&(seg->lstEnt));
      KW_FREE(gCb,seg, sizeof(KwSeg));
      KW_LLIST_FIRST_SEG(recBuf->segLst, seg);
   }
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief Private handler to store the received segment
 *
 * @b Description
 *        Private handler invokded by kwPlcPduInRecBuf to add a received
 *        segment in receiver buffer for a RBCB.
 *        - It is responsible for detecting duplicate segments
 *        - Adding it at appropriate position in the received buffer
 *        - Calling ExpByteSeg to set expSo field in the receiver buffer
 *
 * @param[in]  rbCb     Radio Bearer Contro Block
 * @param[in]  amHdr    AM Header received
 * @param[in]  pdu      Buffer received other than the headers
 * @param[in]  pduSz    size of the PDU buffer received
 *
 *  @return  Bool
 *   -#TRUE  Successful insertion into the receiver buffer
 *   -#FALSE Possibly a duplicate segment
 */
#ifdef ANSI
PRIVATE Bool kwAmmAddRcvdSeg
(
KwCb               *gCb,
KwUlRbCb            *rbCb,
KwAmHdr           *amHdr,
Buffer            *pdu,
U16               pduSz
)
#else
PRIVATE Bool kwAmmAddRcvdSeg(rbCb, amHdr, pdu, pduSz)
KwCb               *gCb;
KwUlRbCb            *rbCb;
KwAmHdr           *amHdr;
Buffer            *pdu;
U16               pduSz;
#endif
{
   KwAmRecBuf     *recBuf;
   KwSeg          *seg;
   KwSeg          *tseg;
   U16            soEnd = amHdr->so + pduSz - 1;

   TRC2(kwAmmAddRcvdSeg)
   if (AMUL.recBuf[amHdr->sn] == NULLP)
   {
      if (AMUL.recBuf[amHdr->sn] == NULLP)
      {
         KW_ALLOC(gCb,recBuf, sizeof(KwAmRecBuf));
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (recBuf == NULLP)
         {
            KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW009, (ErrVal)0,
                  "kwPlcPduInRecBuf: Allocation failed for recBuf \n");
            KW_FREE_BUF(pdu);
            RETVALUE(FALSE);
         }
#endif /* ERRCLASS & ERRCLS_RES */
         AMUL.recBuf[amHdr->sn] = recBuf;
      }
   }
   else
   {
      recBuf = AMUL.recBuf[amHdr->sn];
   }
   if (recBuf->allRcvd == TRUE)
   {
      KW_FREE_BUF(pdu);
      RETVALUE(FALSE);
   }
   
   /* kw003.201 - Move past the segments that are different than the */
   /*             one received.                                      */
   KW_LLIST_FIRST_SEG(recBuf->segLst, seg);
   while ((seg != NULLP) && (seg->amHdr.so < amHdr->so))
   {
      KW_LLIST_NEXT_SEG(recBuf->segLst, seg);
   }

   /* kw003.201 - All the segments that are duplicates of this can  */
   /*             be removed                                        */
   while ((seg) && (seg->amHdr.so >= amHdr->so) && (seg->soEnd <= soEnd))
   {
      if ((seg->amHdr.so == amHdr->so) && (seg->soEnd == soEnd))
      {
         /* This is an exact duplicate of the received seg          */
         KW_FREE_BUF(pdu);
         RETVALUE(FALSE);
      }
      else
      {
         /* This is a segment that is contained with in the received */
         /* segment. This could be removed as it is a smaller dup    */
         /* kw003.201 - This branch could be further enhanced        */
         /* kwAmmRemSeg(recBuf, seg);*/
         KW_FREE_BUF(pdu);
         RETVALUE(FALSE);
      }
      KW_LLIST_NEXT_SEG(recBuf->segLst, seg);
   }

   /* If we have come this far, we have to add this segment to the   */
   /* reception buffer as we either have eliminated duplicates or    */
   /* have found none.                                               */
   KW_ALLOC(gCb,tseg, sizeof(KwSeg));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (tseg == NULLP)
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW010, (ErrVal)0,
                  "kwPlcPduInRecBuf: Allocation failed for seg \n");
      KW_FREE_BUF(pdu);
      RETVALUE(FALSE);
   }
#endif /* ERRCLASS & ERRCLS_RES */

   tseg->seg = pdu;
   tseg->segSz = pduSz; 
   KW_MEM_CPY(&tseg->amHdr, amHdr, sizeof(KwAmHdr));
   recBuf->amHdr.rf = 1;
   recBuf->amHdr.sn = amHdr->sn;
   tseg->soEnd = soEnd;
   if (seg == NULLP)
   {
      cmLListAdd2Tail(&recBuf->segLst, &tseg->lstEnt);
   }
   else
   {
      recBuf->segLst.crnt = &seg->lstEnt;
      cmLListInsCrnt(&recBuf->segLst, &tseg->lstEnt);
   }
   tseg->lstEnt.node = (PTR)tseg;
   kwAmmUpdExpByteSeg(gCb,&AMUL,tseg);

   RETVALUE(TRUE);
}

/**
 *
 * @brief Private handler to place the PDU in the reception buffer 
 *
 * @b Description 
 *        This function checks if the received PDU's SN falls within the
 *        receiving window, after which it places the same in the reception 
 *        buffer if its not a duplicate.
 *
 * @param[in]  pdu      Received PDU
 * @param[out] amUl     AM UL Info 
 *
 *  @return Bool 
 *      -# TRUE 
 *      -# FALSE 
 *
 */
#ifdef ANSI
PRIVATE Bool kwPlcPduInRecBuf
(
KwCb               *gCb,
Buffer             *pdu,
KwUlRbCb             *rbCb,
KwAmHdr            *amHdr
)
#else
PRIVATE Bool kwPlcPduInRecBuf(gCb, pdu, rbCb, amHdr)
KwCb               *gCb;
Buffer             *pdu;
KwUlRbCb             *rbCb;
KwAmHdr            *amHdr;
#endif
{
   KwSn            sn      = 0;
   Bool            snInWin = 0;
   MsgLen          pduSz   = 0;
   KwAmUl          *amUl   = &(rbCb->m.amUl);

   TRC2(kwPlcPduInRecBuf)

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwPlcPduInRecBuf(pdu, rbCb, amHdr)\n"));

   sn = amHdr->sn;
   SFndLenMsg(pdu, &pduSz);
   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.bytesRecv += pduSz;

   /* Check if SN falls within reordering window */
   KW_AM_CHK_SN_IN_WINDOW(sn, amUl, snInWin);

   if (!snInWin)
   {
      KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
            (gCb->init.prntBuf, "kwPlcPduInRecBuf: SN  %d falls outside the window \n",
              sn));
      /* kw005.201 ccpu00117318, updating the statistics */
      gCb->genSts.unexpPdusRecv++;
      KW_FREE_BUF(pdu);
      RETVALUE(FALSE);
   }

   if (amHdr->rf == 0)
   {
      KwAmRecBuf      *recBuf;

      /* We received a complete PDU. Either we already have it, in which */
      /* case we just ignore the new PDU and discard it. Otherwise,      */
      /* store the received PDU in the reception buffer                  */
      if (amUl->recBuf[amHdr->sn] == NULLP)
      {
         KW_ALLOC(gCb,recBuf, sizeof(KwAmRecBuf));
#if (ERRCLASS & ERRCLS_ADD_RES)
         if (recBuf == NULLP)
         {
            KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW009, (ErrVal)0,
                  "kwPlcPduInRecBuf: Allocation failed for recBuf \n");
            KW_FREE_BUF(pdu);
            RETVALUE(FALSE);
         }
#endif /* ERRCLASS & ERRCLS_RES */
         amUl->recBuf[sn] = recBuf;
      }
      else if (amUl->recBuf[amHdr->sn]->allRcvd != TRUE)
      {
         kwAmmRlsAllSegs(gCb,amUl->recBuf[amHdr->sn]);
         recBuf = amUl->recBuf[sn];
      }
      else
      {
         /* kw005.201 ccpu00117318, updating the statistics */
         gCb->genSts.unexpPdusRecv++;
         KW_FREE_BUF(pdu);
         RETVALUE(FALSE);
      }
      recBuf->pdu = pdu;
      recBuf->pduSz = pduSz;
      recBuf->allRcvd = TRUE;
      KW_MEM_CPY(&recBuf->amHdr, amHdr, sizeof(KwAmHdr));
      RETVALUE(TRUE);
   }
   else
   {
      /* We received a segment. We need to add that to the existing */
      /* segments, if any.                                          */
      RETVALUE(kwAmmAddRcvdSeg(gCb,rbCb, amHdr, pdu, pduSz));
   }
} /* kwPlcPduInRecBuf */


/**
 *
 * @brief Private handler to trigger status report
 *
 * @b Description
 *        Private handler invokded by kwAmmProcessPdus to check if the 
 *        status report need to be sent, and update the status trigger 
 *        flag accordingly based on status prohibit timer.
 *   
 *        - Check if the received pdu's sn is less than vrMs, set the 
 *          staTrg flag.
 *        - If staProhTmr is not running, calculate cntrlBo, else it'll be
 *          updated at the expiry of staProhTmr.
 *        - Expiry of reOrdTmr also will set staTrg flag.
 *   
 * @param[in]  rbCb     RB control block 
 *
 *  @return  Void
 *
 */
#ifdef ANSI
PRIVATE Void kwTriggerStatus
(
KwCb      *gCb,
KwUlRbCb  *rbCb,                       /* AM UL Info */
KwSn      sn,                          /* Received PDU's SN */
Bool      discFlg                      /* Discard flag */
)
#else
PRIVATE Void kwTriggerStatus(gCb,rbCb, sn, discFlg)
KwCb      *gCb;
KwUlRbCb  *rbCb;                       /* AM UL Info */
KwSn      sn;                          /* Received PDU's SN */
Bool      discFlg;                     /* Discard Flag */
#endif
{
   Bool tmrRunning = FALSE;
   KwSn  tSn,tVrMr, tVrMs;
   KwAmUl *amUl = &(rbCb->m.amUl);

   TRC2(kwTriggerStatus)

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwTriggerStatus(rbCb, sn, discFlg)\n"));

   MODAMR(amUl->vrMr, tVrMr, amUl->vrR);
   MODAMR(amUl->vrMs, tVrMs, amUl->vrR);
   MODAMR(sn , tSn, amUl->vrR);
   
   if(sn == 14)
   {
       printf("sq num 14 reached\n");
   }

   /* kw005.201 Product CR ccpu00117114       *
    * The "=" in the 2nd condition is removed */
   if ((discFlg) || (tSn < tVrMs) || (tSn >= tVrMr))
   {
      KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
            (gCb->init.prntBuf, "kwTriggerStatus: Set Status Trigger \n"));

      amUl->staTrg = TRUE;

      /* Check if staProhTmr is running */
      tmrRunning = kwChkTmr(gCb,(PTR) rbCb, KW_EVT_AMUL_STA_PROH_TMR);

      if (!tmrRunning)
      {
         printf("\n##### Triggering status report for sq num: %d#####\n",sn);
         kwUpdCntrlBo(gCb,amUl);
      }
   }
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief Private handler to update control BO
 *
 * @b Description
 *  
 *         This function updates the control BO in the AM Uplink structure. 
 *   
 * @param[in]  amUl     AM UL Info 
 *
 * @return  Void
 * 
 */
#ifdef ANSI
PRIVATE Void kwUpdCntrlBo 
(
KwCb      *gCb,
KwAmUl    *amUl
)
#else
PRIVATE Void kwUpdCntrlBo(gCb, amUl)
KwCb      *gCb;
KwAmUl    *amUl;
#endif
{
   KwSn             sn  = 0;
   KwSn             mSn = 0;
   KwSn             mvrMs = 0;
   U16              seqSo = 0;
   S32              cntrlBo = 0;
   KwSeg            *seg = NULLP;

   TRC2(kwUpdCntrlBo)
   
   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwUpdCntrlBo(amUl)\n"));

   cntrlBo += KW_CNTRL_PDU_FIXED_HDRSZ;

   sn = amUl->vrR;

   MODAMR(sn, mSn, amUl->vrR);
   MODAMR(amUl->vrMs, mvrMs, amUl->vrR); 
   while (mSn < mvrMs)
   {
      if (amUl->recBuf[sn] == NULLP)
      {
         /* For NACK_SN, E1 and E2 */
         cntrlBo += 2;
      }
      else
      {
         if ( amUl->recBuf[sn]->amHdr.rf == 0 )
         {
            sn = (sn + 1) % 1024;
            MODAMR(sn, mSn, amUl->vrR);
            continue;
         }
 
         if ( (amUl->recBuf[sn]->amHdr.rf == 1) &&
              (amUl->recBuf[sn]->segLst.count > 0))
         {
            /* For NACK_SN, E1 and E2 */
            cntrlBo += 2;
         } 

         seqSo  = 0;
         
         KW_LLIST_FIRST_SEG(amUl->recBuf[sn]->segLst, seg);
         while (seg != NULLP)
         {
            /* For missing byte segments */
            if (seg->amHdr.so != seqSo)
            {
               /* For soStart and soEnd */
               cntrlBo+= 4;
            }
            seqSo = seg->soEnd + 1;
            KW_LLIST_NEXT_SEG(amUl->recBuf[sn]->segLst, seg);
         }

         /* Check if the last segment is missing */
         KW_LLIST_LAST_SEG(amUl->recBuf[sn]->segLst, seg);
         if ( (seg != NULLP) && (seg->amHdr.lsf != 1) )
         {
            cntrlBo += 2;
         }
      }
      sn = (sn + 1) % 1024;
      MODAMR(sn, mSn, amUl->vrR);
   }

   amUl->cntrlBo = cntrlBo;
#ifndef ALIGN_64BIT
   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwUpdCntrlBo: Updated cntrlBo = %ld\n", cntrlBo));
#else
   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwUpdCntrlBo: Updated cntrlBo = %d\n", cntrlBo));
#endif
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief Private handler to get a portion of SDU
 *
 * @b Description
 *        Private handler invokded by kwAmmProcPduOrSeg to fetch a portion
 *        of SDU that is addressed by the LI at position liCnt. It also
 *        increments liCnt.
 *
 * @param[in]  liCnt    refers to the SDU (portion) to be retrieved
 * @param[in]  amHdr    AM header carries the SDU size through LIs
 * @param[in]  pdu      PDU from which SDU is formed
 * @param[in]  sdub     Updated and returned to the caller
 *
 *  @return  S16
 *
 */
#ifdef ANSI
PRIVATE S16 kwAmmGetSdu
(
KwCb         *gCb,
U16          *liCnt,
KwAmHdr      *amHdr,
Buffer       **pdu,
Buffer       **sdu
)
#else
PRIVATE S16 kwAmmGetSdu
(
KwCb      	*gCb;
U16          *liCnt,
KwAmHdr      *amHdr,
Buffer       **pdu,
Buffer       **sdu
)
#endif
{
   Buffer    *remPdu;

   TRC2(kwAmmGetSdu)

   if ((*liCnt) < amHdr->numLi)
   {
      /* Segment the PDU based on length in LI table */
      SSegMsg(*pdu, amHdr->li[*liCnt], &remPdu);
      *sdu = *pdu;
      *pdu = remPdu;
   }
   else
   {
      /* The entire remaining PDU forms the SDU */
      *sdu = *pdu;
      *pdu = NULLP;
   }
   (*liCnt)++;
   RETVALUE(ROK);
}

/**
 *
 * @brief Private handler to reassemble from a segment or a PDU
 *
 * @b Description
 *        Private handler invokded by kwAmmReassembleSdus with either a
 *        PDU or a segment of a PDU. This is also called in the case of
 *        reestablishment and hence out of sequence joining is also to
 *        be supported
 *
 *
 * @param[in]  rbCb     RB control block 
 * @param[in]  pdu      PDU to be reassembled
 * @param[in]  amHdr    AM header received for this segment/PDU
 *
 *  @return  Void
 *
 */
#ifdef ANSI
PRIVATE Void kwAmmProcPduOrSeg
(
KwCb                  *gCb,
KwUlRbCb              *rbCb,
KwAmHdr               *amHdr,
Buffer                *pdu
)
#else
PRIVATE Void kwAmmProcPduOrSeg(gCb, rbCb, amHdr, pdu)
KwCb                  *gCb;
KwUlRbCb              *rbCb;
KwAmHdr               *amHdr;
Buffer                *pdu;
#endif
{
   Buffer             *sdu;
   U16                liCnt = 0;

   TRC2(kwAmmProcPduOrSeg)

   if ((AMUL.expSn != amHdr->sn) || (AMUL.expSo != amHdr->so))
   {
      /* Release the existing partial SDU as we have PDUs or */
      /* segments that are out of sequence                   */
      KW_FREE_BUF(AMUL.partialSdu);
   }

   if (amHdr->fi & KW_FI_FIRST_SEG)
   {
      /* The first byte is not first byte of any SDU. That would mean */
      /* that there should be a partial SDU. If it is not there we    */
      /* ignore this portion of the PDU                               */
      if (AMUL.partialSdu == NULLP)
      {
         kwAmmGetSdu(gCb,&liCnt, amHdr, &pdu, &sdu);
         KW_FREE_BUF(sdu);
      }
      else if (amHdr->numLi == 0)
      {
         SCatMsg(pdu, AMUL.partialSdu, M2M1);
         KW_FREE_BUF(AMUL.partialSdu);
      }
      else
      {
         kwAmmGetSdu(gCb,&liCnt, amHdr, &pdu, &sdu);
         SCatMsg(sdu, AMUL.partialSdu, M2M1);
         KW_FREE_BUF(AMUL.partialSdu);
         kwUtlSndDatInd(gCb,rbCb, sdu);
      }
   }
   else
   {
      /* This is the case where the first byte starts an SDU */
      /* Any existingg partial SDU is there by error         */
      if (AMUL.partialSdu != NULLP)
      {
         KW_FREE_BUF(AMUL.partialSdu);
      }
   }

   /* The below while loop covers starting with second LI */
   while(liCnt < amHdr->numLi)
   {
      kwAmmGetSdu(gCb,&liCnt, amHdr, &pdu, &sdu);
      kwUtlSndDatInd(gCb,rbCb, sdu);
   }

   if (amHdr->fi & KW_FI_LAST_SEG)
   {
      /* Any left over PDU will be joined with the next PDU */
      AMUL.partialSdu = pdu;
   }
   else if (pdu != NULLP)
   {
      AMUL.partialSdu = NULLP;
      kwUtlSndDatInd(gCb,rbCb, pdu);
   }
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}

/**
 *
 * @brief Private handler to reassemble SDUs
 *
 * @b Description
 *        Private handler invokded by kwAmmProcessPdus with the PDU
 *        from the reception buffer in sequence to reassemble SDUs and 
 *        send it to PDCP. 
 *
 *        - With the stored header info, FI and LSF segment / concatenate 
 *          PDUs or byte segments of PDUs to get the associated SDU.   
 *
 * @param[in]  rbCb     RB control block 
 * @param[in]  pdu      PDU to be reassembled
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwReassembleSdus
(
KwCb                  *gCb,
KwUlRbCb              *rbCb,
KwAmRecBuf          **recBuf
)
#else
PRIVATE S16 kwReassembleSdus(gCb, rbCb, recBuf)
KwCb                  *gCb;
KwUlRbCb              *rbCb;
KwAmRecBuf          **recBuf;
#endif
{
   KwSeg        *seg;

   TRC2(kwReassembleSdus)
   if ((*recBuf)->amHdr.rf == 0)
   {
      /* This is a PDU */
      kwAmmProcPduOrSeg(gCb,rbCb, &(*recBuf)->amHdr, (*recBuf)->pdu);
      AMUL.expSn = ((*recBuf)->amHdr.sn + 1) % 1024;
      AMUL.expSo = 0;
   }
   else
   {
      /* This is a set of segments */
      KW_LLIST_FIRST_SEG((*recBuf)->segLst, seg);
      AMUL.expSn = (*recBuf)->amHdr.sn;
      AMUL.expSo = 0;
      while(seg)
      {
         kwAmmProcPduOrSeg(gCb,rbCb, &seg->amHdr, seg->seg);
         AMUL.expSo = seg->soEnd + 1;
         KW_LLIST_NEXT_SEG((*recBuf)->segLst, seg);
      }
      AMUL.expSn = ((*recBuf)->amHdr.sn + 1) % 1024;
      AMUL.expSo = 0;
   }

   RETVALUE(ROK);
} /* kwReassembleSdus */

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
PUBLIC S16 kwAmmUlReEstablish
(
KwCb              *gCb,
CmLteRlcId        rlcId,
Bool                sendReEst,
KwUlRbCb            *rbCb
)
#else
PUBLIC S16 kwUlAmmReEstablish(rlcId, rbCb)
KwCb              *gCb;
CmLteRlcId        rlcId;
Bool                sendReEst;
KwUlRbCb            *rbCb;
#endif
{
   KwSn   sn    = 0;
   KwSn   mSn   = 0;
   KwSn   mVrMr = 0;

#ifndef KW_PDCP
   KwKwuSapCb *kwKwSap = NULLP;         /* KWU SAP Information */
#endif

   TRC2(kwAmmReEstablish);

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmReEstablish(rbCb)\n"));

   sn = AMUL.vrR;

   MODAMR(AMUL.vrMr, mVrMr, AMUL.vrR); 
   MODAMR(sn, mSn, AMUL.vrR); 

   /* Reassemble SDUs from PDUs with SN less than upper edge of the window */
   while (mSn < mVrMr)
   {
      if (AMUL.recBuf[sn] != NULLP)
      {
         if (AMUL.recBuf[sn]->allRcvd == TRUE)
         {
            kwReassembleSdus(gCb,rbCb, &AMUL.recBuf[sn]);
            /* if (AMUL.recBuf[sn]->pdu != NULLP)
                KW_FREE_BUF(AMUL.recBuf[sn]->pdu); */
         }
         else
         {
            KwSeg *seg = NULLP;
            /* Remove PDU and segments */
            KW_FREE_BUF(AMUL.recBuf[sn]->pdu);

            KW_LLIST_FIRST_SEG(AMUL.recBuf[sn]->segLst, seg)
            while (seg != NULLP)
            {
               KW_FREE_BUF(seg->seg);
               cmLListDelFrm(&(AMUL.recBuf[sn]->segLst),&(seg->lstEnt));
               KW_FREE(gCb,seg, sizeof(KwSeg));
               KW_LLIST_FIRST_SEG(AMUL.recBuf[sn]->segLst, seg);
            }
         }

         KW_FREE(gCb,AMUL.recBuf[sn], sizeof(KwAmRecBuf));
      }
      sn = (sn + 1) % 1024;
      MODAMR(sn, mSn, AMUL.vrR); 
   }
   /* Discard remaining PDUs and bytesegments in recBuf */

   /* Stop all timers and reset variables */
   /* Venki */
   if(TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_AMUL_REORD_TMR))
   {
       kwStopTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_REORD_TMR);
   }
   if(TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_AMUL_STA_PROH_TMR))
   {
       kwStopTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_STA_PROH_TMR);
   }
   if(TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_AMDL_POLL_RETX_TMR))
   {
       kwStopTmr(gCb,(PTR)rbCb, KW_EVT_AMDL_POLL_RETX_TMR);
   }
   AMUL.sn   = 0;
   AMUL.vrR  = 0; 
   AMUL.vrH  = 0;
   AMUL.vrX  = 0;
   rbCb->m.amUl.vrMr = (rbCb->m.amUl.vrR + KW_AM_WIN_SZ) % 1024;
   AMUL.vrMs = 0;
   AMUL.staTrg  = FALSE;
   AMUL.cntrlBo = 0;
#if 0
#ifdef LTE_L2_MEAS
   /* Discard SDUs from the sduQ */
   kwUtlEmptySduQ(rbCb, &AMDL.sduQ);
#else
   kwUtlEmptySduQ(&AMDL.sduQ);
#endif
   AMDL.nxtTx = NULLP;
#endif
#ifndef KW_PDCP
   kwKwSap = gCb->u.ulCb->kwuUlSap + KW_UI_PDCP;

   if (sendReEst)
   {
      KwUiKwuReEstCmpInd(&kwKwSap->pst, kwKwSap->suId, rlcId);
   }
#endif
   RETVALUE(ROK);
} /* kwUlAmmReEstablish */

/**
 *
 * @brief 
 *
 *        Handler for reorder timer expiry
 *
 * @b Description: 
 *
 *        This function is used to handle events upon expiry of reorder timer
 *            
 *  @param[in] rbCb   RB control block 
 *  @param[in] sduId  Sdu ID of the SDU to be discarded
 *  @return  Void 
 *
 */

#ifdef ANSI
PUBLIC Void kwAmmReOrdTmrExp 
(
KwCb        *gCb,
KwUlRbCb    *rbCb                        /* AM UL Info */
)
#else
PUBLIC Void kwAmmReOrdTmrExp(rbCb)
KwCb        *gCb;
KwUlRbCb    *rbCb;                       /* AM UL Info */
#endif
{
   KwAmUl *amUl = &(rbCb->m.amUl);
   KwSn sn    = 0;
   KwSn mSn   = 0;
   KwSn mVrMr = 0; 
   KwSn mVrMs = 0; 
   KwSn mVrH = 0; 
   Bool tmrRunning = FALSE;

   TRC2(kwAmmReOrdTmrExp);

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmReOrdTmrExp(rbCb)\n"));

   /* Update vrMs */
   sn = amUl->vrX;

   MODAMR(sn, mSn, amUl->vrR);
   MODAMR(amUl->vrMr, mVrMr, amUl->vrR);

   while (mSn < mVrMr)
   {
      if ( (amUl->recBuf[sn] == NULLP) ||
            ((amUl->recBuf[sn] != NULLP) &&
            (!amUl->recBuf[sn]->allRcvd)) )
      {
         amUl->vrMs = sn;
         amUl->staTrg = TRUE; 
         /* Check if staProhTmr is running */
         tmrRunning = kwChkTmr(gCb,(PTR) rbCb, KW_EVT_AMUL_STA_PROH_TMR);

         if (!tmrRunning)
         {
            kwUpdCntrlBo(gCb,amUl);
printf("\n************ REORDER Timer Exp: PROHIBIT timer not running, Updated cntrlBo[%d]\n",amUl->cntrlBo);            
         }
         if (amUl->cntrlBo)
         {
/*Pradeep - start, fix, added the bellow function to construct and send the STATUS PDU to RLC-DL*/         
            kwAssembleCntrlInfo(gCb,rbCb);
/*Pradeep - end, fix*/
#if 0
            Bool staPduPrsnt;
            S32  bo = 0;

           AMDL.cntrlBo = AMUL.cntrlBo;
           /* Accumulate bo */
           KW_UPD_AMBO(AMDL, bo); 

           /* Fill StaRsp and send it to MAC */
           staPduPrsnt = (AMDL.cntrlBo) ? TRUE : FALSE;
           kwUtlSndDStaRsp(rbCb, bo, AMDL.estHdrSz, staPduPrsnt);
#endif
         }

         break;
      }
      sn = (sn + 1) % 1024;
      MODAMR(sn, mSn, amUl->vrR);
   }

   /* Update vrX */
   MODAMR(amUl->vrH, mVrH, amUl->vrR);
   MODAMR(amUl->vrMs, mVrMs, amUl->vrR);
   if (mVrH > mVrMs)
   {
      kwStartTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_REORD_TMR);
      amUl->vrX = amUl->vrH;
   }

/*Pradeep - start*/
printf("\n********************** REORDER Timer Exp *************************\n");
printf("UEID[%d] LchId[%d] RbId[%d]\n",rbCb->rlcId.ueId,rbCb->lch.lChId,rbCb->rlcId.rbId);
printf("VR(R)[%d] VR(H)[%d] VR(X)[%d] VR(MS)[%d] VR(MR)[%d]",amUl->vrR,amUl->vrH,amUl->vrX,amUl->vrMs,amUl->vrMr);
printf("\n******************************************************************\n");
/*Pradeep - end*/

if(amUl->vrMr == 767)
{
    printf("\n VR[MR] = %d breakpoint reached \n",amUl->vrMr);
}

   RETVOID;
} /* kwAmmReOrdTmrExp */

/**
 *
 * @brief 
 *
 *        Handler for status prohibit timer expiry
 *
 * @b Description: 
 *
 *        This function is used to handle events upon expiry of status prohibit
 *        timer 
 *            
 *  @param[in] rbCb   RB control block
 *  @param[in] sduId  Sdu ID of the SDU to be discarded
 *  @return  Void 
 *
 */

#ifdef ANSI
PUBLIC Void kwAmmStaProTmrExp 
(
KwCb        *gCb,
KwUlRbCb    *rbCb                        /* AM UL Info */
)
#else
PUBLIC Void kwAmmStaProTmrExp(gCb, rbCb)
KwCb        *gCb;
KwUlRbCb    *rbCb;                       /* AM UL Info */
#endif
{
   KwAmUl *amUl = &(rbCb->m.amUl);

   TRC2(kwAmmStaProTmrExp);

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmStaProTmrExp(rbCb)\n"));

   amUl->cntrlBo = 0;
   if (amUl->staTrg == TRUE)
   {
      kwUpdCntrlBo(gCb,amUl);
   }
   /* kw002.201 : Sending StaRsp after StaProhibit tmr expiry */
   if (amUl->cntrlBo)
   {
/*Pradeep - start, fix, added the bellow function to construct and send the STATUS PDU to RLC-DL*/         
      kwAssembleCntrlInfo(gCb,rbCb);
      /*amUl->cntrlBo = 0;*/
/*Pradeep - end, fix*/

#if 0
      AMDL.cntrlBo = AMUL.cntrlBo;
      /* Accumulate bo */
      KW_UPD_AMBO(AMDL, bo); 
      /* Fill StaRsp and send it to MAC */
      staPduPrsnt = (AMDL.cntrlBo) ? TRUE : FALSE;
      kwUtlSndDStaRsp(rbCb, bo, AMDL.estHdrSz, staPduPrsnt);
#endif
   }

   RETVOID; 
} /* kwAmmStaProTmrExp */

#if 0
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
KwUlRbCb    *rbCb,
KwSn      mAckSn,
CmLList   *retxNode
)
#else
PRIVATE Void kwUpdRemPduAck(rbCb, mAckSn, retxNode)
KwUlRbCb    *rbCb;
KwSn      mAckSn;
CmLList   *retxNode;
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
         KW_AM_SUC_RETX_PDU(rbCb, retx);
      }
   }

   /* For the remaining ACKs  after last nackSn */
   MODAMT(AMDL.txSn, mSn, AMDL.vtA);
   sn = AMDL.txSn;
   while(mSn < mAckSn)
   {
      if ((AMDL.txBuf[sn] != NULLP) )
      {
         KWDBGP((KW_DBGMASK_AM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
                  (gCb->init.prntBuf, "kwUpdRemPduAck: Handle ACK for PDU with sn = \
                   %d\n", sn));

         /* Remove pdus from txBuf */
         kwAmmSucTxPdu(rbCb, sn);
      }
      mSn++; sn = (sn + 1)%1024;
   }

   RETVOID;
}
#endif

/**
 *
 * @brief 
 *
 *        Handler to extract an element of AM Header
 *
 * @b Description: 
 *
 *        This function is used to extract an element of AM header. 
 *            
 *
 */

#ifdef ANSI
PRIVATE Void kwExtractElmnt
(
KwCb        *gCb,
Buffer      *pdu,
KwExtHdr    *hdrInfo
)
#else
PRIVATE Void kwExtractElmnt(gCb, pdu, hdrInfo)
KwCb        *gCb;
Buffer      *pdu;
KwExtHdr    *hdrInfo;
#endif
{
   U8   hdr  = 0x00;
   U8   pLen = hdrInfo->pLen;
   U8   len  = (U8)hdrInfo->len;
   U16  val  = 0;
   U8   tHdr = 0x00;
   U8   fLen = 0;
   U8   rLen = 0;
   U8   rLen1 = 0;
   U16  tVal;
       
   TRC2(kwExtractElmnt);

   hdr = hdrInfo->hdr;
   
   if (pLen == 0)
   {
      SRemPreMsg(&hdr, pdu);
      pLen = 8;
   }
   tHdr = hdr;
   if (len <= 8)
   {
      val = tHdr >> (KW_BYTE_LEN - (len));
      hdr =  hdr << len;
      pLen -= len;
   }
   else if (len > 8)                                       
   {
      fLen = pLen;
      val = tHdr;
      val = val >> (KW_BYTE_LEN - fLen);
      val = val << (len - fLen);
      rLen = len - fLen;
      SRemPreMsg(&hdr, pdu);
      tHdr = hdr;
      if (rLen <= 8)
      {
         hdr = hdr >> (KW_BYTE_LEN - rLen);               
         val = val | hdr;
         hdr = tHdr << rLen;
         pLen = (KW_BYTE_LEN - rLen);
      }                                                     
      else
      {
        rLen1 = rLen - KW_BYTE_LEN;
        tVal = hdr;
        tVal = tVal << rLen1;
        val = val | tVal;

        SRemPreMsg(&hdr, pdu);
        tHdr = hdr;
        hdr = hdr >> (KW_BYTE_LEN - rLen1);
        val = val | hdr;
        hdr = tHdr << rLen1;
        pLen = (KW_BYTE_LEN - rLen1);
      }
   }

   hdrInfo->pLen = pLen;
   hdrInfo->hdr = hdr;
   hdrInfo->val = val;
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}


/**
 *
 * @brief 
 *
 *        Handler to form control bits
 *
 * @b Description: 

 *
 *        This function is used to assemble control bits for the control PDU
 *            
 * @param[in] cntrlInfo  Control Info
 * @param[in] staPdu     Status PDU
 * @param[in] kwDatReq   Data Request Information
 *
 * @return Void   
 */

#if 1
#ifdef ANSI
PRIVATE Void kwFormCntrlBits 
(
KwCb        *gCb,
KwCntrlInfo *cntrlInfo,
U16         *staPdu,
U16         *maxCPduLen
)
#else
PRIVATE Void kwFormCntrlBits(gCb, cntrlInfo, staPdu, maxCPduLen)
KwCb        *gCb,
KwCntrlInfo *cntrlInfo;
U16         *staPdu;
U16         *maxCPduLen;
#endif
{
   U16  val     = cntrlInfo->val;
   U16  len     = cntrlInfo->len;
   U16  idx     = cntrlInfo->idx;
   U8   eb      = cntrlInfo->emtBits;
   U16  e1Idx   = cntrlInfo->e1Idx;
   U16  e2Idx   = cntrlInfo->e2Idx;   
   U8   e1eb    = cntrlInfo->e1eb;

   U16 pIdx      = idx;                                       
   U16 cIdx      = idx + 1;                                   
   U16 tPdu;                                               
   U16 tVal      = val;                                        

   TRC2(kwFormCntrlBits);

   /* this is best possible example for unreadable code */
   if (eb >= len)                                        
   {                                                       
      tPdu = (tVal << (eb-len) ) | staPdu[pIdx];           
      staPdu[pIdx] = tPdu;                                
      eb = eb - len;                                    
      if (len != KW_SO_LEN)
      {
         /* Store e1Idx/e2Idx and e1eb */                  
         e1Idx = e2Idx = pIdx;                            
         e1eb = eb;                                       
      }
   }                                                       
   else                                                    
   {                                                       
      if (eb == 0)                                        
      {                                                    
         staPdu[cIdx] = 0;
         tVal = tVal << (KW_2BYTE_LEN - len);
         staPdu[cIdx] = tVal;                             
         eb = KW_2BYTE_LEN - len;                        
         /* Store e1Idx/e2Idx and e1eb */                  
         if (len != KW_SO_LEN)
         {
            e1Idx = e2Idx = cIdx;                            
            e1eb = eb;                                       
         }
      }                                                    
      else /* eb < len */                                
      {                                                    
         tPdu = (tVal >> (len - eb)) | staPdu[pIdx];    
         staPdu[pIdx] = tPdu;                             
         staPdu[cIdx] = 0;
         staPdu[cIdx] = tVal << (KW_2BYTE_LEN - (len - eb));             
         eb = KW_2BYTE_LEN - (len - eb);                

         if (len != KW_SO_LEN)
         {
         /* Store e1Idx/e2Idx and e1eb */                  
         if (eb == 15)                                    
         {                                                  
            e1Idx = pIdx;                                  
            e2Idx = cIdx;                                  
            e1eb = 0;                                       
         }                                                  
         else                                               
         {                                                  
            e1Idx = e2Idx = cIdx;                          
            e1eb = eb;                                     
         }                                                  
         }
      }                                                    
      
      if ((cIdx - idx == 1) && (idx != 0)) 
      {
         *maxCPduLen -= 2;
      }
      idx = cIdx;                                        
   }                                                       

   cntrlInfo->val     = val;
   cntrlInfo->len     = (U8)len;
   cntrlInfo->idx     = idx;
   cntrlInfo->emtBits = eb;
   cntrlInfo->e1Idx   = e1Idx;
   cntrlInfo->e2Idx   = e2Idx;   
   cntrlInfo->e1eb    = e1eb;
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}
#else

/**
 *
 * @brief 
 
#ifdef ANSI
PRIVATE Void kwFormCntrlBits 
(
KwCntrlInfo *cntrlInfo,
U16         *staPdu,
KwDatReq    *kwDatReq
)
#else
PRIVATE Void kwFormCntrlBits(cntrlInfo, staPdu, kwDatReq)
KwCntrlInfo *cntrlInfo;
U16         *staPdu;
KwDatReq    *kwDatReq;
#endif
{
   U16  val     = cntrlInfo->val;
   U16  len     = cntrlInfo->len;
   U16  idx     = cntrlInfo->idx;
   U8   eb      = cntrlInfo->emtBits;
   U16  e1Idx   = cntrlInfo->e1Idx;
   U16  e2Idx   = cntrlInfo->e2Idx;   
   U8   e1eb    = cntrlInfo->e1eb;

   U16 pIdx      = idx;                                       
   U16 cIdx      = idx + 1;                                   
   U16 tPdu;                                               
   U16 tVal      = val;                                        

   TRC2(kwFormCntrlBits);

   /* this is best possible example for unreadable code */
   if (eb >= len)                                        
   {                                                       
      tPdu = (tVal << (eb-len) ) | staPdu[pIdx];           
      staPdu[pIdx] = tPdu;                                
      eb = eb - len;                                    
      if (len != KW_SO_LEN)
      {
         /* Store e1Idx/e2Idx and e1eb */                  
         e1Idx = e2Idx = pIdx;                            
         e1eb = eb;                                       
      }
   }                                                       
   else                                                    
   {                                                       
      if (eb == 0)                                        
      {                                                    
         staPdu[cIdx] = 0;
         tVal = tVal << (KW_2BYTE_LEN - len);
         staPdu[cIdx] = tVal;                             
         eb = KW_2BYTE_LEN - len;                        
         /* Store e1Idx/e2Idx and e1eb */                  
         if (len != KW_SO_LEN)
         {
            e1Idx = e2Idx = cIdx;                            
            e1eb = eb;                                       
         }
      }                                                    
      else /* eb < len */                                
      {                                                    
         tPdu = (tVal >> (len - eb)) | staPdu[pIdx];    
         staPdu[pIdx] = tPdu;                             
         staPdu[cIdx] = 0;
         staPdu[cIdx] = tVal << (KW_2BYTE_LEN - (len - eb));             
         eb = KW_2BYTE_LEN - (len - eb);                

         if (len != KW_SO_LEN)
         {
         /* Store e1Idx/e2Idx and e1eb */                  
         if (eb == 15)                                    
         {                                                  
            e1Idx = pIdx;                                  
            e2Idx = cIdx;                                  
            e1eb = 0;                                       
         }                                                  
         else                                               
         {                                                  
            e1Idx = e2Idx = cIdx;                          
            e1eb = eb;                                     
         }                                                  
         }
      }                                                    
      
      if ((cIdx - idx == 1) && (idx != 0)) 
      {
         kwDatReq->pduSz -= 2;
      }
      idx = cIdx;                                        
   }                                                       

   cntrlInfo->val     = val;
   cntrlInfo->len     = (U8)len;
   cntrlInfo->idx     = idx;
   cntrlInfo->emtBits = eb;
   cntrlInfo->e1Idx   = e1Idx;
   cntrlInfo->e2Idx   = e2Idx;   
   cntrlInfo->e1eb    = e1eb;
   /*kw004.201 Adding of Missing Trace in LTE RLC PDCP*/
   RETVOID;
}
#endif /* UDX Changes */

/**
 *
 * @brief 
 *
 *        Handler to updated expected byte seg 
 *
 * @b Description: 
 *
 *        This function is used to update expected byte segment and allRcvd flag
 *        for recBuf.
 *
 * @param[in]  amUl  AM Uplink Control Block
 * @param[in]  sn    Sequence Number
 * @param[in]  so    Segment Offset
 * 
 * @return Void
 *            
 *
 */

#ifdef ANSI
PRIVATE Void kwAmmUpdExpByteSeg
(
KwCb               *gCb,
KwAmUl             *amUl,
KwSeg              *seg
)
#else
PRIVATE Void kwAmmUpdExpByteSeg(gCb, amUl, seg)
KwCb               *gCb;
KwAmUl             *amUl;
KwSeg              *seg;
#endif
{
   U16             seqSo   = 0;                                          
   KwSn            sn      = seg->amHdr.sn;
   Bool            lstRcvd = FALSE;

   TRC2(kwAmmUpdExpByteSeg);

   KWDBGP(gCb, (KW_DBGMASK_AM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwAmmUpdExpByteSeg(amUl, sn, so)\n"));
                                                           
   if (seg->amHdr.so != amUl->recBuf[sn]->expSo)
   {
      RETVOID;
   }
   seqSo   = seg->soEnd + 1;  
   amUl->recBuf[sn]->expSo = seqSo;
   lstRcvd = seg->amHdr.lsf;
   /* kw003.201 - This should update seg with the one after newSeg */
   KW_LLIST_NEXT_SEG(amUl->recBuf[sn]->segLst, seg);
   while(seg)
   {
      if (seg->amHdr.so == seqSo)
      {
         seqSo = seg->soEnd + 1;
         lstRcvd = seg->amHdr.lsf;
         KW_LLIST_NEXT_SEG(amUl->recBuf[sn]->segLst, seg);
      }
      else
      {
         amUl->recBuf[sn]->expSo = seqSo;
         RETVOID;
      }
   }
   if (lstRcvd == TRUE)
   {
      amUl->recBuf[sn]->allRcvd = TRUE;
   }

   RETVOID;
} /* kwAmmUpdExpByteSeg */


/*@}*/

  
/********************************************************************30**
  
         End of file:     kw_amm_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:43 2014
  
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

