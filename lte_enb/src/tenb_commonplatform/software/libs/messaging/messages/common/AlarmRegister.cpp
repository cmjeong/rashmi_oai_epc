///////////////////////////////////////////////////////////////////////////////
//
// AlarmRegister 
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/NumberConversions.h>
#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "AlarmRegister.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

AlarmRegister::AlarmRegister() : 
    m_alarmId(0),
    m_alarmSeverity(0),
    m_alarmCauseType(0),
    m_alarmCauseVal(0),
    m_additionalInfo(""),
    m_addtnlInfo("")
{
}
AlarmRegister::AlarmRegister( u32 id, 
			      u8 alarmSeverity,
			      u8 alarmCauseType,
 			      u8 alarmCauseVal,
			      char* additionalInfo):
    m_alarmId(id),
    m_alarmSeverity(alarmSeverity),
    m_additionalInfo(additionalInfo),
    m_addtnlInfo(additionalInfo)
    
{
    SetAdditionalInfo(alarmCauseType,alarmCauseVal); // This sets the specific problem of the alarm
	SetAddtnlInfo(alarmCauseType,alarmCauseVal); //This sets the additional information of the alarm
}

const char *AlarmRegister::s1CauseRadioNetwork[] =
{
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

const char *AlarmRegister::s1CauseTransport[] = {
"transport_resource_unavailable",
"transport_unspecified"
};

const char *AlarmRegister::s1CauseNas[] = {
"Nasnormal_release",
"Nasauthentication_failure",
"Nasdetach",
"Nasunspecified"
};

const char *AlarmRegister::s1CauseProtocol[] = {
"Prottransfer_syntax_error",
"Protabstract_syntax_error_reject",
"Protabstract_syntax_error_ignore_and_notify",
"Protmessage_not_compatible_with_receiver_state",
"Protsemantic_error",
"Protabstract_syntax_error_falsely_constructed_message",
"Protunspecified"
};

const char *AlarmRegister::s1CauseMisc[] = {
"Misccontrol_processing_overload",
"Miscnot_enough_user_plane_processing_resources",
"Mischardware_failure",
"Miscom_intervention",
"Miscunspecified",
"Miscunknown_PLMN"
};

const char *AlarmRegister::x2CauseRadioNetwork[] = {
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

const char *AlarmRegister::x2CauseTransport[] = {
"Transport_resource_unavailable",
"Transportunspecified"
};

const char  *AlarmRegister::x2CauseProtocol[] = {
"prottransfer_syntax_errorenum",
"protabstract_syntax_error_rejectenum",
"protabstract_syntax_error_ignore_and_notifyenum",
"protmessage_not_compatible_with_receiver_stateenum",
"protsemantic_errorenum",
"protunspecifiedenum",
"protabstract_syntax_error_falsely_constructed_messageenum"
};

const char  *AlarmRegister::x2CauseMisc[] = {
"Misccontrol_processing_overload",
"Mischardware_failure",
"Miscom_intervention",
"Miscnot_enough_user_plane_processing_resources",
"Miscunspecified"
};

const char *AlarmRegister::configFail[] ={
"Initial_Config_fail_due_to_error",
"Abnormal_Fail_due_to_timer_exp"
};

const char *AlarmRegister::cfgCauseSON[] = {
"PCIList_configured_for_serving_cell_is_empty",
"DLEARFCNList_configured_for_serving_cell_is_empty",
"ULEARFCNList_configured_for_serving_cell_is_empty",
"Prach_configuration_of_List_parameters_are_ empty",
"Configuration_from_SON_Unspecified"
};

const char* AlarmRegister::pciCollision="Pci_Collision";
const char* AlarmRegister::pciConfusion="Pci_Confusion";


s32 AlarmRegister::Serialise(u8* data, u32 dataMaxBytes) const
{
    RSYS_ASSERT(dataMaxBytes >= 128);

    const u8* const dataStart = data;

    SerialiseIt(m_alarmId, data);
    SerialiseIt(m_alarmSeverity, data);
    SerialiseIt(m_alarmCauseType, data);
    SerialiseIt(m_alarmCauseVal, data);
    SerialiseIt(m_additionalInfo, data);
	SerialiseIt(m_addtnlInfo, data);

    return (data - dataStart);
}

bool AlarmRegister::DeSerialise(const u8* data, u32 dataLen)
{
    RSYS_ASSERT(dataLen >= 4);

    DeSerialiseIt(m_alarmId, data);
    DeSerialiseIt(m_alarmSeverity, data);
    DeSerialiseIt(m_alarmCauseType, data);
    DeSerialiseIt(m_alarmCauseVal, data);
    DeSerialiseIt(m_additionalInfo, data, ADDITIONAL_INFO_MAX_LEN);
	DeSerialiseIt(m_addtnlInfo, data, ADDITIONAL_INFO_MAX_LEN);

    return (true);
}

string AlarmRegister::ToString() const
{
    ostringstream stream;

      stream << "alarmId=" << m_alarmId << " \"";
      stream << ", alarmSeverity =" << m_alarmSeverity << " \"" << m_additionalInfo << " \"" <<
      			m_addtnlInfo << " \"" ;

    return (stream.str());
}

//This method actually sets the specific problem of the alarm.
void AlarmRegister::SetAdditionalInfo(u8 alarmCauseType,u8 alarmCauseVal)
{
   char *additionalInfo = NULL;
   additionalInfo = new char[100];
   RSYS_ASSERT(additionalInfo != NULL);
   memset(additionalInfo,'\0',sizeof(char)*100);
   if(additionalInfo == NULL)
   {
      //We should not reach here
      return;
   }

   m_alarmCauseType = alarmCauseType;
   m_alarmCauseVal = alarmCauseVal;		

   if(m_alarmSeverity != ALARM_SEVERITY_CLEARED )
   {
      switch(m_alarmId%MAX_ALARMS)
      {
         case S1_SETUP_FAIL:
         case S1_ERROR_IND:
         case S1_RESET:
            switch(alarmCauseType)
            {
               case S1_CAUSE_RADIO_NW:
                  strcpy(additionalInfo, s1CauseRadioNetwork[alarmCauseVal]);
                  break;
               case S1_CAUSE_TRANSPORT:
                  strcpy(additionalInfo, s1CauseTransport[alarmCauseVal]);
                  break;
               case S1_CAUSE_NAS:
                  strcpy(additionalInfo, s1CauseNas[alarmCauseVal]);
                  break;
               case S1_CAUSE_PROTOCOL:
                  strcpy(additionalInfo, s1CauseProtocol[alarmCauseVal]);
                  break;
               case S1_CAUSE_MISC:
                  strcpy(additionalInfo, s1CauseMisc[alarmCauseVal]);
                  break;
               default:
                  break;
            }
            break;

         case X2_SETUP_FAIL:
         case X2_ERROR_IND :
         case X2_RESET :

            switch(alarmCauseType)
            {

               case X2_CAUSE_RADIO_NW:
                  strcpy(additionalInfo, x2CauseRadioNetwork[alarmCauseVal]);
                  break;
               case X2_CAUSE_TRANSPORT:
                  strcpy(additionalInfo, x2CauseTransport[alarmCauseVal]);
                  break;
               case X2_CAUSE_PROTOCOL:
                  strcpy(additionalInfo, x2CauseProtocol[alarmCauseVal]);
                  break;
               case X2_CAUSE_MISC:
                  strcpy(additionalInfo, x2CauseMisc[alarmCauseVal]);
                  break;
               default:
                  break;
            }
            break;
         case SOCKET_CFG_FAIL:
         case SCTP_CFG_FAIL:
         case S1AP_CFG_FAIL:
         case EGTP_CFG_FAIL:
         case X2AP_CFG_FAIL:
         case RRM_CFG_FAIL:
         case APP_CFG_FAIL:
         case RRC_CFG_FAIL:
         case PDCPUL_CFG_FAIL:
         case PDCPDL_CFG_FAIL:
         case RLCUL_CFG_FAIL:
         case RLCDL_CFG_FAIL:
         case MAC_CFG_FAIL:
         case CL_CFG_FAIL:
         case CELLUP_CFG_FAIL:
         case ADMIN_STATE_CHANGE_FAIL:
         case GENERIC_PRAMS_CFG_FAIL:
         case MME_IP_PRAMS_CFG_FAIL:
         case CELL_CONFIG_PRAMS_FAIL:
         case ENBIP_CFG_FAIL:
         case MIB_CFG_FAIL:
         case PRACH_CFG_FAIL:
         case RACH_CFG_FAIL:
         case PDSCH_CFG_FAIL:
         case SRS_CFG_FAIL:
         case PUSCH_CFG_FAIL:
         case ULPOWER_CFG_FAIL:
         case ULFREQ_CFG_FAIL:
         case PUCCH_CFG_FAIL:
         case UETMRCONS_CFG_FAIL:
         case SIB1_CFG_FAIL:
         case SIB2_CFG_FAIL:
         case SIB3_CFG_FAIL:
         case SIB4_CFG_FAIL:
         case SIB6_CFG_FAIL:
         case SIB9_CFG_FAIL:
         case ANR_CFG_FAIL:
         case MEAS_CFG_FAIL:
         case EAID_CFG_FAIL:
         case SIBSCHED_CFG_FAIL:
         case RABPOLICY_CFG_FAIL:
         case TIMER_CFG_FAIL:
         case RRM_CELL_CFG_FAIL:
         case ULSCHD_CFG_FAIL:
         case DLSCHD_CFG_FAIL:
         case NEIGH_CFG_FAIL:
         case NEIGH_CELL_CFG_FAIL:
         case NEIGH_FREQ_CFG_FAIL:
         case NEIGH_BAND_CLASS_CFG_FAIL:
         case ENB_PROTO_CFG_FAIL:
         case UTRANEIFREQ_CFG_FAIL:
         case EUTRANEIFREQ_CFG_FAIL:
         case UTRANEICELL_CFG_FAIL:
         case EUTRANEICELL_CFG_FAIL:
         case UTRANEILIST_CFG_FAIL:
         case EUTRANEILIST_CFG_FAIL:
         case RABSRB1_CFG_FAIL:
         case RABSRB2_CFG_FAIL:
         case EVNT_NEIGH_ENB_CFG_FAIL:
         case SMCELL_CFG_FAIL:
         case PROCTMR_CFG_FAIL:
            switch(alarmCauseType)
            {
               case ALARM_CAUSE_TYPE_ERR_IND:
               case ALARM_CAUSE_TYPE_TMR_EXP:
                  strcpy(additionalInfo,configFail[alarmCauseVal]);
                  break;
               default:
                  TRACE_PRINTF("Invalid alarmCause\n");
                  break;
            }
            break;

         case CFG_FAIL_FROM_SON:
            switch(alarmCauseType)
            {	
               case CFG_SRV_CELL_FROM_SON_FAIL:
                  strcpy(additionalInfo, cfgCauseSON[alarmCauseVal]);
                  break;
               default:
                  break;
            }
            break;
         case PCI_COLLISION:
            {
               switch(alarmCauseType)
               {
                  case PCI_ALARM_FROM_SON:
                     {
                        strcpy(additionalInfo, pciCollision);
                     }
                     break;

                  default:
                     break;
               }
            }
            break;

         case PCI_CONFUSION:
            {
               switch(alarmCauseType)
               {
                  case PCI_ALARM_FROM_SON:
                     {
                        strcpy(additionalInfo, pciConfusion);
                     }
                     break;
                  default:
                     break;
               }
            }
            break;
         default:	
            strcpy(additionalInfo, "No Specific Cause");
            break;
      }
   }
   else
   {			
      strcpy(additionalInfo, "Specific Cause is not required");
   }
   m_additionalInfo = additionalInfo;

   if(m_additionalInfo.length() > ADDITIONAL_INFO_MAX_LEN)
   {
      // Truncate the additional info.
      m_additionalInfo.resize(ADDITIONAL_INFO_MAX_LEN);
   }
   delete [] additionalInfo;
   additionalInfo = NULL;
}

void AlarmRegister::SetAddtnlInfo(u8 alarmCauseType,u8 alarmCauseVal)
{
   std::stringstream addinfo;
   char* pci, *cellId, *actionType;
   char infostr[200];
   strcpy((char *)infostr,m_addtnlInfo.c_str());
   pci = strtok(infostr,",");
   cellId = strtok(NULL,",");
   actionType = strtok(NULL,",");
   switch(m_alarmId%MAX_ALARMS)
   {
      case PCI_COLLISION:
         {
            addinfo << "Incorrect PCI selected. Need to reconfigure PCI, else eNB wont come up. PCI: "<< pci <<
               "Cell Id: " << cellId << "Action: ";
            if(actionType)
               addinfo << "Automatic Correction";
            else
               addinfo << "Manual Intervention Required";
            break;
         }
      case PCI_CONFUSION:
         {
            addinfo << "Another eNB discovered to have same PCI but is not a direct neighbor. Need to take action to resolve the same. PCI: "<< pci  << "Cell Id: " << cellId << "Action: ";
            if(actionType)
               addinfo << "Automatic Correction";
            else
               addinfo << "Manual Intervention Required";
            break;
         }
      default:
         addinfo<<"";
   }
   m_addtnlInfo = addinfo.str().c_str();
   if(m_addtnlInfo.length() > ADDITIONAL_INFO_MAX_LEN)
   {
      // Truncate the additional info.
      m_addtnlInfo.resize(ADDITIONAL_INFO_MAX_LEN);
   }
}
