

/**********************************************************************
 
    Name:   LTE UE Simulator layer
 
    Type:   C include file
 
    Desc:   Defines required by LTE UE Simulator
 
    File:   ue_rlc.c
 
    Sid:      ue_rlc.c@@/main/1 - Sun Mar 28 22:59:26 2010
 
    Prg:    vp
 
**********************************************************************/
 

/**********************************************************************
 This file (ue_rlc.c) implements RLC layer for UE simulator                  
 Brief functionality description:                                 
    1. Forming of RLC and PDCP PDUs                               
    2. Reassembly of RLC PDUs received from eNodeB.               
    3. Handling UL allocation by requesting RLC for PDUS.         
    4. Demultiplexing DL data into RLC PDUs and delivery to RLC  
*********************************************************************/
/* header include files -- defines (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system service interface */
#include "cm_hash.h"       /* common hash list */
#include "cm_llist.h"      /* common linked list library */
#ifndef SS_CAVIUM
#include "cm_inet.h"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_err.h"        /* common error */
#include "cm_lte.h"        /* common LTE */
#include "cm_pasn.h"        /* common LTE */
#ifndef SS_CAVIUM
#include <pcap.h>
#endif /* SS_CAVIUM */
/* ue007.101: unused file */
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
#include "ue.h"
#include "ue_err.h"

/* ue002.101: Changes to support MSPD CL */
#ifdef YS_MSPD
#include "LtePhyL2Api.h" /* Phy api file */
#include "apidefs.h"     /* Phy api file */
#include "resultcodes.h" /* Phy api file */
#endif
/* header/extern include files (.x) */
#include "gen.x"           /* general layer typedefs */
#include "ssi.x"           /* system services typedefs */
#include "cm5.x"           /* common timers */
#include "cm_hash.x"       /* common hash list */
#include "cm_lib.x"        /* common library */
#include "cm_llist.x"      /* common linked list */
#ifndef SS_CAVIUM
#include "cm_inet.x"       /* common tokens */
#endif /* SS_CAVIUM */
#include "cm_mblk.x"       /* memory management */
#include "cm_tkns.x"       /* common tokens */
#include "cm_lte.x"       /* common tokens */
#include "cm_pasn.x"        /* common LTE */
#include "nhu_asn.x"
#include "ue_nhu_app.x"    /* UE App Interface with RRC */
#include "cm_emm.x"        /* EMM Defines */
#include "cm_esm.x"        /* ESM Defines */
#include "cm_emm_esm.x"    /* EMM-ESM Defines */
#include "ue_app.x"        /* UE application includes */
#include "tfu.x"
#include "ue.x"            /* typedefs for MAC */

/* ue002.101: Multi ue support changes on Uu interface */ 
#ifdef ENB_PERF_MEAS
EXTERN Bool ueAppSignalingComplte;
#endif
/* ue006.101: Changes for end to end performance */
PUBLIC U16 noRlcSdus = 0, noRlcPdus = 0;
typedef struct ueExtHdr
{
   U16 val;
   U16 len;
   U8  hdr;
   U8  pLen;
} UeExtHdr;

/* ue002.101: Changes to support RLC UM mode */
#ifdef UE_SUPPORT_RLC_UM_MODE
PRIVATE S16 ueRlcExtractUmHdr ARGS((Buffer    *pdu,
                                    UeRlcUmHdr  *umHdr,                     
                                    UeCb        *ueCb));
#endif

PRIVATE S16 ueRlcExtractAmHdr
(
Buffer      *pdu,                         
UeRlcAmHdr  *amHdr,
U8          *fByte                    
);

PUBLIC S16 ueRlcAmReAssemblePdu
(
UeCb     *ueCb,
UeRlcAmHdr *amHdr,
U8       lcId,
Buffer   *pdu
);

PUBLIC S16 ueRlcExtPdcpHdr
(
UeCb             *ueCb,
U8               lcId,
Buffer           *mBuf
);
PUBLIC S16 ueRlcSndDatInd
(
UeCb             *ueCb,
U8               lcId,
Buffer           *mBuf
);

PRIVATE Void ueRlcExtractElmnt
(
Buffer      *pdu,
UeExtHdr    *hdrInfo
);

U8  statBuf[UEMAXBUFLEN]={0};
S32 count = 20;

/* ue002.101: Changes to support RLC UM mode */
#ifdef UE_SUPPORT_RLC_UM_MODE
/* 
 *
 *       Fun:    ueRlcExtractUmHdr 
 * 
 *       Desc:   This function extracts the RLC UM header.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueRlcExtractUmHdr 
(
Buffer    *pdu,                         /* Received PDU */
UeRlcUmHdr  *umHdr,                      /* AM Header Info */
UeCb       *ue                           /* UeCb */
)
#else
PRIVATE S16 ueRlcExtractUmHdr(pdu, umHdr, ue)
Buffer    *pdu;                        /* Received PDU */
UeRlcUmHdr  *umHdr;                     /* AM Header Info */
UeCb        *ue;                      /* UeCb */
#endif
{
   U8 e;                        /* Extension Bit */
   Data *dst = NULLP;           /* Destination Buffer */
   Data li[2];                  /* Data */
   U16 numLi;                   /* Number of LIs */
   S32     totalSz;             /* Sum of LIs */
   MsgLen  pduSz;               /* PDU size */
   MsgLen  tPduSz;              /* PDU size backup */
   S16      ret;                /* Return Value */

   TRC2(ueRlcExtractUmHdr)

   numLi = 0;
   e = 0;
   dst = li;

   SFndLenMsg(pdu, &pduSz);
   tPduSz = pduSz;
   totalSz = 0;

   if (ue->rlc.snLen == 1)
   {
      ret = SRemPreMsg(dst,pdu);
      if (ret != ROK)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                    "ueRlcExtractUmHdr: SRemPreMsg Failed\n"); 
         RETVALUE(RFAILED);
      }
      pduSz--;
      umHdr->sn = (dst[0]) & 0x1F; 
      umHdr->fi = (dst[0]) >> 6;
      e       = (dst[0]>>5) & 0x01;
   }

   else if (ue->rlc.snLen == 2)
   {
      ret = SRemPreMsgMult(dst,2,pdu);
      if (ret != ROK)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                    "ueRlcExtractUmHdr: SRemPreMsg Failed\n"); 
         RETVALUE(RFAILED);
      }
      pduSz -= 2;
      if ( !( ( dst[0] ) >> 5) )
      {
         umHdr->fi = ( dst[0] ) >> 3;
         e       = ( (dst[0] ) >> 2) & 0x01;
         umHdr->sn = (  dst[0] & 0x03) << 8;
         umHdr->sn  |= dst[1];
      }
      else
      {
         /* Reserved values.So discard it  and log an error */
         UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                    "ueRlcExtractUmHdr: Invalid Reserved values for PDU\n"); 
         RETVALUE(RFAILED);
      }
   }

   while (e && numLi < UE_RLC_MAX_LI && pdu)
   {
      ret = SRemPreMsgMult(dst,2,pdu);
      if (ret != ROK)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                    "ueRlcExtractUmHdr: Invalid Reserved values for PDU\n"); 
         RETVALUE(RFAILED);
      }
      umHdr->li[numLi] = ((dst[0]) & 0x7F) << 4;
      umHdr->li[numLi] |= dst[1] >> 4;
      if (umHdr->li[numLi] == 0)
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                    "ueRlcExtractUmHdr: Received LI with 0\n"); 
         RETVALUE(RFAILED); 
      }
      totalSz += umHdr->li[numLi];
      /* The situation where in the PDU size is something that does not
         match with the size in LIs*/
      if ( pduSz <=  totalSz )
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                    "Corrupted PDU\n"); 
         RETVALUE(RFAILED); 
      }
      numLi++;
      pduSz -= 2;

      e = ((dst[0]) & 0x80) >> 7;

      if ( e && numLi < UE_RLC_MAX_LI)
      {
         U8 tmp = ((dst[1]) & 0x08) >> 3;
         umHdr->li[numLi] = ( dst[1] & 0x07) << 8;
         if (e) 
         {
            ret = SRemPreMsg(dst,pdu);
            if (ret != ROK)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                    "SRemPreMsg Failed\n"); 
               RETVALUE(RFAILED);
            }
          /* The first byte lies in the first 8 bits.We want them in the
             last 8 bits */
            umHdr->li[numLi] |= ( dst[0] ); 
            if (umHdr->li[numLi] == 0)
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                          "Received 0 for LI\n");
               RETVALUE(RFAILED); 
            }
            totalSz += umHdr->li[numLi];
            pduSz--;
            numLi++;

          /* The situation where in the PDU size is something that does not
             match with the size in LIs*/
            if ( pduSz <  totalSz )
            {
               RETVALUE(RFAILED); 
            }
         }
         e = tmp;
      }
      else
      {
         /* PDU was constructed with LIs that exceeded UE_RLC_MAX_LI */
         if (e)
            RETVALUE(RFAILED);
      }
   }

   if ( numLi <= UE_RLC_MAX_LI )
   {
      umHdr->numLi = numLi;
   }
   else
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                   "liCount exceeded the maximum count\n");
      RETVALUE(RFAILED);
   }

   if ((totalSz +  ue->rlc.snLen) > tPduSz)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
                   "Corrupted PDU\n");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}
