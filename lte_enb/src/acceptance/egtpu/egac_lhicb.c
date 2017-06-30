
/********************************************************************20**
  
     Name:     TCP UDP Convegence Layer Sample Stack Manager
  
     Type:     C source file
  
     Desc:     Sample code for Management Interface primitives supplied 
               by TRILLIUM
              
     File:     egac_lhicb.c
  
     Sid:      egac_lhicb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:37 2015

     Prg:      an
  
*********************************************************************21*/
/* header include files (.h) */

#include "egac_acc.x"
#include "egac_lhi.x"

/*
*     interface functions to layer management service user
*/
/*
*
*       Fun:   Configuration Confirm
*
*       Desc:  This function is used by to present configuration confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_lhicb.c
*
*/
 
#ifdef ANSI
PUBLIC S16 egAcSmMiLhiCfgCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* configuration */
)
#else
PUBLIC S16 egAcSmMiLhiCfgCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* configuration */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLhiCfgCfm)

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiCfgCfm(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiCfgCfm(): txnId(%ld)\n", cfm->hdr.transId));
#endif
#endif /* LMINT3 */

   /*-- Update Event --*/
   pst->event = EVTLHICFGCFM;

   egAcUtlLhiSendMsg(pst, cfm, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of egAcSmMiLhiCfgCfm */


/*
*
*       Fun:   Control Confirm
*
*       Desc:  This function is used by to present control confirm
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcSmMiLhiCntrlCfm
(
Pst     *pst,          /* post structure */
HiMngmt *cfm           /* control */
)
#else
PUBLIC S16 egAcSmMiLhiCntrlCfm(pst, cfm)
Pst     *pst;          /* post structure */
HiMngmt *cfm;          /* control */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLhiCntrlCfm)

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiCntrlCfm(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiCntrlCfm(): txnId(%ld)\n", cfm->hdr.transId));
#endif
#endif

   /*-- Update Event --*/
   pst->event = EVTLHICNTRLCFM;

   egAcUtlLhiSendMsg(pst, cfm, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of egAcSmMiLhiCntrlCfm */

/*
*
*       Fun:   Status Indication
*
*       Desc:  This function is used by to present  uneglicited status 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 egAcSmMiLhiStaInd
(
Pst     *pst,           /* post structure */
HiMngmt *usta           /* uneglicited status */
)
#else
PUBLIC S16 egAcSmMiLhiStaInd(pst, usta)
Pst     *pst;           /* post structure */
HiMngmt *usta;          /* uneglicited status */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLhiStaInd)

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiStaInd(): txnId(%d)\n", usta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiStaInd(): txnId(%ld)\n", usta->hdr.transId));
#endif
#endif

   /*-- Update Event --*/
   pst->event = EVTLHISTAIND;

   egAcUtlLhiSendMsg(pst, usta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of egAcSmMiLhiStaInd */


/*
*
*       Fun:   Trace Indication
*
*       Desc:  This function is used to present trace
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 egAcSmMiLhiTrcInd
(
Pst *pst,               /* post structure */
HiMngmt *trc,           /* trace */
Buffer *mBuf            /* message buffer */
)
#else
PUBLIC S16 egAcSmMiLhiTrcInd(pst, trc, mBuf)
Pst *pst;               /* post structure */
HiMngmt *trc;           /* trace */
Buffer *mBuf;           /* message buffer */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLhiTrcInd)

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiTrcInd(): txnId(%d)\n", trc->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiTrcInd(): txnId(%ld)\n", trc->hdr.transId));
#endif
#endif

   /*-- Update Event ----*/
   pst->event = EVTLHITRCIND;

   egAcUtlLhiSendMsg(pst, trc, mBuf);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of egAcSmMiLhiTrcInd */

