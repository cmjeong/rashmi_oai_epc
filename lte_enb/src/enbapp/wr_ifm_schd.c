
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_ifm_schd.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/


/* header include files (.h) */
static const char* RLOG_MODULE_NAME="IFM";
static int RLOG_FILE_ID=79;


static int RLOG_MODULE_ID=4;

#include "wr.h"
#include "wr_cmn.h"
#include "wr_ifm_schd.h"
#include "wr_lwr.h"

#include "wr_emm.h"
#include "wr_umm.h"
#include "wr_smm_smallcell.h"
#include "wr_dam.h"
#include "wr_smm_init.h"
#ifdef TIP_L3
#include "crg.h"
#include "crg.x"
#include "tip_mac.h"
#endif
#include "tip_cmn.h"

#ifdef SS_DIAG
EXTERN U32 numTti;
#endif /* SS_DIAG */
EXTERN TipDrvrTskIpProcIdInfo drvrIpProcIdInfo[WR_MAX_CELLS];
PUBLIC U32 numTtiTicks;
/*ccpu00129785*/
PUBLIC Bool memAlarm=FALSE;
#ifdef WR_WATCHDOG
PUBLIC U32 wrMonitorTtiInd = 0;
#endif
#ifdef TIP_L3
void sendGtpTxRxEvent(U16  cellId)
{
   static Pst                pst = {.dstProcId=20,.srcProcId=30,.dstEnt = ENTEG, .srcEnt = ENTSM};

   pst.srcProcId = WR_L3_OFFSET;
   pst.dstProcId =  drvrIpProcIdInfo[cellId - 1].ul2ProcId;
   Buffer *mBuf = NULLP;
   SGetMsg(0, 0, (Buffer **) &mBuf);
   pst.event = 22;
   SPstTsk(&pst,mBuf);

   mBuf = NULLP;
   SGetMsg(0, 0, (Buffer **) &mBuf);
   pst.event = 23;
   SPstTsk(&pst,mBuf);
}
#endif

#ifndef TIP_L3
/** @brief Request from RRM to MAC to bind the interface saps */
PRIVATE  RgrBndReq WrIfmSchdBndReqMt[] =
{
   cmPkRgrBndReq,       /* 0 - loseely coupled */
#ifndef LCRGR
   RgUiRgrBndReq,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkRgrBndReq        /* 2 - light weight loosely coupled */
};
#endif
/** @brief Request from RRM to MAC to Unbind the interface saps */
PRIVATE  RgrUbndReq WrIfmSchdUbndReqMt[] =
{
   cmPkRgrUbndReq,       /* 0 - loseely coupled */
#ifndef LCRGR
   RgUiRgrUbndReq,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkRgrUbndReq        /* 2 - light weight loosely coupled */
};
#ifndef TIP_L3
/** @brief Configuration Request from RRM to MAC for 
 * configuring Cell/Ue/Lc */
PRIVATE  RgrCfgReq WrIfmSchdCfgReqMt[] =
{
   cmPkRgrCfgReq,       /* 0 - loseely coupled */
#ifndef LCRGR
   RgUiRgrCfgReq,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkRgrCfgReq        /* 2 - light weight loosely coupled */
};
#endif

#ifdef SI_NEW
#ifndef TIP_L3
/** @brief Configuration Request from RRM to MAC for 
 * configuring SI */
PRIVATE  RgrSiCfgReq WrIfmSchdSiCfgReqMt[] =
{
   cmPkRgrSiCfgReq,       /* 0 - loseely coupled */
#ifndef LCRGR
   RgUiRgrSiCfgReq,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkRgrSiCfgReq        /* 2 - light weight loosely coupled */
};
#endif
/* PH04_CMAS : Added for CMAS feature. */
/** @brief Configuration Request from RRM to MAC for
 * configuring warning SI */
PRIVATE  RgrWarningSiCfgReq WrIfmSchdWrngSiCfgReqMt[] =
{
   cmPkRgrWarningSiCfgReq,       /* 0 - loseely coupled */
#ifndef LCRGR
   RgUiRgrWarningSiCfgReq,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkRgrWarningSiCfgReq        /* 2 - light weight loosely coupled */
};

/*  PH04_CMAS : Added for CMAS feature. */
/** @brief Configuration Request from RRM to MAC for
 *  stoping  warning SI */
PRIVATE  RgrWarningSiStopReq  WrIfmSchdWrngSiStopReqMt[] =
{
   cmPkRgrWarningSiStopReq,       /* 0 - loseely coupled */
#ifndef LCRGR
   RgUiRgrWarningSiStopReq,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkRgrWarningSiStopReq        /* 2 - light weight loosely coupled */
};
/* PH04_CMAS : end */

