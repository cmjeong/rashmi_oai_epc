///////////////////////////////////////////////////////////////////////////////
//
// TR069DataModelManager.cpp
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
#include <mobnet/PlmnId.h>
#include <mib-core/MibManager.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069SetParameterValueManager.h"
#include "Tr069ParameterValueChangeNotificationManager.h"
#include "Tr069DataModelManager.h"
#include "Tr069MibAttributeValueFactory.h"
#include "Tr069MultiInstanceMibObjectManager.h"
#include "autogen/Tr069DataModel.h"

#include "SoapEnvelope.h"
#include "SoapFault.h"

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

ValidationFailureDescriptor ProcessGroupIdRemScanOnBoot(const Tr069AttributeValues&, MibAttributeValues& );
//ValidationFailureDescriptor ProcessGroupIdRemScanPeriodically(const Tr069AttributeValues&, MibAttributeValues&);
//ValidationFailureDescriptor ProcessGroupIdMinMaxValidation(const Tr069AttributeValues&, MibAttributeValues&);
ValidationFailureDescriptor ProcessGroupIdListValidation(const Tr069AttributeValues&, MibAttributeValues&);
ValidationFailureDescriptor ProcessGroupIdBooleanValidation(const Tr069AttributeValues&, MibAttributeValues&);
ValidationFailureDescriptor ProcessGroupIdEnumValidation(const Tr069AttributeValues&, MibAttributeValues&); 
//ValidationFailureDescriptor ProcessGroupIdSingleInstanceValidation(const Tr069AttributeValues&, DmNameMap::const_iterator iterDmNameMap, MibAttributeValues&);
//static void ProcessGroupIdPlmnId(const ExtDMAttrDefinition*, ParameterList&);
//static void AppendConstantToParameterList( const ExtDMAttrDefinition * dmDefinition, ParameterList & parameterList);
//static void ProcessGroupIdMinMax(const ExtDMAttrDefinition*, ParameterList&);
static void ProcessGroupIdList(const ExtDMAttrDefinition*, ParameterList&);
static void ProcessGroupIdBoolean(const ExtDMAttrDefinition*, ParameterList&);
static void ProcessGroupIdEnum(const ExtDMAttrDefinition*, ParameterList&); 
bool ProcessGroupIdEnableValidation(DmNameMap & m_nameMap,const ParameterValueMap & parameterValueMap,DmNameMap::const_iterator dm ,ValidationFailureDescriptor & validationFailureDescriptor) ;
void setKeys(MibObjectClass &dnClass,string str,MibAttributeId keyValues[]);
bool ProcessGroupIdKey(DmNameMap::const_iterator dm , ValidationFailureDescriptor & validationFailureDescriptor) ;
void initialize();
//static void ProcessGroupIdSingleInstance(const ExtDMAttrDefinition*, ParameterList&);
KeyMap Dn2KeyMap;

ValidateKeys KeysDefination[] =
 {
    {
        {
             MIB_OBJECT_CLASS_LTE_RAN_NEIGH_LIST_LTE_CELL,
             PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_ENABLE,
             PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_PLMNID,
             PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_CID,
             PARAM_ID_INVALID
         } ,
        "LTE_RAN_NEIGH_LIST_LTE_CELL"
    },
    {
       {
            MIB_OBJECT_CLASS_LTE_CELL_PLMN_LIST,
            PARAM_ID_LTE_EPC_PLMN_ENABLE,
            PARAM_ID_LTE_OAM_PLMNID,
            PARAM_ID_INVALID,
            PARAM_ID_INVALID
       },
       "LTE_CELL_PLMN_LIST"
   },
   {
      {    
            MIB_OBJECT_CLASS_LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER,
            PARAM_ID_LTE_INTER_FREQ_ENABLE,
            PARAM_ID_LTE_INTER_FREQ_DL_EARFCN,
            PARAM_ID_INVALID,
            PARAM_ID_INVALID
      },
      "LTE_RAN_MOB_IDLE_MODE_INTER_FREQ_CARRIER"  
   },
   {
      {
         MIB_OBJECT_CLASS_LTE_UMTS_NEIGHBOR,
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_ENABLE,
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_PLMNID,
         PARAM_ID_LTE_OAM_NEIGHBOUR_UTRA_CELL_CID_IRAT,
         PARAM_ID_INVALID
      },
      "LTE_UMTS_NEIGHBOR"
   },
   {
      {
         MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_LIST,
         PARAM_ID_LTE_GERAN_CELL_ENABLE,
         PARAM_ID_LTE_GERAN_CELL_PLMNID,
         PARAM_ID_LTE_GERAN_CELL_LAC,
         PARAM_ID_LTE_GERAN_CELL_CI
      },
      "LTE_INTER_RAT_GERAN_NEIGHBOR_CELL_LIST" 
   },
   {
      {
         MIB_OBJECT_CLASS_UTRA_UTRAN_FDD_FREQ,
         PARAM_ID_LTE_UTRA_FDD_ENABLE_IRAT,
         PARAM_ID_LTE_UTRA_FDD_CARRIER_ARFCN,
         PARAM_ID_INVALID,
         PARAM_ID_INVALID
       } ,
       "UTRA_UTRAN_FDD_FREQ"
   },
   {
      {
         MIB_OBJECT_CLASS_LTE_INTER_RAT_GERAN_NEIGHBOR_FREQ_LIST,
         PARAM_ID_LTE_GERAN_FREQ_ENABLE,
         PARAM_ID_LTE_GERAN_FREQ_BCCH_ARFCN,
         PARAM_ID_INVALID,
         PARAM_ID_INVALID
      },
      "LTE_INTER_RAT_GERAN_NEIGHBOR_FREQ_LIST"
   }
};


DataModelManager* DataModelManager::s_instance = NULL;

MibDnAttribute::MibDnAttribute(const ExtDMAttrDefinition * dmDef)
{
   RSYS_ASSERT(dmDef);

   m_dn = MibDN::GenerateMibDN( string(dmDef->mibDN) );
   m_id = dmDef->mibAttrId;
}

MibDnAttribute::MibDnAttribute(const MibDN & dn, MibAttributeId id) :
   m_dn(dn),
   m_id(id)
{
}

bool MibDnAttribute::operator< ( const MibDnAttribute & rhs ) const
{
   bool lessThan =
      (m_dn.ToString() < rhs.m_dn.ToString())
      || ( (m_dn.ToString() == rhs.m_dn.ToString())
            &&
            (m_id < rhs.m_id) );

   return lessThan;
}

DataModelManager& DataModelManager::GetInstance()
{
   ENTER ();

   if (s_instance == NULL)
   {
      s_instance = new DataModelManager(Tr069Application::GetInstance().GetMibCache());

      RSYS_ASSERT(s_instance);
   }

   RETURN (*s_instance);
}

DataModelManager::DataModelManager( MibAccessInterface& mib) :
   m_validationOk(true),
   m_mib(mib),
   changeApplies(0),
   numCell(2)
{
   string numCellStr = getConfigParam("OAM_NUM_CELL_ENTRIES", "");
   if(NULL != numCellStr.c_str())
   {
      numCell = (u16)atoi(numCellStr.c_str());
   }
   string vendor("RADISYS");
   if( m_mib.IsMibAttributePresent(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING),PARAM_ID_GATEWAY_VENDOR) )
   {
      m_mib.GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_COMMISSIONING), PARAM_ID_GATEWAY_VENDOR, vendor );
   }

   TRACE_PRINTF("Gateway vendor: Radisys");
   for(size_t i = 0; i < radisysDataModelArrayLength; i++)
   {
      updateDmDef(radisysDataModel[i]);
   }
}

