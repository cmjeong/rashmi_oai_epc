

/**********************************************************************

     Name:     LTE-RLC Layer 
  
     Type:     C file
  
     Desc:     Source code for RLC Unacknowledged mode assembly and
               reassembly.This file contains following functions

                  --kwUmmQSdu
                  --kwUmmProcessSdus
                  --kwUmmProcessPdus
                  --kwUmmReAssembleSdus
                  --kwUmmReEstablish 

     File:     gp_umm.c

     Sid:      kw_umm_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:54 2014

     Prg:      vp 

**********************************************************************/
/** @file gp_umm.c
@brief RLC Unacknowledged Mode module
*/

/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *      1000372     LTE-MAC
 *      1000369     LTE-RRC
 */

/* header (.h) include files */
#include "envopt.h"             /* environment options */
#include "envdep.h"             /* environment dependent */
#include "envind.h"             /* environment independent */

#include "gen.h"                /* general */
#include "ssi.h"                /* system services interface */
#include "cm5.h"                /* Timer Functions */
#include "cm_lte.h"             /* common umts header file */
#include "cm_hash.h"            /* common hash module  file */
#include "cm_llist.h"           /* common list header file */
#include "ckw.h"                /* RRC layer */
#include "lkw.h"                /* RRC layer */
#include "kwu.h"                /* RLC service user */
#include "lkw.h"                /* LM Interface */
#include "rgu.h"                /* MAC layer */
#include "kw_env.h"             /* RLC environment options */

#include "kw.h"                 /* RLC layer */
#include "kw_err.h"
#include "kw_ul.h"


/* header/extern include files (.x) */

#include "gen.x"                /* general */
#include "ssi.x"                /* system services interface */
#include "cm_lib.x"             /* common library */
#include "cm5.x"                /* Timer Functions */
#include "cm_hash.x"            /* common hash module */
#include "cm_lte.x"             /* common umts file */
#include "cm_llist.x"           /* common list header file */
#include "ckw.x"                /* RRC layer */
#include "kwu.x"                /* RLC service user */
#include "lkw.x"                /* LM Interface */
#include "rgu.x"                /* MAC later */

#include "kw.x"                 /* RLC layer */
#include "kw_ul.x"

PRIVATE S16 kwUmmExtractHdr ARGS ((KwCb *gCb, KwUlRbCb *rbCb,
                                   Buffer *pdu,KwUmHdr **umHdr));
PRIVATE S16 kwUmmReAssembleSdus ARGS ((KwCb *gCb,KwUlRbCb *rbCb,
                                       KwUmRecBuf *umRecBuf));


/**
 *
 * @brief 
 * 
 *        Handler to process the Data Indication from the lower layer and send the PDUs to
 *        re-assembly unit. 
 *
 * @b Description:
 *
 *        This function processes the PDUs received from the lower layer
 *        re-orders them and sends them one after the other in sequence 
 *        to the re-assembly unit.
 *            
 * @param[in] rbCb     RB control block 
 * @param[in] pduInfo  Pdu information 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
#ifdef ANSI
PUBLIC S16 kwUmmProcessPdus
(
KwCb      *gCb,
KwUlRbCb    *rbCb,                   /* Rb Control Block */
KwPduInfo *pduInfo,                 /* Pdu  data and related information */
KwL2MeasUlThrpTimInfo *ulTimeInfo  /* Ul timing info */
)
#else
PUBLIC S16 kwUmmProcessPdus(gCb,rbCb,pduInfo,ulTimeInfo)
KwCb      *gCb;
KwUlRbCb    *rbCb;                   /* Rb Control Block */
KwPduInfo *pduInfo;                /* Pdu  data and related information */
KwL2MeasUlThrpTimInfo *ulTimeInfo; /* Ul timing info */
#endif
#else
#ifdef ANSI
PUBLIC S16 kwUmmProcessPdus
(
KwCb      *gCb,                 /* global Cb */
KwUlRbCb    *rbCb,                /* Rb Control Block */
KwPduInfo *pduInfo              /* Pdu  data and related information */
)
#else
PUBLIC S16 kwUmmProcessPdus(gCb,rbCb,pduInfo)
KwCb      *gCb;                 /* global Cb */
KwUlRbCb    *rbCb;                /* Rb Control Block */
KwPduInfo *pduInfo;             /* Pdu  data and related information */
#endif
#endif
#else
#ifdef ANSI
PUBLIC S16 kwUmmProcessPdus
(
KwCb      *gCb,
KwUlRbCb    *rbCb,                /* Rb Control Block */
KwPduInfo *pduInfo              /* Pdu  data and related information */
)
#else
PUBLIC S16 kwUmmProcessPdus(gCb,rbCb,pduInfo)
KwCb      *gCb;
KwUlRbCb    *rbCb;                /* Rb Control Block */
KwPduInfo *pduInfo;             /* Pdu  data and related information */
#endif
#endif
{
   U16 *vrUh;                   /* vr(uh) */
   U16 *vrUr;                   /* vr(ur) */
   KwSn *vrUx;                  /* vr(ux) */
   U16 curSn;                   /* Current Sequence Number */
   U8  pduCount;                /* PDU count */
   U8  count;                   /* Loop counter */
   U16 umReOrdWinSz;            /* UM ReOrder Window Size */
   KwUmHdr *umHdr;              /* UM Header Structure */
   KwUmRecBuf **recBuf;         /* UM Reception Buffer */
   S16 ret;                     /* Return Value */
   U16 umRcpWinSz;              /* Reception Window Size */
   KwUmUl *umUl;                /* UM UL Pointer */
   Bool tmrRunning;             /* Boolean for checking Tmr */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
   MsgLen              rlcSduSz = 0;  /*Holds length of Rlc Sdu*/
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */

   TRC2(kwUmmProcessPdus)
#ifdef DEBUGP 
   KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_UL),
                  (gCb->init.prntBuf," kwUmmProcessPdus(rbCb,pduInfo) \n"));
