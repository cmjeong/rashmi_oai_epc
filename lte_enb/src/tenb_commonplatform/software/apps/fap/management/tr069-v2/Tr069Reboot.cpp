///////////////////////////////////////////////////////////////////////////////
//
// TR069Reboot.cpp
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

#include "Tr069ServerConnection.h"
#include "Tr069Application.h"

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

Tr069Reboot* Tr069Reboot::s_instance = NULL;


Tr069Reboot& Tr069Reboot::GetInstance()
{
    ENTER
    ();

    if (s_instance == NULL)
    {
        s_instance = new Tr069Reboot();

        RSYS_ASSERT(s_instance);
    }

    RETURN (*s_instance);
}

Tr069Reboot::Tr069Reboot() :
    m_fapRebooting(false),
    m_stateGuardTimer(0),
    m_fsm(*this, true)
{
}

Tr069Reboot::~Tr069Reboot()
{
}


void Tr069Reboot::HandleEvent( shared_ptr<Queueable> event)
{
    RSYS_ASSERT(event);

    switch(event->GetDomain())
    {
        case Queueable::OTHER:
        {
            shared_ptr<Tr069QueueableEvent> tr069Event = dynamic_pointer_cast<Tr069QueueableEvent>(event);

            if (tr069Event)
            {
                if(Tr069QueueableEvent::REBOOT_FSM == tr069Event->GetDst())
                {
                    switch( tr069Event->GetId() )
                    {
                        case Tr069QueueableEvent::REBOOT_REQ:
                            m_fsm.InjectRebootReq(NULL);
                            break;

                        default:
                            RSYS_ASSERT_PRINTF(false,"Unhandled REBOOT_FSM event %s.", tr069Event->ToString());
                            break;
                    }
                }
            }
        }
        break;

        default:
            break;
    }
}

bool Tr069Reboot::HandleTimerExpiry(threeway::TimerHandle expiredTimer)
{
    bool timerHandled = false;

    if(expiredTimer)
    {
        if( expiredTimer == m_stateGuardTimer )
        {
            m_fsm.InjectStateGuardTimerExpiry( NULL );
            timerHandled = true;
        }
    }

    return timerHandled;
}

void Tr069Reboot::OperationalStateDisabled(void)
{
    m_fsm.InjectOperationalStateDisabled(NULL);
}


// Actions
void Tr069Reboot::ImmediateReboot(void*)
{
    if(system("reboot") != oam_ret_zero )
    {
    	TRACE_MSG("Tr069Reboot::ImmediateReboot, Reboot command Failed");
    }
}

// Entry/Exit
void Tr069Reboot::RebootingEntry()
{
    m_fapRebooting = true;

    OamActionReq oamActionReq(OAM_ACTION_REBOOT);
    Tr069Application::GetInstance().SendMessage(oamActionReq, ENTITY_OAM, ENTITY_TR069);
}

void Tr069Reboot::DelaySecGwDisconnectEntry()
{
    m_stateGuardTimer = Tr069Application::GetInstance().CreateTimer( "DelayedSecGwDisconnect", TimerEngineInterface::MillisecondsToTicks( 4500 ) );
}

void Tr069Reboot::DelaySecGwDisconnectExit()
{
    Tr069Application::GetInstance().DeleteTimer( m_stateGuardTimer );

    m_stateGuardTimer = 0;
}

void Tr069Reboot::SecGwDisconnectEntry()
{
    m_stateGuardTimer = Tr069Application::GetInstance().CreateTimer( "DelayedSecGwDisconnect", TimerEngineInterface::SecondsToTicks( 60 ) );

    shared_ptr<SecGwModifyReq> secGwModifyReq( new SecGwModifyReq(SecGwModifyReq::None) );
    Tr069Application::GetInstance().Enqueue(secGwModifyReq);
}

void Tr069Reboot::SecGwDisconnectExit()
{
    Tr069Application::GetInstance().DeleteTimer( m_stateGuardTimer );

    m_stateGuardTimer = 0;
}

// Guard Conditions
bool Tr069Reboot::QueryOperational()
{
    u32 currentOperationalState = 0;
    Tr069Application::GetInstance().GetMibCache().GetMibAttribute(MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_LTE_RFTX_OP_STATE, currentOperationalState );

    bool operational = (currentOperationalState == 1);

    return operational;
}


}

