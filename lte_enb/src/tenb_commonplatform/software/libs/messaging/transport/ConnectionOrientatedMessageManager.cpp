///////////////////////////////////////////////////////////////////////////////
//
// ConnectionOrientatedMessageManager.cpp
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
#include <messaging/messages/common/MessagingConnectionReq.h>
#include <messaging/messages/common/MessagingConnectionConf.h>
#include <messaging/messages/common/MessagingConnectionRef.h>
#include <messaging/messages/common/MessagingReleaseReq.h>
#include <messaging/messages/common/MessagingReleaseConf.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "ConnectionOrientatedMessageManager.h"

#define AWM_CONNECTION_INFO


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
// Class Functions
///////////////////////////////////////////////////////////////////////////////
ConnectionOrientatedMessageManager::ConnectionOrientatedMessageManager( MessagingEntity entity, SendMessageInterface & sendMessageInterface) :
        m_thisEntity(entity),
        m_sendMessageInterface(sendMessageInterface),
        m_nextConnectionIdentifier(0),
        m_traceMessages(true)
{
    Thread::InitialiseMutex(m_connectionsMutex);
}

ConnectionOrientatedMessageManager::~ConnectionOrientatedMessageManager()
{
    Thread::DestroyMutex(m_connectionsMutex);
}


bool ConnectionOrientatedMessageManager::SendInitialCoMessage(Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingConnectionIdentifier& newConnectionId, MessagingEntity sourceEntity)
{
    ENTER();

    // assign a new local connection id
    newConnectionId = m_nextConnectionIdentifier++;

    if (m_nextConnectionIdentifier == ConnectionIdentifierUnused)
    {
        m_nextConnectionIdentifier = 0;
    }

    if (ENTITY_INVALID == sourceEntity)
    {
        sourceEntity = m_thisEntity;
    }

    // Trace if required
    if(m_traceMessages)
    {
        // Trace messages in proto prof
        MESSAGE_TAG_SHORT(MessagingEntityToString(sourceEntity),
                          MessagingEntityToString(destinationEntity),
                          "", SerialisationIdToString((SerialisationId)messageToSend.GetSerialisationId()), "CO-TX");
        TRACE_PRINTF("MSGCON: SendingInitialCoMsg [id=%" PRIu32 "]: %s", newConnectionId, messageToSend.ToString().c_str());
    }

    // pack the payload message into a connection request
    MessagingConnectionReq msgConnReq(newConnectionId, messageToSend);

    // Guard scope
    {
        Thread::Guard connectionsGuard(m_connectionsMutex);

        // store the new connection details before sending the conn req to avoid a race with the returning conf
        m_connections.push_back(MessagingConnection(newConnectionId, sourceEntity, destinationEntity));
        m_connections.back().m_state = MessagingConnection::MSG_CONN_STATE_AWAITING_CONN_CONF;

#ifdef AWM_CONNECTION_INFO
        TraceConnectionTable();
#endif
    }

    // Send it off using our messenger which has already been set up
    // to send the message to the app running the post office.

    if(!m_sendMessageInterface.SendMessage(msgConnReq, destinationEntity, sourceEntity))
    {
        // clear out the failed connection
        Thread::Guard connectionsGuard(m_connectionsMutex);
        m_connections.pop_back();
        RETURN(false);
    }
    RETURN(true);
}

