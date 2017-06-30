///////////////////////////////////////////////////////////////////////////////
//
// MibUpgrade.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <iostream>
#include <sstream>

#include <system/Trace.h>
#include <system/ConfigurationFile.h>
#include <mib-core/IniFormatNvStore.h> // IniFormatNvStore...a concrete NVSI
#include <mib-core/MibManager.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibUpgrade.h"
#include <string.h>

#define MAX_DIR_LEN 50

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

char* m_pOamConfigFilesDir=NULL;
std::string m_sOamConfigFilesDir=""; 

void MibUpgrade::UpdateOamMiBDirPath()
{
   boost::shared_ptr<MibManager> mibManager(new MibManager(NULL));

   m_pOamConfigFilesDir = mibManager->m_pOamConfigFilesDir;

   if(NULL != m_pOamConfigFilesDir)
   {
      m_sOamConfigFilesDir = m_pOamConfigFilesDir;
   }
}


static const NvStoreSchemaVersion MIB_NV_FACTORY_SCHEMA_REQUIRED = 2;
static const NvStoreSchemaVersion MIB_NV_OPERATIONAL_SCHEMA_REQUIRED = 11;

static const NvContainerName FACTORY_CONTAINER = "FACTORY";
static const string OLD_FACTORY_FILE_NAME = m_sOamConfigFilesDir + "/config/mib-factory";

static const NvContainerName OPERATIONAL_CONTAINER = "FAP";
static const string OLD_OPERATIONAL_FILE_NAME = m_sOamConfigFilesDir + "/config/mib-params";

static const NvContainerName COMMISSIONING_CONTAINER = "COMMISSIONING";

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

void MibUpgrade::DoMibUpgrade()
{
   TRACE_MSG("Checking if MIB upgrade required.");

   string nvStorePath, factoryNvStoreFileName, operationalNvStoreFileName;

   UpdateOamMiBDirPath();
   //#ifndef BUILD_i686_linux
   //    nvStorePath = "/mnt/config/";
   //#endif

   m_sOamConfigFilesDir = m_sOamConfigFilesDir + "/config/";

   nvStorePath = m_sOamConfigFilesDir;

   factoryNvStoreFileName = nvStorePath + "mib-factory.nv";

   //#if defined(PRODUCT_hbs2_iu) || defined(PRODUCT_hbs2_factory)
   bool isHomeFapBuild = true;
   operationalNvStoreFileName = nvStorePath + "mib-home-fap.nv";
   //#else
   //bool isHomeFapBuild = false;
   //operationalNvStoreFileName = nvStorePath + "mib-standalone.nv";
   //#endif

   // Upgrade the factory aspects
   MibUpgrade mibFactoryUpgrade;
   mibFactoryUpgrade.Perform(MIB_NV_FACTORY_SCHEMA_REQUIRED, factoryNvStoreFileName, true /* factory store */, isHomeFapBuild);

   // Upgrade the operational aspects
   MibUpgrade mibOperationalUpgrade;
   mibOperationalUpgrade.Perform(MIB_NV_OPERATIONAL_SCHEMA_REQUIRED, operationalNvStoreFileName, false /* operational store */, isHomeFapBuild);

   TRACE_MSG("Finished MIB upgrade.");
}

void MibUpgrade::Perform(NvStoreSchemaVersion targetNvStoreSchema, const string& nvStoreFile, bool isFactoryFile, bool isHomeFapBuild)
{
   IniFormatNvStore iniFormatNvStore;
   iniFormatNvStore.SetStoreFileName(nvStoreFile);
   if(!(iniFormatNvStore.InitialiseNvStore()))
   {
      //SendFactoryResetReq();
   }

   NvStoreSchemaVersion currentNvStoreSchema;
   currentNvStoreSchema = iniFormatNvStore.GetCurrentNvStoreSchemaVersion();

   // Now upgrade the store to the target version
   for (NvStoreSchemaVersion schema = currentNvStoreSchema + 1;
         schema <= targetNvStoreSchema;
         schema++)
   {
      TRACE_PRINTF("Upgrading %s NV store from %d to %d", (isFactoryFile ? "factory" : "operational"), schema - 1, schema);
      iniFormatNvStore.StartNvTransaction();
      iniFormatNvStore.SetCurrentNvStoreSchemaVersion(schema);

      if(isFactoryFile)
      {
         UpgradeFactoryFile(schema, iniFormatNvStore, isHomeFapBuild);
      }
      else
      {
         UpgradeOperationalFile(schema, iniFormatNvStore, isHomeFapBuild);
      }

      iniFormatNvStore.EndNvTransaction();
   } // for

   // Mark as the latest and greatest.
   // Note, this also handles downgrades... nothing will happen above but the store should
   // already support the schema we're downgrading to so just tell it to use it.
   iniFormatNvStore.SetCurrentNvStoreSchemaVersion(targetNvStoreSchema);
}

