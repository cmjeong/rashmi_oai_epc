

/**********************************************************************

     Name:     LTE-RLC Layer 
  
     Type:     C file
  
     Desc:     Source code for RLC Utility Module
               This file contains following functions

                  --kwUtlSndToLi
                  --kwUtlRcvFrmLi
                  --kwUtlEmptySduQ
                  --kwUtlSndDStaRsp
                  --kwUtlSndDatInd 
                  --kwUtlShutDown
     File:     gp_utl.c

     Sid:      kw_utl_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:55 2014

     Prg:      vp 

**********************************************************************/
/** @file gp_utl.c
@brief RLC Utility Module 
*/


/*
 *      This software may be combined with the following TRILLIUM
 *      software:
 *
 *      part no.                      description
 *      --------    ----------------------------------------------
 *      1000241     LTE-MAC
 *      1000369     LTE-RRC
 */
/* header (.h) include files */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#include <sys/time.h>
#endif

#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm5.h"           /* common timer defines */
#include "cm_tkns.h"       /* common tokens defines */
#include "cm_mblk.h"       /* common memory allocation library defines */
#include "cm_llist.h"      /* common link list  defines  */
#include "cm_hash.h"       /* common hash list  defines */
#include "cm_lte.h"        /* common LTE defines */
#include "ckw.h"
#include "kwu.h"
#include "lkw.h"
#include "rgu.h"

#include "kw_env.h"        /* RLC environment options */
#include "kw.h"            /* RLC defines */
#include "kw_err.h"        /* Error defines */
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
#include "ckw.x"
#include "kwu.x"
#include "lkw.x"
#include "rgu.x"

#include "kw.x"
#include "kw_ul.x"



/**
 *
 * @brief 
 *
 *        Handler for receiving data for multiple logical channels from MAC.
 *
 * @b Description:
 *
 *        This function receives the data sent by MAC for one or more 
 *        logical channels.It calls the UMM or AMM functions to process
 *        the PDUs and send them to the uppper layer.  
 *
 *  @param[in] datIndInfo     Data Indication Information containing the PDU(s)
 *                            for one or more logical channels  
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 kwUtlRcvFrmLi
(
KwCb         *gCb,
KwDatIndInfo *datIndInfo                        /* Data Indication Information */
)
#else
PUBLIC S16 kwUtlRcvFrmLi(gCb,datIndInfo)
KwCb         *gCb;
KwDatIndInfo *datIndInfo;                       /* Data Indication Information */
#endif
{
   U8 count;                                    /* Loop Counter */
   KwPduInfo *pduInfo;                           /* PDU Information */
   KwUlRbCb    *rbCb;                             /* RB Control Block */
   KwUlUeCb     *ueCb;                            /* UE Control Block */
   KwUeKey    ueKey;                            /* UE Key */
   S16        ret;                              /* Return Value */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
   KwL2MeasUlThrpTimInfo *ulTimeInfo = NULLP;   /*kw005.201 Store timing info for*
                                                 *UL IP throughput measurement.  */
#endif
#endif

   TRC2(kwUtlRcvFrmLi)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwUtlRcvFrmLi(datIndInfo)\n"));
#endif
   ueKey.cellId = datIndInfo->cellId;
   ueKey.ueId   = datIndInfo->rnti;
   ueCb = NULLP;

   ret = kwDbmFetchUlUeCb(gCb,ueKey.ueId,ueKey.cellId,&(ueCb));

   if ( ret != ROK )
   {
      /* Fetch UeCb failed */
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW221, (ErrVal) RFAILED,
            "kwDbmFetchUeCb Failed.");
      RETVALUE(RFAILED);
   }

   for ( count = 0;count < datIndInfo->numLch; count++ )
   {
      rbCb = ueCb->lCh[datIndInfo->lchData[count].lcId - 1].ulRbCb;
      /* kw002.201 Removed allocation of pduInfo */ 
      pduInfo = &(datIndInfo->lchData[count].pdu); 

      if ( rbCb->mode == CM_LTE_MODE_UM )
      {
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
         /*kw005.201 Get ul timeinfo*/
         ulTimeInfo = &(datIndInfo->lchData[count].timeInfo);
         ret = kwUmmProcessPdus(gCb,rbCb,pduInfo,ulTimeInfo);
#else
         ret = kwUmmProcessPdus(gCb,rbCb,pduInfo);
#endif
#else
         ret = kwUmmProcessPdus(gCb,rbCb,pduInfo);
#endif
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ret != ROK )
            {
               KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW222, (ErrVal) RFAILED,
                       "kwUmmProcessPdus Failed.");
               RETVALUE(RFAILED);
             }
#endif /* ERRCLASS & ERRCLS_DEBUG */
      }
      else if (rbCb->mode == CM_LTE_MODE_AM )
      {
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
         /*kw005.201 Get ul timeinfo*/
         ulTimeInfo = &(datIndInfo->lchData[count].timeInfo);
         ret = kwAmmProcessPdus(gCb,rbCb,pduInfo,ulTimeInfo);
#else
         ret = kwAmmProcessPdus(gCb,rbCb,pduInfo);
#endif
#else
         ret = kwAmmProcessPdus(gCb,rbCb,pduInfo);
#endif
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ret != ROK )
            {
               KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW223, (ErrVal) RFAILED,
                       "kwAmmProcessPdus Failed.");
               RETVALUE(RFAILED);
             }
#endif /* ERRCLASS & ERRCLS_DEBUG */
      }
   }
   RETVALUE(ROK);
}

