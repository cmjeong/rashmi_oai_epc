///////////////////////////////////////////////////////////////////////////////
//
// FiatLux.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <system/Trace.h>

#include <messaging/messages/common/MfOpStateInformInd.h>
#include <messaging/messages/common/MfSetAdminStateReq.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "FiatLux.h"
#include "../oam_env.h"

using namespace std;
using namespace boost;
using namespace threeway;


///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////


FiatLux::FiatLux( SetLedInterface &setLedInterface,
                  LedBehaviourInterface &ledBehaviourInterface,
                  threeway::TimerEngineInterface &tEInterface,
                  threeway::TimerNotifyInterface &tNInterface,
                  u32 noConnToSrvTimer,     // default to NOT_CONNECTION_TIMEOUT
                  u32 noOperationalTimer   // default to NOT_OPERATIONAL_TIMEOUT
                ):
    m_notOperationalTimerHandle(NULL_TIMER),
    m_noConnectionToServerTimerHandle(NULL_TIMER),
    m_setLedInterface(setLedInterface),
    m_ledBehaviour(ledBehaviourInterface),
    m_timerEngine(tEInterface),
    m_fsm(*this,true)
{
    m_notOperationalTimerHandle = m_timerEngine.CreateTimer("LED Not Operational timer",
                                                        noOperationalTimer,
                                                        tNInterface,
                                                        TimerEngineInterface::TIMER_WAIT,
                                                        TimerEngineInterface::TIMER_SINGLE_SHOT_WITHOUT_DELETE);

    m_noConnectionToServerTimerHandle = m_timerEngine.CreateTimer("LED No Connection To Server timer",
                                                        noConnToSrvTimer,
                                                        tNInterface,
                                                        TimerEngineInterface::TIMER_WAIT,
                                                        TimerEngineInterface::TIMER_SINGLE_SHOT_WITHOUT_DELETE);

    m_ledBehaviour.LoadDefaultMap( m_ledEventScenarios );
    m_fsm.InjectEventMapLoaded(NULL);
};


FiatLux::~FiatLux()
{
    if (m_notOperationalTimerHandle != NULL_TIMER)
    {
        m_timerEngine.DeleteTimer(m_notOperationalTimerHandle);
    }

    if (m_noConnectionToServerTimerHandle != NULL_TIMER)
    {
        m_timerEngine.DeleteTimer(m_noConnectionToServerTimerHandle);
    }
};


bool FiatLux::TriggerLedBehaviour(LedEvent event)
{
    TRACE_PRINTF_LEV(TRACE_VERBOSE, "FiatLux: received event %s", ledEventToString(event) );

    map<LedEvent, LedMap>::iterator it = m_ledEventScenarios.find(event);

    if ( it == m_ledEventScenarios.end() )
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "FiatLux::SetLed - event (%s) not found!", ledEventToString(event) );
        return false;
    }

    for (u32 i=0; i< LED_MAX_NUMBER; ++i)
    {
        if ( it->second.l[i].colour != LED_SAME_COLOUR
        	|| it->second.l[i].pattern != LED_SAME_PATTERN )
        {
            m_setLedInterface.SetLed(i,
                                      it->second.l[i].colour,
                                      it->second.l[i].pattern );

            TRACE_PRINTF_LEV(TRACE_VERBOSE, "Local Led Map updated for led %"PRIu32", with colour %s and pattern %s",
                    i, ledColourToString(it->second.l[i].colour), ledPatternToString(it->second.l[i].pattern) );
        }
    }

    return true;
}


bool FiatLux::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
    bool handled = false;

    if (message == NULL)
    {
    	TRACE_PRINTF_LEV(TRACE_WARNING, "FiatLux - Received NULL message");
    	return false;
    }

    u32 messageId = message->GetSerialisationId();

    // TODO: Add GPS location handling

    switch( messageId )
    {
        case SERIALISATION_ID_MF_OP_STATE_INFORM_IND:
        {
            shared_ptr<MfOpStateInformInd> opStateMsg = Serialisable::DeSerialise<MfOpStateInformInd>(message);

            if (opStateMsg == NULL)
            {
            	TRACE_PRINTF_LEV(TRACE_WARNING, "FiatLux - failure while attempting to create MfOpStateInformInd");
            	return false;
            }

            bool isEnabled = ( opStateMsg->GetOpState() == ManagedObject::OP_STATE_ENABLED ? true : false);

            switch ( opStateMsg->GetManagedFing() )
            {
				/* Over/Under Temperature */
                case MF_TEMPERATURE_MONITOR:
                {
                    TRACE_PRINTF_LEV(TRACE_INFO,
                            "FiatLux - Temperature monitor (normal[1]/over temperature[0]) - event connection to server - value is: %"PRId16,
                            isEnabled);

                    if (isEnabled)
                    {
                    	m_fsm.InjectEventTemperatureInRange(NULL);
                    }
                    else
                    {
                    	m_fsm.InjectEventTemperatureOutOfRange(NULL);
                    }
                }
                break;

                /* No Cal */
                case MF_HW_CONFIG:
                {
                    TRACE_PRINTF_LEV(TRACE_INFO,
                            "FiatLux - HW config (OK[1]/not working[0]) - event fap error - value is: %"PRId16,
                            isEnabled);

                    if (isEnabled)
                    {
                        m_fsm.InjectEventSelfTestOk( NULL );
                    }
                    else
                    {
                    	m_fsm.InjectEventNoCalibration(NULL);
                    }
                }
                break;

                case MF_IPSEC_TUNNEL:
                {
                    TRACE_PRINTF_LEV(TRACE_INFO,
                            "FiatLux - IPSec Tunnel (up[1]/down[0]) msg, - event not operational / no conn. to server - value is: %"PRId16,
                            isEnabled);

                    if (isEnabled)
                    {
                        m_fsm.InjectEventConnectedToServer(NULL);
                    }
                    else
                    {
                    	m_fsm.InjectEventCannotConnectToServer(NULL);
                    }

                }
                break;

                case MF_REM_SCAN:
                {
                	TRACE_PRINTF_LEV(TRACE_INFO,
                            "FiatLux - Rem Scan: opState is %s",
                            ManagedObject::OpStateToString(opStateMsg->GetOpState()));

                	if (isEnabled)
                	{
                    	TriggerLedBehaviour( REM_IN_PROGRESS );
                	}
                	else
                	{
                    	TriggerLedBehaviour( HMS_ACCEPTS_REM_RESULTS );
                	}
                }
                break;

                case MF_RADIO:
                {
                    TRACE_PRINTF_LEV(TRACE_INFO,
                            "FiatLux - MF_RADIO (up[1]/down[0]) msg, - event transmitting / not transmitting - value is: %"PRId16,
                            isEnabled);

                    if (isEnabled)
                    {
                        m_fsm.InjectEventTransmitterEnabled(NULL);
                    }
                    else
                    {
                    	m_fsm.InjectEventTransmitterDisabled(NULL);
                    }
                }
                break;

                default:
                {
                    TRACE_PRINTF_LEV(TRACE_INFO, "MfOpStateInformInd Unhandled Message: %s",
                                     message->ToString().c_str() );
                }
                break;
            }
        }
        break;

    }

    // At the moment always return false since SAPI maybe interested to process same events
    return handled;
}