void MibUpgrade::UpgradeFactoryFile(NvStoreSchemaVersion targetSchema, NonVolatileStoreUpgradeDowngradeInterface& schemingNvStore, bool isHomeFapBuild)
{
   switch(targetSchema)
   {
      case 1:
         Upgrade0To1(schemingNvStore, true /* factory */);
         break;
      case 2:
         UpgradeFactory1To2(schemingNvStore);
         break;
      default:
         RSYS_ASSERT_FAIL("No factory MIB upgrader to target schema %"PRIu32, (u32)targetSchema);
         break;
   }
}

void MibUpgrade::UpgradeOperationalFile(NvStoreSchemaVersion targetSchema, NonVolatileStoreUpgradeDowngradeInterface& schemingNvStore, bool isHomeFapBuild)
{
   switch(targetSchema)
   {
      case 1:
         Upgrade0To1(schemingNvStore, false /* operational */);
         break;
      case 2:
         UpgradeOperational1To2(schemingNvStore, isHomeFapBuild);
         break;
      case 3:
         UpgradeOperational2To3(schemingNvStore, isHomeFapBuild);
         break;
      case 4:
         UpgradeOperational3To4(schemingNvStore);
         break;
      case 5:
         UpgradeOperational4To5(schemingNvStore);
         break;
      case 6:
         UpgradeOperational5To6(schemingNvStore);
         break;
      case 7:
         UpgradeOperational6To7(schemingNvStore);
         break;
      case 8:
         UpgradeOperational7To8(schemingNvStore);
         break;
      case 9:
         UpgradeOperational8To9(schemingNvStore);
         break;
      case 10:
         UpgradeOperational9To10(schemingNvStore);
         break;
      case 11:
         UpgradeOperational10To11(schemingNvStore);
         break;
      default:
         RSYS_ASSERT_FAIL("No operational MIB upgrader to target schema %"PRIu32, (u32)targetSchema);
         break;
   }
}

