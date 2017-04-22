///////////////////////////////////////////////////////////////////////////////
//
// <File name>
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069QueueableEvent.h"
#include "Tr069SocketClient.h"


#include "Tr069HttpPostResponse.h"
#include "Tr069HttpPostRequest.h"
#include "Tr069TcpConnectReq.h"
#include "Tr069TcpConnectInd.h"
#include "Tr069TcpConnectRej.h"
#include "Tr069TcpConnectCnf.h"
#include "Tr069TcpDisconnectReq.h"
#include "Tr069TcpConnectionFailureInd.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{

SocketClient::SocketClient( const IPv4Address & localIpAddress ) :
    ThreadWithQueue("SocketsThread"),
    m_socketFsm(*this, true),
    m_httpConn(localIpAddress)
{
}

SocketClient::~SocketClient()
{
}

u32 SocketClient::ThreadProcedure()
{
    TRACE_PRINTF("Start SocketClient::ThreadProcedure");

    while(!ThreadStopped())
    {
        shared_ptr<Queueable> event = Dequeue( 500 );

        if (event)
        {
            if (Queueable::TIMER_EXPIRY == event->GetDomain())
            {
                TRACE_PRINTF("ReceiveEvent(TIMER_EXPIRY).\n");
                shared_ptr<TimerExpiry> timer = dynamic_pointer_cast<TimerExpiry>(event);

                if (timer)
                {
                     //eventHandlers.HandleTimerExpiry(timer->GetTimerHandle());
                }
            }
            else if (Queueable::MESSAGE_SERIALISED_DATA == event->GetDomain())
            {
                shared_ptr<MessageSerialisedData> message = dynamic_pointer_cast<MessageSerialisedData>(event);
                if (message)
                {
                        TRACE_PRINTF("Received message of type %" PRIu32 " for entity %s (%" PRIu32 ")",
                                            message->GetSerialisationId(),
                                            MessagingEntityToString(message->GetToEntity()),
                                            (u32)message->GetToEntity());
                }
            }
            else if (Queueable::OTHER == event->GetDomain())
            {
                shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(event);

                if (tr069Event)
                {
                    switch(tr069Event->GetId())
                    {

                        case Tr069QueueableEvent::HTTP_POST_REQ:
                        {
                            shared_ptr<HttpPostRequest> httpPostRequest = dynamic_pointer_cast<HttpPostRequest>(event);
                            m_socketFsm.InjectHTTP_POST_REQUEST(httpPostRequest);
                        }
                        break;

                        case Tr069QueueableEvent::TCP_CONNECT_REQ:
                            m_socketFsm.InjectTCP_CONNECT_REQ(event);
                            break;

                        case Tr069QueueableEvent::TCP_CONNECT_IND:
                            m_socketFsm.InjectTCP_CONNECT_IND(event);
                            break;

                        case Tr069QueueableEvent::TCP_DISCONNECT_REQ:
                        {
                            m_socketFsm.InjectTCP_DISCONNECT_REQ(NULL);
                        }
                        break;

                        default:
                            RSYS_ASSERT_PRINTF(false, "Unsupported Event not handled %s", tr069Event->ToString() );
                            break;
                    }
                }
            }
            else
            {
                TRACE_PRINTF("ReceiveEvent(unknown).\n");
            }
        }
    }

    TRACE_PRINTF("Stop SocketClient::ThreadProcedure");

    return 0;
}






}

