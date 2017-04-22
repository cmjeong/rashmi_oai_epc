

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

     Sid:      kw_utl_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:55 2014

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
#include "kw_dl.h"

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
#include "kw_dl.x"


/**
 *
 * @brief 
 *
 *        Handler for sending the data to multiple logical channels of a UE.
 *
 * @b Description:
 *
 *        This function sends the data for one or more logical channels
 *        after processing the SDUs and forming the PDUs.It calls
 *        UMM or AMM functions to form the PDUs for the requested sizes
 *        by MAC. 
 *
 *  @param[in] staIndInfo   Status Indication Information containing the 
 *                          size of PDU(s) for one or more logical channels  
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 *
 */
#ifdef ANSI
PUBLIC S16 kwUtlSndToLi
(
KwCb          *gCb,
KwDStaIndInfo *staIndInfo               /* Status Indication Information */
)
#else
PUBLIC S16 kwUtlSndToLi(gCb,staIndInfo)
KwCb           *gCb;
KwDStaIndInfo  *staIndInfo;             /* Status Indication Information */
#endif
{
   KwDlUeCb *ueCb;                        /* UE control block */
   U8 count;                            /* Loop Counter */
   U8 numTb;                            /* Number of Tbs */
   KwDlRbCb *rbCb;                        /* RB Control Block */
   KwDatReq datReq;                    /* PDUs Information */
   RguDDatReqInfo *datReqInfo;          /* Data Request Information */
   KwRguSapCb *rguSap;                  /* MAC SAP CB */
   KwUeKey   ueKey;                     /* UE Key for fetching UE CB */
   S16       ret;                       /* Return value */
   U32       totNumPdu;                 /* Total number of PDUS */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
   KwTbSnMap *tbSnMap;                  /* Tb Sn Map */
   U8        snIdx1;
   U8        snIdx2;
#endif /* LTE_L2_MEAS_RLC */

   TRC2(kwUtlSndToLi)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF | KW_DBGMASK_DL ),
          (gCb->init.prntBuf, "kwUtlSndToLi(staIndInfo)\n"));
#endif
   count = 0;
   ueCb = NULLP;
   totNumPdu = 0;

   ueKey.cellId = staIndInfo->cellId;
   ueKey.ueId   = staIndInfo->rnti;

   ret = kwDbmFetchDlUeCb(gCb,ueKey.ueId, ueKey.cellId, &ueCb);
   if (ret != ROK )
   {
      /* Fetch UeCb failed */
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW217, (ErrVal) RFAILED,
            "kwDbmFetchUeCb : Fetch UeCb Failed.");
      RETVALUE(RFAILED);
   }
   KW_ALLOC(gCb,datReqInfo,sizeof(RguDDatReqInfo));
   /* kw002.201 Removed the allocation of KwDatReq */
   /* kw004.201 Used SSI function to initialize the variable */
   cmMemset( (U8 *)&datReq, 0, sizeof(KwDatReq) ); 

