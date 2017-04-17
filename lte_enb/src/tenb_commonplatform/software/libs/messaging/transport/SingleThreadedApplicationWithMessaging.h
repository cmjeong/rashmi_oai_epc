///////////////////////////////////////////////////////////////////////////////
//
// SingleThreadedApplicationWithMessaging.h
//
// Class from which to inherit for a single threaded application.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SingleThreadedApplicationWithMessaging_h_
#define __SingleThreadedApplicationWithMessaging_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <unistd.h>

#include <boost/shared_ptr.hpp>

#include <system/Application.h>
#include <system/ThreadWithQueue.h>
#include <system/Serialisable.h>
#include <system/Queueable.h>
#include <system/TimerInterface.h>
#include <system/TimerExpiry.h>
#include <system/AlarmEvent.h>
#include <system/SoftwareWarningInterface.h>
#include <comms/IPv4Address.h>
#include <system/ThreadlessTimerEngine.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Messenger.h"
#include "MessagingEntity.h"
#include "MessageHandler.h"
#include "MessageSerialisedData.h"
#include <messaging/messages/common/MessagingDataInd.h>
#include <system/Selector.h>
#include "CliHandler.h"

using namespace boost;
using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////
typedef shared_ptr<Queueable> QueueablePtr;
typedef queue<QueueablePtr>   QueueOfQueueablePtr;

class ExternalQueue : SelectorCallBackInterface
{
public:
    ExternalQueue( QueueOfQueueablePtr & internalQueue, SelectorRegisterInterface * sri);
    virtual ~ExternalQueue();

    void SelectCallBack();
    void push(shared_ptr<Queueable> queueable);

private:
    static const size_t   readIdx  = 0;
    static const size_t   writeIdx = 1;

    Mutex                 m_mutex;
    QueueOfQueueablePtr   m_queue;
    int                   m_fd[2];
    FILE*                 m_file[2];
    QueueOfQueueablePtr & m_internalQueue;
};