/**
 *
 * @brief 
 * 
 *        Handler for sending Data Indication to the upper layer. 
 * 
 * @b Description:
 *
 *        This function is used to send re-assembled SDU
 *        to the upper layer.
 *
 *  @param[in]  rbCb               RB Control Block 
 *  @param[in]  sdu                SDU to be freed
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 kwUtlSndDatInd
(
KwCb   *gCb,
KwUlRbCb *rbCb,                   /* RB Control Block */
Buffer *sdu                     /* SDU to be sent to PDCP*/
)
#else
PUBLIC S16 kwUtlSndDatInd(gCb,rbCb,sdu)
KwCb   *gCb;
KwUlRbCb *rbCb;                   /* RB Control Block */
Buffer *sdu;                    /* SDU to be sent to PDCP*/
#endif
{
#ifdef KW_PDCP
#else
   KwKwuSapCb *kwKwSap = NULLP;         /* KWU SAP Information */
   KwuDatIndInfo *datIndInfo = NULLP;   /* Data Indication Information */
#endif

   TRC3(kwUtlSndDatInd)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwUtlSndDatInd(rbCb,sdu)\n"));
#endif

#ifndef KW_PDCP
   KW_ALLOC(gCb,datIndInfo,sizeof(KwuDatIndInfo));

#if (ERRCLASS & ERRCLS_ADD_RES )
   if ( datIndInfo == NULLP  )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW225, (ErrVal) RFAILED,
                       "KW_ALLOC failed for datIndInfo .");
      KW_FREE_BUF(sdu);
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   KW_MEM_CPY(&(datIndInfo->rlcId),&(rbCb->rlcId),sizeof(CmLteRlcId));
#endif /* KW_PDCP */
   
   /* If trace flag is enabled send the trace indication */
   if(gCb->init.trc == TRUE)
   {
      /* Populate the trace params */
      kwLmmSendTrc(gCb,KWU_EVT_DAT_IND, sdu);
   }
#ifdef KW_PDCP
#else
   kwKwSap = gCb->u.ulCb->kwuUlSap + KW_UI_PDCP;

   KwUiKwuDatInd(&kwKwSap->pst, kwKwSap->suId, datIndInfo, sdu);
#endif   
   RETVALUE(ROK);
} /* kwUtlSndDatInd */


/** @details
 * This primitive Frees the UM/AM RbCb transmission Buffer, retransmission
 * Buffer and reciption Buffers
 *
 * @param [out]   rbCb     -  RB Control Block
 *
 * @return
 *          - ROK
 *          - RFAILED
 */
#ifdef ANSI
PUBLIC Void kwUtlFreeUlRbCb
(
KwCb              *gCb,
KwUlRbCb            *rbCb
)
#else
PUBLIC Void kwUtlFreeUlRbCb(gCb,rbCb)
KwCb              *gCb;
KwUlRbCb            *rbCb;
#endif
{
   KwSn              curSn = 0;
   KwSn              windSz = 0;
   KwUmRecBuf        **umRecBuf;
   KwAmRecBuf        **amRecBuf;
   KwSeg             *seg = NULLP;

   TRC2(kwUtlFreeUlRbCb)
#ifdef DEBUGP
   KWDBGP(gCb,
          (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF | KW_DBGMASK_DL | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwUtlFreeRbCb(rbCb)\n")); 
#endif
   if ( rbCb->mode == CM_LTE_MODE_UM )
   {
      windSz  = rbCb->m.umUl.umWinSz << 1;

      umRecBuf =  rbCb->m.umUl.recBuf;

      /* Venki */
      if(TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_UMUL_REORD_TMR))
      {
          kwStopTmr(gCb,(PTR)rbCb,KW_EVT_UMUL_REORD_TMR);
      }
      while ( curSn < windSz )
      {
         if ( umRecBuf[curSn] != NULLP )
         {
            if (umRecBuf[curSn] && (umRecBuf[curSn]->pdu != NULLP))
            {
               KW_FREE_BUF(umRecBuf[curSn]->pdu);
               KW_FREE(gCb,umRecBuf[curSn]->umHdr, sizeof(KwUmHdr));
               KW_FREE(gCb,umRecBuf[curSn],sizeof(KwUmRecBuf));
            }
         }
         curSn++;
      }
         KW_FREE(gCb,rbCb->m.umUl.recBuf, (windSz ) *
               sizeof(KwUmRecBuf*));
   }
   else if (rbCb->mode == CM_LTE_MODE_AM)
   {
      windSz  = KW_AM_WIN_SZ * 2;
      amRecBuf =  rbCb->m.amUl.recBuf;

      /* Venki */
      if(TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_AMUL_REORD_TMR))
      {
            kwStopTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_REORD_TMR);
      }
      if(TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_AMUL_STA_PROH_TMR))
      {
            kwStopTmr(gCb,(PTR)rbCb, KW_EVT_AMUL_STA_PROH_TMR);
      }

      while ( curSn < windSz )
      {
         if ( amRecBuf[curSn] != NULLP )
         {
            if (amRecBuf[curSn] &&  (amRecBuf[curSn]->pdu != NULLP))
               KW_FREE_BUF(amRecBuf[curSn]->pdu);

            KW_LLIST_FIRST_SEG(amRecBuf[curSn]->segLst, seg);                     
            while (seg)
            {
               KW_FREE_BUF(seg->seg); 
               cmLListDelFrm(&(amRecBuf[curSn]->segLst),&(seg->lstEnt));
               KW_FREE(gCb,seg, sizeof(KwSeg));
               KW_LLIST_FIRST_SEG(amRecBuf[curSn]->segLst, seg);
            }
            KW_FREE(gCb,amRecBuf[curSn],sizeof(KwAmRecBuf));
         }
         curSn++;
      }
      KW_FREE(gCb,rbCb->m.amUl.recBuf, (windSz)* sizeof(KwAmRecBuf*));
   }

   RETVOID;
} /* kwUtlFreeRbCb */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC

/**
 *
 * @brief Handler for L2 Measurement timer expiry.
 *
 *
 * @b Description
 *        This function is called when the l2 measurement timer expires. 
 *        This function sends a consolidates the mesaurements taken during
 *        this time and sends the confirm .
 *
 *  @param[in] measEvtCb    Measurement Event Control Block.
 *
 *
 *  @return  S16
 *      -# ROK
 */

