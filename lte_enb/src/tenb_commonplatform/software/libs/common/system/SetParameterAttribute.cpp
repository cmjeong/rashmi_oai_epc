///////////////////////////////////////////////////////////////////////////////
//
// SetParameterAttribute.cpp
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

#include "SetParameterAttribute.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SetParameterAttribute::SetParameterAttribute() :
    m_name(),
    m_notification(SET_PARAMETER_ATTRIBUTE_NOTIFICATION_END)
{
}

SetParameterAttribute::SetParameterAttribute( string & name,
        SetParameterAttributeNotification notification ) :

    m_name(name),
    m_notification(notification)
{
}

s32 SetParameterAttribute::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_name.length() > 0);
    RSYS_ASSERT(
            (m_notification >= SET_PARAMETER_ATTRIBUTE_NOTIFICATION_BEGIN) &&
            (m_notification < SET_PARAMETER_ATTRIBUTE_NOTIFICATION_END) );

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(SERIALISATION_FORMAT, serialisedData);

    SerialiseIt(m_name, serialisedData);

    SerialiseIt(u8(m_notification), serialisedData);

    RETURN(serialisedData - data);
}

bool SetParameterAttribute::DeSerialise(const u8* data, u32 dataLen)
{
    // Preconditions.
    if(dataLen < 3)
        RETURN(false);

    // Check the format.
    u8 format;
    DeSerialiseIt(format, data);
    if(format != SERIALISATION_FORMAT)
    {
        TRACE_PRINTF("Can't DeSerialise as data is wrong format.  Expecting %u, got %u.", SERIALISATION_FORMAT, format);
        return false;
    }

    // Deserialise all the members.
    u8 deserialisedByte;

    DeSerialiseIt(m_name, data, ATTRIBUTE_NAME_MAX_LENGTH);

    DeSerialiseIt(deserialisedByte, data);
    m_notification = (SetParameterAttributeNotification)deserialisedByte;

    return true;
}

std::string SetParameterAttribute::ToString() const
{
    ostringstream stream;

    stream << "name=" << m_name << ", notify " << u32(m_notification);

    return stream.str();
}

}
