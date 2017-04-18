

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

     Sid:      kw_umm_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:54 2014

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
#include "kw_dl.h"


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
#include "kw_dl.x"

PRIVATE S16 kwUmmEstHdrSz ARGS ((KwCb *gCb,KwDlRbCb *rbCb,
                                 U8 type,U16 sduCount));
PRIVATE S16 kwUmmCreatePdu ARGS ((KwCb *gCb,KwDlRbCb *rbCb,
                                  Buffer **pdu,U8 fi));
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
PRIVATE Void  kwUmmCalDlIpThrPut ARGS ((KwCb *gCb,KwRbCb *rbCb, MsgLen dataVol, 
                                      S32 initialBo, MsgLen pduSz));
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */

/** @addtogroup ummode */
/*@{*/

/**
 *
 * @brief 
 *
 *        Handler to queue the SDU in the SDU queue and update BO and report it to the lower layer.
 *
 * @b Description: 
 *
 *        This function is used to queue the received SDU in the 
 *        SDU queue maintained in the radio bearer control block.
 *        After queuing the SDU, BO is updated and is reported
 *        to the lower layer. 
 *            
 *  @param[in] rbCb RB control block 
 *  @param[in] sdu  SDU to be queued 
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwUmmQSdu       
(
KwCb   *gCb,
KwDlRbCb *rbCb,                   /* Rb Control Block */
U32    sduId,                   /* Data Request Information */
Buffer *mBuf                    /* SDU buffer */
)
#else
PUBLIC S16 kwUmmQSdu(gCb,rbCb,sduId,mBuf)
KwCb          *gCb;
KwDlRbCb        *rbCb;            /* Rb Control Block */
U32           sduId;            /* Data Request Information */
Buffer        *mBuf;            /* SDU buffer */
#endif
{
   MsgLen len;                  /* SDU buffer length */
   KwSdu  *sdu;                 /* SDU */
   KwUmDl *umDl;                /* UM Downlink Cb */

   TRC2(kwUmmQSdu)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL), (gCb->init.prntBuf,
           "kwUmmQSdu(rbCb, sduId, mBuf)\n"));
#endif
   KW_ALLOC(gCb,sdu,(Size)sizeof(KwSdu));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( sdu == NULLP )
   {
       KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW214, (ErrVal) RFAILED,
            "KwSdu: sdu allocation Failed.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   SFndLenMsg(mBuf,&len);
   umDl = &(rbCb->m.umDl);

   sdu->mBuf = mBuf;
   sdu->sduSz = len;
   sdu->mode.um.sduId = sduId;
   sdu->mode.um.isSegmented = FALSE;

   umDl->bo += len;
   kwUmmEstHdrSz(gCb,rbCb,KW_ADD_SDU,1);
   
   cmLListAdd2Tail(&(rbCb->m.umDl.sduQ), &sdu->lstEnt);
   sdu->lstEnt.node = (PTR)sdu;
   
   kwUtlSndDStaRsp(gCb,rbCb,umDl->bo,umDl->estHdrSz,FALSE);
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   /* Update numActUe if it is not active */
   if((rbCb->rbL2Cb.measOn & LKW_L2MEAS_ACT_UE) &&
      (rbCb->ueCb->numActRb[rbCb->qci]++ == 0))
   {
     kwCb.kwL2Cb.numActUe[rbCb->qci]++;
   }
#endif
   RETVALUE(ROK); 
   
}

#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
/**
 *
 * @brief Private handler to calculate DL IP throughput.
 *
 * @b Description
 *      This function is called from kwUmmProcessSdus.
 *      If the RLC bo is more than allocation from MAC,
 *        T2 time stamp is taken and stored in KwRbCb.
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
PRIVATE Void kwUmmCalDlIpThrPut
(
KwRbCb          *rbCb,
MsgLen          dataVol,
S32             initialBo,
MsgLen          pduSz
)
#else
PRIVATE Void  kwUmmCalDlIpThrPut (rbCb, dataVol, initialBo, pduSz)
KwRbCb          *rbCb;
MsgLen          dataVol;
S32             initialBo;
MsgLen          pduSz;
#endif
{
   KwTbSnMap      *curTbSnMap = NULLP; /*Holds the current TbSnMap*/
   KwL2MeasIpThruput *l2MeasIpThruput = NULLP;
   EpcTime timeSt;

   TRC2(kwUmmCalDlIpThrPut)
