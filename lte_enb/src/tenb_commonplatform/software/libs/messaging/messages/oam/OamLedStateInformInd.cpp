///////////////////////////////////////////////////////////////////////////////
//
// OamLedStateInformInd.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "OamLedStateInformInd.h"

using namespace std;
using namespace boost;
using namespace threeway;


OamLedStateInformInd::OamLedStateInformInd() :
        m_ledId(),
        m_ledColour(),
        m_ledPattern()
{
}

OamLedStateInformInd::OamLedStateInformInd(u32 ledId, LedColour colour, LedPattern pattern) :
        m_ledId(ledId),
        m_ledColour(colour),
        m_ledPattern(pattern)
{
}


s32 OamLedStateInformInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    RSYS_ASSERT(dataMaxBytes >= 12 /* 3 x u32 */);

    const u8* const dataStart = data;

    SerialiseIt(m_ledId, data);
    SerialiseIt((u32)m_ledColour, data);
    SerialiseIt((u32)m_ledPattern, data);

    return (data - dataStart);
}


bool OamLedStateInformInd::DeSerialise(const u8* data, u32 dataLen)
{
    RSYS_ASSERT(dataLen == 12 /* 3 x u32 */);

    DeSerialiseIt(m_ledId, data);

    u32 colour;
    DeSerialiseIt(colour, data);
    m_ledColour = (LedColour)colour;

    u32 pattern;
    DeSerialiseIt(pattern, data);
    m_ledPattern = (LedPattern)pattern;

    return true;
}


string OamLedStateInformInd::ToString() const
{
    ostringstream stream;

    stream << "OamLedStateInformInd { ledId: " << m_ledId
           << ", colour " << ledColourToString(m_ledColour)
           << ", pattern " << ledPatternToString(m_ledPattern) << " }";

    return(stream.str());
}

string OamLedStateInformInd::ToBriefString() const
{
    ostringstream stream;

    stream << "led=" << m_ledId;
    if(m_ledPattern != LED_SET_OFF)
    {
        stream << " state=" << ledColourToString(m_ledColour);
        if(m_ledPattern != LED_SET_ON)
        {
            stream << "/" << ledPatternToString(m_ledPattern);
        }
    }
    else
    {
        stream << " state=OFF";
    }

    return(stream.str());
}


