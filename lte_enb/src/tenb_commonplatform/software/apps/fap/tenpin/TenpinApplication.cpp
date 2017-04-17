///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <arpa/inet.h>
#include <signal.h>
#include <system/Exception.h>
#include <system/Trace.h>
#include <system/SerialisationIds.h>
#include <system/WatchDogDereg.h>
#include <mib-common/MibAttributeValues.h>
#include <mib-common/MibAttributeValuesByDn.h>
#include <mib-common/MibAttributeIdsByDn.h>
#include <MibAttributeId.h>
#include <mib-common/messages/MibSetAttributesReq.h>
#include <mib-common/messages/MibSubscribeAttributesReq.h>
#include <mib-common/messages/MibSubscribeAttributesCnf.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <messaging/transport/CliHandler.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <messaging/messages/tenpin/TenpinFirewallOpenReq.h>
#include <messaging/messages/tenpin/TenpinFirewallOpenCnf.h>
#include <messaging/messages/tenpin/TenpinFirewallCloseReq.h>
#include <messaging/messages/tenpin/TenpinFirewallCloseCnf.h>
#include <messaging/messages/tenpin/TenpinSignatureVerifyReq.h>
#include <messaging/messages/tenpin/TenpinSignatureVerifyCnf.h>
#include <messaging/messages/tenpin/TenpinDnsServerAddReq.h>
#include <messaging/messages/tenpin/TenpinDnsServerAddCnf.h>
#include <messaging/messages/ike/IkeTunnelCreateReq.h>
#include <messaging/messages/ike/IkeTunnelCreateCnf.h>
#include <messaging/messages/ike/IkeTunnelDeleteReq.h>
#include <messaging/messages/ike/IkeTunnelDeleteCnf.h>
#include <messaging/messages/ike/IkeTunnelConnectInd.h>
#include <messaging/messages/ike/IkeTunnelDisconnectInd.h>
#include <messaging/messages/ike/HwCryptoAvailableInd.h>
#include <messaging/messages/common/UploadLogReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinStack.h"
#include "TenpinHardware.h"
#include "TenpinX509.h"
#include "TenpinApplication.h"

using namespace threeway;
using namespace boost;

bool TenpinApplication::isWatchdogDereg =false;
   /* ADDING CHANGES FOR PSK */
char argv1[20];
u32 timervalue = 0;
#define MAX_CRYPTO_PROFILE 2
#define LOG_UPLOAD_SUBSCRIPTION_ID 5
///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<TenpinApplication> TenpinApplication::s_instance;

DeclareAppVersionStamp

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

TenpinApplication::TenpinApplication() :
    ApplicationWithMessaging("tenpin"),
    m_guardTimer(0),
    m_ikeGraceTimer(0),
    m_fapId(""),
    m_tunnelDb(),
    m_configuration(),
    m_fsm(*this, true) /* initial state entry must not depend upon this constructor body ... */
{
   ENTER();

   TenpinStack& stack = TenpinStack::GetInstance();

   m_firewall = stack.GetFirewall();
   m_dns      = stack.GetDns();
   m_ike      = stack.GetIke();
   m_hwCrypto = stack.GetHwCrypto();

   TenpinHardware& hardware = TenpinHardware::GetInstance();
   m_tpm = hardware.GetTpm();

   RegisterMessageHandler(this, "tenpin");

   TenpinX509& x509 = TenpinX509::GetInstance();

   m_x509 = x509.GetX509();

   EXIT();
}

TenpinApplication& TenpinApplication::GetInstance()
{
   if (NULL == s_instance)
   {
      s_instance.reset(new TenpinApplication());
   }

   return (*s_instance);
}

void TenpinSignalSigtermHandler(int sig)
{
   TenpinApplication::isWatchdogDereg = true;
   DeregisterWithWatchDog(ENTITY_TENPIN, ENTITY_WATCHDOG);
   exit(0);
}