#ifdef DEBUGP
   KWDBGP((KW_DBGMASK_UM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL), (gCb->init.prntBuf,
           "kwUmmCalDlIpThrPut(rbCb, dataVol, initialBo, pduSz)\n"));
#endif

   /*Get the current TbSnMap*/
   curTbSnMap = kwCb.kwL2Cb.curTbSnMap;

   l2MeasIpThruput = &rbCb->l2MeasIpThruput;

   KWDBGP((KW_DBGMASK_UM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
   (gCb->init.prntBuf, "kwUmmCalDlIpThrPut: Log for dl ip throughput:\n \
    RB_MeasOn: %d\n curTbSnMap->numSn: %d\n State: %d\n      \
    Count: %d\n  dataVol: %lu\n prevTbSnMap: %p\n initialBo: %ld\n \
    Alloc from MAC: %d\n", rbCb->rbL2Cb.measOn, curTbSnMap->numSn,
    l2MeasIpThruput->dlIpThrputSt, l2MeasIpThruput->count,
    l2MeasIpThruput->dataVol, (Void*)l2MeasIpThruput->prevTbSnMap,
    initialBo, pduSz));

   /*Check if DL ip throughput measurement is going on or not AND at least*
    *one new data PDU is formed.                                          */
   if( (0 != (rbCb->rbL2Cb.measOn & LKW_L2MEAS_DL_IP)) && (curTbSnMap->numSn > 0) )
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
               l2MeasIpThruput->prevTbSnMap->snSduMap[l2MeasIpThruput->prevTbSnMap->numSn - 1].isBurstSplitted = FALSE;
            }
            else if(l2MeasIpThruput->count == 0)
            {
               l2MeasIpThruput->prevTbSnMap = NULLP;
            }
            else
            {
#ifndef ALIGN_64BIT
               KWDBGP((KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_DL),
               (gCb->init.prntBuf, "kwUmmProcessSdus: count can be either 1 or 0.\
                L2Mcount = %d \n", l2MeasIpThruput->count));
#else
               KWDBGP((KW_DBGMASK_UM | KW_DBGMASK_ERROR | KW_DBGMASK_DL),
               (gCb->init.prntBuf, "kwUmmProcessSdus: count can be either 1 or 0.\
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

            /*Store in KwRbCb.*/
            l2MeasIpThruput->timeT2 = timeSt;

            /*Preserve the curent TbSnMap in KwRbCb upto next allocation.*/
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

   KWDBGP((KW_DBGMASK_UM | KW_DBGMASK_DETAIL | KW_DBGMASK_DL),
   (gCb->init.prntBuf, "kwUmmCalDlIpThrPut: Log for dl ip throughput:\n \
    RB_MeasOn: %d\n curTbSnMap->numSn: %d\n State: %d\n      \
    Count: %d\n  dataVol: %lu\n prevTbSnMap: %p\n initialBo: %ld\n \
    Alloc from MAC: %d\n", rbCb->rbL2Cb.measOn, curTbSnMap->numSn,
    l2MeasIpThruput->dlIpThrputSt, l2MeasIpThruput->count,
    l2MeasIpThruput->dataVol, (Void*)l2MeasIpThruput->prevTbSnMap,
    initialBo, pduSz));
} /* kwUmmCalDlIpThrPut */
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */


/**
 *
 * @brief 
 *
 *        Handler to form PDU(s) and update the BO. 
 *
 * @b Description: 
 *
 *        -# This function forms pdu(s) from the SDU(s) in the
 *        SDU queue and returns them.
 *        -# This function also updates the BO along with the 
 *        along with the estimated Header size.
 *            
 * @param[in]  rbCb     RB control block 
 * @param[out] pduInfo  Pdu Info to be filled and the PDU size to be formed and the updated BO
 * @param[in]  pduSz    The size for which PDUs have to constructed
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 kwUmmProcessSdus
(
KwCb      *gCb,
KwDlRbCb    *rbCb,                /* Rb Control Block */
KwDatReq  *datReq               /* PDU Info to be filled */
)
#else
PUBLIC S16 kwUmmProcessSdus(gCb,rbCb, datReq)
KwCb      *gCb;
KwDlRbCb    *rbCb;                /* Rb Control Block */
KwDatReq  *datReq;              /* PDU Info to be filled */
#endif
{
   CmLList *firstNode;          /* First Node in SDU queue */
   CmLListCp *sduQ;             /* SDU queue */
   U8      fi;                  /* Framing Info */
   Buffer  *pdu;                /* Buffer for holding the formed PDU */
   S32     *bo;                 /* BO   */
   U16     sduCount;            /* SDU count */
   U8      snLen;               /* SN length */
   KwPduInfo *pduInfo;          /* PDU Info pointer */
   S16     pduSz;               /* PDU Size to be constructed */
   S16     ret;                 /* Return value */
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   Bool    dataWasPrsnt;        /* Initially was data existing? */
#ifdef LTE_RLC_R9
   S32            initialBo   = 0;     /*Used to compare with DL allocation*/
   U16            dataVol     = 0;     /* Holds the sum of added RLC SDUs */
   MsgLen         sduSz;
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */

   /* kw005.201, updated for statistics */
   KwKwuSapCb   *kwuSapCb;      /* KWU SapCb */

   TRC2(kwUmmProcessSdus)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL), (gCb->init.prntBuf,
           "kwUmmProcessSdus(rbCb, datReq)\n"));
