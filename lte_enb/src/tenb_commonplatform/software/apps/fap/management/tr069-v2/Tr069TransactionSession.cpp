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

#include <sstream>
#include <fstream>
#include <iostream>
#include <system/Trace.h>
#include <system/Filename.h>
#include <messaging/messages/common/OamActionReq.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069Parser.h"
#include "Tr069Parameters.h"
#include "Tr069ParameterValueChangeNotificationManager.h"

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

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

Tr069TransactionSession::Tr069TransactionSession(MibAccessInterface& mai, CwmpInterface &cwmpInterface) :
        m_paramCache(mai),
        m_cwmpInterface(cwmpInterface),
        m_fsm(*this, true ),
        m_workerThreadGuardTimer(NULL_TIMER),
        m_socketsInterface(NULL),
        m_unauthErrCount(0)
{
}

Tr069TransactionSession::~Tr069TransactionSession()
{
}


void Tr069TransactionSession::HandleEvent( shared_ptr<Queueable> event)
{
   RSYS_ASSERT(event);

   switch(event->GetDomain())
   {
      case Queueable::OTHER:
         {
            shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(event);

            if (tr069Event)
            {
               switch( tr069Event->GetDst() )
               {
                  case Tr069QueueableEvent::TRANSACTION_SESSION_FSM:
                     {
                        switch(tr069Event->GetId())
                        {
                           case Tr069QueueableEvent::TRANSPORT_CNF:
                              {
                                 shared_ptr<TransportCnf> transportCnf = dynamic_pointer_cast<TransportCnf>(tr069Event);
                                 m_fsm.InjectTransportCnf( transportCnf );
                              }
                              break;

                           case Tr069QueueableEvent::START_TRANSACTION_SESSION:
                              {
                                 m_fsm.InjectStartTransactionSession( NULL );
                              }
                              break;

                           case Tr069QueueableEvent::HTTP_POST_RES:
                              {
                                 shared_ptr<HttpPostResponse> httpResponse = dynamic_pointer_cast<HttpPostResponse>(tr069Event);
                                 m_fsm.InjectHttpResponse( httpResponse );
                              }
                              break;

                           case Tr069QueueableEvent::TCP_CONNECTION_FAILURE_IND:
                              {
                                 shared_ptr<TcpConnectionFailureInd> connFailureInd = dynamic_pointer_cast<TcpConnectionFailureInd>(tr069Event);
                                 m_fsm.InjectTcpConnectionFailure( connFailureInd );
                              }
                              break;

                           case Tr069QueueableEvent::TCP_CONNECT_REJ:
                              {
                                 shared_ptr<TcpConnectRej> connectRej = dynamic_pointer_cast<TcpConnectRej>(tr069Event);
                                 m_fsm.InjectTcpConnectRej( connectRej );
                              }
                              break;

                           case Tr069QueueableEvent::Tr069QueueableEvent::TCP_CONNECT_CNF:
                              {
                                 shared_ptr<TcpConnectCnf> connectCnf = dynamic_pointer_cast<TcpConnectCnf>(tr069Event);
                                 m_fsm.InjectTcpConnectCnf( connectCnf );
                              }
                              break;

                           case Tr069QueueableEvent::TCP_DISCONNECT_CNF:
                              {
                                 shared_ptr<TcpDisconnectCnf> disconnectCnf = dynamic_pointer_cast<TcpDisconnectCnf>(tr069Event);
                                 m_fsm.InjectTcpDisconnectCnf( disconnectCnf );
                              }
                              break;

                           default:
                              RSYS_ASSERT_PRINTF(false,"Unhandled TRANSACTION_SESSION_FSM event %s.", tr069Event->ToString());
                              break;
                        }
                     }
                     break;

                  case Tr069QueueableEvent::SOCKET_INTERFACE_FSM:
                     {
                        if(m_socketsInterface)
                        {
                           m_socketsInterface->HandleEvent(event);
                        }
                     }
                     break;

                  default:
                     RSYS_ASSERT_PRINTF(false,"Unhandled event %s.", tr069Event->ToString());
                     break;
               }
            }
         }
         break;

      default:
         RSYS_ASSERT_PRINTF(false, "Unsupported Event domain not handled" );
         break;
   }
}

bool Tr069TransactionSession::HandleTimerExpiry(threeway::TimerHandle expiredTimer)
{
    bool timerHandled = false;

    if(expiredTimer)
    {
        if( expiredTimer == m_workerThreadGuardTimer )
        {
            m_fsm.InjectWorkerThreadStalledTimerExpiry( NULL );
            timerHandled = true;
        }
    }

    return timerHandled;
}

void Tr069TransactionSession::EnqueueSoapEnvelope( shared_ptr<string> soapEnvelope )
{
    TRACE_PRINTF("Added to the end of the HTTP Post queue");

    httpPostQueue.push_back(soapEnvelope);
}

