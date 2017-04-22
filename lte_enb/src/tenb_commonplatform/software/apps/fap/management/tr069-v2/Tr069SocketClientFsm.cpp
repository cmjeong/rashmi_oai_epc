///////////////////////////////////////////////////////////////////////////////
//
// Tr069FgwFsm.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <system/Trace.h>
#include <libcsoap/soap-server.h>
#include <nanohttp/nanohttp-client.h>
#include <pthread.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069SocketClient.h"
#include "Tr069QueueableEvent.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////




//****************************************************************************
//
// FSM STATES
//
//****************************************************************************

//****************************************************************************
// BaseState
//****************************************************************************



SocketClientFsmActionHandleTcpConnectReq::Outcome SocketClient::HandleTcpConnectReq( shared_ptr<Queueable> event)
{
    ENTER();

    shared_ptr<TcpConnectReq> tcpConnectReq = dynamic_pointer_cast<TcpConnectReq>(event);

    SocketClientFsmActionHandleTcpConnectReq::Outcome result = SocketClientFsmActionHandleTcpConnectReq::FSM_ACTION_SUCCESS;

    bool connectedOk = m_httpConn.Connect( tcpConnectReq->GetConnectionUrl());

    if(connectedOk)
    {
        m_httpConn.SendTcpConnectCnf();
        result = SocketClientFsmActionHandleTcpConnectReq::FSM_ACTION_SUCCESS;
    }
    else
    {
        m_httpConn.SendTcpConnectionFailureInd();
        result = SocketClientFsmActionHandleTcpConnectReq::FSM_ACTION_CONNECTION_FAILURE;
    }

    RETURN(result);
}

void SocketClient::HandleTcpConnectInd( shared_ptr<Queueable> event)
{
    ENTER();

    Tr069Application& app = Tr069Application::GetInstance();

    shared_ptr<TcpConnectInd> tcpConnectInd = dynamic_pointer_cast<TcpConnectInd>(event);

    shared_ptr<ConnectionRequest> connectionRequest(new ConnectionRequest());
    shared_ptr<TransactionSessionCommand> transactionSessionCommand(new TransactionSessionCommand( connectionRequest ));
    app.Enqueue(transactionSessionCommand);

    EXIT();
}

void SocketClient::HandleTcpDisconnectReq( void* )
{
    ENTER();

    m_httpConn.Disconnect();

    TRACE_PRINTF("Send (TcpDisconnectCnf)");

    shared_ptr<TcpDisconnectCnf> tcpDisconnectCnf(new TcpDisconnectCnf() );
    Tr069Application::GetInstance().Enqueue(tcpDisconnectCnf);

    EXIT();
}

void SocketClient::SendHttpPostButDoNotWaitForResponse(shared_ptr<HttpPostRequest> httpPostRequest)
{
    m_httpConn.Post( httpPostRequest->GetPost(), NULL );
}



//****************************************************************************
// ConnectedState
//****************************************************************************
SocketClientFsmActionSendHttpPost::Outcome SocketClient::SendHttpPost( shared_ptr<HttpPostRequest> httpPostRequest )
{
    ENTER();

    SocketClientFsmActionSendHttpPost::Outcome result = SocketClientFsmActionSendHttpPost::FSM_ACTION_SUCCESS;

    Tr069Application& app = Tr069Application::GetInstance();


    hresponse_t * response = NULL;

    if(m_httpConn.Post( httpPostRequest->GetPost(), &response  ) )
    {
        shared_ptr<HttpPostResponse> httpPostResponse( new HttpPostResponse( response ) );

        app.Enqueue(httpPostResponse);

        result = SocketClientFsmActionSendHttpPost::FSM_ACTION_SUCCESS;
    }
    else
    {
        m_httpConn.SendTcpConnectionFailureInd( );

        result = SocketClientFsmActionSendHttpPost::FSM_ACTION_CONNECTION_FAILURE;
    }

    if(response)
    {
        hresponse_free(response);
    }

    RETURN(result);
}

void SocketClient::RejectTcpConnectReq( shared_ptr<Queueable> event )
{
    ENTER();

    shared_ptr<TcpConnectReq> tcpConnectReq = dynamic_pointer_cast<TcpConnectReq>(event);

    Tr069Application& app = Tr069Application::GetInstance();

    shared_ptr<TcpConnectRej> tcpConnectRej( new TcpConnectRej() );

    app.timerDelayedProcedures.Enqueue(tcpConnectRej, TimerEngineInterface::SecondsToTicks(1) );

    EXIT();
}

bool SocketClient::QueryAfterPostWaitForResponse(shared_ptr<HttpPostRequest> httpPostRequest)
{
    return httpPostRequest->WaitForResponse();
}