#endif

/* 
 *
 *       Fun:    ueRlcExtractAmHdr 
 * 
 *       Desc:   This function extracts the RLC AM header.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PRIVATE S16 ueRlcExtractAmHdr
(
Buffer      *pdu,                         /* Received PDU */
UeRlcAmHdr  *amHdr,                      /* AM Header Info */
U8          *fByte                        /* First byte for contrl PDU */
)
#else
PRIVATE S16 ueRlcExtractAmHdr(pdu, amHdr, fByte)
Buffer      *pdu;                        /* Received PDU */
UeRlcAmHdr  *amHdr;                     /* AM Header Info */
U8          *fByte;                      /* First byte for contrl PDU */
#endif
{
   Buffer *tPdu = NULLP;
   U8     e = 0;
   U16    li = 0;
   U16    liCnt = 0;
   MsgLen pduSz = 0;
   MsgLen totalSz = 0;
   UeExtHdr hdrInfo;

   TRC2(ueRlcExtractAmHdr)


   cmMemset((U8*)&hdrInfo, 0, sizeof(UeExtHdr));

   tPdu = pdu;

   /* Extract fixed part of the header */ 
   SFndLenMsg(pdu,&pduSz);

   hdrInfo.len = UE_RLC_DC_LEN;
   ueRlcExtractElmnt(pdu, &hdrInfo);
   amHdr->dc = (U8) hdrInfo.val;

   if (amHdr->dc == UE_RLC_STATUS_PDU)
   {
      *fByte = hdrInfo.hdr;
      RETVALUE(ROK);
   }
   hdrInfo.len = UE_RLC_RF_LEN;
   ueRlcExtractElmnt(pdu, &hdrInfo); 
   amHdr->rf = (U8) hdrInfo.val;

   hdrInfo.len = UE_RLC_P_LEN;
   ueRlcExtractElmnt(pdu, &hdrInfo); 
   amHdr->p = (U8)hdrInfo.val;

   hdrInfo.len = UE_RLC_FI_LEN;
   ueRlcExtractElmnt(pdu, &hdrInfo);
   amHdr->fi = (U8)hdrInfo.val;

   hdrInfo.len = UE_RLC_E_LEN;
   ueRlcExtractElmnt(pdu, &hdrInfo);
   e = amHdr->e = (U8)hdrInfo.val;

   hdrInfo.len = UE_RLC_SN_LEN;
   ueRlcExtractElmnt(pdu, &hdrInfo);
   amHdr->sn = hdrInfo.val;

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueRlcExtractAmHdr: RLC SN %d ",amHdr->sn));

   if (amHdr->rf == UE_RLC_SEGMENT_PDU)
   {
      /* Extract extn part of the header */
      hdrInfo.len = UE_RLC_LSF_LEN;
      ueRlcExtractElmnt(pdu, &hdrInfo);
      amHdr->lsf = (U8)hdrInfo.val;

      hdrInfo.len = UE_RLC_SO_LEN;
      ueRlcExtractElmnt(pdu, &hdrInfo); 
      amHdr->so = hdrInfo.val;
      pduSz -= 2;
   }

   /* Extract LIs */ 
   while (e && pdu)
   {
      hdrInfo.len = UE_RLC_E_LEN;
      ueRlcExtractElmnt(pdu, &hdrInfo); 
      e = amHdr->e = (U8)hdrInfo.val;

      if ( pdu )
      {
         hdrInfo.len = UE_RLC_LI_LEN;
         ueRlcExtractElmnt(pdu, &hdrInfo);
         li = hdrInfo.val;

         if (li == 0)
         {
            UE_FREE_BUF(pdu);
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
      pduSz -= (S16)((liCnt + ((liCnt-1)/2) + 3));
   }
   else
   {
      pduSz -= (S16)((liCnt + (liCnt/2)) + 2);
   }

   if ( totalSz >= pduSz )
   {
      UE_FREE_BUF(pdu);
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueRlcExtractElmnt
 * 
 *       Desc:   This function extracts the elements of RLC header.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PRIVATE Void ueRlcExtractElmnt
(
Buffer      *pdu,
UeExtHdr    *hdrInfo
)
#else
PRIVATE Void ueRlcExtractElmnt(pdu, hdrInfo)
Buffer      *pdu;
UeExtHdr    *hdrInfo;
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
       

   TRC2(ueRlcExtractElmnt)

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueRlcExtractElmnt:  Extracting the elements of RLC header"));

   hdr = hdrInfo->hdr;
   
   if (pLen == 0)
   {
      SRemPreMsg(&hdr, pdu);
      pLen = 8;
   }
   tHdr = hdr;
   if (len <= UE_RLC_BYTE_LEN)
   {
      val = tHdr >> (UE_RLC_BYTE_LEN - (len));
      hdr =  hdr << len;
      pLen -= len;
   }
   else if (len > UE_RLC_BYTE_LEN)                                       
   {
      fLen = pLen;
      val = tHdr;
      val = val >> (UE_RLC_BYTE_LEN - fLen);
      val = val << (len - fLen);
      rLen = len - fLen;
      SRemPreMsg(&hdr, pdu);
      tHdr = hdr;
      if (rLen <= UE_RLC_BYTE_LEN)
      {
         hdr = hdr >> (UE_RLC_BYTE_LEN - rLen);               
         val = val | hdr;
         hdr = tHdr << rLen;
         pLen = (UE_RLC_BYTE_LEN - rLen);
      }                                                     
/* ue003.101: added remove DRB1 check */ 
      else
      {
        rLen1 = rLen - UE_RLC_BYTE_LEN;
        tVal = hdr;
        tVal = tVal << rLen1;
        val = val | tVal;

        SRemPreMsg(&hdr, pdu);
        tHdr = hdr;
        hdr = hdr >> (UE_RLC_BYTE_LEN - rLen1);
        val = val | hdr;
        hdr = tHdr << rLen1;
        pLen = (UE_RLC_BYTE_LEN - rLen1);
      }
   }

   hdrInfo->pLen = pLen;
   hdrInfo->hdr = hdr;
   hdrInfo->val = val;
}

/* 
 *
 *       Fun:    ueRlcUmReAssemblePdu
 * 
 *       Desc:   This function re-assembles the UM PDUs received
 *               from the lower layer and sends the SDUs to
 *               upper layer.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRlcUmReAssemblePdu
(
UeCb     *ueCb,
UeRlcUmHdr *umHdr, 
U8       lcId,
Buffer   *pdu
)
#else
PUBLIC S16 ueRlcUmReAssemblePdu(ueCb,umHdr,lcId,pdu)
UeCb     *ueCb;
UeRlcUmHdr *umHdr;
U8       lcId;
Buffer   *pdu;
#endif
{
   U16 liCount = 0;                 /* LI count */
   U16 cnt = 0;                   /* Loop counter */
   U8  fi =0;                      /* Framing Info */
   U16 sn = 0;                      /* Sequence Number of current PDU */
   MsgLen len = 0;                  /* PDU Length */
   Buffer *sdu = NULLP;                 /* SDU to be sent to upper layer */
   Buffer *remPdu = NULLP;              /* Remaining PDU */
   Buffer **partialSdu = NULLP;         /* Partial SDU */
   U16 *li = NULLP;
   U16      rcvdSn    = ueCb->rlc.rbArr[lcId].rcvd_um_seq;

   TRC2(ueRlcUmReAssemblePdu)
      
   liCount = umHdr->numLi;
   fi = umHdr->fi;
   li = (U16 *)&(umHdr->li);
   sn  =  umHdr->sn;

   for ( cnt = 0; (cnt <= liCount);cnt++ )
   {
      if ( cnt < liCount )
         len = umHdr->li[cnt];
      else
      {
         if (pdu == NULLP)
         {
           RETVALUE(ROK);
         }
         SFndLenMsg(pdu,&len);
      }
      UE_ALLOC_BUF(sdu);
      SSegMsg(pdu,len,&remPdu);
      SCatMsg(sdu,pdu,M1M2);
      SPutMsg(pdu);
      pdu = remPdu;
      
      partialSdu = &(ueCb->rlc.rbArr[lcId].partialSdu);
      /* While re-assembling the SDUs, consider the first LI and perform the following steps.
          -# If the first bit of FI(Framing Info of 2  bits) is set => 
                -# The current Data field in the PDU is a segment. So form a SDU only if the 
                   rbCb->m.um.umUl.partialSdu exists and the SNs are in-sequence.
                -# If there are no LIs and the second bit of LI is 1 then a partial SDU is formed
                   which would not be sent to the upper layer.
          -# else
                -# If rbCb->partialSdu is not NULL then flush it off.
                -# If LI count > 0 or LI count is 0 and second bit of FI is not 1 
                         The SDU is complete.So send it to upper layer.
                -# else
                         The SDU is partial and is placed in rbCb->m.um.umUl.partialSdu;
      */
             
      if (cnt == 0)
      {
         if ( fi & UE_RLC_FI_FIRST_SEG)
         {
            if ((*partialSdu != NULLP) && (sn == (rcvdSn + 1) % 1024 ))
            {
               SCatMsg(*partialSdu,sdu,M1M2);
               SPutMsg(sdu);
               sdu = NULLP;
               if ( liCount > 0 || !(fi & UE_RLC_FI_LAST_SEG))
               {
                  ueRlcSndDatInd(ueCb, lcId, *partialSdu);
                  *partialSdu = NULLP;
               }
            }
            else
            {
                /* Partial Sdu stored is not valid now.So free it */
               if (*partialSdu != NULLP)
               {
                  SPutMsg(*partialSdu);
                  *partialSdu = NULLP;
               }
               SPutMsg(sdu);
               sdu = NULLP;
            }
         }
         else
         {
            if ( *partialSdu )
               *partialSdu = NULLP;
            if (liCount > 0 || !( fi & UE_RLC_FI_LAST_SEG))
            {
               ueRlcSndDatInd(ueCb, lcId, sdu);
            }
            else
            {
                  *partialSdu = sdu; 
            }
         }
      }
      /*
          If the SDU pointer has the last Data field of the PDU
            -# If FI is 1,place the SDU in rbCb->m.um.umDl.partialSdu
            -# else send the SDU to upper layer.
      */
      else if ( cnt == liCount )
      {
         if ( fi & UE_RLC_FI_LAST_SEG)
            *partialSdu = sdu;
         else
            ueRlcSndDatInd(ueCb, lcId, sdu);
      }
      /*  
         If the LI is something other than the first one, just send the SDU to the upper layer */
      else
      {
         ueRlcSndDatInd(ueCb, lcId, sdu);
      }
   }
   RETVALUE(ROK);
}

/* 
 *
 *       Fun:    ueRlcDatInd
 * 
 *       Desc:   This function processes the header of the
 *               PDU received from lower layer and calls the
 *               function which re-assembles the SDUs
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRlcDatInd
(
UeCb   *ueCb, 
U8     lcId, 
Buffer *mBuf
)
#else
PUBLIC S16 ueRlcDatInd(ueCb,lcId,mBuf)
UeCb   *ueCb;
U8     lcId;
Buffer *mBuf;
#endif
{
#ifdef UE_SUPPORT_RLC_UM_MODE
   UeRlcUmHdr  umHdr;
#endif
   U8    fByte = 0;
   UeRlcAmHdr  amHdr;
   S16    ret = ROK;

   TRC2(ueRlcDatInd)

   /* ue002.101: kworks_fix */
   if (mBuf == NULLP)
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
         "ueRlcDatInd: mBuf is NULL\n");
      RETVALUE(RFAILED);
   }

   /* if CCCH data : directly send it to RRC */
   if ( lcId == UE_LC_SRB0 )
   {
      
      UE_DBGP_INFO((UE_PRNTBUF, 
         "ueRlcDatInd:  Processing the CCCH data in data indication"));
      ueRrcDatInd(ueCb, lcId, mBuf);
      RETVALUE(ROK);
   }