bool DataModelManager::HandleCliSetParameterValue(string name,string value,string &result)
{
   TRACE_PRINTF("%s",__func__);

   shared_ptr<MibAttributeValuesByDn> mibAttributeValuesByDn(new MibAttributeValuesByDn);
   bool ret;
   DmNameMap::const_iterator dm = m_nameMap.find(name);
   if(dm == m_nameMap.end()|| ((dm->second).mibAttrId == PARAM_ID_INVALID))
   {
      result = "Parameter Name Is InValid";
      return false;
   }
   MibDN mibDn = MibDN::GenerateMibDN( string((dm->second).mibDN) );
   if((Tr069Application::GetInstance().GetMibCache().IsMibObjectPresent(mibDn)))
   {
      TRACE_PRINTF("ARGUMENT to mibdn is :%s",string((dm->second).mibDN).c_str());
      MibAttributeValues mValue;
      ret = ValidateParameterAgainstDataModelTables(dm, value, mValue);
      if(ret)
      {
         ParameterValueMap CliSPVMap;
         bool CliValidationOk;
         CliSPVMap.insert(pair<string,string>(name,value));
         CliValidationOk = ValidateSetParamterValue(CliSPVMap);
         if(!CliValidationOk)
         {
            result = "Validation Failure";
            return false;
         }
         else if(1 == changeApplies)
         {  
            OamActionReq oamActionReq(OAM_ACTION_REBOOT);
            Tr069Application::GetInstance().SendMessage(oamActionReq, ENTITY_OAM, ENTITY_TR069);
            return false;
         }
         else
         {
            Tr069Application::GetInstance().GetMibCache().SetMibAttributesByDn(mibDn,mValue, ENTITY_TR069);
         }
      }
   }
   else
   {
      result = "Parameter Name Is InValid";
      ret = false;
   }
   return ret;
}

bool DataModelManager::getAttrInfo(const char* name, MibAttributeId &attr, char *dn)
{
   attr=PARAM_ID_INVALID;

   DmNameMap::const_iterator dm = m_nameMap.find(name);
   if(dm == m_nameMap.end())
   {
      return 0;
   }
   strcpy(dn ,(dm->second).mibDN.c_str());
   attr = (dm->second).mibAttrId ;
   return 1;
}

void DataModelManager::getAllAttrInfo(const char* name,std::vector<std::string> &names, std::vector<MibAttributeId> &attr, std::vector<std::string > &dn)
{

   for( DmNameMap::const_iterator i = m_nameMap.begin(); i != m_nameMap.end(); i++)
   {
      const ExtDMAttrDefinition  * dmDefinition = &(i->second);

      if(strstr(dmDefinition->name.c_str(),name))
      {
         names.push_back(std::string(dmDefinition->name));
         attr.push_back(dmDefinition->mibAttrId);
         dn.push_back(std::string(dmDefinition->mibDN));
      }
   }
}

DataModelManager::~DataModelManager()
{
   m_nameMap.clear();
   m_paramIdMap.clear();
}

void DataModelManager::updateDmDef(const ExtDMAttrDefinition dmAttrDefinition)
{
   ExtDMAttrDefinition dmAttrDef = dmAttrDefinition;
   string name = dmAttrDef.name;
   string mibDN = dmAttrDef.mibDN;
   string str;
   u16 inst = 0;
   int nameStartPos, mibDnStartPos;
   int nameEndPos, mibDnEndPos;
   string tmpString;
   int itr = 1;

   if(std::string::npos != name.find("{"))
   {
      nameStartPos = name.find("{");
      nameEndPos = name.find("}");
      mibDnStartPos = mibDN.find("{");
      mibDnEndPos = mibDN.find("}");
      tmpString = name.substr(0, nameStartPos + 1);
      if(std::string::npos != tmpString.find("FAPService.{"))
      {
         inst = numCell;
      }
      else
      {
         str = name.substr(nameStartPos + 1, (nameEndPos - nameStartPos - 1));
         if(NULL != str.c_str())
         {
            inst = (u16)atoi(str.c_str());
         }
      }
      for(itr = 1; itr <= inst; itr++)
      {
         stringstream convert;
         convert << itr;
         string nameStr, mibDnStr;
         nameStr.append(name.substr(0,nameStartPos-1));
         nameStr.append(".");
         nameStr.append(convert.str());
         nameStr.append(name.substr(nameEndPos+1));

         if((std::string::npos != mibDN.find("{")))
         {
            stringstream itrStr;
            itrStr << (itr - 1);
            mibDnStr.append(mibDN.substr(0,mibDnStartPos-1));
            mibDnStr.append(".");
            mibDnStr.append(itrStr.str());
            mibDnStr.append(mibDN.substr(mibDnEndPos+1));
            dmAttrDef.mibDN = (char *)mibDnStr.c_str();
         }

         dmAttrDef.name = (char *)nameStr.c_str();

         updateDmDef(dmAttrDef);
      }
   }
   else
   {
      UpdateDataModelAttributeDefinition(dmAttrDef);
   }
}

void DataModelManager::UpdateDataModelAttributeDefinition(const ExtDMAttrDefinition dmAttrDefinition)
{
   string name = dmAttrDefinition.name;

   MibDnAttribute fqma(&dmAttrDefinition);
   m_nameMap[ name ] = dmAttrDefinition;
   m_paramIdMap.insert( pair<MibDnAttribute, const ExtDMAttrDefinition>( fqma, dmAttrDefinition) );

   if( dmAttrDefinition.mibAttrId < NUM_MIB_ATTR_IDS || dmAttrDefinition.mibGroup < NUM_GROUP_IDS )
   {
      ExtDMAttrNotificationType notifyVal;
      MibDN dn = MibDN::GenerateMibDN( string(dmAttrDefinition.mibDN) );
      NvAttributeResult result = Tr069Application::GetInstance().GetParamAttNvStore()->GetParamAttributeNvVal(dn, MibAttributeIdToString(dmAttrDefinition.mibAttrId), notifyVal);
      if(result != NV_ATTRIBUTE_RESULT_OK)
      {
         notifyVal = dmAttrDefinition.notify;
      }
      //   TRACE_PRINTF("Attribute %s/%s has notify Val %d and Name = %s", dn.ToString().c_str(), MibAttributeIdToString(dmAttrDefinition.mibAttrId),(int)notifyVal,name.c_str() );
      Tr069ParameterValueChangeNotificationManager::GetInstance().SetParamterAttributes( name, notifyVal);
   }

   if( dmAttrDefinition.forcedInform )
   {
      m_forcedInformParameters.insert(name);
   }
}