#ifdef ANSI
PUBLIC S16 kwUtlHdlL2TmrExp
(
KwL2MeasEvtCb *measEvtCb
)
#else
PUBLIC S16 kwUtlHdlL2TmrExp(measEvtCb)
KwL2MeasEvtCb *measEvtCb;
#endif
{
   U16             qciIdx;
   KwL2MeasCb     *measCb;

   TRC3(kwUtlHdlL2TmrExp)

   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_DETAIL), 
          (gCb->init.prntBuf, "kwUtlHdlL2TmrExp(transId(%ld))\n", measEvtCb->transId));

   /* Clean up the RB data structures */
   if((measEvtCb->measCb.measType & LKW_L2MEAS_ACT_UE) &&
      (measEvtCb->measCb.numSamples))
   {
      measCb = &measEvtCb->measCb;

      for(qciIdx = 0; qciIdx < measCb->numQci;qciIdx++)
      {
         measCb->measData[measCb->qci[qciIdx]].actUe.numActvUe   +=   
                     kwCb.kwL2Cb.numActUe[measCb->qci[qciIdx]];
         measCb->measData[measCb->qci[qciIdx]].actUe.sampOc++;
      }
      measEvtCb->measCb.numSamples--;
      kwStartTmr((PTR)measEvtCb, KW_EVT_L2_TMR); 
      RETVALUE(ROK);
   }

   kwUtlSndL2MeasCfm(measEvtCb);

   RETVALUE(ROK);
} /* kwUtlHdlL2TmrExp */

/**
 *
 * @brief Handler for Sending L2 Measurement confirm.
 *
 *
 * @b Description
 *        This function sends a consolidates the mesaurements taken during
 *        this time and sends the confirm .
 *
 *  @param[in] measEvtCb    Measurement Event Control Block.
 *
 *
 *  @return  S16
 *      -# ROK
 */

#ifdef ANSI
PUBLIC S16 kwUtlSndL2MeasCfm
(
KwL2MeasEvtCb *measEvtCb
)
#else
PUBLIC S16 kwUtlSndL2MeasCfm(measEvtCb)
KwL2MeasEvtCb *measEvtCb;
#endif
{
   U16                     seqNum;
   U32                     qciIdx;
   KwL2MeasCb              *measCb;
   KwL2MeasCfmEvt          measCfmEvt;
   KwRbCb                  *kwRbCb;
   U32                     posPkts;
   U32                     dLoss;
#ifdef LTE_RLC_R9
   U32                     dlDataVol;
   U32                     dlTime;
   U32                     ulDataVol;
   U32                     ulTime;
   RguL2MUlThrpMeasReqInfo *ulThrpMeasReqInfo = NULLP;
   KwRguSapCb              *rguSap = &(kwCb.rguSap);
   U8                      lcIdIdx;
#endif

   TRC3(kwUtlSndL2MeasCfm)

   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_DETAIL), 
          (gCb->init.prntBuf, "kwUtlSndL2MeasCfm(transId(%ld))\n", measEvtCb->transId));

   
   /* # Clean up the RB data structures */
   measCb = &measEvtCb->measCb;
   seqNum = 0;

   for(qciIdx = 0; qciIdx < measCb->numQci; qciIdx++)
   {
      while (cmHashListFind(&(kwCb.kwL2Cb.qciHlCp), (U8 *) &measCb->qci[qciIdx], 
               sizeof(measCb->qci[qciIdx]),  seqNum++, (PTR *)&kwRbCb) == ROK)
      {
         if((kwRbCb->rbL2Cb.measOn & measCb->measType) &&
            (kwRbCb->rlcId.rbType == CM_LTE_DRB))
         {
            kwRbCb->rbL2Cb.measOn &= ~measCb->measType;
         }
      }
      seqNum = 0;
      kwCb.kwL2Cb.measOn[measCb->qci[qciIdx]] &= ~measCb->measType;
   }

   /*Send notification to MAC to stop Ul Ip measurement for given LChs*/
