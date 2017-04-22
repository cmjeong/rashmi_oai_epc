/********************************************************************20**

     Name:     SON Application

     Type:     

     Desc:     This file contains 
               

     File:     nl_ptmi.c

     Sid:      bk_ptmi.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 17:51:30 2014

     Prg:      subhamay 

*********************************************************************21*/

static const char *RLOG_MODULE_NAME="SON";
static int RLOG_FILE_ID=253;
static int RLOG_MODULE_ID=256;


/* Header include files (.h) */
#include "envopt.h"        /* Environment options */
#include "envdep.h"        /* Environment dependent */
#include "envind.h"        /* Environment independent */
#include "gen.h"           /* General */
#include "ssi.h"           /* System services */
#include "cm5.h"

#include "cm_tkns.h"       /* Common Token defines */
#include "cm_mblk.h"       /* Common Mem Allocation defines */
#include "cm_llist.h"      /* Common Link List defines */
#include "cm_hash.h"       /* Common Hashlist defines */
#include "cm_pasn.h"       /* Common Pasn defines */
#include "cm_lte.h"        /* Common Pasn defines */
#include "rl_common.h"
#include "rl_interface.h"
#include "lnl.h"           /* NL Interface defines */
#include "nlu.h"
#include "nl.h"            /* SON defines */

/* Header/extern include files (.x) */
#include "gen.x"           /* General */
#include "ssi.x"           /* System services */
#include "cm5.x"
#include "cm_tkns.x"       /* Common Token definitions */
#include "cm_mblk.x"       /* Common Memory Allocation */
#include "cm_llist.x"      /* Common Link List definitions */
#include "cm_hash.x"       /* Common Hashlist definitions */
#include "cm_lib.x"        /* Common Library definitions */
#include "cm_pasn.x"       /* Common Hashlist definitions */
#include "cm_lte.x"       /* Common Pasn defines */

#include "lnl.x"           /* NL Interface includes */
#include "nlu.x"
#include "nl.x"            /* SON includes */

/* local defines */

/* local typedefs */
 
/* local externs */
 
/* forward references */

/* private variable definitions */
PRIVATE LnlCfgCfm nlMiLnlCfgCfmMt[NL_MAX_SEL] =
{
#ifdef LCSMSONILNL
   cmPkLnlCfgCfm,
#else
   PtMiLnlCfgCfm,
#endif
   SmMiLnlCfgCfm,
#ifdef LWLCSMSONILNL
   cmPkLnlCfgCfm,
#else
   PtMiLnlCfgCfm,
#endif
};

PRIVATE LnlCntrlCfm nlMiLnlCntrlCfmMt[NL_MAX_SEL] =
{
#ifdef LCSMSONILNL
   cmPkLnlCntrlCfm,
#else
   PtMiLnlCntrlCfm,
#endif
   SmMiLnlCntrlCfm,
#ifdef LWLCSMSONILNL
   cmPkLnlCntrlCfm,
#else
   PtMiLnlCntrlCfm,
#endif
};

PRIVATE LnlCfgUpdateInd nlMiLnlCfgUpdateIndMt[NL_MAX_SEL] =
{
#ifdef LCSMSONILNL
   cmPkLnlCfgUpdateInd,
#else
   PtMiLnlCfgUpdateInd,
#endif
   SmMiLnlCfgUpdateInd,
#ifdef LWLCSMSONILNL
   cmPkLnlCfgUpdateInd,
#else
   PtMiLnlCfgUpdateInd,
#endif
};

PRIVATE LnlStatInd nlMiLnlAlarmIndMt[NL_MAX_SEL] =
{
#ifdef LCSMSONILNL
   cmPkLnlStatInd,
#else
   PtMiLnlStatInd,
#endif
   SmMiLnlStatInd,
#ifdef LWLCSMSONILNL
   cmPkLnlStatInd,
#else
   PtMiLnlStatInd,
#endif
};

PRIVATE LnlSonCfgInd nlMiLnlBrdcmSonCfgIndMt[NL_MAX_SEL] =
{
#ifdef LCSMSONILNL
   cmPkLnlSonCfgInd,
#else
   PtMiLnlSonCfgInd,
#endif
   SmMiLnlSonCfgInd,
#ifdef LWLCSMSONILNL
   cmPkLnlSonCfgInd,
#else
   PtMiLnlSonCfgInd,
#endif
};

