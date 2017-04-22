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
#include <arpa/inet.h>
#include <netdb.h>
#include <system/Trace.h>
#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/ike/IkeTunnelCreateReq.h>
#include <messaging/messages/ike/IkeTunnelCreateCnf.h>
#include <messaging/messages/ike/IkeTunnelConnectInd.h>
#include <messaging/messages/ike/IkeTunnelDeleteReq.h>
#include <messaging/messages/ike/IkeTunnelDeleteCnf.h>
#include <system/AlarmEvent.h>
#include <system/Url.h>
#include <platform/FapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace threeway;

#include "Tr069Application.h"
#include "Tr069SecGwConnection.h"
#include "Tr069Cwmp.h"

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

Tr069SecGwConnection::Tr069SecGwConnection( const char * name ) :
    m_tunnelId(0),
    m_stateGuardTimer(0),
    m_reconnectSecGateway(0),
    m_secGwBootEvent(false),
    m_fsm(*this, true, name)
{
}

Tr069SecGwConnection::~Tr069SecGwConnection()
{
}

bool Tr069SecGwConnection::NextValidServer()
{
   static const u32 MaxInvalidServers = 3;

   u32 servingSecGw = 0;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_SERVING_SECGW, servingSecGw );

   for(u32 i = 0; i < MaxInvalidServers; i++)
   {
      if(++servingSecGw >= 4)
      {
         servingSecGw = 1;
      }

      if(ServerConfigurationIsValid( servingSecGw ))
      {
         MibAttributeValues attrs;
         attrs.AddAttribute( PARAM_ID_SERVING_SECGW, servingSecGw);
         if (m_fsmHms)
         {
            attrs.AddAttribute( PARAM_ID_HMS_BOOTSTRAP_COMPLETED, 0U);
         }
         Tr069Application::GetInstance().GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);

         return true;
      }
   }

   return false;
}

bool Tr069SecGwConnection::ServerConfigurationIsValid( u32 secGw )
{
   switch(secGw)
   {
      case 1:
         {
            TRACE_PRINTF("Validate SecGw-1");
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_1, m_secGwAddress );
         }
         break;

      case 2:
         {
            TRACE_PRINTF("Validate SecGw-2");
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_2, m_secGwAddress );
         }
         break;

      case 3:
         {
            TRACE_PRINTF("Validate SecGw-3");
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_3, m_secGwAddress );
         }
         break;

      default:
         RSYS_ASSERT_PRINTF(false, "Invalid Server");
         break;
   }

   bool serverSelectedValid = !m_secGwAddress.IsNull();

   return serverSelectedValid;
}

void Tr069SecGwConnection::DisconnectedEntry()
{
}

void Tr069SecGwConnection::TerminateEntry()
{
   m_stateGuardTimer = Tr069Application::GetInstance().CreateTimer("Fsm:SecGw(State:Terminate)", TimerEngineInterface::MinutesToTicks( 20 ) );
}

void Tr069SecGwConnection::TerminateExit()
{
   Tr069Application::GetInstance().DeleteTimer( m_stateGuardTimer );
}

void Tr069SecGwConnection::ConnectionProcedureEntry()
{
   u32  timeoutMilliseconds = 16000;

   RSYS_ASSERT(m_stateGuardTimer == 0);

   m_stateGuardTimer = Tr069Application::GetInstance().CreateTimer("Fsm:SecGw(State:ConnectionProcedure)", TimerEngineInterface::MillisecondsToTicks( timeoutMilliseconds ) );
}

void Tr069SecGwConnection::ConnectionProcedureExit()
{
   Tr069Application::GetInstance().DeleteTimer( m_stateGuardTimer );

   m_stateGuardTimer = 0;
}

