///////////////////////////////////////////////////////////////////////////////
//
// TenpinConfiguration.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinConfiguration_h_
#define __TenpinConfiguration_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include <Radisys.h>
#include <messaging/transport/CliHandler.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////

typedef enum {

   CONFIG_IKE_SEND_INTERMEDIATE_CERTS = 0,
   CONFIG_IKE_ENCRYPTION_3DES_ENABLE,
   CONFIG_IKE_ENCRYPTION_AES128_ENABLE,
   CONFIG_IKE_ENCRYPTION_NULL_ENABLE,
   CONFIG_IKE_SA_LIFETIME,
   CONFIG_IKE_DPD_INTERVAL,
   CONFIG_IPSEC_NAT_T_PORT,
   CONFIG_IPSEC_ENCRYPTION_3DES_ENABLE,
   CONFIG_IPSEC_ENCRYPTION_AES_ENABLE,
   CONFIG_IPSEC_ENCRYPTION_AES128_ENABLE,
   CONFIG_IPSEC_ENCRYPTION_NULL_ENABLE,
   CONFIG_IPSEC_SA_LIFETIME,
   CONFIG_IPSEC_AUTH_METHOD,
   CONFIG_IPSEC_INTEGRITY_SHA1_ENABLE,
   CONFIG_IPSEC_INTEGRITY_MAC_ENABLE,
   CONFIG_IKE_INTEGRITY_SHA1_ENABLE,
   CONFIG_IKE_INTEGRITY_MAC_ENABLE,
   CONFIG_IKE_DP1024_ENABLE,
   CONFIG_IKE_DP2048_ENABLE,
   CONFIG_IKE_PRF_SHA1_ENABLE,
   CONFIG_IKE_PRF_XCBC_ENABLE,
   CONFIG_IKE_WINDOW_SIZE,
   CONFIG_IKE_REKEY_LIFETIME,
   CONFIG_IPSEC_LIFETIME_BYTE,
   CONFIG_IPSEC_LIFETIME_TIME,
   CONFIG_NAT_T_KEEP_ALIVE_TIMER,
   CONFIG_IKE_CHILD_SA,
   CONFIG_CRYPTO_SEC_MAX_FRAG_SIZE,
   CONFIG_CRYPTO_SEC_DF_BIT,
   NUM_TENPIN_CONFIGURATION_ITEMS
} TenpinConfigurationItem_e;

typedef enum {
    AUTH_METHOD_PSK,
    AUTH_METHOD_PKI
} TenpinAuthMethod;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;

namespace threeway
{

class TenpinConfiguration
{
   public:
      TenpinConfiguration()
      {
         memset(m_itemSet, 0, sizeof(m_itemSet));
         memset(m_itemVal, 0, sizeof(m_itemVal));
      }
      ~TenpinConfiguration() {}

      void Set(TenpinConfigurationItem_e item, u32 val);
      bool Get(TenpinConfigurationItem_e item, u32& val) const;

      shared_ptr<CliResponse> CliShowConfig(const CliArguments& cliArgs) const;

   private:
      bool m_itemSet[NUM_TENPIN_CONFIGURATION_ITEMS];
      u32  m_itemVal[NUM_TENPIN_CONFIGURATION_ITEMS];
};

} // namespace threeway

#endif
