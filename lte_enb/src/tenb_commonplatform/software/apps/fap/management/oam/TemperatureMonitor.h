
///////////////////////////////////////////////////////////////////////////////
//
// TemperatureMonitor.h
//
// Class for monitoring temperature of the FAP.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TemperatureMonitor_h_
#define __TemperatureMonitor_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <messaging/transport/ApplicationWithMessaging.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class TemperatureMonitor
{
public:
    // The limits below are defined in tenths of a degree
    static const s32 TEMPERATURE_HIGH_ALARM_LIMIT = 810;
    static const s32 TEMPERATURE_LOW_ALARM_LIMIT = 0;
    static const s32 TEMPERATURE_HIGH_CRITICAL_LIMIT = 860;

    typedef enum
    {
        TEMPERATURE_LOW,
        TEMPERATURE_NORMAL,
        TEMPERATURE_HIGH,
        TEMPERATURE_CRITICAL
    } TemperatureStatus;

    /**
     * Constructor/destructor.
     */
    TemperatureMonitor(const threeway::SendMessageInterface& sendMessageInterface);
    ~TemperatureMonitor() {};

    /**
     * Tell the temperature monitor about a new temperature reading for the board.
     */
    void SetNewBoardTemperature(s32 newBoardTempDegC);

private:
    const threeway::SendMessageInterface& m_sendMessageInterface;
    s32               m_smoothedTemperatureDegC10;
    TemperatureStatus m_status;

    s32 GetSmoothedValueDegC() const { return m_smoothedTemperatureDegC10 / 10; }
};

#endif // __TemperatureMonitor_h_
