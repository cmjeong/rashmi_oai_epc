///////////////////////////////////////////////////////////////////////////////
//
// StateMachine.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#include "StateMachine.h"
#include <string.h>
#include <system/Trace.h>
#include <assert.h>

namespace threeway
{

State::~State()
{
    std::vector<Action*>::iterator iter;
    for (iter = m_actions.begin(); iter != m_actions.end(); iter++)
    {
        delete *iter;
    }
    m_actions.clear();
    delete (m_entry);
    delete (m_exit);
}
Action* State::GetAction(int eventId)
{
    ENTER();

    //TRACE_PRINTF("Getting action for eventid %d",eventId);
    std::vector<Action*>::iterator iter;
    for (iter = m_actions.begin(); iter != m_actions.end(); iter++)
    {
        if (((*iter)->GetEventId()) == eventId)
        {
            //TRACE_PRINTF("Action Found....");
            RETURN(*iter);
        }
    }
    RETURN(NULL);
}

void State::AddAction(int eventId, CallbackBase* eventCallback, State *newState)
{
    if(newState == NULL)
        TRACE_PRINTF("State::AddAction (newState == NULL)");

    if (GetAction(eventId) != NULL)
    {
        TRACE_PRINTF("Action for this event already exists");
    }
    else
    {
        Action* theAction = new Action(eventId, eventCallback, newState);
        m_actions.push_back(theAction);
    }
}

State* State::EventHappened(int* eventId)
{
    Action* theAction;
    State* resultantState;

    //TRACE_PRINTF("event (%d) in state %s",*eventId,GetName());

    if ((theAction = GetAction(*eventId)) == NULL)
    {
        //if (m_debugOn)
        //{
        TRACE_PRINTF(" No handler for this event (%d) in state %s",*eventId,GetName());
        //}
        //No handler for this event so pass up the action and do nothing. Resultant state is our state as nothing has changed. Do not change eventid as it has not been consumed
        resultantState = this;
    }
    else
    {
        if((resultantState = theAction->m_newState) != NULL) //if the action has a resultant state, it is not an internal event i.e. it leaves the state and enters another (possibly the same state it left)
        {
            TRACE_PRINTF("~~~~~~~~~~~~  Exiting state %s\n",GetName());
            if (m_exit)
            {
                DoExit();
            }

            if (theAction->m_callback)
            {
                (theAction->m_callback)->Call();
            }

            TRACE_PRINTF("~~~~~~~~~~~~  Entering state %s\n",resultantState->GetName());
            if (resultantState->m_entry)
            {
                resultantState->DoEntry();
            }
        }
        else //action is an internal event handler, so don't do entry/exit functions
        {
            if (theAction->m_callback)
             {
                TRACE_PRINTF("////////////////actioning internal event handler, eventid = %d\n",*eventId);
                 (theAction->m_callback)->Call();
             }
        }
    }
    *eventId = 0; //set eventId to 0 as it has been 'consumed'
    //return the state we are now in
    return resultantState;
}

void StateMachine::Reset(void)
{
    std::vector<State*>::iterator iter;
    for (iter = m_states.begin(); iter != m_states.end(); iter++)
    {
        delete *iter;
    }
    m_states.clear();
    if(m_parallelStateMachine != NULL)
    {
        delete(m_parallelStateMachine);
        m_parallelStateMachine = NULL;
    }
}

void StateMachine::InsertSimpleState(const char* stateName, CallbackBase* entry, CallbackBase* exit)
{
    State* newState;
    //TRACE_PRINTF(" Inserting state %s, callback 1 = %p, callback 2 = %p",stateName,entry,exit);
    if (GetState(stateName) == NULL)
    {
        newState = new State(stateName, entry, exit, m_numStates);
        RSYS_ASSERT((newState!=NULL));
        if (m_states.empty())
        {
            m_currentState = newState;
        }
        m_states.push_back((newState));
        m_numStates++;
    }
    else
    {
        TRACE_PRINTF(" %s: State %s already exists",m_stateMachineName,stateName);
    }
}

StateMachine* StateMachine::InsertCompositeState(const char* stateName, CallbackBase* entry, CallbackBase* exit)
{
    State* newState;
    StateMachine* newSM = NULL;
    TRACE_PRINTF(" Inserting composite state %s",stateName);
    if (GetState(stateName) == NULL)
    {
        newSM = new StateMachine(stateName, entry, exit, m_numStates);
        RSYS_ASSERT(newSM != NULL);
        newState = (State*) newSM;
        if (m_states.empty())
        {
            m_currentState = newState;
        }
        m_states.push_back((newState));
        m_numStates++;
    }
    else
    {
        TRACE_PRINTF(" %s: State %s already exists",m_stateMachineName,stateName);
        RSYS_ASSERT(false);
    }
    return newSM;
}

StateMachine* StateMachine::InsertOrthogonalStateMachine(const char* stateName)
{
    TRACE_PRINTF("Adding orthogonal state machine %s",stateName);
    RSYS_ASSERT(m_parallelStateMachine == NULL);
    m_parallelStateMachine = new StateMachine(stateName);
    RSYS_ASSERT(m_parallelStateMachine != NULL);
    return m_parallelStateMachine;
}

bool StateMachine::InsertEventHandler(int eventId, const char * stateName, CallbackBase* actionCallback,const char* resultantState)
{
    bool retVal;
    State* theState;
    if ((theState = GetState(stateName)) == NULL)
    {
        retVal = false;
        TRACE_PRINTF(" %s: No state of this name: %s",m_stateMachineName,stateName);
    }
    else
    {
/*        State* theResultantState;
        if ((theResultantState = GetState(resultantState)) == NULL)
        {
            retVal = false;
            TRACE_PRINTF(" %s: No resultant state of this name: %s",m_stateMachineName,resultantState);
        }
        else
        {
            theState->AddAction(eventId, actionCallback, theResultantState);
            retVal = true;
        }*/
           State* theResultantState;
           theResultantState = GetState(resultantState);

           theState->AddAction(eventId, actionCallback, theResultantState);
           retVal = true;

    }
    return retVal;
}

void StateMachine::EventHappened(int eventId)
{
    //TRACE_PRINTF(" StateMachine::EventHappened int");
        if (!(m_states.empty()))
        {
            if(m_constructed)
            {
                EventHappened(&eventId);
            }
            else
            {
                TRACE_PRINTF("Help! State machine %s not yet fully constructed",GetName());
            }
        }
        else
        {
            TRACE_PRINTF("State machine not initialised event id = %d",eventId);
        }
}

State* StateMachine::EventHappened(int* eventId)
{
    int theEvent = 0;
    State* newState = this;

   // TRACE_PRINTF(" StateMachine::EventHappened int*");
    if(m_parallelStateMachine != NULL)
    {
        //hand the event on to any orthogonal state machines
        TRACE_PRINTF("handing event (%d) to parallel (orthogonal) sm %s",*eventId,m_parallelStateMachine->GetName());
        m_parallelStateMachine->EventHappened(*eventId);
    }

    //TRACE_PRINTF("event (%d) in state %s",*eventId,GetName());
    // Check that current state is known, i.e. InsertSimpleState() has been called
    if (m_currentState == NULL)
    {
        TRACE_PRINTF("StateMachine::EventHappened(): m_currentState==NULL.  Using NULL as storage event (%d) in state %s",(int)eventId,GetName());
    }
    else
    {
        TRACE_PRINTF(" %s: Event happened entry Event  = %d, in state %s",m_stateMachineName,*eventId,(m_currentState->GetName()));

        m_events.push(*eventId);


        //TRACE_PRINTF(" %s: Event queue size (pre check) = %zu",m_stateMachineName,m_events.size());


        if (m_events.size() == 1) //only start processing if the size of the queue is 1. This avoids re-entrance problems if this method is called by one of the callbacks below.
        {
            while (!(m_events.empty()))
            {
                //TRACE_PRINTF("Event queue size = %d",m_events.size());
                theEvent = m_events.front(); //get the queued event...
                //...send the event to the State.

                //toss toss toss
                m_currentState = m_currentState->EventHappened(&theEvent);
                //if the event has not been 'consumed' try our own State behaviour i.e
                if (theEvent != 0)
                {
                    newState = m_currentState->State::EventHappened(&theEvent);
                }
                else
                {
                    newState = this;
                }

                m_events.pop();
            }
        }
        else
        {
            //if (m_debugOn)
            //{
            //TRACE_PRINTF(" %s: More than one event Event queue size = %zu",m_stateMachineName,m_events.size());
            //}
        }

    }

    *eventId = theEvent;
    return newState;
}

State* StateMachine::GetState(const char *stateName)
{
    ENTER();

    if(stateName == NULL)
    {
        TRACE_PRINTF("StateMachine::GetState (stateName == NULL)");
        RETURN(NULL);
    }
    else
    {
        std::vector<State*>::iterator iter;
        for (iter = m_states.begin(); iter != m_states.end(); iter++)
        {
            if (strcmp((*iter)->GetName(), stateName) == 0)
            {
                RETURN(*iter);
            }
        }
    }
    RETURN(NULL);
}

}