void DataModelManager::AddParameterToParameterList( const string & name, ParameterList & parameterList )
{
   string::const_reverse_iterator rit = name.rbegin();
   char lastChar = *rit;
   bool wildCardSearch = (lastChar == '.');

   if(wildCardSearch)
   {
      const string & pathName = name;
      size_t pathLength = pathName.length();

      TRACE_PRINTF("WildCardGet %s (%zu)",pathName.c_str(), pathLength);

      for( DmNameMap::const_iterator i = m_nameMap.begin();
            i != m_nameMap.end();
            ++i)
      {
         string mapEntryName(i->first);

         bool wildCardMatch = (0 == mapEntryName.compare( 0, pathLength, pathName ) );

         if( wildCardMatch)
         {
            string value;

            const ExtDMAttrDefinition  * dmDefinition = &(i->second);
            if(dmDefinition->mibAttrId < NUM_MIB_ATTR_IDS)
            {
               MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

               bool objPresent = m_mib.IsMibObjectPresent( dn );
               ExtDMAttrDataType  dmType = DATA_TYPE;

               if(objPresent)
               {
                  bool attrPresent = m_mib.IsMibAttributePresent( dn, dmDefinition->mibAttrId);

                  if( attrPresent )
                  {
                     Tr069MibAttributeValueFactory::ToDataModelValue( dmDefinition, value, dmType);
                     parameterList.AppendParameter(mapEntryName, value, dmType );
                  }
               }
            }
            else
            {
               AppendGroupToParameterList(dmDefinition, parameterList);
            }
         }
      }
   }
   else
   {
      DmNameMap::const_iterator i = m_nameMap.find(name);

      string value;

      if( i != m_nameMap.end() )
      {
         const ExtDMAttrDefinition * dmDefinition = &(i->second);
         if(dmDefinition->mibAttrId < NUM_MIB_ATTR_IDS)
         {
            MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

            bool objPresent = m_mib.IsMibObjectPresent( dn );
            ExtDMAttrDataType  dmType = DATA_TYPE;

            if(objPresent)
            {
               bool attrPresent = m_mib.IsMibAttributePresent( dn, dmDefinition->mibAttrId);

               if( attrPresent )
               {
                  Tr069MibAttributeValueFactory::ToDataModelValue( dmDefinition, value, dmType);
               }
               else
               {
                  TRACE_PRINTF("Attribute %s/%s not found in MIB", dn.ToString().c_str(), MibAttributeIdToString(dmDefinition->mibAttrId) );
               }

               parameterList.AppendParameter(name, value, dmType );
            }
            else
            {
               TRACE_PRINTF("Attribute %s/%s not found in MIB", dn.ToString().c_str(), MibAttributeIdToString(dmDefinition->mibAttrId) );
            }
         }
         else
         {
            TRACE_PRINTF("DataModelManager::AddParameterToParameterList(%s) NOT found.", name.c_str());
            AppendGroupToParameterList(dmDefinition, parameterList);
         }
      }
      else
      {
         TRACE_PRINTF("DataModelManager::AddParameterToParameterList(%s) NOT found.", name.c_str());
      }
   }
}

void DataModelManager::AddParameterToCliParameterList( const string & name, ParameterList & parameterList )
{
   TRACE_PRINTF("%s",__func__);

   DmNameMap::const_iterator i = m_nameMap.find(name);

   string value;

   if( i != m_nameMap.end() )
   {
      const ExtDMAttrDefinition * dmDefinition = &(i->second);
      if(dmDefinition->mibAttrId < NUM_MIB_ATTR_IDS)
      {
         MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

         bool objPresent = m_mib.IsMibObjectPresent( dn );
         ExtDMAttrDataType  dmType = DATA_TYPE;

         if(objPresent)
         {
            bool attrPresent = m_mib.IsMibAttributePresent( dn, dmDefinition->mibAttrId);

            if( attrPresent )
            {
               Tr069MibAttributeValueFactory::ToDataModelValue( dmDefinition, value, dmType);
            }
            else
            {
               TRACE_PRINTF("Attribute %s/%s not found in MIB", dn.ToString().c_str(), MibAttributeIdToString(dmDefinition->mibAttrId) );
            }

            parameterList.AppendParameter(name, value, dmType );
         }
         else
         {
            TRACE_PRINTF("Attribute %s/%s not found in MIB", dn.ToString().c_str(), MibAttributeIdToString(dmDefinition->mibAttrId) );
         }
      }
      else
      {
         TRACE_PRINTF("DataModelManager::AddParameterToCliParameterList(%s) NOT found.", name.c_str());
         AppendGroupToParameterList(dmDefinition, parameterList);
      }
   }
}

void DataModelManager::AddParameterToAttributeList( const string & name, AttributeList & parameterList )
{
   string::const_reverse_iterator rit = name.rbegin();
   char lastChar = *rit;
   bool wildCardSearch = (lastChar == '.');

   if(wildCardSearch)
   {
      const string & pathName = name;
      size_t pathLength = pathName.length();

      TRACE_PRINTF("WildCardGet %s (%zu)",pathName.c_str(), pathLength);

      for( DmNameMap::const_iterator i = m_nameMap.begin();
            i != m_nameMap.end();
            ++i)
      {
         string mapEntryName(i->first);

         bool wildCardMatch = (0 == mapEntryName.compare( 0, pathLength, pathName ) );

         if( wildCardMatch)
         {
            string notification;

            const ExtDMAttrDefinition * dmDefinition = &(i->second);
            if(dmDefinition->mibAttrId < NUM_MIB_ATTR_IDS)
            {
               //Check if notify is available in the non-volatile store
               ExtDMAttrNotificationType notifyVal;
               MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );
               NvAttributeResult result = Tr069Application::GetInstance().GetParamAttNvStore()->GetParamAttributeNvVal(dn, MibAttributeIdToString(dmDefinition->mibAttrId), notifyVal);

               //If not available get from XML defaults
               if(result != NV_ATTRIBUTE_RESULT_OK)
               {
                  notifyVal = dmDefinition->notify;
               }
               stringstream ss;
               ss << notifyVal;
               notification = ss.str();
               parameterList.AppendParameter(mapEntryName, notification);
            }
         }
      }
   }
   else
   {
      DmNameMap::const_iterator i = m_nameMap.find(name);

      string notification;

      if( i != m_nameMap.end() )
      {
         const ExtDMAttrDefinition * dmDefinition = &(i->second);
         if(dmDefinition->mibAttrId < NUM_MIB_ATTR_IDS)
         {
            //Check if notify is available in the non-volatile store
            ExtDMAttrNotificationType notifyVal;
            MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );
            NvAttributeResult result = Tr069Application::GetInstance().GetParamAttNvStore()->GetParamAttributeNvVal(dn, MibAttributeIdToString(dmDefinition->mibAttrId), notifyVal);

            //If not available get from XML defaults
            if(result != NV_ATTRIBUTE_RESULT_OK)
            {
               notifyVal = dmDefinition->notify;
            }
            stringstream ss;
            ss << notifyVal;
            notification = ss.str();
            parameterList.AppendParameter(name, notification);
         }
      }
      else
      {
         TRACE_PRINTF("DataModelManager::AddParameterToAttributeList(%s) NOT found.", name.c_str());
      }
   }
}

