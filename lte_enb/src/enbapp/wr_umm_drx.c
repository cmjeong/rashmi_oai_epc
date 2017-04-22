

/********************************************************************20**

     Name:     EnodeB Application

     Type:     C source file

     Desc:     This file contains 
               

     File:     wr_umm_drx.c

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
/* header include files (.h) */
static const char* RLOG_MODULE_NAME="UMM";

static int RLOG_FILE_ID=56;

static int RLOG_MODULE_ID=32;

#include<stdio.h>
/*Removed DRX  flag*/

#include "wr.h"
#include "wr_umm.h"
#include "wr_smm_smallcell.h"
#include "wr_umm_drx.h"
#include "wr_utils.h"

PRIVATE S16 wrUmmRrcFillDrxLongCycleOffset(NhuDRX_Config *drxCfg, U16 longCycle, U16 startOffVal);

PRIVATE S16 wrDrxONDurationTmr[] = {
RGR_DRX_PRD_1PSF,
RGR_DRX_PRD_2PSF,
RGR_DRX_PRD_3PSF,
RGR_DRX_PRD_4PSF,
RGR_DRX_PRD_5PSF,
RGR_DRX_PRD_6PSF,
RGR_DRX_PRD_8PSF,
RGR_DRX_PRD_10PSF,
RGR_DRX_PRD_20PSF,
RGR_DRX_PRD_30PSF,
RGR_DRX_PRD_40PSF,
RGR_DRX_PRD_50PSF,
RGR_DRX_PRD_60PSF,
RGR_DRX_PRD_80PSF,
RGR_DRX_PRD_100PSF,
RGR_DRX_PRD_200PSF
};

PRIVATE S16 wrDrxInactvTmr[] = {
RGR_DRX_PRD_1PSF,
RGR_DRX_PRD_2PSF,
RGR_DRX_PRD_3PSF,
RGR_DRX_PRD_4PSF,
RGR_DRX_PRD_5PSF,
RGR_DRX_PRD_6PSF,
RGR_DRX_PRD_8PSF,
RGR_DRX_PRD_10PSF,
RGR_DRX_PRD_20PSF,
RGR_DRX_PRD_30PSF,
RGR_DRX_PRD_40PSF,
RGR_DRX_PRD_50PSF,
RGR_DRX_PRD_60PSF,
RGR_DRX_PRD_80PSF,
RGR_DRX_PRD_100PSF,
RGR_DRX_PRD_200PSF,
RGR_DRX_PRD_300PSF,
RGR_DRX_PRD_500PSF,
RGR_DRX_PRD_750PSF,
RGR_DRX_PRD_1280PSF,
RGR_DRX_PRD_1920PSF,
RGR_DRX_PRD_2560PSF
};

PRIVATE S16 wrDrxReTxTmr[] = {
RGR_DRX_PRD_1PSF,
RGR_DRX_PRD_2PSF,
RGR_DRX_PRD_4PSF,
RGR_DRX_PRD_6PSF,
RGR_DRX_PRD_8PSF,
RGR_DRX_PRD_16PSF,
RGR_DRX_PRD_24PSF,
RGR_DRX_PRD_33PSF   
};

PUBLIC S16 wrDrxLongCycle[] = {
RGR_DRX_PRD_10SF,
RGR_DRX_PRD_20SF,
RGR_DRX_PRD_32SF,
RGR_DRX_PRD_40SF,
RGR_DRX_PRD_64SF,
RGR_DRX_PRD_80SF,
RGR_DRX_PRD_128SF,
RGR_DRX_PRD_160SF,
RGR_DRX_PRD_256SF,
RGR_DRX_PRD_320SF,
RGR_DRX_PRD_512SF,
RGR_DRX_PRD_640SF,
RGR_DRX_PRD_1024SF,
RGR_DRX_PRD_1280SF,
RGR_DRX_PRD_2048SF,
RGR_DRX_PRD_2560SF
};

PRIVATE S16 wrDrxShortCycle[] = {
RGR_DRX_PRD_2SF,
RGR_DRX_PRD_5SF,
RGR_DRX_PRD_8SF,
RGR_DRX_PRD_10SF,
RGR_DRX_PRD_16SF,
RGR_DRX_PRD_20SF,
RGR_DRX_PRD_32SF,
RGR_DRX_PRD_40SF,
RGR_DRX_PRD_64SF,
RGR_DRX_PRD_80SF,
RGR_DRX_PRD_128SF,
RGR_DRX_PRD_160SF,
RGR_DRX_PRD_256SF,
RGR_DRX_PRD_320SF,
RGR_DRX_PRD_512SF,
RGR_DRX_PRD_640SF
};
   
