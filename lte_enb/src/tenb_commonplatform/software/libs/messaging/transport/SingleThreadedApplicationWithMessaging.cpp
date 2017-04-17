///////////////////////////////////////////////////////////////////////////////
//
// SingleThreadedApplicationWithMessaging.cpp
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

#include <system/Trace.h>
#include <system/ThreadlessTimerEngine.h>
#include <system/ConfigurationFile.h>
#include <system/NumberConversions.h>
#include <system/AlarmEvent.h>
#include <system/AlarmEvent.h>
#include <platform/FapAlarmId.h>
#include <messaging/messages/common/RegisterEntityReq.h>
#include <messaging/messages/common/RegisterEntityCnf.h>
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

#include "SingleThreadedApplicationWithMessaging.h"
#include "ThreadlessUdpMessenger.h"
#include "DeviceMessenger.h"

using namespace std;
using namespace boost;


namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

SingleThreadedApplicationWithMessaging::SingleThreadedApplicationWithMessaging(const char * appName) :
    Application(appName),
    m_thisEntity(ENTITY_INVALID),
    m_traceMessages(false),
    m_selector(),
    m_timerEngine(m_selector)
{
    m_threadPid = getpid();

    CliHandler::SetTimerEngineInterface(&m_timerEngine);
}

SingleThreadedApplicationWithMessaging::~SingleThreadedApplicationWithMessaging()
{
}

void SingleThreadedApplicationWithMessaging::HandleEventCallbacksAndQueues(u32 timeoutMilliSecs)
{
    /**
     * Process queue before select
     */
    ProcessQueue();

    /**
     * Yield upon select
     */
    m_selector.DoSelect(timeoutMilliSecs);

    /**
     * Reprocess queue, as select call-back may have enqueued
     */
    ProcessQueue();
}

int SingleThreadedApplicationWithMessaging::Main(int argc, char * argv[])
{
    if(GetCmdLineArgument("--trace-messaging") != NULL)
    {
        m_traceMessages = true;
    }

    // Construct the external queue
    m_externalQueue.reset( new ExternalQueue(m_internalQueue, &m_selector));

    // Start the derived application.
    int result = AppMain();

    // Remove our PID from the watchdog (it may never have been registered but that's safe).
    WatchdogRemovePid();

    return(result);
}

u16 SingleThreadedApplicationWithMessaging::GetMessagingLocalPort() const
{
    // Get local port to use e.g. "Messaging_ps-user-plane_LocalPort"
    string paramName;
    paramName.append("Messaging_");
    paramName.append(GetName());
    paramName.append("_LocalPort");
    u16 localPort = (u16)m_systemConfig.GetU32Parameter(paramName.c_str(), 0);

    return(localPort);
}


void SingleThreadedApplicationWithMessaging::StartMessaging()
{
    // Get the local port number for this application.
    u16 localPort = GetMessagingLocalPort();

    // Get post office IP and port.
    u16 remotePort = (u16)m_systemConfig.GetU32Parameter("Messaging_PostOffice_LocalPort", 0);
    IPv4Address remoteIpAddress(m_systemConfig.GetStringParameter("Messaging_PostOffice_IpAddress", "127.0.0.1"));

    // Create a UdpMessenger operating in callback mode
    TRACE_PRINTF("Starting application messenger with local port %d. Post office port %d.", localPort, remotePort);
    m_messenger.reset( new ThreadlessUdpMessenger(m_selector, localPort, remoteIpAddress, remotePort, this ) );

    m_messenger->StartReceiving();
}

void SingleThreadedApplicationWithMessaging::RegisterCliHandler(MessagingEntity entity, shared_ptr<CliHandler> handler)
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

void SingleThreadedApplicationWithMessaging::RegisterEntity(const MessagingEntity& entity)
{
    // Preconditions.
    RSYS_ASSERT(m_messenger != NULL);

    TRACE("Registering entity", MessagingEntityToString(entity));

    m_thisEntity = entity;

    // Construct the register message.
    RegisterEntityReq registerEntityReq(entity);

    // Send it to post office.
    m_messenger->SendMessage(registerEntityReq, m_thisEntity, ENTITY_POSTOFFICE);
}