u32 TenpinApplication::ThreadProcedure()
{
   signal(SIGTERM,TenpinSignalSigtermHandler);
   StartTimerEngine();
   StartMessaging();

   RegisterEntity(ENTITY_TENPIN);
   RegisterEntity(ENTITY_IKE);
   RegisterEntity(ENTITY_IPSEC_TUNNEL_DB);
   RegisterEntity(ENTITY_TPM);
   RegisterEntity(ENTITY_X509);

   // Register our PID with the watchdog. 
   TenpinApplication::isWatchdogDereg =false;
   WatchdogRegisterPid();
   m_watchdogKickTimer = CreateTimer ("Tr069WatchdogKick", 5000, TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_REPEAT);
   WatchdogKick(getpid(),5,15);  

   m_guardTimer    = CreateTimer("guardTimer",    2000, TimerEngineInterface::TIMER_WAIT, TimerEngineInterface::TIMER_SINGLE_SHOT_WITHOUT_DELETE);
   /* tests shows that charon takes ~500 ms to start, so 1500 ms gives plenty of time */
   m_ikeGraceTimer = CreateTimer("ikeGraceTimer", 1500, TimerEngineInterface::TIMER_WAIT, TimerEngineInterface::TIMER_SINGLE_SHOT_WITHOUT_DELETE);

   TenpinStack& stack = TenpinStack::GetInstance();

   if (!stack.Init())
   {
      RSYS_ASSERT_PRINTF(0, "Failed to initialise stack!");
      return 1;
   }

   m_fsm.InjectGo(NULL);

   while (1)
   {
      shared_ptr<Queueable> event = ReceiveEvent(5000);
      DispatchEvent(event);
   }

   m_fsm.InjectStop(NULL);

   StopTimerEngine();

   return 0;
}

void TenpinApplication::TunnelTeardownAndReconfigure(
      u32 id
      )
{
   m_ike->Teardown(m_tunnelDb, id);
   m_tunnelDb.DeProvision(id);
   m_ike->Reconfigure(m_tunnelDb, m_fapId);
}

bool TenpinApplication::MessageHandler(
      shared_ptr<threeway::MessageSerialisedData> &message
      )
{
   // First, pass to parent
   bool handled = ApplicationWithMessaging::MessageHandler(message);

   TRACE_PRINTF("RX %d:%s\n", message->GetSerialisationId(), message->ToString().c_str());

   if (ENTITY_TENPIN != message->GetToEntity()) { return false; }

   handled = true;

   switch (message->GetSerialisationId())
   {
      case SERIALISATION_ID_REQUEST_START_RSP:            m_fsm.InjectOamStart(NULL);                     break;
      case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_CNF: /* ignore */                                    break;
      case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND: m_fsm.InjectMibSubscribeAttributesInd(message); break;
      case SERIALISATION_ID_TENPIN_FIREWALL_OPEN_REQ:     m_fsm.InjectFirewallOpenReq(message);           break;
      case SERIALISATION_ID_TENPIN_FIREWALL_OPEN_CNF:     m_fsm.InjectFirewallOpenCnf(message);           break;
      case SERIALISATION_ID_TENPIN_FIREWALL_CLOSE_REQ:    m_fsm.InjectFirewallCloseReq(message);          break;
      case SERIALISATION_ID_TENPIN_FIREWALL_CLOSE_CNF:    m_fsm.InjectFirewallCloseCnf(message);          break;
      case SERIALISATION_ID_TENPIN_SIGNATURE_VERIFY_REQ:  m_fsm.InjectSignatureVerifyReq(message);        break;
      case SERIALISATION_ID_TENPIN_DNS_SERVER_ADD_REQ:    m_fsm.InjectDnsServerAddReq(message);           break;
      case SERIALISATION_ID_IKE_TUNNEL_CREATE_REQ:        m_fsm.InjectIkeTunnelCreateReq(message);        break;
      case SERIALISATION_ID_IKE_TUNNEL_DELETE_REQ:        m_fsm.InjectIkeTunnelDeleteReq(message);        break;
      case SERIALISATION_ID_IKE_TUNNEL_CONNECT_IND:       m_fsm.InjectIkeTunnelConnectInd(message);       break;
      case SERIALISATION_ID_IKE_TUNNEL_DISCONNECT_IND:    m_fsm.InjectIkeTunnelDisconnectInd(message);    break;
      case SERIALISATION_ID_HW_CRYPTO_AVAILABLE_IND:      m_fsm.InjectHwCryptoAvailableInd(message);      break;
      default:                                            /* ignore */                                    break;
   }

   return handled;
}

