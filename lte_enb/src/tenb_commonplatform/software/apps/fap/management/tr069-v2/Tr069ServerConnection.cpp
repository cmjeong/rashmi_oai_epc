///////////////////////////////////////////////////////////////////////////////
//
// Tr069ServerConnection.cpp
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
#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/ike/IkeTunnelCreateReq.h>
#include <messaging/messages/ike/IkeTunnelCreateCnf.h>
#include <messaging/messages/ike/IkeTunnelConnectInd.h>
#include <messaging/messages/ike/IkeTunnelDeleteReq.h>
#include <messaging/messages/ike/IkeTunnelDeleteCnf.h>
#include <messages/Tr069AutoTransfer.h>
#include <system/AlarmEvent.h>
#include <platform/FapAlarmId.h>
#include <netdb.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069ServerConnection.h"
#include "Tr069Application.h"
#include "Tr069Parameters.h"
#include "Tr069SecGwConnection.h"
#include "Tr069SecGwNsn.h"
#include "Tr069UdpServer.h"
#include "Tr069Cwmp.h"

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

Tr069ServerConnection* Tr069ServerConnection::s_instance = NULL;
bool CheckIfFqdnIsIpv6(const char*);

Tr069ServerConnection& Tr069ServerConnection::GetInstance()
{
   ENTER ();

   if (s_instance == NULL)
   {
      s_instance = new Tr069ServerConnection();

      RSYS_ASSERT(s_instance);
   }

   RETURN (*s_instance);
}

Tr069ServerConnection::Tr069ServerConnection()
{
}

Tr069ServerConnection::~Tr069ServerConnection()
{
}

void Tr069ServerConnection::UpdatedSecGwUrl(MibAttributeId mibAttributeId)
{
   bool selectFirstSecGw = false;

   if( Tr069Application::GetInstance().GetMibCache().IsMibAttributePresent(PARAM_ID_SERVING_SECGW) )
   {
      u32 secGwNum;
      Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_SERVING_SECGW, secGwNum );

      switch(mibAttributeId)
      {
         case PARAM_ID_LTE_SEC_GW_SERVER_1: selectFirstSecGw = (secGwNum == 1); break;
         case PARAM_ID_LTE_SEC_GW_SERVER_2: selectFirstSecGw = (secGwNum == 2); break;
         case PARAM_ID_LTE_SEC_GW_SERVER_3: selectFirstSecGw = (secGwNum == 3); break;
         default:
                                            break;
      }
   }
   else
   {
      selectFirstSecGw = true;
   }

   if( selectFirstSecGw )
   {
      shared_ptr<SecGwModifyReq> secGwModifyReq( new SecGwModifyReq( SecGwModifyReq::Rewind) );
      Tr069Application::GetInstance().Enqueue(secGwModifyReq);
   }
}

bool Tr069ServerConnection::QueryMinimumNecessaryConfiguration()
{
   bool minimumNecessaryConfiguration = true;
   bool adminState = true;
   Fqdn server[3];

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_1, server[0] );
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_2, server[1] );
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_SEC_GW_SERVER_3, server[2] );
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_LTE_FAP_ADMIN_STATE, adminState);

   if(true == adminState)
   {
      if(server[0].IsNull() && server[1].IsNull() && server[2].IsNull())
      {
         minimumNecessaryConfiguration = false;
      }
      else
      {
          for(int selected=0;selected<3;selected++)
          {
            if(!server[selected].IsNull())
            {
               if(CheckIfFqdnIsIpv6(server[selected].ToString().c_str()))
               {
                  string ip6addr;      
                  Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_ENB_IP_ADDR_IPV6,ip6addr);
                  if(!strcmp(ip6addr.c_str(),"0:0:0:0:0:0:0:0"))
                  {
                      TRACE_PRINTF("IPV6 IS DISABLED");
                  }
                  else
                  {
                     return minimumNecessaryConfiguration;
                  }
               }
               else
               { 
                 return minimumNecessaryConfiguration; 
               }
            }
         }
            minimumNecessaryConfiguration = false;
      }
   }
   else
   {
      minimumNecessaryConfiguration = false;
   }

   return minimumNecessaryConfiguration;
}

bool CheckIfFqdnIsIpv6(const char *hostname)
{
    if (hostname)
    {
        struct hostent * resolved = gethostbyname2(hostname,AF_INET6);
        if (resolved)
        {
            return true;            
        }
    }
    return false;
}
void Tr069ServerConnection::HandleSecGwSubsciptionInd(void)
{
   TRACE_PRINTF("%s:%d",__func__, __LINE__);

   // Bring up SecGW connection if already configured
   if (QueryMinimumNecessaryConfiguration())
   {
      if (m_fsmSecGw == NULL)
      {
         TRACE_PRINTF("ServerConnection StartFsm: SecGW FSM started");
         m_fsmSecGw = shared_ptr<Tr069SecGwConnection>(new Tr069SecGwConnection);
         m_fsmSecGw->StartFsm();

         // If we are bringing up SecGw FSM, we should bring down our IP address if
         // it is set to FAP eth0 address so that stack is brought down till the tunnel
         // comes up
         MibAttributeValues attrs;
         attrs.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV4, "0.0.0.0");
         Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);
      }
      else
      {
         // TODO: Handle the change to configuration server
      }
   }
}