#endif
   fi = 0;
   sduCount = 0;
   pdu = NULLP;
   bo = &(rbCb->m.umDl.bo); 
   sduQ = &(rbCb->m.umDl.sduQ); 
   snLen = rbCb->m.umDl.snLen;
   pduInfo = &(datReq->pduInfo);
   pduSz = datReq->pduSz;
   /* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   dataWasPrsnt   =  sduQ->count > 0? TRUE: FALSE;
#ifdef LTE_RLC_R9
   initialBo = *bo;
#endif /* LTE_RLC_R9 */
#endif /*  LTE_L2_MEAS_RLC */

   while( pduSz > 0 && sduQ->count > 0 )
   {
      Buffer *tmpPdu = NULLP;
      KwSdu  *sdu;
      MsgLen *msgLen;

      CM_LLIST_FIRST_NODE(sduQ,firstNode);
      sdu = (KwSdu *)(firstNode->node);
      msgLen = &(sdu->sduSz);
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
      sduSz = sdu->sduSz;
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */

      /* When forming a new PDU
           -# Eliminate MAC header size for each pdu 
           -# Initialize the li array to 0 
           -# Substract the fixed header length based on SN length
      */
      if ( pdu == NULLP )
      {
         KW_RMV_MAC_HDR_SZ(pduSz);
         UMDL.numLi = 0;
         if ( sdu->mode.um.isSegmented == TRUE )
            fi = 2;
         else
            fi = 0;
         KW_RMV_RLC_HDR_SZ(pduSz, rbCb->m.umDl.snLen);
         /* kw005.201 fixing pduSz <= 0 problem, ccpu00119417 */
         if(pduSz <= 0)
         {
            break;
         }
      }

      kwUtlCalcLiForSdu(gCb,rbCb->m.umDl.numLi,*msgLen,&pduSz);
     
      /* Exact fit scenario :
         If the SDU size matches with the PDU size
           -# Allocate memory equal to PDU size;
           -# update BO
           -# Remove SDu from queue
           -# Append to already existing PDU portion if present .
           -# Add Header and create complete PDU and place it in pduInfo and return
      */ 
      if ( *msgLen == pduSz )
      {
         SGetMsg(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb),&tmpPdu);

         ret = SCatMsg(tmpPdu,sdu->mBuf,M1M2);
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ROK != ret )
            {
               /* SCatMsg failed */
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SCatMsg Failed\n"));
#endif
               if ( tmpPdu )
               {
                  SPutMsg(tmpPdu);
               }
               (UMDL.numLi)--;
               break;
            }
#endif
        
         if ( pdu == NULLP )
         {
            pdu = tmpPdu;
         }
         else
         {
            ret = SCatMsg(pdu,tmpPdu,M1M2);    
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ROK != ret )
            {
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SCatMsg Failed\n"));
#endif
               sdu->mBuf = tmpPdu;
               (UMDL.numLi)--;
               break;
            }
#endif
            SPutMsg(tmpPdu);
         }
         *bo -= pduSz;
         pduSz = 0;

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
         kwUtlUpdSduSnMap(rbCb, sdu, datReq, TRUE);
