///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParameterValueChangeNotificationManager.h
//
// Class for managing notifications of Parameter Value Changes.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069ParameterValueChangeNotificationManager_h_
#define __Tr069ParameterValueChangeNotificationManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include <set>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "DataModelTypes.h"
#include "CwmpInform.h"
#include "Tr069ParameterValueChange_fsm.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

namespace tr069
{

typedef ExtDMAttrNotificationType Tr069ParamAttributes;

typedef set< string /*param*/> ChangedParams;
typedef map< string /*param*/, Tr069ParamAttributes > AttributesMap;

class Tr069ParameterValueChangeNotificationManager : public ParameterValueChangeFsmInterface
{
private:
    // Is singleton so private constructor.
    Tr069ParameterValueChangeNotificationManager();

public:
    /**
     * Construction / destruction.
     */
    virtual ~Tr069ParameterValueChangeNotificationManager ();
    static Tr069ParameterValueChangeNotificationManager& GetInstance();

    void NotificationValueChange( const string & name );

    void RemoveParmeterFromPendingList( const string & name );
    bool QueryIfActiveValueChangeNotificationStillOutstanding();
    bool QueryIfAnyValueChangeNotificationStillOutstanding();

    void SetParamterAttributes( const string & name, Tr069ParamAttributes attrib );

    void InformManagementServer( CwmpInform & inform );

    void SetHmsConnectionState( bool connected );

    void ClearPendingValueChanges();

    bool HandleTimerExpiry(threeway::TimerHandle expiredTimer);
    Tr069ParamAttributes GetAttrId(const string & name);
private:
    static Tr069ParameterValueChangeNotificationManager* s_instance;

    ChangedParams m_pendingNotifications;
    AttributesMap m_paramAttributes;

    threeway::TimerHandle m_activeNotifyPendingTimer;

    Tr069ParameterValueChangeInterfaceDefinition();
    ParameterValueChangeFsm m_fsm;
};



}
#endif
