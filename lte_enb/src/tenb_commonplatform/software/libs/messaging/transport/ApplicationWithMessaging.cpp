///////////////////////////////////////////////////////////////////////////////
//
// ApplicationWithMessaging.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <system/Trace.h>
#include <system/TimerEngine.h>
#include <system/ConfigurationFile.h>
#include <system/NumberConversions.h>
#include <system/AlarmEvent.h>
#include <system/AlarmEvent.h>
#include <platform/FapAlarmId.h>
#include <messaging/messages/common/RegisterEntityReq.h>
#include <messaging/messages/common/RegisterEntityCnf.h>
#include <messaging/messages/common/MessagingDataInd.h>
#include <messaging/messages/common/RequestStartInd.h>
#include <messaging/messages/common/RequestStartRsp.h>
#include <messaging/messages/common/SetTraceMasksReq.h>
#include <messaging/messages/cli/CliExecuteCmdReq.h>
#include <messaging/messages/cli/CliExecuteCmdCnf.h>
#include <messaging/messages/cli/CliExecuteCmdInd.h>
#include <messaging/messages/watchdog/WatchdogAddPidReq.h>
#include <messaging/messages/watchdog/WatchdogRemovePidReq.h>
#include <messaging/messages/watchdog/WatchdogKickReq.h>
#include <messaging/messages/watchdog/WatchdogKickStopReq.h>
#include <messaging/transport/MessageSerialisedData.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ApplicationWithMessaging.h"
#include "UdpMessenger.h"
#include "DeviceMessenger.h"

using namespace std;
using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

ApplicationWithMessaging::ApplicationWithMessaging(const char * appName) :
    Application(appName),
    m_thisEntity(ENTITY_INVALID),
    m_traceMessages(false),
    m_messagingStarted(false)
{
}

ApplicationWithMessaging::~ApplicationWithMessaging()
{
}

int ApplicationWithMessaging::Main(int argc, char * argv[])
{
    if(GetCmdLineArgument("--trace-messaging") != NULL)
    {
        m_traceMessages = true;
    }

    // Start the derived application.
    // TODO - rename this, it's left over from when AWM derived from Thread.
    int result = ThreadProcedure();

    // Remove our PID from the watchdog (it may never have been registered but that's safe).
    WatchdogRemovePid();

    return(result);
}

u16 ApplicationWithMessaging::GetMessagingLocalPort() const
{
    // Get local port to use e.g. "Messaging_ps-user-plane_LocalPort"
    string paramName;
    paramName.append("Messaging_");
    paramName.append(GetName());
    paramName.append("_LocalPort");
    u16 localPort = (u16)m_systemConfig.GetU32Parameter(paramName.c_str(), 0);

    return(localPort);
}

void ApplicationWithMessaging::StartMessaging()
{
    const u16   localPort      = GetMessagingLocalPort();
    const u16   postOfficePort = PORT_POSTOFFICE;
    IPv4Address postOfficeAddr;

    struct sockaddr_in sa;

    const char * addr = GetCmdLineArgument("--po-addr");

    if (    (addr)
         && (0 < inet_pton(AF_INET, addr, &sa.sin_addr))
       )
    {
        postOfficeAddr.Set(addr);
    }
    else
    {
        postOfficeAddr.Set(m_systemConfig.GetStringParameter("Messaging_PostOffice_IpAddress", "127.0.0.1"));
    }

    // Create a UdpMessenger operating in callback mode
    TRACE_PRINTF("Starting application messenger on port %d, post-office at %s:%d", localPort, postOfficeAddr.ToString(), postOfficePort);
    m_messenger.reset( new UdpMessenger(localPort, postOfficeAddr, postOfficePort, this) );

    m_messenger->StartReceiving();
    m_messagingStarted = true;
}