#endif

/* LTE_ADV_DSFR starts */
/** @brief Configuration Request from RRM to MAC for 
 * configuring LOAD INF */
PRIVATE  RgrLoadInfReq WrIfmSchdLoadInfReqMt[] =
{
   cmPkRgrLoadInfReq,       /* 0 - loseely coupled */
#ifndef LCRGR
   RgUiRgrLoadInfReq,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkRgrLoadInfReq        /* 2 - light weight loosely coupled */
};
/* LTE_ADV_DSFR ends */


/** @brief This function is used to set the MAC transaction Identifier.
 *
 * @details
 *
 *     Function: wrIfmSchdSetTrans
 *
 *         Processing steps:
 *         - Set the transaction Identifier for MAC layer. 
 *
 *
 * @param[out] trans: MAC configuaration Transaction identifier.  
 * @param[in] transId: Transaction ID. 
 * @return void 
 */
PRIVATE Void wrIfmSchdSetTrans
(
RgrCfgTransId                *trans,
U32                          transId
)
{
   trans->trans[7] = transId & 0x000000ff; transId >>= 8;
   trans->trans[6] = transId & 0x000000ff; transId >>= 8;
   trans->trans[5] = transId & 0x000000ff; transId >>= 8;
   trans->trans[4] = transId & 0x000000ff; transId >>= 8;
}

#ifdef WR
/** @brief This function is used to send the SAP Bind Request message
 *         to MAC layer.
 *
 * @details
 *
 *     Function: WrIfmSchdBndReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call the
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the Schedular Bind request message 
 *           to MAC layer.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] spId: Service Provider ID. 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 WrIfmSchdBndReq
(
Pst*                         pst,
SuId                         suId,
SpId                         spId
)
{
   TRC3(WrIfmSchdBndReq);
#ifdef TIP_L3
   WrIfmSchdBndCfm(pst, suId, CM_BND_OK);
#else 
   (*WrIfmSchdBndReqMt[pst->selector])(pst, suId, spId);
#endif
   RETVALUE(ROK);
} /* end of WrIfmSchdBndReq */

/** @brief This function is used to send Unbind request to MAC layer.
 *
 * @details
 *
 *     Function: WrIfmSchdUbndReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the Schedular Unbind request message 
 *           to MAC layer.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] spId: Service Provider ID. 
 * @param[in] reason: Reason to unbind the MAC SAP. 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 WrIfmSchdUbndReq
(
Pst*                         pst,
SpId                         spId,
Reason                       reason
)
{

   TRC3(WrIfmSchdUbndReq);

   (*WrIfmSchdUbndReqMt[pst->selector])(pst, spId, reason);

   RETVALUE(ROK);
} /* end of WrIfmSchdUbndReq */

