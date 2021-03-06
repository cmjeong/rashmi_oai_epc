///////////////////////////////////////////////////////////////////////////////
//
// Tr069SupportedAlarmManager
//
// Wraps the libcsoap interface into an easier to use OO class.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069SupportedAlarmManager_h_
#define __Tr069SupportedAlarmManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <set>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <system/AlarmEventList.h>
#include <system/AlarmEventType.h>
#include <system/AlarmPerceivedSeverity.h>
#include <system/AlarmReportingMechanism.h>
#include <mib-common/MibDN.h>
#include <mib-common/MibAttributeValues.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069SupportedAlarm.h"
#include "Tr069CurrentAlarmManager.h"

using namespace std;

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class SupportedAlarmManager : public AlarmEventListListener
{

public:
    SupportedAlarmManager( MibAccessInterface& mib, SendMessageInterface &messenger );
    virtual ~SupportedAlarmManager(){};

    void ListenAlarmEvent( const AlarmEvent & tr196Alarm );


private:
    MibAccessInterface& m_mib;
    SendMessageInterface &m_messenger;

    map<u32, SupportedAlarm> m_supportedAlarms;
    CurrentAlarmManager m_currentAlarmManager;
};


}

#endif
