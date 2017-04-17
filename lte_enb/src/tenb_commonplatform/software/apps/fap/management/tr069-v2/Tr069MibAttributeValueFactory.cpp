///////////////////////////////////////////////////////////////////////////////
//
// Tr069MibAttributeValueFactory.cpp
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
#include <iostream>
#include <system/Trace.h>
#include <system/StringUtils.h>
#include <mobnet/GsmBandId.h>
#include <mobnet/RemScanStatusId.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069MibAttributeValueFactory.h"

#define INVLD_BOOL_VAL 2

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

const char* Tr069MibAttributeValueFactory::AlarmNotificationTypeStrArr[] = { "NewAlarm", "ChangedAlarm", "ClearedAlarm"};

shared_ptr<MibAttributeValue> Tr069MibAttributeValueFactory::FromDataModelValue( const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValue> mav;

   switch(getMibAttributeType(dmDef->mibAttrId))
   {
      case MIB_ATTRIBUTE_TYPE_U32:          mav = CreateU32( dmDef, dmValue);            break;
      case MIB_ATTRIBUTE_TYPE_U32ARRAY:     mav = CreateU32Array( dmDef, dmValue);       break;
      case MIB_ATTRIBUTE_TYPE_S32:          mav = CreateS32( dmDef, dmValue);            break;
      case MIB_ATTRIBUTE_TYPE_S32ARRAY:     mav = CreateS32Array( dmDef, dmValue);       break;
      case MIB_ATTRIBUTE_TYPE_STRING:       mav = CreateString( dmDef, dmValue);         break;
      case MIB_ATTRIBUTE_TYPE_STRINGARRAY:  mav = CreateStringArray( dmDef, dmValue);    break;
      case MIB_ATTRIBUTE_TYPE_ENUM:         mav = CreateEnum( dmDef, dmValue);           break;
      case MIB_ATTRIBUTE_TYPE_ENUMARRAY:    mav = CreateEnumArray( dmDef, dmValue);      break;
   }

   if(mav)
   {
      TRACE_PRINTF( "%s=%s (%s=%s)", dmDef->name.c_str(),  dmValue.c_str(), MibAttributeIdToString(dmDef->mibAttrId), mav->ToString().c_str() );
   }
   else
   {
      TRACE_PRINTF( "Failure: %s=%s (%s type incompatible?)", dmDef->name.c_str(),  dmValue.c_str(), MibAttributeIdToString(dmDef->mibAttrId) );
   }


   return mav;
}

bool Tr069MibAttributeValueFactory::ToDataModelValue( const ExtDMAttrDefinition * dmDef , string & dmValue, ExtDMAttrDataType & dmType )
{
   bool okStatus = false;

   switch( dmDef->type)
   {
      case INT:        okStatus = CreateDmInt( dmDef, dmValue, dmType);       break;
      case U_INT:      okStatus = CreateDmUInt( dmDef, dmValue, dmType);      break;
      case STRING:     okStatus = CreateDmString( dmDef, dmValue, dmType);    break;
      case BOOLEAN:    okStatus = CreateDmBoolean( dmDef, dmValue, dmType);   break;
      case DATE_TIME:  okStatus = CreateDmDateTime( dmDef, dmValue, dmType);  break;
      case DATA_TYPE:  //Considered as invalid Data Type
      default:  
                       {
                           dmType = DATA_TYPE;
                           break;
                       }
   }

   if(okStatus)
   {
      TRACE_PRINTF( "%s=%s (%s)", dmDef->name.c_str(),  dmValue.c_str(), MibAttributeIdToString(dmDef->mibAttrId) );
      TRACE_PRINTF( "Type of attribute %s = %d", dmDef->name.c_str(),  dmType );
   }
   else
   {
      TRACE_PRINTF( "Failure: %s=%s (%s type incompatible?)", dmDef->name.c_str(),  dmValue.c_str(), MibAttributeIdToString(dmDef->mibAttrId) );
   }

   return okStatus;
}

