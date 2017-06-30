///////////////////////////////////////////////////////////////////////////////
//
// Tr069MibAttributeValueFactory.h
//
// Class for managing thirdparty data model.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069MibAttributeValueFactory_h_
#define __Tr069MibAttributeValueFactory_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/Trace.h>
#include <mib-common/MibAttributeValues.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "DataModelTypes.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;

namespace tr069
{


class Tr069MibAttributeValueFactory
{
public:
    static shared_ptr<MibAttributeValue> FromDataModelValue(const ExtDMAttrDefinition * dmDef , const string & dmValue);
    static bool ToDataModelValue(const ExtDMAttrDefinition * dmDef , string & dmValue, ExtDMAttrDataType & dmType);
    static const char* AlarmNotificationTypeStrArr[3];
private:

    // Set of factory methods to create correct MIB type
    static shared_ptr<MibAttributeValueU32> CreateU32(const ExtDMAttrDefinition * dmDef , const string & dmValue);
    static shared_ptr<MibAttributeValueU32Array> CreateU32Array(const ExtDMAttrDefinition * dmDef , const string & dmValue);
    static shared_ptr<MibAttributeValueS32> CreateS32(const ExtDMAttrDefinition * dmDef , const string & dmValue);
    static shared_ptr<MibAttributeValueS32Array> CreateS32Array(const ExtDMAttrDefinition * dmDef , const string & dmValue);
    static shared_ptr<MibAttributeValueString> CreateString(const ExtDMAttrDefinition * dmDef , const string & dmValue);
    static shared_ptr<MibAttributeValueStringArray> CreateStringArray(const ExtDMAttrDefinition * dmDef , const string & dmValue);
    static shared_ptr<MibAttributeValueU32> CreateEnum(const ExtDMAttrDefinition * dmDef , const string & dmValue);
    static shared_ptr<MibAttributeValueU32Array> CreateEnumArray(const ExtDMAttrDefinition * dmDef , const string & dmValue);

    // Set of factory methods to create correct DataModel type
    static bool CreateDmInt(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType);
    static bool CreateDmUInt(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType);
    static bool CreateDmString(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType);
    static bool CreateDmBoolean(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType);
    static bool CreateDmDateTime(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType);
    static bool CreateDmDataType(const ExtDMAttrDefinition * dmDef, string & dmValue, ExtDMAttrDataType & dmType);

    // Common conversion helpers
    static void ConvertCsvDataModel2Mib( const ExtDMAttrDefinition * dmDef , const string & dataModelValue, string & mibValue);
    static void ConvertDataModel2Mib( const ExtDMAttrDefinition * dmDef , const string & dataModelValue, string & mibValue);

    static void ConvertCsvMib2DataModel( const ExtDMAttrDefinition * dmDef , const string & mibValue, string & dataModelValue);
    static void ConvertMib2DataModel( const ExtDMAttrDefinition * dmDef , const string & mibValue, string & dataModelValue);

};





}
#endif
