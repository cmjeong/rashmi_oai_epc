

/********************************************************************20**
  
     Name:     Fault Management Module
  
     Type:     
  
     Desc:     
  
     File:     wr_alarm_cause.h 
  
     Sid:      wr_alarm_cause.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Thu Jul 25 15:33:14 2013
  
     Prg:      pagarwal 

*********************************************************************21*/
 
#ifndef __WR_ALARM_CAUSE_H__
#define __WR_ALARM_CAUSE_H__

#ifdef __cplusplus
extern "C" {
#endif /* end of __cplusplus */
 
/** @brief defines radio network cause for S1 **/
CONSTANT S8 *s1CauseRadioNetwork[] = {
"RadioNwunspecified",
"RadioNwtx2relocoverall_expiry",
"RadioNwsuccessful_handover",
"RadioNwrelease_due_to_eutran_generated_reason",
"RadioNwhandover_cancelled",
"RadioNwpartial_handover",
"RadioNwho_failure_in_target_EPC_eNB_or_target_system",
"RadioNwho_target_not_allowed",
"RadioNwtS1relocoverall_expiry",
"RadioNwtS1relocprep_expiry",
"RadioNwcell_not_available",
"RadioNwunknown_targetID",
"RadioNwno_radio_resources_available_in_target_cell",
"RadioNwunknown_mme_ue_s1ap_id",
"RadioNwunknown_enb_ue_s1ap_id",
"RadioNwunknown_pair_ue_s1ap_id",
"RadioNwhandover_desirable_for_radio_reason",
"RadioNwtime_critical_handover",
"RadioNwresource_optimisation_handover",
"RadioNwreduce_load_in_serving_cell",
"RadioNwuser_inactivity",
"RadioNwradio_connection_with_ue_lost",
"RadioNwload_balancing_tau_required",
"RadioNwcs_fallback_triggered",
"RadioNwue_not_available_for_ps_service",
"RadioNwradio_resources_not_available",
"RadioNwfailure_in_radio_interface_procedure",
"RadioNwinvalid_qos_combination",
"RadioNwinterrat_redirection",
"RadioNwinteraction_with_other_procedure",
"RadioNwunknown_E_RAB_ID",
"RadioNwmultiple_E_RAB_ID_instances",
"RadioNwencryption_and_or_integrity_protection_algorithms_not_supported",
"RadioNws1_intra_system_handover_triggered",
"RadioNws1_inter_system_handover_triggered",
"RadioNwx2_handover_triggered"
};

/** @brief defines transport cause for S1 **/
CONSTANT S8 *s1CauseTransport[] = {
"transport_resource_unavailable",
"transport_unspecified"
};

/** @brief defines NAS cause for S1 **/
CONSTANT S8 *s1CauseNas[] = {
"Nasnormal_release",
"Nasauthentication_failure",
"Nasdetach",
"Nasunspecified"
};

/** @brief defines Protocol cause for S1 **/
CONSTANT S8 *s1CauseProtocol[] = {
"Prottransfer_syntax_error",
"Protabstract_syntax_error_reject",
"Protabstract_syntax_error_ignore_and_notify",
"Protmessage_not_compatible_with_receiver_state",
"Protsemantic_error",
"Protabstract_syntax_error_falsely_constructed_message",
"Protunspecified"
};

/** @brief defines miscellaneous cause for S1 **/
CONSTANT S8 *s1CauseMisc[] = {
"Misccontrol_processing_overload",
"Miscnot_enough_user_plane_processing_resources",
"Mischardware_failure",
"Miscom_intervention",
"Miscunspecified",
"Miscunknown_PLMN"
};

/** @brief defines radio network cause for X2 **/
CONSTANT S8 *x2CauseRadioNetwork[] = {
"RadioNwhandover_desirable_for_radio_reasons",
"RadioNwtime_critical_handover",
"RadioNwresource_optimisation_handover",
"RadioNwreduce_load_in_serving_cell",
"RadioNwpartial_handover",
"RadioNwunknown_new_eNB_UE_X2AP_ID",
"RadioNwunknown_old_eNB_UE_X2AP_ID",
"RadioNwunknown_pair_of_UE_X2AP_ID",
"RadioNwho_target_not_allowed",
"RadioNwtx2relocoverall_expiry",
"RadioNwtrelocprep_expiry",
"RadioNwcell_not_available",
"RadioNwno_radio_resources_available_in_target_cell",
"RadioNwinvalid_MME_GroupID",
"RadioNwunknown_MME_Code",
"RadioNwencryption_and_or_integrity_protection_algorithms_not_supported",
"RadioNwreportCharacteristicsEmpty",
"RadioNwnoReportPeriodicity",
"RadioNwexistingMeasurementID",
"RadioNwunknown_eNB_Measurement_ID",
"RadioNwmeasurement_temporarily_not_available",
"RadioNwunspecified",
"RadioNwload_balancing",
"RadioNwhandover_optimisation",
"RadioNwvalue_out_of_allowed_range",
"RadioNwmultiple_E_RAB_ID_instances",
"RadioNwswitch_off_ongoing",
"RadioNwnot_supported_QCI_value"
};

/** @brief defines transport cause for X2 **/
CONSTANT S8 *x2CauseTransport[] = {
"Transport_resource_unavailable",
"Transportunspecified"
};

/** @brief defines Protocol cause for X2 **/
CONSTANT S8 *x2CauseProtocol[] = {
"prottransfer_syntax_errorenum",
"protabstract_syntax_error_rejectenum",
"protabstract_syntax_error_ignore_and_notifyenum",
"protmessage_not_compatible_with_receiver_stateenum",
"protsemantic_errorenum",
"protunspecifiedenum",
"protabstract_syntax_error_falsely_constructed_messageenum"
};

/** @brief defines miscellaneous cause for X2 **/
CONSTANT S8 *x2CauseMisc[] = {
"Misccontrol_processing_overload",
"Mischardware_failure",
"Miscom_intervention",
"Miscnot_enough_user_plane_processing_resources",
"Miscunspecified"
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif/* __WR_ALARM_CAUSE_H__*/

/********************************************************************30**

         End of file:     wr_alarm_cause.h@@/main/Br_Tenb_RTLinux_Intg/Br_Tenb_Mspd_T2K_Intg/Br_Tenb_Mspd_T2K_Intg_MS8.0_RC/1 - Thu Jul 25 15:33:14 2013

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
     -   ---     
*********************************************************************91*/ 