#endif
   count = 0;
 
   pduCount = pduInfo->numPdu;
   vrUh   = &(rbCb->m.umUl.vrUh);
   vrUr   = &(rbCb->m.umUl.vrUr);
   vrUx   = &(rbCb->m.umUl.vrUx);
   recBuf = (rbCb->m.umUl.recBuf);
   umReOrdWinSz= rbCb->m.umUl.umWinSz; 
   umRcpWinSz = umReOrdWinSz << 1;
   umHdr = NULLP;
   umUl = &(rbCb->m.umUl);

   while ( (count < pduCount) &&
           (count < RGU_MAX_PDU))
   {
      Buffer *pdu = pduInfo->mBuf[count];
      gCb->genSts.pdusRecv++;

      if ( kwUmmExtractHdr(gCb,rbCb,pdu,&umHdr) != ROK )  
      {
         /* Header extraction is a problem. So log an error and free the allocated memory */
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_UL),
                  (gCb->init.prntBuf,"kwUmmExtractHdr Failed\n"));
#endif
         KW_FREE(gCb,umHdr,sizeof(KwUmHdr));
         SPutMsg(pdu);
         count++;
         /* kw005.201 ccpu00117318, updating the statistics */
         gCb->genSts.errorPdusRecv++;
         continue;
      }
      curSn = umHdr->sn;

      KW_UM_CHK_DUP_PDU(rbCb,curSn,ret);   
      if ( ret )                    
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_UL),
                  (gCb->init.prntBuf,"Received a duplicate pdu with sn %d\n",curSn));