#ifdef LTE_RLC_R9
   if(measCb->measType & LKW_L2MEAS_UL_IP)
   {
      /*Send req to MAC to stop taking timings for these LChs*/
      KW_ALLOC(ulThrpMeasReqInfo, sizeof(RguL2MUlThrpMeasReqInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
      if(NULLP == ulThrpMeasReqInfo)
      {
         KWLOGERROR(ERRCLS_ADD_RES, EKWXXX, (ErrVal) RFAILED,
            "kwUtlSndL2MeasCfm: KW_ALLOC Failed for ulThrpMeasReqInfo.");
         RETVALUE(RFAILED);
      }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
      ulThrpMeasReqInfo->cellId = measCb->cellId;
      ulThrpMeasReqInfo->rnti = measCb->ueId;
      ulThrpMeasReqInfo->numLcId = measCb->numLcId;
      ulThrpMeasReqInfo->enbMeas = FALSE;
      for(lcIdIdx = 0; lcIdIdx < measCb->numLcId; lcIdIdx++)
      {
         ulThrpMeasReqInfo->lcId[lcIdIdx] = measCb->lcId[lcIdIdx];
      }
      /*Send ulThrpMeasReqInfo to MAC*/
      KwLiRguL2MUlThrpMeasReq(&rguSap->pst,rguSap->spId, ulThrpMeasReqInfo);
   }
#endif /* LTE_RLC_R9 */
   
   cmMemset((U8*)&measCfmEvt, 0, sizeof(KwL2MeasCfmEvt));
   measCfmEvt.transId = measEvtCb->transId;
   measCfmEvt.numCfm = 0;

   measCb = &measEvtCb->measCb;
   measCfmEvt.measType = measCb->measType;
   measCfmEvt.status.status = LCM_PRIM_OK;
   measCfmEvt.status.reason = LCM_REASON_NOT_APPL;

   if((measCb->measType & LKW_L2MEAS_DL_IP) ||
      (measCb->measType & LKW_L2MEAS_UL_IP) )
   {
#ifdef LTE_RLC_R9
      measCfmEvt.ueId = measCb->ueId;
      measCfmEvt.cellId = measCb->cellId;
      for(qciIdx = 0; qciIdx < measCb->numQci; qciIdx++)
      {
         measCfmEvt.measCfm[measCfmEvt.numCfm].qci = measCb->qci[qciIdx];
         if(measCb->measType & LKW_L2MEAS_DL_IP)
         {
            dlDataVol = measCb->measData[measCb->qci[qciIdx]].dlIpThruput.volSummation;
            dlTime = measCb->measData[measCb->qci[qciIdx]].dlIpThruput.timeSummation;
            if(0 == dlTime)
            {
               measCfmEvt.measCfm[measCfmEvt.numCfm].val.ipThrput.dlIpThPut = 0;
            }
            else
            {
               measCfmEvt.measCfm[measCfmEvt.numCfm].val.ipThrput.dlIpThPut  =
               (dlDataVol / dlTime);
            }
         }
         if(measCb->measType & LKW_L2MEAS_UL_IP)
         {
            ulDataVol = measCb->measData[measCb->qci[qciIdx]].ulIpThruput.volSummation;
            ulTime = measCb->measData[measCb->qci[qciIdx]].ulIpThruput.timeSummation;
            if(0 == ulTime)
            {
               measCfmEvt.measCfm[measCfmEvt.numCfm].val.ipThrput.ulIpThPut = 0;
            }
            else
            {
               measCfmEvt.measCfm[measCfmEvt.numCfm].val.ipThrput.ulIpThPut  =
               (ulDataVol / ulTime);
            }
         }
         measCfmEvt.numCfm++;
      }
#else
      KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR),
          (gCb->init.prntBuf, "kwUtlSndL2MeasCfm:LTE_RLC_R9 is OFF but IP measurement bit is ON\n"));
#endif
   }
   else
   {
      for(qciIdx = 0; qciIdx < measCb->numQci; qciIdx++)
      {
         measCfmEvt.measCfm[measCfmEvt.numCfm].qci = measCb->qci[qciIdx];
         if(measCb->measType & LKW_L2MEAS_UU_LOSS)
         {
            dLoss = measCb->measData[measCb->qci[qciIdx]].uuLoss.dLoss;
            posPkts = measCb->measData[measCb->qci[qciIdx]].uuLoss.posPkts;
            if(((posPkts + dLoss) != 0))
            {
               measCfmEvt.measCfm[measCfmEvt.numCfm].val.nonIpThrput.uuLoss  =
               ((dLoss  * 1000000) / (posPkts + dLoss));
            }
         }
         if(measCb->measType & LKW_L2MEAS_ACT_UE)
         { 
            measCfmEvt.measCfm[measCfmEvt.numCfm].val.nonIpThrput.numActUe  =
            measCb->measData[measCb->qci[qciIdx]].actUe.numActvUe /
            measCb->measData[measCb->qci[qciIdx]].actUe.sampOc;
         }
         measCfmEvt.numCfm++;
      }
   }
   kwCb.kwL2Cb.kwL2EvtCb[measEvtCb->cbIdx] = NULLP;
   kwCb.kwL2Cb.kwNumMeas--;
   KW_FREE(measEvtCb, sizeof(KwL2MeasEvtCb));
   KwMiLkwL2MeasCfm(&kwCb.genCfg.lmPst, &measCfmEvt);
   RETVALUE(ROK);
} /* kwUtlSndL2MeasCfm */
/**
 *
 * @brief Handler for Sending Negative confirm .
 *
 *
  @b Description
 *        This function is called when the l2 measurement cannot be started
 *        This function sends  negative confirm for all the requests
 *
 *  @param[in] measReqEvt    Measurement Req Structure
 *
 *
 *  @return  S16
 *      -# ROK
 */

#ifdef ANSI
PUBLIC S16 kwUtlSndL2MeasNCfm
(
KwL2MeasReqEvt *measReqEvt,
KwL2MeasCfmEvt *measCfmEvt
)
#else
PUBLIC S16 kwUtlSndL2MeasNCfm(measReqEvt, measCfmEvt)
KwL2MeasReqEvt *measReqEvt;
KwL2MeasCfmEvt *measCfmEvt;
#endif
{
   TRC3(kwUtlSndL2MeasNCfm)

   KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_DETAIL), 
          (gCb->init.prntBuf, "kwUtlSndL2MeasNCfm(transId(%ld))\n", measReqEvt->transId));

   KwMiLkwL2MeasCfm(&kwCb.genCfg.lmPst, measCfmEvt);
   RETVALUE(ROK);
} /* kwUtlSndL2MeasNCfm */

/**
 * @brief  Validates the measurement request parameters. 
 *
 * @details
 *
 *     Function :kwUtlValidateL2Meas 
 *
 *  @param[in] KwL2MeasReqEvt *measReqEvt
 *  @param[out] KwL2MeasCfmEvt * measCfmEvt
 **/
