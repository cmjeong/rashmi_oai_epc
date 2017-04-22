///////////////////////////////////////////////////////////////////////////////
//
// Cwmp.cpp
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
#include <system/StringUtils.h>
#include <messaging/messages/common/RemScanReq.h>
#include <messaging/messages/common/OamActionReq.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace threeway;

#include "Tr069Application.h"
#include "Tr069DataModelManager.h"
#include "Tr069ActiveAlarmEventListRadisysXmlGenerator.h"
#include "Tr069AlarmManager.h"
#include "UpdateConstants.h"
#include "Tr069Cwmp.h"
#include "Tr069RpcSetParameterValue.h"
#include "Tr069RpcSetParameterAttribute.h"
#include "Tr069RpcAddObject.h"
#include "Tr069AddObjectManager.h"
#include "Tr069RpcDeleteObject.h"
#include "Tr069DeleteObjectManager.h"
#include "Tr069SetParameterValueManager.h"
#include "Tr069TransactionSession.h"
#include "Tr069ParameterValueChangeNotificationManager.h"
#include "messages/Tr069Reconnect.h"
#include "messages/Tr069AutoTransfer.h"
#include "SoapEnvelope.h"
#include "CwmpInform.h"
#include "xml/Tr069AutoTransferCompResponse.h"
#include <mobnet/RemScanStatusId.h>

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
Tr069Cwmp::Tr069Cwmp( Tr069FsmInterface & secGwFsm, bool reconnectSecGw, bool bootEventSent ) :
        m_secGwFsm(secGwFsm),
        m_stateGuardTimer(NULL_TIMER),
        m_periodicInformTimer(NULL_TIMER),
        m_connectionReattemptTimer(NULL_TIMER),
        m_fsm(*this, true, "Cwmp"),
        m_bootEventSent(bootEventSent),
        m_reconnectSecGw(reconnectSecGw),
        m_successiveConnectionFailures(0),
        m_cwmpUsesTunnel(true)
{
}

Tr069Cwmp::Tr069Cwmp( Tr069FsmInterface & secGwFsm, bool reconnectSecGw, bool bootEventSent, bool cwmpUsesTunnel ) :
        m_secGwFsm(secGwFsm),
        m_stateGuardTimer(NULL_TIMER),
        m_periodicInformTimer(NULL_TIMER),
        m_connectionReattemptTimer(NULL_TIMER),
        m_successiveConnectionFailures(0),
        m_fsm(*this, true, "Cwmp"),
        m_bootEventSent(bootEventSent),
        m_reconnectSecGw(reconnectSecGw),
        m_cwmpUsesTunnel(cwmpUsesTunnel)
{
}

Tr069Cwmp::~Tr069Cwmp()
{
}

void Tr069Cwmp::StartInitialTransactionSession( void *)
{
    TRACE_PRINTF("Inject \"0 BOOTSTRAP\" to self.");

    shared_ptr<Event0Bootstrap> event0Bootstrap(new Event0Bootstrap() );
    shared_ptr<TransactionSessionCommand> transSessCmd(new TransactionSessionCommand( event0Bootstrap ));
    Tr069ServerConnection::GetInstance().HandleEvent(transSessCmd);
}

void Tr069Cwmp::StartInitialTransactionSession(shared_ptr<TransactionSessionCommand> )
{
   StartInitialTransactionSession(NULL);
}

void Tr069Cwmp::StartDelayTimerForInitialTransactionSession( void *)
{
   if(m_stateGuardTimer != NULL_TIMER)
   {
      Tr069Application::GetInstance().DeleteTimer( m_stateGuardTimer );

      m_stateGuardTimer = NULL_TIMER;
   }

   m_stateGuardTimer = Tr069Application::GetInstance().CreateTimer("'0 BOOTSTRAP' in five if no '4 VALUE CHANGE' occurs", TimerEngineInterface::SecondsToTicks(5) );
}


void Tr069Cwmp::RecordTransactionSession(shared_ptr<TransactionSessionCommand> tsc)
{
   RSYS_ASSERT(!m_transactionSessionInProgressEvent);

   m_transactionSessionInProgressEvent = tsc->GetEvent();
}

void Tr069Cwmp::RecordTransactionSessionResult(shared_ptr<TransactionSessionComplete> tsc)
{
   RSYS_ASSERT(!m_transactionSessionInProgressEvent);

   m_transactionSessionResult = tsc->QueryResult();
   TRACE_PRINTF("Recorded session result (%d)", m_transactionSessionResult);
}

void Tr069Cwmp::SendSecGwModifyReq(shared_ptr<TransactionSessionComplete>)
{
   shared_ptr<SecGwModifyReq> secGwModifyReq( new SecGwModifyReq( SecGwModifyReq::Next) );
   Tr069Application::GetInstance().Enqueue(secGwModifyReq);
}

void Tr069Cwmp::SendLocked(shared_ptr<Shutdown>)
{
   shared_ptr<LockedInd> lockedInd( new LockedInd( Tr069QueueableEvent::SECGW_CONNECTION_FSM) );
   /**
    * Indirectly inject to SecGw FSM, as can lead to deletion of this FSM!
    */
   Tr069Application::GetInstance().Enqueue(lockedInd);
}

void Tr069Cwmp::SendLocked(shared_ptr<TransactionSessionComplete>)
{
   shared_ptr<LockedInd> lockedInd( new LockedInd( Tr069QueueableEvent::SECGW_CONNECTION_FSM) );
   Tr069Application::GetInstance().Enqueue(lockedInd);
}

void Tr069Cwmp::RequestReboot(shared_ptr<TransactionSessionComplete>)
{
   shared_ptr<RebootReq> rebootReq( new RebootReq() );
   Tr069Reboot::GetInstance().HandleEvent(rebootReq);
}

void Tr069Cwmp::HmsConnectionProhibitedEntry()
{
   Tr069ParameterValueChangeNotificationManager::GetInstance().SetHmsConnectionState(false);
}


void Tr069Cwmp::ShuttingDownWaitingForTransactionSessionCompletionEntry()
{
   Tr069ParameterValueChangeNotificationManager::GetInstance().SetHmsConnectionState(false);
}

void Tr069Cwmp::TerminateEntry()
{
   Tr069ParameterValueChangeNotificationManager::GetInstance().SetHmsConnectionState(false);
}

u32 Tr069Cwmp::GetConnectionFailureTimerInSeconds(u32 numberOfConsecutiveFailures)
{
   // TODO Need to get these values from MIB
   u32 minWaitInterval ;
   u32 retryMinWait ;
   u32 intervalMultiplier;
   u32 multiplicationCounter = numberOfConsecutiveFailures > 10 ? 10 : numberOfConsecutiveFailures;
   s32 numberOfDivisions = multiplicationCounter - 1;
   std::string connReqUsername;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute( PARAM_ID_TR069_SESSION_RETRY_INTERVAL,minWaitInterval);

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute( PARAM_ID_TR069_SESSION_RETRY_MULTIPLIER,intervalMultiplier);

   retryMinWait = minWaitInterval;

   for (u32 i = 0; i < multiplicationCounter - 1; i++)
   {
      retryMinWait *= intervalMultiplier;
      if (retryMinWait > 65535)
      {
         retryMinWait /= 1000;
         numberOfDivisions--;
      }
   }
   while (numberOfDivisions > 0)
   {
      retryMinWait /= 1000;
      numberOfDivisions--;
   }
   // TODO - Randomize the retry timer between min and max wait values
   return(retryMinWait);
}

void Tr069Cwmp::HandleConnectionFailure()
{
   if (m_connectionReattemptTimer == NULL_TIMER)
   {
      u32 updateUrlInUse;
      Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_TR069_CONN_WITH_URL_IN_USE, updateUrlInUse);

      if(updateUrlInUse)
      {
         if(CONN_MAX_RETRY <= m_successiveConnectionFailures)
         {
            if(false == Tr069Application::GetInstance().useUrlInUse)
            {
               m_successiveConnectionFailures = 0;
               Tr069Application::GetInstance().useUrlInUse = true;
            }
            else
            {
               u32 factoryReset;
               m_successiveConnectionFailures = 0;
               Tr069Application::GetInstance().useUrlInUse = false;

               Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_LTE_FACTORY_RESET_ON_TR069_CONN_FAIL, factoryReset);
               if(factoryReset)
               {
                  Tr069Application &app = Tr069Application::GetInstance();
                  OamActionReq oamActionReq(OAM_ACTION_FACTORY_RESET);
                  app.SendMessage(oamActionReq, ENTITY_OAM, ENTITY_TR069);
               }
            }
         }
      }

      u32 timerValueInSeconds = GetConnectionFailureTimerInSeconds(++m_successiveConnectionFailures);
      m_connectionReattemptTimer = Tr069Application::GetInstance().CreateTimer("", TimerEngineInterface::SecondsToTicks(timerValueInSeconds) );
      TRACE_PRINTF("CWMP: Failed TCP connection number %d and timeout = %d", m_successiveConnectionFailures, timerValueInSeconds);
   }
}

