///////////////////////////////////////////////////////////////////////////////
//
// FiatLux.h
//
// LED Management Unit - this class is the main component of the whole
// Led Management Unit
// It is responsible to:
// - handle timers
// - load LED behaviours
// - set LED patterns
// Code is abstracted in a way that this class doesn't know about the
// fact that two different hardware (3.5 & 4.0) require different implementations.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FiatLux_h_
#define __FiatLux_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <messaging/transport/MessageHandler.h>
#include <system/TimerInterface.h>
#include <system/ManagedObject.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SetLedInterface.h"
#include "LedBehaviourInterface.h"
#include "Led_fsm.h"

using namespace boost;
using namespace std;
using namespace threeway;

static const u32    NOT_OPERATIONAL_TIMEOUT = 1800000; //30 minutes in ms
static const u32    NOT_CONNECTION_TIMEOUT  =   30000;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/* This class handles event vs LED patterns */

class FiatLux : public IMessageHandler,
				public LedFsmInterface
{
public:
    /*
     * Constructor
     * \param SetLedInterface Provides h/w independent mechanism to set an LED
     * \param LoadBehaviourInterface Provides an interface to load default
     *                               LED patterns to be used when some event happens
     * \param TimerEngineInterface
     * \param TimerNotifyInterface
     * \param TimeOut Optional TimeOut to replace default one for 'no connection to server' event
     *                Default is 30 seconds
     * \param TimeOut Optional Timeout to replace default one for 'no operational' event
     *                Defaukt is 30 minutes
     *
     * */
    FiatLux(SetLedInterface&,
            LedBehaviourInterface&,
            threeway::TimerEngineInterface&, threeway::TimerNotifyInterface&,
            u32 noConnToSrvTimer = NOT_CONNECTION_TIMEOUT,
            u32 noOperationalTimer = NOT_OPERATIONAL_TIMEOUT);

    ~FiatLux();

    /**
     * Deal with it FiatLux timers, returns true if the timer is handled
     */
    bool TimerExpiry(threeway::TimerHandle timerHandle);

    /**
     * Driven by OamUserApplication to handle changes of FAP_ADMIN_STATE
     */
    void SetAdminState(u32);

    /* Takes an action - if needed - in response to an event
     * Internally it calles concrete class 'SetLed()' */
    bool TriggerLedBehaviour(LedEvent);

private:
    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    /* Implementation of LedFsmInterface classes */
    LedInterfaceDefinition();

private:
    /* Interface to set LED pattern */
    SetLedInterface& m_setLedInterface;

    /* Interface to get LED default behaviours */
    LedBehaviourInterface& m_ledBehaviour;

    /**
     * Interface for managing timers.
     */
    threeway::TimerEngineInterface& m_timerEngine;

    /* Timer used to check for Operational Timeout Error */
    threeway::TimerHandle   m_notOperationalTimerHandle;
    /* Timer used to check for No Connection To Server State */
    threeway::TimerHandle   m_noConnectionToServerTimerHandle;

    /* This map is used to associate desired LED behaviours to patterns */
    map<LedEvent, LedMap> m_ledEventScenarios;

    LedFsm 		m_fsm;
};

#endif