/*
*
*       Fun:   Statistics Confirm
*
*       Desc:  This function is used to present eglicited statistics 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 egAcSmMiLhiStsCfm
(
Pst       *pst,         /* post structure */
HiMngmt   *sts          /* confirmed statistics */
)
#else
PUBLIC S16 egAcSmMiLhiStsCfm(pst, sts)
Pst       *pst;         /* post structure */
HiMngmt   *sts;         /* confirmed statistics */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLhiStsCfm)

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiStsCfm(): txnId(%d)\n", sts->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiStsCfm(): txnId(%ld)\n", sts->hdr.transId));
#endif
#endif

   /*-- Update Event --*/
   pst->event = EVTLHISTSCFM;

   egAcUtlLhiSendMsg(pst, sts, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of egAcSmMiLhiStsCfm */

/*
*
*       Fun:   Status Confirm
*
*       Desc:  This function is used to present eglicited status 
*              information to Layer Management.
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_lhicb.c
*
*/
  
#ifdef ANSI
PUBLIC S16 egAcSmMiLhiStaCfm
(
Pst     *pst,           /* post structure */
HiMngmt *sta             /* confirmed status */
)
#else
PUBLIC S16 egAcSmMiLhiStaCfm(pst, sta)
Pst     *pst;           /* post structure */
HiMngmt *sta;            /* confirmed status */
#endif
{
   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcSmMiLhiStaCfm)

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiStaCfm(): txnId(%d)\n", sta->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcSmMiLhiStaCfm(): txnId(%ld)\n", sta->hdr.transId));
#endif
#endif

   /*-- Update Event --*/
   pst->event = EVTLHISTACFM;

   egAcUtlLhiSendMsg(pst, sta, NULLP);

   RETVALUE(CMXTA_ERR_NONE);
} /* end of egAcSmMiLhiStaCfm */