void TenpinApplication::HandleTimerExpiry(
      shared_ptr<TimerExpiry> timer
      )
{
   TRACE_PRINTF("%s:%d \n", __func__, __LINE__);

   TimerHandle expired = timer->GetTimerHandle();

   if (expired == m_guardTimer)
   {
      m_fsm.InjectExpiryGuardTimer(NULL);
   }
   else if (expired == m_ikeGraceTimer)
   {
      m_fsm.InjectExpiryIkeGraceTimer(NULL);
   }
   else if ( expired == m_watchdogKickTimer )
   {
      if(TenpinApplication::isWatchdogDereg == false)
      {
         WatchdogKick (getpid(),5,15);
      }
   } 
   else if(timer->GetTimerHandle() == logTimerHandle)
   {
      string logFileName[3];
      int numClosedFiles = Trace::GetInstance().GetLogFilesToUpload(logFileName);
      for(int n_uploadfile = 0;n_uploadfile < numClosedFiles;n_uploadfile++)
      {
         UploadLogReq upLogReq(logFileName[n_uploadfile]);
         SendMessage(upLogReq,ENTITY_FTP,ENTITY_TENPIN);
      }
      HandleLogUpload();
   }

}

// Tenpin FSM Implementation

// FSM actions

void TenpinApplication::Extract(
      void *  notUsed
      )
{
   ExtractCertificates(NULL);
   ExtractFapId(NULL);
}

void TenpinApplication::DnsServerAdd(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<TenpinDnsServerAddReq> req = Serialisable::DeSerialise<TenpinDnsServerAddReq>(message);

   if (req)
   {
      IPv4Address addr(req->GetAddr());

      m_dns->Add(req->GetId(), addr);
   }

   TenpinDnsServerAddCnf cnf;
   SendMessage(cnf, message->GetFromEntity(), message->GetToEntity());
}

void TenpinApplication::FirewallOpen(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<TenpinFirewallOpenReq> req = Serialisable::DeSerialise<TenpinFirewallOpenReq>(message);

   if (req)
   {
      TenpinFirewallOpenCnf cnf;
      cnf.SetToken(req->GetToken());
      m_firewall->Open(req, cnf.m_handles);
      SendMessage(cnf, message->GetFromEntity(), message->GetToEntity());
   }
}

void TenpinApplication::FirewallOpened(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<TenpinFirewallOpenCnf> cnf = Serialisable::DeSerialise<TenpinFirewallOpenCnf>(message);

   if (cnf)
   {
      m_tunnelDb.FirewallOpened(cnf->GetToken(), cnf->m_handles);
   }
}

void TenpinApplication::FirewallClose(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<TenpinFirewallCloseReq> req = Serialisable::DeSerialise<TenpinFirewallCloseReq>(message);

   if (req)
   {
      TenpinFirewallCloseCnf cnf;
      cnf.SetToken(req->GetToken());
      m_firewall->Close(req->m_handles);
      SendMessage(cnf, message->GetFromEntity(), message->GetToEntity());
   }
}

void TenpinApplication::FirewallClosed(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<TenpinFirewallCloseCnf> cnf = Serialisable::DeSerialise<TenpinFirewallCloseCnf>(message);

   if (cnf)
   {
      m_tunnelDb.FirewallClosed(cnf->GetToken());
   }
}

void TenpinApplication::SignatureVerifyFailed(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   TenpinSignatureVerifyCnf cnf(0);
   SendMessage(cnf, message->GetFromEntity(), message->GetToEntity());
}

void TenpinApplication::SignatureVerifyTest(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   u32 result = 0;

   shared_ptr<TenpinSignatureVerifyReq> req = Serialisable::DeSerialise<TenpinSignatureVerifyReq>(message);

   if (req)
   {
      result = m_x509->SignatureVerify(
            m_ike->FilenameCertificate(CERTIFICATE_RADISYS_ROOT_2),
            req->GetInputFilename(),
            req->GetOutputFilename()
            );
   }

   TenpinSignatureVerifyCnf cnf(result);
   SendMessage(cnf, message->GetFromEntity(), message->GetToEntity());
}

