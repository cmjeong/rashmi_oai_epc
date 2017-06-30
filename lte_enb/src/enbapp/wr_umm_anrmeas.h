
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_anrmeas.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/

#ifndef __WR_UMM_ANRMEAS_H__
#define __WR_UMM_ANRMEAS_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

#define WR_UMM_ANR_MEAS_TRANS_INPROG   1
#define WR_UMM_ANR_MEAS_TRANS_DONE     2

/** @brief This Enum used for Anr Measurement Type.
 */
typedef enum wrUmmAnrMeasCfgInfo
{
  WR_UMM_NOT_CONFIGED = 1,
  WR_UMM_CONFIGED
}WrUmmAnrMeasCfgInfo;

/** @brief This structure used to store ANR measurement Transaction 
 * configuration in Transaction control block.

 -  U8          transId                 Transaction identifier
 -  U8                     transState Transaction state
 -  U32                    anrPrdRptCnt ANR Periodic Report count
 -  Bool                   isDrxReqForRptCgi Drx flag for Report CGI
 -  Bool                   isDrxCfged Is DRX configred
 -  WrUmmMeasRmvInfo       rmvMeasInfo remove List information
 -  WrUmmMeasAddInfo       addMeasInfo Add list information
 -  WrUmmMeasGapInfo       gapMeasInfo Gap related information 
 -  WrDrxCfg               ueDrxCfg Ue DRX Config 
 -  WrDrxCfg               *drxCfgPtr Pointer to DrxConfig  
 -  NhuDatReqSdus          rrcReCfgMsg  RRC reconfig Message Pointer
*/ 
typedef struct wrUmmAnrMeasTranInfo
{
    WrUmmMeasTransInfo       measTransCfg;
    U32                      anrPrdRptCnt; 
    Bool                     isDrxReqForRptCgi;
    Bool                     isDrxCfged;
    Bool                     isReCfgSent;
    Bool                     closeTrns;
    WrDrxCfg                 ueDrxCfg; 
    WrDrxCfg                 *drxCfgPtr; 
} WrUmmAnrMeasTransInfo;

#if 0
/*Removed can be deleted */
/*DRX QCI*/
/** @brief This Enum used for setting initial state of ANR 
       when ANR module receive the DRX QCI internal message
       from UMM module.
 */
typedef enum wrUmmEvntAnrInitialDrxQciState
{
  EVNT_INITIAL_NONE,
  NEW_TRANS_RLS_EVNT_ANR_MEAS_CFG,
  EVNT_WAIT_DRX_SCH_CFG_CFM,
  EVNT_WAIT_FOR_CGI_DRX_CFG_RRC_CMPL,
  EVNT_WAIT_FOR_CGI_RPT_FRM_UE,
  EVNT_WAIT_FOR_DRX_RLS_RRC_CMPL_ANR_SCH_CFGM
  
}WrUmmEvntAnrInitialDrxQciState;

/** @brief This Enum used for setting current state of ANR 
       during the ANR and DRX release procedure.
 */
typedef enum wrUmmEvntAnrDrxQciState
{
   EVNT_STATE_NONE,
   EVNT_MEAS_RLS_RRC_CFG_SENT_TO_UE,
   EVNT_DRX_RLS_SENT_TO_SCH,
   EVNT_MEAS_DRX_RLS_CFG_SENT_TO_UE,
   EVNT_DRX_RLS_RRC_CFG_SENT_TO_UE
   
}WrUmmEvntAnrDrxQciState;
#endif
/** @brief This structure used to store Event ANR measurement Transaction 
 *  configuration in Transaction control block.
 *
 * -  U8                     transId    Transaction identifier
 * -  U8                     transState Transaction state
 * -  Bool                   isDrxReqForRptCgi Drx flag for Report CGI
 * -  Bool                   isDrxCfged is DRX configured 
 * -  WrUmmMeasRmvInfo       rmvMeasInfo remove List information
 * -  WrUmmMeasAddInfo       addMeasInfo Add list information
 * -  WrUmmMeasGapInfo       gapMeasInfo Gap related information 
 * -  NhuDatReqSdus          rrcReCfgMsg  RRC reconfig Message Pointer
 * */ 
typedef struct wrUmmEventAnrTransInfo
{
   WrUmmMeasTransInfo       measTransCfg;
   Bool                     isDrxReqForRptCgi;
   Bool                     isDrxCfged;
   Bool                     isReCfgSent;
   Bool                     closeTrns;
   WrDrxCfg                 ueDrxCfg; 
   WrDrxCfg                 *drxCfgPtr; 
} WrUmmEventAnrTransInfo;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __WR_UMM_ANRMEAS_H__ */

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