void DataModelManager::AddParameterInfoToParameterList( const string & name, ParameterInfoList & parameterInfoList )
{
   string::const_reverse_iterator rit = name.rbegin();
   char lastChar = *rit;
   bool wildCardSearch = (lastChar == '.');

   if(wildCardSearch)
   {
      const string & pathName = name;
      size_t pathLength = pathName.length();

      for( DmNameMap::const_iterator i = m_nameMap.begin();
            i != m_nameMap.end();
            ++i)
      {
         string mapEntryName(i->first);

         bool wildCardMatch = (0 == mapEntryName.compare( 0, pathLength, pathName ) );

         if( wildCardMatch)
         {
            const ExtDMAttrDefinition * dmDefinition = &(i->second);
            if(dmDefinition->mibAttrId < NUM_MIB_ATTR_IDS)
            {
               MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

               const MibObjectAttributeDescriptor* mibObjectAttributeDescriptor = getMibObjectAttributeDescriptor(dn.back().GetMibObjectClass(), dmDefinition->mibAttrId);

               if(mibObjectAttributeDescriptor)
               {
                  string writable;
                  if (mibObjectAttributeDescriptor->accessClass == MIB_ACCESS_READ_WRITE)
                  {
                     writable = "1";
                  }
                  else
                  {
                     writable = "0";
                  }
                  parameterInfoList.AppendParameter(mapEntryName, writable);
               }
               else
               {
                  TRACE_PRINTF("Attribute %d-%d not found in MIB", dn.back().GetMibObjectClass(), dmDefinition->mibAttrId );
               }
            }
            else if (dmDefinition->type == OBJECT)
            {
               // We may have hit a simple object and should be included as readonly
               string writable = "1";
               if (dmDefinition->access == READ_ONLY)
               {
                  writable = "0";
               }
               TRACE_PRINTF("Object: Attribute (%s) - Writable (%s) added to ParameterInfoList", pathName.c_str(), writable.c_str());
               parameterInfoList.AppendParameter(mapEntryName, writable);
            }
            else
            {
               //TRACE_PRINTF("DataModelManager::AttributeId (%d) for Path (%s) is outside valid range", dmDefinition->mibAttrId, pathName.c_str());
            }
         }
      }
   }
   else
   {
      DmNameMap::const_iterator i = m_nameMap.find(name);

      if( i != m_nameMap.end() )
      {
         const ExtDMAttrDefinition * dmDefinition = &(i->second);
         if(dmDefinition->mibAttrId < NUM_MIB_ATTR_IDS)
         {
            MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

            const MibObjectAttributeDescriptor* mibObjectAttributeDescriptor = getMibObjectAttributeDescriptor(dn.back().GetMibObjectClass(), dmDefinition->mibAttrId);

            if(mibObjectAttributeDescriptor)
            {
               string writable;
               if (mibObjectAttributeDescriptor->accessClass == MIB_ACCESS_READ_WRITE)
               {
                  writable = "1";
               }
               else
               {
                  writable = "0";
               }
               parameterInfoList.AppendParameter(name, writable);
            }
            else
            {
               TRACE_PRINTF("Attribute %d-%d not found in MIB", dn.back().GetMibObjectClass(), dmDefinition->mibAttrId );
            }
         }
         else if (dmDefinition->type == OBJECT)
         {
            // We may have hit a simple object and should be included as readonly
            string writable = "1";
            if (dmDefinition->access == READ_ONLY)
            {
               writable = "0";
            }
            TRACE_PRINTF("Object: Attribute (%s) - Writable (%s) added to ParameterInfoList", name.c_str(), writable.c_str());
            parameterInfoList.AppendParameter(name, writable);
         }
         else
         {
            //TRACE_PRINTF("DataModelManager::AttributeId (%d) for Path (%s) is outside valid range", dmDefinition->mibAttrId, name.c_str());
         }
      }
      else
      {
         TRACE_PRINTF("DataModelManager::AddParameterInfoToParameterList(%s) NOT found.", name.c_str());
      }
   }
}


const set<string> & DataModelManager::GetForcedInformParameterSet( )
{
   /**
    * Including:
    Device.DeviceSummary
    Device.DeviceInfo.SoftwareVersion
    Device.DeviceInfo.HardwareVersion
    Device.DeviceInfo.SpecVersion
    Device.DeviceInfo.ProvisioningCode
    Device.ManagementServer.ConnectionRequestURL
    Device.ManagementServer.ParameterKey
    Device.Services.FAPService.1.FAPControl.OpState
    Device.Services.FAPService.1.FAPControl.RFTxStatus
    */

   return m_forcedInformParameters;
}

void DataModelManager::AppendGroupToParameterList( const ExtDMAttrDefinition * dmDefinition, ParameterList & parameterList)
{
   switch(dmDefinition->mibGroup)
   {
      case GROUP_ID_FIRST:
         TRACE_PRINTF("Unexpected group id: GROUP_ID_FIRST.");
         break;
#if 0
      case GROUP_CONSTANT:
         AppendConstantToParameterList( dmDefinition, parameterList);
         break;
#endif
      case GROUP_ID_REM_SCAN_ON_BOOT:
         TRACE_PRINTF("AppendGroupToParameterList GROUP_ID_REM_SCAN_ON_BOOT not handled");
         break;

      case GROUP_ID_REM_SCAN_PERIODICALLY:
         TRACE_PRINTF("AppendGroupToParameterList GROUP_ID_REM_SCAN_PERIODICALLY not handled");
         break;
#if 0
      case GROUP_ID_STORE_BUT_IGNORE:
         TRACE_PRINTF("AppendGroupToParameterList GROUP_ID_STORE_BUT_IGNORE not handled");
         break;
#endif
      case GROUP_ID_MULTIPLE_INSTANCE_MIB_OBJECT:
         MultiInstanceMibObjectManager::GetInstance().AddParameterToParameterList(dmDefinition->name, parameterList);
         break;
      case NUM_GROUP_IDS:
         TRACE_PRINTF("Unexpected group id: NUM_GROUP_IDS.");
         break;

      case GROUP_ID_BOOLEAN:
         ProcessGroupIdBoolean( dmDefinition, parameterList);
         break;

      case GROUP_ID_LIST:
         ProcessGroupIdList( dmDefinition, parameterList);
         break;

      case GROUP_ID_INVALID:
         TRACE_PRINTF("Unexpected group id: GROUP_ID_INVALID.");
         break;

      case GROUP_ID_ENUM:
         ProcessGroupIdEnum( dmDefinition, parameterList);
         break;

      default:
         TRACE_PRINTF("Group id not known at all.");
         break;
   }
}

void DataModelManager::SetParamterAttribute( const RpcSetParameterAttribute & rpcSetParameterAttribute, SetParameterAttributeNotifications & span )
{
   // TODO: Add success/failure result?

   for( SetParameterAttributeNotifications::const_iterator input = rpcSetParameterAttribute.GetNoticications().begin();
         input != rpcSetParameterAttribute.GetNoticications().end();
         ++input )
   {
      SetParameterAttributeNotifications filterResults = FilterSetParamAttribute( *input );

      span.insert( span.end(), filterResults.begin(), filterResults.end() );
   }
}

SetParameterAttributeNotifications DataModelManager::FilterSetParamAttribute( const SetParameterAttributeNotification & in )
{
   SetParameterAttributeNotifications out;

   string name      = in.GetName();
   u32 notification = in.GetNotification();

   string::const_reverse_iterator rit = name.rbegin();
   char lastChar = *rit;
   bool wildCardSearch = (lastChar == '.');

   if(wildCardSearch)
   {
      string & pathName = name;
      size_t pathLength = pathName.length();

      TRACE_PRINTF("WildCardGet %s",pathName.c_str());

      for( DmNameMap::const_iterator i = m_nameMap.begin();
            i != m_nameMap.end();
            ++i)
      {
         string mapEntryName(i->first);

         rit = mapEntryName.rbegin();
         if(rit != mapEntryName.rend())
         {
            lastChar = *rit;
         }
         bool mapEntryNameDoesNotEndWithDot = (lastChar != '.');

         if( mapEntryNameDoesNotEndWithDot )
         {
            bool wildCardMatch = (mapEntryName.substr(0, pathLength) == pathName);

            if( wildCardMatch )
            {
               SetParameterAttributeNotification span( mapEntryName, notification);

               SetParameterAttributeNotifications matches = FilterSetParamAttribute( span );
               const ExtDMAttrDefinition * dmDefinition = &(i->second);
               MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );
               Tr069Application::GetInstance().GetParamAttNvStore()->SetParamAttributeNvVal(dn, (string)MibAttributeIdToString(dmDefinition->mibAttrId), (ExtDMAttrNotificationType)notification);

               out.insert( out.end(), matches.begin(), matches.end() );
            }
         }
      }
   }
   else
   {
      DmNameMap::const_iterator i = m_nameMap.find(name);

      if( i != m_nameMap.end() )
      {
         const ExtDMAttrDefinition * dmDefinition = &(i->second);

         MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

         bool objPresent = m_mib.IsMibObjectPresent( dn );

         if(objPresent)
         {
            bool attrPresent = m_mib.IsMibAttributePresent( dn, dmDefinition->mibAttrId);
            if (attrPresent)
            {
               SetParameterAttributeNotification span( name, notification);
               out.push_back(span);
               Tr069Application::GetInstance().GetParamAttNvStore()->SetParamAttributeNvVal(dn, (string)MibAttributeIdToString(dmDefinition->mibAttrId), (ExtDMAttrNotificationType)notification);
            }
            else
            {
               TRACE_PRINTF("Attribute %s/%s not found in MIB", dn.ToString().c_str(), MibAttributeIdToString(dmDefinition->mibAttrId) );
            }
         }
      }
   }

   return out;
}