void ApplicationWithMessaging::RegisterCliHandler(MessagingEntity entity, shared_ptr<CliHandler> handler)
{
    RSYS_ASSERT (handler);

    CliHandlers::const_iterator iter = m_registeredCliHandlers.find(entity);

    if(iter != m_registeredCliHandlers.end())
    {
        TRACE_LEV(TRACE_WARNING, "CLI handler for entity already exists", MessagingEntityToString(entity));
    }

    TRACE("Adding CLI handler for entity", MessagingEntityToString(entity));
    m_registeredCliHandlers[entity] = handler;
}

void ApplicationWithMessaging::RegisterEntity(const MessagingEntity& entity, bool waitForResponse)
{
    // Preconditions.
    RSYS_ASSERT(m_messenger != NULL);

    // TODO - need to do this with a little state machine that can still allow other messages to be
    // received.

    TRACE("Registering entity", MessagingEntityToString(entity));

    m_thisEntity = entity;

    if(waitForResponse)
    {
        // Ensure messenger is operating in polled mode
        m_messenger->SwitchToPolledMode();

        while(waitForResponse)
        {
            // Construct the register message.
            RegisterEntityReq registerEntityReq(entity);

            // Send it to post office.
            m_messenger->SendMessage(registerEntityReq, m_thisEntity, ENTITY_POSTOFFICE);

            // Wait until post office responds....
            TRACE("  Waiting for confirm", MessagingEntityToString(entity));

            // Wait a short while for a response.
            MessagingEntity fromEntity;
            MessagingEntity toEntity;
            shared_ptr<SerialisedData> receivedMessage = m_messenger->BlockingReceiveMessage(5000, fromEntity, toEntity);

            // May or may not have received a message so check pointer.
            if(receivedMessage != NULL)
            {
                switch(receivedMessage->GetSerialisationId())
                {
                    case SERIALISATION_ID_REGISTER_ENTITY_CNF:
                        {
                            shared_ptr<RegisterEntityCnf> registerEntityCnf =
                                Serialisable::DeSerialise<RegisterEntityCnf>(receivedMessage);

                            RSYS_ASSERT(registerEntityCnf != NULL);

                            if(registerEntityCnf->GetEntity() == entity)
                            {
                                // We have our response...
                                waitForResponse = false;
                                TRACE("  Entity registration confirm received", MessagingEntityToString(entity));
                            }
                            else
                            {
                                // TODO - could this be an assert instead?
                                TRACE_LEV(TRACE_WARNING, "Entity registration confirm received for (wrong) entity", MessagingEntityToString(entity));
                            }
                        }
                        break;

                    default:
                        break;
                }
            }
        }

        // Return to callback mode
        m_messenger->RestoreCallbackMode();
    }
    else
    {
        // Just fire and forget...

        // Construct the register message.
        RegisterEntityReq registerEntityReq(entity);

        // Send it to post office.
        m_messenger->SendMessage(registerEntityReq, m_thisEntity, ENTITY_POSTOFFICE);
    }
}

bool ApplicationWithMessaging::IsRouteAvailable(const MessagingEntity& entity)
{
    // Preconditions.
    RSYS_ASSERT(m_messenger != NULL);

    return(m_messenger->IsRouteAvailable(entity));
}