#endif
         SPutMsg(pdu);
         KW_FREE(gCb,umHdr,sizeof(KwUmHdr));
         count++;
         /* kw005.201 ccpu00117318, updating the statistics */
         gCb->genSts.unexpPdusRecv++;
         continue;
      } 

      KW_ALLOC(gCb,recBuf[curSn],sizeof(KwUmRecBuf));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( recBuf[curSn] == NULLP )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW215, (ErrVal) RFAILED,
            "KwRecBuf: recBuf allocation Failed.");
      KW_FREE(gCb,umHdr,sizeof(KwUmHdr));
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS
#ifdef LTE_RLC_R9
   KWDBGP((KW_DBGMASK_UM | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
   (gCb->init.prntBuf, "kwUmmProcessPdus: Log for ul ip throughput:\n \
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
            rbCb->rbL2Cb.l2Sts[KW_L2MEAS_UL_IP]->ulIpThruput.volSummation +=
               rbCb->l2MeasIpThruput.ulDataVol;
            rbCb->rbL2Cb.l2Sts[KW_L2MEAS_UL_IP]->ulIpThruput.timeSummation +=
               ulTimeInfo->thrpTimeUl;
            /*Reset ulDataVol in rbCb since it has been saved in l2Sts*/
            rbCb->l2MeasIpThruput.ulDataVol = 0;
         }
      }
   }
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS */

      recBuf[curSn]->pdu = pdu;
      recBuf[curSn]->umHdr = umHdr;
      SFndLenMsg(pdu,&(recBuf[curSn]->pduSz));
      /* kw005.201 ccpu00117318, updating the statistics */
      gCb->genSts.bytesRecv += recBuf[curSn]->pduSz;
      KW_CHK_SN_IN_REORD_WIN(curSn,rbCb,ret);

      if ( !ret )
      {
         U16 prevVrUr = *vrUr;
         KwSn sn;
         KwSn ur;
         KwSn tSn;
         KwSn tVrUh = rbCb->m.umUl.vrUh;
         *vrUh  = (curSn + 1) % umRcpWinSz;
         KW_CHK_SN_IN_REORD_WIN(prevVrUr,rbCb,ret); 
         if (!ret )
         {
            /* kw005.201 Added umRcpWinSz in calculating *vrUr */
            *vrUr = (*vrUh + umRcpWinSz - umReOrdWinSz) %  umRcpWinSz;         
            sn = (prevVrUr + 1) % umRcpWinSz;
            tSn = KW_UM_GET_VALUE(sn,tVrUh,umReOrdWinSz,umRcpWinSz);
            ur = KW_UM_GET_VALUE(*vrUr,tVrUh,umReOrdWinSz,umRcpWinSz);
            while ( tSn < ur )
            {
               if ( recBuf[sn] != NULLP)
               {
                  kwUmmReAssembleSdus(gCb,rbCb,recBuf[sn]);
                  KW_FREE(gCb,recBuf[sn]->umHdr,sizeof(KwUmHdr));
                  KW_FREE(gCb,recBuf[sn],sizeof(KwUmRecBuf));
               }
               sn = (sn + 1) % umRcpWinSz;
               tSn = KW_UM_GET_VALUE(sn,tVrUh,umReOrdWinSz,umRcpWinSz);
            }
         }
      }
      if ( recBuf[*vrUr] != NULLP )
      {
         KwSn prevVrUr = *vrUr;
         KwSn sn       = prevVrUr;
         KwSn tSn      = KW_UM_GET_VALUE(sn,*vrUh,umReOrdWinSz,umRcpWinSz); 
         KwSn tVrUr;
        /* kw005.201 */
         KwSn nextVrUr = (prevVrUr + 1)%umRcpWinSz;

         /* kw005.201 */
         KW_UM_FIND_NEXT_VRUR(umUl,nextVrUr,*vrUr);
         tVrUr = KW_UM_GET_VALUE(*vrUr,*vrUh,umReOrdWinSz,umRcpWinSz);
         while ( recBuf[sn] != NULLP && tSn < tVrUr )
         {
            kwUmmReAssembleSdus(gCb,rbCb,recBuf[sn]);
            KW_FREE(gCb,recBuf[sn]->umHdr,sizeof(KwUmHdr));
            KW_FREE(gCb,recBuf[sn],sizeof(KwUmRecBuf));
            sn = (sn + 1) % umRcpWinSz;
            tSn = KW_UM_GET_VALUE(sn,*vrUh,umReOrdWinSz,umRcpWinSz);
         }
      }

      tmrRunning = kwChkTmr(gCb,(PTR)rbCb, KW_EVT_UMUL_REORD_TMR);

      if ( tmrRunning ) 
      {
         KwSn tVrUx = KW_UM_GET_VALUE(*vrUx,*vrUh,umReOrdWinSz,umRcpWinSz);
         KwSn tVrUr = KW_UM_GET_VALUE(*vrUr,*vrUh,umReOrdWinSz,umRcpWinSz);
         /* kw005.201 changes for ccpu00117408 */
         KwSn tVrUh = KW_UM_GET_VALUE(*vrUh,*vrUh,umReOrdWinSz,umRcpWinSz);

         KW_CHK_SN_IN_REORD_WIN(*vrUx,rbCb,ret);
         /* kw005.201 changes for ccpu00117408 */
         if ( (tVrUx <= tVrUr) || ((!ret) && (tVrUx != tVrUh))) 
         {
            kwStopTmr(gCb,(PTR)rbCb,KW_EVT_UMUL_REORD_TMR); 
         }
      }
      tmrRunning = kwChkTmr(gCb,(PTR)rbCb, KW_EVT_UMUL_REORD_TMR);
      if ( !tmrRunning )
      {
         KwSn tVrUr = KW_UM_GET_VALUE(*vrUr,*vrUh,umReOrdWinSz,umRcpWinSz);
         KwSn tVrUh = KW_UM_GET_VALUE(*vrUh,*vrUh,umReOrdWinSz,umRcpWinSz);
         if ( tVrUh > tVrUr )
         {
            kwStartTmr(gCb,(PTR)rbCb,KW_EVT_UMUL_REORD_TMR); 
            *vrUx = * vrUh;
         }
      }
      count++;

   }
   RETVALUE(ROK);   
}