void MibUpgrade::Upgrade0To1(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore, bool isFactoryFile)
{
   TRACE_PRINTF("Upgrading %s NV store from 0 (old MIB) to 1 (new MIB)", (isFactoryFile ? "factory" : "operational"));

   // This needs to be done elsewhere or at least the importing file my be specified from outside because we don't know the name of the exporting .nv file
   // If file doesn't exist then try to import
   ConfigurationFile oldSchemaVersion(isFactoryFile ? OLD_FACTORY_FILE_NAME : OLD_OPERATIONAL_FILE_NAME, "");
   oldSchemaVersion.ReadConfigurationFile();

   NvContainerDescriptor nvContainer;
   nvContainer.m_nvContainerName = (isFactoryFile ? FACTORY_CONTAINER : OPERATIONAL_CONTAINER);
   nvContainer.m_nvContainerInstance = 0;

   vector<string> oldSchemaVersionKeys = oldSchemaVersion.GetParameters();

   TRACE_PRINTF("There are %"PRIu32" parameters.", (u32)oldSchemaVersionKeys.size());

   vector<NvAttribute> nvAttributeList;
   for (vector<string>::const_iterator oldSchemaVersionKeysIter = oldSchemaVersionKeys.begin();
         oldSchemaVersionKeysIter != oldSchemaVersionKeys.end();
         ++oldSchemaVersionKeysIter)
   {
      ////////////////////////////////////////////////////////////////////////////
      // Perform some mutations on some strings that are necessary for the upgrade
      ////////////////////////////////////////////////////////////////////////////
      string potentialName = *oldSchemaVersionKeysIter;

      // Remove PARAM_ID_ substring
      string param_id = "PARAM_ID_";
      if (potentialName.compare(0,param_id.size(), param_id) == 0)
      {
         potentialName = potentialName.substr(param_id.size());
      }

      // Skip 3WAY_MGR_IP_ADDRESS
      if (potentialName == "3WAY_MGR_IP_ADDRESS")
      {
         continue;
      }

      // Perform name swap if attributes has a name in our list
      PerformNameSwap(potentialName);

      // Move digit prefix to end i.e. 1ST_VARIABLENAME becomes VARIABLENAME_1ST
      if (isdigit(potentialName[0]))
      {
         string newName = potentialName.substr(4);
         newName += "_";
         newName += potentialName.substr(0,3);
         potentialName = newName;
      }

      string attributeValue = oldSchemaVersion.GetStringParameter(oldSchemaVersionKeysIter->c_str(), "");

      // Code to change the attribute value goes here
      if (potentialName == "SOFTWARE_RELEASE") // decimalize the hex string
      {
         u32 value = 0;
         string decimalString;

         // Convert from base 16 string to u32
         stringstream conversionStream, conversionStream2;
         conversionStream << attributeValue;
         conversionStream >> hex >> value;

         // Convert from u32 to base 10 string
         conversionStream2 << value;
         conversionStream2 >> dec >> decimalString;
         attributeValue = decimalString;
      }

      NvAttribute nvAttribute(NvAttributeDescriptor(potentialName, 0), attributeValue, 1 /* schema version */);
      nvAttributeList.push_back(nvAttribute);
   }

   schemingNvStore.SetNvAttributes(nvContainer, nvAttributeList);
}

typedef struct
{
   string left;
   string right;
} NameSwapPair;

void MibUpgrade::PerformNameSwap(string & potentialName)
{
   NameSwapPair nameSwapPairs[] =
   {
      { "TOTAL_TX_POWER",             "TOTAL_TX_POWER_DBM"},
      { "CONGESTION_RETRY_TIMER",     "RRC_RETRY_TIMER"},
      { "MEASUREMENT_PERIOD",                 "RELOCATION_MEASUREMENT_PERIOD"},
      { "T_RELOC_PREPARE",                    "RELOCATION_T_RELOC_PREPARE"},
      { "T_RELOC_OVERALL",                    "RELOCATION_T_RELOC_OVERALL"},
      { "S_INTERSEARCH",                "S_INTER_SEARCH"},
      { "HCS_PRIO",                     "HCS_PRIORITY"},
      { "T_CRMAX",                      "T_CR_MAX"},
      { "T_CRMAXHYST",                  "T_CR_MAX_HYST"},
      { "S_INTERSEARCH_PRESENT",        "S_INTER_SEARCH_PRESENT"},
      { "CELL_RESTRICTIONS",            "CELL_RESTRICTION"},
      { "AC_BARRED_LIST_PS_MASK",       "BARRED_LIST_PS_MASK"},
      { "POWER_RAMP_STEP",            "PWR_RAMP_STEP"},
      { "ADVERTISE_HSDPA_CAPABILITY",      "HSDPA_CAPABILITY"},
      { "ADVERTISE_HSUPA_CAPABILITY",      "HSUPA_CAPABILITY"},
      { "NUM_WCDMA_INTRAFREQ_NCELLS",      "NUM_INTRA_FREQ_NEIGHBOUR_CELLS"},
      { "NUM_WCDMA_INTERFREQ_NCELLS",      "NUM_INTER_FREQ_NEIGHBOUR_CELLS"},
      { "RRM_384k_BEARER",             "384k_BEARER"},
      { "RRM_FORCE_PS",                "FORCE_PS"},
      { "REM_MIN_NBOUR_CPICH_ECN0", "MIN_NEIGHBOUR_CPICH_ECN0"},
      { "REM_MIN_NBOUR_CPICH_RSCP", "MIN_NEIGHBOUR_CPICH_RSCP"},
      { "REM_PLANNING_CPICH_RSCP",    "PLANNING_CPICH_RSCP"},
      { "REM_SCAN_FREQUENCY0",        "REM_SCAN_FREQ0"},
      { "REM_SCAN_FREQUENCY1",        "REM_SCAN_FREQ1"},
      { "REM_SCAN_FREQUENCY2",        "REM_SCAN_FREQ2"},
      { "REM_SCAN_FREQUENCY3",        "REM_SCAN_FREQ3"},
      { "CAC_SIG_NTP_AVG_BIT_RATE",         "CAC_NTP_AVG_BIT_RATE" },
      { "CAC_SIG_RANAP_AVG_BIT_RATE",       "CAC_RANAP_AVG_BIT_RATE" },
      { "CAC_SIG_OAM_AVG_BIT_RATE",         "CAC_OAM_AVG_BIT_RATE" },
   };

   for (int i = (sizeof(nameSwapPairs)/sizeof(NameSwapPair)) -1; i >= 0; --i)
   {
      if (nameSwapPairs[i].right == potentialName)
      {
         potentialName = nameSwapPairs[i].left;
         break;
      }
   }
}

