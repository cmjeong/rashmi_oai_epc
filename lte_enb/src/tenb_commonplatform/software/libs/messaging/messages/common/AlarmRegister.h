///////////////////////////////////////////////////////////////////////////////
//
// AlarmRegister.h 
//
// Message sent to inform that alarm is registerd.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AlarmRegister_h_
#define __AlarmRegister_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/SerialisationUtils.h>

#define S1_CAUSE_RADIO_NW  0
#define S1_CAUSE_TRANSPORT 1
#define S1_CAUSE_NAS       2
#define S1_CAUSE_PROTOCOL  3
#define S1_CAUSE_MISC      4

#define X2_CAUSE_RADIO_NW  0
#define X2_CAUSE_TRANSPORT 1
#define X2_CAUSE_PROTOCOL  2
#define X2_CAUSE_MISC      3

#define ALARM_CAUSE_TYPE_ERR_IND 0
#define ALARM_CAUSE_TYPE_TMR_EXP 1

#define CFG_SRV_CELL_FROM_SON_FAIL  0
#define PCI_ALARM_FROM_SON 0

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class AlarmRegister : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    AlarmRegister();
    AlarmRegister(u32 id, u8 alarmSeverity, u8 alarmCauseType, u8 alarmCauseVal, char* additionalInfo);
    virtual ~AlarmRegister() {};

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_ALARM_EVENT; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const; 

    /**
     * Getters.
     */
    u32 GetAlarmId() const { return m_alarmId; };
    u8 GetAlarmSeverity() const { return m_alarmSeverity; };
    const std::string GetAdditionalInfo() const { return  m_additionalInfo; }
	const std::string GetAddtnlInfo() const { return  m_addtnlInfo; }

/** @brief defines radio network cause for S1 **/

static const char *s1CauseRadioNetwork[];

/** @brief defines transport cause for S1 **/
static const char *s1CauseTransport[]; 

/** @brief defines NAS cause for S1 **/
static const char *s1CauseNas[];

/** @brief defines Protocol cause for S1 **/
static const char *s1CauseProtocol[];

/** @brief defines miscellaneous cause for S1 **/
static const char *s1CauseMisc[];

/** @brief defines radio network cause for X2 **/
static const char *x2CauseRadioNetwork[];

/** @brief defines transport cause for X2 **/
static const char *x2CauseTransport[];

/** @brief defines Protocol cause for X2 **/
static const char *x2CauseProtocol[];

/** @brief defines miscellaneous cause for X2 **/
static const char *x2CauseMisc[];

/* defines cause for config fail */
static const char *configFail[];

/** @brief defines miscellaneous cause for Cfg failure from SON **/
static const char *cfgCauseSON[];

/** @brief defines specific problem for PCI collision **/
static const char *pciCollision;

/** @brief defines specific problem for PCI confusion **/
static const char *pciConfusion;


typedef enum alarmId
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
	MAX_ALARMS
} AlarmId;

typedef enum alarmSeverity
{
    ALARM_SEVERITY_CLEARED = 0,
    ALARM_SEVERITY_WARNING,
    ALARM_SEVERITY_MINOR,
    ALARM_SEVERITY_MAJOR,
    ALARM_SEVERITY_CRITICAL
} AlarmSeverity;

private:
    static const u32 ADDITIONAL_INFO_MAX_LEN = 500;
    
    void SetAdditionalInfo(u8 alarmCauseType,u8 alarmCauseVal);
	void SetAddtnlInfo(u8 alarmCauseType,u8 alarmCauseVal);
    
    u32 m_alarmId;
    u8 m_alarmSeverity;
    u8 m_alarmCauseType;
    u8 m_alarmCauseVal;
    std::string m_additionalInfo; // This is actually specific problem
	std::string m_addtnlInfo;  // This is the correct additional info
};

#endif
