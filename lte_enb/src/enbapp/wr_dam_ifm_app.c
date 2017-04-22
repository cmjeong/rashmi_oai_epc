
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_dam_ifm_app.c

     Sid:      fc_dam_ifm_app.c@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:51:33 2014

     Prg:      Sriky 

*********************************************************************21*/

#include "wr_umm.h"
#include "wr_ifm_dam.h"
#include "wr_dam.h"
#include "wr_ifm_dam_utils.h"
#include "wr_ifm_dam_utils.x"
#include "wr_dam_ifm_app.h"


PRIVATE CONSTANT DamTnlCreatCfm EuUiDamTnlCreatCfmMt[] =
{
   cmPkTnlCreatCfm,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuLiDamTnlCreatCfm,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkTnlCreatCfm        /* 2 - light weight loosely coupled */ 
};

PRIVATE CONSTANT DamTnlModCfm EuUiDamTnlModCfmMt[] =
{
   cmPkTnlModCfm,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuLiDamTnlModCfm,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkTnlModCfm /* 2 - light weight loosely coupled */ 
};

PRIVATE CONSTANT DamUeDelCfm EuUiDamUeDelCfmMt[] =
{
   cmPkUeDelCfm,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuLiDamUeDelCfm,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkUeDelCfm     /* 2 - light weight loosely coupled */ 
};

PRIVATE CONSTANT  DamReestabCfm EuUiDamReestabCfmMt[] =
{
   cmPkReestabCfm,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuLiDamReestabCfm,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkReestabCfm      /* 2 - light weight loosely coupled */ 
};

PRIVATE CONSTANT  DamEgtpErrInd EuUiDamEgtpErrIndMt[] =
{
   cmPkEgtpErrInd,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuLiDamEgtpErrInd,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkEgtpErrInd       /* 2 - light weight loosely coupled */ 
};

PRIVATE CONSTANT DamSendCtxtRel EuUiDamSendCtxtRelMt[] =
{
   cmPkDamSendCtxtRel,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuLiDamSendCtxtRel,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkDamSendCtxtRel /* 2 - light weight loosely coupled */ 
};

PRIVATE CONSTANT DamPdcpDatCfm EuUiDamPdcpDatCfmMt[] =
{
   cmPkDamPdcpDatCfm,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuLiDamPdcpDatCfm,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkDamPdcpDatCfm /* 2 - light weight loosely coupled */ 
};
/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamWrCntrlReq 
 *
 *         Processing steps:
 *         - This function is invoked by Stack manager to configre the DAM
 *           module 
 *         - This function invokes the function wrDamCntrlReq to process the
 *           control req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return  Void 
 */
PUBLIC Void  wrIfmDamWrCntrlReq
(
LwrMngmt    *cntrl
)
{
   TRC2(wrIfmDamWrCntrlReq);
   wrDamCntrlReq(cntrl);
   RETVOID;
} /*wrIfmDamWrWrCntrlReq*/

/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamWrCfgReq 
 *
 *         Processing steps:
 *         - This function is invoked by Stack manager to configure the DAM
 *           module 
 *         - This function invokes the function wrIfmDamWrCfgReq to process the
 *           configuration Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return Void  
 */
PUBLIC Void wrIfmDamWrCfgReq
(
LwrMngmt *cfg
)
{
   TRC2(wrIfmDamWrCfgReq);
   wrDamCfgReq(cfg);
   RETVOID;
} /*wrIfmDamWrWrCfgReq*/
/*
 *       Fun:     wrDamGenerateCfm 
 *
 *       Desc:    To generate confirms
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  None.
 */