/**
 *
 * @brief  
 *
 *        Handler to reassemble the SDUs and send them to the upper layer.
 *
 * @b Description:
 *
 *        This function processes the received in-sequence PDU and
 *        re-assembles the SDUs and sends them to the upper layer.
 *            
 * @param[in] rbCb       RB control block
 * @param[in] umRecBuf   Reception Buffer to be Re-Assembled 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */

#ifdef ANSI
PRIVATE S16 kwUmmReAssembleSdus
(
KwCb   *gCb,
KwUlRbCb *rbCb,                   /* RB Control Block */
KwUmRecBuf *umRecBuf            /* Pdu to be re-assembled */
)
#else
PRIVATE S16 kwUmmReAssembleSdus(gCb,rbCb,umRecBuf)
KwCb   *gCb;
KwUlRbCb *rbCb;                   /* RB Control Block */
KwUmRecBuf *umRecBuf;           /* Pdu to be re-assembled */
#endif
{
   U16 liCount;                 /* LI count */
   U16 count;                   /* Loop counter */
   U8  fi;                      /* Framing Info */
   U16 sn;                      /* Sequence Number of current PDU */
   MsgLen len;                  /* PDU Length */
   Buffer *sdu;                 /* SDU to be sent to upper layer */
   Buffer *remPdu;              /* Remaining PDU */
   Buffer *pdu;                 /* PDU buffer */
   Buffer **partialSdu;         /* Partial SDU */

   TRC2(kwUmmReAssembleSdus)  
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_UL),
                  (gCb->init.prntBuf," kwUmmReAssembleSdus(rbCb,umRecBuf) \n"));