void MibUpgrade::UpgradeOperational1To2(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore, bool isHomeFapBuild)
{
#if 0
   // ...if the introduced attribute does not already have a set value...
   // ...explicitly set the corresponding value for that attribute
   // ...otherwise just accept the default value

   if(isHomeFapBuild)
   {
      TRACE_MSG("Operational NV store upgrade from 1 to 2 - FAP hardening attributes.");

      NvContainerDescriptor cd(OPERATIONAL_CONTAINER, 0);

      NvAttributeDescriptor sse("SOFTWARE_SIGNING_ENABLE", 0);

      NvAttributeValue av;

      bool got_cse = (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(cd, cse, av));
      bool got_sse = (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(cd, sse, av));

      if (!got_cse || !got_sse)
      {
         bool got_fhl = (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(cd, cse, av));

         if (got_fhl && (0 == av.GetAsU32()))
         {
            vector<NvAttribute> al;

            if (!got_cse)
            {
               NvAttribute a(cse, "0", 2 /* schema version */);
               al.push_back(a);
            }

            if (!got_sse)
            {
               NvAttribute a(sse, "0", 2 /* schema version */);
               al.push_back(a);
            }

            schemingNvStore.SetNvAttributes(cd, al);
         }
      }
   }
   else
   {
      TRACE_MSG("Operational NV store upgrade from 1 to 2 - nothing to do in standalone FAP.");
   }
#endif
}

void MibUpgrade::UpgradeOperational2To3(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore, bool isHomeFapBuild)
{
#if 0
   // This version just changes the default value for SCCP_T_CONN_EST

   if(isHomeFapBuild)
   {
      TRACE_MSG("Operational NV store upgrade from 2 to 3 - updating default for SCCP_T_CONN_EST.");

      NvContainerDescriptor container(OPERATIONAL_CONTAINER, 0);

      NvAttributeDescriptor attrib("SCCP_T_CONN_EST", 0);

      NvAttributeValue attribValue;

      if (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(container, attrib, attribValue))
      {
         // if the value is set to the default, update it to the new default
         if (5 == attribValue.GetAsU32())
         {
            vector<NvAttribute> attribsToSet;
            attribValue.assign("30");
            NvAttribute updatedAttrib(attrib, attribValue, 3 /* schema version */);
            attribsToSet.push_back(updatedAttrib);
            schemingNvStore.SetNvAttributes(container, attribsToSet);
         }
      }
   }
   else
   {
      TRACE_MSG("Operational NV store upgrade from 2 to 3 - nothing to do in standalone FAP.");
   }
#endif
}

