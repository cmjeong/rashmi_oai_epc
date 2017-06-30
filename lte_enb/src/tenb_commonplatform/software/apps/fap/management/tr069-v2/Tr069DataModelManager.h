///////////////////////////////////////////////////////////////////////////////
//
// DataModelManager.h
//
// Class for managing thirdparty data model.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069DataModelManager_h_
#define __Tr069DataModelManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/Trace.h>
#include <system/StringUtils.h>
#include <mib-common/MibAttributeValues.h>
#include <mib-common/MIOAutoManage.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "DataModelTypes.h"
#include "Tr069ParameterList.h"
#include "Tr069ParameterInfoList.h"
#include "Tr069RpcSetParameterAttribute.h"

#define MAX_NO_OF_FAULTS 5
///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace tr069;

namespace tr069
{


class MibDnAttribute
{
public:
    MibDnAttribute(const ExtDMAttrDefinition *);
    MibDnAttribute(const MibDN & dn, MibAttributeId id);

    bool operator<(const MibDnAttribute & rhs) const;

    MibDN m_dn;
    MibAttributeId m_id;
};

struct KeyValues
{
        MibObjectClass moc;
        MibAttributeId enable;
        MibAttributeId key1;
        MibAttributeId key2;
        MibAttributeId key3;
};

typedef struct KeysInfo
{
    struct KeyValues Data ;
    string key;
}ValidateKeys;

typedef map< string /* name  */,              ExtDMAttrDefinition  /* defintion */ > DmNameMap;
typedef multimap< MibDnAttribute, ExtDMAttrDefinition /* defintion */ > DmMibAttributeIdMap;
typedef map<string,struct KeyValues *> KeyMap ;

class DataModelManager
{
private:
    // Is singleton so private constructor.
    DataModelManager(MibAccessInterface& mib);

public:
    /**
     * Construction / destruction.
     */
    ~DataModelManager ();
    static DataModelManager& GetInstance();

    void AddParameterToParameterList( const string & name, ParameterList & parameterList );
    void AddParameterToCliParameterList( const string & name, ParameterList & parameterList );
    void AddParameterToAttributeList( const string & name, AttributeList & parameterList );
    void AddParameterInfoToParameterList( const string & name, ParameterInfoList & parameterInfoList );
    const set<string> & GetForcedInformParameterSet();

    bool ValidateSetParamterValue( const ParameterValueMap & parameterValueMap );
    void SetParamterAttribute( const RpcSetParameterAttribute & rawRpcSetParameterAttribute, SetParameterAttributeNotifications & span );

    void AddMibAttributesForDataModelParameters( MibAttributeIdsByDn & attributes );
    void MibAttributeUpdatedNotification( const MibDN & dn, MibAttributeId attr);

    void UpdateDataModelAttributeDefinition( const ExtDMAttrDefinition dmAttrDefinition);
    void updateDmDef(const ExtDMAttrDefinition dmAttrDefinition);
    u32  changeApplies;
    bool HandleCliSetParameterValue( string name,string value,string &result);
    bool getAttrInfo(const char* name, MibAttributeId &attr, char *dn);
    void getAllAttrInfo (const char* name,std::vector<std::string> &names, std::vector<MibAttributeId> &attr, std::vector<std::string > &dn);
    DmNameMap m_nameMap;
private:
    static DataModelManager* s_instance;

    ValidationFailureDescriptor ProcessGroupIdEnumValidation(const Tr069AttributeValues& av, MibAttributeValues& mav);
    ValidationFailureDescriptor ProcessGroupIdBooleanValidation(const Tr069AttributeValues& av, MibAttributeValues& mav);
    ValidationFailureDescriptor ProcessGroupIdListValidation(const Tr069AttributeValues& av, MibAttributeValues& mav);
    void AppendGroupToParameterList( const ExtDMAttrDefinition * dmDefinition, ParameterList & parameterList);
    SetParameterAttributeNotifications FilterSetParamAttribute( const SetParameterAttributeNotification & in );
    bool ValidateSetParameterValueGroups(const ParameterValueMap & parameterValueMap, Tr069AttributeValues setParamValues , MibAttributeValuesByDn & mibAttributeValuesByDn, ValidationFailureDescriptor & validationFailureDescriptor );
    bool ValidateParameterAgainstDataModelTables(const DmNameMap::const_iterator & dm, const string & value, MibAttributeValues& mibAttributeValues);

    shared_ptr<MibAttributeValue> CreateMibAttributeValue(const DmNameMap::const_iterator & dm, const string & value);
    static MibAttributeIdsByDn ConvertExtDmDefinitionToMibAttributeIdsByDn(const ExtDMAttrDefinition *);
    void Reset()
    {
       for(int i =0;i< MAX_NO_OF_FAULTS ; i++)
       {
          m_xmlFaultString[i] = "";
          fault_parameters[i] = "";
       }
    }
    MibAccessInterface& m_mib;

    string m_xmlFaultString[MAX_NO_OF_FAULTS];
    string fault_parameters[MAX_NO_OF_FAULTS]; 
    bool m_validationOk;

    DmMibAttributeIdMap m_paramIdMap;
    set<string> m_forcedInformParameters;
    Tr069ParamAttributeNvStore m_paramAttNvStore;
    int numCell;
};
}
#endif
