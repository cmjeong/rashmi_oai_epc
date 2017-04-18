///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinConfiguration.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Private Data
///////////////////////////////////////////////////////////////////////////////

static const char * itemLabel[NUM_TENPIN_CONFIGURATION_ITEMS] = {
/*CONFIG_IKE_SEND_INTERMEDIATE_CERTS*/      "send intermediate certs",
/*CONFIG_IKE_ENCRYPTION_3DES_ENABLE*/       "IKE enable 3DES encryption",
/*CONFIG_IKE_ENCRYPTION_AES128_ENABLE*/     "IKE enable AES-128 encryption",
/*CONFIG_IKE_ENCRYPTION_NULL_ENABLE*/       "IKE enable null encryption",
/*CONFIG_IKE_SA_LIFETIME*/                  "IKE SA lifetime",
/*CONFIG_IKE_DPD_INTERVAL*/                 "DPD interval",
/*CONFIG_IPSEC_NAT_T_PORT*/                 "NAT-T port",
/*CONFIG_IPSEC_ENCRYPTION_3DES_ENABLE*/     "IPsec enable 3DES encryption",
/*CONFIG_IPSEC_ENCRYPTION_AES_ENABLE*/      "IPsec enable AES encryption",
/*CONFIG_IPSEC_ENCRYPTION_AES128_ENABLE*/   "IPsec enable AES-128 encryption",
/*CONFIG_IPSEC_ENCRYPTION_NULL_ENABLE*/     "IPsec enable null encryption",
/*CONFIG_IPSEC_SA_LIFETIME*/                "IPsec SA lifetime",
/*CONFIG_IPSEC_AUTH_METHOD*/                "IPsec authentication mehtod PSK=0, PKI=1",
/*CONFIG_IPSEC_INTEGRITY_SHA1_ENABLE*/      "IPSec Integrity sha enable",
/*CONFIG_IPSEC_INTEGRITY_MAC_ENABLE*/       "IPSec Integrity MAC enable",
/*CONFIG_IKE_INTEGRITY_SHA1_ENABLE*/        "IKE Integrity sha enable",
/*CONFIG_IKE_INTEGRITY_MAC_ENABLE*/         "IKE Integrity MAC enable",
/*CONFIG_IKE_DP1024_ENABLE*/                "DH 1024 enable",
/*CONFIG_IKE_DP2048_ENABLE*/                "DH 2048 enable",
/*CONFIG_IKE_PRF_SHA1_ENABLE*/              "CONFIG_IKE_PRF_SHA1_ENABLE",
/*CONFIG_IKE_PRF_XCBC_ENABLE*/              "CONFIG_IKE_PRF_XCBC_ENABLE",
/*CONFIG_IKE_WINDOW_SIZE*/                  "CONFIG_IKE_WINDOW_SIZE",
/*CONFIG_IKE_REKEY_LIFETIME*/               "CONFIG_IKE_REKEY_LIFETIME",
/*CONFIG_IPSEC_LIFETIME_BYTE*/              "CONFIG_IKE_REKEY_LIFETIME_BYTE",
/*CONFIG_IPSEC_LIFETIME_TIME*/              "CONFIG_IPSEC_LIFETIME_TIME",
/*CONFIG_NAT_T_KEEP_ALIVE_TIMER*/           "CONFIG_NAT_T_KEEP_ALIVE_TIMER",
/*CONFIG_IKE_CHILD_SA*/                     "CONFIG_IKE_CHILD_SA",
/*CONFIG_CRYPTO_SEC_MAX_FRAG_SIZE*/         "CONFIG_CRYPTO_SEC_MAX_FRAG_SIZE",
/*CONFIG_CRYPTO_SEC_DF_BIT*/                "CONFIG_CRYPTO_SEC_DF_BIT"
};

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

void TenpinConfiguration::Set(
      TenpinConfigurationItem_e   item,
      u32                         val
      )
{
   if (    (0 <= item)
         && (item < NUM_TENPIN_CONFIGURATION_ITEMS)
      )
   {
      m_itemSet[item] = true;
      m_itemVal[item] = val;
   }
}

bool TenpinConfiguration::Get(
      TenpinConfigurationItem_e   item,
      u32&                        val
      ) const
{
   if (    (0 <= item)
         && (item < NUM_TENPIN_CONFIGURATION_ITEMS)
         && (true == m_itemSet[item])
      )
   {
      /* support at least one encryption choice, preferring anything other than null encryption */

      if (    (CONFIG_IKE_ENCRYPTION_AES128_ENABLE == item)
            && (0 == m_itemVal[item])
            && (    (false == m_itemSet[CONFIG_IKE_ENCRYPTION_NULL_ENABLE])
               || (0 == m_itemVal[CONFIG_IKE_ENCRYPTION_NULL_ENABLE])
               )
         )
      {
         val = 1;
      }
      else
         if (    (CONFIG_IPSEC_ENCRYPTION_AES128_ENABLE == item)
               && (0 == m_itemVal[item])
               && (    (false == m_itemSet[CONFIG_IPSEC_ENCRYPTION_NULL_ENABLE])
                  || (0 == m_itemVal[CONFIG_IPSEC_ENCRYPTION_NULL_ENABLE])
                  )
            )
         {
            val = 1;
         }
         else
         {
            val = m_itemVal[item];
         }

      return true;
   }

   return false;
}

shared_ptr<CliResponse> TenpinConfiguration::CliShowConfig(
      const CliArguments& cliArgs
      ) const
{
   std::ostringstream stream;

   for (int item = 0; item < NUM_TENPIN_CONFIGURATION_ITEMS; item++)
   {
      u32  val = 0;

      stream << (itemLabel[item] ? itemLabel[item] : "?");
      stream << " = ";

      if (Get((TenpinConfigurationItem_e)item, val))
      {
         stream << val;
      }
      else
      {
         stream << "(not set)";
      }

      stream << "\n";
   }

   shared_ptr<CliResponse> response(new CliResponse(stream.str()));
   return response;
}