/** @brief This function is used to send Configuration equest from RRM
 *         Application to EnodeB.
 *
 * @details
 *
 *     Function: WrIfmSchdCfgReq
 *
 *         Processing steps:
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the Schedular config request message 
 *           to MAC layer.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] spId: Service Provider ID. 
 * @param[in] transId: Transction ID. 
 * @param[in] cfgReqInfo: MAC Config Request 
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 WrIfmSchdCfgReq
(
Pst*                         pst,
SpId                         spId,
RgrCfgTransId                transId,
RgrCfgReqInfo                *cfgReqInfo
)
{

   TRC3(WrIfmSchdCfgReq);
#ifdef TIP_L3
   tipSendMacCfgReq(pst, spId, transId, cfgReqInfo);
#else
   (*WrIfmSchdCfgReqMt[pst->selector])(pst, spId, transId, cfgReqInfo);
#endif

   RETVALUE(ROK);
}

#ifdef SI_NEW
/** @brief This function is used to send the SI Configuration Request to MAC
 *         layer.
 *
 * @details
 *
 *     Function: WrIfmSchdSiCfgReq
 *
 *         Processing steps:
 *         - Set the transaction ID for SI configuration request.
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly 
 *           coupled function to send the SI config request message 
 *           to MAC layer.
 *
 * @param[in] transId: Transaction ID.
 * @param[in] cfgReqInfo: SI Config Request to MAC layer.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 WrIfmSchdSiCfgReq
(
U32                        transId,
RgrSiCfgReqInfo              *cfgReqInfo
)
{
   WrLiSapCb                 *schdSap = wrCb.rgrSap[0];
   RgrCfgTransId             transID;
   SuId                       suId;

   TRC3(WrIfmSchdSiCfgReq);

   WR_GET_SAP_ID_FRM_CELL_ID(cfgReqInfo->cellId, WR_RGR_SAP, suId);

   schdSap = wrCb.rgrSap[suId];

   wrIfmSchdSetTrans(&transID, transId);
#ifdef TIP_L3
   tipSendSiCfgReq(&schdSap->pst, schdSap->spId, transID, cfgReqInfo);
#else
   (*WrIfmSchdSiCfgReqMt[schdSap->pst.selector])(&schdSap->pst, schdSap->spId, 
                                                          transID, cfgReqInfo);
#endif

   RETVALUE(ROK);
}

/* PH04_CMAS : Added for CMAS feature. */
/** @brief This function is used to send the warning SI Configuration Request
 *         to MAC layer.
 *
 * @details
 *
 *     Function: WrIfmSchdWrngSiCfgReq
 *
 *         Processing steps:
 *         - Set the transaction ID for SI configuration request.
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly
 *           coupled function to send the SI config request message
 *           to MAC layer.
 *
 * @param[in] transId: Transaction ID.
 * @param[in] cfgReqInfo: SI Config Request to MAC layer.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 WrIfmSchdWrngSiCfgReq
(
U32                          transId,
RgrWarningSiCfgReqInfo       *cfgReqInfo
)
{
   WrLiSapCb                 *schdSap;
   RgrCfgTransId              transID;
   SuId                       suId;

   TRC3(WrIfmSchdSiCfgReq);

   WR_GET_SAP_ID_FRM_CELL_ID(cfgReqInfo->cellId, WR_RGR_SAP, suId);

   schdSap = wrCb.rgrSap[suId];

   wrIfmSchdSetTrans(&transID, transId);

   (*WrIfmSchdWrngSiCfgReqMt[schdSap->pst.selector])(&schdSap->pst, schdSap->spId,
                                                          transID, cfgReqInfo);

   RETVALUE(ROK);
}


/* PH04_CMAS : This function added for CMAS feature*/
PUBLIC S16 WrIfmSchdWrngSiStopReq
(
    U32            transId,
    U8             siIndex
)
{
   WrLiSapCb                 *schdSap = wrCb.rgrSap[0];
   RgrCfgTransId             transID;

   TRC3(WrIfmSchdSiStopReq);
   wrIfmSchdSetTrans(&transID, transId);
   (*WrIfmSchdWrngSiStopReqMt[schdSap->pst.selector])(&schdSap->pst, schdSap->spId, transID, siIndex);

   RETVALUE(ROK);

}

#endif

/* LTE_ADV_DSFR starts */
/** @brief This function is used to send the LOAD INF Request to MAC
 *         layer.
 *
 * @details
 *
 *     Function: WrIfmSchdLoadInfReq
 *
 *         Processing steps:
 *         - Set the transaction ID for LOAD INF request.
 *         - Based on the selector value, this primitve will call
 *           tightly colupled, loosely coupled or light weight loosly
 *           coupled function to send the LOAD INF request message
 *           to MAC layer.
 *
 * @param[in] transId: Transaction ID.
 * @param[in] loadInfReq: LOAD INF Request to MAC layer.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 WrIfmSchdLoadInfReq
(
U32                        transId,
RgrLoadInfReqInfo          *loadInfReq
)
{
   WrLiSapCb               *schdSap;
   RgrCfgTransId           transID;
   SuId                    suId;

   WR_GET_SAP_ID_FRM_CELL_ID(loadInfReq->cellId, WR_RGR_SAP, suId);

   schdSap = wrCb.rgrSap[suId];

   TRC3(WrIfmSchdLoadInfReq);
   wrIfmSchdSetTrans(&transID, transId);
   (*WrIfmSchdLoadInfReqMt[schdSap->pst.selector])(&schdSap->pst, schdSap->spId,
                                                          transID, loadInfReq);

   RETVALUE(ROK);
}
/* LTE_ADV_DSFR ends */

#endif /*--ifdef WR--*/

