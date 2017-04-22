
///////////////////////////////////////////////////////////////////////////////
//
// MibHelper.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <sstream> // ostringstream

#include <string.h>

#include <system/Trace.h>
#include <system/ConfigurationFile.h>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibHelper.h"

#define MAX_DIR_LEN 50

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<MibManager> MibHelper::s_mibManager;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibAttributeIds MibHelper::FindAllMatchingMibAttributeIds(const string& val, bool (* matcher)(const std::string &, const std::string &))
{
   const char * pName;
   MibAttributeIds ids;
   string lowerMatchString = val;
   u32 i, j;

   //make the search string lower case
   for (j = 0; j < lowerMatchString.size(); j++)
   {
      lowerMatchString.replace(j, 1, 1, tolower(lowerMatchString.at(j)));
   }
   //TRACE("MatchString", lowerMatchString.c_str());

   for(i = 0; i < NUM_MIB_ATTR_IDS; i++)
   {
      pName = getMibAttributeName((MibAttributeId)i);
      string lowerString = string(pName);
      for (j = 0; j < lowerString.size(); j++)
      {
         lowerString.replace(j, 1, 1, tolower(lowerString.at(j)));
      }
      //TRACE_PRINTF("LowerString %d %s %s", i, pName, lowerString.c_str());
      if(matcher(lowerString,lowerMatchString))
      {
         TRACE_PRINTF("Found Match, adding parameter %d %s", i, getMibAttributeName((MibAttributeId)i));
         ids.insert((MibAttributeId)i);
      }
   }
   return ids;
}

bool MibHelper::LooseMatcher(const std::string & haystack, const std::string & needle)
{
   return(haystack.find(needle) != string::npos);
}

bool MibHelper::ExactMatcher(const std::string & haystack, const std::string & needle)
{
   return(haystack == needle);
}

void MibHelper::BuildMoTree(shared_ptr<MibManager> mibManager)
{
   u16  cellIdx;
   ENTER();

   s_mibManager = mibManager;

   // Create a FAP object.
   // If there are child objects in the operational NV store, the call to CreateObject() will ripple through and create them.
   MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
   MibDN rootDn;
   TRACE_PRINTF("MibHelper::BuildMoTree -Trying to send createObj for FAP %s",rootDn.ToString().c_str());
   s_mibManager->CreateObject(rootDn, fapRdn);

   MibDN fapDn;
   fapDn.push_back(fapRdn);

   // Create a child COMMISSIONING object.  This is from the operational NV store so *may* have already been created.
   MibRDN commissioningRdn(MIB_OBJECT_CLASS_COMMISSIONING, 0);
   MibDN commissioningDn = fapDn;
   commissioningDn.push_back(commissioningRdn);
   weak_ptr<MibObject> commissioningObject = s_mibManager->FindMibObject(commissioningDn);
   if(commissioningObject.lock() == NULL)
   {
      s_mibManager->CreateObject(fapDn, commissioningRdn);
   }

   MibDN faplteDn = fapDn;
   for (cellIdx=0; cellIdx < s_mibManager->numOfCells; cellIdx++)
   {
      MibRDN faplteRdn(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);
      MibDN tmpDn = fapDn;
      tmpDn.push_back(faplteRdn);
      weak_ptr<MibObject> faplteObject = s_mibManager->FindMibObject(tmpDn);
      if(faplteObject.lock() == NULL)
      {
         s_mibManager->CreateObject(fapDn, faplteRdn);
      }
   }

   // Create a child COMMISSIONING_LTE object.  This is from the operational NV store so *may* have already been created.
   MibRDN commissioninglteRdn(MIB_OBJECT_CLASS_COMMISSIONING_LTE, 0);
   MibDN commissioninglteDn = fapDn;
   commissioninglteDn.push_back(commissioninglteRdn);
   weak_ptr<MibObject> commissioninglteObject = s_mibManager->FindMibObject(commissioninglteDn);
   if(commissioninglteObject.lock() == NULL)
   {
      s_mibManager->CreateObject(fapDn, commissioninglteRdn);
   }

   // Create LTE REM object for holding LTE REM configuration attributes
   MibRDN remLteRdn(MIB_OBJECT_CLASS_REM_LTE, 0);
   MibDN remLteDn = fapDn;
   remLteDn.push_back(remLteRdn);
   weak_ptr<MibObject> remLteObject = s_mibManager->FindMibObject(remLteDn);
   if(remLteObject.lock() == NULL)
   {
      s_mibManager->CreateObject(fapDn, remLteRdn);
   }

   // Create WCDMA REM object for holding WCDMA REM configuration attributes
   MibRDN remWcdmaRdn(MIB_OBJECT_CLASS_REM_UMTS_WCDMA, 0);
   MibDN remWcdmaDn = fapDn;
   remWcdmaDn.push_back(remWcdmaRdn);
   weak_ptr<MibObject> remWcdmaObject = s_mibManager->FindMibObject(remWcdmaDn);
   if(remWcdmaObject.lock() == NULL)
   {
      s_mibManager->CreateObject(fapDn, remWcdmaRdn);
   }

   /* Create IP interface and IPv4 address MIOs */
   MibRDN ipIntfRdn(MIB_OBJECT_CLASS_IP_INTERFACE, 0);
   MibDN ipIntfDn = fapDn;
   ipIntfDn.push_back(ipIntfRdn);
   weak_ptr<MibObject> ipIntfObject = s_mibManager->FindMibObject(ipIntfDn);
   if (ipIntfObject.lock() == NULL)
   {
      s_mibManager->CreateObject(fapDn, ipIntfRdn);
   }

   MibRDN ipv4AddrRdn(MIB_OBJECT_CLASS_IP_INTERFACE_IPV4_ADDRESS, 0);
   MibDN ipv4AddrDn = ipIntfDn;
   ipv4AddrDn.push_back(ipv4AddrRdn);
   weak_ptr<MibObject> ipv4AddrObject = s_mibManager->FindMibObject(ipv4AddrDn);
   if (ipIntfObject.lock() == NULL)
   {
      s_mibManager->CreateObject(ipIntfDn, ipv4AddrRdn);
   }
   else
   {
      RSYS_ASSERT(false);
   }
//////////////////// for ipv6///////////////////////////

   MibRDN ipv6AddrRdn1(MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS, 0);
   MibDN ipv6AddrDn1 = ipIntfDn;
   ipv6AddrDn1.push_back(ipv6AddrRdn1);
   weak_ptr<MibObject> ipv6AddrObject1 = s_mibManager->FindMibObject(ipv6AddrDn1);
   if (ipIntfObject.lock() == NULL)
   {
      s_mibManager->CreateObject(ipIntfDn, ipv6AddrRdn1);
   }
   else
   {
      RSYS_ASSERT(false);
   }

   MibRDN ipv6AddrRdn2 (MIB_OBJECT_CLASS_IP_INTERFACE_IPV6_ADDRESS, 1);
   MibDN ipv6AddrDn2 = ipIntfDn;
   ipv6AddrDn2.push_back(ipv6AddrRdn2);
   weak_ptr<MibObject> ipv6AddrObject2 = s_mibManager->FindMibObject(ipv6AddrDn2);
   if (ipIntfObject.lock() == NULL)
   {
      s_mibManager->CreateObject(ipIntfDn, ipv6AddrRdn2);
   }
   else
   {
      RSYS_ASSERT(false);
   }

   EXIT();
}