void MibUpgrade::UpgradeOperational3To4(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   // This version just checks the range for CELL_IDENTITY

   TRACE_MSG("Operational NV store upgrade from 3 to 4 - checking CELL_IDENTITY limits.");

   NvContainerDescriptor container(OPERATIONAL_CONTAINER, 0);

   NvAttributeDescriptor attrib("CELL_IDENTITY", 0);

   NvAttributeValue attribValue;

   if (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(container, attrib, attribValue))
   {
      // if the value is out of range, set it to zero
      if (268435456 < attribValue.GetAsU32())
      {
         vector<NvAttribute> attribsToSet;
         attribValue.assign("0");
         NvAttribute updatedAttrib(attrib, attribValue, 4 /* schema version */);
         attribsToSet.push_back(updatedAttrib);
         schemingNvStore.SetNvAttributes(container, attribsToSet);
      }
   }
}

void MibUpgrade::UpgradeOperational4To5(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   TRACE_MSG("Operational NV store upgrade from 4 to 5 - configuring GATEWAY_VENDOR as NSN.");

   NvContainerDescriptor container(OPERATIONAL_CONTAINER, 0);

   NvAttributeDescriptor attrib("GATEWAY_VENDOR", 0);

   NvAttributeValue attribValue;

   vector<NvAttribute> attribsToSet;
   attribValue.assign("NSN");
   NvAttribute updatedAttrib(attrib, attribValue, 1 /* schema version */);
   attribsToSet.push_back(updatedAttrib);
   schemingNvStore.SetNvAttributes(container, attribsToSet);
}



void MibUpgrade::UpgradeOperational5To6(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   TRACE_MSG("Operational NV store upgrade from 5 to 6 - move some attributes to COMMISSIONING object.");

   const char * attributesToMove[] =
   {
      "CONFIGURATION_SERVER_1ST",
      "CONFIGURATION_SERVER_2ND",
      "CONFIGURATION_SERVER_3RD",
      "GATEWAY_VENDOR",
      "MTU",
      "DHCP",
      "UNIT_MAC_ADDRESS",
      "STATIC_IP_CONFIG_IP_ADDRESS",
      "STATIC_IP_CONFIG_NET_MASK",
      "STATIC_IP_CONFIG_GATEWAY",
      "IKE_SEND_INTERMEDIATE_CERTS",
      "IPSEC_NAT_T_PORT",
      NULL
   };

   NvContainerDescriptor fapContainer(OPERATIONAL_CONTAINER, 0);
   NvContainerDescriptor commissioningContainer(COMMISSIONING_CONTAINER, 0);
   vector<NvAttribute> attribsToSet;

   for( size_t idx = 0; attributesToMove[idx] != NULL; idx++)
   {
      NvAttributeDescriptor attrib( attributesToMove[idx], 0);
      NvAttributeValue attribValue;

      if (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(fapContainer, attrib, attribValue))
      {
         NvAttribute updatedAttrib(attrib, attribValue, 6 /* schema version */);
         attribsToSet.push_back(updatedAttrib);
      }

   }

   if( attribsToSet.size() > 0 )
   {
      schemingNvStore.SetNvAttributes(commissioningContainer, attribsToSet);
   }
}

void MibUpgrade::UpgradeOperational6To7(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   // This version just changes the default value for DYNAMIC_MODE_TOTAL_TX_POWER_LIMIT
   TRACE_MSG("Adjusting DYNAMIC_MODE_TOTAL_TX_POWER_LIMIT due to change in valid range");

   NvContainerDescriptor container(OPERATIONAL_CONTAINER, 0);

   NvAttributeDescriptor attrib("DYNAMIC_MODE_TOTAL_TX_POWER_LIMIT", 0);

   NvAttributeValue attribValue;

   if (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(container, attrib, attribValue))
   {
      // if the value is set to the default, update it to the new default
      if (attribValue.GetAsS32() > 15)
      {
         vector<NvAttribute> attribsToSet;
         attribValue.assign("10");
         NvAttribute updatedAttrib(attrib, attribValue, 7 /* schema version */);
         attribsToSet.push_back(updatedAttrib);
         schemingNvStore.SetNvAttributes(container, attribsToSet);
      }
   }
}