PUBLIC S16  wrDamGenerateCfm
(
Pst          *pst,
CmStatus     *cfmSts,
U8           prim,
LwrMngmt     *cfm
)
{
   Pst       cPst;
   Header    *hdr;

   /* Fill the pst structure for LM i/f */
   cPst.srcEnt    = wrDamCb.init.ent;
   cPst.srcInst   = wrDamCb.init.inst;

   cPst.srcProcId = SFndProcId();

   /*
    * If genconfig is done, fill the destn identity
    * from the pst configured, else use the incoming
    * pst structure for destination identity.
    */
   if (NULLP == pst) 
   {  
      cPst.dstEnt    = wrCb.init.lmPst.dstEnt;
      cPst.dstInst   = wrCb.init.lmPst.dstInst;
      cPst.dstProcId = wrCb.init.lmPst.dstProcId;
   }
   else
   {  
      cPst.dstEnt    = pst->srcEnt;
      cPst.dstInst   = pst->srcInst;
      cPst.dstProcId = pst->srcProcId;
   }

   /* we are sending cfg as cfm back by filling properly values */
   hdr = &(cfm->hdr);
   cPst.selector  = hdr->response.selector;
   cPst.prior     = hdr->response.prior;
   cPst.route     = hdr->response.route;
   cPst.region    = hdr->response.mem.region;
   cPst.pool      = hdr->response.mem.pool;

   /* Fill the Header in cfm structure */
/* cmMemset ((U8 *)&cfm->hdr, '\0', sizeof(Header));*/
/* cfm->hdr.elmId.elmnt = hdr->elmId.elmnt;*/
/* Fill the transcation for which the cfm is being sent */
/* cfm->hdr.transId = hdr->transId;*/

   cfm->hdr.entId.ent   = wrDamCb.init.ent;
   cfm->hdr.entId.inst  = wrDamCb.init.inst;

   cfm->cfm.status = cfmSts->status; 
   cfm->cfm.reason = cfmSts->reason;
   switch (prim)
   {  
      case TCFG:
       /*  cmMemset ((U8 *)&cfm->t.cfg, 0, sizeof(LwrCfg));*/
         cPst.event = EVTLWRCFGCFM;
         WrMiDamLwrCfgCfm (&cPst, cfm);
         break;   

      case TCNTRL:
         cPst.event = EVTLWRCNTRLCFM;
         WrMiLwrCntrlCfm (&cPst, cfm);
         break;
   }  

   RETVALUE(ROK);
} /* wrDamGenerateCfm */


/** @brief This function is used to send the configure confirmation 
 *   the enbapp .
 *
 * @details
 *
 *     Function: wrIfmDamWrCfgCfm 
 *
 *         Processing steps:
 *         - This function is invoked the DAM  module 
 *         - This function invokes the pack function to send the 
 *           configuration Confirm.
 *
 * @param[in] cfg    : Data Application Module Configuration.  
 * @param[in] cfgCfm : Status of the configuration process.  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamWrCfgCfm
(
LwrMngmt    *cfg,
CmStatus   *cfgCfm
)
{
   TRC2(wrIfmDamWrCfgCfm);
#ifdef TIP_L3_UL2_LL2_SPLIT
   wrDamGenerateCfm(&wrDamCb.init.lmPst, cfgCfm, TCFG, cfg);
   RETVALUE(ROK);
#else
   Pst  *pst;
   pst = &wrDamCb.wrAppPst;
   RETVALUE(cmPkDamCfgCfm(pst,cfg,cfgCfm));
#endif
} /*wrIfmDamWrCfgCfm*/

/** @brief This function is used to send the control confirm back to the Application.
 *
 * @details
 *
 *     Function: wrIfmDamWrCntrlCfm 
 *
 *         Processing steps:
 *         - This function is invoked by the DAM module to send the confirm for the same. 
 *         - This function invokes the pack function for sending the confirm.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamWrCntrlCfm
(
CmStatus   *status,
LwrMngmt    *cntrl
)
{
   TRC2(wrIfmDamWrCntrlCfm);

   wrDamGenerateCfm(&wrDamCb.init.lmPst, status, TCNTRL, cntrl);
   RETVALUE(ROK);
} /*wrIfmDamWrCntrlCfm*/

/** @brief This function is used to send UE Context release to Application. 
 *
 * @details
 *
 *     Function:wrIfmDamWrCtxtRel
 *
 *         Processing steps:
 *         - This function is invoked by the DAM module to send Context release to app. 
 *         - This function invokes the pack function for sending the conetxt release.
 *
 * @param[in] crnti: UE Identifier.  
 * @param[in] cellId: Cell ID.  
 * @param[in] event: Event causing context release.  
 * @return  Void 
 */
PUBLIC Void wrIfmDamWrCtxtRel
(
U16                    crnti,
U16                    cellId,
U8                     event 
)
{
   Pst  *pst;

   TRC2(wrIfmDamWrCtxtRel);
   pst = &wrDamCb.wrAppPst;

   (*EuUiDamSendCtxtRelMt[pst->selector])(pst,crnti,cellId,event);
   RETVOID;
}

/*
 *       Fun:     wrSendLmAlarm
 *
 *       Desc:    Function trigger alarm
 *
 *       Ret:     ROK   - ok
 *
 *       Notes :  None
 */
PUBLIC Void wrIfmDamWrSendLmAlarm
(
U16                          category,
U16                          event,
U16                          cause
)
{
   TRC2(wrIfmDamWrSendLmAlarm);
   wrSendDamLmAlarm(category,event,cause);
   RETVOID;
}/* wrIfmDamWrSendLmAlarm */


