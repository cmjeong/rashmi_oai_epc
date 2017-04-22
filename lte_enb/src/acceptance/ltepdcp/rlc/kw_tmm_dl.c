

/**********************************************************************

     Name:     LTE-RLC Layer 
  
     Type:     C file
  
     Desc:     Source code for RLC Transparent mode assembly and
               reassembly.This file contains following functions
                
                  --kwTmmQSdu
                  --kwTmmSndToLi
                  --kwTmmRcvFrmLi
                  --kwTmmReEstablish 

     File:     gp_tmm.c

     Sid:      kw_tmm_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:49 2014

     Prg:      vp 

**********************************************************************/
/** @file gp_tmm.c
@brief RLC Transparent Mode module
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
#include "kw_env.h"        /* RLC environment options */

#include "kw.h"            /* RLC defines */
#include "kw_err.h"            /* RLC defines */
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
#include "lkw.x"           /* LKW */
#include "ckw.x"           /* CKW */
#include "kwu.x"           /* KWU */
#include "rgu.x"           /* RGU */

#include "kw.x"
#include "kw_dl.x"

PRIVATE S16 kwTmmSndStaRsp ARGS((KwCb *gCb, KwDlRbCb *rbCb, 
                                 MsgLen bo, KwuDatReqInfo *datReqInfo));


/** @addtogroup tmmode */
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
 *  @param[in] rbCb         RB control block. 
 *  @param[in] datReqInfo   Data Request Information.
 *  @param[in] mBuf         SDU Buffer.
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */
#ifdef ANSI
PUBLIC S16 kwTmmQSdu
(
KwCb     *gCb,
KwDlRbCb *rbCb,                     /* Rb Control Block */
KwuDatReqInfo *datReqInfo,        /* Data Request Information */
Buffer *mBuf                      /* SDU buffer */
)
#else
PUBLIC S16 kwTmmQSdu(gCb,rbCb,datReqInfo,mBuf)
KwCb   *gCb;
KwDlRbCb *rbCb;                     /* Rb Control Block */
KwuDatReqInfo *datReqInfo;        /* Data Request Information */
Buffer *mBuf;                     /* SDU buffer */
#endif
{
   KwSdu   *sdu;                  /* SDU */
   MsgLen len;                    /* SDU length */
 
   TRC2(kwTmmQSdu) 
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_TM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL), (gCb->init.prntBuf,
           "kwTmmQSdu(rbCb, datReqInfo, mBuf)\n")); 
#endif

   KW_ALLOC(gCb,sdu,sizeof(KwSdu));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( sdu == NULLP )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW200, (ErrVal) RFAILED,
                       "KW_ALLOC failed for sdu.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
#ifdef CCPU_OPT   
   if ( rbCb->lch.lChType == CM_LTE_LCH_BCCH || 
        rbCb->lch.lChType == CM_LTE_LCH_PCCH )
   {
      sdu->mode.tm.sfn = datReqInfo->tm.tmg.sfn;
      sdu->mode.tm.subframe = datReqInfo->tm.tmg.subframe;
   }
   else
   {
      sdu->mode.tm.rnti = datReqInfo->tm.rnti;
   }
#endif

   SFndLenMsg(mBuf,&len); 
   sdu->mBuf = mBuf;
   sdu->sduSz   = len;   
   
   cmLListAdd2Tail(&(rbCb->m.tm.sduQ), &(sdu->lstEnt));  
   sdu->lstEnt.node = (PTR)sdu; 

   kwTmmSndStaRsp(gCb,rbCb,len,datReqInfo); 
   /* kw002.201 Removed freeing of datReq to free from correct region at caller */

   RETVALUE(ROK);

}
/**
*  @brief 
*
*         Handler to form a pdu and send it to the lower layer.
* 
*  @b Description: 
* 
*         This function forms one pdu from the first SDU in the
*         SDU queue and sends it to the lower layer.
*             
*  @param[in] rbCb RB control block. 
*
*  @return  S16
*       -# ROK 
*       -# RFAILED         
*/