/*
*     layer management interface functions
*
*     Fun:    NlMiLnlCfgCfm
*
*     Desc:   configuration confirm
*
*     Ret:    ROK     - succeeded
*             RFAILED - failed
*
*     Notes:  None
*
*     File:   nl_ptmi.c
*
*/
PUBLIC S16 NlMiLnlCfgCfm
(
Pst         *pst,
NlMngmt    *cfg
)
{
   S16 ret = ROK;

   TRC3(NlMiLnlCfgCfm)

   ret = (*nlMiLnlCfgCfmMt[pst->selector])(pst, cfg);

   RETVALUE(ret);
}

/*
*     layer management interface functions
*
*     Fun:    NlMiLnlCntrlCfm
*
*     Desc:   control confirm
*
*     Ret:    ROK     - succeeded
*             RFAILED - failed
*
*     Notes:  None
*
*     File:   nl_ptmi.c
*
*/
PUBLIC S16 NlMiLnlCntrlCfm
(
Pst         *pst,
NlMngmt     *cntrl
)
{
   S16 ret = ROK;

   TRC3(NlMiLnlCntrlCfm)

   ret = (*nlMiLnlCntrlCfmMt[pst->selector])(pst, cntrl);

   RETVALUE(ret);
}

/**
 * @brief API for EARFCN/PCI/PRACH configuration update sending from SON towards SM
 *
 * @details
 *
 *     Function: NlMiLnlCfgUpdateInd
 *
 *     This API is invoked by SON towards SM to send uadated PCI/EARFCN/PRACH configuration
 *
 *  @param[in]  Pst                     *pst
 *  @param[in]  NlConfigUpdateInd       *cfgUpdateInd
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 NlMiLnlCfgUpdateInd
(
Pst                      *pst,           /* post structure */
NlCfgUpdateInd           *cfgUpdateInd   /* update config structure */
)
#else
PUBLIC S16 NlMiLnlCfgUpdateInd(pst, cfgUpdateInd)
(
Pst                       *pst;           /* post structure */
NlCfgUpdateInd            *cfgUpdateInd    /* update config structure */
)
#endif
{
   S16 ret;
   TRC3(NlMiLnlCfgUpdateInd)

   ret = (*nlMiLnlCfgUpdateIndMt[pst->selector])
      (pst, cfgUpdateInd);

   RETVALUE(ret);
}

/**
 * @brief API for sending BRDCM-SON configuration parameter to SM
 *
 * @details
 *
 *     This API is invoked by SON towards SM to send BRDCM-SON 
 *     configuration parameters
 *
 *  @param[in]  pst          : post structure
 *  @param[in]  sonCfg       : BRDCM-SON configuration parameters
 *  @return  S16
 *      -#   Success         : ROK
 *      -#   Failure         : RFAILED 
 **/