#ifdef LTE_RLC_R9
#ifdef ANSI
PUBLIC S16 kwUtlValidateL2Meas
(
KwL2MeasReqEvt *measReqEvt,
KwL2MeasCfmEvt *measCfmEvt,
CmLteLcId      *lChId,
U8             *numLCh
)
#else
PUBLIC S16 kwUtlValidateL2Meas(measReqEvt, measCfmEvt, lChId, numLCh)
KwL2MeasReqEvt *measReqEvt;
KwL2MeasCfmEvt *measCfmEvt;
CmLteLcId      *lChId;
U8             *numLCh;
#endif
#else
#ifdef ANSI
PUBLIC S16 kwUtlValidateL2Meas
(
KwL2MeasReqEvt *measReqEvt,
KwL2MeasCfmEvt * measCfmEvt
)
#else
PUBLIC S16 kwUtlValidateL2Meas(measReqEvt, measCfmEvt)
KwL2MeasReqEvt *measReqEvt;
KwL2MeasCfmEvt *measCfmEvt;
#endif
#endif /* LTE_RLC_R9 */
{
   U8      measType;
   S16     ret;
   U8      qciIdx;
   U8      qci;
   U8      idx;
   U8      *qciVal;
   U8      numQci;
   KwRbCb  *rbCb;
#ifdef LTE_RLC_R9
   KwUeCb     *ueCb;
   RbCb       **rbCbLst;
   U8         rbIdx;
   U8         lsbNibble = 0;
   U8         msbNibble = 0;
#endif /* LTE_RLC_R9 */


   TRC3(kwUtlValidateL2Meas)
   
   idx = 0;
   rbCb = NULLP;
   ret = ROK;
   measType = measReqEvt->measReq.measType;
   /* Check for the range of measType */
   /* LKW_L2MEAS_DL_IP+ LKW_L2MEAS_UL_IP = 0x0030*/
   if((measType == 0x00) ||
       measType > 0x30)
   {
      measCfmEvt->numCfm = 0;
      measCfmEvt->transId = measReqEvt->transId;
      measCfmEvt->measType = measType;
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_INVALID_MEASTYPE;
      RETVALUE(RFAILED);
   }
#ifndef LTE_RLC_R9
   /*If LTE_RLC_R9 is not defined, then DL/UL ip throughput can not *
    *be sent in measurement request.                                */
   if((measType & LKW_L2MEAS_DL_IP ) ||
      (measType & LKW_L2MEAS_UL_IP))
   {
      measCfmEvt->numCfm = 0;
      measCfmEvt->transId = measReqEvt->transId;
      measCfmEvt->measType = measType;
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_INVALID_MEASTYPE;
      RETVALUE(RFAILED);
   }
#else
   /*If LTE_RLC_R9 is defined, then user can either request for Active UE,*
    *Dl delay, Dl discard, Uu Loss OR Dl ip throughput, Ul ip throughput. */
   lsbNibble = measType & 0x0F;
   msbNibble = measType & 0xF0;

   if( (lsbNibble != 0) && (msbNibble != 0) )
   {
      measCfmEvt->numCfm = 0;
      measCfmEvt->transId = measReqEvt->transId;
      measCfmEvt->measType = measType;
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_INVALID_MEASTYPE;
      RETVALUE(RFAILED);
   }
#endif
   /* Check for total maximum number of Measurement Control Block */
   if(kwCb.kwL2Cb.kwNumMeas >= LKW_MAX_L2MEAS )
   {
      measCfmEvt->numCfm = 0;
      measCfmEvt->transId = measReqEvt->transId;
      measCfmEvt->measType = measType;
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_EXCEED_NUMMEAS;
      RETVALUE(RFAILED);
   }
#ifdef LTE_RLC_R9
   if(((measType & LKW_L2MEAS_DL_IP) ||
       (measType & LKW_L2MEAS_UL_IP)))
   {
      /* Check for number of QCIs in the measurement request */
      if((measReqEvt->measReq.val.ipThMeas.numQci > LKW_MAX_QCI) ||
         (measReqEvt->measReq.val.ipThMeas.numQci == 0))
      {
         measCfmEvt->numCfm = 0;
         measCfmEvt->transId = measReqEvt->transId;
         measCfmEvt->measType = measType;
         measCfmEvt->status.status = LCM_PRIM_NOK;
         measCfmEvt->status.reason = LKW_CAUSE_INVALID_NUMQCI;
         measCfmEvt->ueId = measReqEvt->measReq.val.ipThMeas.ueId;
         measCfmEvt->cellId = measReqEvt->measReq.val.ipThMeas.cellId;
         RETVALUE(RFAILED);
      }
   }
   else if((measReqEvt->measReq.val.nonIpThMeas.numQci > LKW_MAX_QCI) ||
           (measReqEvt->measReq.val.nonIpThMeas.numQci == 0))
   {
      measCfmEvt->numCfm = 0;
      measCfmEvt->transId = measReqEvt->transId;
      measCfmEvt->measType = measType;
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_INVALID_NUMQCI;
      RETVALUE(RFAILED);
   }
#else
   if((measReqEvt->measReq.val.nonIpThMeas.numQci > LKW_MAX_QCI) ||
       (measReqEvt->measReq.val.nonIpThMeas.numQci == 0))
   {
      measCfmEvt->numCfm = 0;
      measCfmEvt->transId = measReqEvt->transId;
      measCfmEvt->measType = measType;
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_INVALID_NUMQCI;
      RETVALUE(RFAILED);
   }
#endif
   /* Check that number of samples should be a non-zero value */
   if(((measType & LKW_L2MEAS_ACT_UE) &&
      (measReqEvt->measReq.val.nonIpThMeas.numSamples == 0)))
   {
      measCfmEvt->numCfm = 0;
      measCfmEvt->transId = measReqEvt->transId;
      measCfmEvt->measType = measType;
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_ZERO_NUMSAM;
      RETVALUE(RFAILED);
   }
   /* Check that measurement period  should be completely divisible *
    * number of sample.                                             */
   if(((measType & LKW_L2MEAS_ACT_UE) &&
      ((measReqEvt->measPeriod % 
        measReqEvt->measReq.val.nonIpThMeas.numSamples) != 0)))
   {
      measCfmEvt->numCfm = 0;
      measCfmEvt->transId = measReqEvt->transId;
      measCfmEvt->measType = measType;
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_INVALID_NUMSAM;
      RETVALUE(RFAILED);
   }
#ifdef LTE_RLC_R9
   if(((measType & LKW_L2MEAS_DL_IP) ||
       (measType & LKW_L2MEAS_UL_IP)))
   {
      /* Check whether UE is valid or not */
      if (kwDbmFetchUeCb(measReqEvt->measReq.val.ipThMeas.ueId, 
                         measReqEvt->measReq.val.ipThMeas.cellId, &ueCb) != ROK)
      {
#ifdef DEBUGP
         KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR), (gCb->init.prntBuf,
                  "kwUtlValidateL2Meas: kwDbmFetchUeCb Failed.\n"));
#endif
         measCfmEvt->numCfm  = 0;
         measCfmEvt->transId = measReqEvt->transId;
         measCfmEvt->measType = measType;
         measCfmEvt->status.status = LCM_PRIM_NOK;
         measCfmEvt->status.reason = LKW_CAUSE_INVALID_UE;
         measCfmEvt->ueId = measReqEvt->measReq.val.ipThMeas.ueId;
         measCfmEvt->cellId = measReqEvt->measReq.val.ipThMeas.cellId;
         RETVALUE(RFAILED);
      }
      numQci = measReqEvt->measReq.val.ipThMeas.numQci;
      qciVal = measReqEvt->measReq.val.ipThMeas.qci;
      rbCbLst = ueCb->drbCb;
   }
   else