/**************************************************************
   RGR interface handler functions
***************************************************************/
/** @brief This function is used by to present Bind Cfm to RGR.
 *
 * @details
 *
 *     Function: WrIfmSchdBndCfm
 *
 *         Processing steps:
 *         - if the status is BIND_OK, then stop the MAC(RGR) Bind timer.
 *         - send an ALARAM to layer manager.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] status: Status 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 WrIfmSchdBndCfm
(
Pst                          *pst,
SuId                         suId,
U8                           status
)
{
   TRC2(WrIfmSchdBndCfm);

   /*-- Update Event --*/
   pst->event = EVTRGRBNDCFM;

   /* Send alarm */
   if (CM_BND_OK == status)
   {
      wrStopTmr((PTR)wrCb.rgrSap[suId],WR_TMR_RGR_SAP_BND);
      RLOG0(L_INFO, "[ALARM] Sending RGR_SAP_BND_OK to OAM");
      wrSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_OK, LWR_CAUSE_RGR_SAP_BOUND);
   }
   else
   {
      RLOG0(L_FATAL, "[ALARM] Sending RGR_SAP_BND_FAIL to OAM");
      wrStopTmr((PTR)wrCb.rgrSap[suId],WR_TMR_RGR_SAP_BND);
      wrSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL, LCM_CAUSE_UNKNOWN);
   }

   RETVALUE(ROK);
} /* end of WrIfmSchdBndCfm */

/** @brief This function is used to process the configuration confirm status
 *         from MAC layer.
 *
 * @details
 *
 *     Function: WrIfmSchdCfgCfm
 *
 *         Processing steps:
 *         - This function will process the configuration confirm from MAC
 *           layer.
 *         - Based on the configuration type is cell config, then this function
 *           triggers the EMM module function wrEmmSchdCellCfgCfm.
 *         - Otherwise This function will trrigges the UMM module function
 *           wrUmmPrcSchdCfgCfm to process the configuration confirm status
 *           from MAC layer.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] transId: Transction ID. 
 * @param[in] status: Status 
 * @return  S16
 *        -# Success : ROK
 */
PRIVATE S16 WrIfmSchdCfgCfm
(
Pst                          *pst,          
SuId                         suId,
RgrCfgTransId                transId,
U8                           status
)
{
   U16                       cfgType = 0;
   U16                       action  = 0;
   U32                       lTransId;

   TRC2(WrIfmSchdCfgCfm);

   /* Prepare the transaction as requird by EMM                           */
   lTransId = transId.trans[4];
   lTransId = (lTransId << 8) + transId.trans[5];
   lTransId = (lTransId << 8) + transId.trans[6];
   lTransId = (lTransId << 8) + transId.trans[7];
   cfgType  = transId.trans[0];
   action   = transId.trans[1];
   /* If the configuration type is of CELL, invoke EMM appropriately      */

   if(status == RGR_CFG_CFM_OK)
   {
      RLOG1(L_DEBUG, "Received SchdCfgCfm Status = successful, Message ID = %ld",
         lTransId);
   }
   else
   {
        RLOG3(L_ERROR, "Received SchdCfgCfm Status = Failure,  Message ID = %ld,"
         "Configuration Type = %d, Action = %d", lTransId, cfgType, action);
   }

   if(cfgType == RGR_CELL_CFG)
   {
     if(RGR_DELETE == action)
     {
        if (status == RGR_CFG_CFM_OK)
        {
            
           wrFillNhuCellDelCfgReq(lTransId); 
        }
        else
        {
           RLOG1(L_ERROR, "WrIfmSchdCfgCfm: Cell Delete at MAC Sch Failed %ld", lTransId);
        }
        
     }
     else if (RGR_CONFIG == action)
     {
        if (status == RGR_CFG_CFM_OK)
        {
            wrEmmSchdCellCfgCfm(lTransId, WR_CFG_OK);
        }
        else
        {
            wrEmmSchdCellCfgCfm(lTransId, WR_CFG_NOK);
        }
     }
     else
     {
        /* Need to handle for RGR_RECONFIG */
        if (status == RGR_CFG_CFM_OK)
        {
            wrEmmSchdCellReCfgCfm(lTransId, WR_CFG_OK);
        }
        else
        {
            wrEmmSchdCellReCfgCfm(lTransId, WR_CFG_NOK);
        }
     }
   }
   else if(RGR_ENB_CFG == action)
   {
      wrEmmSchdEnbCfgCfm(lTransId, WR_CFG_OK);
   }
   else
   {
      /* If the confirmation is not for CELL, it should be passed to UMM  */
      wrUmmPrcSchdCfgCfm(lTransId, status);
   }

   RETVALUE(ROK);
} /* end of WrIfmSchdCfgCfm */