#ifdef UE_SUPPORT_RLC_UM_MODE
   if (lcId == UE_LC_SRB1 || lcId == UE_LC_SRB2)
   {
      cmMemset((U8 *)(&amHdr), 0, sizeof(UeRlcAmHdr));

      ret = ueRlcExtractAmHdr(mBuf, &amHdr, &fByte);
      if ( ret != ROK )
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
            "ueRlcDatInd: Extraction of Hdr failed\n"); 
         RETVALUE(RFAILED);
      }
      /* Check if its a control PDU */
      if (amHdr.dc == UE_RLC_STATUS_PDU)
      {
         UE_DBGP_INFO((UE_PRNTBUF, 
            "ueRlcDatInd: Status Report Received "));
         UE_FREE_BUF(mBuf);
         RETVALUE(RFAILED);
      }

      if ( amHdr.p == 1 )
      {
         ueCb->rlc.rbArr[lcId].ackToBeSent = TRUE;
         ueCb->rlc.rbArr[0].bo += UE_RLC_AM_HDR_LEN;
      }
      ret  = ueRlcAmReAssemblePdu(ueCb, &amHdr, lcId, mBuf);
      ueCb->rlc.rbArr[lcId].rcvd_am_seq = amHdr.sn;
   }
   else
   {
      cmMemset((U8 *)(&umHdr), 0, sizeof(UeRlcUmHdr));

      ret = ueRlcExtractUmHdr(mBuf, &umHdr, ueCb);
      if ( ret != ROK )
      {
         UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
            "ueRlcDatInd: Extraction of Hdr failed\n"); 
         RETVALUE(RFAILED);
      }

      ret  = ueRlcUmReAssemblePdu(ueCb, &umHdr, lcId, mBuf);
      ueCb->rlc.rbArr[lcId].rcvd_um_seq = umHdr.sn;
   }