/**
 *  @brief This function is used to fill the long DRX Cycle and  
 *  offset in DRX Config IE in the RRC Message
 *         
 *      Function: wrUmmRrcFillDrxLongCycleOffset  
 U
 *          Processing steps:
 *          - Fill long cycle Offset value
 *
 *
 *  @param [in/out] : DRX Long Cycle value, Offset Value
 *  @return S16
 */
PRIVATE S16 wrUmmRrcFillDrxLongCycleOffset
(
NhuDRX_Config    *drxCfg, 
U16  longCycle, 
U16  startOffVal       
)
{
   switch(wrDrxLongCycle[longCycle])
   {
      case RGR_DRX_PRD_10SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf10, startOffVal);
            break;   
      case RGR_DRX_PRD_20SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf20, startOffVal);
            break;   
      case RGR_DRX_PRD_32SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf32, startOffVal);
            break;   
      case RGR_DRX_PRD_40SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf40, startOffVal);
            break;   
      case RGR_DRX_PRD_64SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf64, startOffVal);
            break;   
      case RGR_DRX_PRD_80SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf80, startOffVal);
            break;   
      case RGR_DRX_PRD_128SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf128, startOffVal);
            break;   
      case RGR_DRX_PRD_160SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf160, startOffVal);
            break;   
      case RGR_DRX_PRD_256SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf256, startOffVal);
            break;   
      case RGR_DRX_PRD_320SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf320, startOffVal);
            break;   
      case RGR_DRX_PRD_512SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf512, startOffVal);
            break;   
      case RGR_DRX_PRD_640SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf640, startOffVal);
            break;   
      case RGR_DRX_PRD_1024SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf1024, startOffVal);
            break;   
      case RGR_DRX_PRD_1280SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf1280, startOffVal);
            break;   
      case RGR_DRX_PRD_2048SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf2048, startOffVal);
            break;   
      case RGR_DRX_PRD_2560SF:
         wrFillTknU32(&drxCfg->val.setup.longDRX_CycleStartOffset.val.sf2560, startOffVal);
            break;   
      default:
         {
            RETVALUE(RFAILED);
         }
   }
   RETVALUE(ROK);
}

/**
 *  @brief This function is used to fill the DRX Config IE in the
 *         RRC Message
 *
 *      Function: wrUmmRrcFillDrxCfgIe
 *
 *          Processing steps:
 *          - Fill the IE elements
 *
 *
 *  @param [in/out] drxCfg : DRX Config IE
 *  @return S16
 */
PUBLIC S16 wrUmmRrcFillDrxCfgIe
(
NhuDRX_Config      *drxCfgIe,
WrDrxCfg           *drxCfg 
)
{
   if (drxCfg->isDrxEnabled == TRUE)
   {
      wrFillTknU8(&drxCfgIe->choice, 1);
      wrFillTknU8(&drxCfgIe->val.setup.pres, drxCfg->isDrxEnabled);
      wrFillTknU32(&drxCfgIe->val.setup.onDurationTimer, drxCfg->drxOnDurTmr);
      wrFillTknU32(&drxCfgIe->val.setup.drx_InactivityTimer, drxCfg->drxInactvTmr);
      wrFillTknU32(&drxCfgIe->val.setup.drx_ReTxTimer, drxCfg->drxRetxTmr);
      wrFillTknU8(&drxCfgIe->val.setup.longDRX_CycleStartOffset.choice, 
                                   drxCfg->drxLongCycleOffst.longDrxCycle);
      wrUmmRrcFillDrxLongCycleOffset(drxCfgIe, drxCfg->drxLongCycleOffst.longDrxCycle, 
                                  drxCfg->drxLongCycleOffst.drxStartOffst);
      if(drxCfg->drxShortDrx.pres == TRUE)
      {   
         wrFillTknU8(&drxCfgIe->val.setup.shortDRX.pres, drxCfg->drxShortDrx.pres);
         wrFillTknU32(&drxCfgIe->val.setup.shortDRX.drxShortCycleTimer, 
                                     drxCfg->drxShortDrx.drxShortCycleTmr);
         wrFillTknU32(&drxCfgIe->val.setup.shortDRX.shortDRX_Cycle, 
                                     drxCfg->drxShortDrx.shortDrxCycle);
      }

      /*127802*/
      RLOG0(L_INFO, "Filled DRX config in RRC ReCfg message");
   }
   else
   {
      /*127802*/
      RLOG0(L_INFO, "Releasing the DRX");
      wrFillTknU8(&drxCfgIe->choice, 0);
   }   

   RETVALUE(ROK);
}

/**
 *  @brief This function is used to fill the DRX Configuration in the
 *         scheduler configursation request
 *
 *      Function: wrUmmSchdFillUeDrxCfgInfo
 *
 *          Processing steps:
 *          - Fill the DRX Configuration in reconfiguration structure
 *
 *
 *  @param [in/out]  : RgrUeReCfg structure
 *  @return S16
 */
