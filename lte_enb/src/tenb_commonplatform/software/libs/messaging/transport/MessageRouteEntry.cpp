///////////////////////////////////////////////////////////////////////////////
//
// MessageRouteEntry.cpp
//
// See header file for documentation.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessageRouteEntry.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

MessageRouteEntry::MessageRouteEntry() :
    m_entity(),
    m_port(0)
{
}

MessageRouteEntry::MessageRouteEntry(MessagingEntity entity, IPv4Address& entityIpAddress, u16 entityPort) :
    m_entity(entity),
    m_ipAddress(entityIpAddress),
    m_port(entityPort)
{
}

MessageRouteEntry::MessageRouteEntry(const MessageRouteEntry& rhs)
{
    m_entity    = rhs.m_entity;
    m_ipAddress = rhs.m_ipAddress;
    m_port      = rhs.m_port;
}

MessageRouteEntry& MessageRouteEntry::operator=(const MessageRouteEntry& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    
    m_entity    = rhs.m_entity;
    m_ipAddress = rhs.m_ipAddress;
    m_port      = rhs.m_port;
    
    return *this;
}

bool MessageRouteEntry::operator==(const MessageRouteEntry &route) const
{
    return ((m_entity    == route.m_entity)    &&
            (m_ipAddress == route.m_ipAddress) &&
            (m_port      == route.m_port));
}

bool MessageRouteEntry::operator!=(const MessageRouteEntry &route) const
{
    return (!operator==(route));
}

bool MessageRouteEntry::operator<(const MessageRouteEntry &route) const
{
    if (m_entity < route.m_entity)
        return true;
    else if ((m_entity == route.m_entity) && (m_ipAddress < route.m_ipAddress))
        return true;
    else if ((m_entity == route.m_entity) && (m_ipAddress == route.m_ipAddress) && (m_port < route.m_port))
        return true;
    else
        return false;
}

bool MessageRouteEntry::operator>(const MessageRouteEntry &route) const
{
    return (!operator==(route) && !operator<(route));
}

// Is this a localhost route?
bool MessageRouteEntry::isLocalHost(void) const
{
    if (m_ipAddress == IPv4Address(127, 0, 0, 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

s32 MessageRouteEntry::Serialise(u8* data, u32 dataMaxBytes) const
{
    // Serialise to:
    //   1 byte  - entity
    //   4 bytes - IP Address
    //   2 bytes - UDP Port
    
    const u32 len = 7; // as above

    if (dataMaxBytes >= len)
    {
        data[0] = (u8)m_entity;
        if (!m_ipAddress.GetDigits(data[1], data[2], data[3], data[4]))
        {
            return -1;
        }
        data[5] = m_port >> 8;
        data[6] = m_port & 0xFF;
    
        return len;
    }
    else
    {
        return -1;
    }
}

s32 MessageRouteEntry::DeSerialise(const u8* data, u32 dataLen)
{
    // Deserialise from:
    //   1 byte  - entity
    //   4 bytes - IP Address
    //   2 bytes - UDP Port
    
    const u32 len = 7; // as above

    if (dataLen >= len)
    {
        m_entity = (MessagingEntity)data[0];
        
        m_ipAddress.SetDigits(data[1], data[2], data[3], data[4]);

        m_port  = data[5] << 8;
        m_port |= data[6];

        return len;
    }
    else
    {
        return -1;
    }
}

string MessageRouteEntry::ToString() const
{
    ostringstream stream;

    stream << MessagingEntityToString(m_entity)
           << " " << m_ipAddress.ToString()
           << ":" << (u32)m_port;

    return stream.str();
}