bool DataModelManager::ValidateSetParamterValue( const ParameterValueMap & parameterValueMap)
{
   ValidationFailureDescriptor validationFailureDescriptor;
   int no_of_fault = 0;
   m_validationOk = false;
   Reset();

   shared_ptr<MibAttributeValuesByDn> mibAttributeValuesByDn(new MibAttributeValuesByDn);
   RSYS_ASSERT(mibAttributeValuesByDn);

   bool groupsOk;
   ParameterValueMap::const_iterator param = parameterValueMap.begin();
   Tr069AttributeValues setParamValues;
   string enableName,value;
   while((param != parameterValueMap.end()))
   {  
      setParamValues.clear();
      string name;
      name=param->first;
      StringUtils::Trim(name);

      value = param->second;
      StringUtils::Trim(value);
      DmNameMap::const_iterator dm = m_nameMap.find(name);

#if 0
      if(strstr(name.c_str(),"Enable"))  //In SPV together enable should come at end and there should be atmost 1 enable
      {
         ParameterValueMap::const_iterator EnableAtEnd = --parameterValueMap.end();
         if(!isEnable&&(param != EnableAtEnd))
         {
            enableName = name;
            isEnable = true;
            param++;
            continue;
         }
         else
         {
            isEnable = false;
            param = EnableAtEnd;
         }
      } 
#endif
      if(dm == m_nameMap.end())
      {
         ostringstream oss;
         oss<<"AttributeIdNotFound : "<< name.c_str();
         fault_parameters[no_of_fault] = name ;
         m_xmlFaultString[no_of_fault++] = oss.str();
         groupsOk = false;
      }
      else
      {   
         setParamValues[name] = value;
         groupsOk = ValidateSetParameterValueGroups(parameterValueMap,setParamValues, *mibAttributeValuesByDn, validationFailureDescriptor);
      }
      if(groupsOk)
      {
         if ((dm->second).access == READ_ONLY )
         {
            m_validationOk = false;
            const ExtDMAttrDefinition * dmAttrDefinition = &(dm->second);
            ostringstream oss;
            oss<<"ReadOnly Access: "<<dmAttrDefinition->name<<" Value: ("<<value.c_str()<<") ";
            fault_parameters[no_of_fault] = name ;
            m_xmlFaultString[no_of_fault++] += oss.str();
         }
         else if(((dm->second).mibAttrId != PARAM_ID_INVALID) )
         {
            MibDN mibDn = MibDN::GenerateMibDN( string((dm->second).mibDN) );
            MibAttributeValues & mibAttributeValues = (*mibAttributeValuesByDn)[mibDn];

            if(!strcmp(value.c_str(), ""))
            {
               const ExtDMAttrDefinition * dmAttrDefinition = &(dm->second);
               ostringstream oss;
               oss<<" NotValidValue: "<<dmAttrDefinition->name<<" Value: ("<<value.c_str()<<") ";
               fault_parameters[no_of_fault] = name ;
               m_xmlFaultString[no_of_fault++] += oss.str();
            }
            else
            {
               m_validationOk = ValidateParameterAgainstDataModelTables(dm, value, mibAttributeValues);
               MibDN dnobj = MibDN::GenerateMibDN( string((dm->second).mibDN) );
               const ExtDMAttrDefinition * dmAttrDefinition = &(dm->second);

               u32 opState = false;
               m_mib.GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP),PARAM_ID_LTE_RFTX_OP_STATE, opState);
    
               if((opState == 1)&&dmAttrDefinition->changeApplies)
               {
                  changeApplies = dmAttrDefinition->changeApplies;
               }
               else
               {
                  changeApplies = 0;
               }

               /*if validationOk is false then return fault with error casue :incompatible type*/	
               if(!m_validationOk)
               {
                  const ExtDMAttrDefinition * dmAttrDefinition = &(dm->second);
                  ostringstream oss;
                  oss<<" Invalid Value: "<<dmAttrDefinition->name<<" Value: ("<<value.c_str()<<") ";
                  fault_parameters[no_of_fault] = name ;
                  m_xmlFaultString[no_of_fault++] += oss.str();
               }
            }
         }
      }
      else
      {
         m_validationOk = false;
         if(!validationFailureDescriptor.GetDescription().empty())
         {
            ostringstream oss;
            oss<<validationFailureDescriptor.GetDescription()<<" ";
            fault_parameters[no_of_fault] = name ;
            m_xmlFaultString[no_of_fault++] += oss.str();
         } 
      }
      ++param;
   }
   
   if(no_of_fault > 0)
   {
      m_validationOk = false;
   }
   shared_ptr<DataModelVerifyCnf> dataModelVerifyCnf(new DataModelVerifyCnf(m_validationOk, mibAttributeValuesByDn, m_xmlFaultString,fault_parameters,no_of_fault));
   Tr069ServerConnection::GetInstance().HandleEvent(dataModelVerifyCnf);
   return m_validationOk;   
}

void DataModelManager::AddMibAttributesForDataModelParameters( MibAttributeIdsByDn & attributesByDn )
{
   DmNameMap::const_iterator param;
   MibAttributeIds ids;
   const ExtDMAttrDefinition * dm = &(param->second);
   string dn ;

   for(param = m_nameMap.begin() ; param != m_nameMap.end(); ++param )
   {  ids.clear();
      dm = &(param->second);
      dn  = string(dm->mibDN);
      MibDN dnNew = MibDN::GenerateMibDN(dn);
      MibAttributeIdsByDn::const_iterator i = attributesByDn.find(dnNew);
      if( dm->mibAttrId < NUM_MIB_ATTR_IDS)
      {
        if(i == attributesByDn.end())
        {
         ids.insert(dm->mibAttrId);
         attributesByDn[dnNew] = ids;
        }
        else
        {
         ids = i->second;
         ids.insert(dm->mibAttrId);
         attributesByDn[dnNew] = ids;
        }
      }
   }
}

void DataModelManager::MibAttributeUpdatedNotification(const MibDN & dn, MibAttributeId attr)
{
   MibDnAttribute fqma(dn,attr);

   TRACE_PRINTF("Tr069DataModelManager::MibAttributeUpdatedNotification %s/%s",dn.ToString().c_str(), MibAttributeIdToString(attr));

   pair<DmMibAttributeIdMap::const_iterator,DmMibAttributeIdMap::const_iterator> rangePair = m_paramIdMap.equal_range(fqma);

   for( DmMibAttributeIdMap::const_iterator i = rangePair.first; i != rangePair.second; ++i)
   {
      const ExtDMAttrDefinition * dm = &(i->second);

      string name(dm->name);

      Tr069ParameterValueChangeNotificationManager::GetInstance().NotificationValueChange( name );
   }
}

