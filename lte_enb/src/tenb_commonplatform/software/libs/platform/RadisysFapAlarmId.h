///////////////////////////////////////////////////////////////////////////////
//
// RadisysFapAlarmId.h
//
// Concrete class representing a generic FAP alarm ID.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RadisysFapAlarmId_h_
#define __RadisysFapAlarmId_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/AlarmId.h>
#include <platform/FapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class RadisysFapAlarmId : public AlarmId
{
public:
    typedef enum
    {
        WARNING = 1,
        MINOR = 2,
        MAJOR = 3,
        CRITICAL = 4
    } Severity;

    typedef enum
    {
        CLEARED = 0,
        SET = 1,
        TRANSIENT = 2
    } Activity;


    // Typedefs
    typedef enum
    {
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
   	CFG_FAIL_FROM_SON,
   	PCI_COLLISION,
   	PCI_CONFUSION,
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

        INVALID_RADISYS_ALARM = 0xffffffff
    } Id;

public:

    /**
     * Construct with an alarm ID.
     */
    RadisysFapAlarmId() :
        m_alarm(m_alarmListLength-1),
        m_name(m_alarmList[m_alarmListLength-1].alarmText)
    {
    }

    RadisysFapAlarmId(FapAlarmId::Id id) :
        m_alarm(m_alarmListLength-1)
    {
        RSYS_ASSERT(id < FapAlarmId::NUM_ALARM_IDS);

        u32 alarm;
        for(alarm = 0; alarm < m_alarmListLength; alarm++)
        {
            if(id == m_alarmList[alarm].rsysId)
            {
                m_alarm = alarm;
                break;
            }
        }

        m_name = m_alarmList[m_alarm].alarmText;
    }

    virtual ~RadisysFapAlarmId() {};

    /**
     * Implement AlarmId.
     */
    virtual void SetNumericAlarmId(u32 id)
    {
        m_alarm = m_alarmListLength-1;
        u32 alarm;
        for(alarm = 0; alarm < m_alarmListLength; alarm++)
        {
            if(id == (u32)m_alarmList[alarm].rsysId)
            {
                m_alarm = alarm;
                break;
            }
        }

        m_name = m_alarmList[m_alarm].alarmText;
    }

    virtual u32 GetNumericAlarmId() const { return (u32)m_alarmList[m_alarm].rsysId; }
    virtual std::string ToString() const { return m_name; }

    /**
     * Get alarm ID as enum.
     */
    Id GetRadisysFapAlarmId() const
    {
        RSYS_ASSERT(m_alarm < m_alarmListLength);
        return m_alarmList[m_alarm].radisysId;
    }

    u32 GetAlarmNumber(void) const
    {
        RSYS_ASSERT(m_alarm < m_alarmListLength);
        return (u32)m_alarmList[m_alarm].radisysId;
    }

    const char * GetAlarmText(void) const
    {
        RSYS_ASSERT(m_alarm < m_alarmListLength);
        return &m_alarmList[m_alarm].alarmText[0];
    }

    const char * GetAlarmAdditionInfo(void) const
    {
        RSYS_ASSERT(m_alarm < m_alarmListLength);
        return &m_alarmList[m_alarm].alarmAdditionalInfo[0];
    }

    Severity GetAlarmSeverity(void) const
    {
        RSYS_ASSERT(m_alarm < m_alarmListLength);
        return m_alarmList[m_alarm].severity;
    }
    
private:
    static const unsigned m_alarmTextMaxLength = 80;
    static const unsigned m_alarmListLength = 0;
    // Alarm ID.
    u32 m_alarm;
    std::string m_name;

    typedef struct AlarmDescription_tag
    {
        FapAlarmId::Id rsysId;
        RadisysFapAlarmId::Id radisysId;
        char alarmText[m_alarmTextMaxLength + 1];
        char alarmAdditionalInfo[m_alarmTextMaxLength + 1];
        Severity severity;

    } AlarmDescription;   
    
    static const AlarmDescription m_alarmList[];
};

}
#endif