#endif
   liCount = umRecBuf->umHdr->numLi;
   fi = umRecBuf->umHdr->fi;
   pdu = umRecBuf->pdu; 
   sn  =  umRecBuf->umHdr->sn;
 
   for ( count = 0; (count <= liCount);count++ )
   {
      if ( count < liCount )
         len = umRecBuf->umHdr->li[count];
      else
      {
         if (pdu == NULLP)
         {
           RETVALUE(ROK);
         }
         SFndLenMsg(pdu,&len);
      }
         
      SGetMsg(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb), &sdu);
      SSegMsg(pdu,len,&remPdu);
      SCatMsg(sdu,pdu,M1M2);
      SPutMsg(pdu);
      pdu = remPdu;
      
      partialSdu = &(rbCb->m.umUl.partialSdu);
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
             
      if (count == 0)
      {
         if ( fi & 2 )
         {
            /* kw005.201 */
            if ((*partialSdu != NULLP) && 
                (sn == ((rbCb->m.umUl.sn + 1) % 
                        (rbCb->m.umUl.umWinSz << 1))))
            {
               SCatMsg(*partialSdu,sdu,M1M2);
               SPutMsg(sdu);
               if ( liCount > 0 || !(fi & 1))
               {
                  kwUtlSndDatInd(gCb,rbCb,*partialSdu);
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
            if (liCount > 0 || !( fi & 1))
            {
               kwUtlSndDatInd(gCb,rbCb,sdu);
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
       else if ( count == liCount )
      {
         if ( fi & 1)
            *partialSdu = sdu;
         else
            kwUtlSndDatInd(gCb,rbCb,sdu);
      }
      /*  
         If the LI is something other than the first one, just send the SDU to the upper layer */
      else
      {
         kwUtlSndDatInd(gCb,rbCb,sdu);
      }
   }
   rbCb->m.umUl.sn = sn;

   RETVALUE(ROK);
}
/**
 *
 * @brief 
 *
 *        Handler to process the re-establishment request received from the upper layer. 
 *
 * @b Description:
 *
 *        This function does the following functions : 
 *         - If direction of the RB is downlink : Remove all the SDUs in the SDU queue.
 *         - If direction of the RB is uplink   : Call kwUmmReAssembleSdus() for each PDU with SN < VR(UH)         
 *                                                
 *  @param[in] rbCb  RB control block 
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 kwUmmUlReEstablish
(
KwCb       *gCb,
CmLteRlcId  rlcId,
Bool        sendReEst,
KwUlRbCb    *rbCb
)
#else
PUBLIC S16 kwUmmUlReEstablish(gCb,rlcId, rbCb)
KwCb        *gCb;
CmLteRlcId  rlcId;
Bool        sendReEst;
KwRbCb      *rbCb;
#endif
{

   KwSn  curSn;
   KwSn  vrUh;
   KwUmRecBuf **recBuf;      /* UM Reception Buffer */
   KwKwuSapCb *kwKwSap = NULLP;         /* KWU SAP Information */

   TRC2(kwUmmReEstablish)
#ifdef DEBUGP
   KWDBGP(gCb,
         (KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_DL |  KW_DBGMASK_UL),
                  (gCb->init.prntBuf," kwUmmReEstablish(rbCb) \n"));
#endif
    curSn = rbCb->m.umUl.vrUr;
    vrUh  = rbCb->m.umUl.vrUh;
    recBuf =  rbCb->m.umUl.recBuf;
    /* Venki */ 
    if(TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_UMUL_REORD_TMR))
    {
        kwStopTmr(gCb,(PTR)rbCb,KW_EVT_UMUL_REORD_TMR);
    }
    while ( curSn < vrUh )
    {
       if ( recBuf[curSn] != NULLP )
       {
          kwUmmReAssembleSdus(gCb,rbCb,recBuf[curSn]);
          KW_FREE(gCb,recBuf[curSn]->umHdr,sizeof(KwUmHdr));
          KW_FREE(gCb,recBuf[curSn],sizeof(KwUmRecBuf));
       } 
       curSn++;
   }
   rbCb->m.umUl.vrUr = 0;
   rbCb->m.umUl.vrUh = 0;
   rbCb->m.umUl.vrUx = 0;

   kwKwSap = gCb->u.ulCb->kwuUlSap + KW_UI_PDCP;

   /* Venki */
#ifndef KW_PDCP
   if (sendReEst)
   {
      KwUiKwuReEstCmpInd(&kwKwSap->pst, kwKwSap->suId, rlcId);
   }
#endif
   RETVALUE(ROK);
}

/**
 *
 * @brief 
 *
 *        Handler to extract the header from a PDU.
 *
 * @b Description: 
 *
 *        This function is used to extract the header of a PDU and store it along with the
 *        PDU buffer.The sequence number,framing info and LIs are extracted by this
 *        function.
 *            
 *  @param[in]  rbCb    RB control block
 *  @param[in]  pdu     PDU  
 *  @param[out] umHdr   UM Header to be extracted
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */

#ifdef ANSI
PUBLIC S16 kwUmmExtractHdr
(
KwCb   *gCb,
KwUlRbCb *rbCb,                   /* RB Control Block */
Buffer *pdu,                    /* PDU */
KwUmHdr **umHdr                 /* Extracted UM Header */
)
#else
PUBLIC S16 kwUmmExtractHdr(rbCb,pdu,umHdr)
KwCb     *gCb;
KwUlRbCb *rbCb;                   /* RB Control Block */
Buffer   *pdu;                    /* PDU */
KwUmHdr **umHdr;                /* Extracted UM Header */
#endif
{
   U8 e;                        /* Extension Bit */
   Data *dst = NULLP;           /* Destination Buffer */
   Data li[2];                  /* Data */
   U16 numLi;                   /* Number of LIs */
   KwUmHdr *hdr;                /* UM Header Pointer */
   S32     totalSz;             /* Sum of LIs */
   MsgLen  pduSz;               /* PDU size */
   MsgLen  tPduSz;              /* PDU size backup */
   S16      ret;                /* Return Value */

   TRC3(kwUmmExtractHdr)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_UL),
                  (gCb->init.prntBuf," kwUmmExtractHdr(rbCb,pdu,umHdr) \n"));