void ApplicationWithMessaging::NotifyReady(const MessagingEntity& toEntity, const MessagingEntity& fromEntity, bool waitForResponse)
{
    // TODO - might need to do this with a little state machine that can still allow other messages to be received.

    TRACE("Notifying managing entity we're ready", MessagingEntityToString(toEntity));

    if(m_messenger == NULL)
    {
        TRACE_MSG_LEV(TRACE_WARNING, "No messenger for notifying");
        return;
    }

    // Construct the register message.
    RequestStartInd requestStartInd;

    if(waitForResponse)
    {
        // Ensure messenger is operating in polled mode
        m_messenger->SwitchToPolledMode();

        // Send it to OAM.
        SendMessage(requestStartInd, toEntity, fromEntity);

        // Wait until oam responds....
        // oam will send REGISTER_ENTITY_CNF once it has sent any MIB params that are required.
        TRACE("  Waiting for response", MessagingEntityToString(toEntity));

        while(waitForResponse)
        {
            // Wait a short while for a response.
            MessagingEntity responseFromEntity;
            MessagingEntity responseToEntity;
            shared_ptr<SerialisedData> receivedMessage = m_messenger->BlockingReceiveMessage(5000, responseFromEntity, responseToEntity);

            // May or may not have received a message so check pointer.
            if(receivedMessage != NULL)
            {
                switch(receivedMessage->GetSerialisationId())
                {
                    case SERIALISATION_ID_REQUEST_START_RSP:
                        {
                            waitForResponse = false;
                            TRACE("  Start received!", MessagingEntityToString(responseToEntity));

                            Trace::GetInstance().SetSoftwareWarningInterface(this);
                        }
                        break;

                    default:
                        TRACE("NotifyReady: Received unhandled message while waiting for SERIALISATION_ID_REQUEST_START_RSP", receivedMessage->ToString().c_str());
                        break;
                }
            }
            else
            {
                TRACE("  Timed out waiting, sending requestStartInd again", MessagingEntityToString(toEntity));

                // Send it to OAM.
                SendMessage(requestStartInd, toEntity, fromEntity);
            }
        }

        // Return to callback mode
        m_messenger->RestoreCallbackMode();
    }
    else
    {
        // Just fire and forget...
        TRACE("  Fire and forget", MessagingEntityToString(toEntity));

        // Send it to OAM.
        SendMessage(requestStartInd, toEntity, fromEntity);
    }
}

// Implementation of MessageRxRawInterface
void ApplicationWithMessaging::ReceiveMessage(MessagingEntity fromEntity, MessagingEntity toEntity,
                                              u32 serialisationId, const u8* serialisedData, u32 serialisedDataLen)
{
    // Put the message on the queue - we will handle the connection-orientated messages
    // in the worker thread when we dequeue the message.
    shared_ptr<MessageSerialisedData> receivedMessage(
        new MessageSerialisedData(fromEntity, toEntity, serialisationId, serialisedData, serialisedDataLen));

    // Add the message to the thread queue
    m_eventQueue.Enqueue(receivedMessage);
}

shared_ptr<Queueable> ApplicationWithMessaging::ReceiveEvent(u32 timeoutMilliSecs)
{
    // Poll for a queued event
    shared_ptr<Queueable> event = m_eventQueue.Dequeue(timeoutMilliSecs);

    return(event);
}

void ApplicationWithMessaging::DispatchEvent(shared_ptr<Queueable> event)
{
    if(event == NULL)
    {
        // Can be null as ReceiveEvent can take a timeout and will return a null pointer on timeout.
        return;
    }

    if(Queueable::MESSAGE_SERIALISED_DATA == event->GetDomain())
    {
        shared_ptr<MessageSerialisedData> message = dynamic_pointer_cast<MessageSerialisedData>(event);
        if(message)
        {
            m_messageHandlers.HandleMessage(message);
        }
    }
    else if(Queueable::TIMER_EXPIRY == event->GetDomain())
    {
        shared_ptr<TimerExpiry> timer = dynamic_pointer_cast<TimerExpiry>(event);
        if(timer)
        {
            HandleTimerExpiry(timer);
        }
    }
    else
    {
        HandleOtherEvent(event);
    }
}