void MibUpgrade::UpgradeOperational7To8(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   // This version just changes the type (and name? tbd) of Config server attributes.
   TRACE_PRINTF("Operational NV store upgrade from 7 to 8 - Changing type of server attributes from IP Address to Url.");

   const char * oldName[] =
   {
      "CONFIGURATION_SERVER_1ST",
      "CONFIGURATION_SERVER_2ND",
      "CONFIGURATION_SERVER_3RD",
      NULL
   };
   const char * newName[] =
   {
      "LTE_SEC_GW_SERVER_1",
      "LTE_SEC_GW_SERVER_2",
      "LTE_SEC_GW_SERVER_3",
      NULL
   };

   NvContainerName container[2] =
   {
      NvContainerName(OPERATIONAL_CONTAINER),
      NvContainerName(COMMISSIONING_CONTAINER)
   };

   for( int i = 0; i < 2; i++)
   {
      NvContainerDescriptor containerDescriptor( container[i], 0);

      vector<NvAttribute> attribsToSet;

      for( size_t idx = 0; oldName[idx] != NULL; idx++)
      {
         NvAttributeDescriptor oldAttrib( oldName[idx], 0 /* schema version */);
         NvAttributeValue attribValue;

         if (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute( containerDescriptor, oldAttrib, attribValue))
         {
            TRACE_PRINTF("Upgrade %s/%s to %s" , container[i].c_str(), oldName[idx], newName[idx] );

            NvAttributeDescriptor newAttrib( newName[idx], 0 /* schema version */);
            NvAttribute updatedAttrib(newAttrib, attribValue, 1 /* schema version  **- must match version in XML -** */);
            attribsToSet.push_back(updatedAttrib);
         }
      }

      if( attribsToSet.size() > 0 )
      {
         schemingNvStore.SetNvAttributes( containerDescriptor, attribsToSet);

         attribsToSet.clear();
      }
   }
}

void MibUpgrade::UpgradeOperational8To9(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   // This upgrade is to fix Mantis 3070.
   // In essence, it may sometimes be necessary to re-run the "COMMISSIONING" upgrades
   // after upgrading from 1.1
   TRACE_PRINTF("Operational NV store upgrade from 8 to 9 - Conditional re-run of 'earlier' upgrades.");

   NvContainerDescriptor commissioningContainer( COMMISSIONING_CONTAINER, 0);

   bool commissioningObjectIntact =
      schemingNvStore.IsNvContainerPresent(commissioningContainer) &&
      schemingNvStore.GetNvAttributeNames(commissioningContainer).size();

   if(commissioningObjectIntact)
   {
      TRACE_PRINTF("Commissioning object intact, 8 to 9 upgrade NOT required.");
   }
   else
   {
      TRACE_PRINTF("Commissioning object not found: Creating it by repeating earlier upgrades steps 5to6 & 7to8.");

      TRACE_MSG("Operational NV store upgrade from 8 to 9 - move & rename some attributes.");

      //UpgradeOperational5To6(schemingNvStore);
      const char * attributesToMove[][2] =
      {
         { "CONFIGURATION_SERVER_1ST",       "LTE_SEC_GW_SERVER_1" },
         { "CONFIGURATION_SERVER_2ND",       "LTE_SEC_GW_SERVER_2" },
         { "CONFIGURATION_SERVER_3RD",       "LTE_SEC_GW_SERVER_3" },
         { "GATEWAY_VENDOR",                 "GATEWAY_VENDOR" },
         { "MTU",                            "MTU" },
         { "DHCP",                           "DHCP" },
         { "UNIT_MAC_ADDRESS",               "UNIT_MAC_ADDRESS" },
         { "STATIC_IP_CONFIG_IP_ADDRESS",    "STATIC_IP_CONFIG_IP_ADDRESS" },
         { "STATIC_IP_CONFIG_NET_MASK",      "STATIC_IP_CONFIG_NET_MASK" },
         { "STATIC_IP_CONFIG_GATEWAY",       "STATIC_IP_CONFIG_GATEWAY" },
         { "IKE_SEND_INTERMEDIATE_CERTS",    "IKE_SEND_INTERMEDIATE_CERTS" },
         { "IPSEC_NAT_T_PORT",               "IPSEC_NAT_T_PORT" },
         { NULL,                             NULL },
      };

      NvContainerDescriptor fapContainer(OPERATIONAL_CONTAINER, 0);
      NvContainerDescriptor commissioningContainer(COMMISSIONING_CONTAINER, 0);

      vector<NvAttribute> commissioningAttribsToSet;
      vector<NvAttribute> fapAttribsToSet;

      for( size_t idx = 0; attributesToMove[idx][0] != NULL; idx++)
      {
         NvAttributeDescriptor oldAttrib( attributesToMove[idx][0], 0);
         NvAttributeValue attribValue;

         if (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(fapContainer, oldAttrib, attribValue))
         {
            TRACE_PRINTF("Move FAP.0/%s to COMMISSIONING.0/%s", attributesToMove[idx][0], attributesToMove[idx][1]);

            NvAttributeDescriptor newAttrib( attributesToMove[idx][1], 0);

            NvAttribute updatedAttrib(newAttrib, attribValue, 6 /* schema version */);
            commissioningAttribsToSet.push_back(updatedAttrib);
         }

      }

      if( commissioningAttribsToSet.size() > 0 )
      {
         schemingNvStore.SetNvAttributes(commissioningContainer, commissioningAttribsToSet);
      }

      if( fapAttribsToSet.size() > 0 )
      {
         schemingNvStore.SetNvAttributes( fapContainer, fapAttribsToSet);
      }
   }
}

