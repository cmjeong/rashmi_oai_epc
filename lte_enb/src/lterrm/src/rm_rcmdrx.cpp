
/********************************************************************20**

     Name:     RRM Application

     Type:     CPP source file

     Desc:     This file contains 
               

     File:     rm_rcmdrx.cpp

     Sid:      qf_rcmdrx.cpp@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:38 2013

     Prg:     jbm 

*********************************************************************21*/

static const char* RLOG_MODULE_NAME="RRM";
static int RLOG_MODULE_ID=128;
static int RLOG_FILE_ID=145;
/* header include files */
#ifndef RM_RCMDRX_CPP_
#define RM_RCMDRX_CPP_

#include "rm_cmn.h"
#include "rm_rcmdrx.h"

CRmRcmDrxMgr::CRmRcmDrxMgr(LrmCellConfigData &stCellCfg)
{
   memset(&m_stRmCellDrxCfg, 0, sizeof(CmRrmCellDrxCfg));
   m_stRmCellDrxCfg = stCellCfg.stRmCellDrxCfg;
   rmDrxONDurationTmr[0] = 1;
   rmDrxONDurationTmr[1] = 2; 
   rmDrxONDurationTmr[2] = 3;
   rmDrxONDurationTmr[3] = 4;
   rmDrxONDurationTmr[4] = 5;
   rmDrxONDurationTmr[5] = 6;
   rmDrxONDurationTmr[6] = 8;
   rmDrxONDurationTmr[7] = 10;
   rmDrxONDurationTmr[8] = 20;
   rmDrxONDurationTmr[9] = 30;
   rmDrxONDurationTmr[10] = 40;
   rmDrxONDurationTmr[11] = 50;
   rmDrxONDurationTmr[12] = 60;
   rmDrxONDurationTmr[13] = 80;
   rmDrxONDurationTmr[14] = 100;
   rmDrxONDurationTmr[15] = 200;

   rmDrxLongCycle[0] = 10;
   rmDrxLongCycle[1] = 20;
   rmDrxLongCycle[2] = 32;
   rmDrxLongCycle[3] = 40;
   rmDrxLongCycle[4] = 64;
   rmDrxLongCycle[5] = 80;
   rmDrxLongCycle[6] = 128;
   rmDrxLongCycle[7] = 160;
   rmDrxLongCycle[8] = 256;
   rmDrxLongCycle[9] = 320;
   rmDrxLongCycle[10] = 512;
   rmDrxLongCycle[11] = 640;
   rmDrxLongCycle[12] = 1024;
   rmDrxLongCycle[13] = 1280;
   rmDrxLongCycle[14] = 2048;
   rmDrxLongCycle[15] = 2560;

   rmDrxShortCycle[0] = 2;
   rmDrxShortCycle[1] = 5;
   rmDrxShortCycle[2] = 8;
   rmDrxShortCycle[3] = 10;
   rmDrxShortCycle[4] = 16;
   rmDrxShortCycle[5] = 20;
   rmDrxShortCycle[6] = 32;
   rmDrxShortCycle[7] = 40;
   rmDrxShortCycle[8] = 64;
   rmDrxShortCycle[9] = 80;
   rmDrxShortCycle[10] = 128;
   rmDrxShortCycle[11] = 160;
   rmDrxShortCycle[12] = 256;
   rmDrxShortCycle[13] = 320;
   rmDrxShortCycle[14] = 512;
   rmDrxShortCycle[15] = 640;

   /* Here we Initialize the Onduration based on the number of DL subframe
    * required for accomodating the UL subframes for CQI and RI
    *
    * Below we are assigning the number of DL subbframes for Onduration
    * The corresponding Inde will be derived later
    */

   m_usTddOnDuration = 0;
   m_enUlDlConfig = stCellCfg.enUlDlConfig;
}


   
void CRmRcmDrxMgr::rmRcmDrxPopulateOnduration()
{
   switch(m_enUlDlConfig)
   {
      case LRM_UL_DL_CONFIG_0:
      m_usTddOnDuration = 4;
      break;
      case LRM_UL_DL_CONFIG_1:
      m_usTddOnDuration = 9;
      break;
      case LRM_UL_DL_CONFIG_2:
      m_usTddOnDuration = 8;
      break;
      case LRM_UL_DL_CONFIG_3:
      m_usTddOnDuration = 8;
      break;
      case LRM_UL_DL_CONFIG_4:
      m_usTddOnDuration = 8;
      break;
      case LRM_UL_DL_CONFIG_5:
      m_usTddOnDuration = 10;
      break;
      case LRM_UL_DL_CONFIG_6:
      m_usTddOnDuration = 4;
      break;
      default:
         RLOG0(L_WARNING,"Invalid UL-DL config, settign Onduration"
                             "for UL-DL config 1");
         m_usTddOnDuration = 9;
   }

   
}

