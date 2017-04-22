///////////////////////////////////////////////////////////////////////////////
//
// ValidationReferences.h
//
//  Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidationReferences_h_
#define __ValidationReferences_h_
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include<string>
#include<map>
#include<utility>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include <mib-common/MibAttributeDescriptors.h>
#include <MibAttributes.h>
#include <system/Trace.h>
#include <mib-common/MibAttributeValues.h>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
using namespace boost;

class ValidationReferences
{
   public:
   static ValidationReferences& GetInstance();
   static ValidationReferences* s_instance;
   ValidationReferences(){};
   void setParameterValue( MibAttributeId id , shared_ptr<MibAttributeValue> value,MibDN dn);
   bool getParameterValue( MibAttributeId id ,u32&,MibDN dn);
   bool getParameterValue( MibAttributeId id ,s32&,MibDN dn);
   bool getParameterValue( MibAttributeId id ,std::string&,MibDN dn);
   bool getParameterValue( MibAttributeId id ,std::vector<std::string>&,MibDN dn); 
   bool getParameterValue( MibAttributeId id ,std::vector<u32>&,MibDN dn);
   bool getParameterValue( MibAttributeId id ,std::vector<s32>&,MibDN dn);
   void DeleteDnFromMap(MibDN dn); 
   private:
   static std::map<boost::tuple<MibDN ,MibAttributeId> ,shared_ptr<MibAttributeValue> > ParameterDataMap;
   
};
#endif