bool DataModelManager::ValidateSetParameterValueGroups(const ParameterValueMap & parameterValueMap,
      Tr069AttributeValues setParamValues,
      MibAttributeValuesByDn & mibAttributeValuesByDn,
      ValidationFailureDescriptor & validationFailureDescriptor)
{
   string name, enValue;

   Tr069AttributeValues::const_iterator param;
   param = setParamValues.begin();
   if(param != setParamValues.end())
   {
      name = param->first;
      enValue = param->second;
   }
   u16 grp = 0;
   MibDN dn;
   DmNameMap::const_iterator dm = m_nameMap.find(name);
   if(dm != m_nameMap.end())
   {
      grp = (dm->second).mibGroup;
      dn = MibDN::GenerateMibDN(((dm->second).mibDN));
   }

   if(setParamValues.size())
   {
   //   MibDN fap0 = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP,0);
      
      switch( ExtDataModelAttrGroupId(grp))
      {
         case GROUP_ID_FIRST:
            TRACE_PRINTF("Unexpected group id: GROUP_ID_FIRST.");
            break;
#if 0
         case GROUP_CONSTANT:
            {
               validationFailureDescriptor.Set( ValidationFailureDescriptor::CAUSE_READ_ONLY,
                     "GROUP_CONSTANT -Write not supported.");
            }
            break;
#endif

         case GROUP_ID_REM_SCAN_ON_BOOT:
            {
              // ProcessGroupIdRemScanOnBoot(setParamValues, mibAttributeValuesByDn[fap0]);
               ProcessGroupIdRemScanOnBoot(setParamValues, mibAttributeValuesByDn[dn]);
            }
            break;
#if 0
         case GROUP_ID_STORE_BUT_IGNORE:
            {
               validationFailureDescriptor.Set( ValidationFailureDescriptor::CAUSE_OTHER,
                     "ProcessGroupIdStoreButIgnoreSpv - Function not supported.");
            }
            break;
#endif

         case GROUP_ID_MULTIPLE_INSTANCE_MIB_OBJECT:
            {
               validationFailureDescriptor.Set( ValidationFailureDescriptor::CAUSE_READ_ONLY,
                     "GROUP_ID_MULTIPLE_INSTANCE_MIB_OBJECT -Write not supported.");
            }
            break;

         case NUM_GROUP_IDS:
            TRACE_PRINTF("Unexpected group id: NUM_GROUP_IDS.");
            break;

         case GROUP_ID_LIST:
            {
          //  ProcessGroupIdListValidation(setParamValues, mibAttributeValuesByDn[fap0]);
            ProcessGroupIdListValidation(setParamValues, mibAttributeValuesByDn[dn]);
            break;
            }

         case GROUP_ID_BOOLEAN:
            ProcessGroupIdBooleanValidation(setParamValues, mibAttributeValuesByDn[dn]);
            break;

         case GROUP_ID_INVALID:
            TRACE_PRINTF("Unexpected group id: GROUP_ID_INVALID.");
            break;

         case GROUP_ID_ENUM:
            ProcessGroupIdEnumValidation(setParamValues, mibAttributeValuesByDn[dn]);
            break;
         case GROUP_ID_ENABLE:
            initialize();

            if(!strcmp(enValue.c_str(),"true")||!strcmp(enValue.c_str(),"1"))
            {
               return  ProcessGroupIdEnableValidation(m_nameMap,parameterValueMap,dm,validationFailureDescriptor);
            }
            break;
         case GROUP_ID_KEY:
            initialize();
            return ProcessGroupIdKey(dm,validationFailureDescriptor);
         default:
            TRACE_PRINTF("Group id not known at all.");
            break;

      }
   }

   return true;
}

void initialize()
{
   int size = sizeof(KeysDefination)/sizeof(ValidateKeys) ;
   for(int keyElem = 0; keyElem < size ; keyElem++)
   {
      Dn2KeyMap.insert(pair<string,struct KeyValues *>(KeysDefination[keyElem].key,&KeysDefination[keyElem].Data));
   }
}

bool ProcessGroupIdEnableValidation(DmNameMap &m_nameMap,const ParameterValueMap & parameterValueMap,DmNameMap::const_iterator dm , ValidationFailureDescriptor & validationFailureDescriptor)
{
   u16 cellIdx = 0;
   MibDN dnobj = MibDN::GenerateMibDN( string((dm->second).mibDN) );
   MibDN dnobj1;
   char * cellIdStr = StringUtils::GetMibObjectInstanceNum(dnobj.ToString().substr(0,16));
   if(NULL != cellIdStr)
   {
      cellIdx = atoi(cellIdStr);
   }
   MibDN fapLtednobj = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE, cellIdx);

   DmNameMap::const_iterator keyPresdm;
   MibAccessInterface &m_mib = Tr069Application::GetInstance().GetMibCache();
   string checkkey1,checkkey2,checkkey3,str,key1="",key2="",key3="";
   str= string((dm->second).mibDN).c_str();
   MibAttributeId keyValues[4], PARAM_ID_MAX_ENTRIES;
   MibObjectClass dnClass= MIB_OBJECT_CLASS_INVALID;
   setKeys(dnClass,str,keyValues);
   u32 enable,maxinstances;
   MIOAutoManage::GetInstance().getMaxEntriesParamName(dnobj,PARAM_ID_MAX_ENTRIES);
   m_mib.GetMibAttribute(fapLtednobj,PARAM_ID_MAX_ENTRIES,maxinstances);
   ParameterValueMap::const_iterator it;
   bool keyPres = true; 
   for (it = parameterValueMap.begin(); it != parameterValueMap.end(); ++it)
   {
      string kname,kvalue;
      kname = it->first;
      keyPresdm = m_nameMap.find(kname);
      if(keyPresdm != m_nameMap.end())
      {
         if (((keyPresdm->second).mibAttrId) == keyValues[1])
         {
            key1 = it->second;
         }
         else if (((keyPresdm->second).mibAttrId) == keyValues[2])
         {
            key2 = it->second;
         }
         else
         {
            if (((keyPresdm->second).mibAttrId) == keyValues[3])
            {
               key3 = it->second;
            }
         }
      }
   }

   if(key1 == "")
   {
      if(m_mib.IsMibAttributePresent(dnobj,keyValues[1]))
      {
         m_mib.GetMibAttributeAsString(dnobj,keyValues[1],key1);
      }
      else
      { 
         keyPres = false;
      }
   }
   if(keyValues[2]!=PARAM_ID_INVALID&&(key2=="")&&keyPres)
   {
      if(m_mib.IsMibAttributePresent(dnobj,keyValues[2]))
      {
         m_mib.GetMibAttributeAsString(dnobj,keyValues[2],key2);
      }
      else
      {
         keyPres = false;
      }
   }
   if(keyValues[3]!=PARAM_ID_INVALID&&(key3=="")&&keyPres)
   {
      if(m_mib.IsMibAttributePresent(dnobj,keyValues[3]))
      {
         m_mib.GetMibAttributeAsString(dnobj,keyValues[3],key3);
      }
      else
      {
         keyPres = false;
      }
   }
   if(!keyPres)
   {
      validationFailureDescriptor.Set( ValidationFailureDescriptor::CAUSE_OTHER,"Key values are missing.");
      return false;
   }

   char * index = StringUtils::GetMibObjectInstanceNum(dnobj.ToString());
   if(index != NULL)
   {
      u32 instance = atoi(index);
      MIOAutoManage::GetInstance().getMaxEntriesParamName(dnobj,PARAM_ID_MAX_ENTRIES);
      m_mib.GetMibAttribute(fapLtednobj, PARAM_ID_MAX_ENTRIES, maxinstances);
      for(u32 dnInstance = 0 ; dnInstance < maxinstances  ; dnInstance++)
      {
         dnobj1 =  MibDN::GenerateMibDN(dnClass,dnInstance);
         if(m_mib.IsMibObjectPresent(dnobj1))
         {
            m_mib.GetMibAttribute(dnobj1,keyValues[0],enable);
            if(enable && dnInstance != instance )
            {
               m_mib.GetMibAttributeAsString(dnobj1,keyValues[1],checkkey1);
               if(strcmp(key2.c_str(),""))
               {
                  m_mib.GetMibAttributeAsString(dnobj1,keyValues[2],checkkey2);
               }
               if(strcmp(key3.c_str(),""))
               {
                  m_mib.GetMibAttributeAsString(dnobj1,keyValues[3],checkkey3);
               }
               if((strcmp(checkkey1.c_str(), key1.c_str())==0)&&(strcmp(checkkey2.c_str(),key2.c_str())==0)
                     &&(strcmp(checkkey3.c_str(),key3.c_str())==0))
               {
                  validationFailureDescriptor.Set( ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE,
                        "Duplicate Keys found.");
                  return false;
               }
            }
         }
      }
   }
   return true;
}

