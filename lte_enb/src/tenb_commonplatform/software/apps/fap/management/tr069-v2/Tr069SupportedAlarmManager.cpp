///////////////////////////////////////////////////////////////////////////////
//
// Tr069SupportedAlarmManager
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <system/Trace.h>
#include <system/AlarmEvent.h>
#include <platform/FapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069SupportedAlarmManager.h"
#include "Tr069CurrentAlarmManager.h"
#include "Tr069MultiInstanceMibObjectManager.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

SupportedAlarmManager::SupportedAlarmManager( MibAccessInterface& mib, SendMessageInterface &messenger ) :
            m_mib(mib),
            m_messenger(messenger),
            m_currentAlarmManager(mib,messenger)
{
    string vendor("Radisys");

    if( vendor == "Radisys" )
    {
        TRACE_PRINTF("Gateway vendor: Radisys");
        const MappedSupportedAlarm supportedAlarms[] =
        {
		// Existing alarms
		{
                        FapAlarmId::LOGGED_ASSERTION_FAILURE,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Logged Assertion Failure", "",
                                ALARM_PERCEIVED_SEVERITY_WARNING, ALARM_REPORTING_MECHANISM_LOGGED
                        }
                },
		{
                        FapAlarmId::FAP_BOOT_EVENT,
                        {
                                ALARM_EVENT_TYPE_EQUIPMENT_FAILURE,
                                "FAP Boot event", "",
                                ALARM_PERCEIVED_SEVERITY_WARNING, ALARM_REPORTING_MECHANISM_LOGGED
                        }
                },
                // LTE ALARMS
		{
                        FapAlarmId::LTE_CONFIGURATION_PLAN_ERROR,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Critical Configuration Plan Error", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::LTE_CONFIGURATION_PLAN_INCONSISTENCY,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Configuration Plan Inconsistency", "",
                                ALARM_PERCEIVED_SEVERITY_MINOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::LTE_FREQUENCY_SYNCHRONISATION_FAILURE,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Frequency Synchronization Failure", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::LTE_NTP_SERVER_NOT_RESPONDING,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "NTP Server Not Responding", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::LTE_OSCILLATOR_STABILITY_PROBLEM,
                        {
                                ALARM_EVENT_TYPE_EQUIPMENT_FAILURE,
                                "Oscillator Stability Problem", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::LTE_FAP_TEMPERATURE_OVER_THRESHOLD,
                        {
                                ALARM_EVENT_TYPE_ENVIRONMENT_FAILURE,
                                "FAP Temperature Above Threshold", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PCI_CONFLICT,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "PCI conflict", "",
                                ALARM_PERCEIVED_SEVERITY_WARNING, ALARM_REPORTING_MECHANISM_LOGGED
                        }
                },
                {
                        FapAlarmId::LTE_LOW_QUALITY_CHANNEL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Low Quality LTE channel", "",
                                ALARM_PERCEIVED_SEVERITY_WARNING, ALARM_REPORTING_MECHANISM_LOGGED
                        }
                },
                {
                        FapAlarmId::LTE_NETWORK_JITTER,
                        {
                                ALARM_EVENT_TYPE_QUALITY_OF_SERVICE,
                                "Network Jitter", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::S1_SETUP_FAIL,
                        {
                                ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,
                                "S1 Setup failure", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::X2_SETUP_FAIL,
                        {
                                ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,
                                "X2 Setup failure", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::LTE_MEMORY_ALLOCATION_FAIL,
                        {
                                ALARM_EVENT_TYPE_EQUIPMENT_FAILURE,
                                "Memory allocation failure", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SCTP_LINK_FAIL,
                        {
                                ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,
                                "SCTP link failure", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::TNL_SETUP_FAIL,
                        {
                                ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,
                                "User Plane TNL link failure", "",
                                ALARM_PERCEIVED_SEVERITY_WARNING, ALARM_REPORTING_MECHANISM_LOGGED
                        }
                },
                {
                        FapAlarmId::S1_ERROR_IND,
                        {
                                ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,
                                "Frequent S1 Error Indications from MME", "",
                                ALARM_PERCEIVED_SEVERITY_WARNING, ALARM_REPORTING_MECHANISM_LOGGED
                        }
                },
                {
                        FapAlarmId::S1_RESET,
                        {
                                ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,
                                "Frequent S1 Resets from MME", "",
                                ALARM_PERCEIVED_SEVERITY_MINOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::X2_ERROR_IND,
                        {
                                ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,
                                "Frequent X2 Error Indications from Neighbour", "",
                                ALARM_PERCEIVED_SEVERITY_WARNING, ALARM_REPORTING_MECHANISM_LOGGED
                        }
                },
                {
                        FapAlarmId::X2_RESET,
                        {
                                ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,
                                "Frequent X2 Resets from Neighbour", "",
                                ALARM_PERCEIVED_SEVERITY_MINOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SOCKET_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for TUCL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SOCKET_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for TUCL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SCTP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for SCTP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SCTP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SCTP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::S1AP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for S1AP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::S1AP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for S1AP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EGTP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for EGTP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EGTP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for EGTP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::X2AP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for X2AP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::X2AP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for X2AP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RRM_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for RRM during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RRM_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RRM during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::APP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for APP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::APP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for APP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RRC_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for RRC during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RRC_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RRC during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PDCPUL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for PDCPUL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PDCPUL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for PDCPUL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PDCPDL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for PDCPDL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PDCPDL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for PDCPDL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RLCUL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for RLCUL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RLCUL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RLCUL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RLCDL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for RLCDL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RLCDL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RLCDL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::MAC_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for MAC during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::MAC_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for MAC during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::CL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for CL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::CL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for CL during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::CELLUP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry for CELLUP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::CELLUP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for CELLUP during static config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ADMIN_STATE_CHANGE_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for Admin state dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ADMIN_STATE_CHANGE_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for Admin state dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::GENERIC_PRAMS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for Generic params dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::GENERIC_PRAMS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for Generic params dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::MME_IP_PRAMS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for MME IP dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::MME_IP_PRAMS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for MME IP dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::CELL_CONFIG_PRAMS_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for cell params dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::CELL_CONFIG_PRAMS_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for cell params dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ENBIP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for ENBIP dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ENBIP_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for ENBIP dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::MIB_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for MIB dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::MIB_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for MIB dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PRACH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for RACH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PRACH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for PRACH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RACH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for RACH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RACH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RACH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PDSCH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for PDSCH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PDSCH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for PDSCH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SRS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SRS dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SRS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SRS dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PUSCH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for PUSCH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PUSCH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for PUSCH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ULPOWER_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for UL power dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ULPOWER_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for UL power dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ULFREQ_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for UL freq dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ULFREQ_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for UL freq dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PUCCH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for PUCCH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PUCCH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for PUCCH dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::UETMRCONS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for UE timer dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::UETMRCONS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for UE timer dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB1_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SIB1 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB1_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SIB1 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB2_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SIB2 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB2_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SIB2 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB3_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SIB3 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB3_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SIB3 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB4_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SIB4 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB4_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SIB4 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB6_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SIB6 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB6_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SIB6 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB9_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SIB9 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIB9_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SIB9 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ANR_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for ANR dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ANR_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for ANR dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::MEAS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for MEAS dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::MEAS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for MEAS dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EAID_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for EAID dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EAID_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for EAID dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIBSCHED_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SIB sched dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SIBSCHED_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SIB sched dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RABPOLICY_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for RAB policy dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RABPOLICY_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RAB policy dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::TIMER_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for timer dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::TIMER_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for timer dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RRM_CELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for RRM cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RRM_CELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RRM cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ULSCHD_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for UL sched dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ULSCHD_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for UL sched dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::DLSCHD_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for DL sched dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::DLSCHD_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for DL sched dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::NEIGH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for Neigh dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::NEIGH_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for Neigh dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::NEIGH_CELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for Neigh cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::NEIGH_CELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for Neigh cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::NEIGH_FREQ_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for Neigh freq dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::NEIGH_FREQ_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for Neigh freq dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::NEIGH_BAND_CLASS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for band class dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::NEIGH_BAND_CLASS_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for band class dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ENB_PROTO_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for ENB proto dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::ENB_PROTO_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for ENB proto dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::UTRANEIFREQ_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for UTRA Neigh freq dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::UTRANEIFREQ_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for UTRA neigh freq dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EUTRANEIFREQ_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for EUTRA neigh freq dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EUTRANEIFREQ_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for EUTRA Neigh freq dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::UTRANEICELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for UTRA Neigh cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::UTRANEICELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for UTRA Neigh cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EUTRANEICELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for EUTRA Neigh cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EUTRANEICELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for EUTRA Neigh cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::UTRANEILIST_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for UTRA Neigh list dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::UTRANEILIST_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for UTRA Neigh list dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EUTRANEILIST_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for EUTRA Neigh list dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EUTRANEILIST_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for EUTRA Neigh list dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RABSRB1_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for RAB SRB1 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RABSRB1_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RAB SRB1 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RABSRB2_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for RAB SRB2 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::RABSRB2_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for RAB SRB2 dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EVNT_NEIGH_ENB_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for Neigh ENB dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::EVNT_NEIGH_ENB_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for Neigh ENB dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SMCELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for SM Cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::SMCELL_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for SM cell dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PROCTMR_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Timer expiry  for Proc Timer dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PROCTMR_CFG_FAIL,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Config fail for Proc Timer dynamic config", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::CFG_FAIL_FROM_SON,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "Serving Cell Configuration Failure", "",
                                ALARM_PERCEIVED_SEVERITY_MAJOR, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PCI_COLLISION,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "PCI Collision Detected at SON", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
                {
                        FapAlarmId::PCI_CONFUSION,
                        {
                                ALARM_EVENT_TYPE_PROCESSING_FAILURE,
                                "PCI Confusion Detected at SON", "",
                                ALARM_PERCEIVED_SEVERITY_CRITICAL, ALARM_REPORTING_MECHANISM_EXPEDITED
                        }
                },
        };

         u32 numCell =1;
         string numCellStr = getConfigParam("OAM_NUM_CELL_ENTRIES", "");
         if(NULL != numCellStr.c_str())
         {
         	numCell = (u16)atoi(numCellStr.c_str());
         }
			/*Kwork Fix */
			if(numCell > 10000000)
				return;

        	for(u32 cellId = 0;cellId < numCell;cellId++)
        	{
            for(u32 i = 0; i < (sizeof(supportedAlarms)/sizeof(supportedAlarms[0])); ++i)
            {
                MibAttributeValues attr;
                attr.AddAttribute(PARAM_ID_FAP_ALARM_ID, u32(supportedAlarms[i].alarmId + cellId*FapAlarmId::MAX_ALARMS));
                attr.AddAttribute(PARAM_ID_ALARM_EVENT_TYPE, u32(supportedAlarms[i].alarm.eventType));
                attr.AddAttribute(PARAM_ID_ALARM_PROBABLE_CAUSE, string(supportedAlarms[i].alarm.probableCause));
                attr.AddAttribute(PARAM_ID_ALARM_SPECIFIC_PROBLEM, string(supportedAlarms[i].alarm.specificProblem));
                attr.AddAttribute(PARAM_ID_ALARM_PERCEIVED_SEVERITY, u32(supportedAlarms[i].alarm.perceivedSeverity));
                attr.AddAttribute(PARAM_ID_ALARM_REPORTING_MECHANISM, u32(supportedAlarms[i].alarm.reportingMechanism));

                shared_ptr<MibCreateObjectReq> mibCreateObjectReq = MultiInstanceMibObjectManager::GetInstance().GetMio("Device.FaultMgmt.SupportedAlarm.")->New(attr);
                if(mibCreateObjectReq != NULL)
                {
                   Tr069Application::GetInstance().SendMessage( *mibCreateObjectReq, ENTITY_MIB, ENTITY_TR069 );

                   FapAlarmId newId;
                   newId.SetNumericAlarmId(supportedAlarms[i].alarmId);
                   m_supportedAlarms[supportedAlarms[i].alarmId+cellId*FapAlarmId::MAX_ALARMS] = supportedAlarms[i].alarm;
                }
            }
        	}
    }
    else if (vendor == "NEC" )
    {
        TRACE_PRINTF("Gateway vendor: NEC (No Supported Alarms)");
    }
    else
    {
        TRACE_PRINTF("Gateway vendor: Radisys");
    }

}

void SupportedAlarmManager::ListenAlarmEvent( const AlarmEvent & alarmEvent )
{
    shared_ptr<FapAlarmId> alarmId = dynamic_pointer_cast<FapAlarmId>(alarmEvent.GetAlarmId());

    RSYS_ASSERT(alarmId);

    map<u32, SupportedAlarm>::iterator i = m_supportedAlarms.find((u32)alarmId->GetFapAlarmId() );

    if( i != m_supportedAlarms.end() )
    {
        m_currentAlarmManager.SupportedAlarmEvent( i->second, alarmEvent );
    }
}


}

