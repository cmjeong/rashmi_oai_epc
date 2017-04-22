
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_ifm_dam.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="IFM";
static int RLOG_MODULE_ID=4;
static int RLOG_FILE_ID=19;


#include "wr_cmn.h"
#include "wr_ifm_dam.h"
#include "wr_ifm_dam_utils.h"
#include "wr_ifm_dam_utils.x"
#include "wr_dam_ifm_app.h"
/**************************************************************************
 * DAM Interface Matrices
 *************************************************************************/
PRIVATE CONSTANT DamBndCfm EuUiDamBndCfmMt[] =
{
   cmPkDamBndCfm,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuLiDamBndCfm,       /* 1 - tightly coupled */
#else
   NULLP,
#endif
   cmPkDamBndCfm,        /* 2 - light weight loosely coupled */ 
};
/* DAM Interface Bind Request primitive */
PRIVATE CONSTANT DamBndReq WrIfmDamBndReqMt[] =
{
   cmPkDamBndReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamBndReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkDamBndReq        /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT  DamCntrlReq WrIfmDamCntrlReqMt[] =
{
   cmPkDamCntrlReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamCntrlReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkDamCntrlReq /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT  DamCfgReq WrIfmDamCfgReqMt[] =
{
   cmPkDamCfgReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamCfgReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkDamCfgReq /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT  DamTnlCreatReq WrIfmDamTnlCreatReqMt[] =
{
   cmPkTnlCreatReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamTnlCreatReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkTnlCreatReq /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT  DamStartInactivityTmr WrIfmDamStartInactivityTimerMt[] =
{
   cmPkStartInactivityTimer,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamStartInactivityTmr,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkStartInactivityTimer /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT DamTnlModReq  WrIfmDamTnlModReqMt[] =
{
   cmPkTnlModReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamTnlModReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkTnlModReq /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT DamTnlDelReq  WrIfmDamTnlDelReqMt[] =
{
   cmPkTnlDelReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamTnlDelReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkTnlDelReq /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT DamUeDelReq  WrIfmDamUeDelReqMt[] =
{
   cmPkUeDelReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamUeDelReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkUeDelReq /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT DamReCfgReq WrIfmDamReCfgReqMt[] =
{
   cmPkReCfgReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamReCfgReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkReCfgReq /* 2 - light weight loosely coupled */
};


PRIVATE CONSTANT DamReestabReq WrIfmDamReestabReqMt[] =
{
   cmPkReestabReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamReestabReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkReestabReq /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT DamCellAddReq WrIfmDamCellAddReqMt[] =
{
   cmPkCellAddReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamCellAddReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkCellAddReq /* 2 - light weight loosely coupled */
};


PRIVATE CONSTANT DamTnlStChngReq WrIfmDamChngTnlStateMt[] =
{
   cmPkTnlStChngReq,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamTnlStChngReq,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkTnlStChngReq/* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT  DamHoFailure WrIfmDamHdlHoFailureMt[] =
{
   cmPkHdlHoFailure,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamHdlHoFailure,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkHdlHoFailure /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT  DamStopUeTmr WrIfmDamStopUeTmrMt[] =
{
   cmPkStopUeTmr,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamStopUeTmr,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkStopUeTmr /* 2 - light weight loosely coupled */
};

PRIVATE CONSTANT  DamSetDataRcvdFlag WrIfmDamSetDataRcvdFlagMt[] =
{
   cmPkSetDataRcvdFlag,       /* 0 - loseely coupled */
 #ifndef LCDAM
   EuUiDamSetDataRcvdFlag,       /* 1 - tightly coupled */
 #else
   NULLP,
 #endif
   cmPkSetDataRcvdFlag /* 2 - light weight loosely coupled */
};
/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamCntrlReq 
 *
 *         Processing steps:
 *         - This function invokes the function wrDamCntrlReq to process the
 *           control Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 wrIfmDamCntrlReq
(
LwrMngmt    *cntrl
)
{
   Pst  *pst;
  
#ifdef  TIP_L3_UL2_LL2_SPLIT
   U16 cellId = 0;
   pst = &wrCb.damSap[cellId]->pst;
   /* CellID is same as sapId */
   cellId = cntrl->t.cntrl.u.sapId;
#else
   pst = &wrCb.wrDamPst;
#endif
  (*WrIfmDamCntrlReqMt[pst->selector])(pst, cntrl);
   RETVALUE(ROK);
} /* wrIfmDamCntrlReq */

/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamCfgReq 
 *
 *         Processing steps:
 *         - This function is invoked by Stack manager to configre the DAM
 *           module 
 *         - This function invokes the function wrDamCfgReq to process the
 *           configuration Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamCfgReq
(
LwrMngmt *cfg
)
{
   Pst *pst;
#ifdef  TIP_L3_UL2_LL2_SPLIT
   pst = &wrCb.damSap[cfg->t.cfg.t.lSap.suId]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
  (*WrIfmDamCfgReqMt[pst->selector])(pst, cfg);
   RETVALUE(ROK);

} /* wrIfmDamCfgReq */


/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamSendAlarmInd 
 *
 *         Processing steps:
 *         - This function invokes the function wrSendLmAlarm to process the
 *           Alarm Indication.
 *
 * @param[in] U16     category.  
 * @param[in] U16     event.  
 * @param[in] U16     cause.  
 * @return Void
 */
PUBLIC Void  wrIfmDamSendAlarmInd
(
U16     category,
U16     event,
U16     cause
)
{
   wrSendLmAlarm(category,event,cause);

} /*wrIfmDamSendAlarmInd*/


/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamCntrlCfm 
 *
 *         Processing steps:
 *         - This function is invoked by Stacke maager to configre the DAM
 *           module 
 *         - This function invokes the function wrDamCfg to process the
 *           configuration Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamCntrlCfm
(
LwrMngmt    *cntrl,
CmStatus   *cfmStatus
)
{
   Pst pst;
   cmMemset((U8*)&pst, 0, sizeof(Pst));
#ifdef TENB_T2K3K_SPECIFIC_CHANGES
   switch (cntrl->hdr.elmId.elmnt)
   { 
      case STWRGEN: 
      {
         switch (cntrl->t.cntrl.action)
         {
            case ASHUTDOWN:
            {
               cmMemcpy((U8*)&pst, (U8*)&(wrCb.init.lmPst), sizeof(Pst));
               pst.srcEnt    = wrCb.init.lmPst.dstEnt;
               pst.srcInst   = wrCb.init.lmPst.dstInst;
               pst.srcProcId = wrCb.init.lmPst.dstProcId;
               wrShutdown();
               break;
            }
            default :
            {
               break;
            }
         }
         break;
      }
      default :
      {
         break;
      }
   }
#endif
   wrGenerateCfm(NULLP,cfmStatus,TCNTRL,cntrl);
   RETVALUE(ROK);
} /*wrIfmDamCntrlCfm*/

/** @brief This function is used to configure the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamCfgCfm 
 *
 *         Processing steps:
 *         - This function is invoked by Stacke maager to configre the DAM
 *           module 
 *         - This function invokes the function wrDamCfg to process the
 *           configuration Req.
 *
 * @param[in] cfg: Data Application Module Configuration.  
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamCfgCfm
(
LwrMngmt  *cfg,
CmStatus *cfmStatus
)
{
   Pst *pst = NULLP;
   wrGenerateCfm(pst,cfmStatus,TCFG,cfg);
   RETVALUE(ROK);
} /* end of wrIfmDamCfgCfm*/


/* RLC_DL_MAX_RETX fix */
/** @brief This function is used to handle the Datcfm came from PDCP.
 *
 * @details
 *
 *     Function: wrIfmDamPdcpDatCfm
 *
 *         Processing steps:
 *
 * @param[in]  pdcpId: pointer to CmLtePdcpId structure
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PUBLIC S16  wrIfmDamPdcpDatCfm
(
CmLtePdcpId pdcpId
)
{
   
   TRC2(wrIfmDamPdcpDatCfm);

   if (wrUmmPdcpDatCfm(pdcpId) != ROK)
   {
      /* Log error */
      RLOG0(L_ERROR, "wrIfmDamPdcpDatCfm: wrUmmSndCtxtRelReqn Failed");
      RETVALUE(RFAILED);
   }
   RETVALUE(ROK);
} /*wrIfmDamPdcpDatCfm*/


/** @brief This function is used to an EGTP create tuunel.
 *
 * @details
 *
 *     Function: wrIfmDamTnlCreatReq
 *
 *         Processing steps:
 *         - This function is invoked by the UMM module to ceate a EGTP tunnel.
 *         - This function invokes the function wrDamTnlCreatReq to create
 *           tunnel.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]  tnlInfo: Tunnel Info whhic needs to be create.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamTnlCreatReq
(
U32                          transId,
WrDamTnlInfo                 *tnlInfo
)
{
   Pst *pst;

#ifdef TIP_L3_UL2_LL2_SPLIT
   U16 cellId = 0;
   cellId = tnlInfo->tnlId.cellId;
   pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
  (*WrIfmDamTnlCreatReqMt[pst->selector])(pst, transId,tnlInfo);
   RETVALUE(ROK);
} /* end of wrIfmDamTnlCreatReq */

/** @brief This function is used to start UE timers at DAM module
 *
 * @details
 *
 *     Function: wrIfmDamStartInactivityTimer
 *
 *         Processing steps:
 *         - This function is invoked by the UMM module to start the inactivity timer.
 *         - This function invokes the function wrDamStartUeTmr to start
 *           timer.
 *
 * @param[in]  cellID : Cell ID. 
 * @param[in]  RNTI : RNTI 
 * @param[in]  Event :Type of the timer to start. 
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamStartInactivityTimer
(
 U16                         cellId,
 U16                         crnti
 )
{
    Pst *pst;

#ifdef TIP_L3_UL2_LL2_SPLIT
    pst = &wrCb.damSap[cellId-1]->pst;
#else
    pst = &wrCb.wrDamPst;
#endif     
    (*WrIfmDamStartInactivityTimerMt[pst->selector])(pst, cellId,crnti);
    RETVALUE(ROK);
} /* end of wrIfmDamStartInactivityTimer*/

/** @brief This function informs the tunnel was ceated successfully with local
 *         teid or tunnel was not created to the UMM Module. 
 *
 * @details
 *
 *     Function: wrIfmDamTnlCreatCfm
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
PUBLIC S16 wrIfmDamTnlCreatCfm
(
U32                          transId,
U8                           status,
U32                          lclTeid
)
{
   wrUmmTnlCreatCfm(transId, status, lclTeid);
   RETVALUE(ROK);
} /* end of wrIfmDamTnlCreatCfm */

/* ccpu00126336 */
/** @brief This function is used to modify a EGTP tunnel.
 *
 * @details
 *
 *     Function: wrIfmDamTnlModReq
 *
 *         Processing steps:
 *         - This function is invoked by the UMM module to ceate a EGTP tunnel.
 *         - This function invokes the function wrDamTnlModReq to create
 *           tunnel.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]  tnlInfo: Tunnel Info whhic needs to be create.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamTnlModReq
(
U32                          transId,
WrDamTnlModInfo              *tnlModInfo
)
{
   Pst *pst;
#ifdef TIP_L3_UL2_LL2_SPLIT
   U16 cellId = 0;

   cellId = tnlModInfo->tnlId.cellId;
   pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamTnlModReqMt[pst->selector])(pst,transId,tnlModInfo);
   RETVALUE(ROK);
} /* end of wrIfmDamTnlModReq */

/* ccpu00126336 */
/** @brief This function informs the tunnel was updated successfully with local
 *         teid or tunnel was not created to the UMM Module. 
 *
 * @details
 *
 *     Function: wrIfmDamTnlModCfm
 *
 *         Processing steps:
 *         - This function is process the tunnel modification confirmation from DAM
 *           module.
 *         - This function invokes the UMM Module function wrUmmTnlCreatCfm to
 *           process the tunnel create confirmation from DAM.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   status: status of tunnel creation.
 * @param[in]  lclTeid: Local Tunnel ID.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamTnlModCfm
(
U32                          transId,
U8                           status,
U32                          lclTeId
)
{
   wrUmmTnlModCfm(transId, status, lclTeId);
   RETVALUE(ROK);
} /* end of wrIfmDamTnlModCfm*/

/** @brief This function will be caled to send delete tunnel to the DAM.
 *
 * @details
 *
 *     Function:wrIfmDamTnlDelReq 
 *
 *         Processing steps:
 *         - Call the function wrDamTnlDelReq to delete the tunnel 
 *           in DAM Module.
 *         - This function is invoked by UMM Module to delete a particular tunel
 *           information in DAM.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]    tnlId: Tunnel ID which is going to be delete.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamTnlDelReq
(
U32                          transId,
WrDamTnlId                   *tnlId
)
{
   Pst *pst;
#ifdef TIP_L3_UL2_LL2_SPLIT
   U16 cellId = 0;
   cellId = tnlId->cellId;
   pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamTnlDelReqMt[pst->selector])(pst,transId, tnlId);
   RETVALUE(ROK);
} /* end of wrIfmDamTnlDelReq */

/** @brief This function is used to send the DAM Configuration to Delete the UE.
 *         information in DAM.
 * @details
 *
 *     Function: wrIfmDamUeDelReq
 *
 *         Processing steps:
 *         - This function will be invoked by UMM Module.
 *         - Calls the function wrDamUeDelReq to send the UE Delete Req in DAM. 
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   cellId: Cell ID. 
 * @param[in]    crnti: CRNTI.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamUeDelReq
(
U32                          transId,
U16                          cellId,
U16                          crnti
)
{
   Pst *pst;
#ifdef TIP_L3_UL2_LL2_SPLIT
   pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamUeDelReqMt[pst->selector])(pst, transId, cellId, crnti);
   RETVALUE(ROK);
} /* end of wrIfmDamUeDelReq */

/** @brief This function is used to informs to the UMM Module the tunnel
 * deletion was successful from Data  Application module.
 *
 * @details
 *
 *     Function: wrIfmDamUeDelCfm 
 *
 *         Processing steps:
 *         - This function is invoked by DAM module to inform the tuunel
 *           deletaion was successful in DAM to the UMM.
 *         - Calls the UMM Module function wrUmmPrcDamUeDelCfm to process the
 *           delete conformation. 
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   cellId: Cell ID. 
 * @param[in]    crnti: CRNTI.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamUeDelCfm
(
U32                          transId,
U16                          cellId,
U16                          crnti
)
{
   wrUmmPrcDamUeDelCfm(transId, cellId, crnti);
   RETVALUE(ROK);
} /* end of wrIfmDamUeDelCfm */

/** @brief This function validates the UE-ReConfiguration is possible or not in
 *         the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamReCfgReq 
 *
 *         Processing steps:
 *         - This function invokes the function wrDamReCfgReq.
 *         - This function is invoked by UMM Module during RRC connection 
 *           Reestablishment complete  processing.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   cellId: Cell ID. 
 * @param[in]   crnti : CRNTI. 
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamReCfgReq
(
U32                          transId,
U16                          cellId,
U16                          crnti
)
{
   Pst *pst;

#ifdef TIP_L3_UL2_LL2_SPLIT
   pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamReCfgReqMt[pst->selector])(pst, transId, cellId, crnti);
   RETVALUE(ROK);
} /* end of wrIfmDamReCfgReq */

/** @brief This function validates the UE-Reestablishmint is possible or not in
 *         the Data Application Module.
 *
 * @details
 *
 *     Function: wrIfmDamReestabReq 
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
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamReestabReq
(
U32                          transId,
U16                          cellId,
U16                          oldcrnti,
U16                          newcrnti
)
{
   Pst *pst;

#ifdef TIP_L3_UL2_LL2_SPLIT
   pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamReestabReqMt[pst->selector])(pst, transId,cellId,oldcrnti,newcrnti);
   RETVALUE(ROK);
} /* end of wrIfmDamReestabReq */

/** @brief This function gets the UE Re-establishment Conformation
 *         from Data Application Module. 
 *
 * @details
 *
 *     Function: wrIfmDamReestabCfm 
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
PUBLIC S16 wrIfmDamReestabCfm
(
U32                          transId,
U8                           status
)
{
   wrUmmPrcReestabCfm(transId, status);
   RETVALUE(ROK);
} /* end of wrIfmDamReestabCfm */

/** @brief This function informs the new cell information 
 *         to the Data Application Module during cell creation. 
 *         
 * @details
 *
 *     Function: wrIfmDamCellAddReq
 *
 *         Processing steps:
 *         - Invokes the function wrDamCellAddReq to add cell information to
 *           Data Application Module.
 *         - This function invoked by EMM Module during new cell adding
 *           to enodeB.
 *
 * @param[in] cellInfo: Cell Information. 
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamCellAddReq
(
WrDamCellInfo                *cellInfo
)
{
   Pst *pst = NULLP;
#ifdef TIP_L3_UL2_LL2_SPLIT
   WrLiSapCb *sap = NULLP;
   /* SAP ID is cellId minus one */
   sap = wrCb.damSap[cellInfo->cellId-1];
   pst = &sap->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamCellAddReqMt[pst->selector])(pst,cellInfo);
   RETVALUE(ROK);
} /* end of wrIfmDamCellAddReq */

/** @brief This function forwards the state chagne request for a particular 
 *         tunnel to DAM.
 *         
 * @details
 *
 *     Function: wrIfmDamTnlStChngReq
 *
 *         Processing steps:
 *         - Invokes the function wrDamTnlStChngReq to process the request
 *
 * @param[in] tnlStInfo: State information for the tunnel.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamChngTnlState
(
WrDamTnlStInfo               *tnlStInfo,
U16                          cellId
)
{
    Pst *pst;
#ifdef TIP_L3_UL2_LL2_SPLIT
    pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamChngTnlStateMt[pst->selector])(pst,tnlStInfo);
    RETVALUE(ROK);
} /* end of wrIfmDamChngTnlState*/

/* HO_REEST */
/** @brief This function deletes the FWD tunnels and set the state chagne
 * request for particular drb
 *
 * @details
 *
 *     Function: wrIfmDamHdlHoFailure
 *
 *         Processing steps:
 *         - Invokes the function wrDamHdlHoFailure to process the request
 *
 * @param[in] tnlStInfo: State information for the tunnel.
 * @return S16
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamHdlHoFailure
(
U16                          cellId,
U16                          crnti
)
{
    Pst *pst;
#ifdef TIP_L3_UL2_LL2_SPLIT
    pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamHdlHoFailureMt[pst->selector])(pst,cellId,crnti);
    RETVALUE(ROK);
} /* end of wrIfmDamHdlHoFailure */


/** @brief This function forwards the state chagne request for a particular 
 *         tunnel to DAM.
 *         
 * @details
 *
 *     Function:wrIfmDamStopUeTmr 
 *
 *         Processing steps:
 *         - 
 *
 * @param[in] tnlStInfo: State information for the tunnel.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamStopUeTmr
(
U16                          cellId,
U16                          ueId
)
{
    Pst *pst;
#ifdef TIP_L3_UL2_LL2_SPLIT
    pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif

   (*WrIfmDamStopUeTmrMt[pst->selector])(pst,cellId,ueId);
    RETVALUE(ROK);
} /* end of wrIfmDamStopUeTmr*/

/*ccpu00138576 - start*/
/** @brief This function forwards the state chagne request for a particular 
 *         tunnel to DAM.
 *         
 * @details
 *
 *     Function:wrIfmDamSetDataRcvdFlag
 *
 *         Processing steps:
 *         - 
 *
 * @param[in] cellId.
 * @param[in] ueId.
 * @return S16 
 *        -# Success : ROK
 */
PUBLIC S16 wrIfmDamSetDataRcvdFlag
(
U16                          cellId,
U16                          ueId
)
{
    Pst *pst;
#ifdef TIP_L3_UL2_LL2_SPLIT
    pst = &wrCb.damSap[cellId-1]->pst;
#else
   pst = &wrCb.wrDamPst;
#endif
   (*WrIfmDamSetDataRcvdFlagMt[pst->selector])(pst,cellId,ueId);
    RETVALUE(ROK);
} /* end of wrIfmDamSetDataRcvdFlag*/
/*ccpu00138576 - end*/


/** @brief This function is responsible for Sending Bind request.
 *
 * @details
 *
 * Function:WrIfmDamBndReq
 *
 *   Processing steps:
 *    - based on selector present in Post structure return appropriate function
 *       pointer.
 *
 *  @param[in]  pst: Pointer to the Post structure
 *  @param[in]  suId: Service user Id
 *  @param[in]  spId: Service Provider Id
 *  @return S16
 *       SUCCESS : ROK
 *       FAILED  : RFAILED
 */
PUBLIC S16 WrIfmDamBndReq
(
Pst*                         pst,
SuId                         suId,
SpId                         spId
)
{
  TRC3(WrIfmDamBndReq)

#ifdef TIP_L3
   WrIfmDamBndCfm(pst, suId, CM_BND_OK);
#else
  (*WrIfmDamBndReqMt[pst->selector])(pst, suId, spId);
#endif

   RETVALUE(ROK);
}


/** @brief This function is responsible for Sending DAM Bind confirm.
 *
 * @details
 *
 * Function:WrIfmDamBndCfm
 *
 *   Processing steps:
 *    - check the status 
 *    - process the alarm
 *
 *  @param[in]  pst: Post structure
 *  @param[in]  suId: SuId structure
 *  @param[in]  status: Status
 *  @return S16
 *       SUCCESS : ROK
 *       FAILED  : RFAILED
 */
PUBLIC S16 WrIfmDamBndCfm 
(
Pst                         *pst,
SuId                         suId,
U8                           status
)
{
   TRC2(WrIfmDamBndCfm);

   RLOG0(L_DEBUG, "WrIfmDamBndCfm: DAM Bind Cfm.");

   /* Send alarm */
   if (CM_BND_OK == status)
   {
      RLOG0(L_INFO, "[ALARM] Sending DAM_SAP_BND_OK to OAM");
      wrStopTmr((PTR)wrCb.damSap[suId],WR_TMR_DAM_SAP_BND);
      wrSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_OK, LWR_CAUSE_DAM_SAP_BOUND);
   }
   else
   {
      RLOG0(L_FATAL, "[ALARM] Sending DAM_SAP_BND_FAIL to OAM");
      wrStopTmr((PTR)wrCb.damSap[suId],WR_TMR_DAM_SAP_BND);
      wrSendLmAlarm(LCM_CATEGORY_INTERFACE, LCM_EVENT_BND_FAIL, LCM_CAUSE_UNKNOWN);
   }

   
   RETVALUE(ROK);
} /* WrIfmDamBndCfm */

/**
 * @brief  Handles the bind cfm from DAM.
 *
 *      @details  This function handles the bind cfm from DAM at the data 
 *             plane.
 *
 *     @param[in] pst    Post structure
 *     @param[in] suId   Service user SAP ID
 *     @param[in] status Status of bind request
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED 
 **/      
#ifdef ANSI
PUBLIC S16 EuLiDamBndCfm
(
Pst       *pst,         
SuId      suId,        
U8        status      
)
#else /* ANSI */
PUBLIC S16 EuLiDamBndCfm(pst, suId, status)
Pst       *pst;      
SuId      suId;     
U8        status;  
#endif /* ANSI */
{
   TRC2(EuLiDamBndCfm);

   RETVALUE(WrIfmDamBndCfm(pst,suId,status));
} /* end of EuLiDamBndCfm*/

#ifdef ANSI
PUBLIC S16 EuUiDamBndCfm
(
Pst* pst,
SuId suId,
U8 status
)
#else
PUBLIC S16 EuUiDamBndCfm(pst, suId, status)
Pst* pst;
SuId suId;
U8 status;
#endif
{

   TRC3(EuUiDamBndCfm)
#ifdef TIP_UPPER_L2
  RLOG1(L_DEBUG, "BIND OF APP DAM IS SUCCESSFUL suId = %d", suId);
#else
   (*EuUiDamBndCfmMt[pst->selector])(pst, suId, status);
#endif
   RETVALUE(ROK);
}

/**
 *
 * @brief 
 *
 *        Handler for binding the DAM upper layer service user with 
 *        the DAM layer.
 *
 * @b Description:
 *
 *        1. This function is used by DAM user to request for binding to 
 *        DAM.
 *        2. This function is called by the DAM interface to bind 
 *        DAM's SAP (identified by spId) with the service user's
 *        SAP (identified by suId). 
 *
 *  @param[in] pst   Post structure  
 *  @param[in] suId  Service user SAP ID 
 *  @param[in] spId  Service provider ID
 *
 *  @return  S16
 *      -# ROK 
 *      -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 EuUiDamBndReq 
(
Pst       *pst,    
SuId      suId,   
SpId      spId     
)
#else
PUBLIC S16 EuUiDamBndReq (pst, suId, spId)
Pst       *pst;    
SuId      suId;    
SpId      spId;    
#endif
{
   S16       ret = ROK;

   TRC3(EuUiDamBndReq)

      /* Check the state of the SAP */
      switch (wrDamCb.appSap[0]->sapState)
      {
         case DAM_SAP_UBND: /* SAP is not bound */
            {
               RLOG0(L_DEBUG,"SAP Not yet bound");
               wrDamCb.appSap[0]->sapState = DAM_SAP_BND;
               wrDamCb.appSap[0]->suId = suId;
               wrDamCb.appSap[0]->pst.dstProcId = pst->srcProcId;
               wrDamCb.appSap[0]->pst.dstEnt    = pst->srcEnt;
               wrDamCb.appSap[0]->pst.dstInst   = pst->srcInst;

               /* DEBUG_PRINT */
               RLOG1(L_DEBUG, "EuUiDamBndReq: state (%d)", wrDamCb.appSap[0]->sapState);
               break;
            }
         case DAM_SAP_BND: /* SAP is already bound*/
            {
               RLOG0(L_DEBUG,"SAP is already bound");
               /* 
                * Sap is already bound check source, destination Entity and 
                * Proc Id
                */
               if (wrDamCb.appSap[0]->pst.dstProcId != pst->srcProcId 
                     || wrDamCb.appSap[0]->pst.dstEnt != pst->srcEnt
                     || wrDamCb.appSap[0]->pst.dstInst != pst->srcInst
                     || wrDamCb.appSap[0]->suId != suId)
               {
                  RLOG4(L_DEBUG, "Ui DAM Bnd Req suId(%d)<>suId(%d),"
                        "pst->srcProcId(%d)<>wrDamCb.appSap[0]->pst.dstProcId(%d)",
                        suId, wrDamCb.appSap[0]->suId, pst->srcProcId, wrDamCb.appSap[0]->pst.dstProcId);

                  RLOG4(L_DEBUG,"Ui DAM Bnd Req pst->srcEnt(%d)<>wrDamCb.appSap[0]->pst.dstEnt"
                        "(%d),pst->srcInst(%d)<>wrDamCb.appSap[0]->pst.dstInst(%d))",
                        pst->srcEnt,wrDamCb.appSap[0]->pst.dstEnt,pst->srcInst,wrDamCb.appSap[0]->pst.dstInst);

                  wrIfmDamSendAlarmInd(LCM_CATEGORY_INTERFACE,LCM_EVENT_BND_FAIL, LCM_CAUSE_INV_STATE);
                  ret = RFAILED;
                  break;
               }
            }
         default: /* Should Never Enter here */
            {
               RLOG0(L_ERROR, "Invalid DAM SAP State in Bind Req");

               wrIfmDamSendAlarmInd(LCM_CATEGORY_INTERFACE,LCM_EVENT_BND_FAIL, LCM_CAUSE_INV_STATE);
               ret = RFAILED;
               break;
            }
      }

   if (ret == ROK)
   {
      EuUiDamBndCfm(&(wrDamCb.appSap[0]->pst), suId, CM_BND_OK);
   }
   else
   {
      EuUiDamBndCfm(&(wrDamCb.appSap[0]->pst), suId, CM_BND_NOK);
   }

   RETVALUE(ret);

} /*  EuUiDamBndReq */

/** @brief This function is used to set the data rcvd flag in DAM.
 *         
 * @details
 *
 *     Function: EuUiDamSetDataRcvdFlag
 *
 *         Processing steps:
 *         - This function will be invoked by unpack function.
 *         - Calls the function wrIfmDamWrSetDataRcvdFlag in wr_dam_ifm_app.c. 
 *
 * @param[in]  cellId : Cell ID required to retrieve the UE. 
 * @param[in]  ueId   : UE identifier.
 * @return Void  
 */
#ifdef ANSI
PUBLIC S16 EuUiDamSetDataRcvdFlag 
(
Pst         *pst,
U16      cellId,   
U16      ueId     
)
#else
PUBLIC S16 EuUiDamSetDataRcvdFlag(pst, cellId, ueId)
Pst         *pst;
U16      cellId;    
U16      ueId; 
#endif
{
   TRC3(EuUiDamSetDataRcvdFlag)
   wrIfmDamWrSetDataRcvdFlag(cellId,ueId);

   RETVALUE(ROK);
}


/** @brief This function is called when RRC Re-establishment received from UE at
 * source(both S1 and X2) during HO. It will delete the UL/DL Fowarding tunnels
 * and set the state of DrbCn to NORMAL
 * @details
 *
 *     Function: wrDamHdlHoFailure
 *
 *         Processing steps:
 *         - handle the start timer indication
 *
 * @param[in]  cellId  : Cell ID required to retrieve the UE. 
 * @param[in]  crnti  : UE identifier.
 * @return S16
 *    -#Success : ROK
 */
#ifdef ANSI
PUBLIC S16 EuUiDamHdlHoFailure 
(
Pst         *pst,
U16      cellId,   
U16      crnti 
)
#else
PUBLIC S16 EuUiDamHdlHoFailure(pst, cellId, crnti)
Pst         *pst;
U16      cellId;    
U16      crnti    
#endif
{
   TRC3(EuUiDamHdlHoFailure)
   wrDamHdlHoFailure(cellId,crnti);

   RETVALUE(ROK);
}

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
#ifdef ANSI
PUBLIC S16 EuUiDamTnlModReq 
(
Pst             *pst,
U32             transId,
WrDamTnlModInfo *tnlModInfo
)
#else
PUBLIC S16 EuUiDamTnlModReq(pst, transId, tnlModInfo)
Pst         *pst;
U16      transId;    
U16      tnlModInfo    
#endif
{
   TRC3(EuUiDamTnlModReq)
   wrIfmDamWrTnlModReq(transId,tnlModInfo);

   RETVALUE(ROK);
}

/** @brief This function is used to configure the Data Application Module.
*
* @details
*
*     Function: EuUiDamCntrlReq 
*
*         Processing steps:
*         - This function is invoked by Stack manager to configre the DAM
*           module 
*         - This function invokes the function wrDamCntrlReq to process the
*           control req.
*
* @param[in] cntrl: Data Application Module Configuration.  
* @return  Void 
*/
#ifdef ANSI
PUBLIC S16 EuUiDamCntrlReq 
(
Pst         *pst,
LwrMngmt    *cntrl
)
#else
PUBLIC S16 EuUiDamCntrlReq(pst,cntrl)
Pst         *pst;
LwrMngmt    *cntrl
#endif
{
   TRC3(EuUiDamCntrlReq)
   wrIfmDamWrCntrlReq(cntrl);

   RETVALUE(ROK);
}


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
#ifdef ANSI
PUBLIC S16 EuUiDamCfgReq 
(
Pst         *pst,
LwrMngmt    *cfg
)
#else
PUBLIC S16 EuUiDamCfgReq(pst, cfg)
Pst         *pst;
LwrMngmt    *cfg
#endif
{
   TRC3(EuUiDamCfgReq)
   wrIfmDamWrCfgReq(cfg);

   RETVALUE(ROK);
}


/** @brief This function starts the end marker timer for the corresponding UE.
 *
 * @details
 *
 *     Function: 
 *
 *         Processing steps:
 *         - handle the start timer indication
 *
 * @param[in]  ueCb  : DAM UE Control Block
 * @return S16
 *    -#Success : ROK
 */
#ifdef ANSI
PUBLIC S16 EuUiDamStopUeTmr 
(
Pst                          *pst,
U16                          cellId,
U16                          ueId
)
#else
PUBLIC S16 EuUiDamStopUeTmr(pst, cellId, ueId)
Pst                          *pst;
U16                          cellId;
U16                          ueId
#endif
{
   TRC3(EuUiDamStopUeTmr)

   RETVALUE(wrDamStopUeTmr(cellId, ueId));
}

/** @brief This function is responsible for starting the inactivity timer.
 *
 * @details This function starts the inactivity timer with the provided ueCb.
 *
 *     Function: EuUiDamStartInactivityTmr 
 *         Processing steps:
 *         - use the ueCb and call the wrStartTmr primitive to start the timer.
 *
 *
 * @param[in]  cellId  : Cell ID required to retrieve the UE. 
 * @param[in]  crnti  : UE identifier.
 * @return S16
 *    -#Success : ROK
 */
#ifdef ANSI
PUBLIC S16 EuUiDamStartInactivityTmr 
(
Pst                          *pst,
U16                          cellId,
U16                          crnti
)
#else
PUBLIC S16 EuUiDamStartInactivityTmr(pst, cellId, crnti)
Pst                          *pst;
U16                          cellId;
U16                          crnti 
#endif
{
   TRC3(EuUiDamStartInactivityTmr)

   RETVALUE(wrDamStartUeTmr(cellId, crnti));
}

/** @brief This function forwards the state change request for a particular 
 *         tunnel to DAM.
 *         
 * @details
 *
 *     Function: EuUiDamTnlStChngReq 
 *
 *         Processing steps:
 *         - Invokes the function  wrIfmDamWrChngTnlState to process the request
 *
 * @param[in] tnlStInfo: State information for the tunnel.
 * @return  Void 
 */
#ifdef ANSI
PUBLIC S16 EuUiDamTnlStChngReq 
(
Pst                          *pst,
WrDamTnlStInfo               *tnlStInfo
)
#else
PUBLIC S16 EuUiDamTnlStChngReq(pst, tnlStInfo)
Pst                          *pst;
WrDamTnlStInfo               *tnlStInfo
#endif
{
   TRC3(EuUiDamTnlStChngReq)
   
   wrIfmDamWrChngTnlState(tnlStInfo);
   RETVALUE(ROK);
}

/** @brief This function validates the UE-Reestablishment is possible or not in
 *         the Data Application Module.
 *
 * @details
 *
 *     Function: EuUiDamReestabReq
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
#ifdef ANSI
PUBLIC S16 EuUiDamReestabReq 
(
Pst                          *pst,
U32                          transId,
U16                          cellId,
U16                          oldcrnti,
U16                          newcrnti
)
#else
PUBLIC S16 EuUiDamReestabReq(pst, transId, cellId, oldcrnti, newcrnti)
Pst                          *pst;
U32                          transId;
U16                          cellId;
U16                          oldcrnti;
U16                          newcrnti
#endif
{
   TRC3(EuUiDamReestabReq)
   
   wrIfmDamWrReestabReq(transId, cellId, oldcrnti, newcrnti);
   RETVALUE(ROK);
}

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
#ifdef ANSI
PUBLIC S16 EuUiDamReCfgReq 
(
Pst                          *pst,
U32                          transId,
U16                          cellId,
U16                          crnti
)
#else
PUBLIC S16 EuUiDamReCfgReq(pst, transId, cellId, crnti)
Pst                          *pst;
U32                          transId;
U16                          cellId;
U16                          crnti
#endif
{
   TRC3(EuUiDamReCfgReq)
   
   RETVALUE(wrIfmDamWrReCfgReq(transId, cellId, crnti));
}

/** @brief This function informs the new cell information 
 *         to the Data Application Module during cell creation. 
 *         
 * @details
 *
 *     Function: EuUiDamCellAddReq 
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
#ifdef ANSI
PUBLIC S16 EuUiDamCellAddReq 
(
Pst                          *pst,
WrDamCellInfo                *cellInfo
)
#else
PUBLIC S16 EuUiDamCellAddReq(pst, cellInfo)
Pst                          *pst;
WrDamCellInfo                *cellInfo
#endif
{
   TRC3(EuUiDamCellAddReq)
   wrIfmDamWrCellAddReq(cellInfo);
   RETVALUE(ROK);
}

/** @brief This function is used to send the DAM Configuration to Delete the UE.
 *         
 * @details
 *
 *     Function: EuUiDamUeDelReq 
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
#ifdef ANSI
PUBLIC S16 EuUiDamUeDelReq 
(
Pst                          *pst,
U32                          transId,
U16                          cellId,
U16                          crnti
)
#else
PUBLIC S16 EuUiDamUeDelReq(pst, transId, cellId, crnti)
Pst                          *pst;
U32                          transId;
U16                          cellId;
U16                          crnti
#endif
{
   TRC3(EuUiDamUeDelReq)
   wrIfmDamWrUeDelReq(transId, cellId, crnti);
   RETVALUE(ROK);
}

/** @brief This function will be called to send delete tunnel to the DAM.
 *
 * @details
 *
 *     Function: EuUiDamTnlDelReq
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
#ifdef ANSI
PUBLIC S16 EuUiDamTnlDelReq 
(
Pst                          *pst,
U32                          transId,
WrDamTnlId                   *tnlId
)
#else
PUBLIC S16 EuUiDamTnlDelReq(pst, transId, tnlId)
Pst                          *pst;
U32                          transId;
WrDamTnlId                   *tnlId
#endif
{
   TRC3(EuUiDamTnlDelReq)
   wrIfmDamWrTnlDelReq(transId, tnlId);
   RETVALUE(ROK);
}

/** @brief This function is used to an EGTP create tuunel.
 *
 * @details
 *
 *     Function:EuUiDamTnlCreatReq 
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
#ifdef ANSI
PUBLIC S16 EuUiDamTnlCreatReq 
(
Pst                          *pst,
U32                          transId,
WrDamTnlInfo                 *tnlInfo
)
#else
PUBLIC S16 EuUiDamTnlCreatReq(pst, transId, tnlInfo)
Pst                          *pst;
U32                          transId;
WrDamTnlInfo                 *tnlInfo
#endif
{
   TRC3(EuUiDamTnlCreatReq)
   RETVALUE(wrIfmDamWrTnlCreatReq(transId, tnlInfo));
}

/** @brief This function informs the tunnel was ceated successfully with local
 *         teid or tunnel was not created to the UMM Module. 
 *
 * @details
 *
 *     Function:EuLiDamTnlCreatCfm 
 *
 *         Processing steps:
 *         - This function is process the tunnel creation conformation from DAM
 *           module.
 *         - This function invokes the UMM Module function wrIfmDamWrTnlCreatCfm to
 *           process the tunnel create conformation from DAM.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   status: status of tunnel creation.
 * @param[in]  lclTeid: Local Tunnel ID.
 * @return S16 
 *        -# Success : ROK
 */
#ifdef ANSI
PUBLIC S16 EuLiDamTnlCreatCfm 
(
Pst                          *pst,
U32                          transId,
U8                           status,
U32                          lclTeid
)
#else
PUBLIC S16 EuLiDamTnlCreatCfm(pst, transId, status, lclTeid)
Pst                          *pst;
U32                          transId;
U8                           status;
U32                          lclTeid
#endif
{
   TRC3(EuLiDamTnlCreatCfm)
   RETVALUE(wrIfmDamTnlCreatCfm(transId, status, lclTeid));
}

/** @brief This function is used to informs to the UMM Module the UE 
 * deletion was successful from Data  Application module.
 *
 * @details
 *
 *     Function: EuLiDamUeDelCfm 
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
#ifdef ANSI
PUBLIC S16 EuLiDamUeDelCfm 
(
Pst                          *pst,
U32                          transId,
U16                           cellId,
U16                          crnti
)
#else
PUBLIC S16 EuLiDamUeDelCfm(pst, transId, cellId, crnti)
Pst                          *pst;
U32                          transId;
U16                          cellId;
U16                          crnti
#endif
{
   TRC3(EuLiDamUeDelCfm)
   RETVALUE(wrIfmDamUeDelCfm(transId, cellId, crnti));
}

/** @brief This function gets the UE Re-establishment Conformation
 *         from Data Application Module. 
 *
 * @details
 *
 *     Function: EuLiDamReestabCfm 
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
#ifdef ANSI
PUBLIC S16 EuLiDamReestabCfm 
(
Pst                          *pst,
U32                          transId,
U8                           status
)
#else
PUBLIC S16 EuLiDamReestabCfm(pst, transId, status)
Pst                          *pst;
U32                          transId;
U8                          status
#endif
{
   TRC3(EuLiDamReestabCfm)
   RETVALUE(wrIfmDamReestabCfm(transId, status));
}


/** @brief This function informs the tunnel was updated successfully with local
 *         teid or tunnel was not created to the UMM Module. 
 *
 * @details
 *
 *     Function: EuLiDamTnlModCfm 
 *
 *         Processing steps:
 *         - This function is process the tunnel modification confirmation from DAM
 *           module.
 *         - This function invokes the UMM Module function wrUmmTnlCreatCfm to
 *           process the tunnel create confirmation from DAM.
 *
 * @param[in]  transId: Transaction ID. 
 * @param[in]   status: status of tunnel creation.
 * @param[in]  lclTeid: Local Tunnel ID.
 * @return S16 
 *        -# Success : ROK
 */
#ifdef ANSI
PUBLIC S16 EuLiDamTnlModCfm 
(
Pst                          *pst,
U32                          transId,
U8                           status,
U32                          lclTeId
)
#else
PUBLIC S16 EuLiDamTnlModCfm(pst, transId, status, lclTeId)
Pst                          *pst;
U32                          transId;
U8                           status;
U32                          lclTeId
#endif
{
   TRC3(EuLiDamTnlModCfm)
   wrIfmDamTnlModCfm(transId, status, lclTeId);
   RETVALUE(ROK);
}


/** @brief This function is used to handle the Datcfm came from PDCP.
 *
 * @details
 *
 *     Function: wrIfmDamPdcpDatCfm
 *
 *         Processing steps:
 *
 * @param[in]  pdcpId: pointer to CmLtePdcpId structure
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
#ifdef ANSI
PUBLIC S16 EuLiDamPdcpDatCfm 
(
Pst *pst,
CmLtePdcpId pdcpId
)
#else
PUBLIC S16 EuLiDamPdcpDatCfm(pst, pdcpId)
Pst *pst;
CmLtePdcpId pdcpId
#endif
{
   TRC3(EuLiDamPdcpDatCfm)

   RETVALUE(wrIfmDamPdcpDatCfm(pdcpId));
}

/** @brief This function is responsible for sending context release request 
 *
 * @details
 *
 *     Function: EuLiDamSendCtxtRel 
 *
 *         Processing steps:
 *         - Process message
 *
 * @param [in] crnti : CRNTI for the UE
 * @param [in] cellId: Cell Identity
 * @param [in] event : Event values could be due to Inactivity
 * @return S16
 *       -# ROK
 *       -# RFAILED
 */
#ifdef ANSI
PUBLIC S16 EuLiDamSendCtxtRel 
(
Pst                          *pst,
U16                          crnti,
U16                          cellId,
U8                           event
)
#else
PUBLIC S16 EuLiDamSendCtxtRel(pst, crnti, cellId, event)
Pst                          *pst;
U16                          crnti;
U16                          cellId;
U8                           event
#endif
{
   TRC3(EuLiDamSendCtxtRel)
   RETVALUE(wrUmmSndCtxtRelReq(crnti, cellId, event));
}

/** @brief This function Process EGTP-U error indication for a UE on 
 *             perticular tunnel.
 *
 * @details
 *
 *     Function: EuLiDamEgtpErrInd 
 *
 *         Processing steps:
 *
 * @param[in]  lclTeid    : local tunnel ID
 * @param[in]  numDrbs    : number of DRB's
 * @param[in]  ueId       : crnti
 * @return S16
 *    -#Success : ROK
 */
#ifdef ANSI
PUBLIC S16 EuLiDamEgtpErrInd 
(
Pst                          *pst,
U32                          lclTeid,
U32                          numDrbs,
U16                          crnti 
)
#else
PUBLIC S16 EuLiDamEgtpErrInd(pst, lclTeid, numDrbs, crnti)
Pst                          *pst;
U32                          lclTeid;
U32                          numDrbs;
U16                          crnti 
#endif
{
   TRC3(EuLiDamEgtpErrInd)
   RETVALUE(wrUmmPrcEgtpErrInd(lclTeid, numDrbs, crnti));
}
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