bool ApplicationWithMessaging::MessageHandler(shared_ptr<MessageSerialisedData> & message)
{
    TRACE_PRINTF_LEV( TRACE_VERBOSE, "ApplicationWithMessaging::MessageHandler");

    u32 messageId = message->GetSerialisationId();

    // Trace if required
    if(m_traceMessages)
    {
        // Trace messages in proto prof
        MESSAGE_TAG_SHORT(MessagingEntityToString(message->GetFromEntity()),
                          MessagingEntityToString(message->GetToEntity()),
                          "", SerialisationIdToString((SerialisationId)message->GetSerialisationId()),
                          message->GetStatus() == MessageSerialisedData::CONNECTIONLESS ? "RX" : "CO-RX");
        TRACE("AWM Received", message->ToString());
    }

    if(messageId == SERIALISATION_ID_CLI_EXECUTE_CMD_REQ)
    {
        HandleCliMessage(message);

        // We're done and are going to swallow these messages.
        // Derived classes don't need to know about them.
        return(true);
    }

    if( (messageId == SERIALISATION_ID_SET_TRACE_MASKS_REQ))
    {
        shared_ptr<SetTraceMasksReq> setTraceMasksReq = Serialisable::DeSerialise<SetTraceMasksReq>(message);
        RSYS_ASSERT(setTraceMasksReq != NULL);

        TRACE_PRINTF("Received SetTraceMasksReq: %s", setTraceMasksReq->ToString().c_str());
        Trace::GetInstance().SetTraceLevelsMask(setTraceMasksReq->GetTraceCriticalityMask());
        Trace::GetInstance().SetTraceCategoriesMask(setTraceMasksReq->GetTraceCategoriesMask());

        // We're done and are going to swallow these messages.
        // Derived classes don't need to know about them.
        return(true);
    }

    return(false);
}

bool ApplicationWithMessaging::SendMessage(const Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity) const
{
    // Preconditions.
    RSYS_ASSERT_PRINTF(m_messenger != NULL, "Message=%s Src=%s Dest=%s", messageToSend.ToString().c_str(), MessagingEntityToString(sourceEntity), MessagingEntityToString(destinationEntity));

    // Trace if required
    if(m_traceMessages)
    {
        // Trace messages in proto prof
        MESSAGE_TAG_SHORT(MessagingEntityToString(sourceEntity),
                          MessagingEntityToString(destinationEntity),
                          "", SerialisationIdToString((SerialisationId)messageToSend.GetSerialisationId()), "TX");
        TRACE("Sending", messageToSend.ToString());
    }

    if (ENTITY_INVALID == sourceEntity)
    {
        sourceEntity = m_thisEntity;
    }

    // Send it off using our messenger which has already been set up
    // to send the message to the app running the post office.
    return(m_messenger->SendMessage(messageToSend, sourceEntity, destinationEntity));
}

void ApplicationWithMessaging::SoftwareWarning( const char * warning ) const
{
    shared_ptr<AlarmId> alarmId(new FapAlarmId( FapAlarmId::SOFTWARE_WARNING));
    AlarmEvent alarmEvent(
            alarmId,
            AlarmEvent::ALARM_EVENT_TRANSIENT,
            AlarmEvent::ALARM_SEVERITY_WARNING,
            warning,
            AlarmEvent::ALARM_TYPE_PROCESSING);

    SendMessage(alarmEvent, ENTITY_OAM, m_thisEntity);
}


string ApplicationWithMessaging::ToString() const
{
    ostringstream stream;

    stream << Application::ToString();

    return (stream.str());
}

void ApplicationWithMessaging::StartTimerEngine()
{
    TimerEngineThread::GetInstance().StartTimerEngine();

    CliHandler::SetTimerEngineInterface(&TimerEngine::GetInstance());
}

void ApplicationWithMessaging::StopTimerEngine()
{
    // TODO: Do nothing... we used to stop TimerEngineThread but timers are
    // now handled as part of main (ReceiveEvent) thread.


    TimerEngineThread::GetInstance().StopTimerEngine();
}

TimerHandle ApplicationWithMessaging::CreateTimer(const std::string& timerName, u32 timeoutPeriod,
                                                  TimerEngineInterface::TimerStart startNow,
                                                  TimerEngineInterface::TimerMode timerMode)
{
    return TimerEngine::GetInstance().CreateTimer(timerName, timeoutPeriod, *this, startNow, timerMode);
}

void ApplicationWithMessaging::StartTimer(TimerHandle timerHandle)
{
    TimerEngine::GetInstance().StartTimer(timerHandle);
}

void ApplicationWithMessaging::StopTimer(TimerHandle timerHandle)
{
    TimerEngine::GetInstance().StopTimer(timerHandle);
}

void ApplicationWithMessaging::DeleteTimer(TimerHandle timerHandle)
{
    TimerEngine::GetInstance().DeleteTimer(timerHandle);
}

