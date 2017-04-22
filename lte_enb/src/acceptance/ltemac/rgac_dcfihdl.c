

/********************************************************************20**

  Name:    LTE MAC - acc test file

  Type:    C Source file

  Desc:    This file contains the acc source for DCFI UT testing.

  File:    rgac_dcfihdl.c

  Sid:     

  Prg:     nsadar 
 *********************************************************************21*/
/* header include files (.h) */
#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
#include "gen.h"           /* general */
#include "ssi.h"           /* system services */
#include "cm_tkns.h"       /* Common Token Defines */
#include "cm_llist.h"      /* Common Link List Defines */
#include "cm_hash.h"       /* Common Hash List Defines */
#include "cm_mblk.h"       /* memory management */
#include "cm_lte.h"        /* Common LTE Defines */
#include "cm_xta.h"        /* Common LTE Defines */
#include "rg_env.h"        /* MAC Environment Defines */
#include "crg.h"           /* CRG Interface defines */
#include "rgr.h"           /* RGR Interface defines */
#include "rgu.h"           /* RGU Interface defines */
#include "tfu.h"           /* RGU Interface defines */
#include "lrg.h"           /* LRG Interface defines */
#include "rg_err.h"        /* MAC error defines */
#include "rgac_rgr.h"
#include "rgac_acc.h"
#include "rg_env.h"
#include "rg_sch_inf.h"
#include "rg_sch.h"
#if 0
#include "rg_sch_err.h"
#endif
/* header/extern include files (.x) */
#include "gen.x"           /* general */
#include "ssi.x"           /* system services */
#include "cm5.x"           /* Common Timers */
#include "cm_tkns.x"       /* Common Token Definitions */
#include "cm_llist.x"      /* Common Link List Definitions */
#include "cm_lib.x"        /* Common Library Definitions */
#include "cm_hash.x"       /* Common Hash List Definitions */
#include "cm_mblk.x"       /* memory management */
#include "cm_lte.x"        /* Common LTE Defines */
#include "cm_xta.x"        /* Common LTE Defines */
#include "crg.x"           /* CRG Interface includes */
#include "rgr.x"           /* RGR Interface includes */
#include "rgu.x"           /* RGU Interface includes */
#include "tfu.x"           /* RGU Interface includes */
#include "lrg.x"           /* LRG Interface includes */
#include "rgac_acc.x"
#include "rgac_rgr.x"        /* MAC error defines */
#include "rgr.x"           /* layer management typedefs for MAC */
#include "rg_sch_inf.x"         /* typedefs for Scheduler */
#include "rg_sch.x"        /* typedefs for Scheduler */

#include "rg_sch_cmn.h"
#include "rg_sch_cmn.x"


#ifdef LTE_TDD
/* Number of DL Sub-frame in TDD config Types */
PRIVATE U8 numDlSubFrame[] = {4, 6, 8, 7, 8, 9, 5};

typedef enum{
   UL_SF = 0,
   DL_SF,
   SP_SF
} rgAcSubFrmType;

PRIVATE rgAcSubFrmType subFrameType [][RGSCH_NUM_SUB_FRAMES] = 
{
   {DL_SF, SP_SF, UL_SF, UL_SF, UL_SF, DL_SF, SP_SF, UL_SF, UL_SF, UL_SF},
   {DL_SF, SP_SF, UL_SF, UL_SF, DL_SF, DL_SF, SP_SF, UL_SF, UL_SF, DL_SF},
   {DL_SF, SP_SF, UL_SF, DL_SF, DL_SF, DL_SF, SP_SF, UL_SF, DL_SF, DL_SF},
   {DL_SF, SP_SF, UL_SF, UL_SF, UL_SF, DL_SF, DL_SF, DL_SF, DL_SF, DL_SF},
   {DL_SF, SP_SF, UL_SF, UL_SF, DL_SF, DL_SF, DL_SF, DL_SF, DL_SF, DL_SF},
   {DL_SF, SP_SF, UL_SF, DL_SF, DL_SF, DL_SF, DL_SF, DL_SF, DL_SF, DL_SF},
   {DL_SF, SP_SF, UL_SF, UL_SF, UL_SF, DL_SF, SP_SF, UL_SF, UL_SF, DL_SF}
};
#endif