void Tr069SecGwConnection::CreatingIkeTunnelEntry()
{
   TRACE_PRINTF("%s:%d", __func__, __LINE__);

   bool IpsecEnabled = QueryMinimumNecessaryConfiguration();

   Tr069Application &app = Tr069Application::GetInstance();

   if (IpsecEnabled)
   {
      RSYS_ASSERT( !m_secGwAddress.IsNull() );

      TRACE_PRINTF("Create tunnel to SecGw (%s) requested...", m_secGwAddress.ToString().c_str() );

      string auth = Tr069Application::authMethod;
      TRACE_PRINTF("%s:%d Tr069Application::authMethod %s", __func__, __LINE__, auth.c_str());

      IkeTunnelCreateReq req(m_secGwAddress, Tr069Application::authMethod);

      app.SendMessage(req, ENTITY_TENPIN);
   }   
   else
   {   
      IkeTunnelCreateCnf cnf;
      app.SendMessage(cnf, ENTITY_TR069);
   }   
}

void Tr069SecGwConnection::ConnectingIkeTunnelEntry()
{
}

void Tr069SecGwConnection::DeletingIkeTunnelEntry()
{
   bool enableIPSec = QueryMinimumNecessaryConfiguration();

   Tr069Application &app = Tr069Application::GetInstance();
   IkeTunnelDeleteReq req(m_tunnelId);

   TRACE_PRINTF("Using IPsec, sending msg (%s) to IKE", req.ToString().c_str() );

   app.SendMessage(req, ENTITY_TENPIN);

   m_tunnelId = 0;

   if(enableIPSec == true)
   {
      MibAttributeValues attrs;
      attrs.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV4, "0.0.0.0" );
      attrs.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV6,"0:0:0:0:0:0:0:0");

      Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);
   }
}

void Tr069SecGwConnection::SendTransportCnf(shared_ptr<TransportReq> transportReq)
{
   shared_ptr<TransportCnf> transportCnf(new TransportCnf( true, transportReq->GetSrc()));
   Tr069Application::GetInstance().Enqueue(transportCnf);
}

void Tr069SecGwConnection::SendTransportRej(shared_ptr<TransportReq> transportReq)
{
   shared_ptr<TransportCnf> transportCnf(new TransportCnf( false, transportReq->GetSrc()));
   Tr069Application::GetInstance().Enqueue(transportCnf);
}

void Tr069SecGwConnection::ConnectedEntry()
{
   bool useForCwmp = false;
   m_reconnectSecGateway = 0;

   /* If the IPSec tunnel is not to be used for CWMP traffic, CWMP initialization is done elsewhere */
   Tr069Application & app = Tr069Application::GetInstance();
   app.GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_FAP_TUNNEL_USE_FOR_CWMP, useForCwmp);

   if (useForCwmp)
   {
      m_fsmHms  = shared_ptr<Tr069Cwmp>(new Tr069Cwmp(*this, (m_reconnectSecGateway != 0), m_secGwBootEvent));
      RSYS_ASSERT(m_fsmHms);

      shared_ptr<HmsModifyReq> hmsModifyReq(new HmsModifyReq() );
      m_fsmHms->HandleEvent(hmsModifyReq);
   }
}

void Tr069SecGwConnection::ConnectedExit()
{
   // HeMS CWMP FSM is available only when IPSec tunnel is used for CWMP traffic
   if (m_fsmHms)
   {
      m_fsmHms.reset();
   }
}

void Tr069SecGwConnection::CwmpDisableEntry()
{
   TRACE_PRINTF("%s:%d",__func__, __LINE__);

   // HeMS CWMP FSM is available only when IPSec tunnel is used for CWMP traffic
   if (m_fsmHms)
   {
      shared_ptr<Shutdown> shutdownHmsConnection(new Shutdown( Tr069QueueableEvent::CWMP_CONNECTION_FSM ) );
      m_fsmHms->HandleEvent(shutdownHmsConnection);
   }
   else
   {
      shared_ptr<LockedInd> lockedInd( new LockedInd( Tr069QueueableEvent::SECGW_CONNECTION_FSM) );
      Tr069Application::GetInstance().Enqueue(lockedInd);
   }
}