void TenpinApplication::StoreAttributes(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<MibSubscribeAttributesInd> ind = Serialisable::DeSerialise<MibSubscribeAttributesInd>(message);
   shared_ptr<MibSubscribeAttributesInd> subscribeAttributesInd = Serialisable::DeSerialise<MibSubscribeAttributesInd>(message);

   RSYS_ASSERT(subscribeAttributesInd != NULL);

   if (subscribeAttributesInd->GetSubscriptionId() == 0)
   {
      u32 val = 0;

      const MibAttributeValues& values = ind->GetMibAttributeValues(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING));

      values.GetAttributeValue(PARAM_ID_IKE_SA_LIFETIME, val);
      m_configuration.Set(CONFIG_IKE_SA_LIFETIME, val);
      values.GetAttributeValue(PARAM_ID_IPSEC_NAT_T_PORT, val);
      m_configuration.Set(CONFIG_IPSEC_NAT_T_PORT, val);
      values.GetAttributeValue(PARAM_ID_IPSEC_SA_LIFETIME, val);
      m_configuration.Set(CONFIG_IPSEC_SA_LIFETIME, val);
   }
   else if (( subscribeAttributesInd->GetSubscriptionId() == 2 ) || ( subscribeAttributesInd->GetSubscriptionId() == 3 ))
   {
      u32 valU32 = 0;
      string valStr;
      vector<string> valStrList;
      u32 cryptoEnable = 0;
      u32 cryptoIdx = 0;

      for(cryptoIdx = 0; cryptoIdx < MAX_CRYPTO_PROFILE; cryptoIdx++)
      {
         MibDN cryptoDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_CRYPTO_PROFILES, cryptoIdx);
         vector<MibDN> dnList = ind->GetDnList();
         vector<MibDN>::iterator it = find(dnList.begin(), dnList.end(), cryptoDn);

         if(it != dnList.end())
         {
            const MibAttributeValues& cryptoParams = ind->GetMibAttributeValues(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_CRYPTO_PROFILES, cryptoIdx));

            cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_PROFILE_ENABLED, cryptoEnable);

            if(cryptoEnable)
            {
               m_configuration.Set(CONFIG_IKE_SEND_INTERMEDIATE_CERTS, true);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_PATH, valStr);
               if (valStr.find("Certificate") == string::npos)
               {
                  TRACE_PRINTF("Received auth method [%s]. Setting authentication method to PSK.", valStr.c_str());
                  m_configuration.Set(CONFIG_IPSEC_AUTH_METHOD, AUTH_METHOD_PSK);
               }
               else
               {
                  TRACE_PRINTF("Setting authentication method to PKI.");
                  m_configuration.Set(CONFIG_IPSEC_AUTH_METHOD, AUTH_METHOD_PKI);
               }
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_MAX_CHILD_SA, valU32);
               m_configuration.Set(CONFIG_IKE_CHILD_SA, valU32);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_IKE_CIPHER_ALGO, valStrList);
               for(u32 index = 0; index < valStrList.size(); index++)
               {
                  if(!(valStrList.at(index).compare("3DES-CBC")))
                  {
                     m_configuration.Set(CONFIG_IKE_ENCRYPTION_3DES_ENABLE, true);
                  }
                  else if (!(valStrList.at(index).compare("AES-CBC")))
                  {
                     m_configuration.Set(CONFIG_IKE_ENCRYPTION_AES128_ENABLE, true);
                  }
               }
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_IKE_PRF, valStrList);
               for(u32 index = 0; index < valStrList.size(); index++)
               {
                  if(!(valStrList.at(index).compare("HMAC-SHA1")))
                  {
                     m_configuration.Set(CONFIG_IKE_PRF_SHA1_ENABLE, true);
                  }
                  else if(!(valStrList.at(index).compare("AES-XCBC-PRF-128")))
                  {
                     m_configuration.Set(CONFIG_IKE_PRF_XCBC_ENABLE, true);
                  }
               }
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_IKE_INTG_ALGO, valStrList);
               for(u32 index = 0; index < valStrList.size(); index++)
               {
                  if(!(valStrList.at(index).compare("HMAC-SHA1-96")))
                  {
                     m_configuration.Set(CONFIG_IKE_INTEGRITY_SHA1_ENABLE, true);
                  }
                  else if(!(valStrList.at(index).compare("AES-XCBC-MAC-96")))
                  {
                     m_configuration.Set(CONFIG_IKE_INTEGRITY_MAC_ENABLE, true);
                  }
               }
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_IKE_DH, valStrList);
               for(u32 index = 0; index < valStrList.size(); index++)
               {
                  if(!(valStrList.at(index).compare("1024")))
                  {
                     m_configuration.Set(CONFIG_IKE_DP1024_ENABLE, true);
                  }
                  else if (!(valStrList.at(index).compare("2048")))
                  {
                     m_configuration.Set(CONFIG_IKE_DP2048_ENABLE, true);
                  }
               }
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_ESP_CIPHER_ALGO, valStrList);
               for(u32 index = 0; index < valStrList.size(); index++)
               {
                  if(!(valStrList.at(index).compare("3DES-CBC")))
                  {
                     m_configuration.Set(CONFIG_IPSEC_ENCRYPTION_3DES_ENABLE, true);
                  }
                  else if (!(valStrList.at(index).compare("AES-CBC")))
                  {
                     m_configuration.Set(CONFIG_IPSEC_ENCRYPTION_AES128_ENABLE, true);
                  }
                  else if (!(valStrList.at(index).compare("Null")))
                  {
                     m_configuration.Set(CONFIG_IPSEC_ENCRYPTION_NULL_ENABLE, true);
                  }
               }
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_ESP_INTG_ALGO, valStrList);
               for(u32 index = 0; index < valStrList.size(); index++)
               {
                  if(!(valStrList.at(index).compare("HMAC-SHA1-96")))
                  {
                     m_configuration.Set(CONFIG_IPSEC_INTEGRITY_SHA1_ENABLE, true);
                  }
                  else if(!(valStrList.at(index).compare("AES-XCBC-MAC-96")))
                  {
                     m_configuration.Set(CONFIG_IPSEC_INTEGRITY_MAC_ENABLE, true);
                  }
               }
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_IPSEC_WINDOW_SIZE, valU32);
               m_configuration.Set(CONFIG_IKE_WINDOW_SIZE, valU32);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_IKE_REKEY_LIFETIME, valU32);
               m_configuration.Set(CONFIG_IKE_REKEY_LIFETIME, valU32);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_IKE_REKEY_LIFETIME_BYTE, valU32);
               m_configuration.Set(CONFIG_IPSEC_LIFETIME_BYTE, valU32);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_IKE_REKEY_LIFETIME_TIME, valU32);
               m_configuration.Set(CONFIG_IPSEC_LIFETIME_TIME, valU32);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_DPD_TIMER, valU32);
               m_configuration.Set(CONFIG_IKE_DPD_INTERVAL, valU32);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_NAT_KEEP_ALIVE_TIMER, valU32);
               m_configuration.Set(CONFIG_NAT_T_KEEP_ALIVE_TIMER, valU32);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_SEC_MAX_FRAG_SIZE, valU32);
               m_configuration.Set(CONFIG_CRYPTO_SEC_MAX_FRAG_SIZE, valU32);
               cryptoParams.GetAttributeValue(PARAM_ID_CRYPTO_SEC_DF_BIT, valStr);
               if(!(valStr.compare("On")))
               {
                  m_configuration.Set(CONFIG_CRYPTO_SEC_DF_BIT, true);
               }
               else if(!(valStr.compare("Off")))
               {
                  m_configuration.Set(CONFIG_CRYPTO_SEC_DF_BIT, false);
               }
            }
         }
      }
   }
   else if (subscribeAttributesInd->GetSubscriptionId() == LOG_UPLOAD_SUBSCRIPTION_ID)
   { 
      const MibAttributeValues& logvalues = ind->GetMibAttributeValues(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP));
      logvalues.GetAttributeValue(PARAM_ID_LOG_UPLOAD_INTERVAL,timervalue);   
      HandleLogUpload();  
   }
}

