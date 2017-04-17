
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_plat_t2k.c

     Sid:      fc_plat_intel.c@@/main/tenb_main_ccb/1 - Wed Jul 22 16:16:01 2015

     Prg:      Sriky 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="ENBAPP";
static int RLOG_MODULE_ID=64;
static int RLOG_FILE_ID=111;

#include "wr.h"
#include "wr_utils.h"
#include "wr_umm.h"
#include "wr_emm.h"
#include "wr_smm_smallcell.h"
#include "wr_umm_trans.h"
#include "wr_umm_rrc_msg.h"
#include "wr_umm_s1ap_msg.h"
#include "wr_ifm_rrc.h"
#include "wr_ifm_dam.h"
#include "wr_ifm_schd.h"
#include "wr_ifm_s1ap.h"
#include "wr_ifm_rrm.h"
#include "wr_kpi.h"
#include "wr_umm_sch_msg.h"
#include "wr_umm_meas_fun.h"
#include "wr_ifm_l1.h"
#include "wr_ifm_pdcp.h"
#include "wr_umm_drx.h"
#include "wr_ifm_dam.h"
#include <stdlib.h>



U32 wrNonrtTick;
#ifndef TIP_L2_L3_SPLIT
/* This structure is used for storing the platform specific parameters */
typedef struct WrMsCellCfgReq
{
   U16           opMode;
   U32           counter;
   U32           period;
#ifdef ENABLE_CNM
   U8            isCnmEnabled;/* Add comp macro */
#endif
}WrMsCellCfgReq;
#endif

PUBLIC S16 wrFillCtfVndrCellCfg(WrCellCb *cellCb,CtfCfgReqInfo *cellCfgReq);
PUBLIC S16 wrChkCpuLoadAndUpdInstr(U8 *instruction, CmLteCellId cellId);

PUBLIC Void wrPlatNonrtTickHdl()
{
   wrNonrtTick++;
}
/* CPU OL Changes */
#define MIPS_FILE "/sys/devices/virtual/mmonitor/mmonitor/mips_stat"
#define WR_MIPS_STRING_LEN                    24
#define T2K_FDD_CORE0_L_THRESH                 0
#define T2K_FDD_CORE0_U_THRESH                 5
#define T2K_FDD_RST_THRESH                    20

EXTERN Void PrintEGTPStats(void);
EXTERN Void ResetEGTPStats(void); 
#ifdef TENB_AS_SECURITY
EXTERN S16 wrPlatSecExtractSecKeys2
(
 WrUmmTransCb *transCb,
 U8 keyDerType
);
EXTERN S16 wrPlatSecExtractSecKeys1
(
 WrUeCb                       *ueCb,
 U32                          transId,
 U8                           keyDerType
 );
EXTERN S16 wrPlatSecExtractSecKeys
(
 WrUeSecCfg                   *secCfg,
 TknStrBSXL                   *secKey,
 Bool                         *asKeyGenerated,
 U32                          transId
 );
EXTERN S16 wrPlatRrcReEstabExtSecKeys
(
 WrUmmTransCb *transCb,
 U8 keyDerType
 );
EXTERN S16 wrPlatS1SecExtractSecKeys
(
 WrUeSecCfg                   *secCfg,
 Bool                         *asKeyGenerated,
 U32                          transId
 );
EXTERN S16 wrPlatX2HoGetKeNBStar
(
 WrUmmTransCb                 *transCb
 );

#endif
#ifdef RGR_RRM_TICK