bool ConnectionOrientatedMessageManager::SendCoMessage(Serialisable& messageToSend, MessagingConnectionIdentifier connectionId)
{
    ENTER();

    Thread::Guard connectionsGuard(m_connectionsMutex);
    vector<MessagingConnection>::iterator itConn =
        std::find(m_connections.begin(), m_connections.end(), FindLocalId(connectionId));
    if (itConn != m_connections.end())
    {
        if (itConn->m_state == MessagingConnection::MSG_CONN_STATE_CONNECTED)
        {
            if(m_traceMessages)
            {
                // Trace messages in proto prof
                MESSAGE_TAG_SHORT(MessagingEntityToString(itConn->m_localEntity),
                                  MessagingEntityToString(itConn->m_remoteEntity),
                                  "", SerialisationIdToString((SerialisationId)messageToSend.GetSerialisationId()), "CO-TX");
                TRACE_PRINTF("MSGCON: SendingCo [loc=%" PRIu32 ",rem=%" PRIu32 "]: %s", itConn->m_localId, itConn->m_remoteId, messageToSend.ToString().c_str());
            }

            // pack the payload message into data ind with the connection ids
            MessagingDataInd msgDataInd(itConn->m_localId, itConn->m_remoteId, messageToSend);

            RETURN(m_sendMessageInterface.SendMessage(msgDataInd, itConn->m_remoteEntity, itConn->m_localEntity));
        }
        else if (itConn->m_state == MessagingConnection::MSG_CONN_STATE_AWAITING_CONN_CONF)
        {
            TRACE_MSG_LEV(TRACE_WARNING, "MSGCON: Queuing CO message whilst we wait for connection confirm");

            // Waiting for connection confirm from the far end - queue the message.
            // We don't know the remote id yet, will fill it in later.
            Thread::Guard queueGuard(itConn->m_queueMutex);
            shared_ptr<MessagingDataInd> msgDataInd(new MessagingDataInd(itConn->m_localId, ConnectionIdentifierUnused, messageToSend));
            // As we are queuing the message, call clone to copy the messageToSend
            if (msgDataInd->Clone())
            {
                shared_ptr<MessagingConnectionQueuedMessage> msgForQ(new MessagingConnectionQueuedMessage(itConn->m_localEntity, itConn->m_remoteEntity, msgDataInd));
                itConn->m_queue.push(msgForQ);
            }
            else
            {
                TRACE_MSG_LEV(TRACE_WARNING, "MSGCON: Failed to clone MessagingDataInd for queuing");
            }
        }
        else
        {
            // Can't send - wrong state
            TRACE_MSG_LEV(TRACE_WARNING, "MSGCON: Can't send CO message - wrong state!");
            TRACE_MSG(messageToSend.ToString().c_str());
        }
    }
    else
    {
        TRACE_MSG_LEV(TRACE_WARNING, "MSGCON: Can't send CO message - no connection found.");
        TRACE_MSG(messageToSend.ToString().c_str());
    }

    RETURN(false);
}

void ConnectionOrientatedMessageManager::ReleaseConnection(MessagingConnectionIdentifier connectionId)
{
    ENTER();

    Thread::Guard connectionsGuard(m_connectionsMutex);

    vector<MessagingConnection>::iterator itConn =
        std::find(m_connections.begin(), m_connections.end(), FindLocalId(connectionId));
    if (itConn != m_connections.end())
    {
        if ((itConn->m_state == MessagingConnection::MSG_CONN_STATE_CONNECTED) ||
            (itConn->m_state == MessagingConnection::MSG_CONN_STATE_AWAITING_CONN_CONF))
        {
            // pack the payload message into a connection request
            MessagingReleaseReq msgReleaseReq(itConn->m_localId, itConn->m_remoteId);

            if (!m_sendMessageInterface.SendMessage(msgReleaseReq, itConn->m_remoteEntity, itConn->m_localEntity))
            {
                // failed to send, release local end instead
                TRACE_PRINTF("MSGCON: Failed to send ReleaseReq for connection id=%" PRIu32 ", remEntity=%s. Forced local clear.", connectionId, MessagingEntityToString(itConn->m_remoteEntity));
                m_connections.erase(itConn);
            }
            else
            {
                TRACE_PRINTF("MSGCON: Sent ReleaseReq for connection id=%" PRIu32 " to remEntity=%s", connectionId, MessagingEntityToString(itConn->m_remoteEntity));
            }
        }
        else
        {
            // failed to send, release local end instead
            TRACE_PRINTF("MSGCON: Bad state. Failed to send ReleaseReq for connection id=%" PRIu32 ", remEntity=%s. Forced local clear.", connectionId, MessagingEntityToString(itConn->m_remoteEntity));
            m_connections.erase(itConn);
        }
    }
    else
    {
        TRACE_PRINTF("MSGCON: Failed to release connection id=%" PRIu32, connectionId);
    }

#ifdef AWM_CONNECTION_INFO
    TraceConnectionTable();
#endif

    EXIT();
}