void Tr069Cwmp::HandleConnectionSuccess()
{
   TRACE_PRINTF("CWMP: Successful TCP connection");

   m_successiveConnectionFailures = 0;
   if (m_connectionReattemptTimer != NULL_TIMER)
   {
      Tr069Application::GetInstance().DeleteTimer( m_connectionReattemptTimer );
      m_connectionReattemptTimer = NULL_TIMER;
   }
   // Set BOOTSTRAP_COMPLETED
   u32 boostrapCompleted;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_HMS_BOOTSTRAP_COMPLETED, boostrapCompleted );
   if( !boostrapCompleted )
   {
      MibAttributeValues attrs;

      attrs.AddAttribute(PARAM_ID_HMS_BOOTSTRAP_COMPLETED, 1U);
      Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);
      m_bootEventSent = true;
   }

   u32 updateUrlInUse;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_LTE_TR069_CONN_WITH_URL_IN_USE, updateUrlInUse);

   if(updateUrlInUse)
   {
      if(!Tr069Application::GetInstance().useUrlInUse)
      {
         MibAttributeValues attrs;

         Url url;

         Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_MANAGEMENT_SERVER, url);

         attrs.AddAttribute(PARAM_ID_MANAGEMENT_SERVER_IN_USE, url.ToString().c_str());
         Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_OAM);
      }
   }
}

void Tr069Cwmp::IdleEntry()
{
   TRACE_PRINTF("Idle Entry - %d", m_transactionSessionResult);
   if (m_transactionSessionResult == TransactionSessionComplete::CONNECTION_FAILURE)
   {
      HandleConnectionFailure();
   }
   else
   {
      HandleConnectionSuccess();
   }
}

void Tr069Cwmp::AwaitInitialTransactionSessionEntry()
{
   Tr069ParameterValueChangeNotificationManager::GetInstance().SetHmsConnectionState(true);

   StartInitialTransactionSession(NULL);
}

void Tr069Cwmp::AwaitInitialTransactionSessionExit()
{
   Tr069Application::GetInstance().DeleteTimer( m_stateGuardTimer );

   m_stateGuardTimer = NULL_TIMER;
}

void Tr069Cwmp::AwaitTransportCnfEntry()
{
   if (m_cwmpUsesTunnel)
   {
      shared_ptr<TransportReq> transportReq(new TransportReq( Tr069QueueableEvent::CWMP_CONNECTION_FSM) );
      Tr069Application::GetInstance().Enqueue(transportReq);
   }
   else
   {
      shared_ptr<TransportCnf> transportCnf(new TransportCnf( true, Tr069QueueableEvent::CWMP_CONNECTION_FSM) );
      Tr069Application::GetInstance().Enqueue(transportCnf);
   }
}

void Tr069Cwmp::TransactionSessionInProgressEntry()
{
   if (!m_fsmTransactionSession)
   {
      m_fsmTransactionSession.reset(new Tr069TransactionSession( Tr069Application::GetInstance().GetMibCache(), *this ));
   }
   m_fsmSetParameterValueManager.reset(new Tr069SetParameterValueManager(
            Tr069Application::GetInstance().GetMibCache(),
            Tr069Application::GetInstance(),
            *m_fsmTransactionSession ));
   m_getParameterValuesManager.reset(new GetParameterValuesManager());
   m_getParameterNamesManager.reset(new GetParameterNamesManager());
   m_getParameterAttributesManager.reset(new GetParameterAttributesManager());

   RSYS_ASSERT(m_transactionSessionInProgressEvent);

   TRACE_PRINTF("Transaction Session %s starting...", m_transactionSessionInProgressEvent->ToString() );

   shared_ptr<StartTransactionSession> startTransactionSession(new StartTransactionSession());
   m_fsmTransactionSession->HandleEvent(startTransactionSession);

   switch(m_transactionSessionInProgressEvent->GetId())
   {
      case Tr069QueueableEvent::EVENT_0_BOOTSTRAP:
         {
            shared_ptr<Event0Bootstrap> boot = dynamic_pointer_cast<Event0Bootstrap>(m_transactionSessionInProgressEvent);
            Enqueue( boot );
         }
         break;

      case Tr069QueueableEvent::VALUE_CHANGE:
         {
            shared_ptr<ValueChange> valueChange = dynamic_pointer_cast<ValueChange>(m_transactionSessionInProgressEvent);
            Enqueue( valueChange );
         }
         break;

      case Tr069QueueableEvent::CONNECTION_REQ:
         {
            shared_ptr<ConnectionRequest> connectionRequest = dynamic_pointer_cast<ConnectionRequest>(m_transactionSessionInProgressEvent);
            Enqueue( connectionRequest );
         }
         break;

      case Tr069QueueableEvent::DOWNLOAD_RESPONSE:
         {
            shared_ptr<DownloadResponse> downloadResponse = dynamic_pointer_cast<DownloadResponse>(m_transactionSessionInProgressEvent);
            Enqueue( downloadResponse );
         }
         break;

      case Tr069QueueableEvent::UPLOAD_RESPONSE:
         {
            shared_ptr<UploadResponse> uploadResponse = dynamic_pointer_cast<UploadResponse>(m_transactionSessionInProgressEvent);
            Enqueue( uploadResponse );
         }
         break;

      case Tr069QueueableEvent::PERIODIC:
         {
            shared_ptr<Periodic> periodic = dynamic_pointer_cast<Periodic>(m_transactionSessionInProgressEvent);
            Enqueue( periodic );
         }
         break;
      case Tr069QueueableEvent::AUTO_TRANSFER_COMPLETE:
         {  
            shared_ptr<AutoTransfer> autoTransfer = dynamic_pointer_cast<AutoTransfer>(m_transactionSessionInProgressEvent);
            SendAutoTransferCompReq(autoTransfer);
         }
         break;
      default:
         break;
   }

}

void Tr069Cwmp::TransactionSessionInProgressExit()
{
   m_transactionSessionInProgressEvent.reset();
   m_fsmSetParameterValueManager.reset();
   m_fsmAddObjectManager.reset();
   //m_fsmTransactionSession.reset();
   m_getParameterValuesManager.reset();
   m_getParameterNamesManager.reset();
   m_getParameterAttributesManager.reset();
}

bool Tr069Cwmp::QueryIsTr069Enabled( shared_ptr<HmsModifyReq> )
{
   bool enableTr069 = true;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_ENABLE_TR069, enableTr069);
   return enableTr069;
}

bool Tr069Cwmp::QueryIsReconnectSecGw( shared_ptr<HmsModifyReq> )
{

   //Ideally we should have a seperate action function to set the HmsConnectionState.
   if(m_reconnectSecGw == true)
   {
      Tr069ParameterValueChangeNotificationManager::GetInstance().SetHmsConnectionState(true);
   }
   return (m_reconnectSecGw == true);
}


bool Tr069Cwmp::QueryIsInitialTransactionSession( shared_ptr<TransactionSessionCommand> transactionSessionCommand)
{
   return (transactionSessionCommand->GetEvent()->GetId() == Tr069QueueableEvent::EVENT_0_BOOTSTRAP);
}

bool Tr069Cwmp::QueryStartInitialTransactionSession( shared_ptr<TransactionSessionCommand> transactionSessionCommand)
{
   string wcdmaRemScanStatus = "";
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA),PARAM_ID_WCDMA_REM_SCAN_STATUS, wcdmaRemScanStatus ); 

   string lteRemScanStatus = "";
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_REM_SCAN_STATUS, lteRemScanStatus ); 

   u32 remScanOnBoot = false;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_WCDMA_REM_SCAN_ON_BOOT, remScanOnBoot ); 

   u32 lteRemScanOnBoot = false;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE), PARAM_ID_LTE_REM_SCAN_ON_BOOT, lteRemScanOnBoot ); 

   return ((true == remScanOnBoot) && (true == lteRemScanOnBoot) && (wcdmaRemScanStatus != INPROGRESS) && (lteRemScanStatus != INPROGRESS));

}

bool Tr069Cwmp::QueryTransportOk( shared_ptr<TransportCnf> transportCnf)
{
   return transportCnf->GetTransportOk();
}

bool Tr069Cwmp::QueryFapRebooting( shared_ptr<TransactionSessionComplete> )
{
   return Tr069Reboot::GetInstance().QueryFapAboutToReboot();
}

bool Tr069Cwmp::QueryFailedTransactionSessionRecoveryMechanismIsToSelectAnotherServer( shared_ptr<TransactionSessionComplete> transactionSessionComplete )
{
   bool failedTransactionSessionRecoveryMechanismIsToSelectAnotherServer = false;

   switch( m_transactionSessionInProgressEvent->GetId() )
   {
      case Tr069QueueableEvent::EVENT_0_BOOTSTRAP:
         {
            failedTransactionSessionRecoveryMechanismIsToSelectAnotherServer = true;
         }
         break;

      default:
         break;
   }

   return failedTransactionSessionRecoveryMechanismIsToSelectAnotherServer;
}

bool Tr069Cwmp::QueryTransactionSessionSucceded( shared_ptr<TransactionSessionComplete> transactionSessionComplete )
{
   bool succeded = !transactionSessionComplete->QueryFailed();

   if(succeded)
   {
      switch( m_transactionSessionInProgressEvent->GetId() )
      {
         case Tr069QueueableEvent::EVENT_0_BOOTSTRAP:
            {
               MibAttributeValues attrs;
               attrs.AddAttribute(PARAM_ID_HMS_BOOTSTRAP_COMPLETED, 1U);
               Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);
               m_bootEventSent = true;
            }
            break;

         default:
            break;
      }


   }

   return succeded;
}

