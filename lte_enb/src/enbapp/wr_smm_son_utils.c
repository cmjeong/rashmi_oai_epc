/********************************************************************20**

     Name:     Eson Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_smm_son_utils.c

     Sid:      fc_smm_son_utils.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/9 - Tue Jan 13 12:01:15 2015

     Prg:      subhamay 

*********************************************************************21*/


/* header include files */ 
#include "wr.h"
#include "wr_cmn.h"
#include "wr_smm_init.h"
#include "wr_smm_smallcell.h"
#include "wr_utils.h"
#include "wr_lwr.h"
#include "lnl.h"
#include "nlu.h"
#include "lys.x"
#include "wr_msm_common.h"
#include "lnl.x"
#include "nlu.x"
#ifdef __cplusplus
extern "C" {
#endif /* cplusplus */

static const char* RLOG_MODULE_NAME="SMM";
static int RLOG_MODULE_ID=2;
static int RLOG_FILE_ID=312;

EXTERN MsmLteeNodeBparams lteeNodeBparams[WR_MAX_CELLS];
#ifdef WR_RSYS_OAM
EXTERN Void smUpdateSONParams(U32 msgType, void* params);
#endif /* WR_RSYS_OAM*/

PRIVATE S16 smBuildNlCellPciCfg   ARGS((
LnlCellCfg   *cellCfg,
U8            cellCfgIdx
));

PRIVATE  S16 smBuildNlCellPucchCfg ARGS((
LnlPucchCfg   *pucchCfg,
U8            cellCfgIdx
));


PRIVATE S16 smBuildNlCellPrachCfg   ARGS((
LnlPrachCfg   *prachCfg,
U8            cellCfgIdx
));

PRIVATE S16 smBuildNlCellEarfcnCfg  ARGS((
LnlCellCfg   *cellCfg,
U8            cellCfgIdx
));

PRIVATE S16 smBuildNlCellCsgCfg  ARGS((
LnlCellCfg   *cellCfg
));

/*
 *
 *       Fun:    smBuildNlCellPciCfg
 *
 *       Desc:   Build Cell configuration of a cell
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */

#ifdef ANSI
PUBLIC S16 smBuildNlCellPciCfg
(
LnlCellCfg   *cellCfg,
U8            cellCfgIdx
)
#else
PUBLIC S16 smBuildNlCellPciCfg(cellCfg, cellCfgIdx)
LnlCellCfg   *cellCfg;
U8            cellCfgIdx;
#endif /* ANSI */
{
   U32   pciCount;

   TRC3(smBuildNlCellPciCfg);
   cellCfg->pci = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.physCellId;
   cellCfg->numPci = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.pciListCfg.numPci;
   RLOG3(L_DEBUG, "smBuildNlCellPciCfg:cellCfgIdx=%d:pci=%d:numPci=%ld\n",cellCfgIdx,cellCfg->pci,cellCfg->numPci);
   for(pciCount = 0; pciCount < cellCfg->numPci; pciCount ++)
   {
      cellCfg->pciList[pciCount] = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.pciListCfg.pciLst[pciCount];
      RLOG1(L_DEBUG, "cellCfg->pciList[pciCount]=%d\n",cellCfg->pciList[pciCount]);
   }
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smBuildNlCellPucchCfg
 *
 *       Desc:   Build Cell PUCCH Config params of a cell
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */

#ifdef ANSI
PRIVATE S16 smBuildNlCellPucchCfg
(
LnlPucchCfg   *pucchCfg,
U8 cellCfgIdx
)
#else
PRIVATE S16 smBuildNlCellPucchCfg(pucchCfg,cellCfgIdx)
LnlPucchCfg *pucchCfg;
U8 cellCfgIdx;
#endif /* ANSI */
{
   TRC3(smBuildNlCellPucchCfg);

   pucchCfg->pucchCqiResIdx = lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nRBCqi;
   pucchCfg->n1PucchAn = lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.n1PucchAn;
   pucchCfg->deltaShift = lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.deltaShift + 1;
   pucchCfg->cyclicShift = lteeNodeBparams[cellCfgIdx].ltePucchCfgCommon.nCSAN;

   RETVALUE(ROK);
}


/*
 *
 *       Fun:    smBuildNlCellPrachCfg
 *
 *       Desc:   Build Cell Prach Config params of a cell
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */

#ifdef ANSI
PRIVATE S16 smBuildNlCellPrachCfg
(
LnlPrachCfg   *prachCfg,
U8            cellCfgIdx
)
#else
PRIVATE S16 smBuildNlCellPrachCfg(prachCfg,cellCfgIdx)
LnlPrachCfg   *prachCfg;
U8            cellCfgIdx;
#endif /* ANSI */
{
   TRC3(smBuildNlCellPrachCfg);

   prachCfg->servRootSeqIdx =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.rootSequenceIndx;
   prachCfg->servPrachCfgIdx = 1;

   prachCfg->servZeroCorrelationZoneCfg =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachCfgInfo.zeroCorrelationZoneCfg;
   prachCfg->servPrachFreqOffset =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachCfgInfo.prachFreqOffset;
   prachCfg->highSpeedFlag = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachCfgInfo.highSpeedFlag;

   RLOG1(L_DEBUG, "smBuildNlCellPrachCfg:highSpeedFlag=%d\n",
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo.highSpeedFlag
         );

   prachCfg->numRootSeqIndex =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachParamLst.numRootSeqIndex;
   if(prachCfg->numRootSeqIndex)
   {
      U8 rootSeqIdxCnt;
      for(rootSeqIdxCnt = 0; 
          rootSeqIdxCnt < prachCfg->numRootSeqIndex;
          rootSeqIdxCnt++)
      {
         prachCfg->rootSeqIdx[rootSeqIdxCnt] =
            lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.rootSequenceIndxLst[rootSeqIdxCnt];
         
         RLOG2(L_DEBUG, "smBuildNlCellPrachCfg:numRootSeqIndex=%d,rootSequenceIndxLst=%d\n",
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachParamLst.numRootSeqIndex,
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.rootSequenceIndxLst[rootSeqIdxCnt]
         );
      }
   }

   prachCfg->numPrachCfgIdx =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachParamLst.numPrachCfgIdx;
   if(prachCfg->numPrachCfgIdx)
   {
      U8 prachCfgIdxCnt;
      for(prachCfgIdxCnt = 0;
          prachCfgIdxCnt < prachCfg->numPrachCfgIdx;
          prachCfgIdxCnt ++)
      {
         prachCfg->prachConfigIdx[prachCfgIdxCnt] =
            lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.prachCfgIdxLst[prachCfgIdxCnt];
         RLOG2(L_DEBUG, "smBuildNlCellPrachCfg:numPrachCfgIdx=%d,prachCfgIdxLst=%d\n",
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachParamLst.numPrachCfgIdx,
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.prachCfgIdxLst[prachCfgIdxCnt]
         );
      }
   }

   prachCfg->numZeroCorrCfgZone =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachParamLst.numZeroCorrZoneCfg;
   if(prachCfg->numZeroCorrCfgZone)
   {
      U8 zeroCorrCfgZoneCnt;
      for(zeroCorrCfgZoneCnt = 0;
          zeroCorrCfgZoneCnt < prachCfg->numZeroCorrCfgZone;
          zeroCorrCfgZoneCnt ++)
      {
         prachCfg->zeroCorrelationZoneCfg[zeroCorrCfgZoneCnt] =
            lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.zeroCorrelationZoneCfgLst[zeroCorrCfgZoneCnt];
         RLOG2(L_DEBUG, "smBuildNlCellPrachCfg::numZeroCorrZoneCfg=%d,zeroCorrelationZoneCfgLst=%d\n",
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachParamLst.numZeroCorrZoneCfg,
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo.zeroCorrelationZoneCfg
         );
      }
   }

   prachCfg->numFreqOffset =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachParamLst.numPrachFreqOffset;
   if(prachCfg->numFreqOffset)
   {
      U8 freqOffsetCnt;
      for(freqOffsetCnt = 0;
          freqOffsetCnt < prachCfg->numFreqOffset;
          freqOffsetCnt ++)
      {
         prachCfg->freqOffset[freqOffsetCnt] =
            lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.prachFreqOffsetLst[freqOffsetCnt];
         RLOG2(L_DEBUG, "smBuildNlCellPrachCfg::numPrachFreqOffset=%d,prachFreqOffset=%d\n",
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePrachCfgCommon.prachParamLst.numPrachFreqOffset,
               lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.prachFreqOffsetLst[freqOffsetCnt]);
      }
   }


   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smBuildNlCellReCfg
 *
 *       Desc:   fill all the cell reconfiguration parameter received from OAM
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildNlCellReCfg
(
LnlCellReCfg   *cellReCfg
)
#else
PUBLIC S16 smBuildNlCellReCfg(cellReCfg)
LnlCellReCfg   *cellReCfg;
#endif /* ANSI */
{
   U32                   idx;
   MsmLteCellSib1CfgGrp *sib1cfg = NULLP;
   MsmLtePlmnId         *priPlmn = NULLP;
   TRC3(smBuildNlCellReCfg);
   cellReCfg->cellId = 1;
   sib1cfg  = &(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteCellSib1CfgGrp);
   cellReCfg->ecgi.cellId = sib1cfg->cellAccessInfo.cellId;

   for(idx = 0; idx < sib1cfg->cellAccessInfo.numOfPlmns; idx++)
   {
      if(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[idx].isPrimary == TRUE)
      {
         priPlmn = &sib1cfg->cellAccessInfo.plmnInfo[idx].plmnId;
         cellReCfg->ecgi.plmn.numMncDigits  = priPlmn->numMncDigits;
         cellReCfg->ecgi.plmn.mcc[0] = priPlmn->mcc[0];
         cellReCfg->ecgi.plmn.mcc[1] = priPlmn->mcc[1];
         cellReCfg->ecgi.plmn.mcc[2] = priPlmn->mcc[2];

         cellReCfg->ecgi.plmn.mnc[0]= priPlmn->mnc[0];
         cellReCfg->ecgi.plmn.mnc[1]= priPlmn->mnc[1];
         cellReCfg->ecgi.plmn.mnc[2]= priPlmn->mnc[2];
         break;
      }
   }
   cellReCfg->numPci = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteAddCellCfg.pciListCfg.numPci;
   for(idx = 0; idx < cellReCfg->numPci; idx++)
   {
      cellReCfg->pciList[idx] = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteAddCellCfg.pciListCfg.pciLst[idx]; 
   }
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smBuildNlCellRsysTpmCfg
 *
 *       Desc:   Fill the Rsys TPM configuration from OAM
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PRIVATE S16 smBuildNlCellRsysTpmCfg
(
LnlCellCfg   *cellCfg
)
#else
PRIVATE S16 smBuildNlCellRsysTpmCfg(cellCfg)
LnlCellCfg   *cellCfg;
#endif /* ANSI */
{
   TRC3(smBuildNlCellRsysTpmCfg);

   cellCfg->tpmCfg.tgtRsrp = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].tpmCfg.tgtRsrp;
   cellCfg->tpmCfg.attnConstIdx = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].tpmCfg.attnConstIdx;
   cellCfg->tpmCfg.minRsrp = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].tpmCfg.minRsrp;
   cellCfg->tpmCfg.maxRsrp = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].tpmCfg.maxRsrp;
   
   RETVALUE(ROK);
}


