///////////////////////////////////////////////////////////////////////////////
//
// MessageRoutingTable.cpp
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

#include "MessageRoutingTable.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

MessageRoutingTable::MessageRoutingTable() :
    m_hasDefaultRoute(false)
{
}

MessageRoutingTable::MessageRoutingTable(const MessageRouteEntry& defaultRoute) :
    m_hasDefaultRoute(true),
    m_defaultRoute(defaultRoute)
{
}

MessageRoutingTable::MessageRoutingTable(const MessageRoutingTable& rhs)
{
    m_hasDefaultRoute   = rhs.m_hasDefaultRoute;
    m_defaultRoute      = rhs.m_defaultRoute;
    
    m_routes.clear();
    m_routes = rhs.m_routes;
}

MessageRoutingTable::~MessageRoutingTable()
{
}

MessageRoutingTable& MessageRoutingTable::operator=(const MessageRoutingTable& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    
    m_hasDefaultRoute   = rhs.m_hasDefaultRoute;
    m_defaultRoute      = rhs.m_defaultRoute;
    
    m_routes.clear();
    m_routes = rhs.m_routes;
    
    return *this;
}

bool MessageRoutingTable::GetRoute(const MessagingEntity entity, MessageRouteEntry& route)
{
    bool foundRoute = false;
    
    Routes::const_iterator routeIter = m_routes.find(entity);
    if (routeIter != m_routes.end())
    {
        route      = routeIter->second;
        foundRoute = true;
    }
    else if (m_hasDefaultRoute)
    {
        route      = m_defaultRoute;
        foundRoute = true;
    }
    
    return foundRoute;
}

bool MessageRoutingTable::GetDefaultRoute(MessageRouteEntry& route)
{
    bool foundRoute = false;
    
    if (m_hasDefaultRoute)
    {
        route      = m_defaultRoute;
        foundRoute = true;
    }
    
    return foundRoute;
}

void MessageRoutingTable::AddRoute(const MessagingEntity entity, const MessageRouteEntry& route)
{
    m_routes[entity] = route;
}

void MessageRoutingTable::AddDefaultRoute(const MessageRouteEntry& route)
{
    m_hasDefaultRoute = true;
    m_defaultRoute    = route;
}

void MessageRoutingTable::ClearRoutingTable(void)
{
    m_routes.clear();
}

void MessageRoutingTable::VisitAllRoutes(u32 token, MessageRoutingTableVisitor& visitor)
{
    for (Routes::iterator routeIter = m_routes.begin(); routeIter != m_routes.end(); routeIter++)
    {
        visitor.MessageRouteVisit(routeIter->second, token);
    }
}

bool MessageRoutingTable::IsEntityPresent(const MessagingEntity& entity)
{
    return m_routes.find(entity) != m_routes.end();
}

s32 MessageRoutingTable::Serialise(u8* data, u32 dataMaxBytes) const
{
    // Serialise to:
    //   1 byte  - bool, hasDefaultRoute
    //   1 byte  - number of routing table entries
    //   optional N bytes   - RouteEntry, default route (only present if hasDefaultRoute is true)
    //   optional MxN bytes - MxRouteEntry, the routing table
    
    const u32 minLen = 2; // as above
    int i = 0;
    int numBytes;
    
    if (dataMaxBytes >= minLen)
    {
        data[i++] = (u8)m_hasDefaultRoute;
        data[i++] = (u8)m_routes.size();
        
        if (m_hasDefaultRoute)
        {
            numBytes = m_defaultRoute.Serialise(&data[i], dataMaxBytes - i);
            if (numBytes >= 0)
            {
                i += numBytes;
            }
            else
            {
                return -1;
            }
        }
        
        for (Routes::const_iterator routeIter = m_routes.begin(); routeIter != m_routes.end(); routeIter++)
        {
            numBytes = routeIter->second.Serialise(&data[i], dataMaxBytes - i);
            if (numBytes >= 0)
            {
                i += numBytes;
            }
            else
            {
                return -1;
            }
        }
        
        return i;
    }
    else
    {
        return -1;
    }
}

s32 MessageRoutingTable::DeSerialise(const u8* data, u32 dataLen)
{
    // Deserialise from:
    //   1 byte  - bool, hasDefaultRoute
    //   1 byte  - number of routing table entries
    //   optional N bytes   - RouteEntry, default route (only present if hasDefaultRoute is true)
    //   optional MxN bytes - MxRouteEntry, the routing table
    
    const u32 minLen = 2; // as above
    int i = 0;
    int numRoutes, numBytes;

    if (dataLen >= minLen)
    {
        m_hasDefaultRoute = (bool)data[i++];
        numRoutes         = data[i++];
        
        if (m_hasDefaultRoute)
        {
            numBytes = m_defaultRoute.DeSerialise(&data[i], dataLen - i);
            if (numBytes >= 0)
            {
                i += numBytes;
            }
            else
            {
                return -1;
            }
        }
        
        m_routes.clear();

        while (numRoutes)
        {
            MessageRouteEntry route;
            numBytes = route.DeSerialise(&data[i], dataLen - i);
            if (numBytes >= 0)
            {
                m_routes[route.GetEntity()] = route;
                i += numBytes;
            }
            else
            {
                return -1;
            }
            
            numRoutes--;
        }
        
        return i;
    }
    else
    {
        return -1;
    }
}

string MessageRoutingTable::ToString() const
{
    ostringstream stream;

    if (m_hasDefaultRoute)
    {
        stream << "Routing Table (default " << m_defaultRoute.ToString() << "):" << std::endl;
    }
    else
    {
        stream << "Routing Table (no default route):" << std::endl;
    }
    
    for (Routes::const_iterator routeIter = m_routes.begin(); routeIter != m_routes.end(); routeIter++)
    {
        stream << "   " << routeIter->second.ToString() << std::endl;
    }

    return stream.str();
}