bool  ProcessGroupIdKey(DmNameMap::const_iterator dm , ValidationFailureDescriptor & validationFailureDescriptor)
{
   MibDN dnobj = MibDN::GenerateMibDN( string((dm->second).mibDN) );
   MibAccessInterface &m_mib = Tr069Application::GetInstance().GetMibCache();

   if (!m_mib.IsMibObjectPresent(dnobj))
         {
            validationFailureDescriptor.Set( ValidationFailureDescriptor::CAUSE_OBJECT_DOES_NOT_EXIST,
                  "Object not created yetfor this perticular instance.");
            return false;

         }
   u32 en ;
   struct KeyValues *val;
   string str= string((dm->second).mibDN).c_str();
   string keystr;
   for(map<string,struct KeyValues *>::iterator itr = Dn2KeyMap.begin(); itr != Dn2KeyMap.end(); ++itr )
   {
      keystr = itr->first;
      if(strstr(str.c_str(),keystr.c_str()))
      {
         val = itr->second;
         m_mib.GetMibAttribute(dnobj,val->enable,en);
         if(en == 1)
         {
            validationFailureDescriptor.Set( ValidationFailureDescriptor::CAUSE_NOT_VALID_VALUE,
                  "Unable To Modify Key Value. Set Enable To False To Allow Key Modification.");
            return false;
         }
         break;
      }
   }
   return true;
}

bool DataModelManager::ValidateParameterAgainstDataModelTables(const DmNameMap::const_iterator & dm, const string & value, MibAttributeValues & mibAttributeValues)
{
   const ExtDMAttrDefinition * dmAttrDefinition = &(dm->second);

   TRACE_PRINTF("Tr069DataModelManager::ValidateParameterAgainstDataModelTables(%s, %s)", dmAttrDefinition->name.c_str(), value.c_str() );

   shared_ptr<MibAttributeValue> mav = Tr069MibAttributeValueFactory::FromDataModelValue( dmAttrDefinition, value);

   if(mav)
   {
      mibAttributeValues.AddAttribute(dmAttrDefinition->mibAttrId, mav);
      return true;
   }
   else
   {
      /*518/519:modified*/ 
      return false;
   }
}

void setKeys(MibObjectClass & dnClass,string str,MibAttributeId keyValues[])
{
   for(map<string,struct KeyValues *>::iterator itr = Dn2KeyMap.begin(); itr != Dn2KeyMap.end(); ++itr )
   {
      string keystr = itr->first;
      if(strstr(str.c_str(),keystr.c_str()))
      {
         struct KeyValues *val;
         val = itr->second;
         dnClass = val->moc;
         keyValues[0] =  val->enable;
         keyValues[1] =  val->key1 ;
         keyValues[2] =  val->key2 ;
         keyValues[3] =  val->key3 ;
         break;
      }
   }
}

ValidationFailureDescriptor  ProcessGroupIdFactory(const Tr069AttributeValues&, MibAttributeValues&)
{
   ValidationFailureDescriptor validationFailureDescriptor;

   validationFailureDescriptor.Set( ValidationFailureDescriptor::CAUSE_READ_ONLY, "Factory written parameter");

   return validationFailureDescriptor;
}


ValidationFailureDescriptor ProcessGroupIdRemScanOnBoot(const Tr069AttributeValues& av, MibAttributeValues& mav)
{
   u32 newValue = 0;

   Tr069AttributeValues::const_iterator itr;

   for(itr = av.begin(); itr != av.end(); ++itr)
   {
      string name  = itr->first;
      string value = itr->second;

      TRACE_PRINTF( "%s=%s", name.c_str(), value.c_str());

      if( value == "true" )
      {
         newValue = 1;
      }

      if(name == MibAttributeIdToString( PARAM_ID_WCDMA_REM_SCAN_ON_BOOT ))
      {
         TRACE_PRINTF( "%s=%"PRIu32,  MibAttributeIdToString( PARAM_ID_WCDMA_REM_SCAN_ON_BOOT ), newValue);
         mav.AddAttribute(PARAM_ID_WCDMA_REM_SCAN_ON_BOOT, newValue);
      }

      if(name == MibAttributeIdToString( PARAM_ID_LTE_REM_SCAN_ON_BOOT ))
      {
         TRACE_PRINTF( "%s=%"PRIu32,  MibAttributeIdToString( PARAM_ID_LTE_REM_SCAN_ON_BOOT ), newValue);
         mav.AddAttribute(PARAM_ID_LTE_REM_SCAN_ON_BOOT, newValue);
      }

      if(name == MibAttributeIdToString( PARAM_ID_ABORT_REM_SCAN ))
      {
         TRACE_PRINTF( "%s=%"PRIu32,  MibAttributeIdToString( PARAM_ID_ABORT_REM_SCAN ), newValue);
         mav.AddAttribute(PARAM_ID_ABORT_REM_SCAN, newValue);
      }

   }

   ValidationFailureDescriptor validationFailureDescriptor;

   return validationFailureDescriptor;
}

ValidationFailureDescriptor DataModelManager::ProcessGroupIdListValidation(const Tr069AttributeValues& av, MibAttributeValues& mav)
{
   TRACE_PRINTF("ProcessGroupIdListValidation: Group id is List");
   Tr069AttributeValues::const_iterator itr;
   string name;
   string value;

   for(itr = av.begin(); itr != av.end(); ++itr)
   {
      name  = itr->first;
      value = itr->second;

      TRACE_PRINTF( "%s=%s", name.c_str(), value.c_str());

      DmNameMap::const_iterator param = m_nameMap.find(name);

      if( param != m_nameMap.end())
      {
         const ExtDMAttrDefinition * dm = &(param->second);
         if( dm->mibAttrId < NUM_MIB_ATTR_IDS )
         {
            switch(dm->mibAttrId)
            {
               case PARAM_ID_LTE_ALLOWED_DL_EARFCN: 
                  mav.AddAttribute(PARAM_ID_LTE_ALLOWED_DL_EARFCN, value);
                  break;

               case PARAM_ID_LTE_SIGLINK_SERVER_LIST: 
                  mav.AddAttribute(PARAM_ID_LTE_SIGLINK_SERVER_LIST, value);
                  break;

               default: 
                  TRACE_PRINTF("ProcessGroupIdListValidation: Not a valid Parameter under the groupi id List");
                  break;
            }
         } 		
      }
   }
   ValidationFailureDescriptor validationFailureDescriptor;

   return validationFailureDescriptor;
}