/** @brief This function is call handler to process the SI confirmation
 *         from MAC layer to Application.
 *
 * @details
 *
 *     Function: NxLiRgrSiCfgCfm
 *
 *         Processing steps:
 *         - This function is invoked on reception of SI configuration confirm from
 *           MAC layer through Loosely coupled.
 *         - This function will invoke the function wrEmmSchdSiCfgCfm to process
 *           the SI configuration confirm status.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] transId: Transction ID. 
 * @param[in] status: Status 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NxLiRgrSiCfgCfm 
(
Pst*                 pst,
SuId                 suId,
RgrCfgTransId        transId,
U8                   status
)
{
   U32     lTransId = 0;

   TRC2(NxLiRgrSiCfgCfm);

   /* Prepare the transaction as requird by EMM                           */
   lTransId = transId.trans[4];
   lTransId = (lTransId << 8) + transId.trans[5];
   lTransId = (lTransId << 8) + transId.trans[6];
   lTransId = (lTransId << 8) + transId.trans[7];

   RETVALUE(wrEmmSchdSiCfgCfm(lTransId,status));

} /* end of NxLiRgrSiCfgCfm */


/* PH04_CMAS : Added for CMAS feature.*/
PUBLIC S16 NxLiRgrWrngSiCfgCfm
(
Pst*                 pst,
SuId                 suId,
RgrCfgTransId        transId,
U8                   siId,
U8                   status
)
{
   U32     lTransId = 0;
   
   TRC2(NxLiRgrWrngSiCfgCfm);

   /* Prepare the transaction as requird by EMM                           */
   lTransId = transId.trans[4];
   lTransId = (lTransId << 8) + transId.trans[5];
   lTransId = (lTransId << 8) + transId.trans[6];
   lTransId = (lTransId << 8) + transId.trans[7];

   RETVALUE(wrEmmSchdWrngSiCfgCfm(lTransId,status));

} /* end of NxLiRgrWrngSiCfgCfm */


/* PH04_CMAS : Added for CMAS feature. */
PUBLIC S16 NxLiRgrStopWrngSiCfgCfm
(
Pst*                 pst,
SuId                 suId,
RgrCfgTransId        transId,
U8                   status
)
{
   U32     lTransId = 0;

   TRC2(NxLiRgrStopWrngSiCfgCfm);

   /* Prepare the transaction as requird by EMM                           */
   lTransId = transId.trans[4];
   lTransId = (lTransId << 8) + transId.trans[5];
   lTransId = (lTransId << 8) + transId.trans[6];
   lTransId = (lTransId << 8) + transId.trans[7];

   RETVALUE(wrEmmSchdStopWrngSiCfgCfm(lTransId,status));

} /* end of NxLiRgrWrngSiCfgCfm */


/** @brief This function is call handler for every TTI indication from MAC
 *         layer.
 *
 * @details
 *
 *     Function: NxLiRgrTtiInd
 *
 *         Processing steps:
 *         - This function is call hanler on reception TTI Indication from MAC
 *           layer. 
 *         - This function will invokes the function wrEmmSchdTtiInd to 
 *           process the TTI Indication at application.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] ttiInd: TTI Indication. 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NxLiRgrTtiInd
(
Pst                          *pst,          
SuId                         suId,
RgrTtiIndInfo                *ttiInd
)
{
#ifndef TENB_ACC
   U32 ttiCnt = 0;
   TRC2(NxLiRgrTtiInd);
#if 0 /* ticks generation is done at UL2 now, as part of DAM cell create */
#ifdef TIP_L3
//   if((ttiCnt % 10) == 0)
   {
        sendGtpTxRxEvent(ttiInd->cellId); 
   }
#endif
#endif
      //WR_EMM_SET_TTI_CNT(ttiInd->cellId);
   for (U8 cellIdx = 0; cellIdx < wrEmmCb.numCells; cellIdx++)
   {
      if((wrEmmCb.cellCb[cellIdx] != NULLP) && 
            (wrEmmCb.cellCb[cellIdx]->cellId == ttiInd->cellId))
      WR_EMM_SET_TTI_CNT(wrEmmCb.cellCb[cellIdx]->cellId);
   }
   WR_EMM_GET_TTI_CNT(ttiInd->cellId, ttiCnt);

   wrPlatRgrTtiHndl(ttiCnt, ttiInd->cellId);
   if((ttiCnt % 3000) == 0)
   {
      for (U8 cellIdx = 0; cellIdx < wrEmmCb.numCells; cellIdx++)
      {
         if(wrEmmCb.cellCb[cellIdx] != NULLP)
            printf("L3 TTI Ind for cell Id: %d \n", wrEmmCb.cellCb[cellIdx]->cellId);
      }
#if 0
      wrDamPrintThroughput(ttiInd->cellId);
#ifdef MAC_SCH_STATS
      smBuildRgStsReq();
#endif /* MAC_SCH_STATS */
#endif /* MAC_SCH_STATS */
   }
