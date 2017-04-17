///////////////////////////////////////////////////////////////////////////////
//
// MibDN.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include<string.h>
#include<sstream>
#include <system/Trace.h>
#include <system/Regex.h>
#include <system/SerialisationUtils.h>
#include "MibObjectClass.h"
#include <mib-common/MIOAutoManage.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibDN.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibDN MibDN::GenerateMibDN(const string & inputStr)
{
   string str(inputStr);

   MibDN dn;

   // Some help! (Makes prefix optional)
   if( str.substr(0, 3) != "FAP" )
   {
      str.insert(0,"FAP.0.");
   }

   // Rdn format: name.#
   threeway::Regex rdnRegex("[a-zA-Z][a-zA-Z0-9_]*[.][0-9]+[.]?");

   while(str.size())
   {
      u16 matchedLength = 0;

      if( rdnRegex.Compare(str.c_str(), &matchedLength) )
      {
         string matchedString = str.substr(0, matchedLength);
         str.erase(0, matchedLength);

         size_t dotPos = matchedString.find_first_of( '.' );
         RSYS_ASSERT(dotPos > 0);

         string rdnClass("MIB_OBJECT_CLASS_");
         rdnClass.append(matchedString.substr(0, dotPos) );

         u16 moi = strtoul ( matchedString.substr(dotPos + 1).c_str(), NULL, 10 );

         for(int i = 0; i < NUM_MIB_OBJECT_CLASSES; ++i)
         {
            MibObjectClass moc = MibObjectClass(i);

            if( 0 == rdnClass.compare( MibObjectClassToString(moc) ) )
            {
               MibRDN mibRdn(moc, moi);

               dn.push_back(mibRdn);
               break;
            }
         }
      }
      else
      {
         str.clear();
      }
   }
   return dn;
}