#ifdef ANSI
PUBLIC S16 kwTmmSndToLi
(
KwCb      *gCb,
KwDlRbCb    *rbCb                  /* Rb Control Block */
)
#else
PUBLIC S16 kwTmmSndToLi(gCb,rbCb)
KwCb   *gCb;
KwDlRbCb *rbCb;                    /* Rb Control Block */
#endif
{
   CmLList *firstNode;            /* Current Link List Node */
   KwSdu   *sdu;                  /* SDU */
   RguCDatReqInfo  *cDatReqInfo;  /* Data Request Information */
   KwRguSapCb *rgSap;             /* MAC SAP */
   MsgLen   len;                  /* SDU len */
   CmLListCp *sduQ;               /* SDU queue */
   /* kw005.201, updated for statistics */
   KwKwuSapCb   *kwuSapCb;         /* KWU SapCb */

   TRC2(kwTmmSndToLi)
#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_TM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL), (gCb->init.prntBuf,
           "kwTmmSndToLi(rbCb)\n"));
#endif
   sduQ = &(rbCb->m.tm.sduQ);

   CM_LLIST_FIRST_NODE( sduQ,firstNode );

   if ( firstNode == NULLP )
   {
      /* Log an error saying the SDU queue is empty */
#ifdef DEBUGP
      KWDBGP(gCb,(KW_DBGMASK_TM | KW_DBGMASK_ERROR| KW_DBGMASK_DL),
                  (gCb->init.prntBuf,"SDU Queue is empty \n"));
#endif
      RETVALUE(RFAILED);
   }
   sdu = (KwSdu *)firstNode->node;
   SFndLenMsg(sdu->mBuf,&len);

   KW_ALLOC(gCb,cDatReqInfo,(Size)sizeof(RguCDatReqInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( cDatReqInfo == NULLP )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW201, (ErrVal) RFAILED,
                       "KW_ALLOC failed for cDatReqInfo.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
#ifdef CCPU_OPT
   
   if ( rbCb->lch.lChType == CM_LTE_LCH_BCCH ||  
        rbCb->lch.lChType == CM_LTE_LCH_PCCH )
   {
      cDatReqInfo->u.timeToTx.sfn = sdu->mode.tm.sfn;
      cDatReqInfo->u.timeToTx.subframe = sdu->mode.tm.subframe; 
   }
   else
   {
      cDatReqInfo->u.rnti = sdu->mode.tm.rnti;
   }
#endif 
   cDatReqInfo->pdu = sdu->mBuf; 
   cDatReqInfo->transId = rbCb->transId;
   cDatReqInfo->cellId  = rbCb->rlcId.cellId;
   cDatReqInfo->lcId   = rbCb->lch.lChId; 
   cDatReqInfo->lcType = rbCb->lch.lChType; 

   /* kw005.201 ccpu00117318, updating the statistics */
   gCb->genSts.bytesSent += sdu->sduSz;
   gCb->genSts.pdusSent++;
   kwuSapCb = (KwKwuSapCb *)(gCb->u.dlCb->kwuDlSap + rbCb->kwuSapId);
   kwuSapCb->sts.sduTx++;

   /* remove SDU from queue */ 
   sdu->mBuf = NULLP;
   cmLListDelFrm(sduQ,&sdu->lstEnt); 
   KW_FREE(gCb,sdu, sizeof(KwSdu));

   rgSap = &(gCb->u.dlCb->rguDlSap);

   /* If trace flag is enabled send the trace indication */
   if(gCb->init.trc == TRUE)
   {
      /* Populate the trace params */
      kwLmmSendTrc(gCb,EVTRGUCDATREQ, NULLP);
   }

   KwLiRguCDatReq (&rgSap->pst, rgSap->spId, cDatReqInfo);
   
   RETVALUE(ROK); 
   
} /* kwTmmSndToLi */

/**
 *
 * @brief 
 * 
 *        Handler to process the re-establishment request received from the upper layer. 
 *
 * @b Description: 
 *
 *        This function empties the SDU queue for the RB in the downlink.
 *            
 *  @param[in] rbCb  RB control block. 
 *
 *  @return  S16
 *      -# ROK 
 *       
 **************************************************************************************/
#ifdef ANSI
PUBLIC S16 kwDlTmmReEstablish
(
KwCb      *gCb,
KwDlRbCb    *rbCb         /* RB Control Block */
)
#else
PUBLIC S16 kwDlTmmReEstablish(gCb,rbCb)
KwCb   *gCb;
KwDlRbCb *rbCb;            /* RB Control Block */
#endif
{

   TRC2(kwDlTmmReEstablish)
#ifdef DEBUGP  
   KWDBGP(gCb,(KW_DBGMASK_TM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL | KW_DBGMASK_UL),
          (gCb->init.prntBuf, "kwTmmReEstablish(rbCb)\n"));
#endif
#ifdef LTE_L2_MEAS
      kwUtlEmptySduQ(rbCb, &rbCb->m.tm.sduQ);
#else
      kwUtlEmptySduQ(gCb,&rbCb->m.tm.sduQ);
#endif

   RETVALUE(ROK);
}
/**
 *
 * @brief 
 *
 *        Handler to send Status Response to the lower layer.
 *
 * @b Description: 
 *
 *        This function is used to the BO to the lower layer after
 *        receiving a data request from the upper layer. 
 *            
 *  @param[in] rbCb         RB control block. 
 *  @param[in] datReqInfo   Data Request Information.
 *  @param[in] mBuf         SDU Buffer.
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 *
 */

#ifdef ANSI
PRIVATE S16 kwTmmSndStaRsp
(
KwCb     *gCb,
KwDlRbCb *rbCb,                           /* RB Control Block */
MsgLen    bo,                             /* Buffer Occupancy */
KwuDatReqInfo *datReqInfo               /* Status response Information */
)
#else
PRIVATE S16 kwTmmSndStaRsp(rbCb,bo,datReqInfo)
KwCb      *gCb;
KwDlRbCb  *rbCb;                       /* RB Control Block */
MsgLen     bo;                          /* Buffer Occupancy */
KwuDatReqInfo *datReqInfo;              /* Status response Information */
#endif
{
   RguCStaRspInfo  *staRspInfo;         /* Status Response Information */
   KwRguSapCb *rguSap;                  /* SAP Information */

   TRC3(kwTmmSndStaRsp)

#ifdef DEBUGP
   KWDBGP(gCb,(KW_DBGMASK_TM | KW_DBGMASK_BRIEF | KW_DBGMASK_DL ),
          (gCb->init.prntBuf, "kwTmmSndStaRsp(rbCb, bo, datReqInfo)\n"));
#endif
   rguSap = &(gCb->u.dlCb->rguDlSap);

   KW_ALLOC(gCb,staRspInfo,sizeof(RguCStaRspInfo));
#if (ERRCLASS & ERRCLS_ADD_RES)
   if ( staRspInfo == NULLP )
   {
      KWLOGERROR(gCb,ERRCLS_ADD_RES, EKW203, (ErrVal) RFAILED,
                       "KW_ALLOC failed for stRspInfo.");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS & ERRCLS_ADD_RES */
   staRspInfo->bo = bo;
   staRspInfo->cellId = rbCb->rlcId.cellId;
   staRspInfo->lcId   = rbCb->lch.lChId;
   staRspInfo->lcType = rbCb->lch.lChType;
#ifdef CCPU_OPT    
   if ( rbCb->lch.lChType == CM_LTE_LCH_BCCH ||
        rbCb->lch.lChType == CM_LTE_LCH_PCCH )
   {
      staRspInfo->u.timeToTx.sfn      = datReqInfo->tm.tmg.sfn;
      staRspInfo->u.timeToTx.subframe = datReqInfo->tm.tmg.subframe;
   }
   else if ( rbCb->lch.lChType == CM_LTE_LCH_CCCH )
   {
       staRspInfo->u.rnti = datReqInfo->tm.rnti;
   }
#endif

   /* If trace flag is enabled send the trace indication */
   if(gCb->init.trc == TRUE)
   {
      /* Populate the trace params */
      kwLmmSendTrc(gCb,EVTRGUCSTARSP, NULLP);
   }

   KwLiRguCStaRsp(&rguSap->pst,rguSap->spId,staRspInfo);

   RETVALUE(ROK);
} /* kwTmmSndStaRsp */

#ifdef _cplusplus
}
#endif
/*@}*/
/********************************************************************30**
         End of file:     kw_tmm_dl.c@@/main/TeNB_Main_BR/4 - Thu Apr 24 17:07:49 2014
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
/main/4      kw005.201 ap   1. Updating the statistics.                       
*********************************************************************91*/