bool Tr069Cwmp::QueryFailedTransactionSessionShouldBeIgnored( shared_ptr<TransactionSessionComplete> transactionSessionComplete )
{
   bool failedTransactionSessionShouldBeIgnored = false;

   switch( m_transactionSessionInProgressEvent->GetId() )
   {
      case Tr069QueueableEvent::CONNECTION_REQ:
         {
            failedTransactionSessionShouldBeIgnored = true;
         }
         break;

      case Tr069QueueableEvent::SCAN_RESULTS:
         {
            if(transactionSessionComplete->QueryResult() == TransactionSessionComplete::FAP_AT_UNAUTHORISED_LOCATION)
            {
               /* In terms of ServerConnection...
               */
               failedTransactionSessionShouldBeIgnored = true;
            }
         }
         break;

      default:
         break;
   }

   return failedTransactionSessionShouldBeIgnored;
}

void Tr069Cwmp::HandleEvent( shared_ptr<Queueable> event)
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
                  case Tr069QueueableEvent::CWMP_CONNECTION_FSM:
                     {
                        switch(tr069Event->GetId())
                        {
                           case Tr069QueueableEvent::HMS_MODIFY_REQ:
                              {
                                 shared_ptr<HmsModifyReq> hmsModifyReq = dynamic_pointer_cast<HmsModifyReq>(tr069Event);
                                 m_fsm.InjectHmsModifyReq( hmsModifyReq );
                              }
                              break;

                           case Tr069QueueableEvent::TRANSPORT_CNF:
                              {
                                 shared_ptr<TransportCnf> transportCnf = dynamic_pointer_cast<TransportCnf>(tr069Event);
                                 m_fsm.InjectTransportCnf( transportCnf );
                              }
                              break;

                           case Tr069QueueableEvent::TRANSACTION_SESSION_COMMAND:
                              {
                                 shared_ptr<TransactionSessionCommand> transactionSessionCommand = dynamic_pointer_cast<TransactionSessionCommand>(tr069Event);
                                 m_fsm.InjectTransactionSessionCommand( transactionSessionCommand );
                              }
                              break;

                           case Tr069QueueableEvent::TRANSACTION_SESSION_COMPLETE:
                              {
                                 shared_ptr<TransactionSessionComplete> transactionSessionComplete = dynamic_pointer_cast<TransactionSessionComplete>(tr069Event);
                                 m_fsm.InjectTransactionSessionComplete( transactionSessionComplete );
                              }
                              break;

                           case Tr069QueueableEvent::SHUTDOWN:
                              {
                                 shared_ptr<Shutdown> shutdown = dynamic_pointer_cast<Shutdown>(tr069Event);
                                 m_fsm.InjectShutdown( shutdown );
                              }
                              break;

                           case Tr069QueueableEvent::PERIODIC_INFORM_UPDATE:
                              {
                                 HandlePeriodicInformSubscriptionInd();
                              }
                              break;

                           case Tr069QueueableEvent::AUTO_TRANSFER_COMPLETE:
                              {
                                 shared_ptr<AutoTransfer> autoTransfer(new AutoTransfer());
                                 autoTransfer = dynamic_pointer_cast<AutoTransfer>(tr069Event);
                                 shared_ptr<TransactionSessionCommand> transSessCommand(new TransactionSessionCommand( autoTransfer));
                                 RSYS_ASSERT(transSessCommand);
                                 /* ALWAYS post to external queue */
                                 Tr069Application::GetInstance().Enqueue(transSessCommand);
                              }
                              break;

                           default:
                              RSYS_ASSERT_PRINTF(false,"Unhandled CWMP_CONNECTION_FSM event %s.", tr069Event->ToString());
                              break;
                        }
                        break;
                     }

                  case Tr069QueueableEvent::TRANSACTION_SESSION_FSM:
                     {
                        if(m_fsmTransactionSession)
                        {
                           m_fsmTransactionSession->HandleEvent(event);
                        }
                        else
                        {
                           TRACE_PRINTF("TRANSACTION_SESSION_FSM event %s dropped.", tr069Event->ToString())
                        }
                     }
                     break;

                  case Tr069QueueableEvent::SPV_FSM:
                     {
                        if(m_fsmSetParameterValueManager)
                        {
                           m_fsmSetParameterValueManager->HandleEvent(event);
                        }
                        else
                        {
                           TRACE_PRINTF("SPV_FSM event %s dropped.", tr069Event->ToString())
                        }
                     }
                     break;

                  case Tr069QueueableEvent::ADD_OBJECT_FSM:
                     {
                        if(m_fsmAddObjectManager)
                        {
                           m_fsmAddObjectManager->HandleEvent(event);
                        }
                        else
                        {
                           TRACE_PRINTF("SPV_FSM event %s dropped.", tr069Event->ToString())
                        }
                     }
                     break;

                  default:
                     RSYS_ASSERT_PRINTF(false, "Unsupported Event not handled %s", tr069Event->ToString() );
                     break;
               }
            }
         }
         break;

      case Queueable::MESSAGE_SERIALISED_DATA:
         {
            shared_ptr<MessageSerialisedData> message = dynamic_pointer_cast<MessageSerialisedData>(event);
            if (message)
            {
               switch (message->GetSerialisationId())
               {
                  case SERIALISATION_ID_REM_SCAN_CNF:
                     {
                        m_fsm.InjectRemScanCnf(NULL);
                     }
                     break;

                  case SERIALISATION_ID_MIB_VALIDATE_ATTRIBUTES_CNF:
                     {
                        if(m_fsmSetParameterValueManager)
                        {
                           m_fsmSetParameterValueManager->HandleEvent(event);
                        }
                     }
                     break;

                  case SERIALISATION_ID_MIB_CREATE_OBJECT_CNF:
                     {
                        if(m_fsmAddObjectManager)
                        {
                           m_fsmAddObjectManager->HandleEvent(event);
                        }
                     }
                     break;

                  case SERIALISATION_ID_MIB_DELETE_OBJECT_CNF:
                     {
                        if(m_fsmDeleteObjectManager)
                        {
                           m_fsmDeleteObjectManager->HandleEvent(event);
                        }
                     }
                     break;

                  default:
                     TRACE_PRINTF("Unhabdled message %s", message->ToString().c_str() )
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

bool Tr069Cwmp::HandleTimerExpiry(threeway::TimerHandle expiredTimer)
{
   bool timerHandled = false;

   if(expiredTimer)
   {
      if( expiredTimer == m_stateGuardTimer )
      {
         m_fsm.InjectStateGuardTimerExpiry( NULL );
         timerHandled = true;
      }
      else if( expiredTimer == m_periodicInformTimer )
      {
         HandlePeriodicInformTimerExpiry( NULL );
         timerHandled = true;
      }
      else if( expiredTimer == m_connectionReattemptTimer )
      {
         TRACE_PRINTF("Connection Failure Timer Expired");
         HandleConnectionFailureTimerExpiry( NULL );
         timerHandled = true;
      }
   }

   return timerHandled;
}

void Tr069Cwmp::HandleServerCommand( shared_ptr<HttpPostResponse> cwmpCommand)
{
   if( QueryAddObject(cwmpCommand) )
   {
      HandleAddObject(cwmpCommand);
   }
   else if( QueryDeleteObject(cwmpCommand) )
   {
      HandleDeleteObject(cwmpCommand);
   }
   else if( QueryDownloadRequest(cwmpCommand) )
   {
      HandleDownloadRequest(cwmpCommand);
   }
   else if( QueryFactoryReset(cwmpCommand) )
   {
      HandleFactoryReset(cwmpCommand);
   }
   else if( QueryGetParametersValueRequest(cwmpCommand) )
   {
      HandleGetParametersValueRequest(cwmpCommand);
   }
   else if( QueryGetParameterNamesRequest(cwmpCommand) )
   {
      HandleGetParameterNamesRequest(cwmpCommand);
   }
   else if( QueryGetParameterAttributesRequest(cwmpCommand) )
   {
      HandleGetParameterAttributesRequest(cwmpCommand);
   }
   else if( QueryReboot(cwmpCommand) )
   {
      HandleReboot(cwmpCommand);
   }
   else if( QuerySetParametersValueRequest(cwmpCommand) )
   {
      HandleSetParametersValueRequest(cwmpCommand);
   }
   else if( QuerySetParametersAttributesRequest(cwmpCommand) )
   {
      HandleSetParametersAttributesRequest(cwmpCommand);
   }
   else if( QueryUploadRequest(cwmpCommand) )
   {
      HandleUploadRequest(cwmpCommand);
   }
   else if( QueryGetRpcMethods(cwmpCommand) )
   {
      HandleGetRpcMethods(cwmpCommand);
   }
   else
   {
      HandleUnknownServerCommand(cwmpCommand);
   }
}

void Tr069Cwmp::HandleServerResponse( shared_ptr<HttpPostResponse> cwmpResponse)
{
   TRACE_PRINTF("Tr069Cwmp::HandleServerResponse");

   if( QueryInformResponse(cwmpResponse) || Query401Response(cwmpResponse))
   {
      m_fsmTransactionSession->IncrUnAuthErrCount();
      HandleInformResponse(cwmpResponse);
   }
   else if( QueryTransferCompleteResponse(cwmpResponse) )
   {
      HandleTransferCompleteResponse(cwmpResponse);
   }
   else
   {
      //HandleUnknownServerResponse( cwmpResponse );
   }
}

bool Tr069Cwmp::Query401Response( shared_ptr<HttpPostResponse> cwmpResponse)
{
   if (cwmpResponse && (cwmpResponse->getResponseErrCode() == 401))
      return true;
   else
      return false;
}

void Tr069Cwmp::HandleServerFault(shared_ptr<HttpPostResponse> httpResponse, TransactionSessionComplete::Result & tscResult)
{
   ENTER();

   boost::shared_ptr<Tr069ParseFault> fault = httpResponse->parsed->body->fault;

   if( fault->detail &&
         fault->detail->faultDetail )
   {
      int faultCode = atoi(fault->detail->faultDetail->faultcode.c_str());

      switch( faultCode )
      {

         default:
            {
               tscResult = TransactionSessionComplete::DEFAULT_FAILURE;
               TRACE_PRINTF("Unrecognised fault code = %s",fault->detail->faultDetail->faultcode.c_str());
            }
            break;
      }

      std::cerr <<
         "*************************************************\n"
         "******  TR069: Fault #" <<  fault->detail->faultDetail->faultcode << " " << fault->detail->faultDetail->faultstring <<  "\n"
         "*************************************************\n";
   }

   EXIT();
}

void Tr069Cwmp::HandleAddObject(shared_ptr<HttpPostResponse> httpResponse)
{
   //
   // FAP                             HMS
   //  |                               |
   //  |   AddObject(Request) |
   //  |<------------------------------|
   //  |                               |
   //  |              MIB              |
   //  | MibCreateObjReq  |            |
   //  |----------------->|            |
   //  | MibCreatObjCnf   |            |
   //  |<-----------------|            |
   //  |                               |
   //  | AddObject(Response)           |
   //  |------------------------------>|
   //  |                               |
   //

   shared_ptr<RpcAddObject> rpcAddObject(
         new RpcAddObject(
            httpResponse->parsed->body->addObject->m_objectName,
            httpResponse->parsed->body->addObject->m_parameterKey) );

   std::string cwmpId = httpResponse->parsed->header->cwmp_Id;
   rpcAddObject->SetCwmpId(cwmpId);

   if(!m_fsmAddObjectManager)
   {
      m_fsmAddObjectManager.reset(new
            AddObjectManager(
               Tr069Application::GetInstance().GetMibCache(),
               Tr069Application::GetInstance(),
               *m_fsmTransactionSession) );
   }

   m_fsmAddObjectManager->HandleEvent(rpcAddObject);
}

void Tr069Cwmp::HandleDeleteObject(shared_ptr<HttpPostResponse> httpResponse)
{
   //
   // FAP                             HMS
   //  |                               |
   //  |   AddObject(Request) |
   //  |<------------------------------|
   //  |                               |
   //  |              MIB              |
   //  | MibCreateObjReq  |            |
   //  |----------------->|            |
   //  | MibCreatObjCnf   |            |
   //  |<-----------------|            |
   //  |                               |
   //  | AddObject(Response)           |
   //  |------------------------------>|
   //  |                               |
   //

   shared_ptr<RpcDeleteObject> rpcDeleteObject(
         new RpcDeleteObject(
            httpResponse->parsed->body->deleteObject->m_objectName,
            httpResponse->parsed->body->deleteObject->m_parameterKey) );

   std::string cwmpId = httpResponse->parsed->header->cwmp_Id;
   rpcDeleteObject->SetCwmpId(cwmpId);

   if(!m_fsmDeleteObjectManager)
   {
      m_fsmDeleteObjectManager.reset(new
            DeleteObjectManager(
               Tr069Application::GetInstance().GetMibCache(),
               Tr069Application::GetInstance(),
               *m_fsmTransactionSession) );
   }

   m_fsmDeleteObjectManager->HandleEvent(rpcDeleteObject);
}


void Tr069Cwmp::HandleSetParametersValueRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   //
   // FAP                             HMS
   //  |                               |
   //  |   SetParameterValues(Request) |
   //  |<------------------------------|
   //  |                               |
   //  |               DmMgr           |
   //  | DmVerifyReq()   |             |
   //  |================>|             |
   //  |     DmVerifyCnf |             |
   //  |<----------------|             |
   //  |              MIB              |
   //  | MibVerifyReq  |               |
   //  |-------------->|               |
   //  | MibVerifyCnf  |               |
   //  |<--------------|               |
   //  |                  OAM          |
   //  | SetMibAttributes  |           |
   //  |------------------>|           |
   //  |                               |
   //  | SetParameterValues(Response)  |
   //  |------------------------------>|
   //  |                               |
   //

   shared_ptr<RpcSetParameterValue> rpcSetParameterValue( new RpcSetParameterValue( httpResponse->parsed->body->setParameterValues->m_parameterKey) );

   if(httpResponse->parsed->body->setParameterValues->m_parameterList)
   {
      boost::shared_ptr<ParameterList> parameterList = httpResponse->parsed->body->setParameterValues->m_parameterList;

      ParameterList_t::const_iterator i;

      for( i =  parameterList->m_parameters.begin();
            i != parameterList->m_parameters.end();
            ++i)
      {
         shared_ptr<ParameterValueStruct> pvs = i->second;

         const string & name  = pvs->m_name;
         const string & value = pvs->m_value;

         rpcSetParameterValue->Add( name, value );
      }

   }
   rpcSetParameterValue->SetCwmpId(httpResponse->parsed->header->cwmp_Id);
   m_fsmSetParameterValueManager->HandleEvent(rpcSetParameterValue);
}

void Tr069Cwmp::HandleSetParametersAttributesRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   //
   // FAP                                 HMS
   //  |                                   |
   //  |   SetParameterAttributes(Request) |
   //  |<----------------------------------|
   //  |                                   |
   //  |                    DmMgr          |
   //  | DmSetAtrributesReq() |            |
   //  |=====================>|            |
   //  |                                   |
   //  | SetParameterAttributes(Response)  |
   //  |---------------------------------->|
   //  |                                   |
   //

   RpcSetParameterAttribute rpcSetParameterAttribute;

   if(httpResponse->parsed->body->setParameterAttributes->parameterList)
   {
      boost::shared_ptr<Tr069ParseParameterAttributeList> parameterList = httpResponse->parsed->body->setParameterAttributes->parameterList;

      for( vector< shared_ptr<Tr069ParseParameterAttributeStruct> >::const_iterator i =  parameterList->parameterAttributeStruct.begin();
            i != parameterList->parameterAttributeStruct.end();
            ++i)
      {
         shared_ptr<Tr069ParseParameterAttributeStruct> pas = *i;

         TRACE_PRINTF(" Name(%s) NotficationChange(%s) notification(%s) accessListChange(%s) accessList(%s)", pas->name.c_str(), pas->notificationChange.c_str(),pas->notification.c_str(),pas->accessListChange.c_str(), pas->accessList.c_str());

         bool notificationChange;

         StringUtils::ConvertStringToBool(pas->notificationChange, notificationChange);

         if(notificationChange)
         {
            u32 notification;

            (void)StringUtils::ConvertStringToInteger(pas->notification, notification);

            rpcSetParameterAttribute.Add( pas->name, notification );
         }
      }

   }
   rpcSetParameterAttribute.SetCwmpId(httpResponse->parsed->header->cwmp_Id);
   shared_ptr<Tr069FsmInterface> tranactionSessionFsmInterface = dynamic_pointer_cast<Tr069FsmInterface>(m_fsmTransactionSession);
   Tr069Application::GetInstance().GetParameterAttributeManager()->HandleSetParamAttributes( *tranactionSessionFsmInterface, rpcSetParameterAttribute );
}

void Tr069Cwmp::HandleInformResponse(shared_ptr<HttpPostResponse> httpResponse)
{
   Tr069Application &app = Tr069Application::GetInstance();
   u32 downLoadCompleted;
   string commandKey;

   app.GetMibCache().GetMibAttribute(PARAM_ID_LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE, downLoadCompleted );
   app.GetMibCache().GetMibAttribute(PARAM_ID_LTE_COMMAND_KEY, commandKey );

   if(downLoadCompleted)
   {
      TimeWrap now;
      TimeWrap dwStartTime;
      string startTime;
      string faultString = "";
      struct tm tm;

      app.GetMibCache().GetMibAttribute(PARAM_ID_LTE_DOWNLOAD_START_TIME, startTime);

      memset(&tm, 0, sizeof(struct tm));
      strptime((const char*)startTime.c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm);
      dwStartTime = mktime(&tm);

      u32 upgradeCompleted;
      app.GetMibCache().GetMibAttribute(PARAM_ID_LTE_SOFTWARE_UPGRADE_COMPLETE, upgradeCompleted );
      if(upgradeCompleted > 1)
      {
         std::stringstream ss("");
         ss<<upgradeCompleted;
         faultString = ss.str();
      }

      MibAttributeValues attrs;
      attrs.AddAttribute(PARAM_ID_LTE_SOFTWARE_UPGRADE_COMPLETE, false);

      PostTransferComplete( commandKey, Tr069ParseFaultDetail::NoFault, faultString, dwStartTime, now, "");

      attrs.AddAttribute(PARAM_ID_LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE, false);

      app.GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);
   }

   if(Query401Response(httpResponse) && m_fsmTransactionSession->GetUnAuthErrCount()<2)
   {
      shared_ptr<Event0Bootstrap> boot = dynamic_pointer_cast<Event0Bootstrap>(m_transactionSessionInProgressEvent);
      Enqueue( boot );
   }
}