MibDN MibDN::GenerateMibDN(MibObjectClass mibObjectClass, u32 mibObjectInstance)
{
   ENTER();

   MibDN dn;

   switch(mibObjectClass)
   {
      case MIB_OBJECT_CLASS_FAP:
         {
            MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, mibObjectInstance);
            dn.push_back(fapRdn);
            TRACE_PRINTF("MibDN::GenerateMibDN -Trying to create MibDn %d",  mibObjectClass);
         }
         break;
      case MIB_OBJECT_CLASS_REM_LTE:
         {
            MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(fapRdn);
            MibRDN remRdn(MIB_OBJECT_CLASS_REM_LTE, mibObjectInstance);
            dn.push_back(remRdn);
            TRACE_PRINTF("MibDN::GenerateMibDN -Trying to create MibDn %d",  mibObjectClass);
         }
         break;

      case MIB_OBJECT_CLASS_COMMISSIONING:
         {
            MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(fapRdn);
            MibRDN commissioningRdn(MIB_OBJECT_CLASS_COMMISSIONING, mibObjectInstance);
            dn.push_back(commissioningRdn);
            TRACE_PRINTF("MibDN::GenerateMibDN -Trying to create MibDn %d",  mibObjectClass);
         }
         break;

      case MIB_OBJECT_CLASS_FAP_LTE:
         {
            MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(fapRdn);
            MibRDN faplteRdn(MIB_OBJECT_CLASS_FAP_LTE, mibObjectInstance);
            dn.push_back(faplteRdn);
            TRACE_PRINTF("MibDN::GenerateMibDN -Trying to create MibDn %d",  mibObjectClass);
         }
         break;

      case MIB_OBJECT_CLASS_COMMISSIONING_LTE:
         {
            MibRDN fapRdn(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(fapRdn);
            MibRDN commissioninglteRdn(MIB_OBJECT_CLASS_COMMISSIONING_LTE, mibObjectInstance);
            dn.push_back(commissioninglteRdn);
            TRACE_PRINTF("MibDN::GenerateMibDN -Trying to create MibDn %d",  mibObjectClass);
         }
         break;

      case MIB_OBJECT_CLASS_TR196_CURRENT_ALARM:
         {
            MibRDN alarmCurRdn(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(alarmCurRdn);
            MibRDN alarmCurrRdn(MIB_OBJECT_CLASS_TR196_CURRENT_ALARM, mibObjectInstance);
            dn.push_back(alarmCurrRdn);
            TRACE_PRINTF("MibDN::GenerateMibDN for alarm -Trying to create MibDn %d",  mibObjectClass);
         }
         break;

      case MIB_OBJECT_CLASS_TR196_SUPPORTED_ALARM:
         {
            MibRDN alarmRdn(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(alarmRdn);
            MibRDN alarmSuppRdn(MIB_OBJECT_CLASS_TR196_SUPPORTED_ALARM, mibObjectInstance);
            dn.push_back(alarmSuppRdn);
            TRACE_PRINTF("MibDN::GenerateMibDN for alarm -Trying to create MibDn %d",  mibObjectClass);
         }
         break;

      case MIB_OBJECT_CLASS_TR196_EXPEDITED_EVENT:
         {
            MibRDN alarmERdn(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(alarmERdn);
            MibRDN alarmExpRdn(MIB_OBJECT_CLASS_TR196_EXPEDITED_EVENT, mibObjectInstance);
            dn.push_back(alarmExpRdn);
            TRACE_PRINTF("MibDN::GenerateMibDN for alarm -Trying to create MibDn %d",  mibObjectClass);
         }
         break;
      case MIB_OBJECT_CLASS_PERF_MGMT:
         {
            MibRDN perfMgmtRDN(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(perfMgmtRDN);
            MibRDN perfMgmtExpRDN(MIB_OBJECT_CLASS_PERF_MGMT, mibObjectInstance);
            dn.push_back(perfMgmtExpRDN);
            TRACE_PRINTF("MibDN::GenerateMibDN for performance management -Trying to create MibDn %d",  mibObjectClass);
         }
         break;
      case MIB_OBJECT_CLASS_IP_INTERFACE:
         {
            MibRDN fapRDN(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(fapRDN);
            MibRDN ipIntfRDN(MIB_OBJECT_CLASS_IP_INTERFACE, mibObjectInstance);
            dn.push_back(ipIntfRDN);
            TRACE_PRINTF("MibDN::GenerateMibDN for IP Interface -Trying to create MibDn %d",  mibObjectClass);
         }
         break;
      case MIB_OBJECT_CLASS_REM_UMTS_WCDMA:
         {
            MibRDN fapRDN(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(fapRDN);
            MibRDN remRDN(MIB_OBJECT_CLASS_REM_UMTS_WCDMA, mibObjectInstance);
            dn.push_back(remRDN);
            TRACE_PRINTF("MibDN::GenerateMibDN for rem UMTS -Trying to create MibDn %d",  mibObjectClass);
         }
         break;
      case MIB_OBJECT_CLASS_REM_SCANNED_WCDMA_CELL:
         {
            MibRDN fapRDN(MIB_OBJECT_CLASS_FAP, 0);
            dn.push_back(fapRDN);
            MibRDN remCellRDN(MIB_OBJECT_CLASS_REM_SCANNED_WCDMA_CELL, mibObjectInstance);
            dn.push_back(remCellRDN);
            TRACE_PRINTF("MibDN::GenerateMibDN for rem UMTS CellInfo -Trying to create MibDn %d",  mibObjectClass);
         }
         break;
      default:
         {
            MibObjectClass objClass = mibObjectClass;
            if(MIOAutoManage::GetInstance().isMibObjectClassPresent(objClass))
            {
               MibRDN fapRDN(MIB_OBJECT_CLASS_FAP, 0);
               dn.push_back(fapRDN);
               MibRDN rDN(mibObjectClass, mibObjectInstance);
               dn.push_back(rDN);
               TRACE_PRINTF("MibDN generated MibDN for %s : %d",
                     MibObjectClassToString(mibObjectClass),mibObjectInstance);
            }
            else
            {
               TRACE_PRINTF("MibDN failed to create  MibDN for %s ",MibObjectClassToString(mibObjectClass));
               RSYS_ASSERT(false);
            }
            break;
         }
   }
   RETURN(dn);
}

MibDN MibDN::GenerateMibDN(MibDN &dn, MibObjectClass mibObjectClass, u32 mibObjectInstance)
{
   MibDN newDn = dn;
   MibRDN mibRDN(mibObjectClass,mibObjectInstance);
   newDn.push_back(mibRDN);
   TRACE_PRINTF("Trying to create MibDn %d",  mibObjectClass);
   return newDn;
}

std::string MibDN::ToString() const
{
   ENTER();

   ostringstream stream;

   stream << (*this);

   RETURN(stream.str());
}

s32 MibDN::Serialise(u8* data, u32 dataMaxBytes) const
{
   ENTER();

   // Preconditions.
   RSYS_ASSERT(dataMaxBytes > 2048); // Should be plenty :)

   u32 numRdns = size();
   SerialiseIt(numRdns, data);
   s32 totalLen = 4; // numRdns

   for(const_iterator iter = begin(); iter < end(); ++iter)
   {
      s32 len = iter->Serialise(data, dataMaxBytes - totalLen);
      RSYS_ASSERT(len > 0);
      totalLen += len;
      data += len;
   }
   RETURN(totalLen);
}

bool MibDN::DeSerialise(const u8* data, u32 dataLen)
{
   ENTER();

   clear();

   u32 numRdns;
   if(!dataLen)
   {
      TRACE_PRINTF("Error: DeSerialise something without a valid buffer?");
   }
   DeSerialiseIt(numRdns, data);
   RSYS_ASSERT_PRINTF(dataLen == 4 + (numRdns * 8), "dataLen=%"PRIu32, dataLen);

   bool deSerialiseSuccess;
   for(u32 i = 0; i < numRdns; i++)
   {
      MibRDN mibRdn;
      deSerialiseSuccess = mibRdn.DeSerialise(data, 8 /* it's always 8 */);
      RSYS_ASSERT(deSerialiseSuccess);
      data += 8;
      push_back(mibRdn);
   }
   RETURN(true);
}

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator<< (std::ostream& os, const MibDN& s)
{
   ENTER();

   // Print out the contents of s interspersed with '.'
   if (!s.empty())
   {
      std::ostream_iterator<MibRDN> output_1 (os, ".");
      std::copy(s.begin(), s.end()-1, output_1);
      os << *(s.end()-1);
   }

   RETURN(os);
}
s32 MibDN::GetMibObjectInstanceNum(MibDN dN,s32 childIdx)
{
   TRACE_PRINTF("%s: %d",__FUNCTION__,__LINE__);
   return GetMibObjectInstanceNum(dN.ToString(),childIdx);
}

s32 MibDN::GetMibObjectInstanceNum(std::string dNString,s32 childIdx)
{
   TRACE_PRINTF("%s %d ",__FUNCTION__,__LINE__);
   std::string dn(dNString.c_str());
   char* dnchar = const_cast<char*>(dn.c_str());
   char * token = strtok(dnchar,".");
   bool skip=true;
   std::vector<s32> instances;
   while(token != NULL)
   {
      if(!skip)
      {
         instances.push_back(atoi(token));
      }
            skip=!skip;
      token = strtok(NULL,".");
   }
   if( -1 == childIdx)
   {
      childIdx=instances.size();
   }
   if((u32)childIdx > instances.size())
   {
      return -1;
   }
   else
   {
      return(instances.at(childIdx));
   }
}