#ifdef ANSI
PUBLIC S16 NlMiLnlBrdcmSonCfgInd
(
Pst         *pst,     /*!< post structure */
LnlSonCfg   *sonCfg   /*!< BRDCM-SON config structure */
)
#else
PUBLIC S16 NlMiLnlBrdcmSonCfgInd(pst, sonCfg)
(
Pst         *pst;      /*!< post structure */
LnlSonCfg   *sonCfg    /*!< BRDCM-SON config structure */
)
#endif
{
   S16 ret = ROK;
   ret = (*nlMiLnlBrdcmSonCfgIndMt[pst->selector])
      (pst, sonCfg);

   RETVALUE(ret);
}
/**
 * @brief API for sending updated EARFCN from SON towards SM
 *
 * @details
 *
 *     Function: nlSendEarfcnUpdateInd
 *
 *     This API is invoked by SON towards SM to send the updated EARFCN.
 *
 *  @param[in]  cellCb     : SON cell control block
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 nlSendEarfcnUpdateInd
(
NlCellCb                 *cellCb  /* cell control block */
)
#else
PUBLIC S16 nlSendEarfcnUpdateInd(cellCb)
(
NlCellCb                 *cellCb; /* cell control block */
)
#endif
{
   NlCfgUpdateInd        *cfgUpdateInd = NULLP;
   TRC3(nlSendEarfcnUpdateInd);
   NL_ALLOC(NL_REGION, NL_POOL, &cfgUpdateInd, sizeof(NlCfgUpdateInd));
   if(NULLP == cfgUpdateInd)
   {
      //RLOG0(L_ERROR, "Failed to allocate memory for update EARFCN config");
      RETVALUE(RFAILED);
   }
   cfgUpdateInd->cfgType = LNL_CFG_UPDATE_EARFCN;
   cfgUpdateInd->u.earfcnCfgInd.dlEarfcn = cellCb->cellInfo.dlEarfcn;
   cfgUpdateInd->u.earfcnCfgInd.ulEarfcn = cellCb->cellInfo.ulEarfcn;
   cfgUpdateInd->u.earfcnCfgInd.cellCfgIdx = cellCb->cellId;/*as filled in smBuildNlCellCfg*/
   cmMemcpy((U8 *) &(cfgUpdateInd->ecgi),(U8 *)&(cellCb->cellInfo.ecgi),
                   sizeof(LnlEcgi)); 
   /* Fill Pst */
   nlCb.init.lmPst.event = EVTLNLCFGUPDATEIND;
   /* Send the request to the Stack manager */
   NlMiLnlCfgUpdateInd(&nlCb.init.lmPst, cfgUpdateInd);
   RETVALUE(ROK);
}

/**
 * @brief API for sending update PCI from SON towards SM
 *
 * @details
 *
 *     Function: nlSendPciUpdateInd
 *
 *     This API is invoked by SON towards SM to send the updated PCI.
 *
 *  @param[in]  cellCb     : SON cell control block
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 nlSendPciUpdateInd
(
NlCellCb                 *cellCb  /* cell control block */
)
#else
PUBLIC S16 nlSendPciUpdateInd(cellCb)
(
NlCellCb                 *cellCb; /* cell control block */
)
#endif
{
   NlCfgUpdateInd    *cfgUpdate = NULLP;
   TRC3(nlSendPciUpdateInd);
   NL_ALLOC(NL_REGION, NL_POOL, &cfgUpdate, sizeof(NlCfgUpdateInd));
   if(NULLP == cfgUpdate)
   {
      //RLOG0(L_ERROR, "Failed to allocate memory for update PCI config");
      RETVALUE(RFAILED);
   }
   cfgUpdate->cfgType = LNL_CFG_UPDATE_PCI;
   cfgUpdate->u.pciCfgInd.cellId = cellCb->cellInfo.ecgi.cellId;
   cfgUpdate->u.pciCfgInd.pci = cellCb->cellInfo.pci;
   cfgUpdate->u.pciCfgInd.cellCfgIdx = cellCb->cellId;/*as filled in smBuildNlCellCfg*/
   cmMemcpy((U8 *) &(cfgUpdate->ecgi),(U8 *)&(cellCb->cellInfo.ecgi),
                   sizeof(LnlEcgi)); 
   /* Fill Pst */
   nlCb.init.lmPst.event = EVTLNLCFGUPDATEIND;
   /* Send the request to the Stack manager */
   NlMiLnlCfgUpdateInd(&nlCb.init.lmPst, cfgUpdate);
   RETVALUE(ROK);
}

