

/**********************************************************************

     Name:     LTE UE Simulator

     Type:     C extern file

     Desc:     Contains extern definitions for LTE UE Simulator ASN1.C database
               This file is to be same as nh_db.x file of LTE RRC. Updates to
               LTE RRC file should be reflected here.

     File:     ue_nh_db.x

     Sid:      ue_nh_db.x@@/main/1 - Sun Mar 28 22:59:25 2010

     Prg:      vp

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
/* ue005.101: Added support for UeCapability */
/* ue008.101: Added support for  HandOver and Radio 
 * access capability And Removed UE_RAD_CAP flag*/
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
         End of file:     ue_nh_db.x@@/main/1 - Sun Mar 28 22:59:25 2010
**********************************************************************/
/**********************************************************************

        Revision history:

**********************************************************************/
/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
/main/1      ---      vp        1.Initial Release.
/main/1+   ue005.101  cshekar   1. Added support for ue capability.
/main/1+   ue008.101  ragrawal  1. Added support for HandOver and Radio
                                   access capability And Removed UE_RAD_CAP flag.
*********************************************************************91*/