void MibHelper::ApplyDeveloperMibAttributes()
{
   ENTER();

   ConfigurationFile developerFile("developer", s_mibManager->m_sOamConfigFilesDir.c_str());

   if(developerFile.FileExists())
   {
      developerFile.ReadConfigurationFile();

      vector<string> params = developerFile.GetParameters();
      string paramValue;
      MibAttributeValues attrValslte;
      MibAttributeValues attrValsltefactory;
      MibAttributeValues attrValsltecommissioning;

      for(vector<string>::const_iterator iter = params.begin(); iter != params.end(); ++iter)
      {
         MibAttributeIds ids = FindAllMatchingMibAttributeIds(*iter, &ExactMatcher);
         if(ids.size() == 1)
         {
            paramValue = developerFile.GetStringParameter((*iter).c_str());
            if(paramValue.length() > 0)
            {
               MibAttributeId id = *(ids.begin());
               MibAttributeType type = getMibAttributeType(id);
               shared_ptr<MibAttributeValue> attrValue = MibAttributeValue::Create(type, paramValue);
               attrValslte.AddAttribute(id, attrValue);
               TRACE_PRINTF("MibHelper::DeveloperFile - MIB_OBJECT_CLASS_FAP_LTE");
            }
         }
      }

      if(attrValslte.GetAttributeCount() > 0)
      {
         MibAttrValidationFailures failures = s_mibManager->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrValslte);
         if(failures.size() == 0)
         {
            s_mibManager->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE), attrValslte);
         }
         else
         {
            TRACE_LEV(TRACE_WARNING, "MIB attributes of FAP_LTE in 'developer' file failed validation", failures.ToString());
         }
      }
      if(attrValsltefactory.GetAttributeCount() > 0)
      {
         MibAttrValidationFailures failuresltecommissioning = s_mibManager->ValidateAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING_LTE), attrValsltecommissioning);
         if(failuresltecommissioning.size() == 0)
         {
            s_mibManager->SetAttributes(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING_LTE), attrValsltecommissioning);
         }
         else
         {
            TRACE_LEV(TRACE_WARNING, "MIB attributes of COMMISSIONING_LTE in 'developer' file failed validation", failuresltecommissioning.ToString());
         }
      }
   }

   EXIT();
}