bool ConnectionOrientatedMessageManager::MessageHandler(shared_ptr<MessageSerialisedData> & coMessage)
{
    ENTER();

    u32 messageId = coMessage->GetSerialisationId();

    // Is this one of our Connection Orientated messages?
    if ( (SERIALISATION_ID_COM_BASE > messageId) ||
         (SERIALISATION_ID_COM_END_OF_COM_MESSAGES < messageId) )
    {
        return false;
    }

    bool embeddedMessage = false;
    bool coMessageValid  = false;

    TRACE_PRINTF("MSGCON: HandleReceivedCoMessage %s embeddedMessage %d", coMessage->ToString().c_str(), embeddedMessage);

    switch (coMessage->GetSerialisationId())
    {
        case SERIALISATION_ID_COM_CONNECTION_REQ:
        {
            shared_ptr<MessagingConnectionReq> connReq = Serialisable::DeSerialise<MessagingConnectionReq>(coMessage);
            if (connReq)
            {
                if (HandleReceivedConnectionRequest(coMessage, connReq->GetSourceConnectionId()))
                {
                    if (connReq->GetPayloadData() != NULL)
                    {
                        // Extract the embedded message
                        coMessage.reset(
                                new MessageSerialisedData(
                                        coMessage->GetFromEntity(), coMessage->GetToEntity(),
                                        coMessage->GetLocalConnectionId(),
                                        coMessage->GetRemoteConnectionId(),
                                        connReq->GetPayloadSerialisationId(),
                                        connReq->GetPayloadData(),
                                        connReq->GetPayloadDataLength()));
                        embeddedMessage = true;
                    }
                    coMessageValid = true;
                }
            }
            break;
        }

        case SERIALISATION_ID_COM_CONNECTION_CONF:
        {
            shared_ptr<MessagingConnectionConf> connConf = Serialisable::DeSerialise<MessagingConnectionConf>(coMessage);
            if (connConf)
            {
                coMessageValid = HandleReceivedConnectionConfirm(coMessage, connConf->GetSourceConnectionId(), connConf->GetDestConnectionId());
            }
            break;
        }

        case SERIALISATION_ID_COM_CONNECTION_REF:
        {
            shared_ptr<MessagingConnectionRef> connRef = Serialisable::DeSerialise<MessagingConnectionRef>(coMessage);
            if (connRef)
            {
                coMessageValid = HandleReceivedConnectionRefused(coMessage, connRef->GetDestConnectionId());
            }
            break;
        }

        case SERIALISATION_ID_COM_DATA_IND:
        {
            shared_ptr<MessagingDataInd> dataInd = Serialisable::DeSerialise<MessagingDataInd>(coMessage);
            if (dataInd)
            {
                // Extract the embedded message
                coMessage.reset(
                        new MessageSerialisedData(
                                coMessage->GetFromEntity(), coMessage->GetToEntity(),
                                dataInd->GetDestConnectionId(),
                                dataInd->GetSourceConnectionId(),
                                dataInd->GetPayloadSerialisationId(),
                                dataInd->GetPayloadData(),
                                dataInd->GetPayloadDataLength()));
                embeddedMessage = true;
                coMessageValid  = true;
            }
            break;
        }

        case SERIALISATION_ID_COM_RELEASE_REQ:
        {
            shared_ptr<MessagingReleaseReq> relReq = Serialisable::DeSerialise<MessagingReleaseReq>(coMessage);
            if (relReq)
            {
                coMessageValid = HandleReceivedReleaseRequest(coMessage, relReq->GetSourceConnectionId(), relReq->GetDestConnectionId());
            }
            break;
        }

        case SERIALISATION_ID_COM_RELEASE_CONF:
        {
            shared_ptr<MessagingReleaseConf> relCnf = Serialisable::DeSerialise<MessagingReleaseConf>(coMessage);
            if (relCnf)
            {
                coMessageValid = HandleReceivedReleaseConfirm(coMessage, relCnf->GetSourceConnectionId(), relCnf->GetDestConnectionId());
            }
            break;
        }

        default:
            TRACE("MSGCON: HandleReceivedCoMessage: unknown message type ", coMessage->GetSerialisationId());
            break;
    }

    if (!coMessageValid)
    {
        coMessage->SetStatus(MessageSerialisedData::INVALID);
        TRACE_MSG("MSGCON: Failed to handle connection orientated message");
    }

    bool handledAlwaysFalseToAllowOtherMessageHandlersToFurtherProcessCoMessages = false;

    RETURN(handledAlwaysFalseToAllowOtherMessageHandlersToFurtherProcessCoMessages);
}