/** @brief This function is used to handle the Datacfm came from PDCP.
 *
 * @details
 *
 *     Function:wrIfmDamWrPdcpDatCfm 
 *
 *         Processing steps:
 *         - Function invoke by DAM Module to send the data confirm message.
 *
 * @param[in]  pdcpId: pointer to CmLtePdcpId structure
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PUBLIC S16  wrIfmDamWrPdcpDatCfm
(
CmLtePdcpId pdcpId
)
{
   Pst *pst;
   TRC2(wrIfmDamWrPdcpDatCfm);
   pst = &wrDamCb.wrAppPst;
   (*EuUiDamPdcpDatCfmMt[pst->selector])(pst, pdcpId);
   RETVALUE(ROK);

} /* end of  wrIfmDamWrPdcpDatCfm*/


/** @brief This function is used to an EGTP create tuunel.
 *
 * @details
 *
 *     Function: wrIfmDamWrTnlCreatReq
 *
 *         Processing steps:
 *         - This function is invoked by the UMM module to ceate a EGTP tunnel.
 *         - This function invokes the function wrDamTnlCreatReq to create
 *           tunnel.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]  tnlInfo: Tunnel Info which needs to be create.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamWrTnlCreatReq
(
U32                          transId,
WrDamTnlInfo                 *tnlInfo
)
{
   TRC2(wrIfmDamWrTnlCreatReq);
   wrDamTnlCreatReq(transId, tnlInfo);
   RETVALUE(ROK);
} /*wrIfmDamWrTnlCreatReq */

/** @brief This function informs the tunnel was ceated successfully with local
 *         teid or tunnel was not created to the UMM Module. 
 *
 * @details
 *
 *     Function: wrIfmDamWrTnlCreatCfm
 *
 *         Processing steps:
 *         - This function is process the tunnel creation conformation from DAM
 *           module.
 *         - This function invokes the UMM Module function wrUmmTnlCreatCfm to
 *           process the tunnel create conformation from DAM.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   status: status of tunnel creation.
 * @param[in]  lclTeid: Local Tunnel ID.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamWrTnlCreatCfm
(
U32                          transId,
U8                           status,
U32                          lclTeid
)
{
   Pst *pst;
   TRC2(wrIfmDamWrTnlCreatCfm);

   pst = &wrDamCb.wrAppPst;
   (*EuUiDamTnlCreatCfmMt[pst->selector])(pst, transId, status, lclTeid);
   RETVALUE(ROK);
} /*wrIfmDamWrTnlCreatCfm*/

/* ccpu00126336 */
/** @brief This function is used to modify a EGTP tunnel.
 *
 * @details
 *
 *     Function: wrIfmDamWrTnlModReq
 *
 *         Processing steps:
 *         - This function is invoked by the UMM module to ceate a EGTP tunnel.
 *         - This function invokes the function wrDamTnlModReq to create
 *           tunnel.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]  tnlInfo: Tunnel Info which needs to be created.
 * @return Void 
 */
PUBLIC Void wrIfmDamWrTnlModReq
(
U32                          transId,
WrDamTnlModInfo              *tnlModInfo
)
{
   TRC2(wrIfmDamWrTnlModReq);
   wrDamTnlModReq(transId, tnlModInfo);
   WR_FREE_DATA_APP_SHAREBLE_BUF(tnlModInfo, sizeof(WrDamTnlModInfo));
   RETVOID;
} /*wrIfmDamWrTnlModReq */

/* ccpu00126336 */
/** @brief This function informs the tunnel was updated successfully with local
 *         teid or tunnel was not created to the UMM Module. 
 *
 * @details
 *
 *     Function: wrIfmDamTnlModCfm
 *
 *         Processing steps:
 *         - This function processes the tunnel modification confirmation from DAM
 *           module.
 *         - This function invokes the UMM Module function wrUmmTnlCreatCfm to
 *           process the tunnel create confirmation from DAM.
 *
 * @param[in]  transId : Transaction ID. 
 * @param[in]  status  : status of tunnel creation.
 * @param[in]  lclTeid : Local Tunnel ID.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamWrTnlModCfm
(
U32                          transId,
U8                           status,
U32                          lclTeId
)
{
   Pst *pst;
   TRC2(wrIfmDamWrTnlModCfm);

   pst = &wrDamCb.wrAppPst;
   (*EuUiDamTnlModCfmMt[pst->selector])(pst, transId, status, lclTeId);
   RETVALUE(ROK);

} /*wrIfmDamWrTnlModCfm*/

