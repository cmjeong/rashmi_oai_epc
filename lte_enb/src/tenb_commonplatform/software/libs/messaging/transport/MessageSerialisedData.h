///////////////////////////////////////////////////////////////////////////////
//
// MessageSerialisedData.h
//
// MessageSerialisedData is a helper class used to pass the "raw" data received 
// from a Messenger up to the user application, where it can be DeSerialised.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessageSerialisedData_h_
#define __MessageSerialisedData_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>
#include <string>
#include <system/SerialisedData.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessagingEntity.h"
#include "ConnectionIdentifier.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MessageSerialisedData : public SerialisedData
{
public:
    typedef enum Status_tag
    {
        CONNECTIONLESS,         // The default, this message is connectionless
        NEW_CONNECTION,         // The first connection orientated message on a new connection
        CONNECTED,              // Connection orientated with existing connection
        CONNECTION_DELETED,     // Indication that an existing connection has gone
        CONNECTION_REFUSED,     // A new connection was refused by the far end
        
        INVALID                 // For reporting errors
    } Status;

    MessageSerialisedData();
    
    // Constructor for connectionless messages
    MessageSerialisedData(const MessagingEntity fromEntity, const MessagingEntity toEntity, 
                          const u32 serialisationId, const u8* serialData, const u32 dataLength);

    // Constructor for connection orientated messages
    MessageSerialisedData(const MessagingEntity fromEntity, const MessagingEntity toEntity, 
                          const MessagingConnectionIdentifier localConnectionId,
                          const MessagingConnectionIdentifier remoteConnectionId,
                          const u32 serialisationId, const u8* serialData, const u32 dataLength);
    
    // Constructor for close of connection, with no message
    MessageSerialisedData(const MessagingEntity fromEntity, const MessagingEntity toEntity, 
                          const MessagingConnectionIdentifier localConnectionId,
                          const MessagingConnectionIdentifier remoteConnectionId);

    virtual ~MessageSerialisedData();
    
    // Accessors
    Status          GetStatus(void) const { return m_status; };
    MessagingEntity GetFromEntity(void) const { return m_fromEntity; };
    MessagingEntity GetToEntity(void) const { return m_toEntity; };
    MessagingConnectionIdentifier GetLocalConnectionId(void) const { return m_localConnectionId; };
    MessagingConnectionIdentifier GetRemoteConnectionId(void) const { return m_remoteConnectionId; };
    
    void SetConnectionless(const MessagingEntity fromEntity, const MessagingEntity toEntity);
    void SetConnectionOrientated(const Status status, 
                                 const MessagingConnectionIdentifier localConnectionId,
                                 const MessagingConnectionIdentifier remoteConnectionId);
    void SetStatus(const Status status) { m_status = status; };
    void SetEntities(const MessagingEntity fromEntity, const MessagingEntity toEntity);
    
    // Convert to string for debug.
    virtual std::string ToString() const;
    
private:
    Status          m_status;
    MessagingEntity m_fromEntity;
    MessagingEntity m_toEntity;

    // For connection orientated messages
    MessagingConnectionIdentifier m_localConnectionId;
    MessagingConnectionIdentifier m_remoteConnectionId;
        
};


} // namespace threeway

#endif
