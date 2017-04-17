


/************************************************************************
 
     Name:     LTE-MAC layer
  
     Type:     C source file
  
     Desc:     C source code for Entry point fucntions
  
     File:     rg_dhm.c
  
     Sid:      rgac_tfucb.c@@/main/3 - Sat Jul 30 02:21:07 2011
  
     Prg:      ps
  
**********************************************************************/

/** @file rg_dhm.c
@brief APIs related to Downlink HARQ.
*/


/* Common include file for all acceptance files */
#include "rgac_acc.x"
#include "rg.h"

EXTERN Bool startPfsSim;
/* ##################################################### */
#ifdef ANSI
PUBLIC S16 TfUiTfuSchBndReq
(
 Pst     *pst,
 SuId    suId,
 SpId    spId
 )
#else
PUBLIC S16 TfUiTfuSchBndReq (pst, suId, spId)
 Pst     *pst;
 SuId    suId;
 SpId    spId;
#endif
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   RgAccMsgQElm   *rgMsg;

   TRC2(TfUiTfuSchBndReq)

   CMXTA_DBG_PARAM((_cmxtap, "TfUiTfuSchBndReq():\n"));

   /* A single save message sort of function wont work for this interface as we
    * have primitives with very different set of parameters, so lets just save
    * whatever we need separately.
    */

   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuSchBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
   pst->event = EVTTFUSCHBNDREQ;

   CMXTA_CPY((U8 *)&(qElm.pst), (U8*)pst, sizeof(Pst));

   rgMsg->u.tfuInfo.suId = suId;
   rgMsg->u.tfuInfo.spId = spId;
   qElm.msgFreeFun = rgAcUtlTfuFreeFunc;
   qElm.data = (Void *)rgMsg;

   if ((tcCb = rgAcUtlFindTcCb()) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuSchBndReq(): tcCb not found, msg dropped\n"));
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      RETVALUE(ROK);
   }

   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);
   RETVALUE(ROK);

} /* end of TfUiTfuSchBndReq */


#ifdef ANSI
PUBLIC S16 TfUiTfuSchUbndReq
(
 Pst     *pst,
 SpId    spId,
 Reason  reason
 )
#else
PUBLIC S16 TfUiTfuSchUbndReq (pst, spId, reason)
 Pst     *pst;
 SpId    spId;
 Reason  reason;
#endif
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   RgAccMsgQElm   *rgMsg;

   TRC2(TfUiTfuSchUbndReq)

   UNUSED(reason);
   CMXTA_DBG_PARAM((_cmxtap, "TfUiTfuSchUbndReq():\n"));

   /* A single save message sort of function wont work for this interface as we
    * have primitives with very different set of parameters, so lets just save
    * whatever we need separately.
    */

   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfSchUbndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
   pst->event = EVTTFUSCHUBNDREQ;

   CMXTA_CPY((U8 *)&(qElm.pst), (U8*)pst, sizeof(Pst));

   rgMsg->u.tfuInfo.spId = spId;
   qElm.msgFreeFun = rgAcUtlTfuFreeFunc;
   qElm.data = (Void *)rgMsg;

   if ((tcCb = rgAcUtlFindTcCb()) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuSchUbndReq(): tcCb not found, msg dropped\n"));
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      RETVALUE(ROK);
   }

   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);
   RETVALUE(ROK);

} /* end of TfUiTfuSchUbndReq */

#ifdef ANSI
PUBLIC S16 TfUiTfuBndReq
(
 Pst     *pst,
 SuId    suId,
 SpId    spId
 )
#else
PUBLIC S16 TfUiTfuBndReq (pst, suId, spId)
 Pst     *pst;
 SuId    suId;
 SpId    spId;
#endif
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   RgAccMsgQElm   *rgMsg;

   TRC2(TfUiTfuBndReq)

   CMXTA_DBG_PARAM((_cmxtap, "TfUiTfuBndReq():\n"));

   /* A single save message sort of function wont work for this interface as we
    * have primitives with very different set of parameters, so lets just save
    * whatever we need separately.
    */

   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
   pst->event = EVTTFUBNDREQ;

   CMXTA_CPY((U8 *)&(qElm.pst), (U8*)pst, sizeof(Pst));

   rgMsg->u.tfuInfo.suId = suId;
   rgMsg->u.tfuInfo.spId = spId;
   qElm.msgFreeFun = rgAcUtlTfuFreeFunc;
   qElm.data = (Void *)rgMsg;

   if ((tcCb = rgAcUtlFindTcCb()) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuBndReq(): tcCb not found, msg dropped\n"));
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      RETVALUE(ROK);
   }

   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);
   RETVALUE(ROK);

} /* end of TfUiTfuBndReq */


#ifdef ANSI
PUBLIC S16 TfUiTfuUbndReq
(
 Pst     *pst,
 SpId    spId,
 Reason  reason
 )
#else
PUBLIC S16 TfUiTfuUbndReq (pst, spId, reason)
 Pst     *pst;
 SpId    spId;
 Reason  reason;