#endif
   numLi = 0;
   e = 0;
   dst = li;

   KW_ALLOC (gCb,*umHdr, sizeof(KwUmHdr));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( *umHdr == NULLP )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW216, (ErrVal) RFAILED,
            "KwUmHdr: umHdr allocation Failed.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
   
   hdr = *umHdr;
   SFndLenMsg(pdu,&pduSz);
   tPduSz = pduSz;
   totalSz = 0;
 
   if ( rbCb->m.umUl.snLen == 1)
   {
      ret = SRemPreMsg(dst,pdu);
#if (ERRCLASS & ERRCLS_DEBUG)
      if (ret != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf," SRemPreMsg Failed \n"));
#endif
         RETVALUE(RFAILED);
      }
#endif
      pduSz--;
      hdr->sn = (dst[0]) & 0x1F; 
      hdr->fi = (dst[0]) >> 6;
      e       = (dst[0]>>5) & 0x01;
   }
   else if ( rbCb->m.umUl.snLen == 2)
   {
      ret = SRemPreMsgMult(dst,2,pdu);
#if (ERRCLASS & ERRCLS_DEBUG)
      if (ret != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf," SRemPreMsgMult Failed \n"));
#endif
         RETVALUE(RFAILED);
      }
#endif
      pduSz -= 2;
   
      /* kw005.201 R9 Upgrade 3gpp spec 36.322 ver9.3.0 CR0082      *
       * Removed the "if" condition for checking the reserved field *
       * Added mask 0x03 for extracting the FI field.		    */

      hdr->fi = ( (dst[0] ) >> 3) & 0x03;
      e       = ( (dst[0] ) >> 2) & 0x01;
      hdr->sn = (  dst[0] & 0x03) << 8;
      hdr->sn  |= dst[1];
   }
   while (e && numLi < KW_MAX_LI && pdu)
   {
      ret = SRemPreMsgMult(dst,2,pdu);
#if (ERRCLASS & ERRCLS_DEBUG)
      if (ret != ROK)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf," SRemPreMsgMult Failed \n"));
#endif
         RETVALUE(RFAILED);
      }
#endif
      hdr->li[numLi] = ((dst[0]) & 0x7F) << 4;
      hdr->li[numLi] |= dst[1] >> 4;
      if (hdr->li[numLi] == 0)
      {
#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf," Received LI with 0 \n"));
#endif
         RETVALUE(RFAILED); 
      }
      totalSz += hdr->li[numLi];
      if ( pduSz <=  totalSz )
      {

#ifdef DEBUGP
         KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf," Corrupted PDU  \n"));
#endif
         RETVALUE(RFAILED); /* the situation where in the PDU size is something that does not match with the size in LIs*/
      }
      numLi++;
      pduSz -= 2;

      e = ((dst[0]) & 0x80) >> 7;
     
      if ( e && numLi < KW_MAX_LI)
      {
         U8 tmp = ((dst[1]) & 0x08) >> 3;
         hdr->li[numLi] = ( dst[1] & 0x07) << 8;
         if (e) 
         {
            ret = SRemPreMsg(dst,pdu);
#if (ERRCLASS & ERRCLS_DEBUG)
            if (ret != ROK)
            {
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf," SRemPreMsg Failed \n"));
#endif
               RETVALUE(RFAILED);
            }
#endif
            hdr->li[numLi] |= ( dst[0] );    /* The first byte lies in the first 8 bits.We want them in the last 8 bits */
            if (hdr->li[numLi] == 0)
            {
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                     (gCb->init.prntBuf," Received 0 for LI \n"));
#endif
               RETVALUE(RFAILED); 
            }
            totalSz += hdr->li[numLi];
            pduSz--;
            numLi++;

            if ( pduSz <  totalSz )
            {
               RETVALUE(RFAILED); /* the situation where in the PDU size is something that does not match with the size in LIs*/
            }
         }
         e = tmp;
      }
      else 
      {
         /* PDU was constructed with LIs that exceeded KW_MAX_LI */
         if (e)
            RETVALUE(RFAILED);
      }
   }
   if ( numLi <= KW_MAX_LI )
   {
      hdr->numLi = numLi;
   }
   else
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf," liCount exceeded the maximum count \n"));
#endif
      RETVALUE(RFAILED);
   }

   if ((totalSz +  rbCb->m.umUl.snLen) > tPduSz)
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
                  (gCb->init.prntBuf," Corrupted PDU \n"));