bool SingleThreadedApplicationWithMessaging::IsRouteAvailable(const MessagingEntity& entity)
{
    // Preconditions.
    RSYS_ASSERT(m_messenger != NULL);

    return(m_messenger->IsRouteAvailable(entity));
}

void SingleThreadedApplicationWithMessaging::NotifyReady(const MessagingEntity& toEntity, const MessagingEntity& fromEntity)
{
    // Preconditions.
    RSYS_ASSERT(m_messenger != NULL);

    TRACE("Notifying managing entity we're ready", MessagingEntityToString(toEntity));

    // Construct the register message.
    RequestStartInd requestStartInd;

    // Send it to OAM.
    SendMessage(requestStartInd, toEntity, fromEntity);
}

// Implementation of MessageRxRawInterface
void SingleThreadedApplicationWithMessaging::ReceiveMessage(MessagingEntity fromEntity, MessagingEntity toEntity,
                                              u32 serialisationId, const u8* serialisedData, u32 serialisedDataLen)
{
    // Put the message on the queue - we will handle the connection-orientated messages
    // in the worker thread when we dequeue the message.
    shared_ptr<MessageSerialisedData> receivedMessage(
        new MessageSerialisedData(fromEntity, toEntity, serialisationId, serialisedData, serialisedDataLen));

    Enqueue(receivedMessage);
}

void SingleThreadedApplicationWithMessaging::Enqueue(shared_ptr<Queueable> message)
{
    pid_t callingThread = getpid();

    if( m_threadPid ==  callingThread )
    {
        m_internalQueue.push(message);
    }
    else
    {
        m_externalQueue->push(message);
    }
}

void SingleThreadedApplicationWithMessaging::ProcessQueue()
{
    while(m_internalQueue.size())
    {
        shared_ptr<Queueable> message = m_internalQueue.front();
        m_internalQueue.pop();

        Dispatch(message);
    }
}

void SingleThreadedApplicationWithMessaging::Dispatch(shared_ptr<Queueable> queueable)
{
    if(queueable)
    {
        if(Queueable::MESSAGE_SERIALISED_DATA == queueable->GetDomain())
        {
            shared_ptr<MessageSerialisedData> message = dynamic_pointer_cast<MessageSerialisedData>(queueable);
            if(message)
            {
                m_messageHandlers.HandleMessage(message);
            }
        }
        else if(Queueable::TIMER_EXPIRY == queueable->GetDomain())
        {
            shared_ptr<TimerExpiry> timer = dynamic_pointer_cast<TimerExpiry>(queueable);
            if(timer)
            {
                HandleTimerExpiry(timer);
            }
        }
        else
        {
            HandleOtherEvent(queueable);
        }
    }
};