shared_ptr<MibAttributeValueU32> Tr069MibAttributeValueFactory::CreateU32(const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValueU32> mavU32;

   switch(dmDef->type)
   {
      case BOOLEAN:
      case STRING:
      case U_INT:
      case INT:
         {
            string mibValue;
            ConvertDataModel2Mib(dmDef, dmValue, mibValue);
            mavU32 = dynamic_pointer_cast<MibAttributeValueU32>( MibAttributeValue::Create(MIB_ATTRIBUTE_TYPE_U32, mibValue) );
         }
         break;

      default:
         break;
   }

   return mavU32;
}

shared_ptr<MibAttributeValueU32Array> Tr069MibAttributeValueFactory::CreateU32Array(const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValueU32Array> mavU32Array;

   switch(dmDef->type)
   {
      case BOOLEAN:
      case STRING:
      case U_INT:
      case INT:
         {
            string mibValue;
            ConvertCsvDataModel2Mib(dmDef, dmValue, mibValue);
            mavU32Array = dynamic_pointer_cast<MibAttributeValueU32Array>( MibAttributeValue::Create(MIB_ATTRIBUTE_TYPE_U32ARRAY, mibValue) );
         }
         break;

      default:
         break;
   }

   return mavU32Array;
}

shared_ptr<MibAttributeValueU32> Tr069MibAttributeValueFactory::CreateEnum(const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValueU32> mavU32;

   switch(dmDef->type)
   {
      case BOOLEAN:
      case STRING:
      case U_INT:
      case INT:
         {
            string mibValue;
            ConvertDataModel2Mib(dmDef, dmValue, mibValue);
            mavU32 = dynamic_pointer_cast<MibAttributeValueU32>( MibAttributeValue::Create(MIB_ATTRIBUTE_TYPE_U32, mibValue) );
         }
         break;

      default:
         break;
   }

   return mavU32;
}

shared_ptr<MibAttributeValueU32Array> Tr069MibAttributeValueFactory::CreateEnumArray(const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValueU32Array> mavU32Array;

   switch(dmDef->type)
   {
      case BOOLEAN:
      case STRING:
      case U_INT:
      case INT:
         {
            string mibValue;
            ConvertCsvDataModel2Mib( dmDef, dmValue, mibValue);
            mavU32Array = dynamic_pointer_cast<MibAttributeValueU32Array>( MibAttributeValue::Create(MIB_ATTRIBUTE_TYPE_U32ARRAY, dmValue) );
         }
         break;

      default:
         break;
   }

   return mavU32Array;
}

shared_ptr<MibAttributeValueS32> Tr069MibAttributeValueFactory::CreateS32(const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValueS32> mavS32;

   switch(dmDef->type)
   {
      case BOOLEAN:
      case STRING:
      case U_INT:
      case INT:
         {
            string mibValue;
            ConvertDataModel2Mib( dmDef, dmValue, mibValue);
            mavS32 = dynamic_pointer_cast<MibAttributeValueS32>( MibAttributeValue::Create(MIB_ATTRIBUTE_TYPE_S32, mibValue) );
         }
         break;

      default:
         break;
   }

   return mavS32;
}


shared_ptr<MibAttributeValueS32Array> Tr069MibAttributeValueFactory::CreateS32Array(const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValueS32Array> mavS32Array;

   switch(dmDef->type)
   {
      case BOOLEAN:
      case STRING:
      case U_INT:
      case INT:
         {
            string mibValue;
            ConvertCsvDataModel2Mib( dmDef, dmValue, mibValue);
            mavS32Array = dynamic_pointer_cast<MibAttributeValueS32Array>( MibAttributeValue::Create(MIB_ATTRIBUTE_TYPE_S32ARRAY, mibValue) );
         }
         break;

      default:
         break;
   }

   return mavS32Array;
}

shared_ptr<MibAttributeValueString> Tr069MibAttributeValueFactory::CreateString(const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValueString> mavString;

   mavString.reset( new MibAttributeValueString( dmValue) );

   return mavString;
}