/**
 * @brief API for sending update Tx Power from SON towards SM
 *
 * @details
 *
 *     Function: nlSendTxPwrUpdateInd
 *
 *     This API is invoked by SON towards SM to send the updated Tx Power.
 *
 *  @param[in]  cellCb     : SON cell control block
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 nlSendTxPwrUpdateInd
(
NlCellCb                 *cellCb  /* cell control block */
)
#else
PUBLIC S16 nlSendTxPwrUpdateInd(cellCb)
(
NlCellCb                 *cellCb; /* cell control block */
)
#endif
{
   NlCfgUpdateInd    *cfgUpdate = NULLP;

   RLOG0(L_INFO, "sending BRDCM selected Tx-power indication to SM");
   TRC3(nlSendTxPwrUpdateInd);
   NL_ALLOC(NL_REGION, NL_POOL, &cfgUpdate, sizeof(NlCfgUpdateInd));
   if(NULLP == cfgUpdate)
   {
      RLOG0(L_ERROR, "Failed to allocate memory for update Tw Power config");
      RETVALUE(RFAILED);
   }
   cfgUpdate->cfgType = LNL_CFG_UPDATE_TXPWR;
   cfgUpdate->u.txPwrCfgInd.refSignalTxPwr = cellCb->txPowerSel.refSignalTxPwr;
   cfgUpdate->u.txPwrCfgInd.pssPowerOffset = cellCb->txPowerSel.pssPowerOffset;
   cfgUpdate->u.txPwrCfgInd.sssPowerOffset = cellCb->txPowerSel.sssPowerOffset;
   cfgUpdate->u.txPwrCfgInd.pbchPowerOffset = cellCb->txPowerSel.pbchPowerOffset;
   cfgUpdate->u.txPwrCfgInd.pB = cellCb->txPowerSel.pB;
   cfgUpdate->u.txPwrCfgInd.pout = cellCb->txPowerSel.pout;
   cfgUpdate->u.txPwrCfgInd.cellCfgIdx = cellCb->cellId;
   /* Fill Pst */
   nlCb.init.lmPst.event = EVTLNLCFGUPDATEIND;
   /* Send the request to the Stack manager */
   NlMiLnlCfgUpdateInd(&nlCb.init.lmPst, cfgUpdate);
   RETVALUE(ROK);
}





/**
 * @brief API for sending alarm towards SM
 *
 * @details
 *
 *     Function: NlMiLnlAlarmInd
 *
 *     This API is invoked by SON towards SM to send alarm
 *
 *  @param[in]  pst         : post structure
 *  @param[in]  nlMngmt     : lnl interface management strcuture
 *  @return  S16
 *      -# ROK
 **/

#ifdef ANSI
PUBLIC S16 NlMiLnlAlarmInd
(
Pst                      *pst,        /* post structure */
NlMngmt                  *nlMngmt     /* interface structure */
)
#else
PUBLIC S16 NlMiLnlAlarmInd(pst, nlMngmt)
(
Pst                       *pst;        /* post structure */
NlMngmt                   *nlMngmt;      /* interface structure */
)
#endif
{
   S16 ret;
   TRC3(NlMiLnlAlarmInd)

   ret = (*nlMiLnlAlarmIndMt[pst->selector])
      (pst, nlMngmt);

   RETVALUE(ret);
}

/**
 * @brief API for sending alarm towards SM
 *
 * @details
 *
 *     Function: nlSendLnlAlarm
 *
 *     This API is invoked by SON towards SM to send alarm
 *
 *  @param[in]  alarm     : SON alarm structure
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 nlSendLnlAlarm
(
LnlUstaDgn                 *alarm  /* alarm structure */
)
#else
PUBLIC S16 nlSendLnlAlarm(alarm)
(
LnlUstaDgn                 *alarm; /* alarm structure */
)
#endif
{
   NlMngmt       *nlMngmt = NULLP;
   NlUsta        *usta = NULLP;
   LnlUstaDgn    *dgn  = NULLP;
   TRC3(nlSendLnlAlarm);
   
   NL_ALLOC(NL_REGION, NL_POOL, &nlMngmt, sizeof(NlMngmt));
   if(NULLP == nlMngmt)
   {
      //RLOG0(L_ERROR, "Failed to allocate memory for alarm");
      RETVALUE(RFAILED);
   }
   usta = &(nlMngmt->u.usta);
   usta->staType = LNL_STAT_ALARM;
   usta->u.stAlarm.alarm.category = LCM_CATEGORY_PROTOCOL;
   usta->u.stAlarm.alarm.event    = /*LWR_EVENT_SEND_ALARM*/0;
   usta->u.stAlarm.alarm.cause    = LCM_CAUSE_UNKNOWN;
   dgn = &(usta->u.stAlarm.dgn);
   cmMemcpy((U8 *)dgn,(U8 *)alarm, sizeof(LnlUstaDgn)); 
   /* Fill Pst */
   nlCb.init.lmPst.event = EVTLNLSTAIND;
   /* Send the request to the Stack manager */
   NlMiLnlAlarmInd(&nlCb.init.lmPst, nlMngmt);
   RETVALUE(ROK);
}