bool SingleThreadedApplicationWithMessaging::MessageHandler(shared_ptr<MessageSerialisedData> & message)
{
    u32 messageId = message->GetSerialisationId();

    // Trace if required
    if(m_traceMessages)
    {
        // Trace messages in proto prof
        MESSAGE_TAG_SHORT(MessagingEntityToString(message->GetFromEntity()),
                          MessagingEntityToString(message->GetToEntity()),
                          "", SerialisationIdToString((SerialisationId)message->GetSerialisationId()),
                          message->GetStatus() == MessageSerialisedData::CONNECTIONLESS ? "RX" : "CO-RX");
        TRACE("Received", message->ToString());
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

bool SingleThreadedApplicationWithMessaging::SendMessage(const Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity) const
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

void SingleThreadedApplicationWithMessaging::SoftwareWarning( const char * warning ) const
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

SelectorRegisterInterface & SingleThreadedApplicationWithMessaging::GetSelectorRegisterInterface()
{
    return m_selector;
}

string SingleThreadedApplicationWithMessaging::ToString() const
{
    ostringstream stream;

    stream << Application::ToString();

    return (stream.str());
}

TimerHandle SingleThreadedApplicationWithMessaging::CreateTimer(const std::string& timerName, u32 timeoutPeriod,
                                                  TimerEngineInterface::TimerStart startNow,
                                                  TimerEngineInterface::TimerMode timerMode)
{
    return m_timerEngine.CreateTimer(timerName, timeoutPeriod, *this, startNow, timerMode);
}

void SingleThreadedApplicationWithMessaging::StartTimer(TimerHandle timerHandle)
{
    m_timerEngine.StartTimer(timerHandle);
}

void SingleThreadedApplicationWithMessaging::StopTimer(TimerHandle timerHandle)
{
    m_timerEngine.StopTimer(timerHandle);
}

void SingleThreadedApplicationWithMessaging::DeleteTimer(TimerHandle timerHandle)
{
    m_timerEngine.DeleteTimer(timerHandle);
}

bool SingleThreadedApplicationWithMessaging::IsTimerRunning(TimerHandle timerHandle) const
{
    return m_timerEngine.IsTimerRunning(timerHandle);
}

void SingleThreadedApplicationWithMessaging::NotifyTimerExpiry(TimerHandle expiredTimer)
{
    // Create a timer expiry object and place it on the internal queue
    TRACE_PRINTF_LEV(TRACE_VERBOSE, "AWM: Queuing expired timer id=%" PRIu32, expiredTimer);
    shared_ptr<TimerExpiry> timerExpiry(new TimerExpiry(expiredTimer));
    Enqueue(timerExpiry);
}

void SingleThreadedApplicationWithMessaging::HandleCliMessage(shared_ptr<MessageSerialisedData> message)
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
                if(cliExecuteCmdReq != NULL)
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


void SingleThreadedApplicationWithMessaging::WatchdogRegisterPid()
{
    WatchdogAddPidReq apr(getpid(), GetName());
    SendMessage(apr, ENTITY_WATCHDOG);
}


void SingleThreadedApplicationWithMessaging::WatchdogRemovePid()
{
    WatchdogRemovePidReq rpr(getpid());
    SendMessage(rpr, ENTITY_WATCHDOG);
}


void SingleThreadedApplicationWithMessaging::WatchdogKick(u32 id, u16 soft, u16 hard)
{
    WatchdogKickReq kr(id, soft, hard);
    SendMessage(kr, ENTITY_WATCHDOG);
}


void SingleThreadedApplicationWithMessaging::WatchdogKickStop(u32 id)
{
    WatchdogKickStopReq kr(id);
    SendMessage(kr, ENTITY_WATCHDOG);
}


ExternalQueue::ExternalQueue( QueueOfQueueablePtr & internalQueue, SelectorRegisterInterface * sri ) :
    m_fd(),
    m_file(),
    m_internalQueue(internalQueue)
{
    Thread::InitialiseMutex(m_mutex);

    TRACE_PRINTF("ExternalQueue()");

    int thePipe = pipe( &m_fd[0] );
    RSYS_ASSERT( thePipe == 0 );

    m_file[writeIdx] = fdopen(m_fd[writeIdx],"w");
    RSYS_ASSERT( m_file[writeIdx] );

    m_file[readIdx] = fdopen(m_fd[readIdx],"r");
    RSYS_ASSERT( m_file[readIdx] );

    sri->RegisterFD(m_fd[readIdx], *this);
}

ExternalQueue::~ExternalQueue()
{
    Thread::DestroyMutex(m_mutex);
    
    fclose(m_file[writeIdx]);
    fclose(m_file[readIdx]);
    close(m_fd[writeIdx]);
    close(m_fd[readIdx]);
}

void ExternalQueue::push(shared_ptr<Queueable> queueable)
{
    {
        Thread::Guard queueGuard(m_mutex);

        m_queue.push(queueable);
    }

    fputs("\n",m_file[writeIdx]);
    fflush(m_file[writeIdx]);
}

void ExternalQueue::SelectCallBack()
{
    fflush(m_file[readIdx]);

    {
        Thread::Guard queueGuard(m_mutex);

        while(m_queue.size())
        {
            shared_ptr<Queueable> message = m_queue.front();
            m_queue.pop();

            m_internalQueue.push(message);
        }
    }
}


}
