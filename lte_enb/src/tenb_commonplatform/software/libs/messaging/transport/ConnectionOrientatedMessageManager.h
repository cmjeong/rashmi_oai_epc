///////////////////////////////////////////////////////////////////////////////
//
// ConnectionOrientatedMessageManager.h
//
// Class to provide connection management behaviour for
// applications that require it.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

/** DELETE THIS
 * Use this template for C/C++ header files.
 *  - Fill in the header above.
 *  - Delete sections below that are empty (to make it easier to read).
 *  - Don't forget to replace __Template_h_ with __<Your Filename Stem>_h__
 */

#ifndef __ConnectionOrientatedMessageManager_h_
#define __ConnectionOrientatedMessageManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <boost/shared_ptr.hpp>
#include <system/ThreadWithQueue.h>
#include <system/Serialisable.h>
#include <messaging/messages/common/MessagingDataInd.h>

/** DELETE THIS
 * Add all your system includes in <>
 */

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "Messenger.h"
#include "MessageSerialisedData.h"
#include "MessageHandler.h"

using namespace std;
using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ConnectionOrientatedMessageManager : public IMessageHandler
{

public:
    ConnectionOrientatedMessageManager( MessagingEntity entity, SendMessageInterface & sendMessageInterface);
    ~ConnectionOrientatedMessageManager();

    /**
     * Connection Orientated message handling.
     *
     * These methods provide provide virtual connections over a link the a
     * destination entity, similar to SCCP. The connection is identified by
     * a identifier supplied by this class when the initial message is sent.
     * The constanst ConnectionIdentifierUnused may be used to indicate
     * a no connection.
     */

    /**
     * Intiates a new connection and sends the message over it.  The confirmation
     * or rejection of this connection will be handled by the application framework.
     *
     * \param messageToSend     The payload message to send over this new connection.
     * \param destinationEntity Destination messaging entity.
     * \param newConnectionId   Receives the new identifier.
     * \return                  true on successful send of message, false otherwise.
     */
    virtual bool SendInitialCoMessage(Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingConnectionIdentifier& newConnectionId, MessagingEntity sourceEntity = ENTITY_INVALID);

    /**
     * Sends the message over an existing connection.
     *
     * \param messageToSend     The payload message to send over this new connection.
     * \param connectionId      The identifier supplied by SendInitialCoMessage.
     * \return                  true on successful send of message, false otherwise.
     */
    virtual bool SendCoMessage(Serialisable& messageToSend, MessagingConnectionIdentifier connectionId);

    /**
     * Closes a connection, this attempts a graceful release with the peer. If this
     * fails the application framework will do a local end release.
     *
     * \param connectionId      The identifier supplied by SendInitialCoMessage.
     * \return                  none, once called the connection will be gone, one way or another.
     */
    virtual void ReleaseConnection(MessagingConnectionIdentifier connectionId);

    /**
     * Return internal connection table as a string.
     * This function can be used to provide this connection information
     * to any cli command that requires it.
     */
    std::string ConnectionTableToString(const char *entityName) const;

    /**
     * Return TRUE if connection ID is valid, FALSE otherwise.
     * This function can be used to find whether the connection ID
     * exists in the connection list.
     */
    bool IsConnectionValid(MessagingConnectionIdentifier connectionId);

protected:

    bool HandleReceivedConnectionRequest(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier sourceConnectionId);
    bool HandleReceivedConnectionConfirm(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier sourceConnectionId, MessagingConnectionIdentifier destConnectionId);
    bool HandleReceivedConnectionRefused(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier destConnectionId);
    bool HandleReceivedReleaseRequest(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier sourceConnectionId, MessagingConnectionIdentifier destConnectionId);
    bool HandleReceivedReleaseConfirm(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier sourceConnectionId, MessagingConnectionIdentifier destConnectionId);

private:
    // Source of local connection ids
    MessagingConnectionIdentifier m_nextConnectionIdentifier;

    class FindLocalId
    {
    public:
        FindLocalId(MessagingConnectionIdentifier id) : m_id(id) {}

        MessagingConnectionIdentifier m_id;
    };

    class FindRemote
    {
    public:
        FindRemote(MessagingConnectionIdentifier id, MessagingEntity remoteEntity) : m_id(id), m_remoteEntity(remoteEntity) {}

        MessagingConnectionIdentifier m_id;
        MessagingEntity               m_remoteEntity;
    };

    // Class to queue messages in MessagingConnection
    class MessagingConnectionQueuedMessage
    {
        friend class ApplicationWithMessaging;

    public:

        MessagingConnectionQueuedMessage() :
            m_fromEntity(ENTITY_INVALID),
            m_toEntity(ENTITY_INVALID)
        {}

        MessagingConnectionQueuedMessage(MessagingEntity fromEntity, MessagingEntity toEntity, shared_ptr<MessagingDataInd> messagingDataInd) :
            m_fromEntity(fromEntity),
            m_toEntity(toEntity)
        {
            m_messagingDataInd = messagingDataInd;
        }

        MessagingEntity                 m_fromEntity;
        MessagingEntity                 m_toEntity;
        shared_ptr<MessagingDataInd>    m_messagingDataInd;
    };

    // Connection handling class
    class MessagingConnection
    {
        friend class ApplicationWithMessaging;

    public:
        typedef enum
        {
            MSG_CONN_STATE_DISCONNECTED,
            MSG_CONN_STATE_AWAITING_CONN_CONF,
            MSG_CONN_STATE_CONNECTED,
            MSG_CONN_STATE_AWAITING_REL_CONF,

            MSG_CONN_STATE_NUM_STATES
        } ConnectionState;

        MessagingConnection() :
            m_localId(ConnectionIdentifierUnused),
            m_localEntity(ENTITY_INVALID),
            m_remoteId(ConnectionIdentifierUnused),
            m_remoteEntity(ENTITY_INVALID),
            m_state(MSG_CONN_STATE_DISCONNECTED)
            {
                threeway::Thread::InitialiseMutex(m_queueMutex);
            }

        MessagingConnection(MessagingConnectionIdentifier localId, MessagingEntity localEntity, MessagingEntity remoteEntity) :
            m_localId(localId),
            m_localEntity(localEntity),
            m_remoteId(ConnectionIdentifierUnused),
            m_remoteEntity(remoteEntity),
            m_state(MSG_CONN_STATE_DISCONNECTED)
            {
                threeway::Thread::InitialiseMutex(m_queueMutex);
            }

        MessagingConnection(MessagingConnectionIdentifier localId, MessagingConnectionIdentifier remoteId, MessagingEntity localEntity, MessagingEntity remoteEntity) :
            m_localId(localId),
            m_localEntity(localEntity),
            m_remoteId(remoteId),
            m_remoteEntity(remoteEntity),
            m_state(MSG_CONN_STATE_DISCONNECTED)
            {
                threeway::Thread::InitialiseMutex(m_queueMutex);
            }

        virtual ~MessagingConnection();

        bool operator==(const FindLocalId& localId) const { return (m_localId == localId.m_id); }
        bool operator==(const FindRemote& remote) const { return ((m_remoteId == remote.m_id) && (m_remoteEntity == remote.m_remoteEntity)); }

        virtual std::string ToString() const;

        MessagingConnectionIdentifier m_localId;
        MessagingEntity               m_localEntity;
        MessagingConnectionIdentifier m_remoteId;
        MessagingEntity               m_remoteEntity;
        ConnectionState               m_state;
        typedef std::queue< shared_ptr<MessagingConnectionQueuedMessage> > MessagingConnectionQueuedMessageQueue;
        Mutex                                   m_queueMutex;
        MessagingConnectionQueuedMessageQueue   m_queue; // Try saying that quickly...

    };

    Mutex                       m_connectionsMutex;
    vector<MessagingConnection> m_connections;

    /**
     * Utility function to dump connection table to trace file.
     */
    void TraceConnectionTable();


private:
    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    MessagingEntity m_thisEntity;
    SendMessageInterface & m_sendMessageInterface;
    bool m_traceMessages;
};

}

#endif