#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( datReqInfo == NULLP )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW218, (ErrVal) RFAILED,
            "KwDatReq: kwDatReq allocation Failed.");

      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */

   for (numTb = 0; numTb < staIndInfo->nmbOfTbs; numTb++)
   {
      RguStaIndTb  *staIndTb = &(staIndInfo->staIndTb[numTb]);
      RguDatReqTb  *datReqTb = &(datReqInfo->datReqTb[numTb]);

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
      KW_ALLOC(tbSnMap,sizeof(KwTbSnMap));
      tbSnMap->tbId  =  ++kwCb.kwL2Cb.tbId;
      kwCb.kwL2Cb.curTbSnMap = tbSnMap;
      datReqTb->snMapPres = TRUE;
      KW_ALLOC(datReqTb->rguSnInfo,sizeof(RguSnMapInfo));
      datReqTb->rguSnInfo->tbId = tbSnMap->tbId;
      datReqTb->rguSnInfo->numLch = staIndTb->nmbLch;
#endif /* LTE_L2_MEAS_RLC */

      for (count = 0;count < staIndTb->nmbLch; count++)
      {
         rbCb = ueCb->lCh[staIndTb->lchStaInd[count].lcId - 1].dlRbCb;

         if ( rbCb != NULLP )
         { 
            datReq.pduSz = staIndTb->lchStaInd[count].totBufSize;
            if ( rbCb->mode == CM_LTE_MODE_UM )
            {
               ret = kwUmmProcessSdus(gCb,rbCb,&datReq);
#if (ERRCLASS & ERRCLS_DEBUG)
               if ( ret != ROK )
               {
#ifdef DEBUGP
                  KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW219, (ErrVal) RFAILED,
                            "kwUmmProcessSdus Failed.");
#endif

                  RETVALUE(RFAILED);
               }
#endif /* ERRCLASS & ERRCLS_DEBUG */
            }
            else if ( rbCb->mode == CM_LTE_MODE_AM )
            {
               ret = kwAmmProcessSdus(gCb,rbCb,&datReq);
#if (ERRCLASS & ERRCLS_DEBUG)
               if ( ret != ROK )
               {
#ifdef DEBUGP
                   KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW220, (ErrVal) RFAILED,
                             "kwAmmProcessSdus Failed.");
#endif

                   RETVALUE(RFAILED);
               }
#endif /* ERRCLASS & ERRCLS_DEBUG */
            }
   
            if ( datReq.pduInfo.numPdu == 0 )
            {
               continue;
            }
            totNumPdu += datReq.pduInfo.numPdu;
            cmMemcpy((U8 *)(&(datReqTb->lchData[count].pdu)),(U8 *)(&(datReq.pduInfo)),sizeof(KwPduInfo));
            datReqTb->lchData[count].boReport.bo = datReq.boRep.bo;

#ifdef CCPU_OPT
            datReqTb->lchData[count].boReport.estRlcHdrSz = datReq.boRep.estHdrSz;
            datReqTb->lchData[count].boReport.staPduPrsnt = datReq.boRep.staPduPrsnt;
#endif /* CCPU_OPT */

            datReqTb->lchData[count].lcId = staIndTb->lchStaInd[count].lcId;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
            datReqTb->rguSnInfo->lchMap[count].lChId = staIndTb->lchStaInd[count].lcId;
            /* In some cases L2 Measurement for few of the lcId may be off, 
             * in this case we are assigning snList to 0xffff 
             */
            for(snIdx1 = 0; snIdx1 < RGU_MAX_PDU; snIdx1++)
            {
               datReqTb->rguSnInfo->lchMap[count].snList[snIdx1] = 0xffff;
            }
            if(tbSnMap->numSn != 0)
            {
               snIdx2 = 0;
               for(snIdx1 = tbSnMap->prevNumSn; snIdx1 < tbSnMap->numSn; snIdx1++)
               {
                   datReqTb->rguSnInfo->lchMap[count].snList[snIdx2++] = 
                   tbSnMap->snSduMap[snIdx1].sn;
               }
               tbSnMap->prevNumSn = tbSnMap->numSn;
            }
#endif
            /* kw004.201 Used SSI function to initialize the variable */
            cmMemset( (U8 *)&datReq, 0, sizeof(KwDatReq) ); 
         }
      }
      datReqTb->nmbLch = staIndTb->nmbLch;
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
      if(tbSnMap->numSn == 0)
      {
         KW_FREE(tbSnMap,sizeof(KwTbSnMap));
         KW_FREE(datReqTb->rguSnInfo,sizeof(RguSnMapInfo));
         datReqTb->rguSnInfo = NULLP;
         kwCb.kwL2Cb.curTbSnMap = NULLP;
         datReqTb->snMapPres = FALSE;
      }
      else
      {
         cmHashListInsert(&(kwCb.kwL2Cb.tbHlCp),(PTR)tbSnMap,
               (U8 *) &(tbSnMap->tbId), (U16)sizeof(tbSnMap->tbId));
         kwCb.kwL2Cb.curTbSnMap = NULLP;
      }
