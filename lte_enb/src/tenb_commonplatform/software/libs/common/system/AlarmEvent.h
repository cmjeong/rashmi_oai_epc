///////////////////////////////////////////////////////////////////////////////
//
// AlarmEvent.h
//
// Simple class to encapsulate an alarm event.  These can be raised by any
// entity/module and sent to OAM or other event handler.  Derived classes
// can add other information such as device or MO address.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AlarmEvent_h_
#define __AlarmEvent_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <string>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/TimeWrap.h>
#include <system/AlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class AlarmEvent : public Serialisable
{
public:

    // Constants

    /**
     * Serialisation format version.
     * Allows us to serialise to file then check version on reading back.
     */
    static const u8 SERIALISATION_FORMAT = 0;

    /**
     * Maximum length of the additional info string.
     */
    static const u32 ADDITIONAL_INFO_MAX_LEN = 512;

    /**
     * Sequence number before it has been set.
     * Hopefully we won't get to 4 billion alarm events...
     */
    static const u32 INVALID_SEQUENCE_NUMBER = 0xFFFFFFFF;

    // Typedefs

    /**
     * Lifetime of an event.  Transient events will not be 'cleared'.
     */
    typedef enum
    {
        ALARM_EVENT_TRANSIENT = 0,
        ALARM_EVENT_NONTRANSIENT
    } AlarmEventLifetime;

    /**
     * Alarm severity.  Speaks for itself hopefully.
     * Note: Transient alarms cannot have a severity of CLEARED.
     */
    typedef enum
    {
        ALARM_SEVERITY_CLEARED = 0,
        ALARM_SEVERITY_WARNING,
        ALARM_SEVERITY_MINOR,
        ALARM_SEVERITY_MAJOR,
        ALARM_SEVERITY_CRITICAL
    } AlarmSeverity;

    /**
     * Alarm type/category.
     */
     typedef enum
     {
        ALARM_TYPE_COMMUNICATIONS = 0,
        ALARM_TYPE_QOS,
        ALARM_TYPE_PROCESSING,
        ALARM_TYPE_EQUIPMENT,
        ALARM_TYPE_ENVIRONMENT
     } AlarmType;

    /**
     * Default constructor.  For messaging internal use only.
     * Call SetAlarmId() before deserialising.
     */
    AlarmEvent();

    /**
     * Construct an alarm event.
     *
     * \param id             ID for the alarm.  Will be specific to a particular platform/product.
     * \param lifetime       Transient or non-transient?  Transient alarms don't have lifetimes.
     * \param severity       Level of severity, includes 'CLEARED' to clear an active non-transient alarm.
     * \param additionalInfo Any other info that may be useful in resolving the problem.
     * \param alarmType      Type/category of alarm.
     */
    AlarmEvent(shared_ptr<AlarmId> id,
               AlarmEventLifetime lifetime,
               AlarmSeverity severity,
               const std::string& additionalInfo,
               AlarmType alarmType);

    /**
     * Construct an alarm event.  As above but string can be passed in as a literal.
     *
     * \param id             ID for the alarm.  Will be specific to a particular platform/product.
     * \param lifetime       Transient or non-transient?  Transient alarms don't have lifetimes.
     * \param severity       Level of severity, includes 'CLEARED' to clear an active non-transient alarm.
     * \param additionalInfo Any other info that may be useful in resolving the problem.
     * \param alarmType      Type/category of alarm.
     */
    AlarmEvent(shared_ptr<AlarmId> id,
               AlarmEventLifetime lifetime,
               AlarmSeverity severity,
               const char * additionalInfo,
               AlarmType alarmType);
	
	 /**
     * Construct an alarm event  as above it also containg Additional Information
     *
     * \param id             ID for the alarm.  Will be specific to a particular platform/product.
     * \param lifetime       Transient or non-transient?  Transient alarms don't have lifetimes.
     * \param severity       Level of severity, includes 'CLEARED' to clear an active non-transient alarm.
     * \param additionalInfo Specific Problem of the alarm
     * \param alarmType      Type/category of alarm.
     * \param additnlInfo      Any other info that may be useful in resolving the problem.
     */
	AlarmEvent(shared_ptr<AlarmId> id,
							   AlarmEventLifetime lifetime,
							   AlarmSeverity severity,
							   const std::string& additionalInfo,
							   AlarmType alarmType,
							   const std::string& additnlInfo) ;

    virtual ~AlarmEvent() {};

    /**
     * Set alarm ID to the concrete ID required.  We have to be intelligent
     * and know what type of event we are dealing with at this point i.e.
     * is it internal ID, TR-069, SNMP etc.
     * We have to set the alarm ID before we deserialise.
     */
    void SetAlarmId(shared_ptr<AlarmId> alarmId) { m_alarmId = alarmId; }

    /**
     * Set sequence number.
     * Initially the alarm event won't have a sequence number as alarm
     * events can be raised by multiple processes.
     * Something central (e.g. OAM in FAP) will set the sequence number
     * as unique.
     *
     * \param sequenceNumber Unique sequence number for this alarm event.
     */
    void SetSequenceNumber(u32 sequenceNumber) { m_sequenceNumber = sequenceNumber; };

    /**
     * Getters.
     */
    shared_ptr<AlarmId> GetAlarmId() const { return m_alarmId; };
    AlarmEventLifetime  GetLifetime() const { return m_lifetime; };
    AlarmSeverity GetSeverity() const { return m_severity; };
    std::string GetAdditionalInfo() const { return m_additionalInfo; }; //This is actually used for specific problem
	std::string GetAddtnlInfo() const { return m_addtnlInfo; };
    AlarmType GetAlarmType() const { return m_alarmType; };
    TimeWrap GetObservationTime() const { return m_observationTime; };
    u32 GetSequenceNumber() const;

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_ALARM_EVENT; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

private:
    /**
     * What alarm is this?
     * This is intentionally not an enum as this class should be decoupled
     * from the particular system it is used in.
     */
    shared_ptr<AlarmId> m_alarmId;

    /**
     * Is this a transient or non-transient alarm event?
     * Transient alarms are never cleared.
     */
    AlarmEventLifetime  m_lifetime;

    /**
     * Alarm severity.  Transient events cannot be 'cleared'.
     */
    AlarmSeverity       m_severity;

    /**
     * Specific Problem. Name is misleading TODO correction
     * Specific Problem of the alarm typically as per alarm standards.
     */
    std::string         m_additionalInfo;

	/**
     * Additional information.  Freeform but should be geared towards
     * providing information that will help someone at the operator's
     * NOC diagnose and correct the problem.
     */
	std::string			m_addtnlInfo;

    /**
     * What category/type of alarm is this?
     */
    AlarmType           m_alarmType;

    /**
     * What time did this event occur?
     * TimeWrap supports detecting if actual time has not been set and can
     * be queried to allow us to put a null time in any alarm reports.
     */
    TimeWrap            m_observationTime;

    /**
     * Alarm unique sequence number.
     * As multiple processes can send alarm events and each management
     * interface (TR069, SNMP, whatever) may want to filter out certain
     * events, the sequence number is initially assigned by a central
     * clearing house (e.g. OAM) but may be overwritten/ignored by any
     * particular management interface.
     */
    u32                 m_sequenceNumber;
};

}

#endif