PUBLIC Void wrPlatRgrTtiHndl(U32 tticnt, CmLteCellId  cellId)
{
   extern Bool g_usettitmr;
   extern Void mtTmrHdlrPublic(void);
   extern S16 SRegInfoShow(Region region,U32 *availmem);
   U32 memAvail;
   /*static U32 tticnt = 0; */

   if((tticnt % 3000) == 0)
   {
      RLOG1(L_INFO, "Time : %ld sec", (tticnt/100));
   }
   /* Reducing the timer resolution */
      /*WR_DBGP(DBGMASK_SM, (WR_PRNT_BUF, "\nTime : %lu sec \n", (tticnt/100)));
  if((tticnt % 10) == 0) */
   {
      g_usettitmr = TRUE;
      if(cellId == WR_DFLT_CELL_INDX)
      {
         mtTmrHdlrPublic();
      }
   }
   
   if((tticnt % 1000) == 0)
   {
      PrintPDCPStats();
      ResetPDCPStats();
      PrintEGTPStats();
      ResetEGTPStats();
      SRegInfoShow(1, &memAvail);/*EGTP -PDCP thread*/
      memAvail = 0;
   }
}
#endif
#ifdef TENB_AS_SECURITY
/* ccpu00126532 */
PUBLIC S16 wrPlatSecExtractSecKeys2
(
WrUmmTransCb *transCb,
U8 keyDerType
)
{
   CpjKdfReqInfo             *kdfInfo;
   WrUeSecCfg                *secCfg;
   WrUeSecCfg                *hzsecCfg;
   WrCellCb                  *cellCb = NULLP;

   secCfg = (WrUeSecCfg *)(transCb->u.initCtxtCb.secCfg);
   hzsecCfg = (WrUeSecCfg *)(transCb->u.initCtxtCb.hzSecCfg);

   RLOG0(L_DEBUG, "Extract Intg. and ciphering keys");

    WR_ALLOC(&kdfInfo, sizeof(CtfKdfReqInfo));
    if (kdfInfo == NULLP)
    {
       RLOG0(L_FATAL, "Memory allocation failed.");
       RETVALUE(ROK);
    }
    if(keyDerType == CTF_KDF_TYPE2)
    {
       WR_EMM_GET_CELLCB(cellCb, transCb->ueCb->cellId);
       if(cellCb == NULLP)
       {
          RLOG0(L_ERROR, "Invaid Cell ID");
          RETVALUE(RFAILED);
       }
       kdfInfo->keyDerType = CTF_KDF_TYPE2;
       kdfInfo->u.kEnbStarInf.dlCarrFreq = cellCb->dlCarrierFreq;
       kdfInfo->u.kEnbStarInf.physCellId = cellCb->physCellId;
       cmMemcpy((U8*)kdfInfo->u.kEnbStarInf.secKey,\
                       secCfg->kENB, WR_KENB_KEY_LEN);
   }
   else if(keyDerType == CTF_KDF_TYPE1)
   {
       kdfInfo->keyDerType = CTF_KDF_TYPE1;
       kdfInfo->u.kEnbInf.intgAlgoType = secCfg->intgAlgo;
       kdfInfo->u.kEnbInf.ciphAlgoType = secCfg->ciphAlgo;
       cmMemcpy((U8*)kdfInfo->u.kEnbInf.secKey,\
                       (U8*)hzsecCfg->kENB, WR_KENB_KEY_LEN);
    }
   /*Update keNB configuration only*/

   if (wrIfmPdcpKdfReq(kdfInfo, transCb->transId) != ROK)
   {
      RLOG0(L_ERROR, "wrIfmPdcpKdfReq failed");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

PUBLIC S16 wrPlatSecExtractSecKeys1 
(
WrUeCb                       *ueCb,
U32                          transId,
U8                           keyDerType
)
{
   CpjKdfReqInfo             *kdfInfo;
   WrUeSecCfg                *secCfg;
   WrUeSecCfg                *hzsecCfg;
   WrCellCb                  *cellCb = NULLP;

   RLOG0(L_DEBUG, "Extract Intg. and ciphering keys");

   WR_ALLOC(&kdfInfo, sizeof(CtfKdfReqInfo));
   if (kdfInfo == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(ROK);
   }
   if(keyDerType == CTF_KDF_TYPE2)
   {
      secCfg = ueCb->secCfg;
      kdfInfo->keyDerType = CTF_KDF_TYPE2;
      WR_EMM_GET_CELLCB(cellCb, ueCb->cellId);
      if(cellCb == NULLP)
      {
         RLOG0(L_ERROR, "Invaid Cell ID");
         RETVALUE(RFAILED);
      }
      kdfInfo->u.kEnbStarInf.dlCarrFreq = cellCb->dlCarrierFreq;
      kdfInfo->u.kEnbStarInf.physCellId = cellCb->physCellId;
      cmMemcpy((U8*)kdfInfo->u.kEnbStarInf.secKey,\
            secCfg->kENB, WR_KENB_KEY_LEN);
   }
   else if(keyDerType == CTF_KDF_TYPE1)
   {
      hzsecCfg = ueCb->hzSecCfg;
      kdfInfo->keyDerType = CTF_KDF_TYPE1;
      kdfInfo->u.kEnbInf.intgAlgoType = hzsecCfg->intgAlgo;
      kdfInfo->u.kEnbInf.ciphAlgoType = hzsecCfg->ciphAlgo;
      cmMemcpy((U8*)kdfInfo->u.kEnbInf.secKey,\
            (U8*)hzsecCfg->kENB, WR_KENB_KEY_LEN);
   }
   /*Update keNB configuration only*/

   if (wrIfmPdcpKdfReq(kdfInfo, transId) != ROK)
   {
      RLOG0(L_ERROR, "wrIfmPdcpKdfReq failed");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/** @brief This function is responsible for deriving the ciphering and 
 *         integrity keys, and storing them in local data structure.
 *
 * @details
 *
 *     Function: wrUmmSecExtractSecKeys
 *
 *         Processing steps:
 *         - invoke wrUmmSecKeyDervFunc to derive the control plane
 *           ciphering key
 *         - store the derived control plane ciphering key to the local data
 *           structure
 *         - invoke wrUmmSecKeyDervFunc to derive the user plane
 *           ciphering key
 *         - store the derived user plane ciphering key to the local data
 *           structure
 *         - invoke wrUmmSecKeyDervFunc to derive the integrity key
 *         - store the derived integrity key to the local data structure
 *
 * @param[out] secCfg  : local data structure to store the security info
 * @param[in]  secKey  : KeNB
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PUBLIC S16 wrPlatSecExtractSecKeys
(
WrUeSecCfg                   *secCfg,
TknStrBSXL                   *secKey,
Bool                         *asKeyGenerated,
U32                          transId
)
{
   /* ccpu00126532 */
   U8                        idx = 0;
   CpjKdfReqInfo             *kdfInfo;

   RLOG0(L_DEBUG, "Extract Intg. and ciphering keys");

   /* storing the base key (KENB)                                         */
   cmMemcpy((U8*)&secCfg->kENB[0], (U8*)&secKey->val[idx], WR_KENB_KEY_LEN);
   
   if(secCfg->intgAlgo == WR_UMM_NULL_ALGO)
   {
      RLOG0(L_DEBUG, "Integrity Algo is NULL No need for KDF");
      (*asKeyGenerated) = TRUE;   
      RETVALUE(ROK);
   }

   WR_ALLOC(&kdfInfo, sizeof(CtfKdfReqInfo));
   if (kdfInfo == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   kdfInfo->keyDerType = CTF_KDF_TYPE1;
   kdfInfo->u.kEnbInf.ciphAlgoType = secCfg->ciphAlgo;
   kdfInfo->u.kEnbInf.intgAlgoType = secCfg->intgAlgo;
   cmMemcpy((U8*)kdfInfo->u.kEnbInf.secKey, (U8*)secCfg->kENB, WR_KENB_KEY_LEN);

   /* Update keNB configuration only                                      */
   if (wrIfmPdcpKdfReq(kdfInfo, transId) != ROK)
   {
      RLOG0(L_ERROR, "wrIfmPdcpKdfReq failed");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}
PUBLIC S16 wrPlatRrcReEstabExtSecKeys
(
WrUmmTransCb *transCb,
U8 keyDerType
)
{
   CpjKdfReqInfo             *kdfInfo;
   WrCellCb                  *cellCb = NULLP;
   WrUeCb                    *ueCb = transCb->ueCb;

   RLOG0(L_DEBUG, "Extract Intg. and ciphering keys");

    WR_ALLOC(&kdfInfo, sizeof(CtfKdfReqInfo));
    if (kdfInfo == NULLP)
    {
       RLOG0(L_FATAL, "Memory allocation failed.");
       RETVALUE(ROK);
    }
    if(keyDerType == CTF_KDF_TYPE2)
    {
       kdfInfo->keyDerType = CTF_KDF_TYPE2;
       WR_EMM_GET_CELLCB(cellCb, transCb->ueCb->cellId);
       if(cellCb == NULLP)
       {
          RLOG0(L_ERROR, "Invaid Cell ID");
          RETVALUE(RFAILED);
       }

       kdfInfo->u.kEnbStarInf.dlCarrFreq = cellCb->dlCarrierFreq;
       kdfInfo->u.kEnbStarInf.physCellId = cellCb->physCellId;
       cmMemcpy((U8*)kdfInfo->u.kEnbStarInf.secKey,\
                       ueCb->hzSecCfg->kENB, WR_KENB_KEY_LEN);
   }
   else if(keyDerType == CTF_KDF_TYPE1)
   {
       kdfInfo->keyDerType = CTF_KDF_TYPE1;
       kdfInfo->u.kEnbInf.intgAlgoType = ueCb->secCfg->intgAlgo;
       kdfInfo->u.kEnbInf.ciphAlgoType = ueCb->secCfg->ciphAlgo;
       cmMemcpy((U8*)kdfInfo->u.kEnbInf.secKey,\
                       (U8*)ueCb->hzSecCfg->kENB, WR_KENB_KEY_LEN);
   }
   /*Update keNB configuration only*/

   if (wrIfmPdcpKdfReq(kdfInfo, transCb->transId) != ROK)
   {
      RLOG0(L_ERROR, "wrIfmPdcpKdfReq failed");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

PUBLIC S16 wrPlatS1SecExtractSecKeys
(
WrUeSecCfg                   *secCfg,
Bool                         *asKeyGenerated,
U32                          transId
)
{
   CpjKdfReqInfo             *kdfInfo;

   RLOG0(L_DEBUG, "Extract Intg. and ciphering keys");

   if(secCfg->intgAlgo == WR_UMM_NULL_ALGO)
   {
      RLOG0(L_DEBUG, "Integrity Algo is NULL No need for KDF");
      (*asKeyGenerated) = TRUE;   
      RETVALUE(ROK);
   }

   WR_ALLOC(&kdfInfo, sizeof(CtfKdfReqInfo));
   if (kdfInfo == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   kdfInfo->keyDerType = CTF_KDF_TYPE1;
   kdfInfo->u.kEnbInf.ciphAlgoType = secCfg->ciphAlgo;
   kdfInfo->u.kEnbInf.intgAlgoType = secCfg->intgAlgo;
   cmMemcpy((U8*)kdfInfo->u.kEnbInf.secKey, (U8*)secCfg->kENB, WR_KENB_KEY_LEN);

   /* Update keNB configuration only                                      */
   if (wrIfmPdcpKdfReq(kdfInfo, transId) != ROK)
   {
      RLOG0(L_ERROR, "wrIfmPdcpKdfReq failed");
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/**
 * @brief 
 *    This function is used to get KeNB Star Value.
 *
 * @details
 *    Function: wrUmmX2HoGetKeNBStar
 *
 *    Processing steps:
 *       - Send kEnb * key generation request to KDF.
 *       
 * @param[in]
 *    transCb      : transaction control block
 * @return S16
 *    -#Success : ROK
 *    -#Failure : RFAILED
 */
PUBLIC S16 wrPlatX2HoGetKeNBStar
(
WrUmmTransCb                 *transCb
)
{
   WrUmmX2SrcHoTrans         *x2SrcHoTrans = &(transCb->u.x2SrcHoTrans);
#ifdef TENB_AS_SECURITY
   CpjKdfReqInfo             *kdfInfo;
   WrUeSecCfg                *secCfg;

   RLOG2(L_DEBUG, "Generate kEnb * for Target PCI [%d] and EARFCN [%ld]",
      x2SrcHoTrans->targetPci, x2SrcHoTrans->targetEarfcnDl);

   WR_ALLOC(&kdfInfo, sizeof(CpjKdfReqInfo));
   if (kdfInfo == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed.");
      RETVALUE(RFAILED);
   }

   secCfg = transCb->ueCb->secCfg;
   kdfInfo->keyDerType = CTF_KDF_TYPE2;
   kdfInfo->u.kEnbStarInf.dlCarrFreq = x2SrcHoTrans->targetEarfcnDl;
   kdfInfo->u.kEnbStarInf.physCellId = x2SrcHoTrans->targetPci;
   cmMemcpy((U8*)kdfInfo->u.kEnbStarInf.secKey, secCfg->kENB, WR_KENB_KEY_LEN);

   if (wrIfmPdcpKdfReq(kdfInfo, transCb->transId) != ROK)
   {
      RLOG0(L_ERROR, "wrIfmPdcpKdfReq failed");
      RETVALUE(RFAILED);
   }
#else
   U16 i;
   for(i = 0; i < WR_KENB_KEY_LEN; i++)
      x2SrcHoTrans->kEnbStar[i] = 0xff;
#endif

   RETVALUE(ROK);
}
#endif
/***********************************************************************
                    CTF related functions
************************************************************************/
/** @brief This function fills vendor specific parameters related to cell 
 *         configuration for PHY layer. 
 *
 * @details This function prepares and fills vendor specific parameters 
 *          related to cell configuration for PHY layer.
 *
 *     Function: wrFillCtfVndrCellCfg
 *
 *         Processing steps:
 *         - Fill the vendor specific PHY related configuration parameters.
 *
 * @param[in] cellCb: Cell control block.  
 * @param[in, out] cellCfgReq: Cell configuration.  
 * @return S16 
 *        -# Success : ROK
 *        -# Failure : RFAILED. 
 */
PUBLIC S16 wrFillCtfVndrCellCfg 
(
WrCellCb          *cellCb,
CtfCfgReqInfo     *cellCfgReq
)
{
   WrMsCellCfgReq    *msCellCfgReq;
   
#ifdef CTF_VER3
   WR_ALLOC(&cellCfgReq->vendorParams.paramBuffer, sizeof(WrMsCellCfgReq));
   if(cellCfgReq->vendorParams.paramBuffer == NULLP)
   {
      RLOG0(L_FATAL, "Memory allocation failed. paramBuffer is NULL");
      RETVALUE(RFAILED);
   } /* end of if statement */

   msCellCfgReq = (WrMsCellCfgReq *)cellCfgReq->vendorParams.paramBuffer;
   /*changed from sizeof(msCellCfgReq) to
    * sizeof(WrMsCellCfgReq) */
   cellCfgReq->vendorParams.buffLen = sizeof(WrMsCellCfgReq);
   msCellCfgReq->opMode  = cellCb->ctfCfg.dfltOpMode;/*chethan*/
   msCellCfgReq->counter = 0;
   msCellCfgReq->period  = cellCb->ctfCfg.dfltTagPeriod;/*chethan*/

#ifdef ENABLE_CNM
   msCellCfgReq->isCnmEnabled  =  wrEmmCb.isCnmEnabled;
#endif

   RLOG2(L_ALWAYS, "OP MODE : %d  PERIOD :%ld",msCellCfgReq->opMode,
      msCellCfgReq->period);

#endif
   RETVALUE(ROK);
} /* end of wrFillCtfVndrCellCfg */

/** @brief This function is used check CPU utilization and
 * Update the the action to be taken 
 *
 *
 * @details
 *
 *     Function: wrChkCpuLoadAndUpdInstr
 *
 *         Processing steps:
 *
 * @param[in]  instruction Pointer to insctrution to be updated 
 * @return
 *   ROK     : Success
 *   RFAILED : Failure
 */
PUBLIC S16 wrChkCpuLoadAndUpdInstr(U8 *instruction, CmLteCellId cellId)
{
   FILE          *mipsFd = NULLP;
   S8             mipsStr[WR_MIPS_STRING_LEN];
   S8             *strPart;
   U32            freeCpuCore0;
   U32            freeCpuCore1 = 0;
   U32            avgFreeCpu;
   PRIVATE Bool   isTpCpuCntrlStarted= FALSE;
   WrCellCb      *cellCb = NULLP;
   U8             dlNumUePerTti;
   U8             maxUePerTtiCpuOlTrig;
   PRIVATE U8     upperThresh;
   PRIVATE U8     lowerThresh;
   PRIVATE U8     numUePerTtiInstrTrigCnt = 0;


   /* Initialize instruction to zero */
   *instruction = 0;

   WR_EMM_GET_CELLCB(cellCb, cellId);
   if(cellCb == NULLP)
   {
      RLOG1(L_ERROR, "Error in getting WR CELL CB for cellId = %lu",
            (U32)cellId);
      RETVALUE(RFAILED);
   }

   /* CPU OL is disabled if avgFreeCpuRqd configured as  0 */ 
   /* As of now CPU OL is enabled only of numUePerTti > 2 */
   dlNumUePerTti = cellCb->schdCfg.genCfg.maxDlUeNewTxPerTti;
   if ( (0 == wrEmmCb.avgFreeCpuRqd) || ( dlNumUePerTti < 2))
   {
      RETVALUE(ROK);
   }

   /* Calculate the thresholds based on freeCPUrequired first time */
   if ( 0 == upperThresh )
   {
      if ( wrEmmCb.avgFreeCpuRqd <= 2 )
      {
         lowerThresh = 1; 
      }
      else
      {
         lowerThresh = wrEmmCb.avgFreeCpuRqd - 2; 
      }
      upperThresh = wrEmmCb.avgFreeCpuRqd + 2; 
      printf("lowerThresh = %d, upperThresh = %d, resetThresh = %d\n", lowerThresh, upperThresh, T2K_FDD_RST_THRESH);
      RLOG3(L_DEBUG, "lowerThresh[%d] upperThresh[%ld] "
            "upperThresh[%ld]", lowerThresh, upperThresh, T2K_FDD_RST_THRESH);
   }

   mipsFd = fopen(MIPS_FILE, "r");

   if(mipsFd == NULLP)
   {
      RLOG0(L_ERROR,"MIPS_FILE is not present");
      RETVALUE(RFAILED);
   }

   /* Get the free mips available value from the file */
   if(NULLP  == fgets(mipsStr, 24, mipsFd))
   {
      RLOG0(L_ERROR,"fgets failed");
      fclose(mipsFd);
      RETVALUE(RFAILED);
   }

   strtok(mipsStr, " ");

   strPart = strtok(NULLP, " ");
   if(NULLP == strPart)
   {
      RLOG0(L_ERROR,"strtok function failed");
      fclose(mipsFd);
      RETVALUE(RFAILED);
   }
   freeCpuCore0 = atoi(strPart);
   strPart = strtok(NULLP, " ");
   if(NULLP != strPart)
   {
      freeCpuCore1 = atoi(strPart);
   }
   avgFreeCpu = ( freeCpuCore0 + freeCpuCore1 ) / 2; 

   /* Get the maximum UE per TTI CPU over load instruction triggered. */
   maxUePerTtiCpuOlTrig = RGR_MAX_PERC_NUM_UE_PER_TTI_RED * (dlNumUePerTti - 1);

   if ( ( freeCpuCore0 <= T2K_FDD_CORE0_L_THRESH )||( avgFreeCpu < lowerThresh ) )
   {
      /* TODO: Add voLTE call limitation  - 
       * if number of voLTE calls are more than the MAX_LIMIT to trigger 
       * CPU OL with num UE per TTI reducction, then do not trigger it*/ 
      if ( ( maxUePerTtiCpuOlTrig != 0 ) && ( numUePerTtiInstrTrigCnt < maxUePerTtiCpuOlTrig ))
      {
         numUePerTtiInstrTrigCnt++;
         *instruction = RGR_CPU_OVRLD_DL_DEC_NUM_UE_PER_TTI | RGR_CPU_OVRLD_UL_DEC_NUM_UE_PER_TTI;
         RLOG0(L_DEBUG,"Trigger Decremenet num UE");
         printf("Trig_Dec_Num_Ue\n"); 
      }
      else if ( avgFreeCpu < lowerThresh )
      {
         printf("Trig_Dec_TP\n"); 
         RLOG0(L_DEBUG,"Trigger Decremenet TP");
         *instruction = RGR_CPU_OVRLD_DL_TPT_DOWN | RGR_CPU_OVRLD_UL_TPT_DOWN;
         isTpCpuCntrlStarted = TRUE;
      }
   }
   /* If the enough CPU is available then no need to be 
    * in CPU OL state, hence reset the the CPU OL */
   else if ( ( avgFreeCpu > T2K_FDD_RST_THRESH ) && 
         ((TRUE == isTpCpuCntrlStarted) || (numUePerTtiInstrTrigCnt != 0)))
   {
      printf("wrChkCpuLoad: avgFreeCpu > RESET_THRESH, hence resetting it \n");
      RLOG0(L_DEBUG,"Resetting CPU Ovrload control");
      *instruction = RGR_CPU_OVRLD_RESET;
      isTpCpuCntrlStarted = FALSE;
      numUePerTtiInstrTrigCnt = 0;
   }
   /* if any one of the core is at 99% then avoid increasing the TP */
   else if ( ( freeCpuCore0 >= T2K_FDD_CORE0_U_THRESH )||( avgFreeCpu > upperThresh ))
   {
      if ( ( numUePerTtiInstrTrigCnt > 0 ) && ( freeCpuCore0 >= T2K_FDD_CORE0_U_THRESH ))
      {
         printf("Trig_Inc_Num_Ue\n"); 
         RLOG0(L_DEBUG,"Trigger Increment num UE");
         *instruction = RGR_CPU_OVRLD_DL_INC_NUM_UE_PER_TTI | RGR_CPU_OVRLD_UL_INC_NUM_UE_PER_TTI;
         numUePerTtiInstrTrigCnt--;
      }
      else if ( avgFreeCpu > upperThresh )
      {
         if ( (isTpCpuCntrlStarted == TRUE) && ( freeCpuCore0 >= 1 ) && ( freeCpuCore1 >= 1))
         {
            printf("\nTrig_Inc_TP\n"); 
            RLOG0(L_DEBUG,"Trigger Increment TP");
            *instruction = RGR_CPU_OVRLD_DL_TPT_UP | RGR_CPU_OVRLD_UL_TPT_UP;
         }
      }
   }

   RLOG3(L_DEBUG, "CORE-0 FREE[%d] CORE1-FREE[%ld] "
         "Avg FREE[%d]", freeCpuCore0, freeCpuCore1,
         (freeCpuCore0 + freeCpuCore1)/2);
   printf("\n CORE 0: %ld, CORE 1: %ld, Avg CPU = %ld\n",freeCpuCore0, freeCpuCore1, (freeCpuCore0 + freeCpuCore1)/2);

   if( 0 != fclose(mipsFd))
   {
      RLOG0(L_ERROR,"fclose failed");
   }
   RETVALUE(ROK);
} /* wrChkCpuLoadAndUpdInstr */
/********************************************************************30**

           End of file:     fc_plat_intel.c@@/main/tenb_main_ccb/1 - Wed Jul 22 16:16:01 2015

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