void Tr069Cwmp::HandleTransferCompleteResponse(shared_ptr<HttpPostResponse> httpResponse)
{
}

void Tr069Cwmp::HandleUnknownServerResponse(shared_ptr<HttpPostResponse> httpResponse)
{
   std::string cwmpId = httpResponse->parsed->header->cwmp_Id;
   std::ostringstream txFault;
   std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
   txFault << "<soap-env:Envelope" << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";
   if(timeout.compare("") != 0)
   {
      txFault << 
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">" <<timeout<<"</cwmp:SessionTimeout>";
   }
   txFault <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<soap-env:Fault>"
      "<faultcode>Server</faultcode>"
      "<faultstring>CWMP fault</faultstring>"
      "<detail>"
      "<cwmp:Fault>"
      "<FaultCode>9000</FaultCode>"
      "<FaultString>Method not supported</FaultString>"
      "</cwmp:Fault>"
      "</detail>"
      "</soap-env:Fault>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<string> faultPost(new string(txFault.str() ));
   m_fsmTransactionSession->EnqueueSoapEnvelope(faultPost);
}

void Tr069Cwmp::PostTransferComplete(
      const string & commandKey,
      Tr069ParseFaultDetail::FaultCode faultcode,
      const string & faultString,
      const TimeWrap & startTime,
      const TimeWrap & completeTime,
      const string cwmpId
      )
{
   string start;
   string complete;
   string cwmpId_loc;
   string timeout = Tr069Application::GetInstance().GetSoapTimeout();
   if (cwmpId.empty())
   {
      ostringstream ss;
      ss << random();
      cwmpId_loc = ss.str();
   }else
   {
      cwmpId_loc = cwmpId;
   }

   Tr069Application::GetInstance().GetFormattedUtcTime( start, startTime);
   Tr069Application::GetInstance().GetFormattedUtcTime( complete, completeTime);

   std::ostringstream transferComplete;
   transferComplete << "<soap-env:Envelope"
      << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<<cwmpId_loc<<"</cwmp:ID>";
   if(timeout.compare("") != 0)
   {
      transferComplete << 
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<<timeout<<"</cwmp:SessionTimeout>";
   }
   transferComplete <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:TransferComplete>"
      "<CommandKey>" << commandKey << "</CommandKey>"
      "<FaultStruct>"
      "<FaultCode>" << faultcode << "</FaultCode>"
      "<FaultString>" << XmlSafeString(faultString) << "</FaultString>"
      "</FaultStruct>"
      "<StartTime>" << start << "</StartTime>"
      "<CompleteTime>" << complete << "</CompleteTime>"
      "</cwmp:TransferComplete>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<string> transferPost(new string(transferComplete.str() ));
   m_fsmTransactionSession->EnqueueSoapEnvelope(transferPost);
}