#ifdef HCSG_DBG
   if((ttiCnt % 1000) == 0)
   {
      wrUmmHcsgPrintUeStats();
   }
#endif
   if ( 0 == (ttiCnt % WR_CPU_MON_PERIOD) )
   {
      wrCpuLoadCntrl(ttiInd->cellId);
   }
#ifdef WR_WATCHDOG
   wrMonitorTtiInd++;
#endif
    /*adde to get same time stamp in UARM and LARM for logs*/   
    /*we are not going to reset this because it is used in prasentation thread for solting*/
#ifdef SS_DIAG
   numTti+=10;
#endif /* SS_DIAG */
   RETVALUE(wrEmmSchdTtiInd(ttiInd));
#else
   RETVALUE(ROK);/* Klockwork P1 warning fix */
#endif /* TENB_ACC */
} /* end of NxLiRgrTtiInd */

/**************************************************************
   RGR interface wrapper functions
***************************************************************/
/** @brief This function is call handler to process the Bind confirmation
 *         from MAC layer to Application.
 *
 * @details
 *
 *     Function: NxLiRgrBndCfm
 *
 *         Processing steps:
 *         - This function is invoked on reception of SAP bind confirm from
 *           MAC layer through Loosely coupled.
 *         - This function will invoke the function WrIfmSchdBndCfm to process
 *           the schedular bind confirm status.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] status: Status 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NxLiRgrBndCfm
(
Pst                          *pst,
SuId                         suId,
U8                           status
)
{

   TRC2(NxLiRgrBndCfm);
   RETVALUE(WrIfmSchdBndCfm(pst,suId,status));
} /* end of NxLiRgrBndCfm */

/** @brief This function is call handler to process the schedular configuration
 *         confirm status from MAC layer to Application.
 *
 * @details
 *
 *     Function: NxLiRgrCfgCfm
 *
 *         Processing steps:
 *         - This function is invoked on reception of configuration confirm from
 *           MAC layer through Loosely coupled.
 *         - This function will invoke the function WrIfmSchdCfgCfm to process
 *           the schedular configuration confirm status.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] transId: Transction ID. 
 * @param[in] status: Status 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NxLiRgrCfgCfm
(
Pst                          *pst,          
SuId                         suId,
RgrCfgTransId                transId,
U8                           status
)
{
   TRC2(NxLiRgrCfgCfm);
   RETVALUE(WrIfmSchdCfgCfm(pst, suId, transId, status));
} /* end of NxLiRgrCfgCfm */

/** @brief This function is used to send SCH/PFS configuration request to SCH
 *         layer.
 *
 * @details
 *
 *     Function: WrIfmSchdEnbCfg
 *
 *         Processing steps:
 *         - This function is invoked by EMM module during ENB Sched config.
 *         - This function is used to send SCH configuration request to SCH
 *           layer.
 *
 * @param[in] cfgReq: Cell Configuration Req to SCH. 
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED 
 */