#endif /*  LTE_L2_MEAS_RLC */
         KW_RMV_SDU(gCb,&(rbCb->m.umDl.sduQ),sdu); /* kw003.201 */
         KW_CREATE_UM_PDU(gCb,rbCb,pdu,fi,pduInfo,ret); 
         gCb->genSts.pdusSent++;
#if (ERRCLASS & ERRCLS_DEBUG)
         if ( ret != ROK )
         {
#ifdef DEBUGP
            KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"KW_CREATE_UM_PDU Failed\n"));
#endif
            SPutMsg(pdu);
            break;
         }
#endif
         /* kw005.201 ccpu00117318, updating the statistics */
         kwuSapCb = (KwKwuSapCb *)(gCb->u.dlCb->kwuDlSap + rbCb->kwuSapId);
         kwuSapCb->sts.sduTx++;
         sduCount++;
      }
      /* Concatenation scenario :
         If SDU size is less than the requested PDU size
           -# Allocate memory and copy SDU into it.
           -# Update BO
           -# Remove SDU from the Queue.
           -# Append to already existing PDU portion if present .
           -# If the SDU size is greater than 2047 or the number of LIs reaches max,
                 place it as a separate PDU in pduInfo and set pdu to NULL
              else 
                 place the msglen in li array and continue with the next SDU.
           -# If the number of PDUs is more than KW_MAX_PDU, return from the function
              even if pduSize > 0.
      */
      else if (*msgLen < pduSz )
      {
         SGetMsg(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb),&tmpPdu);
         ret = SCatMsg(tmpPdu,sdu->mBuf,M1M2);
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ROK != ret )
            {
               /* SCatMsg Failed */
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SCatMsg Failed\n"));
#endif
               if ( tmpPdu )
               {
                  SPutMsg(tmpPdu);
               }
               (UMDL.numLi)--;
               break;
            }
#endif
         if (pdu == NULLP)
         {
            pdu = tmpPdu;
         }
         else
         {
            ret = SCatMsg(pdu,tmpPdu,M1M2);
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ROK != ret )
            {
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SCatMsg Failed\n"));
#endif
               sdu->mBuf = tmpPdu;
               (UMDL.numLi)--;
               break;
            }
#endif
            SPutMsg(tmpPdu);
         }
         *bo -= *msgLen;

         pduSz -= *msgLen;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
          kwUtlUpdSduSnMap(rbCb, sdu, datReq, TRUE);
#endif /*  LTE_L2_MEAS_RLC */
         if ( *msgLen < 2048 && UMDL.numLi < KW_MAX_LI )
         {
            rbCb->m.umDl.li[(UMDL.numLi)++] = *msgLen;
         }
         else 
         {
            KW_CREATE_UM_PDU(gCb,rbCb,pdu,fi,pduInfo,ret);     
            gCb->genSts.pdusSent++;
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ret != ROK )
            {
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"KW_CREATE_UM_PDU Failed\n"));
#endif
               SPutMsg(pdu);
               break;
            }
#endif
            if ( pduInfo->numPdu == KW_MAX_PDU)
            {
                /* Could not transmit what MAC asked for because the number of PDUs to be transmitted has reached maximum. */
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"Maximum Pdu limit has been reached\n"));
#endif
               break;
            }
         }
         KW_RMV_SDU(gCb,&(rbCb->m.umDl.sduQ),sdu);
         /* kw005.201 ccpu00117318, updating the statistics */
         kwuSapCb = (KwKwuSapCb *)(gCb->u.dlCb->kwuDlSap + rbCb->kwuSapId);
         kwuSapCb->sts.sduTx++;
         sduCount++;
      }
      /* Segmentation scenario :
         If size of SDU is greater than PDU size 
           -# Allocate memory and Segment the Sdu.
           -# Update BO
           -# Append to already existing PDU if any.
           -# Set the second bit of the framing info.
           -# Create the complete PDU and place in pduInfo.
      */ 
      else {
         Buffer *remSdu;
       
         SGetMsg(KW_GET_MEM_REGION(gCb), KW_GET_MEM_POOL(gCb),&tmpPdu);
         ret = SSegMsg(sdu->mBuf,pduSz,&remSdu);
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ROK != ret )
            {
               /* SSegMsg failed */
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SSegMsg Failed\n"));
#endif
               if ( tmpPdu )
               {
                  SPutMsg(tmpPdu);
               }
               (UMDL.numLi)--;
               break;
            }
