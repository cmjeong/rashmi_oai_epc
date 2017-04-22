

/**********************************************************************

     Name:     LTE RRC Layer

     Type:     C extern file

     Desc:     Contains extern definitions for LTE RRC ASN1.C database

     File:     nh_db.x

     Sid:      nh_db.x@@/main/3 - Fri Jul  1 01:13:11 2011

     Prg:      chebli 

**********************************************************************/
#ifndef __NHDBX__
#define __NHDBX__



#ifdef __cplusplus
EXTERN "C" {
#endif
EXTERN CmPAsnElmDef *nhUL_CCCH_Pdu[];
EXTERN CmPAsnElmDef *nhUL_DCCH_Pdu[];
EXTERN CmPAsnElmDef *nhDL_CCCH_Pdu[];
EXTERN CmPAsnElmDef *nhDL_DCCH_Pdu[];
EXTERN CmPAsnElmDef *nhPCCH_Pdu[];
EXTERN CmPAsnElmDef *nhBCCH_BCH_Pdu[];
EXTERN CmPAsnElmDef *nhBCCH_DL_SCH_Pdu[];
EXTERN CmPAsnElmDef *nhUE_EUTRA_Cap_Pdu[];
EXTERN CmPAsnElmDef *nhHovrCmd_Pdu[];
EXTERN CmPAsnElmDef *nhHovrPrepInfo_Pdu[];
EXTERN CmPAsnElmDef *nhUERadioAccessCapInfo_Pdu[];
EXTERN CmPAsnElmDef *nhUECapInfo_Pdu[];
#ifdef NHU_VER2
EXTERN CmPAsnElmDef *nhVarShortMAC_Input_Pdu[];
#endif /* NHU_VER2 */

/* SPS changes starts */
EXTERN CmPAsnElmDef *nhUERadioAccessCap9A0Info_Pdu[];
/* SPS changes ends */

#ifdef __cplusplus
}
#endif


#endif /* __NHDBX__ */

/**********************************************************************
         End of file:     nh_db.x@@/main/3 - Fri Jul  1 01:13:11 2011
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