bool ApplicationWithMessaging::IsTimerRunning(TimerHandle timerHandle) const
{
    return TimerEngine::GetInstance().IsTimerRunning(timerHandle);
}

void ApplicationWithMessaging::NotifyTimerExpiry(TimerHandle expiredTimer)
{
    // Create a timer expiry object and place it on the priority queue
    TRACE_PRINTF_LEV(TRACE_VERBOSE, "AWM: Queuing expired timer id=%" PRIu32, expiredTimer);
    shared_ptr<TimerExpiry> timerExpiry(new TimerExpiry(expiredTimer));
    m_eventQueue.PriorityEnqueue(timerExpiry);
}

void ApplicationWithMessaging::HandleCliMessage(shared_ptr<MessageSerialisedData> message)
{
    u32 messageId = message->GetSerialisationId() ;

    // Look for a CLI handler
    MessagingEntity cliTargetEntity = message->GetToEntity();
    CliHandlers::const_iterator iter = m_registeredCliHandlers.find(cliTargetEntity);
    if(iter != m_registeredCliHandlers.end())
    {

        if(iter->second != NULL)
        {
            // We have a CLI handler!
            if (messageId == SERIALISATION_ID_CLI_EXECUTE_CMD_REQ)
            {
                // Try to execute a CLI command...
                shared_ptr<CliExecuteCmdReq> cliExecuteCmdReq = Serialisable::DeSerialise<CliExecuteCmdReq>(message);
                if(cliExecuteCmdReq)
                {
                    // Run the command and send the output back.
                    shared_ptr<CliResponse> response = iter->second->ExecuteCliCmd(cliExecuteCmdReq->GetCliCmd(), cliExecuteCmdReq->GetCliCmdArgs());
                    if (response != NULL)
                    {
                   		TRACE_PRINTF("CLI command handler returned %" PRId32 " '%s'", response->GetStatus(), response->GetResponseText().c_str());

                   		char* txPtr = (char *)response->GetResponseText().c_str() ;
                   		while (strlen(txPtr) > MAX_CLI_RESPONSE_PACKET_LENGTH)
                   		{
                   			shared_ptr<CliExecuteCmdInd> cliExecuteCmdInd (new CliExecuteCmdInd (txPtr, MAX_CLI_RESPONSE_PACKET_LENGTH)) ;
                   			SendMessage(*cliExecuteCmdInd, message->GetFromEntity());
                   			txPtr += MAX_CLI_RESPONSE_PACKET_LENGTH ;
                   		}
                   		shared_ptr <CliExecuteCmdCnf> cliExecuteCmdCnf( new CliExecuteCmdCnf (iter->second->GetNamespace().c_str(), cliExecuteCmdReq->GetCliCmd().c_str(), txPtr, response->GetStatus()));
                   		SendMessage(*cliExecuteCmdCnf, message->GetFromEntity());
                   	}
                    else
                    {
                       	TRACE_PRINTF("CLI command handler returned NULL response.");
                    }
                }
            }
        }
        else
        {
            TRACE_MSG_LEV(TRACE_WARNING, "No registered CLI handler available for entity");
        }
    }
}

void ApplicationWithMessaging::WatchdogRegisterPid()
{
    WatchdogAddPidReq apr(getpid(), GetName());
    SendMessage(apr, ENTITY_WATCHDOG);
}


void ApplicationWithMessaging::WatchdogRemovePid()
{
    WatchdogRemovePidReq rpr(getpid());
    SendMessage(rpr, ENTITY_WATCHDOG);
}


void ApplicationWithMessaging::WatchdogKick(u32 id, u16 soft, u16 hard)
{
    WatchdogKickReq kr(id, soft, hard);
    SendMessage(kr, ENTITY_WATCHDOG);
}


void ApplicationWithMessaging::WatchdogKickStop(u32 id)
{
    WatchdogKickStopReq kr(id);
    SendMessage(kr, ENTITY_WATCHDOG);
}


}