bool ConnectionOrientatedMessageManager::HandleReceivedConnectionRequest(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier sourceConnectionId)
{
    ENTER();

    TRACE("MSGCON: HandleReceivedConnectionRequest from ", sourceConnectionId);

    if ((sourceConnectionId != ConnectionIdentifierUnused) && coMessage)
    {
        MessagingEntity localEntity  = coMessage->GetToEntity();
        MessagingEntity remoteEntity = coMessage->GetFromEntity();

        Thread::Guard connectionsGuard(m_connectionsMutex);

        vector<MessagingConnection>::iterator itConn =
            std::find(m_connections.begin(), m_connections.end(), FindRemote(sourceConnectionId, coMessage->GetFromEntity()));
        if (itConn == m_connections.end())
        {
            // haven't got this source connection in our list so that's normal,
            // we'll create a new connection

            // assign a new local connection id
            MessagingConnectionIdentifier newConnectionId = m_nextConnectionIdentifier++;
            if (m_nextConnectionIdentifier == ConnectionIdentifierUnused)
            {
                m_nextConnectionIdentifier = 0;
            }

            m_connections.push_back(MessagingConnection(
                                        newConnectionId,              // Local
                                        sourceConnectionId,           // Remote
                                        localEntity,     // Local
                                        remoteEntity)); // Remote
            m_connections.back().m_state = MessagingConnection::MSG_CONN_STATE_CONNECTED;

            // reply with a Conf to the sender
            MessagingConnectionConf msgConnectConf(newConnectionId, sourceConnectionId);
            if (!m_sendMessageInterface.SendMessage(msgConnectConf, remoteEntity, localEntity ))
            {
                // oh globbits...discard the connection
                TRACE("MSGCON: HandleReceivedConnectionRequest: failed, can't send Conf to  ", sourceConnectionId);
                m_connections.pop_back();
                RETURN(false);
            }

            TRACE_PRINTF("MSGCON: new connection accepted (loc=%" PRIu32 ", rem=%" PRIu32 ")", newConnectionId, sourceConnectionId);
            coMessage->SetConnectionOrientated(MessageSerialisedData::NEW_CONNECTION,
                                               newConnectionId,     // local
                                               sourceConnectionId); // remote

#ifdef AWM_CONNECTION_INFO
            TraceConnectionTable();
#endif
            RETURN(true);
        }
        else
        {
            // that's not right...we already have this remote connection id,
            // we'll refuse this new one
            TRACE("MSGCON: HandleReceivedConnectionRequest : refusing already known source ID ", sourceConnectionId);
            MessagingConnectionRef msgConnectRef(itConn->m_remoteId);
            m_sendMessageInterface.SendMessage(msgConnectRef, remoteEntity, localEntity);
        }
    }

    RETURN(false);
}