#endif /* LTE_L2_MEAS_RLC */
   }
   if ( totNumPdu == 0 )
   {
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"No data to send \n"));
#endif
      KW_FREE(gCb,datReqInfo,sizeof(RguDDatReqInfo));
      RETVALUE(ROK);
   }
  
   datReqInfo->nmbOfTbs = staIndInfo->nmbOfTbs;
   datReqInfo->transId = staIndInfo->transId;
   datReqInfo->cellId  = staIndInfo->cellId;
   datReqInfo->rnti    = staIndInfo->rnti; 
   /* If trace flag is enabled send the trace indication */
   if(gCb->init.trc == TRUE)
   {
      /* Populate the trace params */
      kwLmmSendTrc(gCb,EVTRGUDDATREQ, NULLP);
   }

   rguSap = &(gCb->u.dlCb->rguDlSap);
   KwLiRguDDatReq(&rguSap->pst,rguSap->spId,datReqInfo); 
   RETVALUE(ROK);
}
/**
 *
 * @brief 
 *
 *        Handler for sending Status Response to MAC. 
 *
 * @b Description:
 *
 *        This function is used by  RLC entity for sending
 *        status response to MAC after receiving a SDU from
 *        PDCP.
 *
 *  @param[in]  rbCb               Radio Bearer Control Block 
 *  @param[in]  bo                 BO
 *  @param[in]  estHdrSz           Estimated Header Size
 *  @param[in]  staPduPrsnt        Status PDU present or not
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 kwUtlSndDStaRsp
(
KwCb     *gCb,
KwDlRbCb *rbCb,                           /* RB Control Block */
S32    bo,                              /* Buffer Occupancy */
S32    estHdrSz,                        /* Estimated Header Size */
Bool   staPduPrsnt                        /* Status PDU presence */
)
#else
PUBLIC S16 kwUtlSndDStaRsp(gCb,rbCb,bo,estHdrSz,staPduPrsnt)
KwCb   *gCb;
KwDlRbCb *rbCb;                            /* RB Control Block */
S32    bo;                              /* Buffer Occupancy */
S32    estHdrSz;                        /* Estimated Header Size */
Bool   staPduPrsnt;                       /* Status PDU presence */
#endif
{
   RguDStaRspInfo  *staRspInfo;         /* Status Response Information */
   KwRguSapCb *rguSap;                 /* MAC SAP Information */
printf("\n*******************************\n");
printf("UEId[%d] RBId[%d] lchId[%d] BO[%d]",rbCb->rlcId.ueId,rbCb->rlcId.rbId,rbCb->lch.lChId,bo);
printf("\n*******************************\n");
   TRC3(kwUtlSndDStaRsp)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwUtlSndDStaRsp(rbCb)\n"));
#endif
   KW_ALLOC(gCb,staRspInfo,sizeof(RguDStaRspInfo)); 
#if (ERRCLASS & ERRCLS_ADD_RES)
   if (staRspInfo == NULLP )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW224, (ErrVal) RFAILED,
               " KW_ALLOC failed for staRspInfo.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
   rguSap = &(gCb->u.dlCb->rguDlSap);

#ifdef CCPU_OPT
   staRspInfo->boReport.estRlcHdrSz = estHdrSz;
   staRspInfo->boReport.staPduPrsnt = staPduPrsnt;
#endif

   staRspInfo->boReport.bo = bo;
   staRspInfo->cellId      = rbCb->rlcId.cellId;
   staRspInfo->rnti        = rbCb->rlcId.ueId;
   staRspInfo->lcId        = rbCb->lch.lChId;

   /* If trace flag is enabled send the trace indication */
   if(gCb->init.trc == TRUE)
   {
      /* Populate the trace params */
      kwLmmSendTrc(gCb,EVTRGUDSTARSP, NULLP);
   }

   KwLiRguDStaRsp(&rguSap->pst,rguSap->spId,staRspInfo);

   RETVALUE(ROK);
}
/**
 *
 * @brief 
 * 
 *        Handler for emptying the SDU queue. 
 * 
 * @b Description:
 *
 *        This function is used to empty the SDU queue when
 *        a re-establishment request is received from the 
 *        upper layer.
 *
 *  @param[in]  sduQ        SDU queue to be emptied
 *
 *  @return  S16
 *      -# ROK 
 */
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
#ifdef ANSI
PUBLIC S16 kwUtlEmptySduQ
(
KwCb      *gCb,
KwDlRbCb    *rbCb,   /* KwRbCb */ 
CmLListCp *sduQ  /* SDU queue */
)
#else
PUBLIC S16 kwUtlEmptySduQ(gCb,rbCb, sduQ)
KwCb      *gCb;
KwDlRbCb    *rbCb;  /* KwRbCb */   
CmLListCp *sduQ;  /* SDU queue */
#endif
#else
#ifdef ANSI
PUBLIC S16 kwUtlEmptySduQ
(
KwCb      *gCb,
CmLListCp *sduQ  /* SDU queue */
)
#else
PUBLIC S16 kwUtlEmptySduQ(gCb,sduQ)
KwCb      *gCb;
CmLListCp *sduQ;  /* SDU queue */
#endif
#endif
{
   CmLList *firstNode;                  /* First Node in SDU Queue */
   KwSdu   *sdu;                        /* Pointer to a SDU */
#ifdef LTE_L2_MEAS_RLC
   CmLListCp   *sduSnMapQ;             /* SDU Sequence number map queue */
   CmLList     *firstSduSnMap;         /* First Node in SDU SnMap Queue */
   KwSduSnMap  *sduSnMap;              /* SDU Sn Map */
#endif

   TRC2(kwUtlEmptySduQ)
#ifdef LTE_L2_MEAS_RLC
   sduSnMapQ = NULLP;
   firstSduSnMap = NULLP;
   sduSnMap = NULLP;
#endif
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwUtlEmptySduQ(sduQ)\n"));
#endif

#ifdef LTE_L2_MEAS_RLC
   sduSnMapQ = &rbCb->sduSnMapQ;
   CM_LLIST_FIRST_NODE(sduSnMapQ, firstSduSnMap);

   while(firstSduSnMap)
   {
      sduSnMap = (KwSduSnMap *)firstSduSnMap->node;
      if(sduSnMap != NULLP)
      {
         cmLListDelFrm(&(rbCb->sduSnMapQ), &(sduSnMap->lstEnt));
         KW_FREE(gCb,sduSnMap, sizeof(KwSduSnMap));
      }
      CM_LLIST_FIRST_NODE(sduSnMapQ, firstSduSnMap);
   }
#endif
   CM_LLIST_FIRST_NODE( sduQ,firstNode );
   while(firstNode)
   { 
      sdu = (KwSdu *)firstNode->node;
      KW_RMV_SDU(gCb,sduQ,sdu);   
      CM_LLIST_FIRST_NODE(sduQ, firstNode);
   }
   RETVALUE(ROK);
}