shared_ptr<MibAttributeValueStringArray> Tr069MibAttributeValueFactory::CreateStringArray(const ExtDMAttrDefinition * dmDef , const string & dmValue)
{
   shared_ptr<MibAttributeValueStringArray> mavStringArray;

   vector<string> valueAsStringArray;

   char *valueStr= const_cast<char*>(dmValue.c_str());
   char *valueTockn=strtok(valueStr,",");
   while(valueTockn!=NULL)
   {
      valueAsStringArray.push_back(string(valueTockn));
      valueTockn=strtok(NULL,",");
   }

   mavStringArray.reset( new MibAttributeValueStringArray( valueAsStringArray) );

   return mavStringArray;
}

bool Tr069MibAttributeValueFactory::CreateDmUInt(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType)
{
   stringstream ss;
   bool createOk = false;

   MibDN dn = MibDN::GenerateMibDN(dmDef->mibDN);

   switch(getMibAttributeType(dmDef->mibAttrId))
   {
      case MIB_ATTRIBUTE_TYPE_ENUM:
      case MIB_ATTRIBUTE_TYPE_U32:
         {
            u32 mibValue;
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute( dn, dmDef->mibAttrId, mibValue);
            ss << mibValue;
            dmType = U_INT;
         }
         break;

      case MIB_ATTRIBUTE_TYPE_U32ARRAY:
      case MIB_ATTRIBUTE_TYPE_S32ARRAY:
         {
            std::vector<u32> mibValuesList;
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute( dn, dmDef->mibAttrId, mibValuesList);

            for(u32 i=0; i<mibValuesList.size();i++)
            {
               ss << mibValuesList[i];
               if(i < (mibValuesList.size() - 1))
               {
                  ss << ",";
               }
            }
            dmType = INT;
         }
         break;

      case MIB_ATTRIBUTE_TYPE_S32:
         {
            s32 mibValue;
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute( dn, dmDef->mibAttrId, mibValue);

            if(mibValue > 0)
            {
               ss << mibValue;
            }
            dmType = U_INT;
         }
         break;

      default:
         break;
   }

   if(ss.str().size())
   {
      ConvertMib2DataModel(dmDef, ss.str(), dmValue);
      createOk = true;
   }

   return createOk;
}

bool Tr069MibAttributeValueFactory::CreateDmInt(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType)
{
   stringstream ss;
   bool createOk = false;

   MibDN dn = MibDN::GenerateMibDN(dmDef->mibDN);

   switch(getMibAttributeType(dmDef->mibAttrId))
   {
      case MIB_ATTRIBUTE_TYPE_ENUM:
      case MIB_ATTRIBUTE_TYPE_U32:
         {
            u32 mibValue;
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute( dn, dmDef->mibAttrId, mibValue);
            ss << mibValue;
            dmType = U_INT;
         }
         break;

      case MIB_ATTRIBUTE_TYPE_S32:
         {
            s32 mibValue;
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute( dn, dmDef->mibAttrId, mibValue);

            ss << mibValue;
            dmType = INT;
         }
         break;
      case MIB_ATTRIBUTE_TYPE_S32ARRAY:
         {
            std::vector<s32> mibValuesList;
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute( dn, dmDef->mibAttrId, mibValuesList);

            for(u32 i=0; i<mibValuesList.size();i++)
            {
               ss << mibValuesList[i];
               if(i < (mibValuesList.size() - 1))
               {
                  ss << ",";
               }
            }
            dmType = INT;
         }
         break;

      default:
         break;
   }

   if(ss.str().size())
   {
      ConvertMib2DataModel(dmDef, ss.str(), dmValue);
      createOk = true;
   }

   return createOk;
}

