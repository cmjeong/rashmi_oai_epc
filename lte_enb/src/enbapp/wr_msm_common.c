
/********************************************************************20**

Name:     EnodeB Application

Type:     C include file

Desc:     This file contains 


File:     wr_msm_interface.c

Sid:      $SID$ 

Prg:      Sriky 

 *********************************************************************21*/

#include "wr.h"
#include "wr_smm_init.h"
#include "wr_msm_common.h"

EXTERN MsmLteeNodeBparams lteeNodeBparams[MSM_MAX_CELLS];
PUBLIC MsmWcdmaNodeBparams wcdmaNodeBparams;
PUBLIC MsmFaultMgmtParams faultMgmtParams;
PUBLIC MsmFapParameters    fapParameters;

/** @brief This function is used for setting prach cfg  parameters
 *
 * @details
 *
 *     Function: msmSetPrachConfigCommonParameters
 *
 *         Processing steps:
 *
 * @param[in] ltePrachCfgCommon
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPrachConfigCommonParameters
(
 const MsmLtePrachCfgCommon *ltePrachCfgCommon,
 U16 cellIdx
 )
{
   if(ltePrachCfgCommon == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].ltePrachCfgCommon = *ltePrachCfgCommon;
   RETVALUE(ROK);
}

PUBLIC S16 msmSetFreqSyncParameters
(
 const MsmLteFreqSyncParams *lteFreqSyncParams,
 U16 cellIdx
 )
{
   if(lteFreqSyncParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteFreqSyncParams = *lteFreqSyncParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting RIM parameters
 * *
 * * @details
 * *
 * *     Function: msmSetRimParameters
 * *
 * *         Processing steps:
 * *
 * * @param[in] lteRimParams
 * * @return S16
 * *        -# Success : ROK
 * *        -# Failure : RFAILED
 * */