bool Tr069SecGwConnection::QuerySelectNextServer()
{
   m_reconnectSecGateway = 0;

   bool validServer = false;
   bool selectNextServerFromList = true;

   if(m_secGwModifyReq)
   {
      switch(m_secGwModifyReq->GetMode())
      {
         case SecGwModifyReq::Rewind:
            {
               if( ServerConfigurationIsValid( 1 ) )
               {
                  validServer = true;
                  selectNextServerFromList = false;
               }
            }
            break;

         case SecGwModifyReq::None:
            {
               validServer = false;
               selectNextServerFromList = false;
            }
            break;

         case SecGwModifyReq::Next:
            {
               selectNextServerFromList = true;
            }
            break;

         default:
            RSYS_ASSERT_FAIL("SecGwModifyReq::Mode %u not recognised.", m_secGwModifyReq->GetMode());
            break;
      }

      m_secGwModifyReq.reset();
   }

   if(selectNextServerFromList)
   {
      validServer = NextValidServer();
   }

   return validServer;
}

bool Tr069SecGwConnection::QueryReconnectServer()
{
   TRACE_PRINTF("%s:%d",__func__, __LINE__);

   u32 secGwReconnectEnabled = 0;

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_TR069_RECONNECT_SECGW_ENABLE, secGwReconnectEnabled );
   bool reconnectGw = (m_reconnectSecGateway == 1);
   m_reconnectSecGateway++;
   return ( (secGwReconnectEnabled != 0) && (reconnectGw));
}

void Tr069SecGwConnection::PerformInitialisation()
{
   u32 servingSecGw;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_SERVING_SECGW, servingSecGw );

   if( !ServerConfigurationIsValid( servingSecGw ) )
   {
      bool selectFirstServerWithValidConnectConfig = NextValidServer();

      RSYS_ASSERT( selectFirstServerWithValidConnectConfig );
   }
}


void Tr069SecGwConnection::SystemReboot(void*)
{
   TRACE_PRINTF("%s:%d", __func__, __LINE__);

   if ( system("/bin/reboot") != oam_ret_zero )
   {
      TRACE_MSG("Tr069SecGwConnection::SystemReboot, SystemReboot Failed");
   }
}


void Tr069SecGwConnection::RaiseIpsecTunnelFailureAlarm(shared_ptr<threeway::Queueable> event)
{
   //Here it is assumed that Ipsec Tunnel Delete Indication comes only when ipsec 
   //tunnel goes down on its own.
   m_reconnectSecGateway = 1;
   if(m_fsmHms)
   {
      m_secGwBootEvent = m_fsmHms->GetBootEvent();
   }

   shared_ptr<AlarmId> alarmId(new FapAlarmId(FapAlarmId::IPSEC_TUNNEL_FAILURE));
   AlarmEvent alarmEvent(alarmId,
         AlarmEvent::ALARM_EVENT_TRANSIENT,
         AlarmEvent::ALARM_SEVERITY_CRITICAL,
         "IPsec tunnel failed.",
         AlarmEvent::ALARM_TYPE_COMMUNICATIONS);

   Tr069Application::GetInstance().SendMessage(alarmEvent, ENTITY_OAM);
}

// Guard conditions
void Tr069SecGwConnection::StoreTunnelId( shared_ptr<Queueable> event)
{
   shared_ptr<MessageSerialisedData> message = dynamic_pointer_cast<MessageSerialisedData>(event);

   RSYS_ASSERT(message);

   shared_ptr<IkeTunnelCreateCnf> cnf = Serialisable::DeSerialise<IkeTunnelCreateCnf>(message);

   RSYS_ASSERT(cnf);

   m_tunnelId = cnf->GetId();

   TRACE_PRINTF("TunnelId:%"PRIu32, m_tunnelId)
}

