///////////////////////////////////////////////////////////////////////////////
//
// AlarmEvent.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "AlarmEvent.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

AlarmEvent::AlarmEvent() :
    m_alarmId(shared_ptr<AlarmId>()),
    m_lifetime(ALARM_EVENT_TRANSIENT),
    m_severity(ALARM_SEVERITY_CLEARED),
    m_alarmType(ALARM_TYPE_COMMUNICATIONS),
    m_sequenceNumber(INVALID_SEQUENCE_NUMBER)
{
    ENTER();
    EXIT();
}

AlarmEvent::AlarmEvent(shared_ptr<AlarmId> id,
                       AlarmEventLifetime lifetime,
                       AlarmSeverity severity,
                       const std::string& additionalInfo,
                       AlarmType alarmType) :
    m_alarmId(id),
    m_lifetime(lifetime),
    m_severity(severity),
    m_additionalInfo(additionalInfo),
    m_alarmType(alarmType),
    m_sequenceNumber(INVALID_SEQUENCE_NUMBER),
    m_addtnlInfo(additionalInfo)
{
    ENTER();
    EXIT();
}

AlarmEvent::AlarmEvent(shared_ptr<AlarmId> id,
                       AlarmEventLifetime lifetime,
                       AlarmSeverity severity,
                       const char * additionalInfo,
                       AlarmType alarmType) :
    m_alarmId(id),
    m_lifetime(lifetime),
    m_severity(severity),
    m_additionalInfo(""),
    m_alarmType(alarmType),
    m_sequenceNumber(INVALID_SEQUENCE_NUMBER),
    m_addtnlInfo("")
{
    ENTER();

    if(additionalInfo)
    {
	    m_additionalInfo = additionalInfo;
		m_addtnlInfo = "Unspecified Additional Information";
	}

    EXIT();
}
	
AlarmEvent::AlarmEvent(shared_ptr<AlarmId> id,
						   AlarmEventLifetime lifetime,
						   AlarmSeverity severity,
						   const std::string& additionalInfo,
						   AlarmType alarmType,
						   const std::string& addtnlInfo) :
		m_alarmId(id),
		m_lifetime(lifetime),
		m_severity(severity),
		m_additionalInfo(""),
		m_alarmType(alarmType),
		m_sequenceNumber(INVALID_SEQUENCE_NUMBER),
		m_addtnlInfo("")
	{
		ENTER();
			m_additionalInfo = additionalInfo;
			m_addtnlInfo = addtnlInfo;
			TRACE_PRINTF("AlarmEvent: m_additionalInfo= %s, m_addtnlInfo =%s",additionalInfo.c_str(),
				addtnlInfo.c_str());
		EXIT();
	}

u32 AlarmEvent::GetSequenceNumber() const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_sequenceNumber != INVALID_SEQUENCE_NUMBER);

    RETURN(m_sequenceNumber);
}

s32 AlarmEvent::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_alarmId != NULL);
    RSYS_ASSERT(dataMaxBytes >= ADDITIONAL_INFO_MAX_LEN + 18);
    string additionalInfo, addtnlInfo;
    additionalInfo.assign( m_additionalInfo, 0, ADDITIONAL_INFO_MAX_LEN );
	addtnlInfo.assign( m_addtnlInfo );

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(SERIALISATION_FORMAT, serialisedData);

    SerialiseIt(m_alarmId->GetNumericAlarmId(), serialisedData);

    SerialiseIt((u8)m_lifetime, serialisedData);

    SerialiseIt((u8)m_severity, serialisedData);

    SerialiseIt(additionalInfo, serialisedData);

    SerialiseIt((u8)m_alarmType, serialisedData);

    SerialiseIt(m_observationTime.GetUnixTime(), serialisedData);
    SerialiseIt(m_observationTime.GetMicroSecs(), serialisedData);

    SerialiseIt(m_sequenceNumber, serialisedData);
	SerialiseIt(addtnlInfo, serialisedData);

    RETURN(serialisedData - data);
}

bool AlarmEvent::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // Preconditions.
    if(dataLen < 18)
        RETURN(false);

    // Check the format.
    u8 format;
    DeSerialiseIt(format, data);
    if(format != SERIALISATION_FORMAT)
    {
        TRACE_PRINTF("Can't DeSerialise as data is wrong format.  Expecting %u, got %u.", SERIALISATION_FORMAT, format);
        RETURN(false);
    }

    // Deserialise all the members.
    u8 deserialisedByte;
    u32 deserialisedU32;

    DeSerialiseIt(deserialisedU32, data);
    if(m_alarmId != NULL)
    {
        m_alarmId->SetNumericAlarmId(deserialisedU32);
    }

    DeSerialiseIt(deserialisedByte, data);
    m_lifetime = (AlarmEventLifetime)deserialisedByte;

    DeSerialiseIt(deserialisedByte, data);
    m_severity = (AlarmSeverity)deserialisedByte;

    DeSerialiseIt(m_additionalInfo, data, ADDITIONAL_INFO_MAX_LEN);

    DeSerialiseIt(deserialisedByte, data);
    m_alarmType = (AlarmType)deserialisedByte;

    u32 unixTime;
    DeSerialiseIt(unixTime, data);
    u32 microSecs;
    DeSerialiseIt(microSecs, data);
    m_observationTime.Set(unixTime, microSecs);

    DeSerialiseIt(m_sequenceNumber, data);
	DeSerialiseIt(m_addtnlInfo, data, ADDITIONAL_INFO_MAX_LEN);

    RETURN(true);
}

std::string AlarmEvent::ToString() const
{
    ENTER();


    ostringstream stream;

    if(m_alarmId != NULL)
    {
        stream << "id=" << m_alarmId->GetNumericAlarmId() << "(" << m_alarmId->ToString() << "), ";
    }

    stream << (m_lifetime == ALARM_EVENT_TRANSIENT ? "TRANSIENT" : "NONTRANSIENT")
           << ", severity=" << (u32)m_severity
           << ", specificProblem=" << m_additionalInfo
           << ", additionalInfo=" << m_addtnlInfo
           << ", alarmType=" << m_alarmType
           << ", observationTime=" << m_observationTime.ToString();

    if(m_sequenceNumber != INVALID_SEQUENCE_NUMBER)
    {
        stream << ", seqNum=" << m_sequenceNumber;
    }

    RETURN(stream.str());
}

}