CRmRcmDrxMgr::~CRmRcmDrxMgr()
{
   //Do Nothing 
   return;
}

S32 CRmRcmDrxMgr::rmRcmCfgDrx(CUEContext  *pobjUe, U32  bResCfgMask)
{
   U8              bERABMaxQciPriority = pobjUe->getHighestQciPriorityOfUe();
   CmRrmDrxCfg     stRmDrxCfg;
   U8              bResAllocated = pobjUe->getUeRadioDedResAllocBitMap();
   U16             usLongDrxCycle;
   U16             usOnDurationTmr;
   U16             usRiOffset = pobjUe->getUeRiOffset();
   U16             usLongDrxCycleOffset;

   /* QCI 5 is also considered in DRX GBR profile */
   if(bERABMaxQciPriority >= 1 && bERABMaxQciPriority <= 5)
   {
      usLongDrxCycle = rmDrxLongCycle[m_stRmCellDrxCfg.usLongDrxCycleGbr];
   }   
   else
   {
      usLongDrxCycle = rmDrxLongCycle[m_stRmCellDrxCfg.usLongDrxCycleNonGbr];
   }   

   if(bResAllocated & RM_RCM_UE_RADIO_RES_CQI_BITMAP_VAL)
   {
      /* Checking the minimum value between current Long Cycle value and CQI 
       * Periodicity. The minimum value will be used as Long Cycle value 
       * */
      if(usLongDrxCycle > RM_DFLT_CQI_PRD)
      {
         usLongDrxCycle = RM_DFLT_CQI_PRD;
      }   

      /* Bearer Reconfiguration case: If new calculated Long Cycle value
       * does not match the old configured value, the DRX profile is reconfigured
       * else old cofiguration is retained  */
      if(bResAllocated & RM_RCM_UE_RADIO_RES_DRX_BITMAP_VAL)
      {
         if(usLongDrxCycle == rmDrxLongCycle[pobjUe->getDrxLongCycle()])
         {
            return RM_RCM_DRX_PRES;
         }   
      }

      /* checking if long cycle value is less than the 
       * minimum possible Long Cycle value. If so, DRX
       * is released if setup earlier or it is not setup.
       * */
      if(usLongDrxCycle < RM_DRX_LONG_CYCLE_MIN)
      {
         RLOG_ARG1(L_WARNING, DBG_CRNTI, (pobjUe->getCRNTI()),"Long Cycle (%u) could not be configured",usLongDrxCycle);
         if(bResAllocated & RM_RCM_UE_RADIO_RES_DRX_BITMAP_VAL)
         {
            pobjUe->relDrxCfg();
            return RM_RCM_DRX_ROK;
         }
         else
         {
            return RM_RCM_DRX_RFAILED;
         }   
      }   
      else
      {
         stRmDrxCfg.stDrxLongCycleOffst.usLongDrxCycle = (U16) rmRcmGetDrxLongCycleIdx(usLongDrxCycle);
         stRmDrxCfg.usDrxInactvTmr = m_stRmCellDrxCfg.usDrxInactvTmr;
         stRmDrxCfg.bDrxRetxTmr = m_stRmCellDrxCfg.bDrxRetxTmr;
         stRmDrxCfg.bIsDrxEnabled = TRUE;
      }   
   }
   else
   {
     /* TODO */
   }

   /* Calculate the On Duration Timer */
   if((rmRcmDrxGetOnDuration(usLongDrxCycle, stRmDrxCfg, pobjUe, usOnDurationTmr)) != ROK)
   {
       RLOG_ARG0(L_WARNING, DBG_CRNTI, (pobjUe->getCRNTI()),
						"On Duration Timer could not be configured\n");
      if(bResAllocated & RM_RCM_UE_RADIO_RES_DRX_BITMAP_VAL)
      {
         pobjUe->relDrxCfg();
         return RM_RCM_DRX_ROK;
      }
      else
      {
         return RM_RCM_DRX_RFAILED;
      }   
   }   

   usLongDrxCycleOffset = rmRcmGetDrxOffset(usLongDrxCycle, usRiOffset, bResAllocated, usOnDurationTmr);
   stRmDrxCfg.stDrxLongCycleOffst.usDrxStartOffst = usLongDrxCycleOffset;

   if(bResCfgMask & RM_RCM_RES_CFG_DRX_WITH_SHORT)
   {
      /* Calculate the Short Cycle value */
      if((rmRcmDrxGetShortCycle(usLongDrxCycle, usOnDurationTmr, stRmDrxCfg)) != ROK)
      {
         RLOG_ARG0(L_WARNING, DBG_CRNTI, (pobjUe->getCRNTI()),
								"Short Cycle could not be configured\n");
         stRmDrxCfg.stDrxShortDrx.bPres = FALSE;
      }   
   }
   else
   {
      stRmDrxCfg.stDrxShortDrx.bPres = FALSE;
   }   

   RLOG_ARG0(L_DEBUG, DBG_CRNTI, (pobjUe->getCRNTI()),
         "setting the DRX Profile");
   pobjUe->setDrxCfg(stRmDrxCfg);
   return RM_RCM_DRX_ROK;
}
S32 CRmRcmDrxMgr::rmRcmRelDrx(CUEContext         *pobjUe)
{
   CmRrmDrxCfg stRmDrxCfg;

   stRmDrxCfg.bIsDrxEnabled = FALSE;

   pobjUe->setDrxCfg(stRmDrxCfg);

   return ROK;
}