PUBLIC S16 WrIfmSchdEnbCfgReq
(
RgrCfgReqInfo                *cfgReq,
U32                           transId
)
{
   Pst                       *pst = NULLP;
   RgrCfgTransId              transID;
   SuId                       suId;

   TRC2(WrIfmSchdEnbCfgReq);

   RLOG0(L_EVENT, "WrIfmSchdEnbCfgReq: Sending scheduler ENB Cfg Req");

   /* Currently we are assuming that transId is ZERO. as presently
    * we have only One Scheduler Instance, this has to be changed
    * once we have multiple instaces - The additional
      prarameter is passed to future use
   */
   WR_GET_SAP_ID_FRM_CELL_ID(transId, WR_RGR_SAP, suId);

   /* Assign Pst */
   pst = &wrCb.rgrSap[suId]->pst;
   pst->event = EVTRGRCFGREQ;

   /* Trans Id */
   WR_SET_ZERO(&transID , sizeof(RgrCfgTransId));
   transID.trans[0] = RGR_ENB_CFG;
   transID.trans[1] = cfgReq->action; 
   wrIfmSchdSetTrans(&transID, transId);

   /* Fill appropriate TransId details 
    *     * here since lcId & crnti doesnt hold they are populated
    *         * as zero */
   if(ROK != WrIfmSchdCfgReq(pst, wrCb.rgrSap[suId]->spId, transID, cfgReq))
   {
      RLOG0(L_ERROR, "WrIfmSchdEnbCfgReq: WrIfmSchdCfgReq primitive failed.");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of WrIfmSchdEnbCfg */

/** @brief This function is used to send MAC cell configuration request to MAC
 *         layer.
 *
 * @details
 *
 *     Function: WrIfmSchdCfgCell
 *
 *         Processing steps:
 *         - This function is invoked by EMM module during cell configuration.
 *         - This function is used to send cell configuration request to MAC
 *           layer.
 *
 * @param[in] cfgReq: Cell Configuration Req to MAC. 
 * @param[in] transId: Transction ID. 
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED 
 */

PUBLIC S16 WrIfmSchdCfgCell
(
RgrCfgReqInfo                *cfgReq,
U32                          transId
)
{
   Pst                       *pst = NULLP;
   RgrCfgTransId             transID;
   SuId                      suId;

   TRC2(WrIfmSchdCellCfgReq);

   RLOG0(L_DEBUG, "WrIfmSchdCellCfgReq: Sending scheduler cell Cfg Req");

   /* Currently we are assuming that transId is cellId. The additional
      prarameter is passed to future use
   */
   WR_GET_SAP_ID_FRM_CELL_ID(transId, WR_RGR_SAP, suId);

   /* Assign Pst */
   pst = &wrCb.rgrSap[suId]->pst;
   pst->event = EVTRGRCFGREQ;

   /* Trans Id */
   WR_SET_ZERO(&transID , sizeof(RgrCfgTransId));
   transID.trans[0] = RGR_CELL_CFG;
   transID.trans[1] = cfgReq->action; 
   wrIfmSchdSetTrans(&transID, transId);

   /* Fill appropriate TransId details 
    *     * here since lcId & crnti doesnt hold they are populated
    *         * as zero */
   if(ROK != WrIfmSchdCfgReq(pst, wrCb.rgrSap[suId]->spId, transID, cfgReq))
   {
      RLOG0(L_ERROR, "WrIfmSchdCellCfgReq: WrIfmSchdCfgReq primitive failed.");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
} /* end of WrIfmSchdCfgCell */

/** @brief This function is used to send the UE specific configuration 
 *         request to the MAC.
 *
 * @details
 *
 *     Function: WrIfmSchdCfgUe
 *
 *         Processing steps:
 *         - This function is invoked by UMM Module to configure the MAC with UE
 *           specific configuration.
 *
 *
 * @param[in] uecfg: UE Specific Configuration Req to MAC. 
 * @param[in] transId: Transction ID. 
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED 
 */
PUBLIC S16 WrIfmSchdCfgUe
(
RgrCfgReqInfo                *uecfg, 
U32                          transId,
WrCellId                     cellId
)
{
   Pst                       *pst = NULLP;
   RgrCfgTransId              transID;
   SuId                       suId;

   TRC2(WrIfmSchdCfgUe);

   RLOG0(L_DEBUG, "WrIfmSchdCfgUe: Sending Scheduler UE Cfg Req");

   WR_GET_SAP_ID_FRM_CELL_ID(cellId, WR_RGR_SAP, suId);
   /* Assign Pst */
   pst = &wrCb.rgrSap[suId]->pst;
   pst->event = EVTRGRCFGREQ;

   /* Trans Id */
   WR_SET_ZERO(&transID , sizeof(RgrCfgTransId));
   transID.trans[0] = RGR_UE_CFG;
   wrIfmSchdSetTrans(&transID, transId);
   if(ROK != WrIfmSchdCfgReq(pst, wrCb.rgrSap[suId]->spId, transID, uecfg))
   {
      RLOG0(L_ERROR, "WrIfmSchdCfgUe: WrLiRgrCfgReq primitive failed.");      
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}/* end of WrIfmSchdCfgUe*/

#ifdef RGR_CQI_REPT
/** @brief This function is call handler for every TTI indication from MAC
 *         layer.
 *
 * @details
 *
 *     Function: NxLiRgrTtiInd
 *
 *         Processing steps:
 *         - This function is call hanler on reception TTI Indication from MAC
 *           layer. 
 *         - This function will invokes the function wrEmmSchdTtiInd to 
 *           process the TTI Indication at application.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] ttiInd: TTI Indication. 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NxLiRgrStaInd
(
Pst                          *pst,          
SuId                          suId,
RgrStaIndInfo                *staInd
)
{
   TRC2(NxLiRgrStaInd);
   RETVALUE(wrUmmSchdStaInd(staInd));
} /* end of NxLiRgrStaInd */
#endif 

/* LTE_ADV starts */
/** @brief This function is call handler for LOAD INF indication from MAC
 *         layer.
 *
 * @details
 *
 *     Function: NxLiRgrLoadInfInd
 *
 *         Processing steps:
 *         - This function is call hanler on reception LOAD INF Indication from MAC
 *           layer.
 *         - This function will invokes the function wrUmmSchdLoadInfInd to
 *           process the LOAD INF Indication at application.
 *
 * @param[in] pst: POST Data Strucuture.
 * @param[in] suId: Service User ID.
 * @param[in] loadInfInd: LOAD INF Indication.
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NxLiRgrLoadInfInd
(
Pst                           *pst,
SuId                          suId,
RgrLoadInfIndInfo             *loadInfInd
)
{
   TRC2(NxLiRgrLoadInfInd);
   RETVALUE(wrEmmSchdLoadInfInd(loadInfInd));
} /* end of NxLiRgrLoadInfInd */

/* LTE_ADV ends */



/** @brief This function is call handler for every Ue Sta Indication from Sch
 *         layer.
 *
 * @details
 *
 *     Function: NxLiRgrUeStaInd
 *
 *         Processing steps:
 *         - This function is call hanler on reception Ue Sta Indication from 
 *           Sch layer. 
 *         - This function will invokes the function wrUmmSchdUeStaInd to 
 *           process the ue Sta Indication at application.
 *
 * @param[in] pst: POST Data Strucuture.  
 * @param[in] suId: Service User ID. 
 * @param[in] ueStaInd: Ue Sta Indication. 
 * @return  S16
 *        -# Success : ROK
 */
PUBLIC S16 NxLiRgrUeStaInd
(
Pst                          *pst,          
SuId                          suId,
RgrUeStaIndInfo              *ueStaInd
)
{
   TRC2(NxLiRgrUeStaInd);
   RETVALUE(wrUmmSchdUeStaInd(ueStaInd));
} /* end of NxLiRgrUeStaInd */

#ifdef TIP_L3
/** @brief This function is used to send MAC cell configuration request to MAC
 *         layer.
 *
 * @details
 *
 *     Function: wrIfmSchMacCellStartReq
 *
 *         Processing steps:
 *         - This function is invoked by EMM module during cell configuration.
 *         - This function is used to send cell configuration request to MAC
 *           layer.
 *
 * @param[in] cfgReq: Cell Configuration Req to MAC. 
 * @param[in] transId: Transction ID. 
 * @return  S16
 *        -# Success : ROK
 *        -# Failure : RFAILED 
 */
PUBLIC S16 wrIfmSchMacCellStartReq
(
U32                          cellId
)
{
   Pst                       *pst = NULLP;
   SuId                      suId;
   S16                       retVal = RFAILED;

   TRC2(wrIfmSchMacCellStartReq);

   RLOG0(L_DEBUG, "wrIfmSchMacCellStartReq: Sending scheduler cell Cfg Req");

   WR_GET_SAP_ID_FRM_CELL_ID(cellId, WR_RGR_SAP, suId);

   /* Assign Pst */
   pst = &wrCb.rgrSap[suId]->pst;
   pst->event = EVTRGRCFGREQ;
   retVal = tipSendMacCellStartReq(pst, cellId);
   if(retVal != ROK)
   {
      RLOG0(L_ERROR, "wrIfmSchMacCellStartReq primitive failed.");      
      RETVALUE(RFAILED);
   }
#ifdef ENABLE_CNM
   /*#if 0*/
   /* TODO:: Check whether SM variables can be accessed here */
   if(wrEmmCb.isCnmEnabled)
   {
      printf("\n Received CTF CellCfg Cfm.. Starting CNM for cellId %d\n",wrEmmCb.cellCb[0]->cellId);
      wrCnmTrigIctaStartReq();
   }
#endif
   wrEmmPrcPhyCfgCfm(cellId, WR_CFG_OK);
   /* Send alarm */
   RLOG0(L_INFO, "[ALARM] Sending CELL_CFG_SUCCESS to OAM ");
   wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_CELL_CFG_SUCCESS, 
         LCM_CAUSE_UNKNOWN);
   /* Send alarm */
   RLOG0(L_INFO, "[ALARM] Sending CELL_CFG_AVAILABLE to OAM ");
   wrSendLmAlarm(LCM_CATEGORY_PROTOCOL, LWR_EVENT_CELL_AVAILABLE, 
         LCM_CAUSE_UNKNOWN);

   RETVALUE(ROK);
} /* end of wrIfmSchMacCellStartReq*/

#endif
/********************************************************************30**

           End of file:    $SID$

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
$SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