/**
 * @brief API for sending updated Prach Parameters from SON towards SM
 *
 * @details
 *
 *     Function: nlSendPrachParamUpdateInd
 *
 *     This API is invoked by SON towards SM to send the updated PRACH cfg.
 *
 *  @param[in]  cellCb     : SON cell control block
 *  @return  S16
 *      -# ROK
 **/
#ifdef ANSI
PUBLIC S16 nlSendPrachParamUpdateInd
(
NlCellCb                 *cellCb  /* cell control block */
)
#else
PUBLIC S16 nlSendPrachParamUpdateInd(cellCb)
(
NlCellCb                 *cellCb; /* cell control block */
)
#endif
{
   NlCfgUpdateInd    *cfgUpdate = NULLP;

   TRC3(nlSendPrachParamUpdateInd);

   NL_ALLOC(NL_REGION, NL_POOL, &cfgUpdate, sizeof(NlCfgUpdateInd));
   if(NULLP == cfgUpdate)
   {
      RLOG0(L_ERROR, "Failed to allocate memory for update PCI config");
      RETVALUE(RFAILED);
   }

   cfgUpdate->cfgType = LNL_CFG_UPDATE_PRACH;

   cfgUpdate->u.prachCfgInd.rootSequenceIndx =
      cellCb->prachCfg.servRootSeqIdx;
   cfgUpdate->u.prachCfgInd.prachCfgIdx =
      cellCb->prachCfg.servPrachCfgIdx;
   cfgUpdate->u.prachCfgInd.highSpeedFlag =
      cellCb->prachCfg.highSpeedFlag;
   cfgUpdate->u.prachCfgInd.zeroCorrelationZoneCfg =
      cellCb->prachCfg.servZeroCorrelationZoneCfg;
   cfgUpdate->u.prachCfgInd.prachFreqOffset =
      cellCb->prachCfg.servPrachFreqOffset;
   cfgUpdate->u.prachCfgInd.cellCfgIdx = cellCb->cellId;
   
   /* Fill Pst */
   nlCb.init.lmPst.event = EVTLNLCFGUPDATEIND;
   /* Send the request to the Stack manager */
   NlMiLnlCfgUpdateInd(&nlCb.init.lmPst, cfgUpdate);
   RETVALUE(ROK);
}

/**
 * @brief API for sending BRDCM-SON REM Scan Request
 *
 * @details
 *
 *     This API is invoked by SON towards SM to send the BRDCM-SON
 *     REM Scan Request
 *
 *  @param[in]  measInterval :measurement interval value received from BRDCM-SON
 *  @param[in]  cellCb       :cell control block
 *  @return  S16
 *      -# SUCCESS         :ROK
 *      -# FAILURE         :RFAILED
 **/
#ifdef ANSI
PUBLIC S16 nlSendSonREMScanReq
(
U16        remScanInterval, /*!< REM Scan interval*/
U16        remScanCount,    /*!< REM Scan count*/
NlCellCb   *cellCb          /*!< cell control block*/
)
#else
PUBLIC S16 nlSendSonREMScanReq(remScanInterval, remScanCount, cellCb)
(
U16        remScanInterval; /*!< REM Scan interval*/
U16        remScanCount;    /*!< REM Scan count*/
NlCellCb   *cellCb;          /*!< cell control block*/
)
#endif
{
   LnlSonCfg             *sonCfg = NULLP;
   S16                   ret = ROK;

   NL_ALLOC(NL_REGION, NL_POOL, &sonCfg, sizeof(LnlSonCfg));
   if(NULLP == sonCfg)
   {
      /*RLOG0(L_ERROR, "Failed to allocate memory for BRDCM-SON CFG");*/
      RETVALUE(RFAILED);
   }
   cmMemcpy((U8 *) &(sonCfg->ecgi),(U8 *)&(cellCb->cellInfo.ecgi),
                   sizeof(LnlEcgi));
   sonCfg->cfgType = LNL_SON_PERD_REM_SCAN_CFG;
   sonCfg->u.remScanCfg.perdREMScanInterval = remScanInterval; 
   sonCfg->u.remScanCfg.perdREMScanCount = remScanCount;
   
   /* Fill Pst */
   nlCb.init.lmPst.event = EVTLNLSONCFGIND;
   /* Send the request to the Stack manager */
   ret = NlMiLnlBrdcmSonCfgInd(&nlCb.init.lmPst, sonCfg);
   RETVALUE(ret);
}