void TenpinApplication::HandleLogUpload()
{
   if(IsTimerRunning(logTimerHandle))
   {
      DeleteTimer(logTimerHandle);
   }

   if(timervalue > 0)
   {
      TenpinApplication::GetInstance().StartLogTimer(timervalue * 60000);
   }
   else
   {
      TRACE_PRINTF("\nLOG UPLOAD FUNCTIONALITY IS DISABLED");
   }
}

void TenpinApplication::StartLogTimer(u32 timer_value)
{
   logTimerHandle = CreateTimer((const std::string&)"LOG expiration timeout", timer_value ,TimerEngineInterface::TIMER_START_NOW, TimerEngineInterface::TIMER_SINGLE_SHOT);
}

void TenpinApplication::TunnelCreate(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<IkeTunnelCreateReq> req = Serialisable::DeSerialise<IkeTunnelCreateReq>(message);

   if (req)
   {
      u32 id = m_tunnelDb.Provision(message->GetFromEntity(), req->GetDestAddr());
      string& authMethod =req->GetAuthMethod();

      TRACE_PRINTF("Receivied authentication method \"%s\".", authMethod.c_str());
      if (!authMethod.compare("PSK"))
      {
         TRACE_PRINTF("Setting authentication method to PSK.");
         m_configuration.Set(CONFIG_IPSEC_AUTH_METHOD, AUTH_METHOD_PSK);
      }
      else
      {
         TRACE_PRINTF("Setting authentication method to PKI.");
         m_configuration.Set(CONFIG_IPSEC_AUTH_METHOD, AUTH_METHOD_PKI);
      }

      IkeTunnelCreateCnf cnf(id);
      SendMessage(cnf, message->GetFromEntity(), ENTITY_TENPIN);

      if (id)
      {
         m_ike->Reconfigure(m_tunnelDb, m_fapId);
      }
   }
}