void Tr069TransactionSession::ProcessHttpPostResponseHeader(shared_ptr<HttpPostResponse> httpResponse)
{
    if( httpResponse &&
        httpResponse->parsed &&
        httpResponse->parsed->header )
    {
        shared_ptr<Tr069ParseHeader> header = httpResponse->parsed->header;

        if( header->holdRequests == "true")
        {
            m_holdRequests = true;
        }
        else if( header->holdRequests == "false")
        {
            m_holdRequests = false;
        }
    }
}

void Tr069TransactionSession::SendEmptyHttpPostBecauseServerHasHeldRequests()
{
    shared_ptr<HttpPostRequest> emptyPost(new HttpPostRequest( "" ) );
    m_socketsInterface->HandleEvent(emptyPost);
}

void Tr069TransactionSession::SendTerminatingEmptyHttpPostBecauseAllProceduresComplete()
{
	RSYS_ASSERT(m_fgwSentEmptyHttpPostBecauseProceduresFinished);

    m_fapSentEmptyHttpPostBecauseProceduresFinished = true;

    shared_ptr<HttpPostRequest> emptyPost(new HttpPostRequest( "", false ) );
    m_socketsInterface->HandleEvent(emptyPost);
}

void Tr069TransactionSession::SendEmptyHttpPostBecauseFapProceduresComplete()
{
    m_fapSentEmptyHttpPostBecauseProceduresFinished = true;

    shared_ptr<HttpPostRequest> emptyPost(new HttpPostRequest( "" ) );
    m_socketsInterface->HandleEvent(emptyPost);
}

void Tr069TransactionSession::SendHttpPost()
{
    shared_ptr<string> deQueuedPost = httpPostQueue.front();
    httpPostQueue.pop_front();

    TRACE_PRINTF("Popped the first from the HTTP Post queue");

    shared_ptr<HttpPostRequest> postReq(new HttpPostRequest( deQueuedPost->c_str()) );
    m_socketsInterface->HandleEvent(postReq);
}

void Tr069TransactionSession::ClearHoldRequests()
{
    m_holdRequests = false;
}

void Tr069TransactionSession::HandleServerResponse(shared_ptr<HttpPostResponse> httpResponse)
{
    ProcessHttpPostResponseHeader(httpResponse);
    TRACE_PRINTF("Tr069TransactionSession::HandleServerResponse");

    m_cwmpInterface.HandleServerResponse(httpResponse);
}

void Tr069TransactionSession::HandleServerCommand(shared_ptr<HttpPostResponse> httpResponse)
{
    ProcessHttpPostResponseHeader(httpResponse);

    m_cwmpInterface.HandleServerCommand(httpResponse);
}

void Tr069TransactionSession::HandleServerFault(shared_ptr<HttpPostResponse> httpResponse)
{
    ENTER();

    ProcessHttpPostResponseHeader(httpResponse);
   if(httpResponse->parsed && httpResponse->parsed->body && httpResponse->parsed->body->fault)
   {
      TRACE_PRINTF("Unrecognised fault code = %s",
         httpResponse->parsed->body->fault->detail->faultDetail->faultcode.c_str());
    m_cwmpInterface.HandleServerFault(httpResponse, m_transactionSessionResult);
   }
   //If no fault TCp will automatically tear down
    EXIT();
}

void Tr069TransactionSession::MarkTransactionSessionFailed(shared_ptr<TcpConnectionFailureInd>)
{
    m_transactionSessionResult = TransactionSessionComplete::CONNECTION_FAILURE;
}

void Tr069TransactionSession::SendRebootRequest(void*)
{
    Tr069Application::GetInstance().RebootFapViaOam();
}

void Tr069TransactionSession::SendTransactionSessionFailure()
{
   TRACE_PRINTF("SndTransactionsession failure to clear digestValues");

   shared_ptr<TransactionSessionComplete> transactionSessionComplete(new TransactionSessionComplete( m_transactionSessionResult ));
   Tr069Application::GetInstance().Enqueue(transactionSessionComplete);
}

void Tr069TransactionSession::SendTransactionSessionSuccess()
{
   TRACE_PRINTF("SndTransactionsession success to clear digestValues");

   shared_ptr<TransactionSessionComplete> transactionSessionComplete(new TransactionSessionComplete( TransactionSessionComplete::TRANSACTION_SESSION_SUCCESS ));
   Tr069Application::GetInstance().Enqueue(transactionSessionComplete);
}

// Entry & Exit
void Tr069TransactionSession::TransactionSessionInProgressEntry()
{
    RSYS_ASSERT(m_socketsInterface == NULL);

    IPv4Address localIpAddr;
    m_paramCache.GetMibAttribute( PARAM_ID_ENB_IP_ADDR_IPV4, localIpAddr );

    m_socketsInterface = new SocketsInterface( localIpAddr );
    m_serverConnectCount = 0;
    //httpPostQueue.clear();

    m_holdRequests = false;
    m_transactionSessionResult = TransactionSessionComplete::TRANSACTION_SESSION_SUCCESS;
    m_fapSentEmptyHttpPostBecauseProceduresFinished = false;
    m_fgwSentEmptyHttpPostBecauseProceduresFinished = false;
}