void Tr069ServerConnection::HandleAdminStateChange(void)
{
}

void Tr069ServerConnection::StartFsm(void)
{
   TRACE_PRINTF("%s:%d",__func__, __LINE__);

   bool useForCwmp = false;

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_FAP_TUNNEL_USE_FOR_CWMP, useForCwmp);

   // Bring up SecGW connection if already configured
   if (QueryMinimumNecessaryConfiguration())
   {
      TRACE_PRINTF("ServerConnection StartFsm: SecGW FSM started");
      m_fsmSecGw = shared_ptr<Tr069SecGwConnection>(new Tr069SecGwConnection);
      m_fsmSecGw->StartFsm();
   }
   else
   {
      // SecGW is not configured. Set the unit IP address as the FAP IP address.
      // Stack will be brought up with default interface address.
      IPv4Address eth0;
      Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_UNIT_IP_ADDRESS, eth0);
      TRACE_PRINTF("TR069 and IPsec are off, setting FGW0 addr to %s.", eth0.ToString());

      MibAttributeValues attrs;
      attrs.AddAttribute(PARAM_ID_ENB_IP_ADDR_IPV4, eth0.ToString());
      Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);

      MibAttributeValues ipv4MioAttr;
      ipv4MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS,eth0.ToString());
      ipv4MioAttr.AddAttribute(PARAM_ID_IP_INTERFACE_IPV4_ADDRESS_ENABLED,(u32)true);
      MibDN ipInterfaceDn =MibDN::GenerateMibDN(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
      ipInterfaceDn = MibDN::GenerateMibDN(ipInterfaceDn,MIB_OBJECT_CLASS_IP_INTERFACE_IPV4_ADDRESS,0);
      Tr069Application::GetInstance().GetMibCache().SetMibAttributes(ipInterfaceDn,ipv4MioAttr,ENTITY_OAM);

   }

   if (!useForCwmp)
   {
      MibAttributeValues attrs;
      IPv4Address fapAddr;
      Tr069Application & app = Tr069Application::GetInstance();

      Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_UNIT_IP_ADDRESS, fapAddr);

      string connectionRequestUrl ;

      connectionRequestUrl += "http://";
      connectionRequestUrl += fapAddr.ToString();
      connectionRequestUrl += ":7547";
      connectionRequestUrl += app.GetFapUrlAbsolutePath();
      attrs.AddAttribute(PARAM_ID_TR069_CONNECTION_REQUEST_URL, connectionRequestUrl);

      app.GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);
   }
   else if (!QueryMinimumNecessaryConfiguration())
   {
      TRACE_PRINTF("%s Security Gateway address is not configured hence proceeding without IPSec even though useTunnel for Device.FAP.Tunnel.UseForCWMP is Enabled ",__FUNCTION__);
   }

   // If useForCwmp is set, the CWMP object is handled by SecGW implementation
   if (!useForCwmp)
   {
      InitializeCwmp();
   }

   IPv4Address fgwIp;
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_ENB_IP_ADDR_IPV4, fgwIp);
   Tr069SocketServer & startSocketServer = Tr069SocketServer::GetInstance(fgwIp);
   RSYS_ASSERT(&startSocketServer);
   startSocketServer.StartThread();
   Tr069UdpServer & startUdpServer = Tr069UdpServer::GetInstance(fgwIp);
   RSYS_ASSERT(&startUdpServer);
   startUdpServer.StartThread();

}

void Tr069ServerConnection::InitializeCwmp()
{
   TRACE_PRINTF("%s",__func__);

   bool performLteRemScanBeforeBoot = false;
   bool performWcdmaRemScanBeforeBoot = false;
   string lteRemScanStatus;
   string wcdmaScanStatus;
   bool initializeCwmp = FALSE;

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE), PARAM_ID_LTE_REM_SCAN_ON_BOOT, performLteRemScanBeforeBoot );
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA), PARAM_ID_WCDMA_REM_SCAN_ON_BOOT, performWcdmaRemScanBeforeBoot );
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_LTE), PARAM_ID_LTE_REM_SCAN_STATUS, lteRemScanStatus);
   Tr069Application::GetInstance().GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA), PARAM_ID_WCDMA_REM_SCAN_STATUS, wcdmaScanStatus);

   if(!performLteRemScanBeforeBoot && !performWcdmaRemScanBeforeBoot)
   {
      initializeCwmp = TRUE;
   }
   else
   {
      if((strcmp(lteRemScanStatus.c_str(),REM_STATUS_IN_PROGRESS)) && (strcmp(wcdmaScanStatus.c_str(),REM_STATUS_IN_PROGRESS)))
      {
         initializeCwmp = TRUE;
      }
   }

   if(TRUE == initializeCwmp)
   {
      TRACE_PRINTF("ServerConnection StartFsm: CWMP outside tunnel. Bring up CWMP");

      m_fsmHms  = shared_ptr<Tr069Cwmp>(new Tr069Cwmp(*this, false, false, false));
      RSYS_ASSERT(m_fsmHms);

      shared_ptr<HmsModifyReq> hmsModifyReq(new HmsModifyReq() );
      m_fsmHms->HandleEvent(hmsModifyReq);
      InitialisePeriodicInform();
   }
}