void Tr069Cwmp::Enqueue(shared_ptr<Event0Bootstrap> boot)
{
   string currentTime;
   MibAttributeValues attrs;

   Tr069Application &app = Tr069Application::GetInstance();

   CwmpInform inform(m_successiveConnectionFailures);

   if(!m_bootEventSent)
   {
      inform.m_event.AddEvent("1 BOOT");
   }

   u32 boostrapCompleted;
   u32 rebootStatus;
   app.GetMibCache().GetMibAttribute(PARAM_ID_HMS_BOOTSTRAP_COMPLETED, boostrapCompleted );
   if(!boostrapCompleted)
   {
      inform.m_event.AddEvent("0 BOOTSTRAP");
   }

   Tr069ParameterValueChangeNotificationManager::GetInstance().InformManagementServer(inform);

   u32 upgrdCompleted, downloadCompleted;
   app.GetMibCache().GetMibAttribute(PARAM_ID_LTE_SOFTWARE_UPGRADE_COMPLETE, upgrdCompleted );
   app.GetMibCache().GetMibAttribute(PARAM_ID_LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE, downloadCompleted );
   app.GetMibCache().GetMibAttribute(PARAM_ID_LTE_REBOOT_STATUS, rebootStatus);

   if(upgrdCompleted && downloadCompleted)
   {
      inform.m_event.AddEvent("7 TRANSFER COMPLETE");
      inform.m_event.AddEvent("M Download");
   }
   else if(rebootStatus)
   {
      inform.m_event.AddEvent("M Reboot");

      attrs.AddAttribute(PARAM_ID_LTE_REBOOT_STATUS, false);
   }

   app.GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);
   //
   //  FAP                      CS
   //  |                        |
   //  | Inform(Request)        |
   //  |----------------------->|
   //  |                        |
   //
   //  expecting:
   //  |       Inform(Response) |
   //  |<-----------------------|
   //  |                        |
   //
   SoapEnvelope envelope(inform);
   ostringstream ss;
   ss << random();
   envelope.soapheader.SetCwmpId(ss.str());

   shared_ptr<string> informPost(new string( envelope.Xmlise() ));

   m_fsmTransactionSession->EnqueueSoapEnvelope(informPost);
}

void Tr069Cwmp::Enqueue(shared_ptr<ValueChange> valueChange)
{
   bool required = Tr069ParameterValueChangeNotificationManager::GetInstance().QueryIfActiveValueChangeNotificationStillOutstanding();

   if(required)
   {
      //
      //  FAP                      CS
      //  |                        |
      //  | Inform(Request)        |
      //  |----------------------->|
      //  |                        |
      //
      //  expecting:
      //  |       Inform(Response) |
      //  |<-----------------------|
      //  |                        |
      //
      CwmpInform inform(m_successiveConnectionFailures);
      inform.m_event.AddEvent("4 VALUE CHANGE");

      Tr069ParameterValueChangeNotificationManager::GetInstance().InformManagementServer(inform);

      SoapEnvelope envelope(inform);
      ostringstream ss;
      ss << random();
      envelope.soapheader.SetCwmpId(ss.str());

      shared_ptr<string> envelopeStr(new string( envelope.Xmlise() ));
      m_fsmTransactionSession->EnqueueSoapEnvelope(envelopeStr);
   }
   else
   {
      shared_ptr<TransactionSessionComplete> transactionSessionComplete(new TransactionSessionComplete());
      m_fsm.InjectTransactionSessionComplete( transactionSessionComplete );
   }

}

void Tr069Cwmp::Enqueue(shared_ptr<ConnectionRequest> connectionRequest)
{
   //
   //  FAP                      CS
   //  |                        |
   //  | Inform(Request)        |
   //  |----------------------->|
   //  |                        |
   //
   //  expecting:
   //  |       Inform(Response) |
   //  |<-----------------------|
   //  |                        |
   //
   CwmpInform inform (m_successiveConnectionFailures);
   inform.m_event.AddEvent("6 CONNECTION REQUEST");

   Tr069ParameterValueChangeNotificationManager::GetInstance().InformManagementServer(inform);

   SoapEnvelope envelope( inform );
   ostringstream ss;
   ss << random();
   envelope.soapheader.SetCwmpId(ss.str());

   shared_ptr<string> envelopeStr(new string( envelope.Xmlise() ));
   m_fsmTransactionSession->EnqueueSoapEnvelope(envelopeStr);
}

void Tr069Cwmp::Enqueue(shared_ptr<Periodic> periodic)
{
   //
   //  FAP                      CS
   //  |                        |
   //  | Inform(Periodic)       |
   //  |----------------------->|
   //  |                        |
   //
   //  expecting:
   //  |       Inform(Response) |
   //  |<-----------------------|
   //  |                        |
   //
   CwmpInform inform (m_successiveConnectionFailures);
   inform.m_event.AddEvent("2 PERIODIC");

   Tr069ParameterValueChangeNotificationManager::GetInstance().InformManagementServer(inform);

   SoapEnvelope envelope( inform );
   ostringstream ss;
   ss << random();
   envelope.soapheader.SetCwmpId(ss.str());

   shared_ptr<string> envelopeStr(new string( envelope.Xmlise() ));
   TRACE_PRINTF("Data = %s", envelopeStr->c_str());
   m_fsmTransactionSession->EnqueueSoapEnvelope(envelopeStr);
}

void Tr069Cwmp::Enqueue(shared_ptr<DownloadResponse> downloadResponse)
{
   //
   //  FAP                      CS
   //  |                        |
   //  | Inform(Request)        |
   //  |----------------------->|
   //  |                        |
   //
   //  expecting:
   //  |       Inform(Response) |
   //  |<-----------------------|
   //  |                        |
   //
   CwmpInform inform(m_successiveConnectionFailures);
   inform.m_event.AddEvent(downloadResponse->GetEventCode());

   Tr069ParameterValueChangeNotificationManager::GetInstance().InformManagementServer(inform);

   SoapEnvelope envelope(inform);

   shared_ptr<string> envelopeStr(new string( envelope.Xmlise() ));
   m_fsmTransactionSession->EnqueueSoapEnvelope(envelopeStr);

   Tr069Application &app = Tr069Application::GetInstance();

   u32 downLoadCompleted;
   app.GetMibCache().GetMibAttribute(PARAM_ID_LTE_SOFTWARE_IMAGE_DOWNLOAD_COMPLETE, downLoadCompleted );

   if(!downLoadCompleted)
   {
      PostTransferComplete(
            downloadResponse->GetCommandKey(),
            downloadResponse->GetFaultCode(),
            downloadResponse->GetFaultString(),
            downloadResponse->GetStartTime(),
            downloadResponse->GetStopTime(),"" );
   }
}