void TenpinApplication::TunnelDelete(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<IkeTunnelDeleteReq> req = Serialisable::DeSerialise<IkeTunnelDeleteReq>(message);

   if (req)
   {
      u32 id = req->GetId();

      IkeTunnelDeleteCnf cnf(id);
      SendMessage(cnf, message->GetFromEntity(), ENTITY_TENPIN);

      TunnelTeardownAndReconfigure(id);
   }
}

void TenpinApplication::TunnelConnected(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<IkeTunnelConnectInd> ind = Serialisable::DeSerialise<IkeTunnelConnectInd>(message);

   // NOTE: when multiple tunnels will be supported, this will be sent only for the first tunnel currently active
   MfOpStateInformInd opStateInform(MF_IPSEC_TUNNEL, ManagedObject::OP_STATE_ENABLED, 0, "SeGW tunnel is up!");
   SendMessage(opStateInform, ENTITY_OAM);

   if (ind)
   {
      MessagingEntity toEntity = m_tunnelDb.Connected(ind->GetId(), ind->GetTunnelAddr());

      if (ENTITY_INVALID != toEntity)
      {
         SendMessage(*ind, toEntity, ENTITY_TENPIN);
      }
   }
}

void TenpinApplication::TunnelDisconnected(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<IkeTunnelDisconnectInd> ind = Serialisable::DeSerialise<IkeTunnelDisconnectInd>(message);

   // NOTE: when multiple tunnels will be supported, this will be sent only when last tunnel is down
   MfOpStateInformInd opStateInform(MF_IPSEC_TUNNEL, ManagedObject::OP_STATE_DISABLED, 0, "SeGW tunnel is down");
   SendMessage(opStateInform, ENTITY_OAM);

   if (ind)
   {
      MessagingEntity toEntity = m_tunnelDb.Disconnected(ind->GetId());

      if (ENTITY_INVALID != toEntity)
      {
         SendMessage(*ind, toEntity, ENTITY_TENPIN);
      }
   }
}

void TenpinApplication::HwCryptoCtrl(
      shared_ptr<threeway::MessageSerialisedData> message
      )
{
   shared_ptr<HwCryptoAvailableInd> ind = Serialisable::DeSerialise<HwCryptoAvailableInd>(message);

   if (ind)
   {
      if (ind->GetAvailable())
      {
         m_hwCrypto->Enable();
      }
      else
      {
         m_hwCrypto->Disable();
      }
   }
}

// FSM entry/exit

void TenpinApplication::UnusableEntry(
      void
      )
{
   NotifyOamUnusable(NULL);
}

void TenpinApplication::NotConfiguredEntry(
      void
      )
{
   SubscribeAttributes(NULL);
   StartGuardTimer(NULL);
}

void TenpinApplication::NotConfiguredExit(
      void
      )
{
   StopGuardTimer(NULL);
}

void TenpinApplication::NotStartedEntry(
      void
      )
{
   NotifyOamReady(NULL);
   StartGuardTimer(NULL);
}

void TenpinApplication::StartingEntry(
      void
      )
{
   StartIke(NULL);
   StartIkeGraceTimer(NULL);
}

void TenpinApplication::StartingExit(
      void
      )
{
   StopIkeGraceTimer(NULL);
}

void TenpinApplication::StartedEntry(
      void
      )
{
   DeleteGuardTimer(NULL);
   DeleteIkeGraceTimer(NULL);
}

void TenpinApplication::OperationalEntry(
      void
      )
{
   PublishFapId(NULL);
   RegisterCliCommands(NULL);
   NotifyOamOperational(NULL);
}

