///////////////////////////////////////////////////////////////////////////////
//
// MessageRoutingTable.h
//
// Message MessageRoutingTable class.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessageRoutingTable_h_
#define __MessageRoutingTable_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>

#include <3waytypes.h>
#include <comms/IPv4Address.h>
#include <messaging/transport/MessagingEntity.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessageRouteEntry.h"

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////
namespace threeway
{

// Visitor interface class
class MessageRoutingTableVisitor
{
public:
    virtual ~MessageRoutingTableVisitor () {}
    
    /**
     * Visitor callback function
     */
    virtual void MessageRouteVisit(MessageRouteEntry& route, u32 token) = 0; 
};


class MessageRoutingTable
{
public:
    
    /**
     * Construction / destruction.
     */
    MessageRoutingTable();
    MessageRoutingTable(const MessageRouteEntry& defaultRoute);
    MessageRoutingTable(const MessageRoutingTable& rhs);
    virtual ~MessageRoutingTable();

    /**
     * Operators.
     */
    MessageRoutingTable& operator=(const MessageRoutingTable& rhs);

    /**
     * Accessors.
     */
     
    // Try to find a route for the given entity. Returns true if route
    // found, false otherwise. 
    bool GetRoute(const MessagingEntity entity, MessageRouteEntry& route);
    bool GetDefaultRoute(MessageRouteEntry& route);

    // Add a new route
    void AddRoute(const MessagingEntity entity, const MessageRouteEntry& route);
    
    // Add a new default route (will replace any existing default route)
    void AddDefaultRoute(const MessageRouteEntry& route);
    
    // Clear routing table
    void ClearRoutingTable(void);

    // Visit all the entries in the routing table
    void VisitAllRoutes(u32 token, MessageRoutingTableVisitor& visitor);
    
    /**
     * Check if an entity is in the table.
     */
    bool IsEntityPresent(const MessagingEntity& entity);

    /**
     * Serialisors for use in messages.
     * N.B: both these functions return -1 on error, the number of
     *      bytes (de)serialised on success.
     */
    s32 Serialise(u8* data, u32 dataMaxBytes) const;
    s32 DeSerialise(const u8* data, u32 dataLen);
    
    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    // Optional default route if no route exists for a given entity
    bool               m_hasDefaultRoute;
    MessageRouteEntry  m_defaultRoute;

    // The routing table
    typedef std::map < MessagingEntity, MessageRouteEntry > Routes;
    Routes m_routes;
    
};

}

#endif