#else
   cmMemset((U8 *)(&amHdr), 0, sizeof(UeRlcAmHdr));


   ret = ueRlcExtractAmHdr(mBuf, &amHdr, &fByte);
   if ( ret != ROK )
   {
      UELOGERROR(ERRCLS_ADD_RES, EUE099, (ErrVal)0,
         "ueRlcDatInd: Extraction of Hdr failed\n"); 
      RETVALUE(RFAILED);
   }
      /* Check if its a control PDU */
   if (amHdr.dc == UE_RLC_STATUS_PDU)
   {
      UE_DBGP_INFO((UE_PRNTBUF, 
         "ueRlcDatInd: Status Report Received "));
      UE_FREE_BUF(mBuf);
      RETVALUE(RFAILED);
   }

   if ( amHdr.p == 1 )
   {
      ueCb->rlc.rbArr[lcId].ackToBeSent = TRUE;
      ueCb->rlc.rbArr[0].bo += UE_RLC_AM_HDR_LEN;
   }
   ret  = ueRlcAmReAssemblePdu(ueCb, &amHdr, lcId, mBuf);
   ueCb->rlc.rbArr[lcId].rcvd_am_seq = amHdr.sn;
#endif
  
   RETVALUE(ROK);
}


/* 
 *
 *       Fun:    ueRlcAmReAssemblePdu
 * 
 *       Desc:   This function re-assembles the PDUs received
 *               from the lower layer and sends the SDUs to
 *               upper layer.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 *
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRlcAmReAssemblePdu
(
UeCb       *ueCb,
UeRlcAmHdr *amHdr, 
U8          lcId,
Buffer     *pdu
)
#else
PUBLIC S16 ueRlcAmReAssemblePdu(ueCb,amHdr,lcId,pdu)
UeCb       *ueCb;
UeRlcAmHdr *amHdr;
U8          lcId;
Buffer     *pdu;
#endif
{
   U16      idx = 0;
   MsgLen   len = 0;
   U16      numLi = amHdr->numLi;
   U16      rcvdSn    = ueCb->rlc.rbArr[lcId].rcvd_am_seq;
   U16      sn  = amHdr->sn;
   Buffer   *sdu = NULLP;
   Buffer   **partialSdu = NULLP; 
   Buffer   *remPdu     = NULLP;
   Buffer   *seg        = NULLP;
   U16      *li = NULLP;
   U8       fi = 0;
   U8       lsf = 0;

   TRC2(ueRlcAmReAssemblePdu)
 
   li = (U16 *)&(amHdr->li);
   fi = amHdr->fi;
 
   for (idx = 0; idx <= numLi; idx++)
   {
      if ( idx < numLi)
         len = li[idx];
      else
         SFndLenMsg(pdu, &len);

      UE_ALLOC_BUF(sdu);
      /* ue002.101: kworks_fix */
      if(sdu == NULLP)
      {
         RETVALUE(RFAILED);
      }

      SSegMsg (pdu, len, &remPdu);
      /* ue002.101: kworks_fix */
      if(pdu == NULLP)
      {
         RETVALUE(RFAILED);
      }

      SCatMsg (sdu, pdu, M1M2);
      UE_FREE_BUF(pdu);
      pdu = remPdu;

      partialSdu = &(ueCb->rlc.rbArr[lcId].partialSdu);

      UE_DBGP_INFO((UE_PRNTBUF, 
         "ueRlcAmReAssemblePdu: Re-assembling the PDU with sn %d",sn));

      /* For the first/last SDU */
      if (idx == 0)
      {
         /* Check if the first one is a segment */
         if ( fi & UE_RLC_FI_FIRST_SEG )
         {
               /* Parial sdu should exist before to concatenate this sdu and the
                * SN should be adjacent if its a PDU and SN can be same for
                * segments */
            if ((*partialSdu != NULLP) && 
               ((( seg == NULLP) && (sn == (rcvdSn + 1) % UE_RLC_MAX_AM_SEQ)) ||
               (( seg != NULLP) && ((sn == rcvdSn) || (sn == (rcvdSn + 1) % UE_RLC_MAX_AM_SEQ))) ) )
            {
               SCatMsg (*partialSdu, sdu, M1M2);
               UE_FREE_BUF(sdu);

                  /* If there're no more LIs and the last byte is not a segment,
                   * its a complete SDU */
               if ( numLi > 0 || (!(fi & UE_RLC_FI_LAST_SEG)) )
               {
                  ueRlcSndDatInd(ueCb, lcId, *partialSdu);
                  *partialSdu = NULLP;
               }

               if (lsf)
               {
                 UELOGERROR(ERRCLS_ADD_RES, EUE100, (ErrVal)0,
                    "ueRlcReAssembleSdu:Ignoring the mBuf as we received \
                    a (last)Segment\n"); 
               }
            }
            else
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE101, (ErrVal)sn,
                  "ueRlcReAssembleSdu: Received a Out of Sequence PDU\n"); 
               UE_FREE_BUF(*partialSdu);
               UE_FREE_BUF(sdu);
            }
         }
         /* First byte is not a segment */
         else
         {
            if ( *partialSdu )
            {
               UELOGERROR(ERRCLS_ADD_RES, EUE102, (ErrVal)sn,
                  "ueRlcReAssembleSdu: Freeing the partial Sdu when received\n"); 
               UE_FREE_BUF(*partialSdu);
            }

               /* For the completion of SDU */
            if (numLi > 0 || !( fi & UE_RLC_FI_LAST_SEG))
            {
               ueRlcSndDatInd(ueCb, lcId, sdu);
               if (lsf)
               {
                  /* We do nothing here as we assume there is not retransmission happening */
                  UELOGERROR(ERRCLS_ADD_RES, EUE103, (ErrVal)sn,
                     "ueRlcReAssembleSdu: Ignoring the mBuf as we received a \
                     (last)Segment\n"); 
               }
            }
               /* Store the partial sdu */
            else
            {
                  *partialSdu = sdu; 
            }
         }
      }
      /* Check if its the last SDU */
      else if ( idx == numLi)
      {
         /* Check if the last byte is a segment */
         if ( fi & UE_RLC_FI_LAST_SEG)
            *partialSdu = sdu;
         else
         {
               ueRlcSndDatInd(ueCb, lcId, sdu);
         }
      }
         /* For the SDUs in the middle of the data field */
      else
      {
         ueRlcSndDatInd(ueCb, lcId, sdu);
      }
   }
   RETVALUE(ROK);
}