#endif
         ret = SCatMsg(tmpPdu,sdu->mBuf,M1M2);
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ret != ROK )
            {
#ifdef DEBUGP
                KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SCatMsg Failed\n"));
#endif
               if ( tmpPdu )
               {
                  SPutMsg(tmpPdu);
               }
               SPutMsg(sdu->mBuf);
               KW_RMV_SDU(gCb,sduQ,sdu);
               (UMDL.numLi)--;
               break;
            }
#endif
         SPutMsg(sdu->mBuf);
         sdu->mBuf = remSdu;
         *msgLen -= pduSz;
         *bo -= pduSz;
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
         sduSz = pduSz;
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */
         sdu->mode.um.isSegmented = TRUE;
        
         pduSz = 0;
 
         if (pdu == NULLP) 
            pdu = tmpPdu;
         else 
         {
            ret = SCatMsg(pdu,tmpPdu,M1M2);
#if (ERRCLASS & ERRCLS_DEBUG)
            if ( ROK != ret )
            {
#ifdef DEBUGP
               KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SCatMsg Failed\n"));
#endif
               SPutMsg(tmpPdu);
               (UMDL.numLi)--;
               break;
            }
#endif
            SPutMsg(tmpPdu);
         }
         fi |= 1;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
         kwUtlUpdSduSnMap(rbCb, sdu, datReq, FALSE);
#endif /*  LTE_L2_MEAS_RLC */
         KW_CREATE_UM_PDU(gCb,rbCb,pdu,fi,pduInfo,ret);     
         gCb->genSts.pdusSent++;
#if (ERRCLASS & ERRCLS_DEBUG)
         if ( ret != ROK )
         {
#ifdef DEBUGP
            KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"KW_CREATE_UM_PDU Failed\n"));
#endif
            SPutMsg(pdu);
            break;
         }
#endif
      }
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#ifdef LTE_RLC_R9
      dataVol += sduSz;
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */
   }
#ifdef LTE_L2_MEAS_RLC
   if((rbCb->rbL2Cb.measOn) && 
      (sduQ->count == 0)    && 
      (dataWasPrsnt))
   {
      if(--(rbCb->ueCb->numActRb[rbCb->qci]) == 0)
      {
         kwCb.kwL2Cb.numActUe[rbCb->qci]--;
      }
   }
#ifdef LTE_RLC_R9
   /* Calculate DL IP throughput */
   kwUmmCalDlIpThrPut(rbCb, dataVol, initialBo, datReq->pduSz);
#endif /* LTE_RLC_R9 */
#endif /* LTE_L2_MEAS_RLC */

   /* If we have a situation wherein the size requested is greater than the total size of SDUs
      and a pdu buffer which is not null, this if loop helps to send 
      a non null PDU to the lower layer. 
   */
   if ( pduSz > 0 && pdu != NULLP )
   {
      if ( pduInfo->numPdu != KW_MAX_PDU )
      {
         rbCb->m.umDl.numLi--;
         KW_CREATE_UM_PDU(gCb,rbCb,pdu,fi,pduInfo,ret);     
         gCb->genSts.pdusSent++;
#if (ERRCLASS & ERRCLS_DEBUG)
         if ( ret != ROK )
         {
#ifdef DEBUGP
            KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"KW_CREATE_UM_PDU Failed\n"));
#endif
            SPutMsg(pdu);
         }