void Tr069Cwmp::Enqueue(shared_ptr<UploadResponse> uploadResponse)
{
   shared_ptr<UploadRequest> uploadRequest = uploadResponse->GetUploadRequest();
   shared_ptr<FtpCompleteInd> ftpCompleteInd = uploadResponse->GetFtpCompleteInd();
   shared_ptr<FtpFile> ftpFile = uploadRequest->GetFtpFile();

   CwmpInform inform(m_successiveConnectionFailures);

   if(ftpCompleteInd->GetSucceeded())
   {
      inform.m_event.AddEvent(ftpFile->GetResponseEventCodeSuccessString());
      inform.m_event.AddEvent("M Upload");
   }
   else
   {
      inform.m_event.AddEvent(ftpFile->GetResponseEventCodeFailureString());
      inform.m_event.AddEvent("M Upload");
   }

   //
   //  FAP                      CS
   //  |                        |
   //  | Inform(Request)        |
   //  |----------------------->|
   //  |                        |
   //
   //  expecting:
   //  |       Inform(Response) |
   //  |<-----------------------|
   //  |                        |
   //

   Tr069ParameterValueChangeNotificationManager::GetInstance().InformManagementServer(inform);

   SoapEnvelope envelope(inform);

   shared_ptr<string> envelopeStr(new string( envelope.Xmlise() ));
   m_fsmTransactionSession->EnqueueSoapEnvelope(envelopeStr);


   Tr069ParseFaultDetail::FaultCode faultcode = Tr069ParseFaultDetail::NoFault;
   string faultString;

   if( !ftpCompleteInd->GetSucceeded() )
   {
      faultString = ftpCompleteInd->GetFailureString();

      if(string::npos != ftpCompleteInd->GetFailureString().find("530"))
      {
         faultcode = Tr069ParseFaultDetail::FileTransferServerAuthenticationFailure;
      }
      else
      {
         faultcode = Tr069ParseFaultDetail::UploadFailure;
      }
   }

   PostTransferComplete(
         uploadRequest->GetCommandKey(),
         faultcode,
         faultString,
         ftpCompleteInd->GetStartTime(),
         ftpCompleteInd->GetStopTime(),"" );

   EXIT();
}

void Tr069Cwmp::SendAutoTransferCompReq(shared_ptr<AutoTransfer> autoTransfer)
{
   std::ostringstream ss;
   ss<<random();
   AutoTransferCompResponse autoTransferResponse(autoTransfer->GetFileName(),autoTransfer->GetStartTime(),
                                                 autoTransfer->GetCompleteTime(),autoTransfer->GetUploadSuccess());
   SoapEnvelope envelope(autoTransferResponse);
   envelope.soapheader.SetCwmpId(ss.str());
   std::string timeout = Tr069Application::GetInstance().GetSoapTimeout();
   envelope.soapheader.SetSoapTimeout(timeout);
   shared_ptr<string> envelopeStr(new string( envelope.Xmlise() ));
   TRACE_PRINTF("%d: Sending )Complete Request",__LINE__);
   m_fsmTransactionSession->EnqueueSoapEnvelope(envelopeStr);
}

void Tr069Cwmp::HandleUnknownServerCommand(shared_ptr<HttpPostResponse> httpResponse)
{
   std::ostringstream txFault;
   std::string cwmpId = "", timeout = Tr069Application::GetInstance().GetSoapTimeout();
   if(httpResponse->parsed->header)
   {
      cwmpId = httpResponse->parsed->header->cwmp_Id;
   }
   txFault << "<soap-env:Envelope" << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>";
   if(cwmpId.compare("") != 0)
   {
      txFault << "<cwmp:ID soap-env:mustUnderstand=\"1\">"<<cwmpId<<"</cwmp:ID>";
   }
   if(timeout.compare("") != 0)
   {
      txFault <<
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<<timeout<<"</cwmp:SessionTimeout>";
   }
   txFault <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<soap-env:Fault>"
      "<faultcode>Server</faultcode>"
      "<faultstring>CWMP fault</faultstring>"
      "<detail>"
      "<cwmp:Fault>"
      "<FaultCode>9000</FaultCode>"
      "<FaultString>Method not supported</FaultString>"
      "</cwmp:Fault>"
      "</detail>"
      "</soap-env:Fault>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> postReq(new HttpPostRequest( txFault.str().c_str()) );
   m_fsmTransactionSession->HandleEvent(postReq);
}

void Tr069Cwmp::HandleReboot(shared_ptr<HttpPostResponse> httpResponse)
{
   ENTER();

   Tr069Application &app = Tr069Application::GetInstance();

   u32 rebootOffCount;
   app.GetMibCache().GetMibAttribute(PARAM_ID_RPC_REBOOT_OFF_COUNT, rebootOffCount );

   //
   //  FAP                            CS
   //  |                               |
   //  |               Reboot(Request) |
   //  |<------------------------------|
   //  |                               |
   //  | Reboot(Response)              |
   //  |------------------------------>|
   //  |                               |
   //
   Tr069ParseReboot &reboot = *httpResponse->parsed->body->reboot;
   std::string cwmpId = httpResponse->parsed->header->cwmp_Id;
   std::string timeout = app.GetSoapTimeout();

   std::ostringstream txRebootResponse;
   txRebootResponse << "<soap-env:Envelope"
      << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";
   if(timeout.compare("") != 0)
   {
      txRebootResponse <<
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<<timeout<<"</cwmp:SessionTimeout>";
   }
   txRebootResponse <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:RebootResponse/>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> postReq(new HttpPostRequest( txRebootResponse.str().c_str()) );
   m_fsmTransactionSession->HandleEvent(postReq);

   MibAttributeValues attrs;
   attrs.AddAttribute(PARAM_ID_RPC_REBOOT_COMMAND_KEY, reboot.commandKey);
   attrs.AddAttribute(PARAM_ID_RPC_REBOOT_OFF_COUNT, ++rebootOffCount);

   app.GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);

   app.RebootFapViaOam();

   EXIT();

}

void Tr069Cwmp::HandleGetParametersValueRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   //
   //  FAP                            CS
   //  |                               |
   //  |   GetParameterValues(Request) |
   //  |<------------------------------|
   //  |                               |
   //  | GetParameterValues(Response)  |
   //  |------------------------------>|
   //  |                               |
   //

   RpcGetParameterValues rpcGetParameterValues;

   if(httpResponse->parsed->body->getParameterValues->parameterNames)
   {
      boost::shared_ptr<Tr069ParseParameterNames> parameterNames = httpResponse->parsed->body->getParameterValues->parameterNames;

      for(std::vector< std::string >::iterator it = parameterNames->aString.begin(); it != parameterNames->aString.end(); ++it)
      {
         string parameterName = *it;

         rpcGetParameterValues.Add(parameterName);
      }
   }
   rpcGetParameterValues.SetCwmpId(httpResponse->parsed->header->cwmp_Id);

   m_getParameterValuesManager->HandleGetParameterValues(*m_fsmTransactionSession, rpcGetParameterValues);
}

void Tr069Cwmp::HandleGetParameterAttributesRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   //
   //  FAP                                CS
   //  |                                   |
   //  |   GetParameterAttributes(Request) |
   //  |<----------------------------------|
   //  |                                   |
   //  | GetParameterAttributes(Response)  |
   //  |---------------------------------->|
   //  |                                   |
   //

   RpcGetParameterAttributes rpcGetParameterAttributes;

   if(httpResponse->parsed->body->getParameterAttributes->parameterNames)
   {
      boost::shared_ptr<Tr069ParseParameterNames> parameterNames = httpResponse->parsed->body->getParameterAttributes->parameterNames;

      for(std::vector< std::string >::iterator it = parameterNames->aString.begin(); it != parameterNames->aString.end(); ++it)
      {
         string parameterName = *it;

         rpcGetParameterAttributes.Add(parameterName);
      }
   }
   rpcGetParameterAttributes.SetCwmpId(httpResponse->parsed->header->cwmp_Id);

   m_getParameterAttributesManager->HandleGetParameterAttributes(*m_fsmTransactionSession, rpcGetParameterAttributes);
}

void Tr069Cwmp::HandleGetParameterNamesRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   //
   //  FAP                            CS
   //  |                               |
   //  |   GetParameterNames (Request) |
   //  |<------------------------------|
   //  |                               |
   //  | GetParameterNames (Response)  |
   //  |------------------------------>|
   //  |                               |
   //

   RpcGetParameterNames rpcGetParameterNames;

   TRACE_PRINTF("Adding path (%s) to RPC object", httpResponse->parsed->body->getParameterNames->parameterPath.c_str());
   rpcGetParameterNames.Add(httpResponse->parsed->body->getParameterNames->parameterPath);
   TRACE_PRINTF("Adding CWMP ID (%s) to RPC object", httpResponse->parsed->header->cwmp_Id.c_str());
   rpcGetParameterNames.SetCwmpId(httpResponse->parsed->header->cwmp_Id);
   m_getParameterNamesManager->HandleGetParameterNames(*m_fsmTransactionSession, rpcGetParameterNames);
}