U16 CRmRcmDrxMgr::rmRcmGetDrxOffset(U16 usDrxLongCycle, U16 usRiOffset, U8 bResAllocated, U16 usOnDurationTmr)
{
   U16   usDrxOffset = 0;   
   U16   nOffsetCqi;
   
   /* The nOffsetCqi is set with the minimum offset of RI and CQI. Since RI will
    * always be minium of CQI, the RI offset is set as CQI offset for
    * calculating the DRX-Offset 
    */
   nOffsetCqi = usRiOffset;
   
   /* Making The DRX Offset in aliagnment with the Periodic RI offset, 
    * instead of the CQI offset. That is because the RI reporting ocassion
    * will always occur ahead of Periodic CQI ocassion. 
    * DRX Offset = (NoffsetCqi - NoffsetRi)
    * For NoffsetCqi, NoffsetRi refer 36.213 sec 7.2.2 */
   
   if(bResAllocated & RM_RCM_UE_RADIO_RES_CQI_BITMAP_VAL)
   {
      /* Shifting the DRX offset to 2 subframe before the CQI 
       * reporting time, if On Duration is greater than 2 */
      if(usOnDurationTmr > 2)
      {
           usDrxOffset = (nOffsetCqi - 1 + usDrxLongCycle) % usDrxLongCycle;
      }
      else
      {
            usDrxOffset = nOffsetCqi % usDrxLongCycle;
      }   
   }   
   else                     
   {                      
      /* TODO */
   }     

   return usDrxOffset;
}   

U8 CRmRcmDrxMgr::rmRcmGetDrxLongCycleIdx(U16 usDrxLongCycle)
{
   U8 idx;

   for(idx = 0; idx < 16; idx++)
   {
      if(usDrxLongCycle == rmDrxLongCycle[idx])
      {
         break;
      }   
   }   
   return idx; 
}   