void TenpinApplication::OperationalExit(
      void
      )
{
   StopIke(NULL);
}

// FSM conditions

bool TenpinApplication::CheckUsable(
      void
      )
{
   return (CheckCertificates() && CheckFapId());
}

// External actions required by FSM

void TenpinApplication::ExtractCertificates(
      void *  notUsed
      )
{
   m_tpm->ExtractCertificateToFile(TPM_CERT_RADISYS_ROOT1, m_ike->FilenameCertificate(CERTIFICATE_RADISYS_ROOT_1));
   m_tpm->ExtractCertificateToFile(TPM_CERT_RADISYS_ROOT2, m_ike->FilenameCertificate(CERTIFICATE_RADISYS_ROOT_2));
   m_tpm->ExtractCertificateToFile(TPM_CERT_RADISYS_BATCH, m_ike->FilenameCertificate(CERTIFICATE_RADISYS_BATCH));
   m_tpm->ExtractCertificateToFile(TPM_CERT_FAP,           m_ike->FilenameCertificate(CERTIFICATE_RADISYS_FAP));
}

void TenpinApplication::ExtractFapId(
      void *  notUsed
      )
{
   m_tpm->ExtractFapId(m_fapId);
}

void TenpinApplication::PublishFapId(
      void *  notUsed
      )
{
   MibAttributeValues avs;
   avs.AddAttribute(PARAM_ID_FAP_ID, m_fapId);
   MibSetAttributesReq req(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), avs);
   TenpinApplication::GetInstance().SendMessage(req, ENTITY_MIB, ENTITY_TENPIN);
}

void TenpinApplication::StartGuardTimer(
      void *  notUsed
      )
{
   StartTimer(m_guardTimer);
}

void TenpinApplication::StopGuardTimer(
      void *  notUsed
      )
{
   StopTimer(m_guardTimer);
}

void TenpinApplication::DeleteGuardTimer(
      void *  notUsed
      )
{
   DeleteTimer(m_guardTimer);
}

void TenpinApplication::StartIkeGraceTimer(
      void *  notUsed
      )
{
   StartTimer(m_ikeGraceTimer);
}

void TenpinApplication::StopIkeGraceTimer(
      void *  notUsed
      )
{
   StopTimer(m_ikeGraceTimer);
}

void TenpinApplication::DeleteIkeGraceTimer(
      void *  notUsed
      )
{
   DeleteTimer(m_ikeGraceTimer);
}

void TenpinApplication::SubscribeAttributes(
      void *  notUsed
      )
{
   MibDN dn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING);

   MibAttributeIds ids;
   ids.insert(PARAM_ID_IKE_SA_LIFETIME);
   ids.insert(PARAM_ID_IPSEC_NAT_T_PORT);
   ids.insert(PARAM_ID_IPSEC_ENCRYPTION_3DES_ENABLE);
   ids.insert(PARAM_ID_IPSEC_ENCRYPTION_AES_ENABLE);
   ids.insert(PARAM_ID_IPSEC_ENCRYPTION_AES128_ENABLE);
   ids.insert(PARAM_ID_IPSEC_ENCRYPTION_NULL_ENABLE);
   ids.insert(PARAM_ID_IPSEC_SA_LIFETIME);

   MibSubscribeAttributesReq req(0, dn, ids);
   SendMessage(req, ENTITY_MIB, ENTITY_TENPIN);

   u32 idx = 0;
   for(idx = 0; idx < MAX_CRYPTO_PROFILE; idx++)
   {
      MibAttributeIds cryptoParams;
      MibDN cryptoProfileMO = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_CRYPTO_PROFILES, idx);

      cryptoParams.insert(PARAM_ID_CRYPTO_PROFILE_ENABLED);
      cryptoParams.insert(PARAM_ID_CRYPTO_PATH);
      cryptoParams.insert(PARAM_ID_CRYPTO_MAX_CHILD_SA);
      cryptoParams.insert(PARAM_ID_CRYPTO_IKE_CIPHER_ALGO);
      cryptoParams.insert(PARAM_ID_CRYPTO_IKE_PRF);
      cryptoParams.insert(PARAM_ID_CRYPTO_IKE_INTG_ALGO);
      cryptoParams.insert(PARAM_ID_CRYPTO_IKE_DH);
      cryptoParams.insert(PARAM_ID_CRYPTO_ESP_CIPHER_ALGO);
      cryptoParams.insert(PARAM_ID_CRYPTO_ESP_INTG_ALGO);
      cryptoParams.insert(PARAM_ID_CRYPTO_IPSEC_WINDOW_SIZE);
      cryptoParams.insert(PARAM_ID_CRYPTO_IKE_REKEY_LIFETIME);
      cryptoParams.insert(PARAM_ID_CRYPTO_IKE_REKEY_LIFETIME_BYTE);
      cryptoParams.insert(PARAM_ID_CRYPTO_IKE_REKEY_LIFETIME_TIME);
      cryptoParams.insert(PARAM_ID_CRYPTO_DPD_TIMER);
      cryptoParams.insert(PARAM_ID_CRYPTO_NAT_KEEP_ALIVE_TIMER);
      cryptoParams.insert(PARAM_ID_CRYPTO_SEC_MAX_FRAG_SIZE);
      cryptoParams.insert(PARAM_ID_CRYPTO_SEC_DF_BIT);

      MibSubscribeAttributesReq subReq(idx + 2, cryptoProfileMO, cryptoParams);
      SendMessage(subReq, ENTITY_MIB, ENTITY_TENPIN);
   }

   MibDN dn2 = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);
   MibAttributeIds ids2;
   ids2.insert(PARAM_ID_LOG_UPLOAD_INTERVAL);
   MibSubscribeAttributesReq req2(LOG_UPLOAD_SUBSCRIPTION_ID, dn2, ids2);
   SendMessage(req2, ENTITY_MIB, ENTITY_TENPIN);
}