/* 
 * 
 *       Fun:    ueRlcGetPdu
 * 
 *       Desc:   This function assembles the SDUs received
 *               from the upper layer and sends the PDUs to
 *               lower layer.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 * 
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRlcGetPdu
(
UeCb     *ueCb,
MsgLen   size,
Buffer   **pdu,
U8       *lcId
)
#else
PUBLIC S16 ueRlcGetPdu(ueCb,size,pdu,lcId)
UeCb     *ueCb;
MsgLen   size;
Buffer   **pdu;
U8       *lcId;
#endif
{
   CmLList *tmpNode;
   UeRlcSdu *sdu = NULLP;  
   U8       fi   = 0;
   U8       idx = 0;
   /* ue008.101: Added new variable rbIdx.*/
   U8       rbIdx = 0;
   RbCb     *rbCb = NULLP;
   Buffer   *remSdu = NULLP;
   MsgLen   pduSz = size;
   Buffer   *lpdu;

  /* ue002.101: Changes to support RLC UM mode */
#ifdef UE_SUPPORT_RLC_UM_MODE
   U8       logChId = 0;
   /* ue008.101: Added new variable liCnt.*/
   S8       liCnt = 0;
#endif

   TRC2(ueRlcGetPdu)
 
   *pdu = NULLP;
 
   
   if ( pduSz <= UE_RLC_AM_HDR_LEN )
   {
      /*ue007.101: No enough data to form PDUs : ccpu00117613 INFO */
      UE_DBGP_INFO((UE_PRNTBUF,
         "ueRlcGetPdu: Received PDUSZ  less than 2\n "));
      RETVALUE(RFAILED);
   }
   /* Check for any CCCH data */
   CM_LLIST_FIRST_NODE(&(ueCb->rlc.rbArr[0].sduLst), tmpNode); 
   if ( tmpNode != NULLP )
   {
      UE_DBGP_INFO((UE_PRNTBUF, 
         "ueRlcGetPdu: Sending CCCH pdu "));
      sdu = (UeRlcSdu *) tmpNode->node;
      *pdu = sdu->mBuf;
      sdu->mBuf = NULLP;
      ueCb->rlc.rbArr[0].bo -= sdu->len;
      cmLListDelFrm(&(ueCb->rlc.rbArr[0].sduLst), &(sdu->lstEnt));
      UE_FREE(sdu, sizeof(UeRlcSdu));
      *lcId = ueCb->rlc.rbArr[0].lcId; /* Should be 0 here */
      /* We return from here as we send only one PDU at a time */
      RETVALUE(ROK);
   }

   /* ue002.101: Changes to support RLC UM mode */