void Tr069SecGwConnection::HandleTunnelEstablishment(shared_ptr<threeway::Queueable>)
{
   string fgwIp("");
   bool useForCwmp = false;
   Tr069Application & app = Tr069Application::GetInstance();

   app.GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_FAP_TUNNEL_USE_FOR_CWMP, useForCwmp);

   if (useForCwmp)
   {
      app.GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_ENB_IP_ADDR_IPV4, fgwIp);
      string connectionRequestUrl = "http://";
      connectionRequestUrl += fgwIp;
      connectionRequestUrl += ":7547";
      connectionRequestUrl += app.GetFapUrlAbsolutePath();

      MibAttributeValues attrs;
      attrs.AddAttribute(PARAM_ID_TR069_CONNECTION_REQUEST_URL, connectionRequestUrl);
      app.GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);
   }
}

void Tr069SecGwConnection::HandleTunnelEstablishment(shared_ptr<IkeTunnelConnectInd> ikeTunnelConnectInd)
{
   Tr069Application & app = Tr069Application::GetInstance();
   bool useForCwmp = false;
   app.GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_FAP_TUNNEL_USE_FOR_CWMP, useForCwmp);

   MibAttributeValues fapAddrAttr;
   TRACE_PRINTF("Setting FAP address to [%s]", ikeTunnelConnectInd->GetTunnelAddr().Get());
   if(ikeTunnelConnectInd->GetTunnelAddr().CheckIfIPv6())
   { 
      fapAddrAttr.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV6 , ikeTunnelConnectInd->GetTunnelAddr().Get());
      
      MibAttributeValues ipv6MioAttr;
      ipv6MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV6_ADDRESS,ikeTunnelConnectInd->GetTunnelAddr().Get());
      ipv6MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV6_ENABLE,(u32)true);
      MibDN ipInterfaceDn =MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
      MibDN::GenerateMibDN(ipInterfaceDn,MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS,0);
      app.GetMibCache().SetMibAttributes(ipInterfaceDn,ipv6MioAttr,ENTITY_OAM);
   }
   else
   {
      fapAddrAttr.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV4, ikeTunnelConnectInd->GetTunnelAddr().Get());

      MibAttributeValues ipv4MioAttr;
      ipv4MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS,ikeTunnelConnectInd->GetTunnelAddr().Get());
      ipv4MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS_ENABLED,(u32)true);
      MibDN ipInterfaceDn =MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
      ipInterfaceDn = MibDN::GenerateMibDN(ipInterfaceDn,MIB_OBJECT_CLASS_IP_INTERFACE_IPV4_ADDRESS,0);
      app.GetMibCache().SetMibAttributes(ipInterfaceDn,ipv4MioAttr,ENTITY_OAM);

   }
   app.GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), fapAddrAttr, ENTITY_TR069);

   if (useForCwmp)
   {
      string connectionRequestUrl = "http://";
      connectionRequestUrl += ikeTunnelConnectInd->GetTunnelAddr().Get();
      connectionRequestUrl += ":7547";
      connectionRequestUrl += app.GetFapUrlAbsolutePath();
   }
}


void Tr069SecGwConnection::SaveSecGwModify( shared_ptr<SecGwModifyReq> secGwModifyReq)
{
   RSYS_ASSERT(secGwModifyReq);

   m_secGwModifyReq = secGwModifyReq;
}

bool Tr069SecGwConnection::QueryMinimumNecessaryConfiguration()
{
   TRACE_PRINTF("%s:%d", __func__, __LINE__);

   bool minimumNecessaryConfiguration = true;
   Fqdn server[3];

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_1, server[0] );
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_2, server[1] );
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_3, server[2] );

   if(    server[0].IsNull()
         && server[1].IsNull()
         && server[2].IsNull() )
   {
      /*
         TRACE_PRINTF(("Manual config required? - auto reboot in 20 mins"))

         std::cerr <<
         "*************************************************\n"
         "******  TR069: SecGW config required.   *********\n"
         "******         else reboot shortly.     *********\n"
         "******         'killall tr069' to stop  *********\n"
         "*************************************************" << endl;
         */

      minimumNecessaryConfiguration = false;
   }

   return minimumNecessaryConfiguration;
}

bool Tr069SecGwConnection::QueryTunnelIdKnown()
{
   bool tunnelIdKnown = (m_tunnelId != 0);

   return tunnelIdKnown;
}