void Tr069ServerConnection::HandleEvent( shared_ptr<Queueable> event)
{
   RSYS_ASSERT(event);

   switch(event->GetDomain())
   {
      case Queueable::OTHER:
         {
            shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(event);

            if (tr069Event)
            {
               if(Tr069QueueableEvent::TRANSPORT_REQ == tr069Event->GetId())
               {
                  shared_ptr<TransportCnf> transportCnf(new TransportCnf( true, tr069Event->GetSrc()));
                  Tr069Application::GetInstance().Enqueue(transportCnf);
               }

               if( tr069Event->GetDst() == Tr069QueueableEvent::SECGW_CONNECTION_FSM)
               {
                  if (m_fsmSecGw)
                  {
                     m_fsmSecGw->HandleEvent(event);
                  }
               }
               else
               {
                  TRACE_PRINTF("Processing a CWMP event");
                  if (m_fsmHms)
                  {
                     m_fsmHms->HandleEvent(event);
                  }
                  else if (m_fsmSecGw)
                  {
                     m_fsmSecGw->HandleEvent(event);
                  }
               }
            }
            else
            {
               TRACE_PRINTF("ServerConnection: Not a TR069 Event!!");
            }
            break;
         }
      case Queueable::MESSAGE_SERIALISED_DATA:
         {
            shared_ptr<MessageSerialisedData> message = dynamic_pointer_cast<MessageSerialisedData>(event);
            if (message)
            {
               switch (message->GetSerialisationId())
               {
                  case SERIALISATION_ID_IKE_TUNNEL_DISCONNECT_IND:
                  case SERIALISATION_ID_IKE_TUNNEL_CONNECT_IND:
                  case SERIALISATION_ID_IKE_TUNNEL_CREATE_CNF:
                  case SERIALISATION_ID_IKE_TUNNEL_DELETE_CNF:
                     if (m_fsmSecGw)
                     {
                        m_fsmSecGw->HandleEvent(event);
                     }
                     break;
                  default:
                     {
                        if(m_fsmHms)
                        {
                           m_fsmHms->HandleEvent(event);
                        }
                     }
               }
            }
            break;
         }
      case Queueable::TIMER_EXPIRY:
         {
            shared_ptr<TimerExpiry> timer = dynamic_pointer_cast<TimerExpiry>(event);
            if (timer)
            {
               TRACE_PRINTF("ServerConnection: Unhandled timer event (%d) and handle (%d)", timer->GetDomain(), timer->GetTimerHandle());
            }
            break;
         }
      default:
         {
            TRACE_PRINTF("ServerConnection: Unhandled event for domain (%d)", event->GetDomain());
         }
   }
}

bool Tr069ServerConnection::HandleTimerExpiry(threeway::TimerHandle expiredTimer)
{

   bool timerHandled = false;

   if (m_fsmHms)
   {
      timerHandled = m_fsmHms->HandleTimerExpiry(expiredTimer);
   }
   if ((!timerHandled) && (m_fsmSecGw))
   {
      timerHandled = m_fsmSecGw->HandleTimerExpiry(expiredTimer);
   }

   return timerHandled;
}

void Tr069ServerConnection::HandlePeriodicInformSubscriptionInd()
{
   // First will handle the case where CWMP is not using the IPSec tunnel
   // TODO - Support the case where CWMP is using the IPSec tunnel
   if (m_fsmHms)
   {
      TRACE_PRINTF("ServerConnection: Injecting periodic subscription change to CWMP");
      shared_ptr<PeriodicInformUpdate> periodicInformUpdate(new PeriodicInformUpdate() );
      m_fsmHms->HandleEvent(periodicInformUpdate);
   }
   else
   {
   }
}

void Tr069ServerConnection::HandleAutoTransferCompReq(string uploadFileName,
      string startTime, string completeTime, bool isUploadSuccess)
{
   TRACE_PRINTF("ServerConnection: Injecting periodic Log upload to CWMP");
   shared_ptr<AutoTransfer> autoTransfer(new AutoTransfer(uploadFileName,startTime,completeTime,isUploadSuccess));
   TRACE_PRINTF("%d ServerConnection: Injecting periodic Log upload to CWMP", __LINE__);
      TRACE_PRINTF("After getting timer value");
   m_fsmHms->HandleEvent(autoTransfer);

}

void Tr069ServerConnection::HandleConnectionRequestParameterUpdate()
{
}

void Tr069ServerConnection::InitialisePeriodicInform()
{
   TRACE_PRINTF("%s",__FUNCTION__);

   u32 periodicInformEnable;

   Tr069Application::GetInstance().GetMibCache().GetMibAttribute(PARAM_ID_PERIODIC_INFORM_ENABLED,periodicInformEnable);
   if(periodicInformEnable)
   {
      Tr069ServerConnection::GetInstance().HandlePeriodicInformSubscriptionInd();
   }
}
}