void Tr069Cwmp::HandleDownloadRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   ENTER ();

   Tr069Application &app = Tr069Application::GetInstance();
   MibAttributeValues attrs;

   string swPackageA;
   if(app.GetMibCache().IsMibAttributePresent(PARAM_ID_SW_UPDATE_PACKAGE_NAME_A))
   {
      app.GetMibCache().GetMibAttribute(PARAM_ID_SW_UPDATE_PACKAGE_NAME_A, swPackageA );
   }
   else
   {
      TRACE_MSG_LEV(TRACE_WARNING, "Trying to get PARAM_ID_SW_UPDATE_PACKAGE_NAME_A but no value available in cache");
   }

   string swPackageB;
   if(app.GetMibCache().IsMibAttributePresent(PARAM_ID_SW_UPDATE_PACKAGE_NAME_B))
   {
      app.GetMibCache().GetMibAttribute(PARAM_ID_SW_UPDATE_PACKAGE_NAME_B, swPackageB );
   }
   else
   {
      TRACE_MSG_LEV(TRACE_WARNING, "Trying to get PARAM_ID_SW_UPDATE_PACKAGE_NAME_B but no value available in cache");
   }

   string swPackageActive;
   if(app.GetMibCache().IsMibAttributePresent(PARAM_ID_SW_PACKAGE_ACTIVE))
   {
      app.GetMibCache().GetMibAttribute(PARAM_ID_SW_PACKAGE_ACTIVE, swPackageActive );
   }
   else
   {
      TRACE_MSG_LEV(TRACE_WARNING, "Trying to get PARAM_ID_SW_PACKAGE_ACTIVE but no value available in cache");
   }

   enum {
      DownloadHasBeenCompleted = 0,
      DownloadHasNotBeenCompletedAndApplied = 1,
   } responseStatus = DownloadHasNotBeenCompletedAndApplied;

   shared_ptr<DownloadRequest> downloadRequest;

   //
   //  FAP                            CS
   //  |                               |
   //  |             Download(Request) |
   //  |<------------------------------|
   //  |                               |
   //  | Download(Response)            |
   //  |------------------------------>|
   //  |                               |
   //
   Tr069ParseDownload &download = *httpResponse->parsed->body->download;

   if( ( download.fileType == "1 Firmware Upgrade Image" ) || ( download.fileType == "2 Web Content" ) || ( download.fileType == "3 Vendor Configuration File" ) )
   {
      if(download.fileType == "1 Firmware Upgrade Image")
      {
         attrs.AddAttribute(PARAM_ID_LTE_SOFTWARE_UPGRADE_COMPLETE, true);
         attrs.AddAttribute(PARAM_ID_LTE_COMMAND_KEY, download.commandKey);

         app.GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);
      }

      TRACE_PRINTF("X 000FBB SW transfer %s. A::%s, B::%s, Active::%s", download.targetFileName.c_str(), swPackageA.c_str(), swPackageB.c_str(), swPackageActive.c_str() );

      string filePath = getConfigFilePath();

      shared_ptr<DownloadRequest> possibleDownloadRequest(new DownloadRequest(
               download.commandKey,
               shared_ptr<SwTransferFile>(new SwTransferFile()),
               TimerEngineInterface::HoursToTicks(6),
               download.url,
               download.username,
               download.password,
               atoi(download.fileSize.c_str()),
               download.targetFileName,
               download.successUrl,
               download.failureUrl,
               filePath.c_str()) );

      if( (possibleDownloadRequest->GetFilename() != swPackageA) &&
            (possibleDownloadRequest->GetFilename() != swPackageB) )
      {
         MibAttributeValues SwUpdateAttrs;
         SwUpdateAttrs.AddAttribute(PARAM_ID_SW_UPDATE_PACKAGE_NAME_A,possibleDownloadRequest->GetFilename());
         app.GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),SwUpdateAttrs, ENTITY_OAM);
         downloadRequest = possibleDownloadRequest;
      }
      else
      {
         responseStatus = DownloadHasBeenCompleted;
      }
   }

   TimeWrap now;
   string startTime = (string)now.ToString();

   attrs.AddAttribute(PARAM_ID_LTE_DOWNLOAD_START_TIME, startTime);

   app.GetMibCache().SetMibAttributesByDn(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),attrs, ENTITY_OAM);

   std::string cwmpId = httpResponse->parsed->header->cwmp_Id;
   std::string timeout = app.GetSoapTimeout();
   std::ostringstream txDownloadResponse;
   txDownloadResponse << "<soap-env:Envelope"
      << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<<random()<<"</cwmp:ID>";
   if(timeout.compare("") != 0)
   {
      txDownloadResponse << 
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<< timeout <<"</cwmp:SessionTimeout>";
   }
   txDownloadResponse << 
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:DownloadResponse>"
      "<Status>" << responseStatus << "</Status>"
      "<StartTime>" << now.ToString() << "</StartTime>"
      "<CompleteTime>0001-01-01T00:00:00Z</CompleteTime>"
      "</cwmp:DownloadResponse>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> postReq(new HttpPostRequest( txDownloadResponse.str().c_str()) );
   m_fsmTransactionSession->HandleEvent(postReq);

   if( downloadRequest )
   {
      RSYS_ASSERT(responseStatus != DownloadHasBeenCompleted);

      shared_ptr<FtpSessionCommand> fsc(new FtpSessionCommand( downloadRequest ));
      app.timerDelayedProcedures.Enqueue(fsc, TimerEngineInterface::SecondsToTicks( atoi(download.delaySeconds.c_str()) ) );
   }

   EXIT();
}

static void handleUploadPmDataRequest( Tr069ParseUpload & upload )
{
   Tr069Application &app = Tr069Application::GetInstance();

   shared_ptr<UploadRequest> uploadRequest(new UploadRequest(
            upload.commandKey,
            shared_ptr<PmDataFile>(new PmDataFile()),
            TimerEngineInterface::MinutesToTicks(5),
            upload.url,
            upload.username,
            upload.password ) );

   RSYS_ASSERT(uploadRequest);

   Filename localFile( uploadRequest->GetLocalDirectory(), uploadRequest->GetFilename() );

   // TODO: Generate PM Data file.
   if (app.GeneratePmDataFile(localFile))
   {
      shared_ptr<FtpSessionCommand> fsc(new FtpSessionCommand( uploadRequest ));
      app.timerDelayedProcedures.Enqueue(fsc, TimerEngineInterface::SecondsToTicks( atoi(upload.delaySeconds.c_str()) ) );
   }
   else
   {
      TRACE_PRINTF("handleUploadPmDataRequest: Attn!! Ftp session is not started as PMDataFile is not generated");
   }   
}

#if 0
static void handleUploadSwDiagnosticsRequest( Tr069ParseUpload & upload )
{
   Tr069Application &app = Tr069Application::GetInstance();

   shared_ptr<UploadRequest> uploadRequest(new UploadRequest(
            upload.commandKey,
            shared_ptr<SwDiagnosticsFile>(new SwDiagnosticsFile()),
            TimerEngineInterface::MinutesToTicks(35),
            upload.url,
            upload.username,
            upload.password ) );

   RSYS_ASSERT(uploadRequest);

   string localFileUrl = uploadRequest->GetLocalDirectory() + uploadRequest->GetFilename();

   // Generate PM Data file.
   ostringstream generateSwDiagnosticsFile;

   generateSwDiagnosticsFile <<
      "cd /dbx/trace && " <<
      "./create-trace-tarball " << localFileUrl << " && " <<
      "mv -f " << localFileUrl << ".tar.gz " << localFileUrl;

   TRACE_PRINTF("%s", generateSwDiagnosticsFile.str().c_str());
   if(system( generateSwDiagnosticsFile.str().c_str() ) != oam_ret_zero)
   {
      TRACE_MSG("handleUploadSwDiagnosticsRequest : Failed to generate Software Diagnostic File");
   }

   shared_ptr<FtpSessionCommand> fsc(new FtpSessionCommand( uploadRequest ));
   app.timerDelayedProcedures.Enqueue(fsc, TimerEngineInterface::SecondsToTicks( atoi(upload.delaySeconds.c_str()) ) );
}
#endif

void Tr069Cwmp::HandleUploadRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   ENTER
      ();

   Tr069Application &app = Tr069Application::GetInstance();

   string currentTime;
   app.GetFormattedCurrentTime(currentTime);

   //
   //  FAP                            CS
   //  |                               |
   //  |               Upload(Request) |
   //  |<------------------------------|
   //  |                               |
   //  | Upload(Response)              |
   //  |------------------------------>|
   //  |                               |
   //
   Tr069ParseUpload &upload = *httpResponse->parsed->body->upload;
   std::string cwmpId = httpResponse->parsed->header->cwmp_Id;
   std::string timeout = app.GetSoapTimeout();
   std::ostringstream txUploadResponse;
   TimeWrap now;
   txUploadResponse << "<soap-env:Envelope"
      << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";
   if(timeout.compare("") != 0)
   {
      txUploadResponse << 
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<< timeout <<"</cwmp:SessionTimeout>";
   }
   txUploadResponse << 
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:UploadResponse>"
      "<Status>1</Status>"
      "<StartTime>" << now.ToString() << "</StartTime>"
      "<CompleteTime>0001-01-01T00:00:00Z</CompleteTime>"
      "</cwmp:UploadResponse>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> postReq(new HttpPostRequest( txUploadResponse.str().c_str()) );
   m_fsmTransactionSession->HandleEvent(postReq);

   TRACE_PRINTF("Send (Upload)");