/**
 *
 * @brief 
 * 
 *        Handler for calculating the LI length for a SDU. 
 * 
 * @b Description:
 *
 *        This function is used to calculate the LI length
 *        which has to be substracted from the pduSize to 
 *        correctly match the formed PDU(s) size with the 
 *        size requested by MAC.
 *
 *  @param[in]  numLi               Number of LIs already present 
 *  @param[in]  msgLen              Size of the SDU
 *  @param[in]  pduSz               Size of the pDU to be formed
 *
 *  @return  S16
 *      -# ROK 
 */
#ifdef ANSI
PUBLIC S16 kwUtlCalcLiForSdu
(
KwCb   *gCb,
U16     numLi,                          /* Number of LIs */
MsgLen  msgLen,                         /* SDU size */
S16     *pduSz                          /* Remaining PDU size */
)
#else
PUBLIC S16 kwUtlCalcLiForSdu(gCb,numLi,msgLen,pduSz)
KwCb   *gCb;
U16     numLi;                          /* Number of LIs */
MsgLen  msgLen;                         /* SDU size */
S16     *pduSz;                         /* Remaining PDU size */
#endif 
{
   TRC2(kwUtlCalcLiForSdu)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_DUT | KW_DBGMASK_BRIEF | KW_DBGMASK_DL),
          (gCb->init.prntBuf, "kwUtlCalcLiForSdu(rbCb, msgLen, pduSz)\n"));