PUBLIC S16 wrUmmSchdFillUeDrxCfgInfo
(
RgrUeRecfg         *ueRecfg,
WrDrxCfg           *drxCfg 
)
{
   if (drxCfg->isDrxEnabled == TRUE)
   {
      /* Filling parameters related to DRX configuration */
      ueRecfg->ueRecfgTypes            |= RGR_UE_DRX_RECFG;
      ueRecfg->ueDrxRecfg.isDrxEnabled = drxCfg->isDrxEnabled;
      ueRecfg->ueDrxRecfg.drxOnDurTmr  = wrDrxONDurationTmr[drxCfg->drxOnDurTmr];
      ueRecfg->ueDrxRecfg.drxInactvTmr = wrDrxInactvTmr[drxCfg->drxInactvTmr];
      ueRecfg->ueDrxRecfg.drxRetxTmr   = wrDrxReTxTmr[drxCfg->drxRetxTmr];
      ueRecfg->ueDrxRecfg.drxLongCycleOffst.longDrxCycle = 
                          wrDrxLongCycle[drxCfg->drxLongCycleOffst.longDrxCycle];
      ueRecfg->ueDrxRecfg.drxLongCycleOffst.drxStartOffst = 
                                         drxCfg->drxLongCycleOffst.drxStartOffst;
      if(drxCfg->drxShortDrx.pres == TRUE)
      {   
         ueRecfg->ueDrxRecfg.drxShortDrx.pres           = TRUE;
         ueRecfg->ueDrxRecfg.drxShortDrx.shortDrxCycle  = 
                                 wrDrxShortCycle[drxCfg->drxShortDrx.shortDrxCycle];
         ueRecfg->ueDrxRecfg.drxShortDrx.drxShortCycleTmr = 
                                               drxCfg->drxShortDrx.drxShortCycleTmr;
      }
      else
      {
         ueRecfg->ueDrxRecfg.drxShortDrx.pres = FALSE;
      }   
      RLOG0(L_INFO, "Filled DRX config in SCH ReCfg message");
   }
   else
   {
     ueRecfg->ueRecfgTypes            |= RGR_UE_DRX_RECFG; 
     ueRecfg->ueDrxRecfg.isDrxEnabled = FALSE;
     RLOG0(L_INFO, "Disabling the DRX in SCH");
   }   
   RETVALUE(ROK);
}

/**
 *  @brief This function is used to fill the DRX Configuration in the
 *         scheduler configursation request
 *
 *      Function: wrUmmHoSchdFillUeDrxCfgInfo
 *
 *          Processing steps:
 *          - Fill the DRX Configuration in reconfiguration structure
 *
 *
 *  @param [in/out]  : RgrUeCfg structure
 *  @return S16
 */
PUBLIC S16 wrUmmHoSchdFillUeDrxCfgInfo
(
RgrUeCfg         *ueCfg,
WrDrxCfg         *drxCfg 
)
{
   if (drxCfg->isDrxEnabled == TRUE)
   {
      /* Filling parameters related to DRX configuration */
      ueCfg->ueDrxCfg.isDrxEnabled = drxCfg->isDrxEnabled;
      ueCfg->ueDrxCfg.drxOnDurTmr  = wrDrxONDurationTmr[drxCfg->drxOnDurTmr];
      ueCfg->ueDrxCfg.drxInactvTmr = wrDrxInactvTmr[drxCfg->drxInactvTmr];
      ueCfg->ueDrxCfg.drxRetxTmr   = wrDrxReTxTmr[drxCfg->drxRetxTmr];
      ueCfg->ueDrxCfg.drxLongCycleOffst.longDrxCycle = 
                          wrDrxLongCycle[drxCfg->drxLongCycleOffst.longDrxCycle];
      ueCfg->ueDrxCfg.drxLongCycleOffst.drxStartOffst = 
                                         drxCfg->drxLongCycleOffst.drxStartOffst;
      ueCfg->ueDrxCfg.drxShortDrx.pres           = drxCfg->drxShortDrx.pres;
      ueCfg->ueDrxCfg.drxShortDrx.shortDrxCycle  = 
                              wrDrxShortCycle[drxCfg->drxShortDrx.shortDrxCycle];
      ueCfg->ueDrxCfg.drxShortDrx.drxShortCycleTmr = 
                                            drxCfg->drxShortDrx.drxShortCycleTmr;
      RLOG0(L_INFO, "Filled DRX config in SCH ReCfg message for Handover");
   }
   else
   {
     ueCfg->ueDrxCfg.isDrxEnabled = FALSE;
     RLOG0(L_INFO, "Disabling the DRX in SCH for Handover");
   }   
   RETVALUE(ROK);
}
/*Removed DRX  flag*/

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