void Tr069TransactionSession::TransactionSessionInProgressExit()
{
    //httpPostQueue.clear();

    delete m_socketsInterface;
    m_socketsInterface = NULL;
}

void Tr069TransactionSession::WaitHttpResponseEntry()
{
    RSYS_ASSERT(m_workerThreadGuardTimer == NULL_TIMER);

    m_workerThreadGuardTimer = Tr069Application::GetInstance().CreateTimer("WorkerThreadStalledTimer", TimerEngineInterface::MinutesToTicks(10) );
}

void Tr069TransactionSession::WaitHttpResponseExit()
{
    Tr069Application::GetInstance().DeleteTimer( m_workerThreadGuardTimer );

    m_workerThreadGuardTimer = NULL_TIMER;
}

void Tr069TransactionSession::EstablishTcpConnectionEntry()
{
   threeway::Url serverUrl;

   if(Tr069Application::GetInstance().useUrlInUse)
   {
      m_paramCache.GetMibAttribute( PARAM_ID_MANAGEMENT_SERVER_IN_USE, serverUrl);

      if(!strcmp(serverUrl.ToString().c_str(), "0.0.0.0"))
      {
         u32 factoryReset;

         Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_LTE_FACTORY_RESET_ON_TR069_CONN_FAIL, factoryReset);
         if(factoryReset)
         {
            Tr069Application &app = Tr069Application::GetInstance();
            OamActionReq oamActionReq(OAM_ACTION_FACTORY_RESET);
            app.SendMessage(oamActionReq, ENTITY_OAM, ENTITY_TR069);
         }
      }
   }
   else
   {
      m_paramCache.GetMibAttribute( PARAM_ID_MANAGEMENT_SERVER, serverUrl);
   }

   if( serverUrl.GetPort() == 0 )
   {
      string vendor("RADISYS");
      if( Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING),PARAM_ID_GATEWAY_VENDOR) )
      {
         Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), PARAM_ID_GATEWAY_VENDOR, vendor );
      }
      if( 0 == vendor.compare("RADISYS") )
      {
         serverUrl.SetPort(80);
      }
      else
      {
         serverUrl.SetPort(7547);
      }
   }

   if( serverUrl.GetScheme().empty() )
   {
      serverUrl.SetScheme("http:");
   }

   shared_ptr<TcpConnectReq> connectReq(new TcpConnectReq( serverUrl) );
   m_socketsInterface->HandleEvent(connectReq);
}

void Tr069TransactionSession::TearDownTcpConnectionEntry()
{
   TRACE_PRINTF("just before call to clear digestValues");

   Tr069Application::GetInstance().ClearDigestValues();
   shared_ptr<TcpDisconnectReq> disconnectReq(new TcpDisconnectReq() );
   m_socketsInterface->HandleEvent(disconnectReq);
}

void Tr069TransactionSession::ServerSentEmptyPostEntry()
{
    m_fgwSentEmptyHttpPostBecauseProceduresFinished = true;

    MibAttributeValues attrs;
    attrs.AddAttribute(PARAM_ID_TR069_SPV_IN_PROGRESS, 0);
    m_paramCache.SetMibAttributes(attrs, ENTITY_TR069);
}

// Guard conditions
bool Tr069TransactionSession::QueryHoldRequests()
{
    return m_holdRequests;
}

bool Tr069TransactionSession::QueryFapProceduresCompleted()
{
    return (m_fapSentEmptyHttpPostBecauseProceduresFinished);
}

bool Tr069TransactionSession::QueryServerProceduresCompleted()
{
    return (m_fgwSentEmptyHttpPostBecauseProceduresFinished);
}

bool Tr069TransactionSession::QueryAllProceduresCompleted(shared_ptr<TcpConnectionFailureInd>)
{
    return (m_fapSentEmptyHttpPostBecauseProceduresFinished && m_fgwSentEmptyHttpPostBecauseProceduresFinished);
}

bool Tr069TransactionSession::QueryEnqueuedHttpPost()
{
    return !httpPostQueue.empty();
}

bool Tr069TransactionSession::QueryFault(shared_ptr<HttpPostResponse> httpResponse)
{
   int errorCode;

   if(httpResponse)
   {
      errorCode = httpResponse->getResponseErrCode();
      if(errorCode == 401)
      {
         TRACE_PRINTF("Tr069TransactionSession::QueryFault, receoved 401, valid code");
         // Response Code 401 is a valid response code for Digest authentication hence do not consider it as fault.
         return false;
      }
      else if(errorCode >= 400)
      {  
         TRACE_PRINTF("Http Response errorCode[%d]", errorCode);
         return 1;
      }
   }
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->fault;
}

bool Tr069TransactionSession::QueryEmptyHttpPost(shared_ptr<HttpPostResponse> httpResponse)
{
    return (httpResponse && (0 == strcmp(httpResponse->ToString(), "<empty/>")));
}

bool Tr069TransactionSession::QueryTransactionSessionFailed()
{
    return (m_transactionSessionResult != TransactionSessionComplete::TRANSACTION_SESSION_SUCCESS);
}


}