bool ConnectionOrientatedMessageManager::HandleReceivedConnectionConfirm(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier sourceConnectionId, MessagingConnectionIdentifier destConnectionId)
{
    ENTER();

    bool handled = true;

    if ((sourceConnectionId != ConnectionIdentifierUnused) && coMessage)
    {
        Thread::Guard connectionsGuard(m_connectionsMutex);

        vector<MessagingConnection>::iterator itConn =
            std::find(m_connections.begin(), m_connections.end(), FindLocalId(destConnectionId));
        if (itConn != m_connections.end())
        {
            if (itConn->m_state == MessagingConnection::MSG_CONN_STATE_AWAITING_CONN_CONF)
            {
                TRACE_PRINTF("MSGCON: Received a Connection Confirm from %s for connection (src=%" PRIu32 ", dst=%" PRIu32 ") state=%d",
                        MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId, (int)itConn->m_state);
                itConn->m_remoteId = sourceConnectionId;
                itConn->m_state = MessagingConnection::MSG_CONN_STATE_CONNECTED;

                // Now we can send any queued messages, filling in the remote id
                Thread::Guard queueGuard(itConn->m_queueMutex);
                shared_ptr<MessagingConnectionQueuedMessage> dequeued;
                while (!itConn->m_queue.empty())
                {
                    dequeued = itConn->m_queue.front();
                    if (dequeued)
                    {
                        shared_ptr<MessagingDataInd> msgDataInd = dequeued->m_messagingDataInd;
                        if (msgDataInd)
                        {
                            msgDataInd->SetDestConnectionId(sourceConnectionId);
                            TRACE_PRINTF("MSGCON: Sending queued message to %s", MessagingEntityToString(itConn->m_remoteEntity));
                            m_sendMessageInterface.SendMessage(*msgDataInd, itConn->m_remoteEntity, itConn->m_localEntity);
                        }
                    }
                    itConn->m_queue.pop();
                }

                // nothing to pass up to the user application
                coMessage.reset();

#ifdef AWM_CONNECTION_INFO
                TraceConnectionTable();
#endif
            }
            else
            {
                TRACE_PRINTF("MSGCON: Received a unexpected Connection Confirm from %s for an connection (src=%" PRIu32 ", dst=%" PRIu32 ") state=%d, discarding.",
                        MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId, (int)itConn->m_state);
                handled = false;
            }
        }
        else
        {
            // haven't got this local connection in our list so that's not right
            TRACE_PRINTF("MSGCON: Received a Connection Confirm from %s for an unknown connection (src=%" PRIu32 ", dst=%" PRIu32 "), discarding.",
                    MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId);
            handled = false;
        }
    }

    RETURN(handled);
}

bool ConnectionOrientatedMessageManager::HandleReceivedReleaseRequest(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier sourceConnectionId, MessagingConnectionIdentifier destConnectionId)
{
    ENTER();

    bool handled = true;

    TRACE("MSGCON: HandleReceivedReleaseRequest from ", sourceConnectionId);

    if ((sourceConnectionId != ConnectionIdentifierUnused) && coMessage)
    {
        MessagingEntity localEntity  = coMessage->GetToEntity();
        MessagingEntity remoteEntity = coMessage->GetFromEntity();

        Thread::Guard connectionsGuard(m_connectionsMutex);

        // Regardless of whether or not we have a connection handler, still respond with a Release Confirm to make
        // sure the far side of this link clears down correctly - it might not waiting for the Release Confirm, but
        // you never know...
        MessagingReleaseConf msgReleaseConf(destConnectionId, sourceConnectionId);
        if (!m_sendMessageInterface.SendMessage(msgReleaseConf, remoteEntity, localEntity))
        {
            // oh globbits...discard the connection anyway
            TRACE("MSGCON: HandleReceivedReleaseRequest: failed, can't send Conf to  ", sourceConnectionId);
        }

        vector<MessagingConnection>::iterator itConn =
            std::find(m_connections.begin(), m_connections.end(), FindRemote(sourceConnectionId, coMessage->GetFromEntity()));
        if (itConn != m_connections.end())
        {
            if (itConn->m_localId == destConnectionId)
            {
                TRACE_PRINTF("MSGCON: Received a Release Request from %s for connection (src=%" PRIu32 ", dst=%" PRIu32 ") state=%d",
                        MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId, (int)itConn->m_state);

                m_connections.erase(itConn);
                coMessage->SetConnectionOrientated(MessageSerialisedData::CONNECTION_DELETED,
                                                   destConnectionId,    // local
                                                   sourceConnectionId); // remote
#ifdef AWM_CONNECTION_INFO
                TraceConnectionTable();
#endif
            }
            else
            {
                TRACE_PRINTF("MSGCON: Received a Release Request from %s for an mismatched connection (src=%" PRIu32 ", dst=%" PRIu32 ", lcl=%" PRIu32 "), discarding.",
                        MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId, itConn->m_localId);
                handled = false;
            }
        }
        else
        {
            TRACE_PRINTF("MSGCON: Received a Release Request from %s for an unknown connection (src=%" PRIu32 ", dst=%" PRIu32 "), discarding.",
                    MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId);
            handled = false;
        }
    }
    else
    {
        if (coMessage)
        {
            TRACE_PRINTF("MSGCON: Received a Release Request from %s for an invalid connection (src=unknown, dst=%" PRIu32 "), discarding.",
                    MessagingEntityToString(coMessage->GetFromEntity()), destConnectionId);
        }
        handled = false;
    }

    RETURN(handled);
}