/** @brief This function will be called to send delete tunnel to the DAM.
 *
 * @details
 *
 *     Function:wrIfmDamWrTnlDelReq 
 *
 *         Processing steps:
 *         - Call the function wrDamTnlDelReq to delete the tunnel 
 *           in DAM Module.
 *         - This function is invoked by UMM Module to delete a particular tunnel
 *           information in DAM.
 *
 * @param[in]  transId : Transaction ID. 
 * @param[in]  tnlId   : Tunnel ID which is going to be delete.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC Void wrIfmDamWrTnlDelReq
(
U32                          transId,
WrDamTnlId                   *tnlId
)
{
   TRC2(wrIfmDamWrTnlDelReq);
   wrDamTnlDelReq(transId, tnlId);
   WR_FREE_DATA_APP_SHAREBLE_BUF(tnlId, sizeof(WrDamTnlId));
   RETVOID;
} /*wrIfmDamWrTnlDelReq*/

/** @brief This function is used to send the DAM Configuration to Delete the UE.
 *         
 * @details
 *
 *     Function: wrIfmDamWrUeDelReq
 *
 *         Processing steps:
 *         - This function will be invoked by unpack function.
 *         - Calls the function wrDamUeDelReq to send the UE Delete Req in DAM. 
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]  cellId : Cell ID required to retrieve the UE. 
 * @param[in]  crnti  : CRNTI Cell Specific UE identifier.
 * @return Void  
 */
PUBLIC Void wrIfmDamWrUeDelReq
(
U32                          transId,
U16                          cellId,
U16                          crnti
)
{
   TRC2(wrIfmDamWrUeDelReq);
   wrDamUeDelReq(transId, cellId, crnti);
   RETVOID;
} /*wrIfmDamWrUeDelReq*/

/** @brief This function is used to informs to the UMM Module the UE 
 * deletion was successful from Data  Application module.
 *
 * @details
 *
 *     Function: wrIfmDamWrUeDelCfm 
 *
 *         Processing steps:
 *         - This function is invoked by DAM module to inform the UE 
 *           deletaion was successful in DAM to the UMM.
 *         - Calls the UMM Module function wrUmmPrcDamUeDelCfm to process the
 *           delete conformation. 
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]  cellId: Cell ID required to retrieve the UE. 
 * @param[in]  crnti: CRNTI Cell Specific UE identifier.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamWrUeDelCfm
(
U32                          transId,
U16                          cellId,
U16                          crnti
)
{
   Pst *pst;
   TRC2(wrIfmDamWrUeDelCfm);
   pst = &wrDamCb.wrAppPst;
   (*EuUiDamUeDelCfmMt[pst->selector])(pst,transId, cellId,crnti);
   RETVALUE(ROK);
} /*wrIfmDamWrUeDelCfm*/

/** @brief This function validates the UE-ReConfiguration is possible or not in
 *         the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamWrReCfgReq 
 *
 *         Processing steps:
 *         - This function invokes the function wrDamReCfgReq.
 *         - This function is invoked by UMM Module during RRC connection 
 *           Reestablishment complete  processing.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   cellId: Cell ID. 
 * @param[in]   crnti : CRNTI. 
 * @return  Void 
 */
PUBLIC S16 wrIfmDamWrReCfgReq
(
U32                          transId,
U16                          cellId,
U16                          crnti
)
{
   TRC2(wrIfmDamWrReCfgReq);
   wrDamReCfgReq(transId, cellId, crnti);
   RETVALUE(ROK);
} /*wrIfmDamWrReCfgReq*/

/** @brief This function validates the UE-Reestablishment is possible or not in
 *         the Data Application Module.
 *
 * @details
 *
 *     Function:wrIfmDamWrReestabReq
 *
 *         Processing steps:
 *         - This function invokes the function wrDamReestabReq for validating
 *           the new and old CRNTIs for this UE by the Data Application Module. 
 *         - This function is invoked by UMM Module during RRC connection 
 *           Reestablishment Req processing.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   cellId: Cell ID. 
 * @param[in] oldcrnti: Old CRNTI.
 * @param[in] newcrnti: New CRNTI. 
 * @return Void  
 */
PUBLIC Void wrIfmDamWrReestabReq
(
U32                          transId,
U16                          cellId,
U16                          oldcrnti,
U16                          newcrnti
)
{
   TRC2(wrIfmDamWrReestabReq);
   wrDamReestabReq(transId, cellId, oldcrnti, newcrnti);
   RETVOID;
} /*wrIfmDamWrReestabReq */