#endif
   {
      numQci = measReqEvt->measReq.val.nonIpThMeas.numQci;
      qciVal = measReqEvt->measReq.val.nonIpThMeas.qci;
   }
   /* Check whether qci is configured or not */
   for(qciIdx = 0; qciIdx < numQci; qciIdx++)
   {
      qci = qciVal[qciIdx];
      ret = cmHashListFind(&(kwCb.kwL2Cb.qciHlCp), 
            (U8 *)&qci, (U16)sizeof(qci), 0, (PTR *)&rbCb);
      if(ret != ROK)
      {
         measCfmEvt->measCfm[measCfmEvt->numCfm].qci = qci;
         measCfmEvt->numCfm++;
      }
   }
   if(measCfmEvt->numCfm > 0)
   {
      measCfmEvt->status.status = LCM_PRIM_NOK;
      measCfmEvt->status.reason = LKW_CAUSE_INVALID_QCI;
      measCfmEvt->measType = measType;
      measCfmEvt->transId = measReqEvt->transId;
#ifdef LTE_RLC_R9
     if((measType & LKW_L2MEAS_DL_IP) ||
        (measType & LKW_L2MEAS_UL_IP))
     {
        measCfmEvt->ueId = measReqEvt->measReq.val.ipThMeas.ueId;
        measCfmEvt->cellId = measReqEvt->measReq.val.ipThMeas.cellId;
     }
#endif
      RETVALUE(RFAILED);
   }
#ifdef LTE_RLC_R9
   if((measType & LKW_L2MEAS_DL_IP) ||
      (measType & LKW_L2MEAS_UL_IP))
   {
      for(qciIdx = 0; qciIdx < numQci; qciIdx++)
      {
         qci = qciVal[qciIdx];
         for(rbIdx = 0; rbIdx < KW_MAX_DRB_PER_UE; rbIdx++)
         {
            rbCb = &rbCbLst[rbIdx]->kwRbCb;
            if(rbCb)  
            {
               if((rbCb->qci == qci) && 
                 (rbCb->rbL2Cb.measOn & measType))
               {
                  /* measurement is already ongoing */
                  measCfmEvt->status.status = LCM_PRIM_NOK;
                  measCfmEvt->status.reason = LKW_CAUSE_MEAS_ALREADY_ENA;
                  measCfmEvt->measCfm[measCfmEvt->numCfm].qci = qci;
                  measCfmEvt->measType = measType;
                  measCfmEvt->ueId = measReqEvt->measReq.val.ipThMeas.ueId;
                  measCfmEvt->cellId = measReqEvt->measReq.val.ipThMeas.cellId;
                  measCfmEvt->numCfm++;
                  break;
               }
               /*This lChId calculation is for sending the L2MUlThroughput *
                *Measurement Request to MAC only during ul ip measurement. */
               if((measType & LKW_L2MEAS_UL_IP) && (rbCb->qci == qci))
               {
                  switch(rbCb->mode)
                  {
                     case CM_LTE_MODE_AM:
                     {
                        /*In AM, lch idx 1 is for UL logical channel*/
                        lChId[(*numLCh)++] = rbCb->lch[1].lChId;
                        break;
                     }
                     case CM_LTE_MODE_UM:
                     case CM_LTE_MODE_TM:
                     {
                        lChId[(*numLCh)++] = rbCb->lch[0].lChId;
                        break;
                     }
                  } /* Switch ends */
               } /* if((measType & LKW_L2MEAS_UL_IP) && (rbCb->qci == qci)) ends */
            } /* if(rbCb) ends */
         } /* for(rbIdx) ends */
      } /* for(qciIdx) ends */
   }
   else