typedef struct {
   U8 cfi;
   U8 lwrCcePercentage;
} rgAcCfiDecrInfo;


typedef struct {
   U8 percentFailedPdcch;   /* Percentage of this sample TTIs for which CCE failed */
} rgAcPerSampleInfo;

typedef struct {
   U8                 dfltCfi;
   U8                 exptdCfi;
   Bool               isDynCfiEnb;
   U8                 numSamples;
#define RGAC_NUM_SAMPLE_TC_INPUT 11
   rgAcPerSampleInfo  sampleInfo[RGAC_NUM_SAMPLE_TC_INPUT]; /* For CFI Increment */
   rgAcCfiDecrInfo    decrInfo[3]; /* For CFI 1,2,3 */
} rgAcUtTestCase;

/* Add test cases here */
#if 1
PRIVATE rgAcUtTestCase rgAcUTCases[] = {
   {2, 3, TRUE, 1, {{100}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}, {{0, 0}, {0,0}, {0,0}}},   /* DCFI_FDD_04, DCFI_TDD_10, DCFI_TDD_16, DCFI_CMN_46 DCFI_TDD_42 */
   {2, 3, TRUE, 2, {{90}, {10}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}, {{0, 0}, {0,0}, {0,0}}},   /* DCFI_FDD_05, DCFI_TDD_11, DCFI_TDD_17 */
   {2, 3, TRUE, 10, {{50}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {50}, {0}}, {{0, 0}, {0,0}, {0,0}}},  /* DCFI_FDD_06, DCFI_TDD_12, DCFI_TDD_18 */
   {2, 2, TRUE, 11, {{50}, {10}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {50}}, {{0, 0}, {0,0}, {0,0}}}, /* DCFI_FDD_07, DCFI_TDD_13, DCFI_TDD_19 */
   {2, 3, TRUE, 10, {{20}, {30}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {50}, {0}}, {{0, 0}, {0,0}, {0,0}}}, /* DCFI_FDD_08, DCFI_TDD_14, DCFI_TDD_20 */
   {3, 3, TRUE, 1, {{100}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}, {{0, 0}, {0,0}, {0,0}}},   /* DCFI_FDD_09, DCFI_TDD_15, DCFI_TDD_21 */
   {1, 3, TRUE, 3, {{100}, {0}, {100}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}, {{0, 0}, {0,0}, {0,0}}}, 
   {2, 1, TRUE, 11, {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}, {{0, 0}, {0,0}, {0,0}}},    /* DCFI_CMN_28 DCFI_CMN_47 */
   {1, 1, TRUE, 11, {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}, {{0, 0}, {0,0}, {0,0}}},     /* DCFI_FDD_48, DCFI_TDD_49, DCFI_TDD_50 */
   {2, 1, TRUE, 0, {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}, {{1, 90}, {2,10}, {0,0}}}, /* DCFI_FDD_33, DCFI_TDD_35, DCFI_TDD_36 */
   {1, 1, TRUE, 0, {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}, {{1, 80}, {2,20}, {0,0}}}  /* DCFI_FDD_34, DCFI_TDD_37, DCFI_TDD_38 */
};
#else
PRIVATE rgAcUtTestCase rgAcUTCases[] = {
   {2, 3, TRUE, 10, {{20}, {30}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {50}, {0}}, {{0, 0}, {0,0}, {0,0}}} /* DCFI_FDD_08, DCFI_TDD_14, DCFI_TDD_20 */
};
#endif