U16 CRmRcmDrxMgr::rmRcmDrxGetOnDuration(U16 usDrxLongCycle, CmRrmDrxCfg& stRmDrxCfg, CUEContext *pobjUe, U16& usOnDurationTmr)
{
   U8                          bIdx;
   RmuRiConfigIndex            riConfigIndex;

   riConfigIndex = pobjUe->getUeCqiRiIdx();

#ifndef LTE_TDD

   if(riConfigIndex.bPres == TRUE)
   {   
      U16                         bCqiRiGap;

      /* Adding one to the gap of CQI RI Idx to derive the no. of 
       * subframes for CQI, RI reporting */
      bCqiRiGap = (riConfigIndex.usRiConfigIndex - RM_START_RI_IDX) + 1;
#ifndef LTE_ADV
      usOnDurationTmr = (bCqiRiGap < usDrxLongCycle/RM_DRX_ON_DUR_PERCENT)
                          ?(usDrxLongCycle/RM_DRX_ON_DUR_PERCENT):bCqiRiGap;
#else
      if((bCqiRiGap * RM_MAX_CELL_SUPPORTED) > 
            (usDrxLongCycle/RM_DRX_ON_DUR_PERCENT))
      {
         usOnDurationTmr = bCqiRiGap * RM_MAX_CELL_SUPPORTED;
      }  
      else
      {
         usOnDurationTmr = usDrxLongCycle/RM_DRX_ON_DUR_PERCENT;
      }   
#endif
   }   
   else
   {
      usOnDurationTmr = usDrxLongCycle/RM_DRX_ON_DUR_PERCENT;
#ifdef LTE_ADV
      if(usOnDurationTmr < 
            RM_RCM_CQI_PMI_IDX_FACTOR_PER_CELL * RM_MAX_CELL_SUPPORTED)
      {
          usOnDurationTmr =
             RM_RCM_CQI_PMI_IDX_FACTOR_PER_CELL * RM_MAX_CELL_SUPPORTED;
      }   
#endif
   }   
#else
   usOnDurationTmr = m_usTddOnDuration;
#endif
   
   /* Matching to the next possible On Duration timer value */
   for (bIdx = 0; bIdx < 16; bIdx++)
   {
      if(rmDrxONDurationTmr[bIdx] >= usOnDurationTmr)
      {
         usOnDurationTmr = rmDrxONDurationTmr[bIdx];
         break;
      }   
   } 
   
   if(usOnDurationTmr >= usDrxLongCycle)
   {
      RLOG_ARG0(L_ERROR, DBG_CRNTI, (pobjUe->getCRNTI()),
                    "Onduration can not be more than DRX Long Cycle");
      return RFAILED; 
   }   
   else
   {
      stRmDrxCfg.bDrxOnDurTmr = bIdx;
      return ROK;
   }   
}   

S16 CRmRcmDrxMgr::rmRcmDrxGetShortCycle(U16 usDrxLongCycle, U16 usOnDurationTmr, CmRrmDrxCfg& stRmDrxCfg)
{
    U16   usShortCycle;
    U8    idx; 

    for(idx = 0; idx < 16; idx++)
    {
       usShortCycle = rmDrxShortCycle[idx];

       if((usShortCycle > usOnDurationTmr) && (usShortCycle < usDrxLongCycle) &&
          (!(usDrxLongCycle % usShortCycle)))
       {
          /* Trying to keep sleep time in short cycle value as greater than 
           * or equals to On Duration timer */
          if((usShortCycle - usOnDurationTmr) >= usOnDurationTmr)
          {   
             /* Passing the Index of short Cycle Value */
             stRmDrxCfg.stDrxShortDrx.usShortDrxCycle   = idx; 
             stRmDrxCfg.stDrxShortDrx.bDrxShortCycleTmr = usDrxLongCycle/usShortCycle;
             stRmDrxCfg.stDrxShortDrx.bPres             = TRUE;
             return ROK;
          }
          else
          {
            continue;
          }   
       }   
    }   
    return RFAILED;
}   
#endif /* RM_RCMDRX_CPP_ */
/********************************************************************30**

           End of file:     qf_rcmdrx.cpp@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/T2K_MergeTemp_BR/1 - Mon Sep  2 16:45:38 2013

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