/*
*
*       Fun:   egAcUtlLhiSendMsg 
*
*       Desc:  This function is used to send Message
*
*       Ret:   None
*
*       Notes: None
*
*       File:  egac_lhicb.c
*
*/
#ifdef ANSI
PUBLIC S16 egAcUtlLhiSendMsg
(
Pst         *pst,
HiMngmt     *cfm,
Buffer      *mBuf
)
#else
PUBLIC S16 egAcUtlLhiSendMsg(pst, cfm, mBuf)
Pst         *pst;
HiMngmt     *cfm;
Buffer      *mBuf;
#endif /* ANSI */
{
   Bool   del;
   CmXtaTCCb *tcCb;
   CmXtaMsgQElm qElm;
   EgAccMsgQElm *egtpMsg;

   /*-- eg003.201 : TRC changes from eg006.102--*/
   EG_TRC2(egAcUtlLhiSendMsg)

#ifdef LMINT3
#ifdef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlLhiSendMsg(): txnId(%d)\n", cfm->hdr.transId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "egAcUtlLhiSendMsg(): txnId(%ld)\n", cfm->hdr.transId));
#endif
#endif

   CMXTA_ZERO(&qElm, sizeof(qElm));

   /*-- Check if we are in slave mode --*/
   if (cmXtaCb.masterMode == FALSE)
   {
      CMXTA_FREEMBUF(mBuf);
      RETVALUE(CMXTA_ERR_NONE);
   }

   del = TRUE;
   /*-- Do not delete the txn cb if it is partial confirmation --*/
   if (cfm->cfm.status == LCM_PRIM_OK_NDONE)
      del = FALSE;

   /*-- Find the associated test case using the txnId --*/
#ifdef LMINT3
   if ((tcCb = cmXtaTxnTstCbFind(cfm->hdr.transId, del)) == NULLP)
   {
      /*-- No asegciated test case found, spurious 
        message, drop it --*/
#ifdef ALIGN_64BIT
      CMXTA_DBG_INFO((_cmxtap, "egAcUtlLhiSendMsg(): msg dropped for txnId(%d)\n",
               cfm->hdr.transId));
#else
      CMXTA_DBG_INFO((_cmxtap, "egAcUtlLhiSendMsg(): msg dropped for txnId(%ld)\n",
               cfm->hdr.transId));
#endif

      /*-- Drop the message --*/
      if (pst->event == EVTLHITRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }
#endif

   /*-- Check if any tapa directives set --*/

   /*-- Drop the message if the status is OK_NDONE and the global directive 
        is set --*/
   if ((tcCb->directives.partialCfm == FALSE) &&
       (cfm->cfm.status == LCM_PRIM_OK_NDONE))
      RETVALUE(ROK);

   /*-- Check if we are logging the traces --*/
   if ((tcCb->directives.logTrc == TRUE) &&
       (pst->event == EVTLHITRCIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are logging the alarms --*/
   if ((tcCb->directives.logAlarm == TRUE) &&
       (pst->event == EVTLHISTAIND))
   {
      /*-- Log alarms --*/
   }

   /*-- Check if we are ignoring all the messages, or else it is
        an alarm or a trace and the capture for the same is not
        set --*/
   if ((tcCb->directives.ignoreMsg == TRUE)    ||
       ((pst->event == EVTLHISTAIND)     &&
        (tcCb->directives.capAlarm == FALSE))  ||
       ((pst->event == EVTLHITRCIND)     &&
        (tcCb->directives.capTrc == FALSE)))
   {
      /*-- Drop the message --*/
      if (pst->event == EVTLHITRCIND)
      {
         CMXTA_FREEMBUF(mBuf);
      }

      RETVALUE(CMXTA_ERR_NONE);
   }

   /*-- Allocate eGTP memory data --*/
   egtpMsg = NULLP;
   CMXTA_ALLOC(&egtpMsg, sizeof (EgAccMsgQElm));
   if (egtpMsg == NULLP)
   {
      CMXTA_DBG_ERR((_cmxtap, "egAcEgtSaveMsg(): resource error\n"));
      RETVALUE(CMXTA_ERR_RSRC);
   }

   /*-- FILL THE MESSAGE IN THE QUEUE STRUCTURE --*/
   (Void) cmMemcpy((U8 *) &(qElm.pst), (U8 *)pst, sizeof(Pst));
   (Void) cmMemcpy((U8 *) &(egtpMsg->u.hiMngmt), (U8 *)cfm, sizeof(HiMngmt));
   egtpMsg->mBuf = mBuf;
   qElm.msgFreeFun = egAcUtlLhiCb;
   qElm.data = (Void *)egtpMsg;

   /*-- Test case found, queue the message for the tcCb --*/
   /* Push it onto the message queue --*/
   /*  Support for multiple queues */
   (Void) cmXtaPushMsg(&tcCb->msgQ[0], &qElm);

   /*-- Check if the message has arrived in a TC fashion, this
        may happen if the test engine was sending a message and
        the layer sent a message back in TC fashion, do not 
        trigger the test engine now in that case, the test engine
        will later have a look at the queued message --*/
   if (tcCb->busy == FALSE)
      cmXtaTCEngine(tcCb);

   RETVALUE(ROK);
} /* End of egAcUtlLhiSendMsg() */

/********************************************************************30**

         End of file:     egac_lhicb.c@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 18:18:37 2015

*********************************************************************31*/


/********************************************************************40**

        Notes:

*********************************************************************41*/

/********************************************************************50**

*********************************************************************51*/


/********************************************************************60**

        Revision history:

*********************************************************************61*/

/********************************************************************80**

*********************************************************************81*/

/********************************************************************90**

    ver       pat    init                  description
----------- -------- ---- -----------------------------------------------
/main/1      ---      ad          1. Created for Initial release 1.1
/main/2      ---      svenkat     1. Initial for eGTP 1.2 Release
/main/3      ---      pmacharla   1. Initial for eGTP release 2.1
/main/3     eg003.201 psingh      1. Merged code from eg006.102 to Fix 
                                     TRACE5 macro related issue
*********************************************************************91*/
