///////////////////////////////////////////////////////////////////////////////
//
// MessageRouteEntry.h
//
// This is a messaging route information class - it is used to configure
// messaging routes and store routes in the RoutingTable.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessageRouteEntry_h_
#define __MessageRouteEntry_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <3waytypes.h>
#include <comms/IPv4Address.h>
#include <messaging/transport/MessagingEntity.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////
namespace threeway
{

class MessageRouteEntry
{
public:
    
    /**
     * Construction / destruction.
     */
    MessageRouteEntry();
    MessageRouteEntry(MessagingEntity entity, IPv4Address& entityIpAddress, u16 entityPort);
    MessageRouteEntry(const MessageRouteEntry& rhs);
    virtual ~MessageRouteEntry() {};

    /**
     * Operators.
     */
    MessageRouteEntry& operator=(const MessageRouteEntry& rhs);
    bool operator==(const MessageRouteEntry &route) const;
    bool operator!=(const MessageRouteEntry &route) const;
    bool operator<(const MessageRouteEntry &route) const;
    bool operator>(const MessageRouteEntry &route) const;

    /**
     * Accessors.
     */
    MessagingEntity GetEntity() const { return m_entity; };
    IPv4Address     GetIpAddress() const { return m_ipAddress; };
    u16             GetPort() const { return m_port; };
    
    void SetIpAddress(const IPv4Address ipAddress) { m_ipAddress = ipAddress; };
    
    // Is this a localhost route?
    bool isLocalHost(void) const;

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
    
    MessagingEntity m_entity;
    IPv4Address     m_ipAddress;
    u16             m_port;
};

}

#endif