#ifdef UE_SUPPORT_RLC_UM_MODE
   UE_ALLOC_BUF(lpdu);
   *pdu = lpdu;
   for ( idx = 1; idx < UE_MAX_RB; idx++ )
   {
      rbCb = &(ueCb->rlc.rbArr[idx]);
      logChId = rbCb->lcId;

      if (logChId == UE_LC_SRB1 || logChId == UE_LC_SRB2)
      {
         if ( rbCb->ackToBeSent)
         {
            U16   ackData;
            U8    data[2] = {0,0};
            U16   ack_Sn = 0;

            /* Send ACK_SN as sn+1 so that all the PDUs till SN are received */
            ackData = 0x0000;
            ack_Sn  = (rbCb->rcvd_am_seq + 1) % UE_RLC_MAX_AM_SEQ;
            ackData = (U16)(ackData | ack_Sn);
            ackData = (ackData << 2);
            data[0] = (U8)(ackData>> UE_RLC_BYTE_LEN );
            data[1] = (U8)(ackData & 0xFF);
            SAddPstMsgMult(&data[0], UE_RLC_AM_HDR_LEN, *pdu);

            UE_DBGP_INFO((UE_PRNTBUF, 
                "ueRlcGetPdu: Sending a Status PDU with ackSn %d ", ack_Sn));

            rbCb->ackToBeSent = FALSE;
            ueCb->rlc.rbArr[0].bo -= UE_RLC_AM_HDR_LEN;
            *lcId = rbCb->lcId;
            break;
         }
         
         CM_LLIST_FIRST_NODE(&(rbCb->sduLst), tmpNode); 
         if ( tmpNode != NULLP )
         {
            /*printf("Sending Signalling Data for UeId = %d lcId = %d \n",ueCb->rnti, rbCb->lcId);*/
            /* Remove the size of RLC header */
            pduSz -= UE_RLC_AM_HDR_LEN;
            sdu = (UeRlcSdu *) tmpNode->node;
            if ( sdu->isSegmented )
               fi |= UE_RLC_FI_FIRST_SEG;
            if ( pduSz < sdu->len )
            {
               fi |= UE_RLC_FI_LAST_SEG;
               SSegMsg(sdu->mBuf,pduSz, &remSdu);
               SCatMsg(*pdu, sdu->mBuf, M1M2);
               SPutMsg(sdu->mBuf);
               rbCb->bo -= pduSz;
               sdu->isSegmented = TRUE;
               sdu->len -= pduSz;
               sdu->mBuf = remSdu;
            }
            else
            {
               SCatMsg(*pdu, sdu->mBuf,M1M2);
               SPutMsg(sdu->mBuf);
               sdu->mBuf = NULLP;
               rbCb->bo -= sdu->len;
               cmLListDelFrm(&(rbCb->sduLst), &sdu->lstEnt); 
               UE_FREE(sdu, sizeof(UeRlcSdu));
            }
            /* ue008.101: Fix for compilation error in UM mode.*/
            UE_ADD_RLC_HDR(*pdu, rbCb, fi,liCnt);
            
            UE_DBGP_INFO((UE_PRNTBUF, 
                "ueRlcGetPdu: Sending a Data PDU with sn %d  for lcId %d ",
                 rbCb->cur_am_seq, rbCb->lcId ));

            rbCb->cur_am_seq = (rbCb->cur_am_seq+ 1) % UE_RLC_MAX_AM_SEQ;
            *lcId = rbCb->lcId;
            break; 
         }
      }
      else /* UM Data PDU */
      {
         CM_LLIST_FIRST_NODE(&(rbCb->sduLst), tmpNode); 
         if ( tmpNode != NULLP )
         {
            /* printf("Sending Signalling Data for UeId = %d lcId = %d \n",ueCb->rnti, rbCb->lcId); */
            /* Remove the size of RLC header */
            pduSz -= UE_RLC_UM_HDR_LEN;
            sdu = (UeRlcSdu *) tmpNode->node;
            if (sdu->isSegmented)
            {
               fi |= UE_RLC_FI_FIRST_SEG;
            }
            else
            {
               fi = 0;
            }

            if ( pduSz < sdu->len )
            {
               fi |= UE_RLC_FI_LAST_SEG;
               SSegMsg(sdu->mBuf,pduSz, &remSdu);
               SCatMsg(*pdu, sdu->mBuf, M1M2);
               SPutMsg(sdu->mBuf);
               rbCb->bo -= pduSz;
               sdu->isSegmented = TRUE;
               sdu->len -= pduSz;
               sdu->mBuf = remSdu;
            }
            else
            {
               SCatMsg(*pdu, sdu->mBuf,M1M2);
               SPutMsg(sdu->mBuf);
               sdu->mBuf = NULLP;
               rbCb->bo -= sdu->len;
               cmLListDelFrm(&(rbCb->sduLst), &sdu->lstEnt); 
               UE_FREE(sdu, sizeof(UeRlcSdu));
            }

            UE_ADD_RLC_UM_HDR(*pdu, rbCb, fi);

            UE_DBGP_INFO((UE_PRNTBUF, 
                "ueRlcGetPdu: Sending a UM Data PDU with sn %d  for lcId %d ",
                 rbCb->cur_um_seq, rbCb->lcId ));

            rbCb->cur_um_seq = (rbCb->cur_um_seq+ 1) % UE_RLC_MAX_UM_SEQ;
            *lcId = rbCb->lcId;
            break; 
         }
#ifdef ENB_PERF_UL_DATA
         else
         {
           if( rbCb->lcId == UE_LC_DRB1 && (ueAppCellCb.state == UE_STATE_DATA_READY) 
              && (count <= 0) && (ueAppSignalingComplte == TRUE))
           {
             /* Send the Size requested packet */
             U16  tmp = 0;
             U8 sn[2] = {0,0};
             tmp = rbCb->pdcpSn;
             fi = 0;
             rbCb->pdcpSn = (rbCb->pdcpSn + 1) % UE_PDCP_MAX_DRB_UM_SEQ;
             sn[0] = (U8)(tmp & 0xFF);
             sn[1] = (U8)(tmp>>8);
             sn[1] |= 0x80; 
             SAddPreMsgMult(&sn[0], UE_RLC_UM_HDR_LEN, *pdu); /* 2 bytes added here */ 
             UE_ADD_RLC_UM_HDR(*pdu, rbCb, fi); /* 2 bytes added here */

             UE_DBGP_INFO((UE_PRNTBUF, 
                "ueRlcGetPdu: Sending a Data PDU with sn %d  for lcId 3 (perf) ",
                 rbCb->cur_am_seq));

             rbCb->cur_um_seq = (rbCb->cur_um_seq+ 1) % UE_RLC_MAX_UM_SEQ;
             SAddPstMsgMult(statBuf, (size - 4), *pdu);
             /* TODO: We should not set reportBsr in RLC layer. 
                      Need to revisit */
             ueCb->mac.reportBsr = TRUE;
             *lcId = 3; /* rbCb->lcId; */
/* ue003.101: count increment */ 
             count++;
           }
           else
               count--;

         }
#endif/* UM ENB_PERF_UL_DATA */
      }
   }/* For */

#else
   UE_ALLOC_BUF(lpdu);
   *pdu = lpdu;
   for ( idx = 1; idx < UE_MAX_RB; idx++ )
   {
      U8 liCnt = 0;
      rbCb = &(ueCb->rlc.rbArr[idx]);
      if ( rbCb->ackToBeSent)
      {
         U16   ackData;
         U8    data[2] = {0,0};
         U16   ack_Sn = 0;

         /* Send ACK_SN as sn+1 so that all the PDUs till SN are received */
         ackData = 0x0000;
         ack_Sn  = (rbCb->rcvd_am_seq + 1) % UE_RLC_MAX_AM_SEQ;
         ackData = (U16)(ackData | ack_Sn);
         ackData = (ackData << 2);
         data[0] = (U8)(ackData>> UE_RLC_BYTE_LEN );
         data[1] = (U8)(ackData & 0xFF);
         SAddPstMsgMult(&data[0], UE_RLC_AM_HDR_LEN, *pdu);

         UE_DBGP_INFO((UE_PRNTBUF, 
             "ueRlcGetPdu: Sending a Status PDU with ackSn %d ", ack_Sn));

         rbCb->ackToBeSent = FALSE;
         ueCb->rlc.rbArr[0].bo -= UE_RLC_AM_HDR_LEN;
         *lcId = rbCb->lcId;
         /* ue008.101: Set cur_am_seq and rcvd_am_seq to 0 
          * if ueCb->isDel is equal to 1 */
    if (ueCb->isDel == 1)
    {
        printf("lcId = %d\n", rbCb->lcId);
        rbCb->cur_am_seq = 0;
        rbCb->rcvd_am_seq = 0;
         ueCb->isDel = 0;
         for(rbIdx = 0; rbIdx < UE_NUM_RLC_RB_PER_UE; rbIdx++)
         {
            rbCb = &(ueCb->rlc.rbArr[rbIdx]);
            if(rbCb == NULLP)
               continue;
            rbCb->cur_am_seq = 0;
           rbCb->rcvd_am_seq = 0;
         } 
    }
         break;
      }
      CM_LLIST_FIRST_NODE(&(rbCb->sduLst), tmpNode); 
      if ( tmpNode != NULLP )
      {
/* ue003.101: added to print data traffic lcid */ 
         UE_DBGP_INFO((UE_PRNTBUF,"Sending Data for UeId = %d lcId = %d \n",ueCb->rnti, rbCb->lcId));
         /* Remove the size of RLC header */
         pduSz -= UE_RLC_AM_HDR_LEN;
         sdu = (UeRlcSdu *) tmpNode->node;
         if ( sdu->isSegmented )
            fi |= UE_RLC_FI_FIRST_SEG;
         if ( pduSz < sdu->len )
         {
            fi |= UE_RLC_FI_LAST_SEG;
            SSegMsg(sdu->mBuf,pduSz, &remSdu);
            SCatMsg(*pdu, sdu->mBuf, M1M2);
            SPutMsg(sdu->mBuf);
            rbCb->bo -= pduSz;
            sdu->isSegmented = TRUE;
            sdu->len -= pduSz;
            sdu->mBuf = remSdu;
         }
         else
         {
            SCatMsg(*pdu, sdu->mBuf,M1M2);
            SPutMsg(sdu->mBuf);
            sdu->mBuf = NULLP;
            rbCb->bo -= sdu->len;
            cmLListDelFrm(&(rbCb->sduLst), &sdu->lstEnt); 
            /* ue006.101: Changes for end to end performance */
            noRlcSdus++;
            UE_FREE(sdu, sizeof(UeRlcSdu));
         }
         /* ue006.101: Changes for end to end performance */
         noRlcPdus++;
         UE_ADD_RLC_HDR(*pdu, rbCb, fi, liCnt);
         
         UE_DBGP_INFO((UE_PRNTBUF, 
             "ueRlcGetPdu: Sending a Data PDU with sn %d  for lcId %d ",
              rbCb->cur_am_seq, rbCb->lcId ));

         rbCb->cur_am_seq = (rbCb->cur_am_seq+ 1) % UE_RLC_MAX_AM_SEQ;
         *lcId = rbCb->lcId;
         break; 
      }
#ifdef ENB_PERF_UL_DATA
      else
      {
        if( rbCb->lcId == UE_LC_DRB1 && (ueAppCellCb.state == UE_STATE_DATA_READY) 
           && (count <= 0) && (ueAppSignalingComplte == TRUE))
        {
           size -= 2; /* for RLC header */
          /* Send the Size requested packet */
          while(size > 0)
          {
             U8 sn[2] = {0,0};
             U8 temp = 0;
             U16  tmp = 0;
             tmp = rbCb->pdcpSn;
             fi = 0;
             rbCb->pdcpSn = (rbCb->pdcpSn + 1) % UE_PDCP_MAX_DRB_AM_SEQ;
             sn[0] = (U8)(tmp & 0xFF);
             sn[1] = (U8)(tmp>>8);
             sn[1] |= 0x80;
             temp = sn[0];
             sn[0] = sn[1];
             sn[1] = temp;
             SAddPstMsgMult(&sn[0], UE_RLC_AM_HDR_LEN, *pdu); /* 2 bytes added here  for PDCP Header*/
             size -= 2; 
             if ( size > (UE_SDU_SIZE - 1))
             {
                /* UE_ADD_RLC_HDR(*pdu, rbCb, fi);  2 bytes added here */

                UE_DBGP_INFO((UE_PRNTBUF, 
                "ueRlcGetPdu: Sending a Data PDU with sn %d  for lcId 3 (perf) ",
                rbCb->cur_am_seq));
                liCnt++;
                if ( liCnt % 2 ) size -= 2;
                else             size -= 1;

                 SAddPstMsgMult(statBuf, (UE_SDU_SIZE - 2), *pdu); 
                size -=(UE_SDU_SIZE - 2);
             }
             else
             {
                SAddPstMsgMult(statBuf, size, *pdu); 
                size = 0;
             }
          }
          /* Add the RLC Header here */
          UE_ADD_RLC_HDR(*pdu,rbCb,fi,liCnt);
          rbCb->cur_am_seq = (rbCb->cur_am_seq+ 1) % UE_RLC_MAX_AM_SEQ;
          /* TODO: We should not set reportBsr in RLC layer. 
             Need to revisit */
          ueCb->mac.reportBsr = TRUE;
          *lcId = 3; /* rbCb->lcId; */
        }
        else
            count--;

      }
#endif
   }
