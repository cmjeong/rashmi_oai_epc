///////////////////////////////////////////////////////////////////////////////
//
// Tr069Parameters.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <system/Trace.h>
#include <messaging/messages/common/MfOpStateInformInd.h>
#include <messaging/messages/common/RemScanReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Parameters.h"
#include "Tr069TransactionSessionCommand.h"

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

using namespace std;

namespace tr069
{

NsnParameterManager* NsnParameterManager::s_instance = NULL;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
const char * NsnParameter::ActionReset          = "Device.Services.X_NSN_COM_NsnActions.Reset";
const char * NsnParameter::ActionRescan         = "Device.Services.X_NSN_COM_NsnActions.Rescan";

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

const NsnParameter::NsnParameterTypeDefinition NsnParameter::nsnParameterDictionary[] =
{
   {   WidgetActionReset,          ActionReset ,               MIB_OBJECT_CLASS_INVALID,       PARAM_ID_INVALID,                                   NULL,                       FGW_WRITE },
   {   WidgetActionRescan,         ActionRescan ,              MIB_OBJECT_CLASS_INVALID,       PARAM_ID_INVALID,                                   NULL,                       FGW_WRITE },

};

const size_t NsnParameter::nsnParameterDictionaryLength = sizeof(nsnParameterDictionary)/sizeof(nsnParameterDictionary[0]);

NsnParameterManager::NsnParameterManager()
{
   unsigned i;

   for(i = 0; i < NsnParameter::nsnParameterDictionaryLength; i++)
   {
      shared_ptr<NsnParameter> nsnParameter;
      static const NsnParameter::NsnParameterTypeDefinition * paramDef;

      paramDef = &NsnParameter::nsnParameterDictionary[i];

      switch(paramDef->widget)
      {
         case NsnParameter::WidgetActionRescan:
            {
               nsnParameter = shared_ptr<NsnParameter>(new NsnParameterActionRescan(paramDef->fullyQualifiedName, paramDef->mibObjectClass, paramDef->mibAttributeId, paramDef->validator, paramDef->flags ));
            }
            break;

         case NsnParameter::WidgetActionReset:
            {
               nsnParameter = shared_ptr<NsnParameter>(new NsnParameterActionReset(paramDef->fullyQualifiedName, paramDef->mibObjectClass, paramDef->mibAttributeId, paramDef->validator, paramDef->flags ));
            }
            break;

         default:
            RSYS_ASSERT_PRINTF(false,"Unhandled parameter %s", paramDef->fullyQualifiedName);
            break;

      }

      m_parameters [NsnParameter::nsnParameterDictionary[i].fullyQualifiedName] = nsnParameter;
      if(NsnParameter::nsnParameterDictionary[i].mibAttributeId != PARAM_ID_INVALID)
      {
         m_mibParamMap[NsnParameter::nsnParameterDictionary[i].mibAttributeId]        = nsnParameter;
      }

      TRACE_PRINTF_LEV(TRACE_VERBOSE,"Add NsnParameter to NsnParameterManager(%s)",NsnParameter::nsnParameterDictionary[i].fullyQualifiedName);
   }

}

NsnParameterManager& NsnParameterManager::GetInstance()
{
   ENTER
      ();

   if (s_instance == NULL)
   {
      s_instance = new NsnParameterManager();

      RSYS_ASSERT(s_instance);
   }

   RETURN (*s_instance);
}

const string & NsnParameterManager::FgwReadValue( const string & parameterName )
{
   static string notFound("");
   shared_ptr<NsnParameter> nsnParameter = m_parameters[parameterName];

   if(nsnParameter)
   {
      return nsnParameter->FgwReadValue();
   }

   return notFound;
}

void NsnParameterManager::FgwWriteValue( MibAttributeValues& mibAttrs, const char * parameterName, string & value )
{
   shared_ptr<NsnParameter> nsnParameter = m_parameters[parameterName];

   if(nsnParameter)
   {
      nsnParameter->FgwWriteValue(mibAttrs, value);
   }
}

void NsnParameterManager::GetMibValue( const string& parameterName, string & value )
{
   shared_ptr<NsnParameterString> nsnParameter = dynamic_pointer_cast<NsnParameterString>(m_parameters[parameterName]);

   if(nsnParameter)
   {
      value = nsnParameter->GetMibParam();
   }
   else
   {
      RSYS_ASSERT_PRINTF(false, "%s not string parameter.",parameterName.c_str());
   }
}

void NsnParameterManager::ChangeNotification( const string& parameterName, string & value )
{
   shared_ptr<NsnParameter> nsnParameter = m_parameters[parameterName];

   RSYS_ASSERT(nsnParameter);

   nsnParameter->ChangeNotification(value);
}

void NsnParameterManager::SetParameter( const string& parameterName, const string & value )
{
   shared_ptr<NsnParameter> nsnParameter = m_parameters[parameterName];

   if(nsnParameter)
   {
      MibAttributeValues attrs;

      nsnParameter->FgwWriteValue(attrs, value);

      Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);
   }
   else
   {
      TRACE_PRINTF("Parameter %s not recognised.", parameterName.c_str() );
   }
}