#endif
   {
      for(qciIdx = 0; qciIdx < numQci; qciIdx++)
      {
         if(kwCb.kwL2Cb.measOn[qci] & measReqEvt->measReq.measType)
         {
            /* measurement is already ongoing */
            measCfmEvt->status.status = LCM_PRIM_NOK;
            measCfmEvt->status.reason = LKW_CAUSE_MEAS_ALREADY_ENA;
            measCfmEvt->measCfm[measCfmEvt->numCfm].qci = qci;
            measCfmEvt->measType = measType;
            measCfmEvt->numCfm++;
         }
      }
   }
   if(measCfmEvt->numCfm > 0)
   {
      measCfmEvt->transId = measReqEvt->transId;
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* kwUtlValidateL2Meas */



/**
 *
 * @brief Handler for Processing harq status indication
 *
 *
 * @b Description
 *        This function is called when the MAC sends a harq ind Mesage.
 *        This is used only for UuLoss and Dl Delay and DL Ipthoughput
 *        L2 Measurements.
 *
 *  @param[in] 
 *
 *
 *  @return  S16
 *      -# ROK
 */

#ifdef ANSI
PUBLIC S16 kwUtlProcHarqInd
(
RguHarqStatusInd *staInd,
KwUeCb           *ueCb,
U8               tbIdx
)
#else
PUBLIC S16 kwUtlProcHarqInd(staInd, ueCb, tbIdx)
RguHarqStatusInd *staInd;
KwUeCb           *ueCb;
U8               tbIdx;
#endif
{
   U8            tbSnIdx, sduIdx, snIdx1, snIdx2;
   KwRbCb       *kwRbCb;           /* KW Control Block */
   KwTbSnMap    *tbSnMap;          /* Tb SnMap                         */
   KwSnSduMap   *snSduMap;         /* List of SDUs that the SN maps to */
   KwSduSnMap   *sduSnMap;         /* List of SN that the SDU is split into */
#ifndef KW_PDCP
   KwuDatAckInfo *datAckInfo;      /* Data ack info */
   KwKwuSapCb *kwuSap = NULLP;    /* KWU SAP Information */
#endif
#ifdef LTE_RLC_R9
   /*kw005.201 Code added for DL IP thruput measurement*/
   EpcTime       t1;		   /* Holds time stamp T1 */
   KwL2MeasIpThruput *l2MeasIpThruput = NULLP;
#endif
   TRC3(kwUtlProcHarqInd)

   if(staInd->rguSnMapInfo[tbIdx] == NULLP)
   {
      RETVALUE(ROK);
   }
   if(cmHashListFind(&(kwCb.kwL2Cb.tbHlCp), (U8 *) &staInd->rguSnMapInfo[tbIdx]->tbId, 
                  sizeof(staInd->rguSnMapInfo[tbIdx]->tbId),  0, (PTR *)&tbSnMap) != ROK)
   {
      RETVALUE(ROK);
   }

   for(tbSnIdx = 0; tbSnIdx < tbSnMap->numSn; tbSnIdx++)
   {
      snSduMap = &tbSnMap->snSduMap[tbSnIdx];
      if((kwRbCb = ueCb->lCh[snSduMap->lChId - 1].dlRbCb) == NULLP)
      {
            continue;
      }
      for(sduIdx = 0; sduIdx < snSduMap->numSdu; sduIdx++)
      {
         sduSnMap = NULLP;
         sduSnMap  = snSduMap->sduList[sduIdx];
         if(staInd->status[tbIdx] == FALSE) /* If status is HARQ-NACK */
         {
            if(sduSnMap)
            {
               /* if we have not already marked this SDU as failed, we do so now */
               sduSnMap->failMarked = TRUE;
               if(kwRbCb->rbL2Cb.measOn & LKW_L2MEAS_UU_LOSS)
               {
                  kwRbCb->rbL2Cb.l2Sts[KW_L2MEAS_UU_LOSS]->uuLoss.dLoss++;
               }
               sduSnMap->rspRcvd++;
            }
         }
         else /* if status == TRUE */
         {
            if(sduSnMap)
            {
               sduSnMap->rspRcvd++;
               /* If the SDU has been fully sent and also marked as failure, remove it */
               if(!sduSnMap->failMarked)
               {
                  snIdx2 = 0;
                  for(snIdx1 = 0; snIdx1 < sduSnMap->numSn; snIdx1++)
                  {
                     for(snIdx2 = 0; snIdx2 < RGU_MAX_PDU; snIdx2++)
                     {
                        if(sduSnMap->snList[snIdx1] == 
                           staInd->rguSnMapInfo[tbIdx]->lchMap[tbSnIdx].snList[snIdx2])
                        {
                            sduSnMap->harqAck++;
                            break;
                        }
                     }
                  }
                  if((sduSnMap->fullySent == TRUE) && 
                     (sduSnMap->harqAck == sduSnMap->numSn))
                  {
                     /* Update total number positively acknowldged packets */

                     if(kwRbCb->rbL2Cb.measOn & LKW_L2MEAS_UU_LOSS)
                     {
                        kwRbCb->rbL2Cb.l2Sts[KW_L2MEAS_UU_LOSS]->uuLoss.posPkts++;
                     }
                     /* Send the data Ack indication to pdcp */
#ifndef KW_PDCP
                     if(kwRbCb->rbL2Cb.measOn & LKW_L2MEAS_DL_DELAY)
                     {
                        kwuSap = kwCb.kwuSap + KW_UI_PDCP;
                        KW_ALLOC(datAckInfo, sizeof(KwuDatAckInfo));
#if (ERRCLASS & ERRCLS_ADD_RES )
                        if (datAckInfo == NULLP  )
                        {
                           KWLOGERROR(ERRCLS_ADD_RES, EKW225, (ErrVal) RFAILED,
                                "KW_ALLOC failed for datAckInfo .");
                           RETVALUE(RFAILED);
                        }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
                        KW_MEM_CPY(&(datAckInfo->rlcId),&(kwRbCb->rlcId),
                               sizeof(CmLteRlcId));
                        datAckInfo->sduId = sduSnMap->sduId;
                        KwUiKwuDatAckInd(&kwuSap->pst, kwuSap->suId, datAckInfo);
                     }/* end of if DL_DELAY */
#endif
                  }
               }/* end of else */
            }/* end of if(sduSnMap) */
         }/* end of else */
         /* Delete this sduSnMap entry when response is received for all the request */
         if((sduSnMap->rspRcvd == sduSnMap->reqSent) &&
            (sduSnMap->fullySent == TRUE))
         {
            cmLListDelFrm(&kwRbCb->sduSnMapQ, &sduSnMap->lstEnt);
            KW_FREE(sduSnMap, sizeof(KwSduSnMap));
         }
      }/* End of for */

#ifdef LTE_RLC_R9
      /*If burst is splitted, it means that the corresponding data volume was*
       *measured and count was incrementd during Tx.                         */
      if(snSduMap->isBurstSplitted)
      {
         /*Check for Ack/Nack*/
         if(TRUE == staInd->status[tbIdx])  /*If status is HARQ-ACK*/
         {
            l2MeasIpThruput = &kwRbCb->l2MeasIpThruput;
            if(l2MeasIpThruput->count > 0)
            {
               /*Decrement the count since one ACK has been received from MAC*/
               l2MeasIpThruput->count--;

               /*Wait for the burst to get completed for calculating the throughput*/
               if( (0 == l2MeasIpThruput->count) && 
                 (KW_DL_IPTHRU_BURST_COMPLETED == l2MeasIpThruput->dlIpThrputSt) )
               {
                  /*Take T1 time stamp.*/
                  SGetEpcTime(&t1);
                  
                  /*Update the l2Sts structure for calculating throughput*/
                  kwRbCb->rbL2Cb.l2Sts[KW_L2MEAS_DL_IP]->dlIpThruput.volSummation
                  += l2MeasIpThruput->dataVol;
                  kwRbCb->rbL2Cb.l2Sts[KW_L2MEAS_DL_IP]->dlIpThruput.timeSummation
                  += t1 - l2MeasIpThruput->timeT2;

                  /*Reset the IP throughput related parameters. Now next burst*
                   *can be taken up if it is splitting across TTIs.           */
                  kwUtlResetKwRbL2Meas(kwRbCb);
               }

               /*Get the temporary T1 time stamp if the burst is still continuing*
                *and it has been ACK-ed till the point it has been sent on air.  */
               if((0 == l2MeasIpThruput->count) && 
                 ( (KW_DL_IPTHRU_BURST_STARTED == l2MeasIpThruput->dlIpThrputSt) || 
                 (KW_DL_IPTHRU_BURST_CONTINUE == l2MeasIpThruput->dlIpThrputSt) ) )
               {
                  /*Take temporary T1 time stamp.*/
                  SGetEpcTime(&t1);

                  l2MeasIpThruput->tempTimeT1 = t1;
               }
            }
            else
            {
#ifdef DEBUGP
               KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_ERROR | KW_DBGMASK_UL),
               (gCb->init.prntBuf, "kwUtlProcHarqInd: Count can not be zero if burst is split across TTI\n"));
#endif      
            } 
         } /*End of if(ACK == staInd->status[tbIdx])*/
         else
         {
#ifdef DEBUGP
            KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
            (gCb->init.prntBuf, "kwUtlProcHarqInd: Harq status is NACK for this burst\n"));
#endif      
         }
      } /*End of if(snSduMap->isBurstSplitted)*/
      else
      {
#ifdef DEBUGP
         KWDBGP((KW_DBGMASK_DUT | KW_DBGMASK_DETAIL | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwUtlProcHarqInd: Burst is not split across TTI\n"));
#endif      
      }
#endif /* LTE_RLC_R9 */
   }/* End of  for */
   
   /* Delete entry from hash list */
   cmHashListDelete(&(kwCb.kwL2Cb.tbHlCp), (PTR)tbSnMap);
   KW_FREE(tbSnMap,sizeof(KwTbSnMap));  

   KW_FREE(staInd->rguSnMapInfo[tbIdx],sizeof(RguSnMapInfo));  

   RETVALUE(ROK);
}/* end of  kwUtlProcHarqInd */ 


