///////////////////////////////////////////////////////////////////////////////
//
// MessageSerialisedData.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <sstream>

#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessageSerialisedData.h"

namespace threeway
{

MessageSerialisedData::MessageSerialisedData() :
    SerialisedData(SERIALISATION_ID_INVALID, NULL, 0),
    m_status(MessageSerialisedData::CONNECTIONLESS),
    m_fromEntity(ENTITY_INVALID),
    m_toEntity(ENTITY_INVALID),
    m_localConnectionId(ConnectionIdentifierUnused),
    m_remoteConnectionId(ConnectionIdentifierUnused)
{
    SetDomain(Queueable::MESSAGE_SERIALISED_DATA);
}

MessageSerialisedData::MessageSerialisedData(MessagingEntity fromEntity, MessagingEntity toEntity,
                                             u32 serialisationId, const u8* serialData, u32 dataLength) :
    SerialisedData(serialisationId, serialData, dataLength),
    m_status(MessageSerialisedData::CONNECTIONLESS),
    m_fromEntity(fromEntity),
    m_toEntity(toEntity),
    m_localConnectionId(ConnectionIdentifierUnused),
    m_remoteConnectionId(ConnectionIdentifierUnused)
{
    SetDomain(Queueable::MESSAGE_SERIALISED_DATA);
}

// Constructor for connection orientated messages
MessageSerialisedData::MessageSerialisedData(const MessagingEntity fromEntity, const MessagingEntity toEntity,
                      const MessagingConnectionIdentifier localConnectionId,
                      const MessagingConnectionIdentifier remoteConnectionId,
                      const u32 serialisationId, const u8* serialData, const u32 dataLength) :
    SerialisedData(serialisationId, serialData, dataLength),
    m_status(MessageSerialisedData::CONNECTED),
    m_fromEntity(fromEntity),
    m_toEntity(toEntity),
    m_localConnectionId(localConnectionId),
    m_remoteConnectionId(remoteConnectionId)
{
    SetDomain(Queueable::MESSAGE_SERIALISED_DATA);
}

// Constructor for close of connection, with no message
MessageSerialisedData::MessageSerialisedData(const MessagingEntity fromEntity, const MessagingEntity toEntity,
                      const MessagingConnectionIdentifier localConnectionId,
                      const MessagingConnectionIdentifier remoteConnectionId) :
    SerialisedData(SERIALISATION_ID_INVALID, NULL, 0),
    m_status(MessageSerialisedData::CONNECTION_DELETED),
    m_fromEntity(fromEntity),
    m_toEntity(toEntity),
    m_localConnectionId(localConnectionId),
    m_remoteConnectionId(remoteConnectionId)
{
    SetDomain(Queueable::MESSAGE_SERIALISED_DATA);
}

MessageSerialisedData::~MessageSerialisedData()
{
}

void MessageSerialisedData::SetConnectionless(const MessagingEntity fromEntity, const MessagingEntity toEntity)
{
    m_status     = MessageSerialisedData::CONNECTIONLESS,
    m_fromEntity = fromEntity;
    m_toEntity   = toEntity;
}

void MessageSerialisedData::SetConnectionOrientated(const Status status,
                                                   const MessagingConnectionIdentifier localConnectionId,
                                                   const MessagingConnectionIdentifier remoteConnectionId)
{
    m_status             = status;
    m_localConnectionId  = localConnectionId;
    m_remoteConnectionId = remoteConnectionId;
}

void MessageSerialisedData::SetEntities(const MessagingEntity fromEntity, const MessagingEntity toEntity)
{
    m_fromEntity = fromEntity;
    m_toEntity   = toEntity;
}

std::string MessageSerialisedData::ToString() const
{
    std::ostringstream stream;

    stream << SerialisedData::ToString() << ", ";

    switch (m_status)
    {
        case MessageSerialisedData::CONNECTIONLESS:
            stream << "Connectionless";
            break;

        case MessageSerialisedData::NEW_CONNECTION:
            stream << "New Connection";
            break;

        case MessageSerialisedData::CONNECTED:
            stream << "Connected";
            break;

        case MessageSerialisedData::CONNECTION_DELETED:
            stream << "Connection Deleted";
            break;

        case MessageSerialisedData::CONNECTION_REFUSED:
            stream << "Connection Refused";
            break;

        case MessageSerialisedData::INVALID:
            stream << "Invalid";
            break;

        default:
            stream << "Unknown" << (u32)m_status;
            break;
    }

    stream << ", " << MessagingEntityToString(m_fromEntity)
           << " -> " << MessagingEntityToString(m_toEntity);

    if(m_status != MessageSerialisedData::CONNECTIONLESS)
    {
        stream << ", local=" << m_localConnectionId
               << ", remote=" << m_remoteConnectionId
               << ", " << SerialisedData::ToString();
    }

    return(stream.str());
}

}
