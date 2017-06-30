///////////////////////////////////////////////////////////////////////////////
//
// $Id: CarbLedSetReq.cpp 17544 2009-09-16 17:20:15Z mmcternan $
//
// See header file for documentation.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CarbLedSetReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CarbLedSetReq::CarbLedSetReq(led_intensity_t led[NUM_LEDS], bool pulsate[NUM_LEDS])
{
    u8 t;

    for(t = 0; t < NUM_LEDS; t++)
    {
        m_ledState.intensity[t] = led[t];
        m_ledState.pulsate[t]   = pulsate[t];
    }
}


CarbLedSetReq::CarbLedSetReq(led_intensity_t led0, led_intensity_t led1, led_intensity_t led2)
{
    m_ledState.intensity[0] = led0; m_ledState.pulsate[0] = false;
    m_ledState.intensity[1] = led1; m_ledState.pulsate[1] = false;
    m_ledState.intensity[2] = led2; m_ledState.pulsate[2] = false;
}


s32 CarbLedSetReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    if (dataMaxBytes < sizeof(m_ledState))
        return -1;

    memcpy(data, &m_ledState, sizeof(m_ledState));

    return sizeof(m_ledState);
}


bool CarbLedSetReq::DeSerialise(const u8* data, u32 dataLen)
{
    if (dataLen >= sizeof(m_ledState))
    {
        memcpy(&m_ledState, data, sizeof(m_ledState));

        return true;
    }

    return false;
}


string CarbLedSetReq::ToString() const
{
    ostringstream stream;
    u8            t;

    stream << "CarbLedSetReq {" << endl;

    for(t = 0; t < NUM_LEDS; t++)
    {
        stream << "  " << (u32)m_ledState.intensity[t] << (m_ledState.pulsate[t] ? " pulsating" : "") << endl;
    }

    stream << "}" << endl;

    return(stream.str());
}

// END OF FILE