bool FiatLux::TimerExpiry(TimerHandle timerHandle)
{
	bool timerIsHandled = false;

    if (timerHandle == m_notOperationalTimerHandle)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "FiatLux timer not operational expired! Set status to OPERATIONAL ERROR");

        m_fsm.InjectEventNotOperationalTimeout(NULL);
        timerIsHandled = true;
    }
    else if (timerHandle == m_noConnectionToServerTimerHandle)
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "FiatLux timer No Conn To Srvr expired! Set status to NO CONN TO SERVER");

        m_fsm.InjectEventCannotConnectToServer(NULL);
        timerIsHandled = true;
    }

    return timerIsHandled;
}


void FiatLux::SetAdminState(u32 state)
{
	if ( oamEnv_isProductHbs2Iu() )
	{
		if (state)
		{
			TriggerLedBehaviour(HMS_ACCEPTS_REM_RESULTS);
		}
		else
		{
			TriggerLedBehaviour(HNB_IS_LOCATION_LOCKED);
		}
	}
}

/* FSM functions */

void FiatLux::InitialStateEntry()
{}

void FiatLux::WrongTemperatureEntry()
{
	TriggerLedBehaviour(TEMPERATURE_OUT_OF_RANGE);
}

void FiatLux::FapErrorEntry()
{
	TriggerLedBehaviour(FAP_ERROR);
}

void FiatLux::PowerOnSelfTestEntry()
{
	TriggerLedBehaviour(POWER_ON_SELF_TEST);
}

void FiatLux::ConnectToServerEntry()
{
	// Starting timer used by 'No Connection To Server'
	m_timerEngine.StartTimer( m_noConnectionToServerTimerHandle );
	TRACE_PRINTF_LEV(TRACE_VERBOSE, "FiatLux timer no Conn. to Server started (%"PRId16")", m_noConnectionToServerTimerHandle);

	TriggerLedBehaviour(CONNECT_TO_SERVER);
}

void FiatLux::NoConnectionToServerEntry()
{
	TriggerLedBehaviour(NO_CONNECTION_TO_SERVER);
}

void FiatLux::NotOperationalEntry()
{
    // Stopping timer used by 'No Connection to server'
    if ( m_timerEngine.IsTimerRunning(m_noConnectionToServerTimerHandle) )
    {
        m_timerEngine.StopTimer(m_noConnectionToServerTimerHandle);
        TRACE_PRINTF_LEV(TRACE_VERBOSE, "FiatLux: stopping timer for handling No Connection To server (%"PRId16")",
                m_noConnectionToServerTimerHandle);
    }

    // Starting timer used by 'Operational Error'
    m_timerEngine.StartTimer( m_notOperationalTimerHandle );
    TRACE_PRINTF_LEV(TRACE_VERBOSE, "FiatLux Not Operational Timer (%"PRId16") started", m_notOperationalTimerHandle);

	TriggerLedBehaviour(NOT_OPERATIONAL);
}

void FiatLux::OperationalErrorEntry()
{
	TriggerLedBehaviour(OPERATIONAL_ERROR);
}

void FiatLux::OperationalEntry()
{
	// Stopping timer used for 'Operational Error'
	if ( m_timerEngine.IsTimerRunning(m_notOperationalTimerHandle) )
	{
		m_timerEngine.StopTimer(m_notOperationalTimerHandle);
        TRACE_PRINTF_LEV(TRACE_VERBOSE, "FiatLux: stopping timer for handling Operational Error (%"PRId16")",
        		m_notOperationalTimerHandle);
	}
	TriggerLedBehaviour(OPERATIONAL);
}