#endif
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   RgAccMsgQElm   *rgMsg;

   TRC2(TfUiTfuUbndReq)

   UNUSED(reason);
   CMXTA_DBG_PARAM((_cmxtap, "TfUiTfuUbndReq():\n"));

   /* A single save message sort of function wont work for this interface as we
    * have primitives with very different set of parameters, so lets just save
    * whatever we need separately.
    */

   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuBndReq(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }
   pst->event = EVTTFUUBNDREQ;

   CMXTA_CPY((U8 *)&(qElm.pst), (U8*)pst, sizeof(Pst));

   rgMsg->u.tfuInfo.spId = spId;
   qElm.msgFreeFun = rgAcUtlTfuFreeFunc;
   qElm.data = (Void *)rgMsg;

   if ((tcCb = rgAcUtlFindTcCb()) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuBndReq(): tcCb not found, msg dropped\n"));
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      RETVALUE(ROK);
   }

   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);
   RETVALUE(ROK);

} /* end of TfUiTfuBndReq */

EXTERN Bool isPfsSim;

 /** @brief This function handles the reception request
  * @param  pst   Pst structure
  * @param  spId  SpId
  * @param  recpReq
  * @return 
  * -# ROK
  * -# RFAILED
  */
#ifdef ANSI
PUBLIC S16 TfUiTfuRecpReq
(
 Pst                    *pst,
 SpId                   spId,
 TfuRecpReqInfo         *recpReq
)
#else
PUBLIC S16 TfUiTfuRecpReq (pst,  spId,  recpReq)
 Pst                    *pst;
 SpId                   spId;
 TfuRecpReqInfo         *recpReq;
#endif
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   RgAccMsgQElm   *rgMsg;
   RgAcTfuInfo    *tfuInfo;

   TRC2(TfUiTfuRecpReq)

   /* Not adding to queue when recpReq has no info */
   if (recpReq->ueRecpReqLst.count == 0)
   {
      rgAcUtlFreeEvnt ((Data*)recpReq);
      RETVALUE(ROK);
   }
   if(TRUE == startPfsSim)
   {
      rgAcUtlFreeEvnt ((Data*)recpReq);
      RETVALUE(ROK);
   }

   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuRecpReq(): resource error\n"));
      RETVALUE(RFAILED);
   }
   pst->event = EVTTFURECPREQ;

   CMXTA_CPY((U8 *)&(qElm.pst), (U8*)pst, sizeof(Pst));

   rgMsg->u.tfuInfo.spId = spId;
   qElm.msgFreeFun = rgAcUtlTfuFreeFunc;
   qElm.data = (Void *)rgMsg;
   tfuInfo = &(rgMsg->u.tfuInfo);

   tfuInfo->u.recpReqInfo = recpReq;
   tfuInfo->type = EVTTFURECPREQ;
   tfuInfo->timingInfo = recpReq->timingInfo;

   if ((tcCb = rgAcUtlFindTcCb()) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuRecpReq(): tcCb not found, msg dropped\n"));
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      RETVALUE(ROK);
   }

   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);
   RETVALUE(ROK);
} /* end of  TfUiTfuRecpReq*/ 

 /** @brief This function handles the control request sent from scheduler to
  * Physical layer.
  * @param  pst   Pst structure
  * @param  spId  SpId
  * @param  recpReq
  * @return 
  * -# ROK
  * -# RFAILED
  */
#ifdef ANSI
PUBLIC S16 TfUiTfuCntrlReq
(
 Pst                    *pst,
 SpId                   spId,
 TfuCntrlReqInfo        *cntrlReq
)
#else
PUBLIC S16 TfUiTfuCntrlReq (pst,  spId,  cntrlReq)
 Pst                    *pst;
 SpId                   spId;
 TfuCntrlReqInfo        *cntrlReq;
#endif
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   RgAccMsgQElm   *rgMsg;
   RgAcTfuInfo    *tfuInfo;

   TRC2(TfUiTfuCntrlReq)

   if(TRUE == startPfsSim)
   {
      rgAcUtlFreeEvnt ((Data*)cntrlReq);
      RETVALUE(ROK);
   }

   if (rgAccCb.directives.validateCfi != TRUE)
   {
      /* Check if its only CFI then skip storing, just free and return. 
       */
      if ((cntrlReq->ulPdcchLst.count == 0) &&
         (cntrlReq->dlPdcchLst.count == 0) &&
         (cntrlReq->phichLst.count == 0))
      {
         rgAcUtlFreeEvnt ((Data*)cntrlReq);
         RETVALUE(ROK);
      }
   }
   CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
   if (rgMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuCntrlReq(): resource error\n"));
      RETVALUE(RFAILED);
   }
   pst->event = EVTTFUCNTRLREQ;

   CMXTA_CPY((U8 *)&(qElm.pst), (U8*)pst, sizeof(Pst));

   rgMsg->u.tfuInfo.spId = spId;
   qElm.msgFreeFun = rgAcUtlTfuFreeFunc;
   qElm.data = (Void *)rgMsg;
   tfuInfo = &(rgMsg->u.tfuInfo);

   tfuInfo->u.cntrlReqInfo = cntrlReq;
   tfuInfo->type = EVTTFUCNTRLREQ;