bool Tr069SecGwConnection::QueryFapRebootInProgress( )
{
   return Tr069Reboot::GetInstance().QueryFapAboutToReboot();
}


bool Tr069SecGwConnection::QueryTunnelIdIsAsExpected( shared_ptr<IkeTunnelConnectInd> ind)
{ 
   bool IpsecEnabled = QueryMinimumNecessaryConfiguration();

   if (IpsecEnabled)
   {
      return true;
   }
   else
   {
      return (m_tunnelId == ind->GetId());
   }
}

bool Tr069SecGwConnection::QueryIpSecIsEnabled(shared_ptr<threeway::Queueable> event)
{
   bool IpsecEnabled = QueryMinimumNecessaryConfiguration();

   return IpsecEnabled;
}

void Tr069SecGwConnection::HandleEvent( shared_ptr<Queueable> event)
{
   RSYS_ASSERT(event);

   switch(event->GetDomain())
   {
      case Queueable::OTHER:
         {
            shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(event);

            if (tr069Event)
            {
               if( tr069Event->GetDst() == Tr069QueueableEvent::SECGW_CONNECTION_FSM)
               {
                  switch(tr069Event->GetId())
                  {
                     case Tr069QueueableEvent::TRANSPORT_REQ:
                        {
                           shared_ptr<TransportReq> transportReq = dynamic_pointer_cast<TransportReq>(event);
                           RSYS_ASSERT(transportReq);
                           m_fsm.InjectTransportReq(transportReq);
                        }
                        break;

                     case Tr069QueueableEvent::SECGW_MODIFY_REQ:
                        {
                           shared_ptr<SecGwModifyReq> secGwModifyReq = dynamic_pointer_cast<SecGwModifyReq>(event);
                           m_fsm.InjectSecGwModify( secGwModifyReq );
                        }
                        break;

                     case Tr069QueueableEvent::LOCKED_IND:
                        {
                           shared_ptr<LockedInd> lockedInd = dynamic_pointer_cast<LockedInd>(event);
                           m_fsm.InjectCwmpLockedInd( lockedInd );
                        }
                        break;

                     default:
                        RSYS_ASSERT_PRINTF(false,"Unhandled SECGW_CONNECTION_FSM event %s.", tr069Event->ToString());
                        break;
                  }
               }
               else
               {
                  if(m_fsmHms)
                  {
                     m_fsmHms->HandleEvent(event);
                  }
                  else
                  {
                     TRACE_PRINTF("Unhandled event %s.", tr069Event->ToString());
                  }
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
                  case SERIALISATION_ID_IKE_TUNNEL_DISCONNECT_IND:
                     m_fsm.InjectIkeTunnelDisconnectionInd( event );
                     break;

                  case SERIALISATION_ID_IKE_TUNNEL_CONNECT_IND:
                     {
                        shared_ptr<IkeTunnelConnectInd> ind = Serialisable::DeSerialise<IkeTunnelConnectInd>(message);
                        m_fsm.InjectIkeTunnelConnectionInd( ind );
                     }
                     break;

                  case SERIALISATION_ID_IKE_TUNNEL_CREATE_CNF:
                     m_fsm.InjectIkeTunnelCreateCnf( event );
                     break;

                  case SERIALISATION_ID_IKE_TUNNEL_DELETE_CNF:
                     m_fsm.InjectIkeTunnelDeleteCnf( event );
                     break;

                  default:
                     {
                        if(m_fsmHms)
                        {
                           m_fsmHms->HandleEvent(event);
                        }
                     }
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

bool Tr069SecGwConnection::HandleTimerExpiry(threeway::TimerHandle expiredTimer)
{
   bool timerHandled = false;

   if(expiredTimer)
   {
      if( expiredTimer == m_stateGuardTimer )
      {
         m_fsm.InjectStateGuardTimerExpiry( NULL );
         timerHandled = true;
      }
      else
      {
         if(m_fsmHms)
         {
            timerHandled = m_fsmHms->HandleTimerExpiry(expiredTimer);
         }
      }
   }

   return timerHandled;
}

}