bool NsnParameterManager::SetParameterValueStruct( ParameterList_t  & paramValueStructs, std::ostringstream & osstreamFault )
{
   bool commitLooksOk = true;
   map< shared_ptr<NsnParameter>, string > parameters;

   for(ParameterList_t::iterator i = paramValueStructs.begin();
         i != paramValueStructs.end();
         i++)
   {
      shared_ptr<ParameterValueStruct> pvs = i->second;

      string & name  = pvs->m_name;
      string & value = pvs->m_value;

      if(!QueryNameIsPartiallyQualifiedPath(name))
      {
         shared_ptr<NsnParameter> nsnParameter = m_parameters[name];

         if(nsnParameter)
         {
            if(nsnParameter->GetWriteable())
            {
               map< shared_ptr<NsnParameter>, string >::const_iterator j = parameters.find(nsnParameter);

               bool parameterNotFound = (j == parameters.end());

               if(parameterNotFound)
               {
                  if(nsnParameter->QueryParameterValid(value))
                  {
                     parameters[nsnParameter] = value;
                  }
                  else
                  {
                     osstreamFault <<
                        "<SetParameterValuesFault>"
                        "<ParameterName>" << name << "</ParameterName>"
                        "<FaultCode>9003</FaultCode>"
                        "<FaultString>Invalid parameter value (" <<  value << ").</FaultString>"
                        "</SetParameterValuesFault>";

                     commitLooksOk = false;
                  }
               }
               else
               {
                  TRACE_PRINTF("SetParameterValueStruct(%s) parameter duplicated.", name.c_str());

                  osstreamFault <<
                     "<SetParameterValuesFault>"
                     "<ParameterName>" << name << "</ParameterName>"
                     "<FaultCode>9003</FaultCode>"
                     "<FaultString>Invalid arguments (duplicated).</FaultString>"
                     "</SetParameterValuesFault>";

                  commitLooksOk = false;
               }
            }
            else
            {
               TRACE_PRINTF("SetParameterValueStruct(%s) {not readable}", name.c_str());

               osstreamFault <<
                  "<SetParameterValuesFault>"
                  "<ParameterName>" << name << "</ParameterName>"
                  "<FaultCode>9005</FaultCode>"
                  "<FaultString>read-only</FaultString>"
                  "</SetParameterValuesFault>";

               commitLooksOk = false;
            }
         }
         else
         {
            TRACE_PRINTF("SetParameterValueStruct(%s) {not found}", name.c_str());

            osstreamFault <<
               "<SetParameterValuesFault>"
               "<ParameterName>" << name << "</ParameterName>"
               "<FaultCode>9005</FaultCode>"
               "<FaultString>Parameter not recognised</FaultString>"
               "</SetParameterValuesFault>";

            commitLooksOk = false;
         }
      }
      else
      {
         TRACE_PRINTF("SetParameterValueStruct(%s) {partially qualified path} not supported", name.c_str());

         osstreamFault <<
            "<SetParameterValuesFault>"
            "<ParameterName>" << name << "</ParameterName>"
            "<FaultCode>9005</FaultCode>"
            "<FaultString>Attempt to set partially qualified parameters</FaultString>"
            "</SetParameterValuesFault>";

         commitLooksOk = false;
      }
   }

   if(commitLooksOk)
   {
      RSYS_ASSERT(paramValueStructs.size() == parameters.size());

      MibAttributeValues attrs;

      for(map< shared_ptr<NsnParameter>, string >::iterator i = parameters.begin();
            i != parameters.end();
            i++)
      {
         shared_ptr<NsnParameter> nsnParameter = i->first;
         string & value = i->second;

         nsnParameter->FgwWriteValue(attrs, value);
      }

      if( attrs.GetAttributeCount() == 0 )
      {
         TRACE_PRINTF("No commit to MIB for SetParameterValue");
      }
      else
      {
         Tr069Application::GetInstance().GetMibCache().SetMibAttributes(attrs, ENTITY_TR069);
      }
   }

   return commitLooksOk;
}

bool NsnParameterManager::QueryNameIsPartiallyQualifiedPath( const string & parameterName)
{
   bool partiallyQualifiedPath = false;

   if(parameterName.length() > 0)
   {
      partiallyQualifiedPath = ('.' == parameterName.at(parameterName.length() - 1));
   }

   return partiallyQualifiedPath;
}

void NsnParameterActionRescan::FgwWriteValue( MibAttributeValues& mibAttrs, const string & value )
{
   RemScanReq remScanReq;
   Tr069Application::GetInstance().SendMessage(remScanReq, ENTITY_OAM, ENTITY_TR069);
}

void NsnParameterActionReset::FgwWriteValue( MibAttributeValues& mibAttrs, const string & value )
{
   Tr069Application::GetInstance().RebootFapViaOam();
}
}