bool ConnectionOrientatedMessageManager::HandleReceivedReleaseConfirm(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier sourceConnectionId, MessagingConnectionIdentifier destConnectionId)
{
    ENTER();

    bool handled = true;

    TRACE("MSGCON: HandleReceivedReleaseConfirm from ", sourceConnectionId);

    if ((sourceConnectionId != ConnectionIdentifierUnused) && coMessage)
    {
        Thread::Guard connectionsGuard(m_connectionsMutex);

        vector<MessagingConnection>::iterator itConn =
            std::find(m_connections.begin(), m_connections.end(), FindRemote(sourceConnectionId, coMessage->GetFromEntity()));
        if (itConn != m_connections.end())
        {
            if (itConn->m_localId == destConnectionId)
            {
                TRACE_PRINTF("MSGCON: Received a Release Confirm from %s for connection (src=%" PRIu32 ", dst=%" PRIu32 ") state=%d",
                        MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId, (int)itConn->m_state);
                m_connections.erase(itConn);
                coMessage->SetConnectionOrientated(MessageSerialisedData::CONNECTION_DELETED,
                                                   destConnectionId,    // local
                                                   sourceConnectionId); // remote
#ifdef AWM_CONNECTION_INFO
                TraceConnectionTable();
#endif
            }
            else
            {
                TRACE_PRINTF("MSGCON: Received a Release Confirm from %s for an mismatched connection (src=%" PRIu32 ", dst=%" PRIu32 ", lcl=%" PRIu32 "), discarding.",
                        MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId, itConn->m_localId);
                handled = false;
            }
        }
        else
        {
            TRACE_PRINTF("MSGCON: Received a Release Confirm from %s for an unknown connection (src=%" PRIu32 ", dst=%" PRIu32 "), discarding.",
                    MessagingEntityToString(coMessage->GetFromEntity()), sourceConnectionId, destConnectionId);
            handled = false;
        }
    }
    else
    {
        if (coMessage)
        {
            TRACE_PRINTF("MSGCON: Received a Release Confirm from %s for an invalid connection (src=unknown, dst=%" PRIu32 "), discarding.",
                    MessagingEntityToString(coMessage->GetFromEntity()), destConnectionId);
        }
        handled = false;
    }

    RETURN(handled);
}