/** @brief This function gets the UE Re-establishment Confirmation
 *         from Data Application Module. 
 *
 * @details
 *
 *     Function: wrIfmDamWrReestabCfm 
 *
 *         Processing steps:
 *         - This function invokes the function wrUmmPrcReestabCfm to validate
 *           the UE Re-establishment to handle -ve scenarios.
 *
 *
 * @param[in] transId: Transaction ID.  
 * @param[in]  status: Status of  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamWrReestabCfm
(
U32                          transId,
U8                           status
)
{
   Pst *pst;
   TRC2(wrIfmDamWrReestabCfm);
   pst = &wrDamCb.wrAppPst;
   (*EuUiDamReestabCfmMt[pst->selector])(pst, transId, status);
   RETVALUE(ROK);
} /*wrIfmDamWrReestabCfm */

/** @brief This function informs the new cell information 
 *         to the Data Application Module during cell creation. 
 *         
 * @details
 *
 *     Function: wrIfmDamWrCellAddReq
 *
 *         Processing steps:
 *         - Invokes the function wrDamCellAddReq to add cell information to
 *           Data Application Module.
 *         - This function invoked by EMM Module during new cell adding
 *           to enodeB.
 *
 * @param[in] cellInfo: Cell Information. 
 * @return Void  
 */
PUBLIC Void wrIfmDamWrCellAddReq
(
WrDamCellInfo                *cellInfo
)
{
   TRC2(wrIfmDamWrCellAddReq);
   wrDamCellAddReq(cellInfo);
   WR_FREE_DATA_APP_SHAREBLE_BUF(cellInfo, sizeof(WrDamCellInfo));
   RETVOID;
} /*wrIfmDamWrCellAddReq */

/** @brief This function forwards the state change request for a particular 
 *         tunnel to DAM.
 *         
 * @details
 *
 *     Function: wrIfmDamWrChngTnlState
 *
 *         Processing steps:
 *         - Invokes the function wrDamTnlStChngReq to process the request
 *
 * @param[in] tnlStInfo: State information for the tunnel.
 * @return  Void 
 */
PUBLIC Void wrIfmDamWrChngTnlState
(
WrDamTnlStInfo               *tnlStInfo
)
{
   TRC2(wrIfmDamWrChngTnlState);
   wrDamTnlStChngReq(tnlStInfo);
   WR_FREE_DATA_APP_SHAREBLE_BUF(tnlStInfo, sizeof(WrDamTnlStInfo));
   RETVOID;
} /*wrIfmDamWrChngTnlState*/


/** @brief This function forwards the S1-U error indication for a particular 
 *         tunnel to FSM.
 *         
 * @details
 *
 *     Function:wrIfmDamEgtpErrInd
 *
 *         Processing steps:
 *         - 
 *
 * @param[in] lclTeid: Local Teid.
 * @param[in] numDrbs: Drb count.
 * @param[in] ueId: crnti.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamEgtpErrInd
(
U32                          lclTeid,
U32                          numDrbs,
U16                          crnti 
)
{
    Pst        *pst;

    pst = &wrDamCb.wrAppPst;

   (*EuUiDamEgtpErrIndMt[pst->selector])(pst,lclTeid,numDrbs,crnti);
    RETVALUE(ROK);
} /* end of wrIfmDamEgtpErrInd*/

/*ccpu00138576 - start*/
/** @brief This function is used to set the data rcvd flag in DAM.
 *         
 * @details
 *
 *     Function: wrIfmDamWrSetDataRcvdFlag
 *
 *         Processing steps:
 *         - This function will be invoked by unpack function.
 *         - Calls the function wrDamSetDataRcvdFlag in wr_dam.c. 
 *
 * @param[in]  cellId : Cell ID required to retrieve the UE. 
 * @param[in]  ueId   : UE identifier.
 * @return Void  
 */
PUBLIC Void wrIfmDamWrSetDataRcvdFlag
(
U16                          cellId,
U16                          ueId 
)
{
   TRC2(wrIfmDamWrSetDataRcvdFlag);
   wrDamSetDataRcvdFlag(cellId, ueId);
   RETVOID;
} /*end of wrIfmDamWrSetDataRcvdFlag*/
/*ccpu00138576 - end*/

/********************************************************************30**

           End of file:     fc_dam_ifm_app.c@@/main/TeNB_Main_BR/6 - Mon Aug 11 16:51:33 2014

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
SID$        ---      Sriky         1. initial release TotaleNodeB 1.1
*********************************************************************91*/