void TenpinApplication::NotifyOamUnusable(
      void *  notUsed
      )
{
   TRACE_MSG_LEV(TRACE_FATAL, "FAP is unusable, failed to meet pre-requisites for operation.");
}

void TenpinApplication::NotifyOamReady(
      void *  notUsed
      )
{
   NotifyReady(ENTITY_OAM, ENTITY_TENPIN, false);
}

void TenpinApplication::NotifyOamOperational(
      void *  notUsed
      )
{
   MfOpStateInformInd ind(MF_IKE, ManagedObject::OP_STATE_ENABLED, 0, "");
   SendMessage(ind, ENTITY_OAM);
}

void TenpinApplication::RegisterCliCommands(
      void *  notUsed
      )
{
   shared_ptr<CliHandler> handlerTenpin(new CliHandler(ENTITY_TENPIN, "tenpin"));
   RegisterCliHandler(ENTITY_TENPIN, handlerTenpin);

   shared_ptr<CliHandler> handlerIke(new CliHandler(ENTITY_IKE, "ike", false));
   RegisterCliHandler(ENTITY_IKE, handlerIke);
   m_ike->RegisterCli(handlerIke);

   shared_ptr<CliHandler> handlerIPsec(new CliHandler(ENTITY_IPSEC_TUNNEL_DB, "ipsec", false));
   RegisterCliHandler(ENTITY_IPSEC_TUNNEL_DB, handlerIPsec);
   m_tunnelDb.RegisterCli(handlerIPsec);

   shared_ptr<CliHandler> handlerTpm(new CliHandler(ENTITY_TPM, "tpm", false));
   RegisterCliHandler(ENTITY_TPM, handlerTpm);
   m_tpm->RegisterCli(handlerTpm);

   shared_ptr<CliHandler> handlerX509(new CliHandler(ENTITY_X509, "x509", false));
   RegisterCliHandler(ENTITY_X509, handlerX509);
   m_x509->RegisterCli(handlerX509);
}

void TenpinApplication::StartIke(
      void *  notUsed
      )
{
   m_ike->Start(m_tunnelDb, m_fapId);
}

void TenpinApplication::StopIke(
      void *  notUsed
      )
{
   m_ike->Stop();
}

// External conditions required by FSM

bool TenpinApplication::CheckCertificates(
      void
      )
{
   return m_ike->CheckCertificates();
}

bool TenpinApplication::CheckFapId(
      void
      )
{
   return FapId::IsValid(m_fapId);
}

// main

int main(
      int     argc,
      char ** argv
      )
{
   int exitCode = 1;


   try
   {
      exitCode = TenpinApplication::GetInstance().Run(argc, argv);
   }
   catch (threeway::Exception& e)
   {
      TRACE_EXCEPTION(e);
   }

   return exitCode;
}