#define RGSCH_CFI_TTI_SAMPLE_INTRVL ((RGSCH_CFI_TTI_MON_INTRVL * RGSCH_CFI_STEP_UP_TTI_PRCNTG)/100)
#define RGSCH_CFI_NUM_SAMPLE_INTRVL (RGSCH_CFI_TTI_MON_INTRVL/RGSCH_CFI_TTI_SAMPLE_INTRVL)

#ifdef ANSI
PUBLIC S16 rgAcDcfiStubExec
(
 CmXtaTCCb    *tcCb,    /* tcCb data structure  */
 CmXtaSpCb    *spCb
 )
#else
PUBLIC S16 rgAcDcfiStubExec(tcCb,spCb)
   CmXtaTCCb    *tcCb;    /* tcCb data structure  */
   CmXtaSpCb    *spCb;
#endif
{
   U8             instId = 1;
   RgSchCb        *instCb = NULLP;
   RgSchCellCb    *cell = NULLP;
   RgSchCmnCell   *cellSch = NULLP;

   U32            numTcs;
   U32            tcCount;
   U32            cfiStepUpTtiCnt = 0;
   U8             delta = 0;
   U32            smplePrd = RGSCH_CFI_TTI_SAMPLE_INTRVL;
#ifdef LTE_TDD
   U32            numDlSfInSmpleInt;
   U32            numDlSfInMonInt = 0;
#endif

   instCb = &rgSchCb[instId -1];
   cell = instCb->rgrSap[instId - 1].cell;
   cellSch = RG_SCH_CMN_GET_CELL(cell);
#ifdef LTE_TDD
   numDlSfInMonInt = (numDlSubFrame[cell->ulDlCfgIdx] * RGSCH_CFI_TTI_MON_INTRVL) / 10;
   cfiStepUpTtiCnt = (numDlSfInMonInt * RGSCH_CFI_STEP_UP_TTI_PRCNTG) / 100;
   numDlSfInSmpleInt = (numDlSubFrame[cell->ulDlCfgIdx] * smplePrd) / 10;
#else
   cfiStepUpTtiCnt = (RGSCH_CFI_TTI_MON_INTRVL * RGSCH_CFI_STEP_UP_TTI_PRCNTG) / 100;
#endif

#ifndef ALIGN_64BIT
   CMXTA_DBG_PARAM((_cmxtap, "rgAcDcfiStubExec(): tcId (%ld)\n", tcCb->tcId));
#else
   CMXTA_DBG_PARAM((_cmxtap, "rgAcDcfiStubExec(): tcId (%d)\n", tcCb->tcId));
#endif

   cmXtaXmlGetVal(tcCb, spCb->childStep, CMXTA_ATTRIB_U8, "instId",  &(instId));

   numTcs = sizeof(rgAcUTCases)/sizeof(rgAcUtTestCase);

   for (tcCount = 0; tcCount < numTcs; tcCount++)
   {
      U8         dlIdx = 0;
      U8         oldCfi = 0;
      U32        samples = 0;
      RgSchDlSf  *dlSf = NULLP;
      CmLteTimingInfo frm = {0,0};
#define RGAC_CFI_JUMP_MAX_COUNT 2
      U32 numTtiCceFailPerSample[RGAC_CFI_JUMP_MAX_COUNT][RGSCH_CFI_NUM_SAMPLE_INTRVL]; /* 2D array for multiple CFI jump from 1->2->3 or reverse*/
      U32 decrCfiTti[] = {0,0};
      /*Bool flag  = FALSE;*/
      U32 cfiIncr = 0;
      U32 cfiDecr = 0;
      U32 ttiCnt = 0;

      memset(numTtiCceFailPerSample, 0, sizeof(numTtiCceFailPerSample));
      cell->crntTime.sfn = 0;
      cell->crntTime.subframe = 0;
      cellSch->dl.newCfi = cellSch->dl.currCfi = rgAcUTCases[tcCount].dfltCfi;

      cell->dynCfiCb.isDynCfiEnb = rgAcUTCases[tcCount].isDynCfiEnb;

      cell->dynCfiCb.cceUsed = 0;
      cell->dynCfiCb.lowCceCnt = 0;
      cell->dynCfiCb.ttiCnt = 0;
      cell->dynCfiCb.cceFailCnt = 0;
      cell->dynCfiCb.cceFailSum = 0;
      cell->dynCfiCb.cfiSwitches = 0;
      cell->dynCfiCb.cfiIncr = 0;
      cell->dynCfiCb.cfiDecr = 0;
      cell->dynCfiCb.switchOvrInProgress = FALSE;
      cell->dynCfiCb.prevCceFailIdx = 0;

      memset(cell->dynCfiCb.cceFailSamples, 0, (cell->dynCfiCb.numFailSamples * sizeof(U16)));

      frm = cell->crntTime;
      RGSCH_INCR_SUB_FRAME(frm, delta);

      if (rgAcUTCases[tcCount].numSamples != 0)
      {
         for (samples = 0; samples < rgAcUTCases[tcCount].numSamples; samples++)
         {
            U8   isHiDci0;
            U32  ttis;
            U32  numTtiCceFailed;
            U32  sampleIdx = samples % RGSCH_CFI_NUM_SAMPLE_INTRVL;
#ifdef LTE_TDD
            numTtiCceFailed = (rgAcUTCases[tcCount].sampleInfo[samples].percentFailedPdcch * numDlSfInSmpleInt) / 100;
#else
            numTtiCceFailed = (rgAcUTCases[tcCount].sampleInfo[samples].percentFailedPdcch * smplePrd) / 100;
#endif         
            numTtiCceFailPerSample[cfiIncr][sampleIdx] = 0; /* To take care of the moving average */
            for (ttis = 0; (ttis < smplePrd); ttis++)
            {
#ifdef LTE_TDD
               if (subFrameType[cell->ulDlCfgIdx][frm.subframe] != UL_SF)
#endif
               {
#ifdef LTE_TDD
                  dlIdx = rgSCHUtlGetDlSfIdx(cell, &frm);
                  dlSf = cell->subFrms[dlIdx];
                  isHiDci0 = rgSchTddPuschTxKTbl[cell->ulDlCfgIdx][frm.subframe];
#else
                  /* Changing the idexing
                     so that proper subframe is selected */
                  dlIdx = (((frm.sfn & 1) * RGSCH_NUM_SUB_FRAMES) + frm.subframe);
                  RGSCH_ARRAY_BOUND_CHECK(cell->instIdx, cell->subFrms, dlIdx);
                  dlSf = cell->subFrms[dlIdx];
                  isHiDci0 = 1;
#endif

                  if (numTtiCceFailed)
                  {
                     dlSf->isCceFailure = TRUE;
                     numTtiCceFailed--;
                     numTtiCceFailPerSample[cfiIncr][sampleIdx]++;
                  }
                  else
                  {
                     dlSf->isCceFailure = FALSE;
                  }


                  if (isHiDci0)
                  {
                     dlSf->dlUlBothCmplt = 1;
                  }
                  else
                  {
                     dlSf->dlUlBothCmplt = 0;
                  }

                  oldCfi = cellSch->dl.newCfi;
                  ttiCnt = cell->dynCfiCb.ttiCnt;

                  /* Test Function */
                  rgSchCmnUpdCfiDb(cell, delta);

                  if (oldCfi > cellSch->dl.newCfi)
                  {
                     cellSch->dl.currCfi = cellSch->dl.newCfi;
                     decrCfiTti[cfiDecr++] = ttiCnt;
                     cell->dynCfiCb.switchOvrInProgress = FALSE;
                  }
                  if (oldCfi < cellSch->dl.newCfi)
                  {
                     cellSch->dl.currCfi = cellSch->dl.newCfi;
                     cfiIncr++;
                     cell->dynCfiCb.switchOvrInProgress = FALSE;
                  }
               }
#ifdef LTE_TDD
               else
               {
                  cell->dynCfiCb.ttiCnt++;
               }
#endif

               RGSCH_INCR_SUB_FRAME(cell->crntTime, 1);
               RGSCH_INCR_SUB_FRAME(frm, 1);
            }
         }
      }
      if (rgAcUTCases[tcCount].decrInfo[0].lwrCcePercentage != 0)
      {
         U32  ttis;
         U32 decrSample = 0, numTtiDecr = 0;
#ifdef LTE_TDD
         U8  mPhich;
#endif
         for (ttis = 0; (ttis <= RGSCH_CFI_TTI_MON_INTRVL); ttis++)
         {
            U32 nCceLowerCfi;

            if ((numTtiDecr == 0) && (decrSample < 3))
            {
#ifdef LTE_TDD
               numTtiDecr = (rgAcUTCases[tcCount].decrInfo[decrSample++].lwrCcePercentage * numDlSfInMonInt) / 100;
#else
               numTtiDecr = (rgAcUTCases[tcCount].decrInfo[decrSample++].lwrCcePercentage * RGSCH_CFI_TTI_MON_INTRVL) / 100;
#endif
               numTtiDecr++; /* This has been done because our logic in the code has an exception that when 1st time ttiCnt=0,
                                it reset lowCceCnt to 0. Same is for the for loop "=" RGSCH_CFI_TTI_MON_INTRVL */
            }

#ifdef LTE_TDD
            if (subFrameType[cell->ulDlCfgIdx][frm.subframe] != UL_SF)
#endif
            {
               U8 isHiDci0;

               numTtiDecr--;
#ifdef LTE_TDD
               dlIdx = rgSCHUtlGetDlSfIdx(cell, &frm);
               dlSf = cell->subFrms[dlIdx];
               isHiDci0 = rgSchTddPuschTxKTbl[cell->ulDlCfgIdx][frm.subframe];
#else
               dlIdx = (((frm.sfn & 1) * RGSCH_NUM_SUB_FRAMES) + frm.subframe);
               RGSCH_ARRAY_BOUND_CHECK(cell->instIdx, cell->subFrms, dlIdx);
               dlSf = cell->subFrms[dlIdx];
               isHiDci0 = 1;
#endif

#ifdef LTE_TDD      
               mPhich = rgSchTddPhichMValTbl[cell->ulDlCfgIdx][dlSf->sfNum];
               nCceLowerCfi = cell->dynCfiCb.cfi2NCceTbl[mPhich][rgAcUTCases[tcCount].decrInfo[decrSample-1].cfi];
#else
               nCceLowerCfi = cell->dynCfiCb.cfi2NCceTbl[0][rgAcUTCases[tcCount].decrInfo[decrSample-1].cfi];
#endif
               dlSf->isCceFailure = FALSE;
               if (isHiDci0)
               {
                  dlSf->dlUlBothCmplt = 1;
               }
               else
               {
                  dlSf->dlUlBothCmplt = 0;
               }
               dlSf->cceCnt = nCceLowerCfi - 1;

               oldCfi = cellSch->dl.newCfi;
               ttiCnt = cell->dynCfiCb.ttiCnt;

               /* Test Function */
               rgSchCmnUpdCfiDb(cell, delta);

               if (oldCfi > cellSch->dl.newCfi)
               {
                  cellSch->dl.currCfi = cellSch->dl.newCfi;
                  decrCfiTti[cfiDecr++] = ttiCnt;
                  cell->dynCfiCb.switchOvrInProgress = FALSE;
               }
            }
#ifdef LTE_TDD
            else
            {
               cell->dynCfiCb.ttiCnt++;
            }
#endif
            RGSCH_INCR_SUB_FRAME(cell->crntTime, 1);
            RGSCH_INCR_SUB_FRAME(frm, 1);
         }
      }

      /* Compare expected result */
      if (cellSch->dl.newCfi != rgAcUTCases[tcCount].exptdCfi)
      {
         CMXTA_DBG_CALLIND((_cmxtap, "TC[%lu] Failed : CFI MisMatch: exp (%u) rcvd (%u) \n",
                  tcCount+1, rgAcUTCases[tcCount].exptdCfi, cellSch->dl.newCfi), 3);
         continue;
         RETVALUE(CMXTA_ERR_INT);
      }

      if (cfiIncr > 0) /* CFI increased */
      {
         U32 sampleIdx;
         U32 actCfiChangeTti[RGAC_CFI_JUMP_MAX_COUNT] = {0,0};

         for (sampleIdx = 0; sampleIdx < RGSCH_CFI_NUM_SAMPLE_INTRVL; sampleIdx++)
         {
            actCfiChangeTti[0] += numTtiCceFailPerSample[0][sampleIdx];
            actCfiChangeTti[1] += numTtiCceFailPerSample[1][sampleIdx];
         }
         if (actCfiChangeTti[0] != cfiStepUpTtiCnt)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "TC[%lu] Failed : 1st CFI change TTI MisMatch: exp (%lu) rcvd (%lu) \n",
                     tcCount+1, cfiStepUpTtiCnt, actCfiChangeTti[0]), 3);
            continue;
            RETVALUE(CMXTA_ERR_INT);
         }
         if ((cfiIncr >= RGAC_CFI_JUMP_MAX_COUNT) && (actCfiChangeTti[1] != cfiStepUpTtiCnt))
         {
            CMXTA_DBG_CALLIND((_cmxtap, "TC[%lu] Failed : 2nd CFI change TTI MisMatch: exp (%lu) rcvd (%lu) \n",
                     tcCount+1, cfiStepUpTtiCnt, actCfiChangeTti[1]), 3);
            continue;
            RETVALUE(CMXTA_ERR_INT);
         }
         if (cell->dynCfiCb.cfiIncr != cfiIncr)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "TC[%lu] Failed : CFI increment mismatch: exp (%lu) rcvd (%lu) \n",
                     tcCount+1, cfiIncr, cell->dynCfiCb.cfiIncr), 3);
            continue;
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      if (cfiDecr > 0) /* CFI decreased */
      {
         if (decrCfiTti[0] != RGSCH_CFI_TTI_MON_INTRVL)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "TC[%lu] Failed : 1st CFI change TTI MisMatch: exp (%lu) rcvd (%lu) \n",
                     tcCount+1, (U32)RGSCH_CFI_TTI_MON_INTRVL, decrCfiTti[0]), 3);
            continue;
            RETVALUE(CMXTA_ERR_INT);
         }
         if ((cfiDecr >= RGAC_CFI_JUMP_MAX_COUNT) && (decrCfiTti[1] != RGSCH_CFI_TTI_MON_INTRVL))
         {
            CMXTA_DBG_CALLIND((_cmxtap, "TC[%lu] Failed : 2nd CFI change TTI MisMatch: exp (%lu) rcvd (%lu) \n",
                     tcCount+1, (U32)RGSCH_CFI_TTI_MON_INTRVL, decrCfiTti[1]), 3);
            continue;
            RETVALUE(CMXTA_ERR_INT);
         }
         if (cell->dynCfiCb.cfiDecr != cfiDecr)
         {
            CMXTA_DBG_CALLIND((_cmxtap, "TC[%lu] Failed : CFI decrement mismatch: exp (%lu) rcvd (%lu) \n",
                     tcCount+1, cfiIncr, cell->dynCfiCb.cfiDecr), 3);
            continue;
            RETVALUE(CMXTA_ERR_INT);
         }
      }
      CMXTA_DBG_CALLIND((_cmxtap, "TC[%lu] PASSED: CFI new (%u), dflt (%u)\n",tcCount+1, cellSch->dl.newCfi, rgAcUTCases[tcCount].dfltCfi), 3);
   }
   RETVALUE(CMXTA_ERR_NONE);
}