/**
 * @brief API for sending BRDCM-SON configured scheduler config parameters
 *
 * @details
 *
 *     This API is invoked by SON towards SM to send the BRDCM-SON
 *     configured scheduler config parameters.
 *
 *  @param[in]      schdCfg  : scheduler configuration received from BRDCM-SON 
 *  @param[in]      cellCb   : Cell control block 
 *  @return  S16
 *      -# SUCCESS           : ROK
 *      -# FAILURE           : RFAILED
 **/
#ifdef ANSI
PUBLIC S16 nlSendSonSchdCfgInd
(
LnlSonSchdCfg    *schdCfg,
NlCellCb         *cellCb
)
#else
PUBLIC S16 nlSendSonSchdCfgInd(schdCfg, cellCb)
(
LnlSonSchdCfg    *schdCfg;
NlCellCb         *cellCb;
)
#endif
{
   LnlSonCfg             *sonCfg = NULLP;
   NL_ALLOC(NL_REGION, NL_POOL, &sonCfg, sizeof(LnlSonCfg));
   if(NULLP == sonCfg)
   {
      RLOG0(L_ERROR, "Failed to allocate memory for BRDCM-SON SCHD CFG");
      RETVALUE(RFAILED);
   }
   cmMemcpy((U8 *) &(sonCfg->ecgi),(U8 *)&(cellCb->cellInfo.ecgi),
                   sizeof(LnlEcgi));
   sonCfg->cfgType = LNL_SON_SCHD_CFG;
   cmMemcpy((U8 *)&sonCfg->u.schdCfg, (U8 *)schdCfg, sizeof(LnlSonSchdCfg));
   /* Fill Pst */
   nlCb.init.lmPst.event = EVTLNLSONCFGIND;
   /* Send the request to the Stack manager */
   NlMiLnlBrdcmSonCfgInd(&nlCb.init.lmPst, sonCfg);
   RETVALUE(ROK);
}

/**
 * @brief API for sending BRDCM-SON configured UE measurement 
 * reporting interval value
 *
 * @details
 *
 *     This API is invoked by SON towards SM to send the BRDCM-SON
 *     configured UE measurement reporting interval value.
 *
 *  @param[in]  measInterval :measurement interval value received from BRDCM-SON
 *  @param[in]  cellCb       :cell control block
 *  @return  S16
 *      -# SUCCESS         :ROK
 *      -# FAILURE         :RFAILED
 **/
#ifdef ANSI
PUBLIC S16 nlSendSonMeasRptIntervalInd
(
U32        ueMeasInterval,  /*!< UE measurement reporting interval*/
NlCellCb   *cellCb          /*!< cell control block*/
)
#else
PUBLIC S16 nlSendSonMeasRptIntervalInd(ueMeasInterval, cellCb)
(
U32   ueMeasInterval; /*!< UE measurement reporting interval*/
NlCellCb   *cellCb;   /*!< cell control block*/
)
#endif
{
   LnlSonCfg             *sonCfg = NULLP;
   NL_ALLOC(NL_REGION, NL_POOL, &sonCfg, sizeof(LnlSonCfg));
   if(NULLP == sonCfg)
   {
      //RLOG0(L_ERROR, "Failed to allocate memory for BRDCM-SON CFG");
      RETVALUE(RFAILED);
   }
   cmMemcpy((U8 *) &(sonCfg->ecgi),(U8 *)&(cellCb->cellInfo.ecgi),
                   sizeof(LnlEcgi));
   sonCfg->cfgType = LNL_SON_PERD_UE_MEAS_INTERVAL_CFG;
   sonCfg->u.measCfg.periodicUeMeasInterval = ueMeasInterval;     
   /* Fill Pst */
   nlCb.init.lmPst.event = EVTLNLSONCFGIND;
   /* Send the request to the Stack manager */
   NlMiLnlBrdcmSonCfgInd(&nlCb.init.lmPst, sonCfg);
   RETVALUE(ROK);
}


/********************************************************************30**

           End of file:     bk_ptmi.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/1 - Mon Dec 29 17:51:30 2014

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
*********************************************************************91*/