#ifdef RG_ULSCHED_AT_CRC 
   if(!cntrlReq->dlPdcchLst.count)
   {
      tfuInfo->timingInfo = cntrlReq->ulTiming;
   }
   else
#endif
   {
      tfuInfo->timingInfo = cntrlReq->dlTiming;
   }

   if ((tcCb = rgAcUtlFindTcCb()) == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "TfUiTfuCntrlReq(): tcCb not found, msg dropped\n"));
      CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
      RETVALUE(ROK);
   }

   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);
   RETVALUE(ROK);
} /* end of  TfUiTfuCntrlReq*/ 


 /** @brief This function handles the Data request sent from MAC to Physical
  * layer.
  * @param  pst   Pst structure
  * @param  spId  SpId
  * @param  datReq
  * @return 
  * -# ROK
  * -# RFAILED
  */
#ifdef ANSI
PUBLIC S16 TfUiTfuDatReq
(
 Pst                    *pst,
 SpId                   spId,
 TfuDatReqInfo         *datReq
)
#else
PUBLIC S16 TfUiTfuDatReq (pst,  spId,  datReq)
 Pst                    *pst;
 SpId                   spId;
 TfuDatReqInfo          *datReq;
#endif
{
   CmXtaTCCb      *tcCb;
   CmXtaMsgQElm   qElm;
   RgAccMsgQElm   *rgMsg;
   RgAcTfuInfo    *tfuInfo;

   TRC2(TfUiTfuDatReq)

   if(TRUE == startPfsSim)
   {
      CmLList              *node;
      TfuDatReqPduInfo     *pduInfo;

      node = datReq->pdus.first;
      while (node)
      {
         pduInfo = (TfuDatReqPduInfo *)node->node;

         if ((pduInfo->rnti == RG_P_RNTI) || (pduInfo->rnti == RG_SI_RNTI))
         {
            SPutMsg(pduInfo->mBuf[0]);
            pduInfo->mBuf[0] = NULLP;
            cmLListDelFrm(&datReq->pdus, &pduInfo->lnk);
         }
         else
         {
            if (pduInfo->mBuf[0] != NULLP)
            {
               SPutMsg(pduInfo->mBuf[0]);
               pduInfo->mBuf[0] = NULLP;
            }
            if (pduInfo->mBuf[1] != NULLP)
            {
               SPutMsg(pduInfo->mBuf[1]);
               pduInfo->mBuf[1] = NULLP;
            }
            cmLListDelFrm(&datReq->pdus, &pduInfo->lnk); 
         }   
         node = node->next;
      }
      //startPfsSim = FALSE;
      (Void)cmFreeMem((Ptr)datReq);     
      RETVALUE(ROK);
   }
   /* Adding the real Dat Req to queue. Discarding the dummy Dat req*/
   if((datReq->pdus.count) || (datReq->bchDat.pres == TRUE))
   {
      CMXTA_ALLOC(&rgMsg, sizeof (RgAccMsgQElm));
      if (rgMsg == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "TfUiTfuDatReq(): resource error\n"));
         RETVALUE(RFAILED);
      }
      pst->event = EVTTFUDATREQ;

      CMXTA_CPY((U8 *)&(qElm.pst), (U8*)pst, sizeof(Pst));

      rgMsg->u.tfuInfo.spId = spId;
      qElm.msgFreeFun = rgAcUtlTfuFreeFunc;
      qElm.data = (Void *)rgMsg;
      tfuInfo = &(rgMsg->u.tfuInfo);

      tfuInfo->u.datReqInfo = datReq;
      tfuInfo->type = EVTTFUDATREQ;
      tfuInfo->timingInfo = datReq->timingInfo;

      if ((tcCb = rgAcUtlFindTcCb()) == NULLP)
      {
         CMXTA_DBG_ERR((_cmxtap, "TfUiTfuDatReq(): tcCb not found, msg dropped\n"));
         CMXTA_FREE(rgMsg, sizeof (RgAccMsgQElm));
         RETVALUE(ROK);
      }
      (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);
      if (tcCb->busy == FALSE)
         cmXtaTCEngine(tcCb);
   }
   else
   {
      (Void)cmFreeMem((Ptr)datReq);     
   }
   RETVALUE(ROK);
} /* end of  TfUiTfuDatReq*/ 





/**********************************************************************
 
         End of file:     rgac_tfucb.c@@/main/3 - Sat Jul 30 02:21:07 2011
 
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
/main/1      ---     ps              1. Initial Release.
/main/2      ---     ps              1. LTE MAC 2.1 release
/main/2+   rg001.201 apany           1. Not storing TfuRecpReq when it
                                        contains no UE info
/main/3      ---     nu              1. Updated for release LTE-MAC 3.1.
$SID$        ---     rt              1. LTE MAC 4.1 release
*********************************************************************91*/