/*
 *
 *       Fun:    smBuildNlCellTxPwrCfg
 *
 *       Desc:   Fill the Tx Power configuration parameter received from OAM
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PRIVATE S16 smBuildNlCellTxPwrCfg
(
LnlCellCfg   *cellCfg
)
#else
PRIVATE S16 smBuildNlCellTxPwrCfg(cellCfg)
LnlCellCfg   *cellCfg;
#endif /* ANSI */
{
   U32 refSigIdx, pbIdx, paIdx;
   U32 pschIdx, sschIdx, pbchIdx;

   TRC3(smBuildNlCellTxPwrCfg);

   cellCfg->txPwrCfg.refSignalPwrCnt =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.refSignalPwrCnt;
   for(refSigIdx=0; refSigIdx< cellCfg->txPwrCfg.refSignalPwrCnt; refSigIdx++)
   {
      cellCfg->txPwrCfg.referenceSignalPwr[refSigIdx] =
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.referenceSignalPwr[refSigIdx];
   }

   cellCfg->txPwrCfg.pBCnt = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.pBCnt;
   for(pbIdx=0; pbIdx< cellCfg->txPwrCfg.pBCnt; pbIdx++)
   {
      cellCfg->txPwrCfg.pB[pbIdx] =
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.pB[pbIdx];
   }

   cellCfg->txPwrCfg.pACnt = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgDedicated.pACnt;
   for(paIdx=0; paIdx< cellCfg->txPwrCfg.pACnt; paIdx++)
   {
      cellCfg->txPwrCfg.pA[paIdx] = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgDedicated.pA[paIdx];
   }

   cellCfg->txPwrCfg.pschPowerOffCnt = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pschPowerOffCnt;
   for(pschIdx=0;pschIdx<cellCfg->txPwrCfg.pschPowerOffCnt;pschIdx++)
   {
      cellCfg->txPwrCfg.pschPowerOffset[pschIdx] = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pschPowerOffset[pschIdx];
   }

   cellCfg->txPwrCfg.sschPowerOffCnt = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.sschPowerOffCnt;
   for(sschIdx=0;sschIdx<cellCfg->txPwrCfg.sschPowerOffCnt;sschIdx++)
   {
      cellCfg->txPwrCfg.sschPowerOffset[sschIdx] = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.sschPowerOffset[sschIdx];
   }

   cellCfg->txPwrCfg.pbchPowerOffCnt = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pbchPowerOffCnt;
   for(pbchIdx=0;pbchIdx<cellCfg->txPwrCfg.pbchPowerOffCnt;pbchIdx++)
   {
      cellCfg->txPwrCfg.pbchPowerOffset[pbchIdx] = 
         lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pbchPowerOffset[pbchIdx];
   }

   RETVALUE(ROK);
}
/*
 *
 *       Fun:    smBuildNlCellCsgCfg
 *
 *       Desc:   fill all the cell Csg configuration parameter received from OAM
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PRIVATE S16 smBuildNlCellCsgCfg
(
LnlCellCfg   *cellCfg
)
#else
PRIVATE S16 smBuildNlCellCsgCfg(cellCfg)
LnlCellCfg   *cellCfg;
#endif /* ANSI */
{
   U16        csgPciRange = 0;
   TRC3(smBuildNlCellCsgCfg);
   cellCfg->csgPciCfg.isCsgPciCfg = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSib4CsgInfo.isCsgPciCfgd;
   cellCfg->csgPciCfg.csgStartPci = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSib4CsgInfo.csgStartPhyCellId;
   WR_EMM_GET_PCI_RANGE(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSib4CsgInfo.csgPciRange,
            csgPciRange);
   cellCfg->csgPciCfg.csgPciRange = csgPciRange;

   cellCfg->smallCellPciCfg.isSmallCellPciCfg = 
          lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteAddCellCfg.isSmallCellPciCfgd;
   cellCfg->smallCellPciCfg.smallCellStartPci = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteAddCellCfg.startPci;
   if(TRUE == cellCfg->smallCellPciCfg.isSmallCellPciCfg)
   {
      cellCfg->smallCellPciCfg.maxSmallCellPci = 
       cellCfg->smallCellPciCfg.smallCellStartPci + lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteAddCellCfg.pciRange;   
   }
   switch(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteFapAccessParams.accessMode)
   {
      case WR_ENB_OPEN_ACCESS :
      {
         cellCfg->csgPciCfg.accessMode = LNL_ENB_OPEN_ACCESS;
      }
      break;
      case WR_ENB_CLOSED_ACCESS :
      {
         cellCfg->csgPciCfg.accessMode = LNL_ENB_CLOSED_ACCESS;
      }
      break;
      case WR_ENB_HYBRID_ACCESS :
      {
         cellCfg->csgPciCfg.accessMode = LNL_ENB_HYBRID_ACCESS;
      }
      default :
      {
         break;
      }
   }         
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smBuildNlCellEarfcnCfg
 *
 *       Desc:   fill all the cell configuration parameter received from OAM
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PRIVATE S16 smBuildNlCellEarfcnCfg
(
LnlCellCfg   *cellCfg,
U8            cellCfgIdx
)
#else
PRIVATE S16 smBuildNlCellEarfcnCfg(cellCfg,cellCfgIdx)
LnlCellCfg   *cellCfg;
U8            cellCfgIdx;
#endif /* ANSI */
{
   U32                  earfcnCount;

   TRC3(smBuildNlCellEarfcnCfg);

   cellCfg->numDlEarfcn = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfcnListCfg.numEarfcnDl;
   cellCfg->numUlEarfcn = lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfcnListCfg.numEarfcnUl;
   RLOG3(L_DEBUG, "smBuildNlCellEarfcnCfg:cellCfgIdx=%d:numDlEarfcn=%d:numUlEarfcn=%d",
         cellCfgIdx,
         cellCfg->numDlEarfcn,
         cellCfg->numUlEarfcn);
   for(earfcnCount = 0; earfcnCount < cellCfg->numDlEarfcn; earfcnCount ++)
   {
      cellCfg->dlEarfcnList[earfcnCount] =
          lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfcnListCfg.earfcnDlLst[earfcnCount];
      RLOG1(L_DEBUG, "smBuildNlCellEarfcnCfg:cellCfg->dlEarfcnList[earfcnCount]=%d",
            cellCfg->dlEarfcnList[earfcnCount]);
   }
   for(earfcnCount = 0; earfcnCount < cellCfg->numUlEarfcn; earfcnCount ++)
   {
      cellCfg->ulEarfcnList[earfcnCount] =
          lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfcnListCfg.earfcnUlLst[earfcnCount];
      RLOG1(L_DEBUG, "smBuildNlCellEarfcnCfg:cellCfg->ulEarfcnList[earfcnCount]=%d",
            cellCfg->ulEarfcnList[earfcnCount]);
   }
   cellCfg->numRemScanEarfcn = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteEarfcnRssiCfg.numEarfcn;
   for(earfcnCount = 0; earfcnCount < cellCfg->numRemScanEarfcn; earfcnCount ++)
   {
      cellCfg->remScanEarfcn[earfcnCount].dlEarfcn =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteEarfcnRssiCfg.remScanEarfcn[earfcnCount].earfcnDl;
      cellCfg->remScanEarfcn[earfcnCount].rssi =
      lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteEarfcnRssiCfg.remScanEarfcn[earfcnCount].rssi;
   }
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smBuildNlGenCfg
 *
 *       Desc:   fill all the general configuration parameter received from OAM
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 smBuildNlGenCfg
(
NlGenCfg   *genCfg
)
#else
PUBLIC S16 smBuildNlGenCfg(genCfg)
NlGenCfg   *genCfg;
#endif /* ANSI */
{
   TRC3(smBuildNlGenCfg);
   genCfg->tmrRes = 10;
   genCfg->pciSelType = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSonGenericParams.isPciSelEnabled;
   genCfg->prachSelType = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSonGenericParams.isPrachSelEnabled;
   genCfg->earfcnSelType = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSonGenericParams.isEarfcnSelEnabled;
   genCfg->txPowerSelType = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSonGenericParams.isTxPowerSelEnabled;
   genCfg->maxUeSupp = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteSmCellCfg.maxUeSupp;
   genCfg->maxUePerTti = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteCellDlSchdCfgGrp.maxUePerDlSf;

   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smUpdateNlPciVal
 *
 *       Desc:   update the PCI value modified by SON
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 smUpdateNlPciVal
(
NlUpdatePciCfgInd       *pciCfgInd
)
#else
PUBLIC S16 smUpdateNlPciVal(pciCfgInd)
NlUpdatePciCfgInd       *pciCfgInd;
#endif /* ANSI */
{
   TRC3(smUpdateNlPciVal);
   U32 cellCfgIdx = ((pciCfgInd->cellCfgIdx)-1);
   
   lteeNodeBparams[cellCfgIdx].lteAddCellCfg.physCellId = pciCfgInd->pci;
   RLOG2(L_DEBUG, "\nsmUpdateNlPciVal:PCI(%d) for Cell(%lu)\n",pciCfgInd->pci,pciCfgInd->cellCfgIdx);

#ifdef WR_RSYS_OAM
   smUpdateSONParams(MSM_LTE_UPDATE_SON_SELECTED_PCI,
         (void *)&(lteeNodeBparams[cellCfgIdx].lteAddCellCfg.physCellId));
#endif
   RETVALUE(ROK);
}


/*
 *
 *       Fun:    smUpdateNlEarfcnVal
 *
 *       Desc:   update the EARFCN val selected by SON 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 smUpdateNlEarfcnVal
(
NlUpdateEarfcnCfgInd   *earfcnCfgInd
)
#else
PUBLIC S16 smUpdateNlEarfcnVal(earfcnCfgInd)
NlUpdateEarfcnCfgInd   *earfcnCfgInd;
#endif /* ANSI */
{
#ifdef WR_RSYS_OAM
   U8   count;
   U32   cellCfgIdx = ((earfcnCfgInd->cellCfgIdx)-1);

   TRC3(smUpdateNlEarfcnVal);
   /* TODO: MultiCell Impl. Currently SON EARFCN updation is done for only the 1st cell
    * To take care of this in the future. As this requires SON interface changes*/

   for(count = 0; count < lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteNeighFreqCfg.numEutraFreq; count ++)
   {
      if((lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[count].eutranFreq.earfcnDl == \
               lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfdnDl) && \
            (lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[count].eutranFreq.earfcnUl == \
             lteeNodeBparams[cellCfgIdx].lteULFrequencyInfo.eARFCN))
      {
         lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[count].eutranFreq. \
            earfcnDl = earfcnCfgInd->dlEarfcn;
         lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[count].eutranFreq. \
            earfcnUl = earfcnCfgInd->ulEarfcn;
         break;
      }
   }
   lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfdnDl = earfcnCfgInd->dlEarfcn;
   lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfdnUl = earfcnCfgInd->ulEarfcn;
   lteeNodeBparams[cellCfgIdx].lteULFrequencyInfo.eARFCN = earfcnCfgInd->ulEarfcn; 
   
   lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[0].eutranFreq.earfcnDl = earfcnCfgInd->dlEarfcn;
   lteeNodeBparams[cellCfgIdx].lteNeighFreqCfg.t.addNeighFreq[0].eutranFreq.earfcnUl = earfcnCfgInd->ulEarfcn;
   
   RLOG3(L_DEBUG, "smUpdateNlEarfcnVal:cellCfgIdx =%ld: dlEarfcn = %d:ulEarfcn = %d***\n",
         earfcnCfgInd->cellCfgIdx,
         earfcnCfgInd->dlEarfcn,
         earfcnCfgInd->ulEarfcn);
   RLOG3(L_DEBUG, "smUpdateNlEarfcnVal:cellCfgIdx = %ld:dlEarfcn = %ld:ulEarfcn = %ld***\n",
         earfcnCfgInd->cellCfgIdx,
         lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfdnDl,
         lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfdnUl);

   smUpdateSONParams(MSM_LTE_UPDATE_SON_SELECTED_EARFCNUL,
                             (void *)&(lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfdnUl));
   
   smUpdateSONParams(MSM_LTE_UPDATE_SON_SELECTED_EARFCNUL,
                             (void *)&(lteeNodeBparams[cellCfgIdx].lteULFrequencyInfo.eARFCN));

   smUpdateSONParams(MSM_LTE_UPDATE_SON_SELECTED_EARFCNDL,
                                  (void *)&(lteeNodeBparams[cellCfgIdx].lteAddCellCfg.earfdnDl));
#endif
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smUpdateNlPrachVal
 *
 *       Desc:   update the PRACH val selected by SON 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 smUpdateNlPrachVal
(
NlUpdatePrachCfgInd   *prachCfgInd
)
#else
PUBLIC S16 smUpdateNlPrachVal(prachCfgInd)
NlUpdatePrachCfgInd   *prachCfgInd;
#endif /* ANSI */
{
   TRC3(smUpdateNlPrachVal);
   U32 cellCfgIdx = ((prachCfgInd->cellCfgIdx)-1);
   
   lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.rootSequenceIndx =
      prachCfgInd->rootSequenceIndx;
   lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.prachCfgIdxLst[WR_SM_DFLT_CELL_INDX] = 
      prachCfgInd->prachCfgIdx;/*check this*/
   lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo.highSpeedFlag =
      prachCfgInd->highSpeedFlag;
   lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo.zeroCorrelationZoneCfg =
      prachCfgInd->zeroCorrelationZoneCfg;
   lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo.prachFreqOffset =
      prachCfgInd->prachFreqOffset;

   RLOG3(L_DEBUG, "smUpdateNlPrachVal:cellCfgIdx:rootSequenceIndx=%d:prachCfgIdx=%d\n",
         cellCfgIdx,
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.rootSequenceIndx,
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachParamLst.prachCfgIdxLst[WR_SM_DFLT_CELL_INDX]);

   RLOG3(L_DEBUG, "smUpdateNlPrachVal:highSpeedFlag=%d:zeroCorrelationZoneCfg=%d,prachFreqOffset=%d\n",
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo.highSpeedFlag,
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo.zeroCorrelationZoneCfg,
         lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon.prachCfgInfo.prachFreqOffset);
#ifdef WR_RSYS_OAM
   smUpdateSONParams(MSM_LTE_UPDATE_PRACH_CONFIG, 
                    (void *)&(lteeNodeBparams[cellCfgIdx].ltePrachCfgCommon));
#endif
   RETVALUE(ROK);
}
#ifdef WR_RSYS_OAM
/*
 *
 *       Fun:    smUpdateNlPowerOffsetParams
 *
 *       Desc:   update the Power Offset parameter values modified by SON for
 *       TxPower.
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PRIVATE S16 smUpdateNlPowerOffsetParams
(
NlUpdateTxPwrCfgInd  *txPwrCfgInd
)
#else
PRIVATE S16 smUpdateNlPowerOffsetParams(txPwrCfgInd)
NlUpdateTxPwrCfgInd  *txPwrCfgInd;
#endif /* ANSI */
{
   U32    idx;
   U32    pssCnt;
   U32    sssCnt;
   U32    pbchCnt;

   TRC3(smUpdateNlPowerOffsetParams);

   for(pssCnt = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pschPowerOffCnt -1; 
       pssCnt > 0; 
       pssCnt --)
   {
      if(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pschPowerOffset[pssCnt] ==
            txPwrCfgInd->pssPowerOffset)
      {
         for(idx = pssCnt; idx > 0; idx --)
         {
            lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pschPowerOffset[idx] = 
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pschPowerOffset[idx -1]; 
         }
         break;
      }
   }
   lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pschPowerOffset[0] =
      txPwrCfgInd->pssPowerOffset;
   for(sssCnt = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.sschPowerOffCnt -1; 
       sssCnt > 0; 
       sssCnt --)
   {
      if(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.sschPowerOffset[sssCnt] ==
            txPwrCfgInd->sssPowerOffset)
      {
         for(idx = sssCnt; idx > 0; idx --)
         {
            lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.sschPowerOffset[idx] = 
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.sschPowerOffset[idx -1]; 
         }
         break;
      }
   }
   lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.sschPowerOffset[0] =
      txPwrCfgInd->sssPowerOffset;

   for(pbchCnt = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pbchPowerOffCnt -1; 
       pbchCnt > 0; 
       pbchCnt --)
   {
      if(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pbchPowerOffset[pbchCnt] ==
            txPwrCfgInd->pbchPowerOffset)
      {
         for(idx = pbchCnt; idx > 0; idx --)
         {
            lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pbchPowerOffset[idx] = 
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pbchPowerOffset[idx -1]; 
         }
         break;
      }
   }
   lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePowerOffsetParams.pbchPowerOffset[0] =
      txPwrCfgInd->pbchPowerOffset;

#ifdef WR_RSYS_OAM
   smUpdateSONParams(MSM_LTE_POWER_OFFSET_PARAMETERS, 
                  (void *)&(lteeNodeBparams[(txPwrCfgInd->cellCfgIdx)-1].ltePowerOffsetParams));
#endif
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smUpdateNlPdschCfgCommonParams
 *
 *       Desc:   update the PdschConfigCommon value modified by SON for
 *       TxPower.
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PRIVATE S16 smUpdateNlPdschCfgCommonParams
(
NlUpdateTxPwrCfgInd  *txPwrCfgInd
)
#else
PRIVATE S16 smUpdateNlPdschCfgCommonParams(txPwrCfgInd)
NlUpdateTxPwrCfgInd  *txPwrCfgInd;
#endif /* ANSI */
{
   U32    idx;
   U32    refSigTxPwrCount;

   TRC3(smUpdateNlPdschCfgCommonParams);

   for(refSigTxPwrCount = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.refSignalPwrCnt -1; 
       refSigTxPwrCount > 0; 
       refSigTxPwrCount --)
   {
      if(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.referenceSignalPwr[refSigTxPwrCount] ==
            txPwrCfgInd->refSignalTxPwr)
      {
         for(idx = refSigTxPwrCount; idx > 0; idx --)
         {
            lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.referenceSignalPwr[idx] = 
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.referenceSignalPwr[idx -1]; 
         }
         break;
      }
   }
   lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.referenceSignalPwr[0] = txPwrCfgInd->refSignalTxPwr;

   for(refSigTxPwrCount = lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.pBCnt -1; 
       refSigTxPwrCount > 0; 
       refSigTxPwrCount --)
   {
      if(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.pB[refSigTxPwrCount] ==
            txPwrCfgInd->refSignalTxPwr)
      {
         for(idx = refSigTxPwrCount; idx > 0; idx --)
         {
            lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.pB[idx] = 
               lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.pB[idx -1]; 
         }
         break;
      }
   }
   lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.pB[0] = txPwrCfgInd->pB;
 
#ifdef WR_RSYS_OAM
   smUpdateSONParams(MSM_LTE_PDSCH_CONFIG_COMMON_PARAMETERS, 
                  (void *)&(lteeNodeBparams[(txPwrCfgInd->cellCfgIdx)-1].ltePdschCfgCommon));
#endif
   RETVALUE(ROK);
}
#endif

#if 1
/*
 *
 *       Fun:    smUpdateSib2Params
 *
 *       Desc:   update the PCI value modified by SON
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PRIVATE S16 smUpdateSib2Params
(
NlUpdateTxPwrCfgInd  *txPwrCfgInd
)
#else
PRIVATE S16 smUpdateSib2Params(txPwrCfgInd)
NlUpdateTxPwrCfgInd  *txPwrCfgInd;
#endif /* ANSI */
{
   TRC3(smUpdateSib2Params);
   MsmLtePdschCfgCommon modPdschCfg;

   /* Trigger SIB2 change to UE for PDSCH Params */
   if(lteeNodeBparams[WR_SM_DFLT_CELL_INDX].ltePdschCfgCommon.referenceSignalPwr[0] !=
         txPwrCfgInd->refSignalTxPwr)
   {
      modPdschCfg.actType = MSM_ACT_MOD;
      modPdschCfg.refSignalPwrCnt = 1;
      modPdschCfg.referenceSignalPwr[0] = txPwrCfgInd->refSignalTxPwr;
      modPdschCfg.pBCnt = 1;
      modPdschCfg.pB[0] = txPwrCfgInd->pB;
#ifdef WR_RSYS_OAM
      smDynCfgReq((Void *)&modPdschCfg,MSM_LTE_PDSCH_CONFIG_COMMON_PARAMETERS,0);
#endif

      /* Note: This has been added till OAM supports dynamic configuration of
       * MSM_LTE_PDSCH_CONFIG_COMMON_PARAMETERS once SON updates the same to
       * OAM. As of now, we see that once SON updates, dynamic configuration
       * is not being triigered from OAM. This will be removed once OAM
       * provides the required functionality */
      smCfgCb.sonTriggeredDynCfg = TRUE;
   }

   RETVALUE(ROK);
}
#endif


/*
 *
 *       Fun:    smUpdateNlTxPwrVal
 *
 *       Desc:   update the PCI value modified by SON
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 smUpdateNlTxPwrVal
(
NlUpdateTxPwrCfgInd  *txPwrCfgInd
)
#else
PUBLIC S16 smUpdateNlTxPwrVal(txPwrCfgInd)
NlUpdateTxPwrCfgInd  *txPwrCfgInd;
#endif /* ANSI */
{
   TRC3(smUpdateNlTxPwrVal);

   /* Only if Cell is up (PHY is up), send Tx Power change Req to CL */
   if(smCb.smState == WR_SM_STATE_CELL_UP 
#ifdef WR_RSYS_OAM
     || smCb.smState ==  WR_SM_STATE_OAM_DYN_START
#endif
     )
   {
      S16 refSigPwr = (-(txPwrCfgInd->refSignalTxPwr) * 4);
      SmLysTPMTxPwrChangeReq(refSigPwr);         
#if 1
      smUpdateSib2Params(txPwrCfgInd); 
#endif
   }

#ifdef WR_RSYS_OAM
   smUpdateNlPdschCfgCommonParams(txPwrCfgInd);
   smUpdateNlPowerOffsetParams(txPwrCfgInd);
#endif


   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smUpdateNlMeasRptInterval
 *
 *       Desc:   update the measurement interval value configured by BRDCM-SON
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */
#ifdef ANSI
PUBLIC S16 smUpdateNlMeasRptInterval
(
U32   measInterval
)
#else
PUBLIC S16 smUpdateNlMeasRptInterval(measInterval)
U32   measInterval;
#endif /* ANSI */
{
   TRC3(smUpdateNlMeasRptInterval);
   lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteCellMeasCfgGrp.
     measEutraPeridRptCfg[MSM_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS].sonCfgRptInterval = 
      measInterval;
   lteeNodeBparams[WR_SM_DFLT_CELL_INDX].lteCellMeasCfgGrp.
     measEutraPeridRptCfg[MSM_MEAS_EUTRA_PERIODIC_REPORT_STRNG_CELLS].
     isPerdStrongCellCfgRptEnable = TRUE; 
   RETVALUE(ROK);
}

/*
 *
 *       Fun:    smBuildNlNghCellCfg
 *
 *       Desc:   Build neighbor cell configuration
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */

#ifdef ANSI
PUBLIC S16 smBuildNlNghCellCfg
(
LnlNghCellCfg   *nghCellCfg,
U8               cellCfgIdx
)
#else
PUBLIC S16 smBuildNlNghCellCfg(nghCellCfg, cellCfgIdx)
LnlNghCellCfg   *nghCellCfg;
U8               cellCfgIdx;
#endif /* ANSI */
{
   U32                 enbId;
   U32                 dupCount;
   U32                 nghCellCount; 
   LnlNghCellAdd       *nghAdd = NULLP;
   LnlNghCellCfgParam  *nghCellParam = NULLP;
   LnlNghCellInfo      *nghCellInfo = NULLP;
   U32                 enbType;
   MsmNeighCellCfg     *neighCellCfg = &(lteeNodeBparams[cellCfgIdx].lteNeighCellCfg);
   TRC3(smBuildNlNghCellCfg);
   nghCellCfg->servCellId = (cellCfgIdx + 1);
   nghCellCfg->numNghEnb = neighCellCfg->numEutraCells;
   for(nghCellCount = 0; nghCellCount < nghCellCfg->numNghEnb; nghCellCount ++)
   {
      enbId = neighCellCfg->t.neighAddCfg[nghCellCount].eutraCell.cid;
      for(dupCount = 0; dupCount < nghCellCount; dupCount++)
      {
         /* checking if the eNB is already add to configuration */
         /* if yes, ignoring the dulicate configuration and proceeding */
         /* this may occur when multiple cells or same eNB is configured */
         if(enbId == neighCellCfg->t.neighAddCfg[dupCount].eutraCell.cid)
         {
            continue;
         }
      }
      enbType = neighCellCfg->t.neighAddCfg[nghCellCount].eutraCell.enbType;
      if(enbType == 0)
      {
         nghCellCfg->nghEnbCellCfg[nghCellCount].nghEnbId = (enbId >> 8); 
      }
      else
      {
         nghCellCfg->nghEnbCellCfg[nghCellCount].nghEnbId = enbId;
      }
      nghCellParam = &(nghCellCfg->nghEnbCellCfg[nghCellCount].nghCellParam);
      nghCellParam->cfgType = LNL_NGH_ADD;
      nghAdd = &(nghCellParam->u.nghCellAdd);
      nghAdd->numNgh = 1;
      nghAdd->nghCellAddInfo[0].numNghNgh = 0;
      nghCellInfo = &(nghAdd->nghCellAddInfo[0].nghCellInfo);
      nghCellInfo->ecgi.cellId = nghCellCfg->nghEnbCellCfg[nghCellCount].nghEnbId;
      /*FILL PLMN ID*/
      nghCellInfo->ecgi.plmn.numMncDigits = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.plmnId[0].numMncDigits;
      nghCellInfo->ecgi.plmn.mcc[0] = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.plmnId[0].mcc[0];
      nghCellInfo->ecgi.plmn.mcc[1] = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.plmnId[0].mcc[1];
      nghCellInfo->ecgi.plmn.mcc[2] = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.plmnId[0].mcc[2];
      nghCellInfo->ecgi.plmn.mnc[0] = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.plmnId[0].mnc[0];
      nghCellInfo->ecgi.plmn.mnc[1] = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.plmnId[0].mnc[1];
      nghCellInfo->ecgi.plmn.mnc[2] = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.plmnId[0].mnc[2];
      nghCellInfo->pci = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.pci;
      nghCellInfo->dlEarfcn = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.earfcnDl;
      nghCellInfo->ulEarfcn = 
           neighCellCfg->t.neighAddCfg[nghCellCount]. \
                              eutraCell.earfcnUl;

      RLOG3(L_INFO,"SM->SON Neighbor Config [Numcell %u]: enbid = %lu, pci = %u\n",
            nghCellCount + 1,
            nghCellCfg->nghEnbCellCfg[nghCellCount].nghEnbId,
            nghCellInfo->pci);

      /* This is from wr_cfg.txt. Hence no neighbor cell has prach information
       * populated */
      nghCellInfo->isNghPrachInfo = FALSE;
   }

   RETVALUE(ROK);
}/*april 13*/
/*
 *
 *       Fun:    smBuildNlCellCfg
 *
 *       Desc:   Build Cell configuration of a cell 
 *
 *       Ret:    ROK     - succeeded
 *               RFAILED - failed
 *
 *       Notes:  None
 *
 *       File:   wr_smm_son_utils.c
 *
 */

#ifdef ANSI
PUBLIC S16 smBuildNlCellCfg
(
LnlCellCfg   *cellCfg,
U8            cellCfgIdx
)
#else
PUBLIC S16 smBuildNlCellCfg(cellCfg, cellCfgIdx)
LnlCellCfg   *cellCfg;
U8            cellCfgIdx;
#endif /* ANSI */
{
   TRC3(smBuildNlCellCfg);
   MsmLtePlmnId  *priPlmn = &(lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[0].plmnId);
   cellCfg->cellId = (cellCfgIdx + 1);
   cellCfg->ecgi.cellId = lteeNodeBparams[cellCfgIdx].lteCellSib1CfgGrp.cellAccessInfo.cellId;
   cellCfg->ecgi.plmn.numMncDigits = priPlmn->numMncDigits;
   cellCfg->ecgi.plmn.mcc[0] = priPlmn->mcc[0];
   cellCfg->ecgi.plmn.mcc[1] = priPlmn->mcc[1];
   cellCfg->ecgi.plmn.mcc[2] = priPlmn->mcc[2];
   cellCfg->ecgi.plmn.mnc[0] = priPlmn->mnc[0];
   cellCfg->ecgi.plmn.mnc[1] = priPlmn->mnc[1];
   cellCfg->ecgi.plmn.mnc[2] = priPlmn->mnc[2];
   smBuildNlCellCsgCfg(cellCfg);
   smBuildNlCellEarfcnCfg(cellCfg, cellCfgIdx);
   smBuildNlCellPciCfg(cellCfg, cellCfgIdx);

   cellCfg->bandWidth = lteeNodeBparams[cellCfgIdx].lteCellMibCfgGrp.dlBw[0];
   if(NHU_MODE_TDD == lteeNodeBparams[cellCfgIdx].lteSmCellCfg.duplexMode)
   {
      cellCfg->duplexMode = 1;
   }
   else
   {
      cellCfg->duplexMode = 0;
   }

#ifdef LTE_TDD
   cellCfg->subFrameCfg = wrSmTddSubframeConfig;
#endif

   smBuildNlCellPrachCfg(&(cellCfg->prachCfgInfo), cellCfgIdx);
   smBuildNlCellPucchCfg(&(cellCfg->pucchResCfg), cellCfgIdx);
   /* PHICH Configuration */
   cellCfg->phichCfg.ngEnum = wrSmDfltPhichRes;
   cellCfg->phichCfg.isDurExtend = wrSmDfltPhichDur;
   
   smBuildNlCellTxPwrCfg(cellCfg);
   smBuildNlCellRsysTpmCfg(cellCfg);

   RETVALUE(ROK);
}

/********************************************************************30**

           End of file:     fc_smm_son_utils.c@@/main/TeNB_61750_TDD_EA2_4.0.0_SON/9 - Tue Jan 13 12:01:15 2015

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
SID$        ---      
*********************************************************************91*/

