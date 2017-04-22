///////////////////////////////////////////////////////////////////////////////
//
// DataModelTypes.h
//
// This header is to be used from and together with headers in autogen directory
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __DataModelTypes_h_
#define __DataModelTypes_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>

#include <map>
#include <string>
#include <MibAttributeId.h>
#include "autogen/MibGroupEnum.h"


using namespace std;

namespace tr069 {

/* Access type is limited from Core Network point of view.
 * Developers should ensure proper access type per equipment (HMS / HNB) */
typedef enum
{
    READ_ONLY,
    READ_WRITE
} ExtDMAttrAccessType;

typedef enum
{
    INT = 0,
    U_INT,
    STRING,
    BOOLEAN,
    DATE_TIME,
    OBJECT,
    MIO,
    DATA_TYPE
} ExtDMAttrDataType;

typedef enum
{
    NO_NOTIFICATION = 0,
    PASSIVE_NOTIFICATION,
    ACTIVE_NOTIFICATION
} ExtDMAttrNotificationType;

typedef enum
{
   Immediate = 0,
   OnReboot,
   OnEnable
} ExtDMAttrChangeApplies;

typedef struct
{
    string                    name;
    ExtDMAttrAccessType       access;
    ExtDMAttrDataType         type;
    const char*               minVal;
    const char*               maxVal;
    bool					         isList;
    ExtDMAttrNotificationType notify;
    bool                      forcedInform;
    ExtDMAttrChangeApplies    changeApplies;
    const char*               defaultValue;
    ExtDataModelAttrGroupId   mibGroup;
    string		               mibDN;
    MibAttributeId            mibAttrId;
} ExtDMAttrDefinition;


typedef std::map<std::string /* TR196_098 name */, std::string /* value */> Tr069AttributeValues;


}

#endif
