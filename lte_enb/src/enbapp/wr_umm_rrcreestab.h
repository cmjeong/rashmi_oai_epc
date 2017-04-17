
/********************************************************************20**

     Name:     EnodeB Application

     Type:     C include file

     Desc:     This file contains 
               

     File:     wr_umm_rrcreestab.h

     Sid:      $SID$ 

     Prg:      Sriky 

*********************************************************************21*/
#ifndef __WR_UMM_RRCREESTAB_H__
#define __WR_UMM_RRCREESTAB_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */

#define WR_UMM_REESTAB_INITED          0
#define WR_UMM_REESTAB_REJECTED        1
#define WR_UMM_REESTAB_ACCEPTED        2
#define WR_UMM_REESTAB_CMPL_RCVD       3
#define WR_UMM_REESTAB_RRC_CFG_DONE    4
#define WR_UMM_REESTAB_DONE            5
#define WR_UMM_REESTAB_ERROR           6
#define WR_UMM_RRC_RESTB_CFG_FAIL      0x00
#define WR_UMM_RRC_RESTB_CFG_SUCC      0x01
#define WR_UMM_RRC_RESTB_SCH_CFG_DONE  0x02
#define WR_UMM_RRC_RESTB_L1_CFG_DONE   0x04
#define WR_UMM_RRC_RESTB_RRC_CFG_DONE  0x08
#define WR_UMM_RRC_RESTB_CFG_DONE      0x0F



#define WR_UMM_NEW_RNTI_RRC_UPDT            0x01
#define WR_UMM_NEW_RNTI_SCH_UPDT            0x02
#define WR_UMM_NEW_RNTI_PHY_UPDT            0x04
#define WR_UMM_NEW_RNTI_RRM_UPDT            0x08
#define WR_UMM_NEW_RNTI_UPDT_DONE      (WR_UMM_NEW_RNTI_RRC_UPDT | WR_UMM_NEW_RNTI_SCH_UPDT | \
                                        WR_UMM_NEW_RNTI_PHY_UPDT | WR_UMM_NEW_RNTI_RRM_UPDT)

/** 
 * @brief Structure declarations and definitions for 
 * RRC RE-ESTABLISH tranactions CB.
 *
 * @details These are the structure members
   -U8          state
   -U8          rabCfmReceived 
   -U8          rabSchCfg[WR_MAX_DRBS]
   -U16         newRnti - New CRNTI Value 
   -TknStrOSXL  *nasPdu 
   -Bool        UeschCfg - Ue Re-Configuration status
   -Bool        eRabSchCfg - eRAB Re-Configuration Status
   -Bool        reConfigState

 */
typedef struct wrRrcReEstabTransCb {
   U8            state;
   U8            rabCfmReceived;
   U8            rabSchCfg[WR_MAX_DRBS];
   U16           newRnti;
   TknStrOSXL    *nasPdu;
   Bool          UeschCfg;
   Bool          eRabSchCfg;
   Bool          reConfigState;
   U8            schdUeCfgState;
   U8            schdUeRstState;
   U8            curCfgRes;
   U8          reestabCause;
   U8          rejectCause; /* Cause for Rejecting Re-establishment */
   U8          phyCfgState;
   U8          ueRntiUpdtFlg;
#ifdef TENB_AS_SECURITY
   WrUeSecCfg    secCfg;
#endif
   WrUmmMeasGapStatus   measGapStatus;
   U8          isUeCtxtRelDefrd;
#ifdef LTE_ADV
   /* Wheather Scells are added or not*/
   Bool          sCellState;
#endif
}WrRrcReEstabTransCb;

EXTERN S16 wrUmmRrcReestabSchUeReset(U32  transId,U16   cellId,
                      U16   oldRnti);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of __WR_UMM_RRCREESTAB_H__ */

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