#ifdef LTE_RLC_R9
/**
 *
 * @brief Function for reseting the KwRbCb members wrt DL IP throughput
 *
 *
 * @b Description
 *        This function is called when dlIpThrputState becomes RESET.
 *
 *  @param[in] 
 *
 *
 *  @return  Void
 * 
 */
#ifdef ANSI
PUBLIC Void kwUtlResetKwRbL2Meas
(
KwRbCb	*rbCb
)
#else
PUBLIC Void kwUtlResetKwRbL2Meas(rbCb)
KwRbCb	*rbCb;
#endif
{
   KwL2MeasIpThruput *l2MeasIpThruput = &rbCb->l2MeasIpThruput;

   l2MeasIpThruput->timeT2 = 0;
   l2MeasIpThruput->tempTimeT1 = 0;
   l2MeasIpThruput->dataVol = 0;
   l2MeasIpThruput->count = 0;
   /*prevTbSnMap is freed either in kwUtlProcHarqInd or in kwUtlSndToLi. So*
    *it should not be freed here.                                          */
   l2MeasIpThruput->prevTbSnMap = NULLP;
   l2MeasIpThruput->dlIpThrputSt = KW_DL_IPTHRU_RESET;
}
#endif /* LTE_RLC_R9 */

/**
 *
 * @brief Handler for storing address of MeasData in rbCb at right index
 *
 *
 * @b Description
 *        This function is called when LM sends measReq message to RLC.
 *
 *  @param[in] 
 *  @param[out] 
 *  @param[in] 
 *
 *
 *  @return  S16
 *      -# ROK
 */
#ifdef ANSI
PUBLIC Void kwUtlPlcMeasDatInL2Sts
(
KwL2Cntr       *measData, 
KwL2MeasRbCb   *rbL2Cb,
U8             measType
)
#else
PUBLIC Void kwUtlPlcMeasDatInL2Sts(measData, rbL2Cb, measType)
KwL2Cntr       *measData; 
KwL2MeasRbCb   *rbL2Cb;
U8             measType;
#endif
{
   TRC3(kwUtlPlcMeasDatInL2Sts)
   
   /* We should check the number of measType in the request. This can be done 
    * by looking at each bit in the measType. Also store the measData in the 
    * correct index of l2Sts in RbCb.
    * */

    if(measType & LKW_L2MEAS_ACT_UE)
    {
         rbL2Cb->l2Sts[KW_L2MEAS_ACT_UE] = measData;
    }
    if(measType & LKW_L2MEAS_UU_LOSS)
    {
         rbL2Cb->l2Sts[KW_L2MEAS_UU_LOSS] = measData;
    }
    if(measType & LKW_L2MEAS_DL_IP )
    {
         rbL2Cb->l2Sts[KW_L2MEAS_DL_IP] = measData;
    }
    if(measType & LKW_L2MEAS_UL_IP)
    {
         rbL2Cb->l2Sts[KW_L2MEAS_UL_IP] = measData;
    }

}/* End of kwUtlPlcMeasDatInL2Sts */
#endif /* LTE_L2_MEAS_RLC */
/********************************************************************30**
         End of file:     kw_utl_ul.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:55 2014
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
/main/5      kw003.201 vp  1.  Fixes for re-segmentation, segement offset
                               value and optimization 
/main/6      kw004.201 ap  1.  Used SSI function to initialize the variable.
                           2.  Added fn call cmHashListDelete for deleting
                       rd  3.  Code added for DL and UL IP throughput 
                               measurement under flag LTE_L2_MEAS_RLC.
                              the entry from tbHlCp.  
                           4.  Added code for DL/UL IP Meas in fn 
                               kwUtlSndL2MeasCfm().
/main/7      kw005.201 ap  1. Added support for L2 Measurement.                               
*********************************************************************91*/