bool Tr069MibAttributeValueFactory::CreateDmString(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType)
{
   bool createOk = true;

   MibDN dn = MibDN::GenerateMibDN(string(dmDef->mibDN));

   switch(getMibAttributeType(dmDef->mibAttrId))
   {
      case MIB_ATTRIBUTE_TYPE_ENUMARRAY:
      case MIB_ATTRIBUTE_TYPE_U32ARRAY:
         {
            string mibCsv;
            Tr069Application::GetInstance().GetMibCache().GetMibAttributeAsString( dn, dmDef->mibAttrId, mibCsv);

            ConvertCsvMib2DataModel(dmDef, mibCsv, dmValue);
         }
         break;

      case MIB_ATTRIBUTE_TYPE_ENUM:
      case MIB_ATTRIBUTE_TYPE_U32:
      case MIB_ATTRIBUTE_TYPE_S32:
      case MIB_ATTRIBUTE_TYPE_STRING:
      case MIB_ATTRIBUTE_TYPE_STRINGARRAY:
         {
            string mibValue;
            Tr069Application::GetInstance().GetMibCache().GetMibAttributeAsString( dn, dmDef->mibAttrId, mibValue);

            ConvertMib2DataModel(dmDef, mibValue, dmValue);
         }
         break;

      default:
         createOk = false;
         break;
   }

   dmType = STRING;
   return createOk;
}

bool Tr069MibAttributeValueFactory::CreateDmBoolean( const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType)
{
   stringstream ss;
   bool createOk = true;

   MibDN dn = MibDN::GenerateMibDN(string(dmDef->mibDN));

   switch(getMibAttributeType(dmDef->mibAttrId))
   {
      case MIB_ATTRIBUTE_TYPE_ENUM:
      case MIB_ATTRIBUTE_TYPE_U32:
      case MIB_ATTRIBUTE_TYPE_S32:
         {
            string mibValue;
            Tr069Application::GetInstance().GetMibCache().GetMibAttributeAsString( dn, dmDef->mibAttrId, mibValue);

            ConvertMib2DataModel(dmDef, mibValue, dmValue);
         }
         break;

      default:
         createOk = false;
         break;
   }
   dmType = BOOLEAN;

   return createOk;
}

bool Tr069MibAttributeValueFactory::CreateDmDateTime( const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType)
{
   stringstream ss;
   bool createOk = true;

   MibDN dn = MibDN::GenerateMibDN( string(dmDef->mibDN) );

   switch(getMibAttributeType(dmDef->mibAttrId))
   {
      case MIB_ATTRIBUTE_TYPE_U32:
         {
            u32 unixTime;
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute( dn, dmDef->mibAttrId, unixTime);

            TimeWrap timeWrap(unixTime);

            dmValue = timeWrap.ToString();
         }
         break;

      case MIB_ATTRIBUTE_TYPE_STRING:
         {
            Tr069Application::GetInstance().GetMibCache().GetMibAttribute( dn, dmDef->mibAttrId, dmValue);
         }
         break;

      default:
         createOk = false;
         break;
   }
   dmType = DATE_TIME;
   return createOk;
}



void Tr069MibAttributeValueFactory::ConvertCsvDataModel2Mib( const ExtDMAttrDefinition * dmDef , const string & dataModelValues, string &mibValues )
{
   mibValues.clear();

   stringstream conversionStream;

   conversionStream << dataModelValues;
   while (conversionStream.good())
   {
      if(mibValues.size())
      {
         mibValues.append(",");
      }

      std::string dataModelValue;
      std::getline(conversionStream, dataModelValue, ',');

      string mibValue;
      ConvertDataModel2Mib(dmDef, dataModelValue, mibValue);
      mibValues.append(mibValue);
   }
}

void Tr069MibAttributeValueFactory::ConvertDataModel2Mib( const ExtDMAttrDefinition * dmDef , const string & dataModelValue, string &mibValue )
{
   stringstream strStream;

   switch(dmDef->type)
   {
      case BOOLEAN:
         {
            if((0 == strcasecmp(dataModelValue.c_str(),"true"))|| (dataModelValue == "1"))
            {
               strStream << 1;
            }
            else if((0 == strcasecmp(dataModelValue.c_str(),"false"))|| (dataModelValue == "0"))
            {
               strStream << 0;
            }
            else
            {
               strStream << INVLD_BOOL_VAL;
            }
         }
         break;

      default:
         break;
   }

   switch( dmDef->mibAttrId )
   {
      case PARAM_ID_ALARM_REPORTING_MECHANISM:
         {
            AlarmReportingMechanism alarmReportingMechanism;
            if( AlarmReportingMechanismFromString(dataModelValue, alarmReportingMechanism ) )
            {
               strStream << u32(alarmReportingMechanism);
            }
         }
         break;

      default:
         break;
   }

   if(strStream.str().empty())
   {
      mibValue = dataModelValue;
   }
   else
   {
      mibValue = strStream.str();
   }

}