ValidationFailureDescriptor DataModelManager::ProcessGroupIdBooleanValidation(const Tr069AttributeValues& av, MibAttributeValues& mav)
{
   TRACE_PRINTF("ProcessGroupIdBooleanValidation: Group id is boolean");
   Tr069AttributeValues::const_iterator itr;
   string name;
   string value;

   for(itr = av.begin(); itr != av.end(); ++itr)
   {
      name  = itr->first;
      value = itr->second;

      TRACE_PRINTF( "%s=%s", name.c_str(), value.c_str());

      DmNameMap::const_iterator param = m_nameMap.find(name);

      if( param != m_nameMap.end())
      {
         const ExtDMAttrDefinition * dm = &(param->second);

         if( dm->mibAttrId < NUM_MIB_ATTR_IDS )
         {
            switch(dm->mibAttrId)
            {
               case PARAM_ID_LTE_FAP_ADMIN_STATE: 
                  mav.AddAttribute(PARAM_ID_LTE_FAP_ADMIN_STATE, value);
                  break;

               case PARAM_ID_LTE_HIGH_SPEED_FLAG: 
                  mav.AddAttribute(PARAM_ID_LTE_HIGH_SPEED_FLAG, value);
                  break;

               case PARAM_ID_LTE_CELL_BARRED: 
                  mav.AddAttribute(PARAM_ID_LTE_CELL_BARRED, value);
                  break;

               case PARAM_ID_LTE_CELL_RESERVE_FOR_OPERATOR: 
                  mav.AddAttribute(PARAM_ID_LTE_CELL_RESERVE_FOR_OPERATOR, value);
                  break;

               case PARAM_ID_LTE_BARRING_FOR_EMERGENCY: 
                  mav.AddAttribute(PARAM_ID_LTE_BARRING_FOR_EMERGENCY, value);
                  break;

               case PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_ENABLE: 
                  mav.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_ENABLE, value);
                  break;

               case PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_MUST_INCLUDE: 
                  mav.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_MUST_INCLUDE, value);
                  break;

               case PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_BLACK_LISTED: 
                  mav.AddAttribute(PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_BLACK_LISTED, value);
                  break;

               case PARAM_ID_LTE_DRX_ENABLE: 
                  mav.AddAttribute(PARAM_ID_LTE_DRX_ENABLE, value);
                  break;

               case PARAM_ID_LTE_TTI_BUNDLING: 
                  mav.AddAttribute(PARAM_ID_LTE_TTI_BUNDLING, value);
                  break;

               case PARAM_ID_LTE_EPC_PLMN_ENABLE: 
                  mav.AddAttribute(PARAM_ID_LTE_EPC_PLMN_ENABLE, value);
                  break;
               default: 
                  TRACE_PRINTF("ProcessGroupIdBooleanValidation: Not a valid Parameter under boolean group");
                  break;
            }     
         }	
      }
   }
   ValidationFailureDescriptor validationFailureDescriptor;

   return validationFailureDescriptor;
}

ValidationFailureDescriptor DataModelManager::ProcessGroupIdEnumValidation(const Tr069AttributeValues& av, MibAttributeValues& mav)
{
   TRACE_PRINTF("ProcessGroupIdEnumValidation: Group id is enum");
   Tr069AttributeValues::const_iterator itr;
   string name;
   string value;

   for(itr = av.begin(); itr != av.end(); ++itr)
   {
      name  = itr->first;
      value = itr->second;

      TRACE_PRINTF( "%s=%s", name.c_str(), value.c_str());

      DmNameMap::const_iterator param = m_nameMap.find(name);

      if( param != m_nameMap.end())
      {
         const ExtDMAttrDefinition * dm = &(param->second);
         if( dm->mibAttrId < NUM_MIB_ATTR_IDS )
         {
            mav.AddAttribute(dm->mibAttrId, value);
         }	
      } 
   }
   ValidationFailureDescriptor validationFailureDescriptor;

   return validationFailureDescriptor;
}

void ProcessGroupIdList(const ExtDMAttrDefinition * dmDefinition, ParameterList & parameterList)
{
   TRACE_PRINTF("ProcessGroupIdList: Group id is List");
   MibAccessInterface& m_mib = Tr069Application::GetInstance().GetMibCache();

   string name;
   string value;

   MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

   bool objPresent = m_mib.IsMibObjectPresent( dn );

   if(objPresent)
   {
      bool EarfcnDlPresent = m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_ALLOWED_DL_EARFCN);
      bool S1ServerListPresent = m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_SIGLINK_SERVER_LIST);

      if(EarfcnDlPresent)
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_ALLOWED_DL_EARFCN, value );
         parameterList.AppendParameter(name, value);
      }
      if(S1ServerListPresent)
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_SIGLINK_SERVER_LIST, value );
         parameterList.AppendParameter(name, value);
      }
   }
   else
   {
      TRACE_PRINTF("ProcessGroupIdList: Object not present under Group id List");
   }
}

void ProcessGroupIdBoolean(const ExtDMAttrDefinition * dmDefinition, ParameterList & parameterList)
{
   TRACE_PRINTF("ProcessGroupIdBoolean: Group id is Booelan");
   MibAccessInterface& m_mib = Tr069Application::GetInstance().GetMibCache();

   string name;
   string value;

   MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

   bool objPresent = m_mib.IsMibObjectPresent( dn );

   if(objPresent)
   {
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_FAP_ADMIN_STATE))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_FAP_ADMIN_STATE, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_HIGH_SPEED_FLAG))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_HIGH_SPEED_FLAG, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_CELL_BARRED))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_CELL_BARRED, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_CELL_RESERVE_FOR_OPERATOR))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_CELL_RESERVE_FOR_OPERATOR, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_BARRING_FOR_EMERGENCY))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_BARRING_FOR_EMERGENCY, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_ENABLE))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_ENABLE, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_MUST_INCLUDE))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_MUST_INCLUDE, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_BLACK_LISTED))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_NEIGH_LIST_LTE_CELL_BLACK_LISTED, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn,PARAM_ID_LTE_DRX_ENABLE))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_DRX_ENABLE, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_TTI_BUNDLING))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_TTI_BUNDLING, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_EPC_PLMN_ENABLE))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_EPC_PLMN_ENABLE, value );
         parameterList.AppendParameter(name, value);
      }
   }
   else
   {
      TRACE_PRINTF("ProcessGroupIdBoolean: Group id is INVALID");
   }
}

void ProcessGroupIdEnum(const ExtDMAttrDefinition * dmDefinition, ParameterList & parameterList)
{
   TRACE_PRINTF("ProcessGroupIdEnum: Group id is Enum");
   MibAccessInterface& m_mib = Tr069Application::GetInstance().GetMibCache();

   string name;
   string value;

   MibDN dn = MibDN::GenerateMibDN( string(dmDefinition->mibDN) );

   bool objPresent = m_mib.IsMibObjectPresent( dn );

   if(objPresent)
   {
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_S1CON_MODE))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_S1CON_MODE, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_DL_BANDWIDTH))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_DL_BANDWIDTH, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_UL_BANDWIDTH))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_UL_BANDWIDTH, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_CIPHERING_ALGO_LIST))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_CIPHERING_ALGO_LIST, value );
         parameterList.AppendParameter(name, value);
      }
      if(m_mib.IsMibAttributePresent(dn, PARAM_ID_LTE_INTEGRITY_ALGO_LIST))
      {
         name  = dmDefinition->name;
         m_mib.GetMibAttribute(dn, PARAM_ID_LTE_INTEGRITY_ALGO_LIST, value );
         parameterList.AppendParameter(name, value);
      }
   }
   else
   {
      TRACE_PRINTF("ProcessGroupIdEnum: Group id is INVALID");
   }
}

}
