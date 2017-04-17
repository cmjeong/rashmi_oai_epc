///////////////////////////////////////////////////////////////////////////////
//
// Tr069ParameterValueChangeNotificationManager.cpp
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

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069SetParameterValueManager.h"
#include "Tr069ParameterValueChangeNotificationManager.h"
#include "Tr069DataModelManager.h"
#include "autogen/Tr069DataModel.h"

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


Tr069ParameterValueChangeNotificationManager* Tr069ParameterValueChangeNotificationManager::s_instance = NULL;


Tr069ParameterValueChangeNotificationManager& Tr069ParameterValueChangeNotificationManager::GetInstance()
{
    ENTER
    ();

    if (s_instance == NULL)
    {
        s_instance = new Tr069ParameterValueChangeNotificationManager();

        RSYS_ASSERT(s_instance);
    }

    RETURN (*s_instance);
}

Tr069ParameterValueChangeNotificationManager::Tr069ParameterValueChangeNotificationManager() :
        m_activeNotifyPendingTimer(NULL_TIMER),
        m_fsm(*this,true,"PVC")
{

}

Tr069ParameterValueChangeNotificationManager::~Tr069ParameterValueChangeNotificationManager()
{
    m_pendingNotifications.clear();
}

void Tr069ParameterValueChangeNotificationManager::NotificationValueChange( const string & name )
{
    TRACE_PRINTF("Tr069ParameterValueChangeNotificationManager::NotificationValueChange %s", name.c_str());

    AttributesMap::const_iterator i = m_paramAttributes.find(name);

    if(i != m_paramAttributes.end())
    {
        Tr069ParamAttributes paramAttrib = i->second;

        if(    (paramAttrib == PASSIVE_NOTIFICATION)
            || (paramAttrib == ACTIVE_NOTIFICATION))
        {
            TRACE_PRINTF("ValueChange(%s)", name.c_str());
            m_pendingNotifications.insert(name);
        }

        if( paramAttrib == ACTIVE_NOTIFICATION )
        {
            m_fsm.InjectActiveNotify(NULL);
        }
    }
}

void Tr069ParameterValueChangeNotificationManager::RemoveParmeterFromPendingList( const string & name )
{
    ChangedParams::iterator i = m_pendingNotifications.find(name);

    if(i != m_pendingNotifications.end())
    {
        TRACE_PRINTF("~ValueChange(%s)", name.c_str());
        m_pendingNotifications.erase(i);
    }
}

void Tr069ParameterValueChangeNotificationManager::SetHmsConnectionState( bool connected )
{
    if(connected)
    {
        m_fsm.InjectHmsConnection(NULL);
    }
    else
    {
        m_fsm.InjectHmsDisconnection(NULL);
    }
}


bool Tr069ParameterValueChangeNotificationManager::QueryIfActiveValueChangeNotificationStillOutstanding()
{
    bool activeNotificationFound = false;

    for( ChangedParams::iterator i = m_pendingNotifications.begin();
         i != m_pendingNotifications.end();
         i++)
    {
        string name = *i;

        AttributesMap::iterator j = m_paramAttributes.find(name);

        if(j != m_paramAttributes.end())
        {
            Tr069ParamAttributes paramAttrib = j->second;

            if(paramAttrib == ACTIVE_NOTIFICATION)
            {
                activeNotificationFound = true;
                break;
            }
        }
    }

    return activeNotificationFound;
}

bool Tr069ParameterValueChangeNotificationManager::QueryIfAnyValueChangeNotificationStillOutstanding()
{
    bool changeNotificationOutstanding = !m_pendingNotifications.empty();

    return changeNotificationOutstanding;
}


void Tr069ParameterValueChangeNotificationManager::InformManagementServer(CwmpInform & inform)
{
    DataModelManager &dmMgr = DataModelManager::GetInstance();

    if( !m_pendingNotifications.empty() )
    {
        inform.m_event.AddEvent("4 VALUE CHANGE");
    }

    while( !m_pendingNotifications.empty() )
    {
        ChangedParams::iterator i = m_pendingNotifications.begin();

        string name  = *i;
        dmMgr.AddParameterToParameterList( name, inform.m_parameterList);

        RemoveParmeterFromPendingList(name);
    }

    const set<string> & forcedInform = dmMgr.GetForcedInformParameterSet();
    for( set<string>::const_iterator i = forcedInform.begin();
         i != forcedInform.end();
         i++)
    {
        string name  = *i;
        dmMgr.AddParameterToParameterList( name, inform.m_parameterList );
    }
}

void Tr069ParameterValueChangeNotificationManager::SetParamterAttributes( const string & name, Tr069ParamAttributes attrib )
{
    m_paramAttributes[name] = attrib;
}

void Tr069ParameterValueChangeNotificationManager::ClearPendingValueChanges()
{
    TRACE_PRINTF("Clearing pending \"4 VALUE CHANGE\" parameters");

    m_pendingNotifications.clear();
}

/*
 * FSM Implemetation
 */
void Tr069ParameterValueChangeNotificationManager::NewValueChangeTransactionSession(void*)
{
    shared_ptr<ValueChange> valueChange(new ValueChange() );

    shared_ptr<TransactionSessionCommand> transSessCommand(new TransactionSessionCommand( valueChange ));

    RSYS_ASSERT(transSessCommand);

    /* ALWAYS post to external queue */
    Tr069Application::GetInstance().Enqueue(transSessCommand);
}

void Tr069ParameterValueChangeNotificationManager::HmsConnectionEstablishedEntry()
{

}

void Tr069ParameterValueChangeNotificationManager::HmsConnectionEstablishedExit()
{

}

void Tr069ParameterValueChangeNotificationManager::ActiveNotificationPendingEntry()
{
    RSYS_ASSERT(m_activeNotifyPendingTimer == NULL_TIMER);

    m_activeNotifyPendingTimer = Tr069Application::GetInstance().CreateTimer("ActiveNotifyPendingTimer", TimerEngineInterface::SecondsToTicks(5) );
}

void Tr069ParameterValueChangeNotificationManager::ActiveNotificationPendingExit()
{
    Tr069Application::GetInstance().DeleteTimer( m_activeNotifyPendingTimer );

    m_activeNotifyPendingTimer = NULL_TIMER;
}

bool Tr069ParameterValueChangeNotificationManager::QueryActiveNotifyStillPending(void*)
{
    return QueryIfActiveValueChangeNotificationStillOutstanding();
}



bool Tr069ParameterValueChangeNotificationManager::HandleTimerExpiry(threeway::TimerHandle expiredTimer)
{
    //TRACE_PRINTF("PARESH: Tr069ParameterValueChangeNotificationManager::HandleTimerExpiry");
    bool timerHandled = false;

    if(expiredTimer)
    {
        //shared_ptr<Queueable> empty;

        if( expiredTimer ==  m_activeNotifyPendingTimer )
        {
            //TRACE_PRINTF("PARESH: Tr069ParameterValueChangeNotificationManager::HandleTimerExpiry Inject in Fsm");
            m_fsm.InjectTimerExpiry( NULL/*empty*/ );
            timerHandled = true;
        }
    }

    return timerHandled;
}


}