void Tr069MibAttributeValueFactory::ConvertCsvMib2DataModel( const ExtDMAttrDefinition * dmDef , const string & mibValues, string & dataModelValues )
{
   dataModelValues.clear();

   stringstream conversionStream;

   conversionStream << mibValues;
   while (conversionStream.good())
   {
      if(dataModelValues.size())
      {
         dataModelValues.append(",");
      }

      std::string mibValue;
      std::getline(conversionStream, mibValue, ',');

      string dataModelValue;
      ConvertMib2DataModel(dmDef, mibValue, dataModelValue);
      dataModelValues.append(mibValue);
   }
}


void Tr069MibAttributeValueFactory::ConvertMib2DataModel( const ExtDMAttrDefinition * dmDef , const string & mibValue, string & dataModelValue)
{
   stringstream strStream;

   switch(dmDef->type)
   {
      case BOOLEAN:
         {
            strStream << ((mibValue == "0")? "false" : "true");
         }
         break;

      default:
         break;
   }

   switch( dmDef->mibAttrId )
   {
      case PARAM_ID_ALARM_PERCEIVED_SEVERITY:
      case PARAM_ID_TR069_ALARM_STATUS:
         {

            u32 severity;
            if( StringUtils::ConvertStringToInteger(mibValue,severity))
            {
               strStream << AlarmPerceivedSeverityToString( AlarmPerceivedSeverity(severity) );
            }
            else
            {
               TRACE_PRINTF("AlarmPerceivedSeverity conversion not possible (%s)",mibValue.c_str());
            }
         }
         break;
      case PARAM_ID_ALARM_NOTIFICATION_TYPE:
         {
            u32 notification_type;
            if( StringUtils::ConvertStringToInteger(mibValue,notification_type))
            {
               strStream << AlarmNotificationTypeStrArr[notification_type];
            }
            else
            {
               TRACE_PRINTF("Alarm Notification Type conversion not possible (%s)",mibValue.c_str());
            }
         }
         break;
      case PARAM_ID_ALARM_EVENT_TYPE:
         {
            u32 event_type;
            if( StringUtils::ConvertStringToInteger(mibValue,event_type))
            {
               strStream << AlarmEventTypeToString( AlarmEventType(event_type) );
            }
            else
            {
               TRACE_PRINTF("AlarmEventType conversion not possible (%s)",mibValue.c_str());
            }

         }
         break;
      case PARAM_ID_ALARM_REPORTING_MECHANISM:
         {
            u32 alarmReportingMechanism;
            if( StringUtils::ConvertStringToInteger(mibValue,alarmReportingMechanism))
            {
               strStream << AlarmReportingMechanismToString( AlarmReportingMechanism(alarmReportingMechanism) );
            }
            else
            {
               TRACE_PRINTF("AlarmReportingMechanism conversion not possible (%s)",mibValue.c_str());
            }
         }
         break;
      case PARAM_ID_UP_TIME:
         {
            Tr069Application &app = Tr069Application::GetInstance();
            uptime_t now = app.m_uptime.GetMillisecs();
            u32 upTime = now/1000;
            strStream << upTime;
         }
         break;
      case PARAM_ID_NTP_CURRENTLOCALTIME:
         {
            TRACE_PRINTF("%s:%d",__func__, __LINE__);
            char dateStr[64];
            memset (dateStr, '\0', sizeof (dateStr));
            threeway::TimeWrap timeNow;
            timeNow.GetDateStr (dateStr, sizeof(dateStr));
            strStream << dateStr;
         }
         break;
      default:
         break;
   }

   if(strStream.str().empty())
   {
      dataModelValue = mibValue;
   }
   else
   {
      dataModelValue = strStream.str();
   }
}

}