#endif
      RETVALUE(RFAILED);
   }
   
   RETVALUE(ROK); 
}

#ifdef ANSI
PUBLIC S16 kwUmmReOrdTmrExp
(
KwCb      *gCb,
KwUlRbCb  *rbCb                         /* RB Control Block */
)
#else
PUBLIC S16 kwUmmReOrdTmrExp(gCb,rbCb)
KwCb      *gCb;
KwUlRbCb  *rbCb;                        /* RB Control Block */
#endif
{
   KwSn vrUh;                         /* vrUh */
   KwSn *vrUr;                        /* vrUr */
   KwSn prevVrUr;                     /* prevVrUr */
   KwUmRecBuf **recBuf;               /* Um Reception Buffer */
   KwUmUl *umUl;                      /* UM Uplink structure */
   /* kw005.201 */
   U16 umReOrdWinSz;            /* UM ReOrder Window Size */
   U16 umRcpWinSz;              /* Reception Window Size */

   TRC3(kwUmmReOrdTmrExpiry)
#ifdef DEBUGP
    KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
                  (gCb->init.prntBuf,"  kwUmmReOrdTmrExpiry(rbCb) \n"));
#endif 
   umUl = &(rbCb->m.umUl);
   vrUh = umUl->vrUh;
   vrUr = &umUl->vrUr;
   prevVrUr = *vrUr;
   recBuf = umUl->recBuf;
   /* kw005.201 */
   umReOrdWinSz= rbCb->m.umUl.umWinSz;
   umRcpWinSz = umReOrdWinSz << 1; 

   KW_UM_FIND_NEXT_VRUR(umUl,umUl->vrUx, *vrUr);
   /* kw005.201 */
   while ( KW_UM_GET_VALUE(prevVrUr,vrUh,umReOrdWinSz,umRcpWinSz) < KW_UM_GET_VALUE(*vrUr,vrUh,umReOrdWinSz,umRcpWinSz) )
   {
      if ( recBuf[prevVrUr] != NULLP)
      {
         kwUmmReAssembleSdus(gCb,rbCb, recBuf[prevVrUr]);
         KW_FREE(gCb,recBuf[prevVrUr]->umHdr, sizeof(KwUmHdr));
         KW_FREE(gCb,recBuf[prevVrUr], sizeof(KwUmRecBuf));
      }
      /* kw005.201 */
      prevVrUr = (prevVrUr + 1)%umRcpWinSz;
   }
   /* kw005.201 */
   if ( KW_UM_GET_VALUE(vrUh,vrUh,umReOrdWinSz,umRcpWinSz) > KW_UM_GET_VALUE(*vrUr,vrUh,umReOrdWinSz,umRcpWinSz) )
   {
      kwStartTmr(gCb,(PTR)rbCb,KW_EVT_UMUL_REORD_TMR);
      umUl->vrUx = vrUh;
   }

   RETVALUE(ROK);
}
/********************************************************************30**
         End of file:     kw_umm_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:54 2014
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
/main/1      ---       vp   1. initial release.
/main/2      ---       nm   1. LTERLC Release 2.1
/main/3      kw002.201 vp   1. Patch for optimization,fixes for multi-region
                               and retransmission.
/main/4      kw003.201 vp   1. Fixes for re-segmentation, segement offset
                               value and optimization.
/main/5      kw005.201 rd   1. R9 Upgrade 3gpp spec 36.322 ver9.3.0 CR0082
               			       Removed the reserved field validation for UM
               		          10 bit SN header in function kwUmmExtractHdr
                            2. L2 Meas Code added for DL/UL ip throughput.
                       ap   3. Added missing condition in kwUmmProcessPdus
                            4. Updated for missing statistics calculation.
                            5. Added L2 Measurement feature.
                       rd   6. Bug related to dl ip throughput during 
                               segmentation is fixed.
*********************************************************************91*/
/*@}*/

