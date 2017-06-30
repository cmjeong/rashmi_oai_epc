
///////////////////////////////////////////////////////////////////////////////
//
// TemperatureMonitor.cpp
//
// Code for the temperature monitoring class.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <platform/FapAlarmId.h>
#include <messaging/messages/common/MfOpStateInformInd.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TemperatureMonitor.h"
#include "managed-objects/FapMO.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

TemperatureMonitor::TemperatureMonitor(const threeway::SendMessageInterface& sendMessageInterface) :
    m_sendMessageInterface(sendMessageInterface),
    m_smoothedTemperatureDegC10(250),
    m_status(TEMPERATURE_NORMAL)
{
}

void TemperatureMonitor::SetNewBoardTemperature(s32 newBoardTempDegC)
{
    ENTER();

    m_smoothedTemperatureDegC10 = ((m_smoothedTemperatureDegC10 * 8) + (newBoardTempDegC * 20)) / 10;
    TRACE_LEV(TRACE_VERBOSE, "SmoothedTemperature", m_smoothedTemperatureDegC10 / 10);

    TemperatureStatus previousStatus = m_status;

    // TODO: Do we need some hysteresis here to avoid rapid alarms/op state changes?
    if (m_smoothedTemperatureDegC10 > TEMPERATURE_HIGH_CRITICAL_LIMIT)
    {
        m_status = TEMPERATURE_CRITICAL;
    }
    else if (m_smoothedTemperatureDegC10 > TEMPERATURE_HIGH_ALARM_LIMIT)
    {
        m_status = TEMPERATURE_HIGH;
    }
    else if (m_smoothedTemperatureDegC10 < TEMPERATURE_LOW_ALARM_LIMIT)
    {
        m_status = TEMPERATURE_LOW;
    }
    else
    {
        m_status = TEMPERATURE_NORMAL;
    }

    if (m_status != previousStatus)
    {
        // If the temperature has become critical, disable the transmitter, otherwise enable it.
        if(m_status == TEMPERATURE_CRITICAL)
        {
            // Has become critical, disable transmitter.
            MfOpStateInformInd opStateInform(MF_TEMPERATURE_MONITOR, ManagedObject::OP_STATE_DISABLED, 0, "Over Temperature");
            m_sendMessageInterface.SendMessage(opStateInform, ENTITY_OAM, ENTITY_OAM);
        }
        else if(previousStatus == TEMPERATURE_CRITICAL)
        {
            // Was critical but no longer critical so allow transmitter to go enabled.
            MfOpStateInformInd opStateInform(MF_TEMPERATURE_MONITOR, ManagedObject::OP_STATE_ENABLED, 0, "Temperature OK");
            m_sendMessageInterface.SendMessage(opStateInform, ENTITY_OAM, ENTITY_OAM);
        }

        // Raise/clear an alarm if necessary.
        ostringstream alarmText;
        alarmText << "BoardTemperature=" << newBoardTempDegC << ", SmoothedTemperature=" << GetSmoothedValueDegC();
        TRACE_PRINTF("%s", alarmText.str().c_str());

        switch (m_status)
        {
        case TemperatureMonitor::TEMPERATURE_CRITICAL:
        case TemperatureMonitor::TEMPERATURE_HIGH:
        {
            // Raise a high temperature alarm.
            // Check that we have changed from a previous state that wasn't high or critical
            // before sending an alarm to avoid duplicates.
            if((previousStatus != TemperatureMonitor::TEMPERATURE_CRITICAL) && (previousStatus != TemperatureMonitor::TEMPERATURE_HIGH))
            {
                shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::OVER_TEMPERATURE_OPERATIONAL_THRESHOLD));
                AlarmEvent alarmEvent(alarmId,
                        AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                        AlarmEvent::ALARM_SEVERITY_WARNING,
                        alarmText.str(),
                        AlarmEvent::ALARM_TYPE_ENVIRONMENT);
                m_sendMessageInterface.SendMessage(alarmEvent, ENTITY_OAM, ENTITY_OAM);
            }
        }
            break;

        case TemperatureMonitor::TEMPERATURE_NORMAL:
        {
            if((previousStatus == TemperatureMonitor::TEMPERATURE_HIGH) || (previousStatus == TemperatureMonitor::TEMPERATURE_CRITICAL))
            {
                // We're getting cooler so clear the over-temperature alarm.
                shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::OVER_TEMPERATURE_OPERATIONAL_THRESHOLD));
                AlarmEvent alarmEvent(alarmId,
                        AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                        AlarmEvent::ALARM_SEVERITY_CLEARED,
                        alarmText.str(),
                        AlarmEvent::ALARM_TYPE_ENVIRONMENT);
                m_sendMessageInterface.SendMessage(alarmEvent, ENTITY_OAM, ENTITY_OAM);
            }
            else
            {
                // We're getting warmer so clear the under-temperature alarm.
                shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::UNDER_TEMPERATURE_OPERATIONAL_THRESHOLD));
                AlarmEvent alarmEvent(alarmId,
                        AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                        AlarmEvent::ALARM_SEVERITY_CLEARED,
                        alarmText.str(),
                        AlarmEvent::ALARM_TYPE_ENVIRONMENT);
                m_sendMessageInterface.SendMessage(alarmEvent, ENTITY_OAM, ENTITY_OAM);
            }
        }
            break;

        case TemperatureMonitor::TEMPERATURE_LOW:
        {
            // Raise a low temperature alarm.
            shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::UNDER_TEMPERATURE_OPERATIONAL_THRESHOLD));
            AlarmEvent alarmEvent(alarmId,
                    AlarmEvent::ALARM_EVENT_NONTRANSIENT,
                    AlarmEvent::ALARM_SEVERITY_WARNING,
                    alarmText.str(),
                    AlarmEvent::ALARM_TYPE_ENVIRONMENT);
            m_sendMessageInterface.SendMessage(alarmEvent, ENTITY_OAM, ENTITY_OAM);
        }
            break;

        default:
            RSYS_ASSERT(false);
            break;
        }

    }

    EXIT();
}