PUBLIC S16 msmSetRimParameters(const MsmLteRimParams* lteRimParams, U16 cellIdx)
{
   if(lteRimParams == NULLP)
   {
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteRimParams = *lteRimParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting eNodeb IP  parameters
 *
 * @details
 *
 *     Function:msmSetEnodebIpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteeNodeBIPparams 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetEnodebIpParameters
(
 const MsmLteeNodeBIPparams *lteeNodeBIPparams
 )
{
   if(lteeNodeBIPparams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   fapParameters.lteeNodeBIPparams = *lteeNodeBIPparams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting RACH cfg parameters
 *
 * @details
 *
 *     Function: msmSetRachConfigCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRachCfgCommonParams 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetRachConfigCommonParameters
(
 const MsmLteRachCfgCommonParams *lteRachCfgCommonParams,
 U16 cellIdx
 )
{
   if(lteRachCfgCommonParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteRachCfgCommonParams = *lteRachCfgCommonParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting PdschCfg parameters
 *
 * @details
 *
 *     Function:msmSetPdschConfigCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePdschCfgCommon 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPdschConfigCommonParameters
(
 const MsmLtePdschCfgCommon *ltePdschCfgCommon,
 U16 cellIdx
 )
{
   if(ltePdschCfgCommon == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].ltePdschCfgCommon = *ltePdschCfgCommon;
   RETVALUE(ROK);
}

/** @brief This function is used for setting ULPwrCtrl parameters
 *
 * @details
 *
 *     Function: msmSetUlPowerControlCommonParameters
 *
 *         Processing steps:
 *
 * @param[in] lteULPwrCtrlCommon
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetUlPowerControlCommonParameters
(
 const MsmLteULPwrCtrlCommon *lteULPwrCtrlCommon,
 U16 cellIdx
 )
{ 
   if(lteULPwrCtrlCommon == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].lteULPwrCtrlCommon = *lteULPwrCtrlCommon;
   RETVALUE(ROK);
}

/** @brief This function is used for setting ULFrequencyInfo parameters
 *
 * @details
 *
 *     Function:msmSetUlFrequencyInfoParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteULFrequencyInfo
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetUlFrequencyInfoParameters
(
 const MsmLteULFrequencyInfo *lteULFrequencyInfo,
 U16 cellIdx
 )
{
   if(lteULFrequencyInfo == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteULFrequencyInfo = *lteULFrequencyInfo;
   RETVALUE(ROK);
}

/** @brief This function is used for setting lteCellSib3CfgGrp parameters
 *
 * @details
 *
 *     Function:msmSetCell_Sib3ConfigGroupParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCellSib3CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCell_Sib3ConfigGroupParameters
(
 const MsmLteCellSib3CfgGrp *lteCellSib3CfgGrp,
 U16 cellIdx
 )
{
   if( lteCellSib3CfgGrp== NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCellSib3CfgGrp = *lteCellSib3CfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Cell Sib1 Cfg parameters
 *
 * @details
 *
 *     Function:msmSetCellSib1ConfigGroupParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCellSib1CfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellSib1ConfigGroupParameters
(
 const MsmLteCellSib1CfgGrp *lteCellSib1CfgGrp,
 U32 isPlmnCfgd,
 U16 cellIdx
 )
{
   if(lteCellSib1CfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   if(FALSE == isPlmnCfgd)
   {
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.cellAccessInfo.tac =
         lteCellSib1CfgGrp->cellAccessInfo.tac;
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.cellAccessInfo.cellId =
         lteCellSib1CfgGrp->cellAccessInfo.cellId;
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.cellAccessInfo.cellBarred =
         lteCellSib1CfgGrp->cellAccessInfo.cellBarred;
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.cellAccessInfo.csgIdentity =
         lteCellSib1CfgGrp->cellAccessInfo.csgIdentity;
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.cellSelectInfo =
         lteCellSib1CfgGrp->cellSelectInfo;
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.pMax = lteCellSib1CfgGrp->pMax;
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.freqBandInd =
         lteCellSib1CfgGrp->freqBandInd;
   }
   else
   {
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.cellAccessInfo.numOfPlmns =
         lteCellSib1CfgGrp->cellAccessInfo.numOfPlmns;
      lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.cellAccessInfo.maxNumOfPlmns =
         lteCellSib1CfgGrp->cellAccessInfo.maxNumOfPlmns;
      for(U32 idx = 0; idx < lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.
            cellAccessInfo.numOfPlmns; idx++)
      {
         lteeNodeBparams[cellIdx].lteCellSib1CfgGrp.cellAccessInfo.plmnInfo[idx]
            = lteCellSib1CfgGrp->cellAccessInfo.plmnInfo[idx];
      }
   }
   RETVALUE(ROK);
}

/** @brief This function is used for setting Drx Cfg Params parameters
 *
 * @details
 *
 *     Function:msmSetDrxConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteDrxCfgParams 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetDrxConfigParameters
(
const MsmLteDrxCfgParams   *lteDrxCfgParams,
U16                        cellIdx
)
{
   if(lteDrxCfgParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteDrxCfgParams = *lteDrxCfgParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Cell Meas Cfg parameters
 *
 * @details
 *
 *     Function: msmSetCellMeasConfigParameters
 *
 *         Processing steps:
 *
 * @param[in] lteCellMeasCfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellMeasConfigParameters(
const MsmLteCellMeasCfgGrp   *lteCellMeasCfgGrp,
U16                          cellIdx
)
{
   if(lteCellMeasCfgGrp == NULLP)

   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCellMeasCfgGrp = *lteCellMeasCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Add Cell Cfg parameters
 *
 * @details
 *
 *     Function: msmSetAddCellConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteAddCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetAddCellConfigParameters(
const MsmLteAddCellCfg   *lteAddCellCfg,
U16                      cellIdx
)
{
   if(lteAddCellCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteAddCellCfg = *lteAddCellCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Sm Cell Cfg parameters
 *
 * @details
 *
 *     Function:msmSetSmCellConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteSmCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetSmCellConfigParameters
(
const MsmLteSmCellCfg   *lteSmCellCfg,
U16                     cellIdx
)
{
   if(lteSmCellCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteSmCellCfg = *lteSmCellCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Cell Mib Cfg parameters
 *
 * @details
 *
 *     Function:msmSetCellMibConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCellMibCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellMibConfigParameters
(
const MsmLteCellMibCfgGrp   *lteCellMibCfgGrp,
U16                         cellIdx
)
{
   if(lteCellMibCfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCellMibCfgGrp = *lteCellMibCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting MAC_SCH_Conf parameters
 *
 * @details
 *
 *     Function:msmSetMacSchConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteMAC_SCH_Config
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetMacSchConfigParameters
(
const MsmLteMAC_SCH_Config   *lteMACSCHConfig,
U16                          cellIdx
)
{
   if(lteMACSCHConfig == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteMAC_SCH_Config = *lteMACSCHConfig;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Antenna Common Config parameters
 *
 * @details
 *
 *     Function:msmSetAntennaCommonConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteAntenna_Common_Config 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetAntennaCommonConfigParameters
(
const MsmLteAntenna_Common_Config   *lteAntennaCommonConfig,
U16                                 cellIdx
)
{
   if(lteAntennaCommonConfig == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteAntenna_Common_Config = *lteAntennaCommonConfig;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Pdsch Cfg Dedicated parameters
 *
 * @details
 *
 *     Function:msmSetPdschConfigDedicatedParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePdschCfgDedicated
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPdschConfigDedicatedParameters
(
const MsmLtePdschCfgDedicated   *ltePdschCfgDedicated,
U16                             cellIdx
)
{
   if(ltePdschCfgDedicated == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].ltePdschCfgDedicated = *ltePdschCfgDedicated;

   RETVALUE(ROK);
}

/** @brief This function is used for setting Pusch Basic Cfg Common parameters
 *
 * @details
 *
 *     Function:msmSetPuschBasicCfgCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePuschBasicCfgCommon
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPuschBasicCfgCommonParameters
(
 const MsmLtePuschBasicCfgCommon *ltePuschBasicCfgCommon,
 U16 cellIdx
 )
{ 
   if(ltePuschBasicCfgCommon== NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].ltePuschBasicCfgCommon = *ltePuschBasicCfgCommon;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Pusch Ref Signa lCfg  parameters
 *
 * @details
 *
 *     Function:msmSetPuschRefSignalCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePuschRefSignalCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPuschRefSignalCfgParameters
(
 const MsmLtePuschRefSignalCfg *ltePuschRefSignalCfg,
 U16 cellIdx
 )
{ 
   if(ltePuschRefSignalCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].ltePuschRefSignalCfg = *ltePuschRefSignalCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Pucch Cfg Common parameters
 *
 * @details
 *
 *     Function:msmSetPucchCfgCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePucchCfgCommon
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPucchCfgCommonParameters
(
 const MsmLtePucchCfgCommon *ltePucchCfgCommon,
 U16 cellIdx
 )
{
   if(ltePucchCfgCommon == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].ltePucchCfgCommon = *ltePucchCfgCommon;
   RETVALUE(ROK);
}
/** @brief This function is used for setting SRS Cfg Common parameters
 *
 * @details
 *
 *     Function:msmSetSrsCfgCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteSRSCfgCommon 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetSrsCfgCommonParameters
(
 const MsmLteSRSCfgCommon *lteSRSCfgCommon,
 U16 cellIdx
 )
{
   if(lteSRSCfgCommon == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].lteSRSCfgCommon = *lteSRSCfgCommon;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Rab Policy Cfg parameters
 *
 * @details
 *
 *     Function:msmSetRabPolicyCfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRabPolicyCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetRabPolicyCfgGrpSrb1Parameters
(
const MsmLteRabPolicyCfgGrp   *lteRabPolicyCfgGrp,
U16                           cellIdx
)
{ 
   if(lteRabPolicyCfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.actType = lteRabPolicyCfgGrp->actType;
   lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.srbPolicy[MSM_SRB1] = lteRabPolicyCfgGrp->srbPolicy[MSM_SRB1];
   RETVALUE(ROK);
}

/** @brief This function is used for setting Rab Policy Cfg parameters
 *
 * @details
 *
 *     Function:msmSetRabPolicyCfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRabPolicyCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetRabPolicyCfgGrpSrb2Parameters
(
const MsmLteRabPolicyCfgGrp    *lteRabPolicyCfgGrp,
U16                            cellIdx
)
{ 
   if(lteRabPolicyCfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.actType = lteRabPolicyCfgGrp->actType;
   lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.srbPolicy[MSM_SRB2] = lteRabPolicyCfgGrp->srbPolicy[MSM_SRB2];
   RETVALUE(ROK);
}

/** @brief This function is used for setting Rab Policy Cfg parameters
 *
 * @details
 *
 *     Function:msmSetRabPolicyCfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRabPolicyCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetRabPolicyCfgGrpDrbParameters
(
const MsmLteRabPolicyCfgGrp   *lteRabPolicyCfgGrp,
U16                           cellIdx
)
{
   U32 idx;
   if(lteRabPolicyCfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.isDscpEnable = lteRabPolicyCfgGrp->isDscpEnable;
   for(idx = 0; idx < MSM_MAX_QCI; idx++)
   {   
      lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.drbPolicy[idx] = lteRabPolicyCfgGrp->drbPolicy[idx];
   } 
   RETVALUE(ROK);
}

/** @brief This function is used for setting Ue Timer Constants parameters
 *
 * @details
 *
 *     Function:msmSetUeTimerConstantsParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteUeTimerConstants) 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetUeTimerConstantsParameters
(
 const MsmLteUeTimerConstants *lteUeTimerConstants,
 U16 cellIdx
 )
{
   if(lteUeTimerConstants == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteUeTimerConstants = *lteUeTimerConstants;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Cell EAID Cfg parameters
 *
 * @details
 *
 *     Function:msmSetCellEaidCfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCellEAIDCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellEaidCfgGrpParameters
(
const MsmLteCellEAIDCfgGrp   *lteCellEAIDCfgGrp,
U16                          cellIdx
)
{
   if(lteCellEAIDCfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCellEAIDCfgGrp = *lteCellEAIDCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Cell Sib9 Cfg parameters
 *
 * @details
 *
 *     Function:msmSetCellSib9CfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCellSib9CfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellSib9CfgGrpParameters
(
 const MsmLteCellSib9CfgGrp *lteCellSib9CfgGrp,
 U16 cellIdx
 )
{
   if(lteCellSib9CfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCellSib9CfgGrp = *lteCellSib9CfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting CQIPeriodicReportCfg parameters
 *
 * @details
 *
 *     Function:msmSetCqiPeriodicReportCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCQIPeriodicReportCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetCqiPeriodicReportCfgParameters
(
const MsmLteCQIPeriodicReportCfg   *lteCQIPeriodicReportCfg,
U16                                cellIdx
)
{
   if(lteCQIPeriodicReportCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCQIPeriodicReportCfg = *lteCQIPeriodicReportCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting lteNeighFreqCfg parameters
 *
 * @details
 *
 *     Function:msmSetNeighFreqCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteNeighFreqCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetNeighFreqEutraCfgParameters
(
 const MsmLteNeighFreqCfg *lteNeighFreqCfg,
 U16 cellIdx
 )
{
   U16 idx, idx1 = 0;
   if(lteNeighFreqCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.actType =
         lteNeighFreqCfg->actType;
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.numEutraFreq =
         lteNeighFreqCfg->numEutraFreq;
      for(idx=0;idx< (lteNeighFreqCfg->numEutraFreq);idx++)
      {
         lteeNodeBparams[cellIdx].lteNeighFreqCfg.t.addNeighFreq[idx].eutranFreq
            = lteNeighFreqCfg->t.addNeighFreq[idx].eutranFreq;
      }
   }
   RETVALUE(ROK);
}

/** @brief This function is used for setting lteNeighFreqCfg parameters
 *
 * @details
 *
 *     Function:msmSetTdsCdmaUtranTddFreqParameters
 *
 *         Processing steps:
 *
 * @param[in]lteNeighFreqCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetTdsCdmaUtranTddFreqParameters
(
 const MsmLteNeighFreqCfg *lteNeighFreqCfg,
 U16 cellIdx
 )
{
   U16 idx;
   if(lteNeighFreqCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteNeighFreqCfg.actType = lteNeighFreqCfg->actType;
   lteeNodeBparams[cellIdx].lteNeighFreqCfg.numUtraTddFreq =
      lteNeighFreqCfg->numUtraTddFreq;
   lteeNodeBparams[cellIdx].lteNeighFreqCfg.maxUtraTddFreqEntries =
      lteNeighFreqCfg->maxUtraTddFreqEntries;
   for(idx=0; idx< (lteNeighFreqCfg->numUtraTddFreq);idx++)
   {
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.t.addNeighFreq[idx].utranTddFreq
         = lteNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq;
   }
   RETVALUE(ROK);

}

/** @brief This function is used for setting lteNeighFreqCfg parameters
 *
 * @details
 *
 *     Function:msmSetNeighFreqCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteNeighFreqCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetNeighFreqUtraCfgParameters
(
 const MsmLteNeighFreqCfg *lteNeighFreqCfg,
 U16 cellIdx
 )
{
   U16 idx;
   if(lteNeighFreqCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteNeighFreqCfg.actType = lteNeighFreqCfg->actType;
   lteeNodeBparams[cellIdx].lteNeighFreqCfg.numUtraFreq =
      lteNeighFreqCfg->numUtraFreq;
   lteeNodeBparams[cellIdx].lteNeighFreqCfg.maxUtraFreqEntries =
      lteNeighFreqCfg->maxUtraFreqEntries;
   for(idx=0; idx< (lteNeighFreqCfg->numUtraFreq);idx++)
   {
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.t.addNeighFreq[idx].utranFreq =
         lteNeighFreqCfg->t.addNeighFreq[idx].utranFreq;
   }
   RETVALUE(ROK);

}

/** @brief This function is used for setting Eutra Neighbor Cell Configuration
 * parameters
 *
 * @details
 *
 *     Function:msmSetNeighborListInUseParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteNeighCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetNeighborListInUseEutraParameters
(
 const MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U16 idx;
   if((lteNeighCellCfg == NULLP) ||
         (lteeNodeBparams[cellIdx].lteNeighCellCfg.numEutraCells
          > MSM_MAX_NUM_NEIGH_CELLS))
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteNeighCellCfg.isX2Enabled =
      lteNeighCellCfg->isX2Enabled;
   lteeNodeBparams[cellIdx].lteNeighCellCfg.actType =
      lteNeighCellCfg->actType;
   lteeNodeBparams[cellIdx].lteNeighCellCfg.maxCellEntries =
      lteNeighCellCfg->maxCellEntries;
   lteeNodeBparams[cellIdx].lteNeighCellCfg.numEutraCells =
      lteNeighCellCfg->numEutraCells;
   for(idx=0;idx< lteNeighCellCfg->numEutraCells;idx++)
   {  
      lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].
         eutraCell = lteNeighCellCfg->t.neighAddCfg[idx].eutraCell;
   }  
   RETVALUE(ROK);
}

/** @brief This function is used for setting UTRA lteNeighCellCfg parameters
 *
 * @details
 *
 *     Function:msmSetTdsCdmaUtranTddCellParameters
 *
 *         Processing steps:
 *
 * @param[in]lteNeighCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetTdsCdmaUtranTddCellParameters
(
 const MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U16 idx,idx1 = 0;
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {   
      if((lteNeighCellCfg == NULLP) ||
            (lteeNodeBparams[cellIdx].lteNeighCellCfg.numUtraTddCells >
             MSM_MAX_NUM_NEIGH_CELLS))
      {   
         RETVALUE(RFAILED);
      }
      lteeNodeBparams[cellIdx].lteNeighCellCfg.actType =
         lteNeighCellCfg->actType;
      lteeNodeBparams[cellIdx].lteNeighCellCfg.maxTddCellEntries =
         lteNeighCellCfg->maxTddCellEntries;
      lteeNodeBparams[cellIdx].lteNeighCellCfg.numUtraTddCells =
         lteNeighCellCfg->numUtraTddCells;
      for(idx=0;idx< lteNeighCellCfg->numUtraTddCells ;idx++)
      {  
         lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].
            utranTddCell = lteNeighCellCfg->t.neighAddCfg[idx].utranTddCell;
      }
   }  

   RETVALUE(ROK);
}

/** @brief This function is used for setting UTRA lteNeighCellCfg parameters
 *
 * @details
 *
 *     Function:msmSetNeighborListInUseParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteNeighCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetNeighborListInUseUtraParameters
(
 const MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U16 idx,idx1;
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {   
      if((lteNeighCellCfg == NULLP) ||
            (lteeNodeBparams[cellIdx].lteNeighCellCfg.numUtraCells
             > MSM_MAX_NUM_NEIGH_CELLS))
      {   
         RETVALUE(RFAILED);
      }
      lteeNodeBparams[cellIdx].lteNeighCellCfg.actType =
         lteNeighCellCfg->actType;
      lteeNodeBparams[cellIdx].lteNeighCellCfg.maxCellEntries =
         lteNeighCellCfg->maxCellEntries;
      lteeNodeBparams[cellIdx].lteNeighCellCfg.numUtraCells =
         lteNeighCellCfg->numUtraCells;
      for(idx=0;idx< lteNeighCellCfg->numUtraCells ;idx++)
      {  
         lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].utranCell =
            lteNeighCellCfg->t.neighAddCfg[idx].utranCell;
      }
   }  

   RETVALUE(ROK);
}

/** @brief This function is used for setting Sib5 Inter Freq Carrier parameters
 *
 * @details
 *
 *     Function: msmSetSib5InterFreqCarrierInfoParameters
 *
 *         Processing steps:
 *
 * @param[in]lteSib5InterFreqCarrierInfo 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetSib5InterFreqCarrierInfoParameters
(
 const MsmLteSib5InterFreqCarrierInfo *lteSib5InterFreqCarrierInfo,
 U16 cellIdx
 )
{
   if(lteSib5InterFreqCarrierInfo == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteSib5InterFreqCarrierInfo =
      *lteSib5InterFreqCarrierInfo;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Cell Sib6 Cfg Grp parameters
 *
 * @details
 *
 *     Function:msmSetCellSib6ConfigGroupParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteCellSib6CfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellSib6ConfigGroupParameters
(
 const MsmLteCellSib6CfgGrp *lteCellSib6CfgGrp,
 U16 cellIdx
 )
{
   if(lteCellSib6CfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCellSib6CfgGrp = *lteCellSib6CfgGrp;
   RETVALUE(ROK);
}
/** @brief This function is used for setting Enb Proto Cfg parameters
 *
 * @details
 *
 *     Function:msmSetEnbProtoCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteEnbProtoCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetEnbProtoCfgParameters
(
 const MsmLteEnbProtoCfg *lteEnbProtoCfg,
 U16 cellIdx
 )
{
   if(lteEnbProtoCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteEnbProtoCfg = *lteEnbProtoCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Ac Barring Info parameters
 *
 * @details
 *
 *     Function:msmSetAcBarringInfoParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteAcBarringInfo 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetAcBarringInfoParameters
(
 const MsmLteAcBarringInfo *lteAcBarringInfo,
 U16 cellIdx
 )
{
   if(lteAcBarringInfo == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteAcBarringInfo = *lteAcBarringInfo;
   RETVALUE(ROK);
}

/** @brief This function is used for setting enodeb IP parameters
 *
 * @details
 *
 *     Function: msmSetEnodebIpAddr
 *
 *         Processing steps:
 *
 * @param[in]lteEnodebIpAddr
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetEnodebIpAddr(const MsmEnodebIpAddr *lteEnodebIpAddr)
{
   if(lteEnodebIpAddr == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   fapParameters.lteEnodebIpAddr = *lteEnodebIpAddr;
   RETVALUE(ROK);
}


/** @brief This function is used for setting EARFCNDL and RSSI scanned by REM
 *
 * @details
 *
 *     Function:msmSetEarfcnRssiParameters
 *
 *         Processing steps:
 *
 * @param[in]lteEarfcnRssiCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetEarfcnRssiParameters
(
 const MsmLteEarfcnRssiCfg *lteEarfcnRssiCfg,
 U16 cellIdx
 )
{
   if(lteEarfcnRssiCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteEarfcnRssiCfg = *lteEarfcnRssiCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Self Config Params parameters
 *
 * @details
 *
 *     Function:msmSetSelfConfigParameters
 *
 *         Processing steps:
 *
 * @param[in]lteSelfConfigParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetSelfConfigParameters(const MsmLteSonGenericParams *lteSelfConfigParams,U16 cellIdx)
{
   if(lteSelfConfigParams == NULLP)
   {
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteSonGenericParams = *lteSelfConfigParams;
   RETVALUE(ROK);
}
/** @brief This function is used for setting Rem Scan Parameters parameters
 *
 * @details
 *
 *     Function:msmSetRemScanParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteRemScanParameters 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetRemScanParameters
(
 const MsmLteRemScanParameters *lteRemScanParameters,
 U16 cellIdx
 )
{
   if(lteRemScanParameters == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteRemScanParameters = *lteRemScanParameters;
   RETVALUE(ROK);
}
/** @brief This function is used for setting Power Off set parameters
 *
 * @details
 *
 *     Function:msmSetDynCfiParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteDynCfiParams 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetDynCfiParameters(const MsmLteDynCfiGrp *lteDynCfiParams, U16 cellIdx)
{
   if(lteDynCfiParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteDynCfiParams = *lteDynCfiParams;
   RETVALUE(ROK);
}


/** @brief This function is used for setting Power Off set parameters
 *
 * @details
 *
 *     Function:msmSetPowerOffsetParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePowerOffsetParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPowerOffsetParameters
(
 const MsmLtePowerOffsetParams *ltePowerOffsetParams,
 U16 cellIdx
 )
{
   if(ltePowerOffsetParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].ltePowerOffsetParams = *ltePowerOffsetParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Fap Control parameters
 *
 * @details
 *
 *     Function:msmSetFapControlParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteFapControlParams 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetFapControlParameters
(
 const MsmLteFapControlParams *lteFapControlParams,
 U16 cellIdx
 )
{
   if(lteFapControlParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteFapControlParams = *lteFapControlParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting PRB allocation parameters
 *
 * @details
 *
 *     Function:msmSetPrbAllocationParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePRBallocation
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPrbAllocationParameters(const MsmLtePRBallocation *ltePRBallocation, U16 cellIdx)
{
   if(ltePRBallocation == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].ltePRBallocation = *ltePRBallocation;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Sib4 Csg Info parameters
 *
 * @details
 *
 *     Function:msmSetSib4CsgInfoParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteSib4CsgInfo
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetSib4CsgInfoParameters
(
 const MsmLteSib4CsgInfo *lteSib4CsgInfo,
 U16 cellIdx
 )
{
   if(lteSib4CsgInfo == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteSib4CsgInfo = *lteSib4CsgInfo;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Rrm Tdd Param parameters
 *
 * @details
 *
 *     Function:msmSetRrmTddParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRrmTddParam
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetRrmTddParameters(const MsmLteRrmTddParam *lteRrmTddParam, U16 cellIdx)
{
   if(lteRrmTddParam== NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteRrmTddParam = *lteRrmTddParam;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Sctp Cfg parameters
 *
 * @details
 *
 *     Function: msmSetSctpConfigParameters
 *
 *         Processing steps:
 *
 * @param[in] lteSctpCfgParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetSctpConfigParameters
(
 const MsmLteSctpCfgParams *lteSctpCfgParams,
 U16 cellIdx
 )
{
   if(lteSctpCfgParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteSctpCfgParams = *lteSctpCfgParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting PCCH Cfg parameters
 *
 * @details
 *
 *     Function:msmSetPcchConfigCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in]ltePCCHCfgCommon 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetPcchConfigCommonParameters
(
 const MsmLtePCCHCfgCommon *ltePCCHCfgCommon,
 U16 cellIdx
 )
{
   if(ltePCCHCfgCommon == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].ltePCCHCfgCommon = *ltePCCHCfgCommon;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Cell Ul Schd Cfg parameters
 *
 * @details
 *
 *     Function:msmSetCellUlSchdConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteCellUlSchdCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellUlSchdConfigParameters
(
 const MsmLteCellUlSchdCfgGrp *lteCellUlSchdCfgGrp,
 U16 cellIdx
 )
{
   if(lteCellUlSchdCfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCellUlSchdCfgGrp = *lteCellUlSchdCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Cell Dl Schd Cfg parameters
 *
 * @details
 *
 *     Function:msmSetCellDlSchdConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteCellDlSchdCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellDlSchdConfigParameters
(
 const MsmLteCellDlSchdCfgGrp *lteCellDlSchdCfgGrp,
 U16 cellIdx
 )
{
   if(lteCellDlSchdCfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteCellDlSchdCfgGrp = *lteCellDlSchdCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Ms Cell Cfg parameters
 *
 * @details
 *
 *     Function:msmSetMsCellCfgReqParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteMsCellCfgReq
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetMsCellCfgReqParameters
(
 const MsmLteMsCellCfgReq *lteMsCellCfgReq,
 U16 cellIdx
 )
{
   if(lteMsCellCfgReq == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteMsCellCfgReq = *lteMsCellCfgReq;
   RETVALUE(ROK);
}

/** @brief This function is used for setting DbgParams parameters
 *
 * @details
 *
 *     Function:msmSetDbgParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteDbgParams 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetDbgParameters(const MsmLteDbgParams *lteDbgParams)
{
   if(lteDbgParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   fapParameters.lteDbgParams = *lteDbgParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Ul Alloc Info parameters
 *
 * @details
 *
 *     Function:msmSetUlAllocInfoCbParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteUlAllocInfoCbParams 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetUlAllocInfoCbParameters
(
 const MsmLteUlAllocInfoCbParams *lteUlAllocInfoCbParams,
 U16 cellIdx
 )
{
   if(lteUlAllocInfoCbParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteUlAllocInfoCbParams = *lteUlAllocInfoCbParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Proc Timer Cfg parameters
 *
 * @details
 *
 *     Function:msmSetProcTimerCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteProcTimerCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetProcTimerCfgParameters
(
 const MsmLteProcTimerCfg *lteProcTimerCfg,
 U16 cellIdx
 )
{
   if(lteProcTimerCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteProcTimerCfg = *lteProcTimerCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Rem Control parameters
 *
 * @details
 *
 *     Function:msmSetFactorySmCellParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteSmCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetFactorySmCellParameters
(
 const MsmLteSmCellCfg *lteSmCellCfg,
 U16 cellIdx
 )
{
   if(lteSmCellCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteSmCellCfg.maxUeSupp = lteSmCellCfg->maxUeSupp;
   RETVALUE(ROK);
}



PUBLIC S16 msmSetFapAccessParameters
(
 const MsmLteFapAccessParams *lteFapAccessParams,
 U16 cellIdx
 )
{
   if(lteFapAccessParams == NULLP)
   {
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteFapAccessParams=*lteFapAccessParams;
   RETVALUE(ROK);
}

PUBLIC S16 msmGetFapAccessParameters
(
 MsmLteFapAccessParams *lteFapAccessParams,
 U16 cellIdx
 )
{
   if(lteFapAccessParams == NULLP)
   {
      RETVALUE(RFAILED);
   }
   *lteFapAccessParams = lteeNodeBparams[cellIdx].lteFapAccessParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Rem Control parameters
 *
 * @details
 *
 *     Function: msmSetFactoryFapAceessParameters
 *
 *         Processing steps:
 *
 * @param[in] lteFapAccessParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetFapAcceessParameters
(
 const MsmLteFapAccessParams *lteFapAccessParams,
 U16 cellIdx
 )
{
   if(lteFapAccessParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].lteFapAccessParams = *lteFapAccessParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting perf Mgmt parameters
 *
 * @details
 *
 *     Function:msmSetPmParameters 
 *
 *         Processing steps:
 *
 * @param[in] perfMgmtParameters
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 *rakesh*/

PUBLIC S16 msmSetPmParameters(const MsmPerfMgmtParameters *perfMgmtParameters)
{
   if(perfMgmtParameters == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   wcdmaNodeBparams.perfMgmtParameters = *perfMgmtParameters;
   RETVALUE(ROK);
}

/** @brief This function is used for setting frequent Fault Mgmt parameters
 *
 * @details
 *
 *     Function:msmSetFrequentFaultParameters 
 *
 *         Processing steps:
 *
 * @param[in]frequentFaultMgmtParameters 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 *rakesh*/

PUBLIC S16 msmSetFrequentFaultParameters(const MsmFrequentFaultMgmtParameters *frequentFaultMgmtParameters)
{
   if(frequentFaultMgmtParameters == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   faultMgmtParams.frequentFaultMgmtParameters = *frequentFaultMgmtParameters;
   RETVALUE(ROK);
}

/** @brief This function is used for setting dma Band Class parameters
 *
 * @details
 *
 *     Function:msmSetCdmaBandClassParameters 
 *
 *         Processing steps:
 *
 * @param[in] cdmaBandClass
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 **/

PUBLIC S16 msmSetCdmaBandClassParameters
(
 const MsmCdmaBandClass *cdmaBandClassParams,
 U16 cellIdx
 )
{
   if(cdmaBandClassParams == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].cdmaBandClassParams = *cdmaBandClassParams;
   RETVALUE(ROK);
}

/** @brief This function is used for setting generic parameters
 *
 * @details
 *
 *     Function: msmSetCdmaMobilityParameters
 *
 *         Processing steps:
 *
 * @param[in] cdmaMobilityParam
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCdmaMobilityParameters
(
 const MsmCdmaMobilityParam *cdmaMobilityParam,
 U16 cellIdx
 )
{
   if(cdmaMobilityParam == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].cdmaMobilityParam = *cdmaMobilityParam;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Config 1x RTTC parameters
 *
 * @details
 *
 *     Function:msmSetBarringCfg1xRtt 
 *
 *         Processing steps:
 *
 * @param[in] barringConfig1xRTTCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetBarringCfg1xRtt
(
 const MsmBarringConfig1xRTTCfg *barringConfig1xRTTCfg,
 U16 cellIdx
 )
{
   if(barringConfig1xRTTCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].barringConfig1xRTTCfg = *barringConfig1xRTTCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Neigh Cell parameters
 *
 * @details
 *
 *     Function:msmSetCdma1XRttNghCell 
 *
 *         Processing steps:
 *
 * @param[in] lteNeighCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCdma1XRttNghCell
(
 const MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U32 idx = 0, idx1 = 0;
   if(lteNeighCellCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {
      lteeNodeBparams[cellIdx].lteNeighCellCfg.numCdma1xCells =
         lteNeighCellCfg->numCdma1xCells;
      for(idx = 0; idx <
            lteeNodeBparams[cellIdx].lteNeighCellCfg.numCdma1xCells; idx++)
      {
         lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].cdma1xCell
            = lteNeighCellCfg->t.neighAddCfg[idx].cdma1xCell;
      }
   }
   RETVALUE(ROK);
}

/** @brief This function is used for setting generic parameters
 *
 * @details
 *
 *     Function:msmSetSib8Parameters 
 *
 *         Processing steps:
 *
 * @param[in] cellSib8CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetSib8Parameters
(
 const MsmCellSib8CfgGrp *cellSib8CfgGrp,
 U16 cellIdx
 )
{
   if(cellSib8CfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].cellSib8CfgGrp = *cellSib8CfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting csfb Cfg parameters
 *
 * @details
 *
 *     Function:msmSetCsfbCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] csfbCfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCsfbCfgParameters(const MsmCsfbCfgGrp *csfbCfgGrp, U16 cellIdx)
{
   if(csfbCfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].csfbCfgGrp = *csfbCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Sps Cell Cfg parameters
 *
 * @details
 *
 *     Function:msmSetSpsParameters 
 *
 *         Processing steps:
 *
 * @param[in] stSpsCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetSpsParameters
(
 const MsmSpsCellConfigData *stSpsCellCfg,
 U16 cellIdx
 )
{
   if(stSpsCellCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[cellIdx].stSpsCellCfg = *stSpsCellCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting eNB log level parameter
 *
 * @details
 *
 *     Function:msmSetLogLvlParameter 
 *
 *         Processing steps:
 *
 * @param[in] lteLogLvlCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetLogLvlParameter(const MsmEnbLogLvlData *lteLogLvlCfg)
{
   if(lteLogLvlCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   fapParameters.lteLogLvlCfg = *lteLogLvlCfg;
   RETVALUE(ROK);
}

/*TM4 changes */
/** @brief This function is used for setting Transmission Mode Cfg 
 *
 * @details
 *
 *     Function:msmSetTMParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteTransModeCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetTMParameters
(
 const MsmTMCellConfig *lteTransModeCellCfg,
 U16 cellIdx
 )
{
   if(lteTransModeCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].lteTransModeCellCfg = *lteTransModeCellCfg;
   RETVALUE(ROK);
}
/** @brief This function is used for setting CNM Param 
 *
 * @details
 *
 *     Function:msmSetCellCnmCfgGrpParameters
 *
 *         Processing steps:
 *
 * @param[in]lteTddParam 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCellCnmCfgGrpParameters(MsmCnmCfg *lteCnmCfg, U16 cellIdx)
{ 
   if(lteCnmCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].lteCnmCfg = *lteCnmCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Total eNodeB stats configuration 
 *
 * @details
 *
 *     Function:msmSetTenbStatsCfgGrpParameters
 *
 *         Processing steps:
 *
 * @param[in] : 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetTenbStatsCfgGrpParameters(MsmTenbStatsCfg *tenbStatsCfg)
{ 
   if(tenbStatsCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   fapParameters.tenbStatsCfg= *tenbStatsCfg;
   RETVALUE(ROK);
}


/** @brief This function is used for setting Tdd Param 
 *
 * @details
 *
 *     Function:msmSetTddParameters
 *
 *         Processing steps:
 *
 * @param[in]lteTddParam 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetTddParameters(MsmLteTddParam *lteTddParam,U16 cellIdx)
{ 
   if(lteTddParam == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].lteTddParam =*lteTddParam;
   RETVALUE(ROK);
}


/** @brief This function is used for setting Sib7Cfg Param 
 *
 * @details
 *
 *     Function:msmSetsib7CfgGrpParameters
 *
 *         Processing steps:
 *
 * @param[in]sib7CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetsib7CfgGrpParameters
(
 MsmLteCellSib7CfgGrp *sib7CfgGrp,
 U16 cellIdx
 )
{ 
   if(sib7CfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].sib7CfgGrp = *sib7CfgGrp;
   RETVALUE(ROK);
}


/** @brief This function is used for setting csfbGranCfg Param 
 *
 * @details
 *
 *     Function:msmSetcsfbGeranCfgParameters
 *
 *         Processing steps:
 *
 * @param[in]csfbToGeranCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetcsfbGeranCfgParameters
(
 MsmLteCsfbGeranCfg *csfbToGeranCfg,
 U16 cellIdx
 )
{ 
   if(csfbToGeranCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].csfbToGeranCfg = *csfbToGeranCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting NeighFreqCfgGeran Param 
 *
 * @details
 *
 *     Function:msmSetNeighFreqCfgGeranParameters
 *
 *         Processing steps:
 *
 * @param[in]lteNeighFreqCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetNeighFreqCfgGeranParameters
(
 const MsmLteNeighFreqCfg *lteNeighFreqCfg,
 U16 cellIdx
 )
{ 
   U16 idx = 0, idx1 = 0;

   if(lteNeighFreqCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   for(idx1 = 0; idx1 < (cellIdx + 1); idx1++)
   {
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.actType =
         lteNeighFreqCfg->actType;
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.numGeranFreq = 
         lteNeighFreqCfg->numGeranFreq;
      for(idx=0; idx< (lteNeighFreqCfg->numGeranFreq); idx++)
      {
         lteeNodeBparams[cellIdx].lteNeighFreqCfg.t.addNeighFreq[idx].geranFreq
            = lteNeighFreqCfg->t.addNeighFreq[idx].geranFreq;
      }
   }

   RETVALUE(ROK);
}

/** @brief This function is used for setting Neigh Cell Geran parameters
 *
 * @details
 *
 *     Function:msmSetNeighCellCfgGeranParameters
 *
 *         Processing steps:
 *
 * @param[in] lteNeighCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetNeighCellCfgGeranParameters
(
 const MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U32 idx = 0,idx1 = 0;

   if(lteNeighCellCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   for(idx1 = 0; idx1 <MSM_MAX_CELLS; idx1++)
   {
      lteeNodeBparams[cellIdx].lteNeighCellCfg.numGeranCells =
         lteNeighCellCfg->numGeranCells;

      for(idx = 0; idx < lteeNodeBparams[cellIdx].lteNeighCellCfg.numGeranCells;
            idx++)
      {
         lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].geranCell =
            lteNeighCellCfg->t.neighAddCfg[idx].geranCell;
      }
   }

   RETVALUE(ROK);
}
/** @brief This function is used for setting Sib2 Param 
 *
 * @details
 *
 *     Function:msmSetSib2Cfg
 *
 *         Processing steps:
 *
 * @param[in]
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetSib2Cfg(MsmSib2Cfg *sib2Cfg,U16 cellIdx)
{ 
   if(sib2Cfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].sib2Cfg = *sib2Cfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Mac Main Param 
 *
 * @details
 *
 *     Function:msmSetMacMainConfig
 *
 *         Processing steps:
 *
 * @param[in]
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetMacMainConfig(MsmMacMainConifg *macMainConfig,U16 cellIdx)
{ 
   if(macMainConfig == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].macMainConfig = *macMainConfig;
   RETVALUE(ROK);
}

/** @brief This function is used for setting ltecellSchdPwrCfg Param 
 *
 * @details
 *
 *     Function:msmSetSchdPwrCfgParameters
 *
 *         Processing steps:
 *
 * @param[in]
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetSchdPwrCfgParameters
(
 MsmCellSchdPwrCfg *ltecellSchdPwrCfg,
 U16 cellIdx
 )
{ 
   if(ltecellSchdPwrCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].ltecellSchdPwrCfg = *ltecellSchdPwrCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for setting Rsys TPM Param 
 *
 * @details
 *
 *     Function:msmSetRsysTpmCfgParameters
 *
 *         Processing steps:
 *
 * @param[in]   MsmRsysTpmCfg tpmCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmSetRsysTpmCfgParameters(MsmRsysTpmCfg *tpmCfg,U16 cellIdx)
{ 
   if(tpmCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   lteeNodeBparams[cellIdx].tpmCfg = *tpmCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting generic parameters
 *
 * @details
 *
 *     Function: MsmLtePrachCfgCommon 
 *
 *         Processing steps:
 *
 * @param[in] ltePrachCfgCommon 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetPrachConfigCommonParameters
(
 MsmLtePrachCfgCommon *ltePrachCfgCommon,
 U16 cellIdx
 )
{
   if(ltePrachCfgCommon == NULLP)
   {
      RETVALUE(RFAILED);
   }
   *ltePrachCfgCommon = lteeNodeBparams[cellIdx].ltePrachCfgCommon;
   RETVALUE(ROK);
}

/** @brief This function is used for getting RIM parameters
 * *
 * * @details
 * *
 * *     Function: msmGetRimParameters
 * *
 * *         Processing steps:
 * *
 * * @param[in] lteRimParams
 * * @return S16
 * *        -# Success : ROK
 * *        -# Failure : RFAILED
 * */
PUBLIC S16 msmGetRimParameters(MsmLteRimParams* lteRimParams, U16 cellIdx)
{
   if(lteRimParams == NULLP)
   {
      RETVALUE(RFAILED);
   }
   *lteRimParams = lteeNodeBparams[cellIdx].lteRimParams;
   RETVALUE(ROK);
}
/** @brief This function is used for setting generic parameters
 *
 * @details
 *
 *     Function: msmGetEnodebIpParameters
 *
 *         Processing steps:
 *
 * @param[in]lteeNodeBIPparams 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetEnodebIpParameters(MsmLteeNodeBIPparams *lteeNodeBIPparams)
{
   if(lteeNodeBIPparams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteeNodeBIPparams = fapParameters.lteeNodeBIPparams;
   RETVALUE(ROK);
}
/** @brief This function is used for getting generic parameters
 *
 * @details
 *
 *     Function: msmGetRachConfigCommonParameters
 *
 *         Processing steps:
 *
 * @param[in] lteRachCfgCommonParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetRachConfigCommonParameters
(
 MsmLteRachCfgCommonParams *lteRachCfgCommonParams,
 U16 cellIdx
 )
{
   if(lteRachCfgCommonParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteRachCfgCommonParams = lteeNodeBparams[cellIdx].lteRachCfgCommonParams;
   RETVALUE(ROK);
}
/** @brief This function is used for getting generic parameters
 *
 * @details
 *
 *     Function:msmGetPdschConfigCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in]ltePdschCfgCommon
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetPdschConfigCommonParameters
(
 MsmLtePdschCfgCommon *ltePdschCfgCommon,
 U16 cellIdx
 )
{
   if(ltePdschCfgCommon == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *ltePdschCfgCommon = lteeNodeBparams[cellIdx].ltePdschCfgCommon;
   RETVALUE(ROK);
}
/** @brief This function is used for getting generic parameters
 *
 * @details
 *
 *     Function:msmGetUlPowerControlCommonParameters
 *
 *         Processing steps:
 *
 * @param[in]lteULPwrCtrlCommon
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetUlPowerControlCommonParameters
(
 MsmLteULPwrCtrlCommon *lteULPwrCtrlCommon,
 U16 cellIdx
 )
{
   if(lteULPwrCtrlCommon == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteULPwrCtrlCommon = lteeNodeBparams[cellIdx].lteULPwrCtrlCommon;
   RETVALUE(ROK);
}
/** @brief This function is used for etting generic parameters
 *
 * @details
 *
 *     Function:msmGetUlFrequencyInfoParameters
 *
 *         Processing steps:
 *
 * @param[in]lteULFrequencyInfo
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetUlFrequencyInfoParameters
(
 MsmLteULFrequencyInfo *lteULFrequencyInfo,
 U16 cellIdx
 )
{
   if(lteULFrequencyInfo == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteULFrequencyInfo = lteeNodeBparams[cellIdx].lteULFrequencyInfo;
   RETVALUE(ROK);
}
/** @brief This function is used for etting generic parameters
 *
 * @details
 *
 *     Function:msmGetCell_Sib3ConfigGroupParameters
 *
 *         Processing steps:
 *
 * @param[in]lteCellSib3CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetCell_Sib3ConfigGroupParameters
(
 MsmLteCellSib3CfgGrp *lteCellSib3CfgGrp,
 U16 cellIdx
 )
{
   if(lteCellSib3CfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCellSib3CfgGrp = lteeNodeBparams[cellIdx].lteCellSib3CfgGrp;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteCellSib1CfgGrp
 *
 * @details
 *
 *     Function:msmGetCellSib1ConfigGroupParameters:
 *
 *         Processing steps:
 *
 * @param[in]lteCellSib1CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetCellSib1ConfigGroupParameters
(
 MsmLteCellSib1CfgGrp *lteCellSib1CfgGrp,
 U16 cellIdx
 )
{
   if(lteCellSib1CfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCellSib1CfgGrp = lteeNodeBparams[cellIdx].lteCellSib1CfgGrp;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteDrxCfgParams 
 *
 * @details
 *
 *     Function:msmGetDrxConfigParameters
 *
 *         Processing steps:
 *
 * @param[in] lteDrxCfgParam
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetDrxConfigParameters
(
MsmLteDrxCfgParams *lteDrxCfgParams,
U16                cellIdx
)
{
   if(lteDrxCfgParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteDrxCfgParams = lteeNodeBparams[cellIdx].lteDrxCfgParams;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteCellMeasCfgGrp  
 *
 * @details
 *
 *     Function: msmGetCellMeasConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteCellMeasCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetCellMeasConfigParameters
(
MsmLteCellMeasCfgGrp *lteCellMeasCfgGrp,
U16                  cellIdx
)
{
   if(lteCellMeasCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCellMeasCfgGrp = lteeNodeBparams[cellIdx].lteCellMeasCfgGrp;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteAddCellCfg 
 *
 * @details
 *
 *     Function:msmGetAddCellConfigParameters
 *
 *         Processing steps:
 *
 * @param[in]lteAddCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetAddCellConfigParameters
(
MsmLteAddCellCfg *lteAddCellCfg,
U16              cellIdx
)
{
   if(lteAddCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteAddCellCfg = lteeNodeBparams[cellIdx].lteAddCellCfg;
   RETVALUE(ROK);
}
/** @brief This function is used for getting generic parameters
 *
 * @details
 *
 *     Function:msmGetSmCellConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteSmCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetSmCellConfigParameters
(
MsmLteSmCellCfg *lteSmCellCfg,
U16             cellIdx
)
{
   if(lteSmCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteSmCellCfg = lteeNodeBparams[cellIdx].lteSmCellCfg;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteCellMibCfgGrp 
 *
 * @details
 *
 *     Function:msmGetCellMibConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteCellMibCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetCellMibConfigParameters
(
MsmLteCellMibCfgGrp *lteCellMibCfgGrp,
U16                 cellIdx
)
{
   if(lteCellMibCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCellMibCfgGrp = lteeNodeBparams[cellIdx].lteCellMibCfgGrp;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteCellMibCfgGrp 
 *
 * @details
 *
 *     Function:msmGetMacSchConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteMAC_SCH_Config 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetMacSchConfigParameters
(
MsmLteMAC_SCH_Config *lteMAC_SCH_Config,
U16                  cellIdx
)
{
   if(lteMAC_SCH_Config == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteMAC_SCH_Config = lteeNodeBparams[cellIdx].lteMAC_SCH_Config;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteCellMibCfgGrp 
 *
 * @details
 *
 *     Function:msmGetAntennaCommonConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteAntenna_Common_Config 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetAntennaCommonConfigParameters
(
MsmLteAntenna_Common_Config *lteAntenna_Common_Config,
U16                         cellIdx
)
{
   if(lteAntenna_Common_Config == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteAntenna_Common_Config = lteeNodeBparams[cellIdx].lteAntenna_Common_Config;
   RETVALUE(ROK);
}
/** @brief This function is used for getting  lteGenericParaCfgDedicateds
 *
 * @details
 *
 *     Function:msmGetPdschConfigDedicatedParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteGenericParaCfgDedicateds 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetPdschConfigDedicatedParameters
(
MsmLtePdschCfgDedicated *ltePdschCfgDedicated,
U16                     cellIdx
)
{
   if(ltePdschCfgDedicated == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *ltePdschCfgDedicated = lteeNodeBparams[cellIdx].ltePdschCfgDedicated;
   RETVALUE(ROK);
}
/** @brief This function is used for getting ltePuschBasicCfgCommon 
 *
 * @details
 *
 *     Function:msmGetPuschBasicCfgCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePuschBasicCfgCommon
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetPuschBasicCfgCommonParameters
(
 MsmLtePuschBasicCfgCommon *ltePuschBasicCfgCommon,
 U16 cellIdx
 )
{
   if(ltePuschBasicCfgCommon == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *ltePuschBasicCfgCommon = lteeNodeBparams[cellIdx].ltePuschBasicCfgCommon;
   RETVALUE(ROK);
}
/** @brief This function is used for getting ltePuschRefSignalCfg 
 *
 * @details
 *
 *     Function:msmGetPuschRefSignalCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePuschRefSignalCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetPuschRefSignalCfgParameters
(
 MsmLtePuschRefSignalCfg *ltePuschRefSignalCfg,
 U16 cellIdx
 )
{
   if(ltePuschRefSignalCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *ltePuschRefSignalCfg = lteeNodeBparams[cellIdx].ltePuschRefSignalCfg;
   RETVALUE(ROK);
}
/** @brief This function is used for getting ltePucchCfgCommon 
 *
 * @details
 *
 *     Function:msmGetPucchCfgCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in]ltePucchCfgCommon 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetPucchCfgCommonParameters
(
 MsmLtePucchCfgCommon *ltePucchCfgCommon,
 U16 cellIdx
 )
{
   if(ltePucchCfgCommon == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *ltePucchCfgCommon = lteeNodeBparams[cellIdx].ltePucchCfgCommon;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteSRSCfgCommon 
 *
 * @details
 *
 *     Function:msmGetSrsCfgCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteSRSCfgCommon 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetSrsCfgCommonParameters
(
 MsmLteSRSCfgCommon *lteSRSCfgCommon,
 U16 cellIdx
 )
{
   if(lteSRSCfgCommon == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteSRSCfgCommon = lteeNodeBparams[cellIdx].lteSRSCfgCommon;
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteRabPolicyCfgGrp 
 *
 * @details
 *
 *     Function:msmGetRabPolicyCfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRabPolicyCfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetRabPolicyCfgGrpSrb1Parameters
(
MsmLteRabPolicyCfgGrp *lteRabPolicyCfgGrp,
U16                   cellIdx
)
{  
   if(lteRabPolicyCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   lteRabPolicyCfgGrp->actType = 
      lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.actType;
   lteRabPolicyCfgGrp->srbPolicy[MSM_SRB1] = 
      lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.srbPolicy[MSM_SRB1]; 
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteRabPolicyCfgGrp 
 *
 * @details
 *
 *     Function:msmGetRabPolicyCfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRabPolicyCfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetRabPolicyCfgGrpSrb2Parameters
(
MsmLteRabPolicyCfgGrp *lteRabPolicyCfgGrp,
U16                   cellIdx
)
{
   if(lteRabPolicyCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   lteRabPolicyCfgGrp->actType = 
      lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.actType;
   lteRabPolicyCfgGrp->srbPolicy[MSM_SRB2] = 
      lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.srbPolicy[MSM_SRB2]; 
   RETVALUE(ROK);
}
/** @brief This function is used for getting lteRabPolicyCfgGrp 
 *
 * @details
 *
 *     Function:msmGetRabPolicyCfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRabPolicyCfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetRabPolicyCfgGrpDrbParameters
(
MsmLteRabPolicyCfgGrp *lteRabPolicyCfgGrp,
U16                   cellIdx
)
{
   if(lteRabPolicyCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   U32 idx;
   lteRabPolicyCfgGrp->isDscpEnable = lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.isDscpEnable;
   for(idx = 0; idx < MSM_MAX_QCI; idx++)
   {   
      lteRabPolicyCfgGrp->drbPolicy[idx] = lteeNodeBparams[cellIdx].lteRabPolicyCfgGrp.drbPolicy[idx];
   } 
   RETVALUE(ROK);
}

/** @brief This function is used for getting Ue Timer Constants
 *
 * @details
 *
 *     Function:msmGetUeTimerConstantsParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteUeTimerConstants 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetUeTimerConstantsParameters
(
 MsmLteUeTimerConstants *lteUeTimerConstants,
 U16 cellIdx
 )
{
   if(lteUeTimerConstants == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteUeTimerConstants = lteeNodeBparams[cellIdx].lteUeTimerConstants;
   RETVALUE(ROK);
}
/** @brief This function is used for getting Cell EAID Cfg
 *
 * @details
 *
 *     Function:msmGetCellEaidCfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCellEAIDCfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetCellEaidCfgGrpParameters
(
MsmLteCellEAIDCfgGrp *lteCellEAIDCfgGrp,
U16                  cellIdx
)
{
   if(lteCellEAIDCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }
   *lteCellEAIDCfgGrp = lteeNodeBparams[cellIdx].lteCellEAIDCfgGrp;
   RETVALUE(ROK);
}
/** @brief This function is used for getting Cell Sib9 Cfg
 *
 * @details
 *
 *     Function:msmGetCellSib9CfgGrpParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCellSib9CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetCellSib9CfgGrpParameters
(
 MsmLteCellSib9CfgGrp *lteCellSib9CfgGrp,
 U16 cellIdx
 )
{
   if(lteCellSib9CfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCellSib9CfgGrp = lteeNodeBparams[cellIdx].lteCellSib9CfgGrp;
   RETVALUE(ROK);
}
/** @brief This function is used for getting CQI Periodic Report 
 *
 * @details
 *
 *     Function:msmGetCqiPeriodicReportCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteCQIPeriodicReportCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetCqiPeriodicReportCfgParameters
(
MsmLteCQIPeriodicReportCfg *lteCQIPeriodicReportCfg,
U16                        cellIdx
)
{
   if(lteCQIPeriodicReportCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCQIPeriodicReportCfg = lteeNodeBparams[cellIdx].lteCQIPeriodicReportCfg;
   RETVALUE(ROK);
}
/** @brief This function is used for getting Neigh Freq Cfg 
 *
 * @details
 *
 *     Function:msmGetNeighFreqCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteNeighFreqCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetNeighFreqEutraCfgParameters
(
 MsmLteNeighFreqCfg *lteNeighFreqCfg,
 U16 cellIdx
 )
{
   U16 idx, idx1 = 0;
   if(lteNeighFreqCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {
      lteNeighFreqCfg->actType =
         lteeNodeBparams[cellIdx].lteNeighFreqCfg.actType; 
      lteNeighFreqCfg->numEutraFreq =
         lteeNodeBparams[cellIdx].lteNeighFreqCfg.numEutraFreq; 
      for(idx=0;idx< lteNeighFreqCfg->numEutraFreq;idx++)
      {
         lteNeighFreqCfg->t.addNeighFreq[idx].eutranFreq =
            lteeNodeBparams[cellIdx].lteNeighFreqCfg.t.addNeighFreq[idx].
            eutranFreq;
      }
   }

   RETVALUE(ROK);
}

/** @brief This function is used for getting Neigh Freq Cfg 
 *
 * @details
 *
 *     Function:msmGetTdsCdmaUtranTddFreqParameters
 *
 *         Processing steps:
 *
 * @param[in] lteNeighFreqCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetTdsCdmaUtranTddFreqParameters
(
 MsmLteNeighFreqCfg *lteNeighFreqCfg,
 U16 cellIdx
 )
{  
   U16 idx;
   if(lteNeighFreqCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   lteNeighFreqCfg->actType = lteeNodeBparams[cellIdx].lteNeighFreqCfg.actType; 
   lteNeighFreqCfg->numUtraTddFreq =
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.numUtraTddFreq; 
   lteNeighFreqCfg->maxUtraTddFreqEntries =
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.maxUtraTddFreqEntries; 
   for(idx=0;idx < lteNeighFreqCfg->numUtraTddFreq;idx++)
   {
      lteNeighFreqCfg->t.addNeighFreq[idx].utranTddFreq =
         lteeNodeBparams[cellIdx].lteNeighFreqCfg.t.addNeighFreq[idx].
         utranTddFreq;
   }

   RETVALUE(ROK);
}

/** @brief This function is used for getting Neigh Freq Cfg 
 *
 * @details
 *
 *     Function:msmGetNeighFreqCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteNeighFreqCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetNeighFreqUtraCfgParameters
(
 MsmLteNeighFreqCfg *lteNeighFreqCfg,
 U16 cellIdx
 )
{  
   U16 idx;
   if(lteNeighFreqCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   lteNeighFreqCfg->actType = lteeNodeBparams[cellIdx].lteNeighFreqCfg.actType; 
   lteNeighFreqCfg->numUtraFreq =
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.numUtraFreq; 
   lteNeighFreqCfg->maxUtraFreqEntries =
      lteeNodeBparams[cellIdx].lteNeighFreqCfg.maxUtraFreqEntries; 
   for(idx=0;idx < lteNeighFreqCfg->numUtraFreq;idx++)
   {
      lteNeighFreqCfg->t.addNeighFreq[idx].utranFreq =
         lteeNodeBparams[cellIdx].lteNeighFreqCfg.t.addNeighFreq[idx].utranFreq;
   }

   RETVALUE(ROK);
}

/** @brief This function is used for getting Neigh Cell 
 *
 * @details
 *
 *     Function: msmGetTdsCdmaUtranTddCellParameters
 *
 *         Processing steps:
 *
 * @param[in] lteNeighCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetTdsCdmaUtranTddCellParameters
(
 MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U16 idx,idx1;
   if(lteNeighCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   lteNeighCellCfg->actType =lteeNodeBparams[cellIdx].lteNeighCellCfg.actType; 
   lteNeighCellCfg->maxTddCellEntries =
      lteeNodeBparams[cellIdx].lteNeighCellCfg.maxTddCellEntries;
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {  
      lteNeighCellCfg->numUtraTddCells =
         lteeNodeBparams[cellIdx].lteNeighCellCfg.numUtraTddCells; 
      for(idx = 0; idx < lteNeighCellCfg->numUtraTddCells &&
            lteeNodeBparams[cellIdx].lteNeighCellCfg.numUtraTddCells
            <= MSM_MAX_NUM_NEIGH_CELLS; idx++)
      {  
         lteNeighCellCfg->t.neighAddCfg[idx].utranTddCell =
            lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].
            utranTddCell; 
      }
   } 
   RETVALUE(ROK);
}

/** @brief This function is used for getting Neigh Cell 
 *
 * @details
 *
 *     Function: msmGetNeighborListInUseParameters
 *
 *         Processing steps:
 *
 * @param[in] lteNeighCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetNeighborListInUseUtraParameters
(
 MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U16 idx,idx1;
   if(lteNeighCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {
      lteNeighCellCfg->actType =
         lteeNodeBparams[cellIdx].lteNeighCellCfg.actType; 
      lteNeighCellCfg->maxCellEntries =
         lteeNodeBparams[cellIdx].lteNeighCellCfg.maxCellEntries; 
      lteNeighCellCfg->numUtraCells =
         lteeNodeBparams[cellIdx].lteNeighCellCfg.numUtraCells; 
      for(idx=0;idx< lteNeighCellCfg->numUtraCells &&
            lteeNodeBparams[cellIdx].lteNeighCellCfg.numUtraCells <=
            MSM_MAX_NUM_NEIGH_CELLS; idx++)
      {  
         lteNeighCellCfg->t.neighAddCfg[idx].utranCell =
          lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].utranCell;
      }
   } 
   RETVALUE(ROK);
}

/** @brief This function is used for getting Neigh Cell 
 *
 * @details
 *
 *     Function: msmGetNeighborListInUseEutraParameters
 *
 *         Processing steps:
 *
 * @param[in] lteNeighCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetNeighborListInUseEutraParameters
(
 MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U16 idx;
   if(lteNeighCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   lteNeighCellCfg->maxCellEntries =
      lteeNodeBparams[cellIdx].lteNeighCellCfg.maxCellEntries; 
   lteNeighCellCfg->numEutraCells =
      lteeNodeBparams[cellIdx].lteNeighCellCfg.numEutraCells; 
   for(idx=0;idx< lteNeighCellCfg->numEutraCells && 
         lteeNodeBparams[cellIdx].lteNeighCellCfg.numEutraCells <=
         MSM_MAX_NUM_NEIGH_CELLS;idx++)
   {  
      lteNeighCellCfg->t.neighAddCfg[idx].eutraCell=
         lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].eutraCell; 
   }  
   RETVALUE(ROK);

}

/** @brief This function is used for getting Sib5 InterFreq CarrierInfo 
 *
 * @details
 *
 *     Function: msmGetSib5InterFreqCarrierInfoParameters
 *
 *         Processing steps:
 *
 * @param[in] lteSib5InterFreqCarrierInfo
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetSib5InterFreqCarrierInfoParameters
(
 MsmLteSib5InterFreqCarrierInfo *lteSib5InterFreqCarrierInfo,
 U16 cellIdx
 )
{
   if(lteSib5InterFreqCarrierInfo == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteSib5InterFreqCarrierInfo = lteeNodeBparams[cellIdx].lteSib5InterFreqCarrierInfo;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Cell Sib6 Cfg 
 *
 * @details
 *
 *     Function: msmGetCellSib6ConfigGroupParameters
 *
 *         Processing steps:
 *
 * @param[in] lteCellSib6CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetCellSib6ConfigGroupParameters
(
 MsmLteCellSib6CfgGrp *lteCellSib6CfgGrp,
 U16 cellIdx
 )
{
   if(lteCellSib6CfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCellSib6CfgGrp = lteeNodeBparams[cellIdx].lteCellSib6CfgGrp;
   RETVALUE(ROK);
}
/** @brief This function is used for getting Enb Proto Cfg 
 *
 * @details
 *
 *     Function: msmGetEnbProtoCfgParameters
 *
 *         Processing steps:
 *
 * @param[in] lteEnbProtoCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetEnbProtoCfgParameters(MsmLteEnbProtoCfg *lteEnbProtoCfg,U16 cellIdx)
{
   if(lteEnbProtoCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteEnbProtoCfg = lteeNodeBparams[cellIdx].lteEnbProtoCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Ac BarringInfo 
 *
 * @details
 *
 *     Function: msmGetAcBarringInfoParameters
 *
 *         Processing steps:
 *
 * @param[in] lteAcBarringInfo
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetAcBarringInfoParameters
(
 MsmLteAcBarringInfo *lteAcBarringInfo,
 U16 cellIdx
 )
{
   if(lteAcBarringInfo == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteAcBarringInfo = lteeNodeBparams[cellIdx].lteAcBarringInfo;
   RETVALUE(ROK);
}

/** @brief This function is used for getting EnodebIpAddr 
 *
 * @details
 *
 *     Function: msmGetEnodebIpAddr 
 *
 *         Processing steps:
 *
 * @param[in]lteEnodebIpAddr
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetEnodebIpAddr(MsmEnodebIpAddr *lteEnodebIpAddr)
{
   if(lteEnodebIpAddr == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteEnodebIpAddr = fapParameters.lteEnodebIpAddr; 
   RETVALUE(ROK);
}


/** @brief This function is used for getting EARFCNDL and RSSI scanned by REM
 *
 * @details
 *
 *     Function:msmGetEarfcnRssiParameters
 *
 *         Processing steps:
 *
 * @param[in]lteEarfcnRssiCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetEarfcnRssiParameters
(
 MsmLteEarfcnRssiCfg *lteEarfcnRssiCfg,
 U16 cellIdx
 )
{
   if(lteEarfcnRssiCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteEarfcnRssiCfg = lteeNodeBparams[cellIdx].lteEarfcnRssiCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Self Config Params
 *
 * @details
 *
 *     Function:msmGetSelfConfigParameters
 *
 *         Processing steps:
 *
 * @param[in] lteSelfConfigParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetSelfConfigParameters(MsmLteSonGenericParams *lteSelfConfigParams,U16 cellIdx)
{
   if(lteSelfConfigParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteSelfConfigParams = lteeNodeBparams[cellIdx].lteSonGenericParams;
   RETVALUE(ROK);
}
/** @brief This function is used for getting Rem Scan Parameters 
 *
 * @details
 *
 *     Function:msmGetRemScanParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteRemScanParameters
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetRemScanParameters
(
 MsmLteRemScanParameters *lteRemScanParameters,
 U16 cellIdx
 )
{
   if(lteRemScanParameters == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteRemScanParameters = lteeNodeBparams[cellIdx].lteRemScanParameters;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Power Off set
 *
 * @details
 *
 *     Function: msmGetPowerOffsetParameters
 *
 *         Processing steps:
 *
 * @param[in] ltePowerOffsetParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetPowerOffsetParameters(MsmLtePowerOffsetParams *ltePowerOffsetParams,U16 cellIdx)
{
   if(ltePowerOffsetParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *ltePowerOffsetParams = lteeNodeBparams[cellIdx].ltePowerOffsetParams;
   RETVALUE(ROK);
}

/** @brief This function is used for getting lteFapControlParams 
 *
 * @details
 *
 *     Function: msmGetFapControlParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteFapControlParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetFapControlParameters(MsmLteFapControlParams *lteFapControlParams,U16 cellIdx)
{
   if(lteFapControlParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteFapControlParams = lteeNodeBparams[cellIdx].lteFapControlParams;
   RETVALUE(ROK);
}

/** @brief This function is used for getting PRB allocation 
 *
 * @details
 *
 *     Function:msmGetPrbAllocationParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePRBallocation
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetPrbAllocationParameters(MsmLtePRBallocation *ltePRBallocation, U16 cellIdx)
{
   if(ltePRBallocation == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *ltePRBallocation = lteeNodeBparams[cellIdx].ltePRBallocation;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Sib4 CsgI 
 *
 * @details
 *
 *     Function: msmGetSib4CsgInfoParameters
 *
 *         Processing steps:
 *
 * @param[in] lteSib4CsgInfo
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetSib4CsgInfoParameters
(
 MsmLteSib4CsgInfo *lteSib4CsgInfo,
 U16 cellIdx
 )
{
   if(lteSib4CsgInfo == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteSib4CsgInfo = lteeNodeBparams[cellIdx].lteSib4CsgInfo;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Rrm Tdd Param
 *
 * @details
 *
 *     Function:msmGetRrmTddParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteGenericParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetRrmTddParameters(MsmLteRrmTddParam *lteRrmTddParam, U16 cellIdx)
{
   if(lteRrmTddParam == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteRrmTddParam = lteeNodeBparams[cellIdx].lteRrmTddParam;
   RETVALUE(ROK);
}

/** @brief This function is used for getting X2 Config Params
 *
 * @details
 *
 *     Function: msmGetX2ConfigParameters
 *
 *         Processing steps:
 *
 * @param[in] lteGenericParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

/*PUBLIC S16 msmGetX2ConfigParameters(MsmLteX2ConfigParams *lteX2ConfigParams)
  {
  if(lteX2ConfigParams == NULLP)
  {
  RETVALUE(RFAILED);
  }

 *lteX2ConfigParams = lteeNodeBparams[MSM_SM_DFLT_CELL_INDX].lteX2ConfigParams;
 RETVALUE(ROK);
 }*/

/** @brief This function is used for Sctp Cfg Params
 *
 * @details
 *
 *     Function: msmGetSctpConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteSctpCfgParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetSctpConfigParameters
(
 MsmLteSctpCfgParams *lteSctpCfgParams,
 U16 cellIdx
 )
{
   if(lteSctpCfgParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteSctpCfgParams = lteeNodeBparams[cellIdx].lteSctpCfgParams;
   RETVALUE(ROK);
}

/** @brief This function is used for getting PCCH Cfg 
 *
 * @details
 *
 *     Function:msmGetPcchConfigCommonParameters 
 *
 *         Processing steps:
 *
 * @param[in] ltePCCHCfgCommon
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetPcchConfigCommonParameters
(
 MsmLtePCCHCfgCommon *ltePCCHCfgCommon,
 U16 cellIdx
 )
{
   if(ltePCCHCfgCommon == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *ltePCCHCfgCommon = lteeNodeBparams[cellIdx].ltePCCHCfgCommon;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Cell Ul Schd Cfg 
 *
 * @details
 *
 *     Function:lteCellUlSchdCfgGrp 
 *
 *         Processing steps:
 *
 * @param[in] lteGenericParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetCellUlSchdConfigParameters(MsmLteCellUlSchdCfgGrp *lteCellUlSchdCfgGrp, U16 cellIdx)
{
   if(lteCellUlSchdCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCellUlSchdCfgGrp = lteeNodeBparams[cellIdx].lteCellUlSchdCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Cell DlSchd Cfg 
 *
 * @details
 *
 *     Function:msmGetCellDlSchdConfigParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteCellDlSchdCfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetCellDlSchdConfigParameters
(
 MsmLteCellDlSchdCfgGrp *lteCellDlSchdCfgGrp,
 U16 cellIdx
 )
{
   if(lteCellDlSchdCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteCellDlSchdCfgGrp = lteeNodeBparams[cellIdx].lteCellDlSchdCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Ms Cell Cfg
 *
 * @details
 *
 *     Function:msmGetMsCellCfgReqParameters 
 *
 *         Processing steps:
 *
 * @param[in] MsCellCfgReq 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetMsCellCfgReqParameters
(
 MsmLteMsCellCfgReq *lteMsCellCfgReq,
 U16 cellIdx
 )
{
   if(lteMsCellCfgReq == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteMsCellCfgReq = lteeNodeBparams[cellIdx].lteMsCellCfgReq;
   RETVALUE(ROK);
}

/** @brief This function is used for getting lteDbgParams 
 *
 * @details
 *
 *     Function: msmGetDbgParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteDbgParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetDbgParameters(MsmLteDbgParams *lteDbgParams)
{
   if(lteDbgParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteDbgParams = fapParameters.lteDbgParams;
   RETVALUE(ROK);
}

/** @brief This function is used for getting lteUlAllocInfoCbParams 
 *
 * @details
 *
 *     Function: msmGetUlAllocInfoCbParameters
 *
 *         Processing steps:
 *
 * @param[in] lteGenericParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetUlAllocInfoCbParameters
(
 MsmLteUlAllocInfoCbParams *lteUlAllocInfoCbParams,
 U16 cellIdx
 )
{
   if(lteUlAllocInfoCbParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteUlAllocInfoCbParams = lteeNodeBparams[cellIdx].lteUlAllocInfoCbParams;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Proc Timer Cfg 
 *
 * @details
 *
 *     Function: msmGetProcTimerCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in] lteGenericParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetProcTimerCfgParameters
(
 MsmLteProcTimerCfg *lteProcTimerCfg,
 U16 cellIdx
 )
{
   if(lteProcTimerCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteProcTimerCfg = lteeNodeBparams[cellIdx].lteProcTimerCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Proc Timer Cfg
 *
 * @details
 *
 *     Function: msmGetFactoryFapAccessParameters
 *
 *         Processing steps:
 *
 * @param[in] lteFapAccessParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetFactoryFapAccessParameters
(
 MsmLteFapAccessParams *lteFapAccessParams,
 U16 cellIdx
 )
{
   if(lteFapAccessParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteFapAccessParams = lteeNodeBparams[cellIdx].lteFapAccessParams;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Proc Timer Cfg
 *
 * @details
 *
 *     Function: msmGetFactorySmCellParameters
 *
 *         Processing steps:
 *
 * @param[in] lteSmCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetFactorySmCellParameters
(
 MsmLteSmCellCfg *lteSmCellCfg,
 U16 cellIdx
 )
{
   if(lteSmCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteSmCellCfg = lteeNodeBparams[cellIdx].lteSmCellCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting perf Mgmt Parameters parameters
 *
 * @details
 *
 *     Function: msmGetPmParameters
 *
 *         Processing steps:
 *
 * @param[in] lteGenericParams
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 *rakesh*/

PUBLIC S16 msmGetPmParameters(MsmPerfMgmtParameters *perfMgmtParameters)
{
   if(perfMgmtParameters == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *perfMgmtParameters = wcdmaNodeBparams.perfMgmtParameters;
   RETVALUE(ROK);
}

/** @brief This function is used for getting frequent Fault Mgmt Parameters
 *
 * @details
 *
 *     Function:msmGetFrequentFaultParameters 
 *
 *         Processing steps:
 *
 * @param[in] frequentFaultMgmtParameters
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 *rakesh*/

PUBLIC S16 msmGetFrequentFaultParameters
(
 MsmFrequentFaultMgmtParameters *frequentFaultMgmtParameters
 )
{
   if(frequentFaultMgmtParameters == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *frequentFaultMgmtParameters = faultMgmtParams.frequentFaultMgmtParameters;
   RETVALUE(ROK);
}

/** @brief This function is used for getting cdma Band Class 
 *
 * @details
 *
 *     Function:msmGetCdmaBandClassParameters 
 *
 *         Processing steps:
 *
 * @param[in] cdmaBandClass
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 **/

PUBLIC S16 msmGetCdmaBandClassParameters
(
 MsmCdmaBandClass *cdmaBandClassParams,
 U16 cellIdx
 )
{
   if(cdmaBandClassParams == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *cdmaBandClassParams = lteeNodeBparams[cellIdx].cdmaBandClassParams;
   RETVALUE(ROK);
}

/** @brief This function is used for getting cdma Mobility 
 *
 * @details
 *
 *     Function:msmGetCdmaMobilityParameters 
 *
 *         Processing steps:
 *
 * @param[in] cdmaMobilityParam
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetCdmaMobilityParameters
(
 MsmCdmaMobilityParam *cdmaMobilityParam,
 U16 cellIdx
 )
{
   if(cdmaMobilityParam == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *cdmaMobilityParam = lteeNodeBparams[cellIdx].cdmaMobilityParam;
   RETVALUE(ROK);
}

/** @brief This function is used for 
 *
 * @details
 *
 *     Function:msmGetBarringCfg1xRtt 
 *
 *         Processing steps:
 *
 * @param[in] barringConfig1xRTTCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetBarringCfg1xRtt(MsmBarringConfig1xRTTCfg *barringConfig1xRTTCfg,U16 cellIdx)
{
   if(barringConfig1xRTTCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *barringConfig1xRTTCfg = lteeNodeBparams[cellIdx].barringConfig1xRTTCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting neigh cell cfg 
 *
 * @details
 *
 *     Function: msmGetCdma1XRttNghCell
 *
 *         Processing steps:
 *
 * @param[in]lteNeighCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetCdma1XRttNghCell(MsmNeighCellCfg *lteNeighCellCfg, U16 cellIdx)
{
   U32 idx = 0, idx1 = 0;

   if( cellIdx < MSM_MAX_CELLS )
   {
      if(lteNeighCellCfg == NULLP || 
            lteeNodeBparams[cellIdx].lteNeighCellCfg.numCdma1xCells > MSM_MAX_NUM_NEIGH_CELLS)
      {
         RETVALUE(RFAILED);
      }
      for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx++)
      {
         lteNeighCellCfg->numCdma1xCells =
            lteeNodeBparams[cellIdx].lteNeighCellCfg.numCdma1xCells;

         for(idx = 0; idx < lteNeighCellCfg->numCdma1xCells; idx++)
         {
            lteNeighCellCfg->t.neighAddCfg[idx].cdma1xCell =
               lteeNodeBparams[cellIdx].lteNeighCellCfg.t.neighAddCfg[idx].\
               cdma1xCell;
         }
      }
   }
   else
   {
        RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/** @brief This function is used for getting cell Sib8 Cfg
 *
 * @details
 *
 *     Function:msmGetSib8Parameters 
 *
 *         Processing steps:
 *
 * @param[in] cellSib8CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetSib8Parameters(MsmCellSib8CfgGrp *cellSib8CfgGrp,U16 cellIdx)
{
   if(cellSib8CfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *cellSib8CfgGrp = lteeNodeBparams[cellIdx].cellSib8CfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for getting csfb Cfg Grp
 *
 * @details
 *
 *     Function:msmGetCsfbCfgParameters 
 *
 *         Processing steps:
 *
 * @param[in]csfbCfgGrp 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetCsfbCfgParameters(MsmCsfbCfgGrp *csfbCfgGrp, U16 cellIdx)
{
   if(csfbCfgGrp == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *csfbCfgGrp = lteeNodeBparams[cellIdx].csfbCfgGrp;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Sps Cell Cfg 
 *
 * @details
 *
 *     Function:msmGetSpsParameters 
 *
 *         Processing steps:
 *
 * @param[in]stSpsCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetSpsParameters
(
 MsmSpsCellConfigData *stSpsCellCfg,
 U16 cellIdx
 )
{
   if(stSpsCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *stSpsCellCfg = lteeNodeBparams[cellIdx].stSpsCellCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting eNB Log Level Param 
 *
 * @details
 *
 *     Function:msmGetLogLvlParameter 
 *
 *         Processing steps:
 *
 * @param[in]lteLogLvlCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetLogLvlParameter(MsmEnbLogLvlData *lteLogLvlCfg)
{
   if(lteLogLvlCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteLogLvlCfg = fapParameters.lteLogLvlCfg;
   RETVALUE(ROK);
}

/* TM4 changes*/
/** @brief This function is used for getting Transmission Mode Cfg 
 *
 * @details
 *
 *     Function:msmGetTMParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteTransModeCellCfg 
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetTMParameters(MsmTMCellConfig *lteTransModeCellCfg, U16 cellIdx)
{
   if(lteTransModeCellCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteTransModeCellCfg = lteeNodeBparams[cellIdx].lteTransModeCellCfg;
   RETVALUE(ROK);
}
/** @brief This function is used for getting Tdd parameters 
 *
 * @details
 *
 *     Function: msmGetTddParameters 
 *
 *         Processing steps:
 *
 * @param[in]lteTddParam
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */ 

PUBLIC S16 msmGetTddParameters(MsmLteTddParam *lteTddParam,U16 cellIdx)
{
   if(lteTddParam== NULLP)
   {
      RETVALUE(RFAILED);
   }

   *lteTddParam = lteeNodeBparams[cellIdx].lteTddParam;
   RETVALUE(ROK);
}

/** @brief This function is used for getting ltecellSchdPwrCfg Param 
 *
 * @details
 *
 *     Function:msmGetSchdPwrCfgParameters
 *
 *         Processing steps:
 *
 * @param[in]
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */
PUBLIC S16 msmGetSchdPwrCfgParameters
(
 MsmCellSchdPwrCfg *ltecellSchdPwrCfg,
 U16 cellIdx
 )
{ 
   if(ltecellSchdPwrCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   *ltecellSchdPwrCfg = lteeNodeBparams[cellIdx].ltecellSchdPwrCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting Sib7Cfg Param 
 *
 * @details
 *
 *     Function:msmGetsib7CfgGrpParameters
 *
 *         Processing steps:
 *
 * @param[in]sib7CfgGrp
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetsib7CfgGrpParameters
(
 MsmLteCellSib7CfgGrp *sib7CfgGrp,
 U16 cellIdx
 )
{ 
   if(sib7CfgGrp == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   *sib7CfgGrp = lteeNodeBparams[cellIdx].sib7CfgGrp;
   RETVALUE(ROK);
}


/** @brief This function is used for getting csfbGranCfg Param 
 *
 * @details
 *
 *     Function:msmGetcsfbGeranCfgParameters
 *
 *         Processing steps:
 *
 * @param[in]csfbToGeranCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetcsfbGeranCfgParameters
(
 MsmLteCsfbGeranCfg *csfbToGeranCfg,
 U16 cellIdx
 )
{ 
   if(csfbToGeranCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }

   *csfbToGeranCfg = lteeNodeBparams[cellIdx].csfbToGeranCfg;
   RETVALUE(ROK);
}

/** @brief This function is used for getting NeighFreqCfgGeran Param 
 *
 * @details
 *
 *     Function:msmGetNeighFreqCfgGeranParameters
 *
 *         Processing steps:
 *
 * @param[in]lteNeighFreqCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetNeighFreqCfgGeranParameters
(
 MsmLteNeighFreqCfg *lteNeighFreqCfg,
 U16 cellIdx
 )
{ 
   U16 idx = 0, idx1 = 0;

   if(lteNeighFreqCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {
      lteNeighFreqCfg->actType =
         lteeNodeBparams[cellIdx].lteNeighFreqCfg.actType;
      lteNeighFreqCfg->numGeranFreq =
         lteeNodeBparams[cellIdx].lteNeighFreqCfg.numGeranFreq;
      for(idx=0; idx< (lteNeighFreqCfg->numGeranFreq); idx++)
      {
         lteNeighFreqCfg->t.addNeighFreq[idx].geranFreq =
            lteeNodeBparams[cellIdx].lteNeighFreqCfg.t.addNeighFreq[idx].\
            geranFreq;
      }
   }

   RETVALUE(ROK);
}

/** @brief This function is used for getting Neigh Cell Geran parameters
 *
 * @details
 *
 *     Function:msmGetNeighCellCfgGeranParameters
 *
 *         Processing steps:
 *
 * @param[in] lteNeighCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmGetNeighCellCfgGeranParameters
(
 MsmNeighCellCfg *lteNeighCellCfg,
 U16 cellIdx
 )
{
   U32 idx = 0,idx1=0;

   if(lteNeighCellCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
   for(idx1 = 0; idx1 < MSM_MAX_CELLS; idx1++)
   {
      lteNeighCellCfg->numGeranCells =
         lteeNodeBparams[cellIdx].lteNeighCellCfg.numGeranCells;

      for(idx = 0; idx < lteeNodeBparams[cellIdx].lteNeighCellCfg.numGeranCells;
            idx++)
      {
         lteNeighCellCfg->t.neighAddCfg[idx].geranCell =
            lteeNodeBparams[cellIdx].lteNeighCellCfg.t.\
            neighAddCfg[idx].geranCell;
      }
   }
   RETVALUE(ROK);
}

/** @brief This function is used for setting Num of cells parameters
 *
 * @details
 *
 *     Function:msmSetNumOfCellsParameters
 *
 *         Processing steps:
 *
 * @param[in] lteNeighCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetNumOfCellsParameters
(
   MsmLteEnbProtoCfg *lteEnbProtoCfg,
   U16 cellIdx
)
{

   if(lteEnbProtoCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
  lteeNodeBparams[cellIdx].lteEnbProtoCfg.numOfCells = lteEnbProtoCfg->numOfCells; 
   RETVALUE(ROK);
}/*msmSetNumOfCellsParameters*/

PUBLIC S16 msmSetGostLog(MsmGostLog *lteGostLog)
{
   if(lteGostLog == NULLP)
   {
      RETVALUE(RFAILED);
   }
   lteeNodeBparams[0].lteGostLog=*lteGostLog;
   RETVALUE(ROK);
}

#ifdef TIP_OAM
/** @brief This function is used for setting S1U related parameters
*
* @details
*
*     Function:msmSetS1UParameters
*
*         Processing steps:
*
* @param[in] lteNeighCellCfg
* @return S16
*        -# Success : ROK
*        -# Failure : RFAILED
*/
PUBLIC S16 msmSetS1UParameters
(
   MsmS1UCfg   *s1uCfg
)
{
   if(s1uCfg == NULLP)
   {
      RETVALUE(RFAILED);
   }
   fapParameters.s1uCfg = *s1uCfg;
 
   RETVALUE(ROK);
}
#endif

/** @brief This function is used for setting carrier aggregation related
 * parameters which are isCaEnable flag and isCellFreqContiguity flag
 *
 * @details
 *
 *     Function:msmSetCAParameters
 *
 *         Processing steps:
 *
 * @param[in] lteNeighCellCfg
 * @return S16
 *        -# Success : ROK
 *        -# Failure : RFAILED
 */

PUBLIC S16 msmSetCAParameters
(
   MsmCAGenCfg *caGenCfg,
   U16          cellIdx
)
{

#ifdef LTE_ADV
   if(caGenCfg == NULLP)
   {   
      RETVALUE(RFAILED);
   }
  lteeNodeBparams[cellIdx].caGenCfg.isCaEnabled = caGenCfg->isCaEnabled; 
#ifdef LTE_ADV_UECAP
  lteeNodeBparams[cellIdx].caGenCfg.isCellFreqCont = caGenCfg->isCellFreqCont; 
#endif
#endif
   RETVALUE(ROK);
}/*msmSetNumOfCellsParameters*/

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