bool ConnectionOrientatedMessageManager::HandleReceivedConnectionRefused(shared_ptr<MessageSerialisedData> coMessage, MessagingConnectionIdentifier destConnectionId)
{
    ENTER();

    bool handled = true;

    if ((destConnectionId != ConnectionIdentifierUnused) && coMessage)
    {
        Thread::Guard connectionsGuard(m_connectionsMutex);

        vector<MessagingConnection>::iterator itConn =
            std::find(m_connections.begin(), m_connections.end(), FindLocalId(destConnectionId));
        if (itConn != m_connections.end())
        {
            if (itConn->m_state == MessagingConnection::MSG_CONN_STATE_AWAITING_CONN_CONF)
            {
                TRACE_PRINTF("MSGCON: Received a Connection Refused from %s for connection (dst=%" PRIu32 ") state=%d",
                        MessagingEntityToString(coMessage->GetFromEntity()), destConnectionId, (int)itConn->m_state);
                // drop the connection and...
                m_connections.erase(itConn);
                coMessage->SetConnectionOrientated(MessageSerialisedData::CONNECTION_DELETED,
                                                   destConnectionId,            // local
                                                   ConnectionIdentifierUnused); // remote

#ifdef AWM_CONNECTION_INFO
                TraceConnectionTable();
#endif
            }
            else
            {
                TRACE_PRINTF("MSGCON: Received a unexpected Connection Refused from %s for an connection (dst=%" PRIu32 ") state=%d, discarding.",
                        MessagingEntityToString(coMessage->GetFromEntity()), destConnectionId, (int)itConn->m_state);
                handled = false;
            }
        }
        else
        {
            // haven't got this local connection in our list so that's not right
            TRACE_PRINTF("MSGCON: Received a Connection Refused from %s for an unknown connection (dst=%" PRIu32 "), discarding.",
                    MessagingEntityToString(coMessage->GetFromEntity()), destConnectionId);
            handled = false;
        }
    }

    RETURN(handled);
}
void ConnectionOrientatedMessageManager::TraceConnectionTable()
{
    ENTER();

    if (!m_connections.empty())
    {
        TRACE_PRINTF("MSGCON: Connection table:");

        vector<MessagingConnection>::iterator itConn;
        for (itConn=m_connections.begin(); itConn != m_connections.end(); itConn++)
        {
            TRACE_PRINTF("MSGCON: %s", itConn->ToString().c_str());
        }
    }
    else
    {
        TRACE_PRINTF("MSGCON: Connection table empty.");
    }

    EXIT();
}

ConnectionOrientatedMessageManager::MessagingConnection::~MessagingConnection()
{
    ENTER();

    // Clear any queued messages
    Thread::Guard queueGuard(m_queueMutex);
    while (!m_queue.empty())
    {
        m_queue.pop();
    }

    EXIT();
}


// Utility function do return connection table in string for any cli commands
// that require it.
std::string ConnectionOrientatedMessageManager::MessagingConnection::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "LocId[" << MessagingEntityToString(m_localEntity) << ":" << m_localId << "] ";
    stream << "RemId[" << MessagingEntityToString(m_remoteEntity) << ":" << m_remoteId << "] ";
    switch (m_state)
    {
        case MSG_CONN_STATE_DISCONNECTED:
            stream << "Disconnected, ";
            break;

        case MSG_CONN_STATE_AWAITING_CONN_CONF:
            stream << "Awaiting Connection Conf, ";
            break;

        case MSG_CONN_STATE_CONNECTED:
            stream << "Connected, ";
            break;

        case MSG_CONN_STATE_AWAITING_REL_CONF:
            stream << "Awaiting Release Conf, ";
            break;

        default:
            stream << "Unknown, ";
            break;
    }
    stream << "Queued[" << m_queue.size() << "]";

    RETURN(stream.str());
}


std::string ConnectionOrientatedMessageManager::ConnectionTableToString(const char *entityName) const
{
    ENTER();

    ostringstream textString;

    textString << std::endl;

    if (!m_connections.empty())
    {
        textString << "-----------------------------------------------------" << std::endl;
        textString << "     " << entityName << "internal connection table" << std::endl;;
        textString << "-----------------------------------------------------" << std::endl;

        vector<MessagingConnection>::const_iterator itConn;
        for (itConn=m_connections.begin(); itConn != m_connections.end(); itConn++)
        {
            textString << itConn->ToString().c_str() << std::endl;;
        }
        textString << "-----------------------------------------------------" << std::endl;
    }
    else
    {
        textString << entityName << " internal connection table is empty." << std::endl;
    }

    RETURN(textString.str());
}

bool ConnectionOrientatedMessageManager::IsConnectionValid(MessagingConnectionIdentifier connectionId)
{
    Thread::Guard connectionsGuard(m_connectionsMutex);
    vector<MessagingConnection>::iterator itConn =
        std::find(m_connections.begin(), m_connections.end(), FindLocalId(connectionId));
    if (itConn != m_connections.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

}