#endif
      }
      else
          SPutMsg(pdu);
   } 
   kwUmmEstHdrSz(gCb,rbCb,KW_DEL_SDU,sduCount);
   datReq->boRep.bo = UMDL.bo;
   datReq->boRep.estHdrSz = UMDL.estHdrSz;
   datReq->boRep.staPduPrsnt = FALSE;
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
PUBLIC S16 kwDlUmmReEstablish
(
KwCb        *gCb,
CmLteRlcId  rlcId,
Bool        sendReEst,
KwDlRbCb      *rbCb
)
#else
PUBLIC S16 kwDlUmmReEstablish(gCb,rlcId, rbCb)
KwCb        *gCb;
CmLteRlcId  rlcId;
Bool        sendReEst;
KwRbCb      *rbCb;
#endif
{
   KwKwuSapCb *kwKwSap = NULLP;         /* KWU SAP Information */

   TRC2(kwUmmReEstablish)
#ifdef DEBUGP
   KWDBGP(gCb,
         (KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_DL |  KW_DBGMASK_UL),
         (gCb->init.prntBuf," kwUmmReEstablish(rbCb) \n"));
#endif
#ifdef LTE_L2_MEAS_RLC
      kwUtlEmptySduQ(gCb,rbCb, &rbCb->m.umDl.sduQ);
#else
      kwUtlEmptySduQ(gCb,&rbCb->m.umDl.sduQ);
#endif
      rbCb->m.umDl.vtUs = 0;

   kwKwSap = gCb->u.dlCb->kwuDlSap + KW_UI_PDCP;

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
 *        Handler to create the header and complete a PDU.
 *
 * @b Description: 
 *
 *        This function is used to create the header of a PDU and concatenate  it
 *        with the data part of the PDU.
 *            
 *  @param[in] rbCb RB control block 
 *  @param[in] pdu  PDU  
 *  @param[in] fi   Framing Info field
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PRIVATE S16 kwUmmCreatePdu
(
KwCb   *gCb,
KwDlRbCb *rbCb,           /* Rb Control Block */
Buffer **pdu,           /* PDU */
U8     fi               /* Framing Info */
)
#else
PRIVATE S16 kwUmmCreatePdu(gCb,rbCb,pdu,fi)
KwCb   *gCb;
KwDlRbCb *rbCb;           /* Rb Control Block */
Buffer **pdu;           /* PDU */
U8     fi;              /* Framing Info */
#endif
{
   U16  sn;             /*  Sequence Number */
   S16 liCount;         /*  LI count */
   S16 oldliCount;         /*  LI count */
   U16 *li;             /*  LI Array */
   U8   e;              /* Extension Bit */
   S16 count;           /* Loop Counter */
   U16  modVal;          /* Modulation element */

   TRC2(kwUmmCreatePdu) 
#ifdef DEBUGP   
   KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_DL),
                  (gCb->init.prntBuf," kwUmmCreatePdu(rbCb,pdu,fi) \n"));
#endif
   sn = rbCb->m.umDl.vtUs;
   liCount = rbCb->m.umDl.numLi;
   oldliCount = rbCb->m.umDl.numLi;
   li = (rbCb->m.umDl.li);
   e = 0;


   if ( liCount % 2 == 1 )
   {
      U16 liData;
      liData = li[liCount -1] << 4;
      KW_ADD_PRE_MSG(*pdu,liData,2);
      liCount--;
      e = 1;
   } 
   for ( count = liCount - 1;count >= 0;count = count -2 )
   {
      U32 liData = li[count] | ( e << 11);
     
      li[count-1] |= (1<<11);
      liData |= (li[count-1] << 12);

      KW_ADD_PRE_MSG(*pdu,liData,3);
      e = 1; 
   }
   if ( rbCb->m.umDl.snLen == 1) 
   {
      U8 hdrData = 0;
      hdrData |= sn;
     
      if ( liCount > 0)
         hdrData |= 0x20;
      hdrData |= (fi<<6);

      KW_ADD_PRE_MSG(*pdu,hdrData,1);     
   }
   else if ( rbCb->m.umDl.snLen == 2)
   {
      U16 hdrData = 0;
      hdrData |= sn;
      /* kw002.201 Checking for proper liCnt to set first e-bit */ 
      if ( oldliCount  > 0 )
         hdrData |= 0x0400;
      hdrData |= (fi<<11);

      KW_ADD_PRE_MSG(*pdu,hdrData,2);
   }
   modVal = KW_POWER(2, (5 * rbCb->m.umDl.snLen));
   sn = (sn + 1) % modVal; 
   rbCb->m.umDl.vtUs = sn;
   RETVALUE(ROK);
}

/**
 *
 * @brief 
 *
 *        Handler to estimate the header size of the RLC SDUs present in the SDU queue.
 *
 * @b Description: 
 *
 *        This function is used to update the estimated header size variable in RB.
 *        This function is called when a SDU is queued and when a PDU is formed and
 *        sent to the lower layer.
 *            
 *  @param[in] rbCb     RB control block 
 *  @param[in] type     Type of Operation( Addition or Deletion of SDU)
 *  @param[in] sduCount Number of SDUs which are Added/Deleted
 *  @return  S16
 *      -# ROK 
 *
 */