void MibUpgrade::UpgradeOperational9To10(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   // This version just changes the default and max value for NUMBER_OF_CELLS_TO_REPORT
   TRACE_MSG("Adjusting NUMBER_OF_CELLS_TO_REPORT due to change in valid range");

   NvContainerDescriptor container(OPERATIONAL_CONTAINER, 0);

   NvAttributeDescriptor attrib("NUMBER_OF_CELLS_TO_REPORT", 0);

   NvAttributeValue attribValue;

   if (NV_ATTRIBUTE_RESULT_OK == schemingNvStore.GetNvAttribute(container, attrib, attribValue))
   {
      // if the value is set to the default, update it to the new default
      if (attribValue.GetAsU32() > 16)
      {
         vector<NvAttribute> attribsToSet;
         attribValue.assign("16");
         NvAttribute updatedAttrib(attrib, attribValue, 10 /* schema version */);
         attribsToSet.push_back(updatedAttrib);
         schemingNvStore.SetNvAttributes(container, attribsToSet);
      }
   }
}

void MibUpgrade::UpgradeOperational10To11(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   TRACE_MSG("Operational NV store upgrade from 10 to 11 - adding REM_SCAN_ENABLE .");

   NvContainerDescriptor container(OPERATIONAL_CONTAINER, 0);

   NvAttributeDescriptor attrib("REM_SCAN_ENABLE", 0);

   NvAttributeValue attribValue;

   vector<NvAttribute> attribsToSet;
   attribValue.assign("1");
   NvAttribute updatedAttrib(attrib, attribValue, 11 /* schema version */);
   attribsToSet.push_back(updatedAttrib);
   schemingNvStore.SetNvAttributes(container, attribsToSet);
}

void MibUpgrade::UpgradeFactory1To2(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore)
{
   TRACE_MSG("Factory NV store upgrade from 1 to 2 - adding Manufacturer and OUI parameters.");
   NvContainerDescriptor container(FACTORY_CONTAINER, 0);

   NvAttributeDescriptor attrib("MANUFACTURER", 0);
   NvAttributeValue attribValue;
   vector<NvAttribute> attribsToSet;
   attribValue.assign("Radisys");
   NvAttribute updatedAttrib(attrib, attribValue, 2 /* schema version */);
   attribsToSet.push_back(updatedAttrib);
   schemingNvStore.SetNvAttributes(container, attribsToSet);

   NvAttributeDescriptor attrib1("OUI_OF_MANUFACTURER", 0);
   NvAttributeValue attribValue1;
   vector<NvAttribute> attribsToSet1;
   attribValue1.assign("000050");//Radisys OUI
   NvAttribute updatedAttrib1(attrib1, attribValue1, 2 /* schema version */);
   attribsToSet1.push_back(updatedAttrib1);
   schemingNvStore.SetNvAttributes(container, attribsToSet1);
}