#endif
   if (*pduSz > msgLen)
   {
      if (msgLen < 2048)
      {
         if (numLi % 2 == 0)
            *pduSz -= 2;
         else
            *pduSz -= 1;
      }
   }
   RETVALUE(ROK);
}


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
PUBLIC Void kwUtlFreeDlRbCb
(
KwCb                *gCb,
KwDlRbCb            *rbCb
)
#else
PUBLIC Void kwUtlFreeRbCb(gCb,rbCb)
KwCb                *gCb;
KwDlRbCb            *rbCb;
#endif
{
   KwRetx            *retx = NULLP;
   KwSn              sn = 0;
   KwSn              mVtS = 0;
   KwSn              mSn = 0;

   TRC2(kwUtlFreeDlRbCb)
#ifdef DEBUGP
   KWDBGP(gCb,
          (KW_DBGMASK_DUT | KW_DBGMASK_BRIEF | KW_DBGMASK_DL | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwUtlFreeRbCb(rbCb)\n")); 
#endif
   if ( rbCb->mode == CM_LTE_MODE_UM )
   {
      if (rbCb->dir & KW_DIR_DL)
      {
/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
         kwUtlEmptySduQ(rbCb, &rbCb->m.umDl.sduQ);
#else
         kwUtlEmptySduQ(gCb,&rbCb->m.umDl.sduQ);
#endif
      }
   }
   else if (rbCb->mode == CM_LTE_MODE_AM)
   {

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
      kwUtlEmptySduQ(rbCb, &rbCb->m.amDl.sduQ);
#else
      kwUtlEmptySduQ(gCb,&rbCb->m.amDl.sduQ);
#endif

      sn = AMDL.txSn;
      MODAMR(sn, mSn, AMDL.vtA);
      MODAMR(AMDL.vtS, mVtS, AMDL.vtA);

      while (mSn <= mVtS)
      {
         if (AMDL.txBuf[mSn] && AMDL.txBuf[mSn]->pdu)
         {
            KW_FREE_BUF(AMDL.txBuf[mSn]->pdu);
            KW_FREE(gCb,AMDL.txBuf[mSn], sizeof(KwTx));
         }
         sn++;
         MODAMR(sn, mSn, AMDL.vtA);
      }
      KW_FREE(gCb,AMDL.txBuf, (KW_AM_WIN_SZ * 2)* sizeof(KwTx*));

      KW_LLIST_FIRST_RETX(AMDL.retxLst, retx);
      while (retx)
      {
         KW_FREE_BUF(retx->seg);

         cmLListDelFrm(&AMDL.retxLst, &retx->lstEnt);
         KW_FREE(gCb,retx, sizeof(KwRetx));

         KW_LLIST_FIRST_RETX(AMDL.retxLst, retx);
      }
      AMDL.nxtRetx = NULLP;
      /* Venki */
      if(TRUE == kwChkTmr(gCb,(PTR)rbCb,KW_EVT_AMDL_POLL_RETX_TMR))
      {
         kwStopTmr(gCb,(PTR)rbCb, KW_EVT_AMDL_POLL_RETX_TMR);
      }

/* kw005.201 added support for L2 Measurement */
#ifdef LTE_L2_MEAS_RLC
      kwUtlEmptySduQ(gCb,rbCb, &rbCb->m.tm.sduQ);
#else
      kwUtlEmptySduQ(gCb,&rbCb->m.tm.sduQ);
#endif
   }

   RETVOID;
} /* kwUtlFreeRbCb */

/********************************************************************30**
         End of file:     kw_utl_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:55 2014
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
*********************************************************************91*/