#endif/* UE_SUPPORT_RLC_UM_MODE */
    
   RETVALUE(ROK);
}

/* 
 * 
 *       Fun:    ueRlcDatReq
 * 
 *       Desc:   This function stores the SDUs received from
 *               upper layer after adding the PDCP header.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 * 
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRlcDatReq
(
UeCb     *ueCb,
U8       lcId,
Buffer   *mBuf
)
#else
PUBLIC S16 ueRlcDatReq(ueCb,lcId,mBuf)
UeCb     *ueCb;
U8       lcId;
Buffer   *mBuf;
#endif
{
   UeRlcSdu  *sdu   = NULLP;
   RbCb      *rbCb  = &(ueCb->rlc.rbArr[lcId]);
   U8        sn[2] = {0,0};
   U8        macI[UE_PDCP_MACI_LEN] = {0,0,0,0};
   /* ue006.101: Changes for end to end performance */
   PRIVATE   U32  pktdrped = 0;

   TRC2(ueRlcDatReq)
/* ue008.101: Flushing the SRBs context during HO, so that the corresponding ACKs and BO intended for 
   eNB1 will not go to eNB2 */   
   UeAppCb *ueAppCb = NULLP; 
   U8 rbIdx = 0;
   /* Get UeAppCb using the macro using ueCb->ueId */
   UE_GET_APPCB(ueCb->cellId,ueAppCb,ueCb->rnti);  
#ifdef TOTAL_ENB
   /* ue009.101: Added feature to drop the diffrent RRC messages.
    *  depends on the RRC timer. */
   if (((ueAppCb->hoState != 0) && (lcId == 1)) ||
        (ueAppCb->isReest != 0))
#else /* #ifdef TOTAL_ENB */
   if ((ueAppCb->hoState != 0) && (lcId == 1))
#endif
   {
      printf("\n**********RLC Context Resetted**************\n");

      for(rbIdx = 0; rbIdx < UE_NUM_RLC_RB_PER_UE; rbIdx++)
      {
         rbCb = &(ueCb->rlc.rbArr[rbIdx]);
         if(rbCb == NULLP)
            break;

         rbCb->rcvd_um_seq = 0;
         rbCb->cur_um_seq = 0;
         rbCb->rcvd_am_seq = 0;
         rbCb->cur_am_seq = 0;

         rbCb->bo = 0;
         rbCb->ackToBeSent = FALSE;

         /* free it */
         if(rbCb->partialSdu)
            SPutMsg(rbCb->partialSdu);

         if(rbCb->mBuf)
            SPutMsg(rbCb->mBuf);
      }
#ifdef TOTAL_ENB
   /* ue009.101: Added feature to drop the diffrent RRC messages.
    *  depends on the RRC timer. */
      ueAppCb->isReest = 0;
#endif
      rbCb = &(ueCb->rlc.rbArr[lcId]);
   }

   if (rbCb->sduLst.count > 500)
   {
      pktdrped++;
      if (pktdrped % 100 == 0)
      { /* ue007.101: type specifier error */
          UE_DBGP_INFO((UE_PRNTBUF, "Dropped %ld packets\n", pktdrped));
      }
      SPutMsg(mBuf);
      RETVALUE(RFAILED);
    }


   UE_ALLOC(sdu, sizeof(UeRlcSdu));
   /* ue002.101: kworks_fix */
   if(sdu == NULLP)
      RETVALUE(RFAILED);

   /* Add the PDCP header to this mBuf */
   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueRlcDatReq: Received a data request for lcId %d ", lcId));

   if ( lcId == UE_LC_SRB1  || lcId == UE_LC_SRB2)
   {
       sn[0] = rbCb->pdcpSn;
       rbCb->pdcpSn = (rbCb->pdcpSn + 1) % 32;
       SAddPreMsg(sn[0], mBuf);
       SAddPstMsgMult((Data *)&macI[0], UE_PDCP_MACI_LEN, mBuf);

   }