class SingleThreadedApplicationWithMessaging :
    public Application, MessageRxRawInterface,
    public TimerNotifyInterface,
    public SendMessageInterface,
    public SoftwareWarningInterface,
    public IMessageHandler
{
    /**
     * Construct Application with UDP based messenger(s) that communicate
     * with a central post office (application that receives and distributes
     * messages).
     * The post office IP and port are read from the system configuration file.
     * Application must poll for new messages.
     *
     * \param appName      Give the application a name!  Used in log files etc.
     */
protected:
    SingleThreadedApplicationWithMessaging(const char * appName);

public:
    virtual ~SingleThreadedApplicationWithMessaging();

    /**
     * ThreadProcedure to be implemented by concrete app class.
     */
    virtual int AppMain() = 0;

    /**
     * Start up the messaging system.
     */
    void StartMessaging();

    /**
     * Register a CLI handler for a particular entity.
     */
    void RegisterCliHandler(MessagingEntity entity, shared_ptr<CliHandler> handler);

    /**
     * Register an entity with post office so that messages are routed to it correctly.
     *
     * \param entity          Entity to register.
     * \param waitForResponse Wait until RegisterEntityCnf has been received.
     */
    void RegisterEntity(const MessagingEntity& entity);

    /**
     * Register a MessageHandler so that messages are handled correctly.
     *
     * \param handler         Handler to register.
     * \param name            Optional name for trace.
     */
    void RegisterMessageHandler(IMessageHandler * handler, const string & name = "")
    {
        m_messageHandlers.Add(handler, name);
    }

    /**
     * Check to see if an entity is already registered i.e. in our local routing table.
     */
    bool IsRouteAvailable(const MessagingEntity& entity);

    /**
     * Notify a managing entity we are ready to start.
     *
     * \param entity          Managing entity.
     * \param waitForResponse Wait for a start signal if true, else fire and forget.
     */
    void NotifyReady(const MessagingEntity& toEntity, const MessagingEntity& fromEntity);

    /**
     * Get an interface to the single selector we aim to use for all FD events.
     */
    SelectorRegisterInterface & GetSelectorRegisterInterface();

    /**
     * Implement SendMessageInterface.
     *
     * Send a message (any Serialisable object) to some other entity that supports
     * messaging.
     *
     * \param messageToSend     A serialisable object to be serialised and sent.
     * \param destinationEntity Destination messaging entity.
     * \param sourceEntity      The entity this message should be sent "from", used when an app
     *                          registers multiple entities.  Default value means it will be sent
     *                          from the last registered entity.
     * \return                  true on successful send of message, false otherwise.
     */
    virtual bool SendMessage(const Serialisable& messageToSend, MessagingEntity destinationEntity, MessagingEntity sourceEntity = ENTITY_INVALID) const;

    /*
     * Implement SoftwareWarningInterface.
     */
    virtual void SoftwareWarning( const char * warning ) const;

    /**
     * Timer interface - this is very similar to the TimerEngineInterface, but
     * hides the notify interface, as expired timers will be received as a
     * TimerExpiry event via ReceiveEvent(). This is the recommended (and simplest)
     * way to use timers in an application derived from SingleThreadedApplicationWithMessaging.
     */

    // Create a new timer
    TimerHandle CreateTimer(const std::string& timerName, u32 timeoutPeriod,
                            TimerEngineInterface::TimerStart startNow = TimerEngineInterface::TIMER_START_NOW,
                            TimerEngineInterface::TimerMode timerMode = TimerEngineInterface::TIMER_SINGLE_SHOT);

    // Start a timer: if it is already running, it will be stopped and restarted.
    void StartTimer(TimerHandle timerHandle);

    // Stop a currently running timer.  It can be restarted with a call to StartTimer.
    void StopTimer(TimerHandle timerHandle);

    // Delete an existing timer from the system: if it is running, it will be stopped first.
    void DeleteTimer(TimerHandle timerHandle);

    // Query the current status of a registered timer.
    bool IsTimerRunning(TimerHandle timerHandle) const;

    /**
     * Get information about the application as a string for debug/presentation.
     */
    virtual std::string ToString() const;

    /**
     * Implementation of MessageRxRawInterface
     *
     * \param fromEntity        The unique ID for the sending entity.
     * \param toEntity          The unique ID for the receiving entity.
     * \param serialisationId   Uniquely identifies serialised class.
     * \param serialisedData    The serialised class data stream.
     * \param serialisedDataLen Length of above data in bytes.
     */
    void ReceiveMessage(MessagingEntity fromEntity, MessagingEntity toEntity,
                        u32 serialisationId, const u8* serialisedData, u32 serialisedDataLen);

    /**
     * Implementation of TimerNotifyInterface
     *
     * \param expiredTimer      The expired timer handle.
     */
    void NotifyTimerExpiry(TimerHandle expiredTimer);

    /**
     * Register application with the watchdog.
     * This sends the application's PID to the watchdog, which then
     * periodically checks to see whether to the task still exists.  In the
     * case that the task does not exist, the watchdog may then take
     * corrective action, depending on configuration.
     */
    void WatchdogRegisterPid();

    /**
     * De-register application with the watchdog.
     * This sends the application's PID to the watchdog, which then
     * removes it from the set of monitored PIDs.  This reverses the actions
     * taken in response to calling WatchdogRegisterPid().
     */
    void WatchdogRemovePid();

    /**
     * Kick some watchdog context.
     *
     * \param[in] id   The Id of the context to kick.
     * \param[in] soft Timeout in seconds after which warnings are generated
     *                  should the watchdog not have been kicked.
     * \param[in] hard Timeout in seconds after which the context will assume
     *                  to be at fault and corrective action maybe taken.
     */
    void WatchdogKick(u32 id, u16 soft, u16 hard);

    /**
     * Safely stop some watchdog context.
     * This removes a watchdog previously added or maintained by WatchdogKick().
     *
     * \param[in] id   The Id of the context to kick.
     */
    void WatchdogKickStop(u32 id);

    /**
     * Thread safe, but minimal use of mutex
     * for efficient single-threaded use.
     */
    void Enqueue(shared_ptr<Queueable> queueable);

protected:


    /**
     * Process event queues, yield to select for upto the
     * specified timeout, perform any registered callback
     * on set FD(s), process subsequently queued events,
     * then return.
     * Simples.
     */
    void HandleEventCallbacksAndQueues(u32 timeoutMilliSecs);

    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    bool HandleCommonTimerExpiry(shared_ptr<TimerExpiry> timer);
    virtual void HandleTimerExpiry(shared_ptr<TimerExpiry> timer) = 0;
    virtual void HandleOtherEvent(shared_ptr<Queueable> event) {}

    /**
     * This class provides an implementation of Main() that simply starts the worker thread
     * and waits for it to exit. This should be sufficient for most apps...
     */
    virtual int Main(int argc, char * argv[]);

    /**
     * Get the local port number to use for messaging with this application.
     * This is from the system config file, with the parameter name
     * derived from the application name:
     *   Messaging_<app-name>_LocalPort  e.g. Messaging_l1l2_LocalPort
     */
    u16 GetMessagingLocalPort() const;

    // Messenger.  Exchanges messages with some central message processor.
    shared_ptr<Messenger> m_messenger;

    ThreadlessTimerEngine m_timerEngine;

private:
    // Typedefs
    typedef map< MessagingEntity, shared_ptr<CliHandler> > CliHandlers;

    /**
     * Handle messages related to the CLI.
     */
    void HandleCliMessage(shared_ptr<MessageSerialisedData> message);

    /**
     * Handle messages related to KPIs.
     */
    void HandleKpiMessage(shared_ptr<MessageSerialisedData> message);

    // All socket/timer events are triggered by select, managed by this object.
    Selector              m_selector;

    // Messages are offered to each message handler in turn.
    MessageHandlingChain m_messageHandlers;

    // the entity as which this application is registered
    MessagingEntity m_thisEntity;

    // If TRUE, all received messages will be printed to trace output
    bool m_traceMessages;

    // CLI handlers.
    CliHandlers m_registeredCliHandlers;

    /*
     * Queueing mechanism.
     * This is designed to be thread safe when needed,
     * else to simply prevent reentrancy issues when not.
     */
    void ProcessQueue();
    QueueOfQueueablePtr        m_internalQueue;
    shared_ptr<ExternalQueue>  m_externalQueue;
    void Dispatch(shared_ptr<Queueable> queueable);

    /* Our single-thread's PID */
    pid_t m_threadPid;
};

}


#endif
