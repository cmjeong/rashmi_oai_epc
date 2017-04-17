///////////////////////////////////////////////////////////////////////////////
//
// ValidationReferences.cpp 
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include<string>
#include<map>
#include<utility>
#include <mib-common/MibAttributeDescriptors.h>
#include <MibAttributes.h>
#include <system/Trace.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include <mib-common/MibAttributeValues.h>
#include "ValidationReferences.h"
using namespace boost;
std::map<boost::tuple<MibDN,MibAttributeId> ,shared_ptr<MibAttributeValue> > ValidationReferences::  ParameterDataMap;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
ValidationReferences* ValidationReferences::s_instance = NULL;
ValidationReferences& ValidationReferences::GetInstance()
{
   ENTER ();
   if( s_instance == NULL)
   {
      TRACE_PRINTF("%s  Creating Instance for ValidationReferences",__FUNCTION__);
      s_instance = new ValidationReferences();
   }
   RETURN(*s_instance);
}

bool ValidationReferences::getParameterValue(  MibAttributeId id ,std::vector<s32>&  RequestS32Array,MibDN dn)
{
   ENTER ();
   
   if((ValidationReferences::ParameterDataMap.find(make_tuple(dn,id)))!=(ValidationReferences::ParameterDataMap.end()))
   { 
      TRACE_PRINTF("%s  Reading the value of %s (sucess) ",__FUNCTION__,getMibAttributeName(id));
      RequestS32Array=ValidationReferences::ParameterDataMap[make_tuple(dn,id)]->GetValueS32Array();
      return true;
   }
   else
   {
      TRACE_PRINTF("%s  Reading the value of %s (Value not filled yet in ReferenceDatabase) ",__FUNCTION__,getMibAttributeName(id));
      return false;
   }
}

bool ValidationReferences::getParameterValue(  MibAttributeId id ,std::vector<u32>&  RequestU32Array,MibDN dn)
{
   ENTER ();
   if((ValidationReferences::ParameterDataMap.find(make_tuple(dn,id)))!=(ValidationReferences::ParameterDataMap.end()))
   {
      TRACE_PRINTF("%s  Reading the value of %s (sucess) ",__FUNCTION__,getMibAttributeName(id));
      RequestU32Array=ValidationReferences::ParameterDataMap[make_tuple(dn,id)]->GetValueU32Array();
      return true;
   }
   else
   {
      TRACE_PRINTF("%s  Reading the value of %s (Value not filled yet in ReferenceDatabase) ",__FUNCTION__,getMibAttributeName(id));
      return false;
   }
}

bool ValidationReferences::getParameterValue(  MibAttributeId id ,std::vector<std::string>&  RequestStringArray,MibDN dn)
{
   ENTER ();
   if((ValidationReferences::ParameterDataMap.find(make_tuple(dn,id)))!=(ValidationReferences::ParameterDataMap.end()))
   {
      TRACE_PRINTF("%s  Reading the value of %s (sucess) ",__FUNCTION__,getMibAttributeName(id));
      RequestStringArray=ValidationReferences::ParameterDataMap[make_tuple(dn,id)]->GetValueStringArray();
      return true;
   }
   else
   {
      TRACE_PRINTF("%s  Reading the value of %s (Value not filled yet in ReferenceDatabase) ",__FUNCTION__,getMibAttributeName(id));
      return false;
   }
}

bool ValidationReferences::getParameterValue(  MibAttributeId id ,u32& RequestU32Value,MibDN dn)
{
   ENTER ();
   if((ValidationReferences::ParameterDataMap.find(make_tuple(dn,id)))!=(ValidationReferences::ParameterDataMap.end()))
   {
      TRACE_PRINTF("%s  Reading the value of %s (sucess) ",__FUNCTION__,getMibAttributeName(id));
      RequestU32Value=ValidationReferences::ParameterDataMap[make_tuple(dn,id)]->GetValueU32();
      return true;
   }
   else
   {
      TRACE_PRINTF("%s  Reading the value of %s (Value not filled yet in ReferenceDatabase) ",__FUNCTION__,getMibAttributeName(id));
      return false;
   }
}

bool ValidationReferences::getParameterValue(  MibAttributeId id ,s32& RequestS32Value,MibDN dn)
{
   ENTER ();
   if((ValidationReferences::ParameterDataMap.find(make_tuple(dn,id)))!=(ValidationReferences::ParameterDataMap.end()))
   {
      TRACE_PRINTF("%s  Reading the value of %s (sucess) ",__FUNCTION__,getMibAttributeName(id));
      RequestS32Value=ValidationReferences::ParameterDataMap[make_tuple(dn,id)]->GetValueS32();
      return true;
   }
   else
   {
      TRACE_PRINTF("%s  Reading the value of %s (Value not filled yet in ReferenceDatabase) ",__FUNCTION__,getMibAttributeName(id));
      return false;
   }
}

bool ValidationReferences::getParameterValue(  MibAttributeId id ,std::string& RequestStringValue,MibDN dn)
{
   ENTER ();
   if((ValidationReferences::ParameterDataMap.find(make_tuple(dn,id)))!=(ValidationReferences::ParameterDataMap.end()))
   {
      TRACE_PRINTF("%s  Reading the value of %s (sucess) ",__FUNCTION__,getMibAttributeName(id));
      RequestStringValue=ValidationReferences::ParameterDataMap[make_tuple(dn,id)]->GetValueString();
      return true;
   }
   else
   {
      TRACE_PRINTF("%s  Reading the value of %s (sucess) ",__FUNCTION__,getMibAttributeName(id));
      return false;
   }
}

void ValidationReferences::DeleteDnFromMap(MibDN dn)
{
   map<boost::tuple<MibDN ,MibAttributeId> ,shared_ptr<MibAttributeValue> >::iterator iter =  ValidationReferences::ParameterDataMap.begin();
   map<boost::tuple<MibDN ,MibAttributeId> ,shared_ptr<MibAttributeValue> >::iterator niter =  ValidationReferences::ParameterDataMap.begin();
   while(iter != ValidationReferences::ParameterDataMap.end())
   {
      if(dn == get<0>(iter->first))
      {
         niter = iter;
         iter++; 
         ValidationReferences::ParameterDataMap.erase(niter);
         continue;
      }
      iter++;
   }
}

void ValidationReferences::setParameterValue( MibAttributeId id , shared_ptr<MibAttributeValue> value,MibDN dn)
{ 
   ENTER ();
   TRACE_PRINTF("%s  Setting  the value of Attribute %s  %s  ",__FUNCTION__,getMibAttributeName(id),value->ToString().c_str());
   ValidationReferences::ParameterDataMap[make_tuple(dn,id)]=value;
}