/* ue003.101: added remove DRB1 check */ 
   else
   {
      U16  tmp = 0;
      tmp = rbCb->pdcpSn;
      rbCb->pdcpSn = (rbCb->pdcpSn + 1) % UE_PDCP_MAX_DRB_AM_SEQ;
      sn[0] = (U8)(tmp & 0xFF);
      sn[1] = (U8)(tmp>>8);
      sn[1] |= 0x80; 
      SAddPreMsgMult(&sn[0], 2, mBuf); 
   }

   sdu->mBuf = mBuf;
   SFndLenMsg(mBuf, &(sdu->len));
    
   sdu->isSegmented = 0; 
   cmLListAdd2Tail(&rbCb->sduLst, &sdu->lstEnt);
   sdu->lstEnt.node = (PTR)sdu;

   rbCb->bo += sdu->len;
  
   RETVALUE(ROK);       
}

/* 
 * 
 *       Fun:    ueRlcGetBo
 * 
 *       Desc:   This function reports BO to MAC.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 * 
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRlcGetBo
(
UeCb             *ueCb,
U32              *lcg0,
U32              *lcg1,
U32              *lcg2,
U32              *lcg3
)
#else
PUBLIC S16 ueRlcGetBo(ueCb,lcg0,lcg1,lcg2,lcg3)
UeCb             *ueCb;
U32              *lcg0;
U32              *lcg1;
U32              *lcg2;
U32              *lcg3;
#endif
{
    TRC2(ueRlcGetBo)

   *lcg0 = ueCb->rlc.rbArr[0].bo + ueCb->rlc.rbArr[1].bo + ueCb->rlc.rbArr[2].bo;
/* ue003.101: correction lcg1 calculation */ 
   *lcg1 = ueCb->rlc.rbArr[3].bo + ueCb->rlc.rbArr[4].bo;
   *lcg2 = *lcg3 = 0;

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueRlcGetBo: Reporting BO to MAC as %ld for lcg0 and  %ld for lcg1", 
      *lcg0, *lcg1 ));

#ifdef ENB_PERF_UL_DATA
  if(ueAppSignalingComplte == TRUE)
  {
     *lcg1 =150000;
    /* printf("sending BO as greater value\n"); */
  }
#endif
   RETVALUE(ROK);
}

/* 
 * 
 *       Fun:    ueRlcSndDatInd
 * 
 *       Desc:   This function removes the PDCP header
 *               and gives the SDUs to upper layer.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 * 
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRlcSndDatInd
(
UeCb             *ueCb,
U8               lcId,
Buffer           *mBuf
)
#else
PUBLIC S16 ueRlcSndDatInd(ueCb,lcId,mBuf)
UeCb             *ueCb;
U8               lcId;
Buffer           *mBuf;
#endif
{
   U8 hdr[2] = {0,0};
   U8 macI[UE_PDCP_MACI_LEN] = {0,0,0,0};
   U16     sn = 0;

   TRC2(ueRlcSndDatInd)

   SRemPreMsg(&hdr[0], mBuf);

   UE_DBGP_INFO((UE_PRNTBUF, 
      "ueRlcSndDatInd: Sending Data Indication to application for lcId %d", 
      lcId ));

   if ( lcId == UE_LC_SRB1  || lcId == UE_LC_SRB2)
   {
      ueCb->rlc.rbArr[lcId].rcvdPdcpSn = hdr[0] & 0x1F;
      /* Remove the MAC-I for lcId 1 and 2 */
      SRemPstMsgMult((Data *)&macI[0],UE_PDCP_MACI_LEN, mBuf);
      ueRrcDatInd(ueCb, lcId, mBuf);
   }
   else
   {
      SRemPreMsg(&hdr[1], mBuf);
      if ( hdr[0] & 0x80 )
      {
         sn = ( ((hdr[0] & 0x0F )<< 8) | hdr[1]);
      }
      else
      {
         UE_DBGP_INFO((UE_PRNTBUF, 
            "ueRlcSndDatInd: PDCP Control PDU received "));
         SPutMsg(mBuf);
         RETVALUE(ROK);
      }
      ueCb->rlc.rbArr[lcId].rcvdPdcpSn = sn;
      ueDapDatInd(ueCb, lcId, mBuf);
   }
   RETVALUE(ROK);
}

/* 
 * 
 *       Fun:    ueRlcExtPdcpHdr
 * 
 *       Desc:   This function extracts the PDCP header
 *               of PDU received from lower layer.
 * 
 *       Ret:    ROK - ok RFAILED - incase of error
 * 
 *       Notes:  None
 * 
 *       File:   ue_rlc.c
 *
 */
#ifdef ANSI
PUBLIC S16 ueRlcExtPdcpHdr
(
UeCb             *ueCb,
U8               lcId,
Buffer           *mBuf
)
#else
PUBLIC S16 ueRlcExtPdcpHdr(ueCb,lcId,mBuf)
UeCb             *ueCb;
U8               lcId;
Buffer           *mBuf;
#endif
{
   U8 hdr[2] = {0,0};
   U16 sn = 0;

   TRC2(ueRlcExtPdcpHdr)

   SRemPreMsg(&hdr[0], mBuf);
   if ( lcId == UE_LC_SRB1  || lcId == UE_LC_SRB2)
   {
      ueCb->rlc.rbArr[lcId].rcvdPdcpSn = hdr[0] & 0x1F;
   }
/* ue003.101: added remove DRB1 check */ 
   else
   {
      SRemPreMsg(&hdr[1], mBuf);
      if ( hdr[0] & 0x80 )
      {
         sn = ( ((hdr[0] & 0x0F )<< 8) | hdr[1]);
      }
      else
      {
         UE_DBGP_INFO((UE_PRNTBUF, 
            "ueRlcExtPdcpHdr: PDCP Control PDU received "));
      }
   }
   RETVALUE(ROK);
   
}

/**********************************************************************
 
         End of file:     ue_rlc.c@@/main/1 - Sun Mar 28 22:59:26 2010
 
**********************************************************************/
 
/**********************************************************************
 
        Notes:
 
**********************************************************************/
 
/**********************************************************************
 
        Revision history:
 
**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vp            1. Initial Release.
/main/1+   ue002.101  sv            1. Multi ue support changes.
                                    2. Changes to support reading uesim
                                       configuration from file.
                                    3. Changes to support MSPD CL.
/main/1+   ue003.101  rp            1. Changes to support Multiple Drbs.
/main/1+   ue006.101  sriky         1. Performance tuning

/main/1+   ue007.101  ms            1. PDUSZ less then 2 message as INFO
                                    1. type specifier error.
/main/1+   ue008.101 ragrawal       1. Added new variables in ueRlcGetPdu(). 
                                    2. Fix for compilation error in UM mode.
                                    3. Added code to flushing the SRBs context 
                                       during HO, so that the corresponding ACKs 
                                       and BO intended for eNB1 will not go to eNB2.
                                    4. Set cur_am_seq and rcvd_am_seq to 0
                                       if ueCb->isDel is equal to 1 in ueRlcGetPdu().
/main/1+   ue009.101 akaranth       1. Added featutre to drop RRC messages, depends on the RRC timer.
*********************************************************************91*/

