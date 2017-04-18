
/**********************************************************************

     Name:     LTE RRC Layer

     Type:     C extern file

     Desc:     Contains extern definitions for LTE RRC ASN1.C database

     File:     nh_db.x

     Sid:      nhac_db.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:18:32 2015

     Prg:      chebli 

**********************************************************************/
#ifndef __NHACDBX__
#define __NHACDBX__



#ifdef __cplusplus
EXTERN "C" {
#endif
EXTERN CmPAsnElmDef *nhUL_CCCH_Pdu_r9[];
EXTERN CmPAsnElmDef *nhUL_DCCH_Pdu_r9[];
EXTERN CmPAsnElmDef *nhDL_CCCH_Pdu_r9[];
EXTERN CmPAsnElmDef *nhDL_DCCH_Pdu_r9[];
EXTERN CmPAsnElmDef *nhPCCH_Pdu_r9[];
EXTERN CmPAsnElmDef *nhBCCH_BCH_Pdu_r9[];
EXTERN CmPAsnElmDef *nhBCCH_DL_SCH_Pdu_r9[];
EXTERN CmPAsnElmDef *nhUE_EUTRA_Cap_Pdu_r9[];
EXTERN CmPAsnElmDef *nhHovrCmd_Pdu_r9[];
EXTERN CmPAsnElmDef *nhHovrPrepInfo_Pdu_r9[];
EXTERN CmPAsnElmDef *nhUERadioAccessCapInfo_Pdu_r9[];
EXTERN CmPAsnElmDef *nhUECapInfo_Pdu_r9[];
#ifdef NHU_VER2
EXTERN CmPAsnElmDef *nhVarShortMAC_Input_Pdu_r9[];
#endif /* NHU_VER2 */

EXTERN CmPAsnElmDef *nhUL_CCCH_Pdu_r11[];
EXTERN CmPAsnElmDef *nhUL_DCCH_Pdu_r11[];
EXTERN CmPAsnElmDef *nhDL_CCCH_Pdu_r11[];
EXTERN CmPAsnElmDef *nhDL_DCCH_Pdu_r11[];
EXTERN CmPAsnElmDef *nhPCCH_Pdu_r11[];
EXTERN CmPAsnElmDef *nhBCCH_BCH_Pdu_r11[];
EXTERN CmPAsnElmDef *nhBCCH_DL_SCH_Pdu_r11[];
EXTERN CmPAsnElmDef *nhUE_EUTRA_Cap_Pdu_r11[];
EXTERN CmPAsnElmDef *nhHovrCmd_Pdu_r11[];
EXTERN CmPAsnElmDef *nhHovrPrepInfo_Pdur_r11[];
EXTERN CmPAsnElmDef *nhUERadioAccessCapInfo_Pdu_r11[];
EXTERN CmPAsnElmDef *nhUECapInfo_Pdu_r11[];
#ifdef NHU_VER2
EXTERN CmPAsnElmDef *nhVarShortMAC_Input_Pdu_r11[];
#endif /* NHU_VER2 */
#ifdef __cplusplus
}
#endif


#endif /* __NHDBX__ */

/**********************************************************************
         End of file:     nhac_db.x@@/main/TeNB_Main_BR/tenb_main_ccb/1 - Wed Jul 22 20:18:32 2015
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**

   ver       pat      init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      chebli           1. LTE RRC Initial Release.
/main/2      ---      chebli           1. RRC Release 2.1.
/main/3      ---      sbalakrishna     1. Updated for Release of 3.1.
*********************************************************************91*/