MibDN MibHelper::GetMibObjectDn(MibAttributeId id)
{
   ENTER();
   TRACE_PRINTF("MibHelper::GetMibObjectDn Inside getMib dn");

   MibDN objectDn;

   MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
   objectDn.push_back(fapRdn);

   switch(id)
   {
#if 0
      case PARAM_ID_HARDWARE_TYPE:
      case PARAM_ID_HARDWARE_REVISION:
      case PARAM_ID_HARDWARE_MOD_STATE:
      case PARAM_ID_OSC_DAC:
      case PARAM_ID_OSC_DAC_SLOPE_PPT_PER_BIT:
      case PARAM_ID_LONG_SERIAL_NUMBER:
#endif
      case PARAM_ID_MANUFACTURER:
      case PARAM_ID_OUI_OF_MANUFACTURER:
      case PARAM_ID_PRODUCT_CLASS:
         {
            MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
            objectDn.push_back(fapRdn);
            TRACE_PRINTF("MibHelper::GetMibObjectDn - MIB_OBJECT_CLASS_FAP");
         }
         break;

      case PARAM_ID_IKE_SA_LIFETIME:
      case PARAM_ID_IKE_DPD_TRIES:
      case PARAM_ID_IPSEC_NAT_T_PORT:
      case PARAM_ID_IPSEC_ENCRYPTION_3DES_ENABLE:
      case PARAM_ID_IPSEC_ENCRYPTION_AES_ENABLE:
      case PARAM_ID_IPSEC_ENCRYPTION_AES128_ENABLE:
      case PARAM_ID_IPSEC_ENCRYPTION_NULL_ENABLE:
      case PARAM_ID_IPSEC_SA_LIFETIME:
      case PARAM_ID_GATEWAY_VENDOR:
         {
            MibRDN commissioningRdn(MIB_OBJECT_CLASS_COMMISSIONING, 0);
            objectDn.push_back(commissioningRdn);
            TRACE_PRINTF("MibHelper::GetMibObjectDn - MIB_OBJECT_CLASS_COMMISSIONING");
         }
         break;

      case PARAM_ID_LTE_IN_SERVICE_HANDLING:
      case PARAM_ID_LTE_REM_SCAN_ON_BOOT:
      case PARAM_ID_LTE_PERIODIC_SCAN_MODE:
         {
            MibRDN faplteRdn(MIB_OBJECT_CLASS_FAP_LTE, 0);
            objectDn.push_back(faplteRdn);
            TRACE_PRINTF("MibHelper::GetMibObjectDn - MIB_OBJECT_CLASS_FAP_LTE");
         }
         break;
      default:
         {
            string str_faplteparam = MibAttributeIdToString(id);
            TRACE_PRINTF("MibHelper::GetMibObjectDn Value of faplteparam = %s",str_faplteparam.c_str());
            size_t str_found = str_faplteparam.rfind("PARAM_ID_LTE_");
            TRACE_PRINTF("MibHelper::GetMibObjectDn Value of faplteparamcheck = %d",str_found);
            if(str_found!=string::npos)
            {
               MibRDN faplteRdn(MIB_OBJECT_CLASS_FAP_LTE, 0);
               objectDn.push_back(faplteRdn);
               TRACE_PRINTF("MibHelper::GetMibObjectDn - MIB_OBJECT_CLASS_FAP_LTE");
            }
            else
            {
               TRACE_PRINTF("MibHelper::GetMibObjectDn - Not a MIB_OBJECT_CLASS_FAP_LTE Parameter");
            }

         }
         break;

   }

   RETURN(objectDn);
}

boost::shared_ptr<MibAttributeValue> MibHelper::GetMibAttributeDirect( const MibDN& moDn, MibAttributeId mibAttributeId)
{
   RSYS_ASSERT(s_mibManager != NULL);

   MibAttributeIds attributeIds;
   attributeIds.insert(mibAttributeId);
   MibAttributeValues mibAttributeValues;
   s_mibManager->GetAttributes(moDn,
         attributeIds,
         mibAttributeValues);
   shared_ptr<MibAttributeValue> value;
   if(mibAttributeValues.GetAttributeCount() == 1)
   {
      value = mibAttributeValues.GetAttributeValue(mibAttributeId);
   }

   return value;
}

boost::shared_ptr<MibAttributeValue> MibHelper::GetMibAttributeDirect(MibAttributeId mibAttributeId)
{
   MibDN moDn = MibHelper::GetMibObjectDn(mibAttributeId);

   return GetMibAttributeDirect( moDn, mibAttributeId);
}

bool MibHelper::GetMibAttributeDirectAsString(const MibDN& moDn,
      MibAttributeId mibAttributeId,
      std::string& value)
{
   ostringstream stream;
   value.clear();

   shared_ptr<MibAttributeValue> attrValue = GetMibAttributeDirect(moDn, mibAttributeId);
   if(attrValue != NULL)
   {
      value = attrValue->GetValueAsString();
      return true;
   }

   return false;
}


bool MibHelper::GetMibAttributeDirectAsString(MibAttributeId mibAttributeId,
      std::string& value)
{
   MibDN moDn = MibHelper::GetMibObjectDn(mibAttributeId);

   return GetMibAttributeDirectAsString( moDn, mibAttributeId, value);
}
