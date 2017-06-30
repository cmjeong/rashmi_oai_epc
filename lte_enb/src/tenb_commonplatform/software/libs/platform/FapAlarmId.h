///////////////////////////////////////////////////////////////////////////////
//
// FapAlarmId.h
//
// Concrete class representing a generic FAP alarm ID.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FapAlarmId_h_
#define __FapAlarmId_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/AlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FapAlarmId : public AlarmId
{
public:

    // Typedefs

    /**
     * !!!!!! BIG IMPORTANT NOTE !!!!!!
     *
     * It's imperative that these enum values don't change.
     * Any new alarm IDs must be added to the end.
     * This is because alarm IDs are written to the alarm log file and any new
     * revision of s/w must be able to read and correctly interpret old alarms.
     */
    typedef enum
    {
        TEST_ALARM = 0,
        LOGGED_ASSERTION_FAILURE,
        FREQUENCY_STABILITY,  //N.B. this alarm is changed to OSCILLATOR_STABILITY_PROBLEM. The FREQUENCY_STABILITY will not now be activated
        UNUSED_1,
        UNUSED_2,
        OTA_FREQUENCY_SYNCHRONISATION_FAILURE,
        NTP_FREQUENCY_SYNCHRONISATION_FAILURE,
        SHORT_RANGE_INTERFERER,
        LOW_QUAL_WCDMA_BAND,
        NO_FREQUENCY_DISCIPLINE,
        NO_CONFIGURATION_PLAN,
        CONFIGURATION_PLAN_ERROR,
        OVER_TEMPERATURE_OPERATIONAL_THRESHOLD,
        UNDER_TEMPERATURE_OPERATIONAL_THRESHOLD,
        IPSEC_TUNNEL_FAILURE,
        TR069_CONNECTION_FAILURE,
        PARAMETER_VALUE_OUTSIDE_PERMITTED_RANGE,
        SCRAMBLING_CODE_CONFLICT,
        NTP_SERVER_NOT_RESPONDING,
        NETWORK_JITTER,
        OSCILLATOR_STABILITY_PROBLEM,
        CONFIGURATION_PLAN_INCONSISTENCY,
        FAP_BOOT_EVENT,
        SOFTWARE_WARNING,
        FAP_ABOUT_TO_REBOOT_EVENT,
        PHY_CONFIGURATION_FAILURE,
        INCOMPATIBLE_RADIO_LINK_PARAMETER,
        SOFTWARE_UPDATE_INITIALISATION_FAILURE,
        //
        // Always add new IDs here, not before any existing ones!!  See note above.
        //
// Radisys LTE Alarms List
	LTE_CONFIGURATION_PLAN_ERROR = 11100,
	LTE_CONFIGURATION_PLAN_INCONSISTENCY,
   	LTE_FREQUENCY_SYNCHRONISATION_FAILURE,
   	LTE_NTP_SERVER_NOT_RESPONDING,
   	LTE_OSCILLATOR_STABILITY_PROBLEM,
   	LTE_FAP_TEMPERATURE_OVER_THRESHOLD,
   	PCI_CONFLICT,
   	LTE_LOW_QUALITY_CHANNEL,
   	LTE_NETWORK_JITTER,
   	S1_SETUP_FAIL,
  	X2_SETUP_FAIL,
   	LTE_MEMORY_ALLOCATION_FAIL,
   	SCTP_LINK_FAIL,
   	TNL_SETUP_FAIL,
   	S1_ERROR_IND,
   	S1_RESET,
   	X2_ERROR_IND,
   	X2_RESET,
        /* Static Configuration Alarm */
        SOCKET_CFG_FAIL,
        SCTP_CFG_FAIL,
        S1AP_CFG_FAIL,
        EGTP_CFG_FAIL,
        X2AP_CFG_FAIL,
        RRM_CFG_FAIL,
        APP_CFG_FAIL,
        RRC_CFG_FAIL,
        PDCPUL_CFG_FAIL,
        PDCPDL_CFG_FAIL,
        RLCUL_CFG_FAIL,
        RLCDL_CFG_FAIL,
        MAC_CFG_FAIL,
        CL_CFG_FAIL,
        CELLUP_CFG_FAIL,
        /* Dynamic Configuration Alarm */
        ADMIN_STATE_CHANGE_FAIL,
        GENERIC_PRAMS_CFG_FAIL,
        MME_IP_PRAMS_CFG_FAIL,
        CELL_CONFIG_PRAMS_FAIL,
        ENBIP_CFG_FAIL,
        MIB_CFG_FAIL,
        PRACH_CFG_FAIL,
        RACH_CFG_FAIL,
        PDSCH_CFG_FAIL,
        SRS_CFG_FAIL,
        PUSCH_CFG_FAIL,
        ULPOWER_CFG_FAIL,
        ULFREQ_CFG_FAIL,
        PUCCH_CFG_FAIL,
        UETMRCONS_CFG_FAIL,
        SIB1_CFG_FAIL,
        SIB2_CFG_FAIL,
        SIB3_CFG_FAIL,
        SIB4_CFG_FAIL,
        SIB6_CFG_FAIL,
        SIB9_CFG_FAIL,
        ANR_CFG_FAIL,
        MEAS_CFG_FAIL,
        EAID_CFG_FAIL,
        SIBSCHED_CFG_FAIL,
        RABPOLICY_CFG_FAIL,
        TIMER_CFG_FAIL,
        RRM_CELL_CFG_FAIL,
        ULSCHD_CFG_FAIL,
        DLSCHD_CFG_FAIL,
        NEIGH_CFG_FAIL,
        NEIGH_CELL_CFG_FAIL,
        NEIGH_FREQ_CFG_FAIL,
        NEIGH_BAND_CLASS_CFG_FAIL,
        ENB_PROTO_CFG_FAIL,
        UTRANEIFREQ_CFG_FAIL,
        EUTRANEIFREQ_CFG_FAIL,
        UTRANEICELL_CFG_FAIL,
        EUTRANEICELL_CFG_FAIL,
        UTRANEILIST_CFG_FAIL,
        EUTRANEILIST_CFG_FAIL,
        RABSRB1_CFG_FAIL,
        RABSRB2_CFG_FAIL,
        EVNT_NEIGH_ENB_CFG_FAIL,
        SMCELL_CFG_FAIL,
        PROCTMR_CFG_FAIL,
   	CFG_FAIL_FROM_SON,
   	PCI_COLLISION,
   	PCI_CONFUSION,
      MAX_ALARMS,
        NUM_ALARM_IDS,
        INVALID
    } Id;

    /**
     * Construct with an alarm ID.
     */
    FapAlarmId(Id id) : m_fapAlarmId(id) {};
    FapAlarmId() : m_fapAlarmId(INVALID) {};
    virtual ~FapAlarmId() {};

    /**
     * Implement AlarmId.
     */
    virtual void SetNumericAlarmId(u32 id) { m_fapAlarmId = id; };
    virtual u32 GetNumericAlarmId() const { return (u32)m_fapAlarmId; };
    virtual std::string ToString() const
    {
        switch(m_fapAlarmId % MAX_ALARMS)
        {
        case TEST_ALARM:                                return "Test Alarm";
        case LOGGED_ASSERTION_FAILURE:                  return "Logged Assertion Failure";
        case FREQUENCY_STABILITY:                       return "Frequency Stability";
        case UNUSED_1:                                  return "UNUSED_1 (was Over Temperature (Performance))";
        case UNUSED_2:                                  return "UNUSED_2 (was Under Temperature (Performance))";
        case OTA_FREQUENCY_SYNCHRONISATION_FAILURE:     return "No Over-The-Air Frequency Sync";
        case NTP_FREQUENCY_SYNCHRONISATION_FAILURE:     return "No NTP Frequency Sync";
        case SHORT_RANGE_INTERFERER:                    return "Short Range Interferer";
        case LOW_QUAL_WCDMA_BAND:                       return "Low Quality WCDMA Band";
        case NO_FREQUENCY_DISCIPLINE:                   return "No Frequency Discipline";
        case NO_CONFIGURATION_PLAN:                     return "No Configuration Plan";
        case CONFIGURATION_PLAN_ERROR:                  return "Configuration Plan Error";
        case OVER_TEMPERATURE_OPERATIONAL_THRESHOLD:    return "Over Temperature (Operational)";
        case UNDER_TEMPERATURE_OPERATIONAL_THRESHOLD:   return "Under Temperature (Operational)";
        case IPSEC_TUNNEL_FAILURE:                      return "IPSec Tunnel Failure";
        case TR069_CONNECTION_FAILURE:                  return "TR069 Connection Failure";
        case PARAMETER_VALUE_OUTSIDE_PERMITTED_RANGE:   return "Parameter Value Outside Permitted Range";
        case SCRAMBLING_CODE_CONFLICT:					return "Scrambling Code Conflict";
        case NTP_SERVER_NOT_RESPONDING:                 return "NTP Server Not Responding";
        case NETWORK_JITTER:							return "Network Jitter";
        case OSCILLATOR_STABILITY_PROBLEM:				return "Oscillator Stability Problem";
        case CONFIGURATION_PLAN_INCONSISTENCY:			return "Configuration Plan Inconsistency";
        case FAP_BOOT_EVENT:                            return "FAP Boot event";
        case FAP_ABOUT_TO_REBOOT_EVENT:                 return "FAP about to reboot event";
        case SOFTWARE_WARNING:                          return "SW warning";
        case PHY_CONFIGURATION_FAILURE:                 return "PHY configuration failure (no calibration?)";
        case INCOMPATIBLE_RADIO_LINK_PARAMETER:         return " Incompatible Radio Link Parameter ";
        case SOFTWARE_UPDATE_INITIALISATION_FAILURE:	return " Software Update initialisation failure (u-boot environment?)";

// Radisys LTE Alarms List
	case LTE_CONFIGURATION_PLAN_ERROR:              return "LTE Critical Configuration failed";
	case LTE_CONFIGURATION_PLAN_INCONSISTENCY:	return "LTE Configuration plan inconsistency";
	case LTE_FREQUENCY_SYNCHRONISATION_FAILURE:	return "Freq sync fails in LTE";
	case LTE_NTP_SERVER_NOT_RESPONDING:		return "NTP server not responding in LTE";
	case LTE_OSCILLATOR_STABILITY_PROBLEM: 		return "Oscillator stability problem in LTE";
	case LTE_FAP_TEMPERATURE_OVER_THRESHOLD:	return "Temperature over threshold" ;
	case PCI_CONFLICT: 				return "PCI conflict" ;
	case LTE_LOW_QUALITY_CHANNEL:			return "Low quality of LTE channel";
	case LTE_NETWORK_JITTER: 			return "Network Jitter in LTE";
	case S1_SETUP_FAIL: 				return "S1 Setup fails";
	case X2_SETUP_FAIL:				return "X2 Setup fails";
	case LTE_MEMORY_ALLOCATION_FAIL:		return "Memory allocation fails in LTE";
	case SCTP_LINK_FAIL:				return "SCTP link failure";
	case TNL_SETUP_FAIL:				return "TNL setup failure";
	case S1_ERROR_IND:				return "S1 Frequent Error indication";
	case S1_RESET:					return "S1 Frequent Reset";
	case X2_ERROR_IND:				return "X2 Frequent Error indication";
	case X2_RESET:					return "X2 Frequent Reset"; 
        case SOCKET_CFG_FAIL:                           return "TUCL configuration failure";
        case SCTP_CFG_FAIL:                             return "SCTP configuration failure";
        case S1AP_CFG_FAIL:                             return "S1AP configuration failure";
        case EGTP_CFG_FAIL:                             return "EGTP configuration failure";
        case X2AP_CFG_FAIL:                             return "X2AP configuration failure";
        case RRM_CFG_FAIL:                              return "RRM configuration failure";
        case APP_CFG_FAIL:                              return "APP configuration failure";
        case RRC_CFG_FAIL:                              return "RRC configuration failure";
        case PDCPUL_CFG_FAIL:                           return "PDCPUL configuration failure";
        case PDCPDL_CFG_FAIL:                           return "PDCPDL configuration failure";
        case RLCUL_CFG_FAIL:                            return "RLCUL configuration failure";
        case RLCDL_CFG_FAIL:                            return "RLCDL configuration failure";
        case MAC_CFG_FAIL:                              return "MAC configuration failure";
        case CL_CFG_FAIL:                               return "CL configuration failure";
        case CELLUP_CFG_FAIL:                           return "CELLUP configuration failure";
        case ADMIN_STATE_CHANGE_FAIL:                   return "Dynamic configuration failure for Admin State";
        case GENERIC_PRAMS_CFG_FAIL:                    return "Dynamic configuration failure for Generic params";
        case MME_IP_PRAMS_CFG_FAIL:                     return "Dynamic configuration failure for MME IP Params";
        case CELL_CONFIG_PRAMS_FAIL:                    return "Dynamic configuration failure for Cell config params";
        case ENBIP_CFG_FAIL:                            return "Dynamic configuration failure for EnodeB IP";
        case MIB_CFG_FAIL:                              return "Dynamic configuration failure for MIB params";
        case PRACH_CFG_FAIL:                            return "Dynamic configuration failure for PRACH params";
        case RACH_CFG_FAIL:                             return "Dynamic configuration failure for RACH params";
        case PDSCH_CFG_FAIL:                            return "Dynamic configuration failure for PDSCH params";
        case SRS_CFG_FAIL:                              return "Dynamic configuration failure for SRS params";
        case PUSCH_CFG_FAIL:                            return "Dynamic configuration failure for PUSCH params";
        case ULPOWER_CFG_FAIL:                          return "Dynamic configuration failure for UL power params";
        case ULFREQ_CFG_FAIL:                           return "Dynamic configuration failure for UL freq params";
        case PUCCH_CFG_FAIL:                            return "Dynamic configuration failure for PUCCH params";
        case UETMRCONS_CFG_FAIL:                        return "Dynamic configuration failure for UE timer constants";
        case SIB1_CFG_FAIL:                             return "Dynamic configuration failure for SIB1 params";
        case SIB2_CFG_FAIL:                             return "Dynamic configuration failure for SIB2 params";
        case SIB3_CFG_FAIL:                             return "Dynamic configuration failure for SIB3 params";
        case SIB4_CFG_FAIL:                             return "Dynamic configuration failure for SIB4 params";
        case SIB6_CFG_FAIL:                             return "Dynamic configuration failure for SIB6 params";
        case SIB9_CFG_FAIL:                             return "Dynamic configuration failure for SIB9 params";
        case ANR_CFG_FAIL:                              return "Dynamic configuration failure for ANR params";
        case MEAS_CFG_FAIL:                             return "Dynamic configuration failure for measurement params";
        case EAID_CFG_FAIL:                             return "Dynamic configuration failure for EAID params";
        case SIBSCHED_CFG_FAIL:                         return "Dynamic configuration failure for SIB scheduler params";
        case RABPOLICY_CFG_FAIL:                        return "Dynamic configuration failure for RAB policy params";
        case TIMER_CFG_FAIL:                            return "Dynamic configuration failure for timer cfg params";
        case RRM_CELL_CFG_FAIL:                         return "Dynamic configuration failure for RRM cell cfg params";
        case ULSCHD_CFG_FAIL:                           return "Dynamic configuration failure for UL scheduler params";
        case DLSCHD_CFG_FAIL:                           return "Dynamic configuration failure for DL scheduler params";
        case NEIGH_CFG_FAIL:                            return "Dynamic configuration failure for Neigh config params";
        case NEIGH_CELL_CFG_FAIL:                       return "Dynamic configuration failure for neigh cell config params";
        case NEIGH_FREQ_CFG_FAIL:                       return "Dynamic configuration failure for neigh freq config params";
        case NEIGH_BAND_CLASS_CFG_FAIL:                 return "Dynamic configuration failure for band class params";
        case ENB_PROTO_CFG_FAIL:                        return "Dynamic configuration failure for proto config params";
        case UTRANEIFREQ_CFG_FAIL:                      return "Dynamic configuration failure for UTRA neigh freq params";
        case EUTRANEIFREQ_CFG_FAIL:                     return "Dynamic configuration failure for EUTRA neigh freq params";
        case UTRANEICELL_CFG_FAIL:                      return "Dynamic configuration failure for UTRA neigh cell params";
        case EUTRANEICELL_CFG_FAIL:                     return "Dynamic configuration failure for EUTRA neigh cell params";
        case UTRANEILIST_CFG_FAIL:                      return "Dynamic configuration failure for UTRA neigh list params";
        case EUTRANEILIST_CFG_FAIL:                     return "Dynamic configuration failure for EUTRA neigh list params";
        case RABSRB1_CFG_FAIL:                          return "Dynamic configuration failure for RAB SRB1 params";
        case RABSRB2_CFG_FAIL:                          return "Dynamic configuration failure for RAB SRB2 params";
        case EVNT_NEIGH_ENB_CFG_FAIL:                   return "Dynamic configuration failure for Neigh ENB params";
        case SMCELL_CFG_FAIL:                           return "Dynamic configuration failure for SM cell config params";
        case PROCTMR_CFG_FAIL:                          return "Dynamic configuration failure for Proc timer cfg params";
	case CFG_FAIL_FROM_SON:         		return "Serving Cell Configuration failure Alert from SON";
	case PCI_COLLISION:				return "Another eNB which is a direct neighbor discovered to have same PCI as serving cell. Reconfiguration of PCI recommended for eNB to come up";
	case PCI_CONFUSION:				return "Another eNB which is not a direct neighbor discovered to have same PCI as serving cell. Reconfiguration of PCI recommended for eNB to come up.";
        case MAX_ALARMS:
		  case NUM_ALARM_IDS:
        case INVALID:
            return "Invalid Alarm ID";
            break;
        }
        return "Unknown Alarm ID";
    }

    /**
     * Get alarm ID as enum.
     */
    u32 GetFapAlarmId() const { return m_fapAlarmId; };

private:

    // Alarm ID.
    u32 m_fapAlarmId;

};

}

#endif