#if 0
   if( upload.fileType == "X 000FBB PM data" )
   {
      handleUploadPmDataRequest(upload);
   }
   else if( upload.fileType == "X 000FBB SW diagnostics" )
   {
      handleUploadSwDiagnosticsRequest(upload);
   }
#endif
   if( ( upload.fileType == "3 Vendor Configuration File" ) || (upload.fileType == "4 Vendor Log File" ) )
   {
      TRACE_PRINTF("uploading vendor log file");
      handleUploadPmDataRequest(upload);
   }
   else
   {
      TimeWrap now;
      string faultString = upload.fileType;
      faultString += " is not a valid download file type";

      PostTransferComplete(
            upload.commandKey,
            Tr069ParseFaultDetail::UploadFailure,
            faultString,
            now,
            now,
            cwmpId );
   }

   EXIT();
}

void Tr069Cwmp::HandleGetRpcMethods(shared_ptr<HttpPostResponse> httpResponse)
{
   ENTER
      ();

   Tr069Application &app = Tr069Application::GetInstance();

   string currentTime;
   app.GetFormattedCurrentTime(currentTime);

   //
   //  FAP                            CS
   //  |                               |
   //  |      GetRpcMethods  (Request) |
   //  |<------------------------------|
   //  |                               |
   //  | GetRpcMethods (Response)      |
   //  |------------------------------>|
   //  |                               |
   //
   std::string cwmpId = httpResponse->parsed->header->cwmp_Id;
   std::string timeout = app.GetSoapTimeout();
   std::ostringstream txGetRpcMethodsResponse;
   txGetRpcMethodsResponse << "<soap-env:Envelope"
      << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";

   if(timeout.compare("") != 0)
   {
      txGetRpcMethodsResponse << 
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<< timeout <<"</cwmp:SessionTimeout>";
   }
   txGetRpcMethodsResponse <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:GetRPCMethodsResponse>"
      "<MethodList soap-enc:arrayType=\"string[09]\">"
      "<string>GetRPCMethods</string>"
      "<string>SetParameterValues</string>"
      "<string>GetParameterValues</string>"
      "<string>GetParameterNames</string>"
      "<string>GetParameterAttributes</string>"
      "<string>SetParameterAttributes</string>"
      "<string>AddObject</string>"
      "<string>DeleteObject</string>"
      "<string>Reboot</string>"
      "<string>Download</string>"
      "<string>Upload</string>"
      "<string>FactoryReset</string>"
      "</MethodList>"
      "</cwmp:GetRPCMethodsResponse>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> postReq(new HttpPostRequest( txGetRpcMethodsResponse.str().c_str()) );
   m_fsmTransactionSession->HandleEvent(postReq);

   TRACE_PRINTF("Send (GetRPCMethodsResponse)");

   EXIT();
}

void Tr069Cwmp::HandleFactoryReset(shared_ptr<HttpPostResponse> httpResponse)
{
   ENTER();

   //
   //  FAP                            CS
   //  |                               |
   //  |         FactoryReset(Request) |
   //  |<------------------------------|
   //  |                               |
   //  | FactoryReset(Response)        |
   //  |------------------------------>|
   //  |                               |
   //

   std::string cwmpId = httpResponse->parsed->header->cwmp_Id;
   std::ostringstream txFactoryResetResponse;
   Tr069Application &app = Tr069Application::GetInstance();
   std::string timeout = app.GetSoapTimeout();
   txFactoryResetResponse << "<soap-env:Envelope"
      << tr069::tr069XmlNsHeaderPreamble << ">"
      "<soap-env:Header>"
      "<cwmp:ID soap-env:mustUnderstand=\"1\">"<< cwmpId <<"</cwmp:ID>";
   if(timeout.compare("") != 0)
   {
      txFactoryResetResponse <<
         "<cwmp:SessionTimeout soap-env:mustUnderstand=\"0\">"<< timeout <<"</cwmp:SessionTimeout>";
   }
   txFactoryResetResponse <<
      "</soap-env:Header>"
      "<soap-env:Body>"
      "<cwmp:FactoryResetResponse/>"
      "</soap-env:Body>"
      "</soap-env:Envelope>";

   shared_ptr<HttpPostRequest> postReq(new HttpPostRequest( txFactoryResetResponse.str().c_str()) );
   m_fsmTransactionSession->HandleEvent(postReq);

   OamActionReq oamActionReq(OAM_ACTION_FACTORY_RESET);
   app.SendMessage(oamActionReq, ENTITY_OAM, ENTITY_TR069);

   EXIT();

}

bool Tr069Cwmp::QueryInformResponse(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->informResponse;
}

bool Tr069Cwmp::QueryTransferCompleteResponse(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->transferCompleteResponse;
}

bool Tr069Cwmp::QueryReboot(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->reboot;
}

bool Tr069Cwmp::QuerySetParametersValueRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->setParameterValues;
}

bool Tr069Cwmp::QuerySetParametersAttributesRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->setParameterAttributes;
}

bool Tr069Cwmp::QueryGetParametersValueRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->getParameterValues;
}

bool Tr069Cwmp::QueryGetParameterNamesRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->getParameterNames;
}

bool Tr069Cwmp::QueryGetParameterAttributesRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->getParameterAttributes;
}

bool Tr069Cwmp::QueryDownloadRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->download;
}

bool Tr069Cwmp::QueryUploadRequest(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->upload;
}

bool Tr069Cwmp::QueryFactoryReset(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->factoryReset;
}

bool Tr069Cwmp::QueryAddObject(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->addObject;
}

bool Tr069Cwmp::QueryDeleteObject(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->deleteObject;
}

bool Tr069Cwmp::QueryGetRpcMethods(shared_ptr<HttpPostResponse> httpResponse)
{
   return
      httpResponse &&
      httpResponse->parsed &&
      httpResponse->parsed->body &&
      httpResponse->parsed->body->getRpcMethods;
}

void Tr069Cwmp::HandlePeriodicInformSubscriptionInd()
{
   bool periodicInformEnabled = false;

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_PERIODIC_INFORM_ENABLED, periodicInformEnabled);
   if (periodicInformEnabled)
   {
      u32 periodicInformInterval = 0;
      Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_PERIODIC_INFORM_INTERVAL, periodicInformInterval);
      if (!m_periodicInformTimer)
      {
         TRACE_PRINTF("CWMP: Periodic timer creation");
         m_periodicInformTimer = Tr069Application::GetInstance().CreateTimer("Periodic Inform Timer", TimerEngineInterface::SecondsToTicks(periodicInformInterval) );
      }
   }
   else
   {
      // If the timer is running stop the timer
      if (m_periodicInformTimer)
      {
         TRACE_PRINTF("CWMP: Periodic timer deletion");
         Tr069Application::GetInstance().DeleteTimer(m_periodicInformTimer);
         m_periodicInformTimer = NULL_TIMER;
      }
   }
}

void Tr069Cwmp::HandlePeriodicInformTimerExpiry(void *ignore)
{
   Tr069Application &app = Tr069Application::GetInstance();

   TRACE_PRINTF("CWMP: Periodic timer expiry handler");
   shared_ptr<Periodic> periodic(new Periodic());
   shared_ptr<TransactionSessionCommand> transactionSessionCommand(new TransactionSessionCommand(periodic));
   app.Enqueue(transactionSessionCommand);

   if (m_periodicInformTimer)
   {
      TRACE_PRINTF("CWMP: Periodic timer deletion");
      Tr069Application::GetInstance().DeleteTimer(m_periodicInformTimer);
      m_periodicInformTimer = NULL_TIMER;
   }

   u32 periodicInformInterval = 0;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_PERIODIC_INFORM_INTERVAL, periodicInformInterval);
   m_periodicInformTimer = Tr069Application::GetInstance().CreateTimer("Periodic Inform Timer", TimerEngineInterface::SecondsToTicks(periodicInformInterval) );
   return;
}

void Tr069Cwmp::HandleConnectionFailureTimerExpiry(void *ignore)
{
   m_connectionReattemptTimer = NULL_TIMER;
   if (m_fsmTransactionSession)
   {
      Tr069Application &app = Tr069Application::GetInstance();
      shared_ptr<Reconnect> reconnect(new Reconnect());
      shared_ptr<TransactionSessionCommand> transactionSessionCommand(new TransactionSessionCommand(reconnect));
      app.Enqueue(transactionSessionCommand);
      TRACE_PRINTF("CWMP: Connection Failure Timer Expiry Handler");
   }
   else
   {
      TRACE_PRINTF("CWMP: Connection Failure Timer Expiry Handler Failure - Could not find ongoing transaction session");
   }
   return;
}

}