#ifdef ANSI
PUBLIC S16 kwUmmEstHdrSz
(
KwCb   *gCb,
KwDlRbCb *rbCb,           /* RB Control Block */
U8     type,            /* Type of Operation */
U16 sduCount            /* SDU count */
)
#else
PUBLIC S16 kwUmmEstHdrSz(gCb,rbCb,type,sduCount)
KwCb   *gCb;
KwDlRbCb *rbCb;           /* RB Control Block */
U8     type;            /* Type of Operation */
U16 sduCount;           /* SDU count */
#endif
{
   /* kw005.201 removed warning */
   S32 *estHdrSz;
   S32  totalSduCount;

   TRC3(kwUmmEstHdrSz)
#ifdef DEBUGP 
   KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF| KW_DBGMASK_DL),
                  (gCb->init.prntBuf," kwUmmEstHdrSz(rbCb) \n"));
#endif
   estHdrSz = &(rbCb->m.umDl.estHdrSz);
   totalSduCount = rbCb->m.umDl.sduQ.count;

   if ( type == KW_DEL_SDU )
   {
      if (totalSduCount == 0)
      {
         *estHdrSz = 0;
      }
      else
      {
         *estHdrSz -= sduCount * 2;
      }
   }
   else if ( type == KW_ADD_SDU)
   {
      if (totalSduCount == 0)
         *estHdrSz = 3;
      else
         *estHdrSz += 2;
   } 
  
   if ( *estHdrSz < 0)
      *estHdrSz = 0; 

   RETVALUE(ROK);
}

/**
 *
 * @brief 
 *
 *        Handler to discard a SDU.
 *
 * @b Description: 
 *
 *        This function is used to discard a SDU after receiving
 *        the Discard Request from the upper layer.The SDU is 
 *        discarded if it is present and is not mapped to any PDU yet.
 *            
 *  @param[in] rbCb   RB control block 
 *  @param[in] sduId  SDU ID of the SDU to be discarded
 *  @return  S16
 *      -# ROK 
 *
 */

#ifdef ANSI
PUBLIC S16 kwUmmDiscSdu
(
KwCb      *gCb,
KwDlRbCb    *rbCb,                /* RB Control Block */
U32       sduId                 /* SDU ID */
)
#else
PUBLIC S16 kwUmmDiscSdu(gCb,rbCb,sduId)
KwCb      *gCb;
KwDlRbCb    *rbCb;                /* RB Control Block */
U32       sduId;                /* SDU ID */
#endif
{
   CmLList *tmpNode;            /* Temporary Node in SDU queue */
   KwSdu   *sdu;                /* SDU */
   CmLListCp *sduQ;             /* SDU Queue Pointer */
   
   TRC2(kwUmmDiscSdu)
#ifdef DEBUGP  
   KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"  kwUmmDiscSdu(rbCb,sduId) \n"));
#endif 
   sduQ = &(rbCb->m.umDl.sduQ);
  
   CM_LLIST_FIRST_NODE(sduQ,tmpNode);

   while (tmpNode)
   {
      sdu = (KwSdu *)tmpNode->node;
      
      if (sdu->mode.um.sduId == sduId && sdu->mode.um.isSegmented == FALSE)
      {
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
         if(rbCb->rbL2Cb.measOn & LKW_L2MEAS_DL_DISC)
         {
            kwUtlSndDiscSduCfm(rbCb, sdu->mode.um.sduId);
         }
#endif /*  LTE_L2_MEAS_RLC */
         KW_RMV_SDU(gCb,sduQ,sdu);
         gCb->genSts.numSduDisc++;         
         tmpNode = NULLP;
         break;
      }
      CM_LLIST_NEXT_NODE(sduQ,tmpNode);
   }
   if (tmpNode == NULLP)
   {
      /* SDU which has to be deleted if not found in the queue or is segmented and can't be removed */
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_UM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SDU not found for discard\n"));
#endif
   }
   RETVALUE(ROK);
}

/********************************************************************30**
         End of file:     kw_umm_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:54 2014
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

