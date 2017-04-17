///////////////////////////////////////////////////////////////////////////////
//
// StateMachine.h
//
// TBC
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "FNTPcallback.h"
#include <vector>
#include <queue>
#include <system/Trace.h>

//using namespace boost;
//using namespace threeway;

//class CallbackBase;

typedef int tEvent;

namespace threeway
{

class State;

class Action
{
public:
    Action();
    Action(int eventId, CallbackBase* eventCallback, State *newState) :
        m_eventId(eventId),
        m_callback(eventCallback),
        m_newState(newState)
    {
    }

    ~Action()
    {
        delete (m_callback);
    }

    int GetEventId() { return m_eventId; }

    //callback for the action
    CallbackBase* m_callback;
    //state that we will go to after this action.
    State* m_newState;
    int m_eventId;
private:
    // Ensure objects of this type can't be copied.
    Action(const Action&);
    Action& operator=(const Action&);
};

class State
{
public:
    State() :
        m_name(NULL),
        m_entry(NULL),
        m_exit(NULL),
        m_stateId(0)
    {
    }

    State(const char* name, CallbackBase* entry, CallbackBase* exit, int stateId) :
        m_name(name),
        m_entry(entry),
        m_exit(exit),
        m_stateId(stateId)
    {
    }

    virtual ~State();

    //accessors
    Action* GetAction(int eventId);
    void AddAction(int eventId, CallbackBase* eventCallback, State* newState);
    const char* GetName() { return (m_name); }
    void SetName(const char *name) {m_name = name;}

    //entry and exit callbacks
    CallbackBase* m_entry;
    CallbackBase* m_exit;

    virtual void DoEntry() { m_entry->Call(); }
    virtual void DoExit() { m_exit->Call(); }

    virtual State* EventHappened(int* eventId);

private:
    // Ensure objects of this type can't be copied.
    State(const State&);
    State& operator=(const State&);

    //actions defined for this state. If an action happens when we are in this state then there will be some response, otherwise none.
    std::vector<Action*> m_actions;
    //Name. Only ever used when building or displaying
    const char *m_name;
    int m_stateId;
};

class StateMachine: public State
{
public:
    StateMachine() :
        m_currentState(NULL),
        m_numStates(0),
        m_debugOn(false),
        m_parallelStateMachine(NULL),
        m_constructed(false)
    {
        SetName(NULL);
        m_states.clear();
    }

    StateMachine(const char* name) :
        m_currentState(NULL),
        m_numStates(0),
        m_debugOn(false),
        m_stateMachineName(name),
        m_parallelStateMachine(NULL),
        m_constructed(false)
    {
        SetName(name);
        m_states.clear();
    }

    StateMachine(const char* name, CallbackBase* entry, CallbackBase* exit, int stateId) :
        m_currentState(NULL),
        m_numStates(0),
        m_debugOn(false),
        m_stateMachineName(name),
        m_parallelStateMachine(NULL),
        m_constructed(false),
        State(name, entry, exit, stateId)
    {
        m_states.clear();
    }

    ~StateMachine() {Reset();}
    void Reset(void);

    //create a new state. Supply with entry and exit functions. If none supply NULL.
    void InsertSimpleState(const char* stateName, CallbackBase* entry, CallbackBase* exit);
    StateMachine* InsertCompositeState(const char* stateName, CallbackBase* entry, CallbackBase* exit);
    StateMachine* InsertOrthogonalStateMachine(const char* stateName);
    //Insert an event handler. If we are at state stateName, and event eventId happens, then we transition to state resultantState.
    // Both states must exist.
    bool InsertEventHandler(int eventId, const char * stateName, CallbackBase* actionCallback, const char* resultantState);
    void EventHappened(int eventId);
    //event id eventId has happened! Do the required actions.
    State* EventHappened(int* eventId);
    //Set the name for the state machine
    void SetStateMachineName(const char *stateMachineName) { m_stateMachineName = stateMachineName; }
    //activate/deactivate extended debug for this state machine
    const char *GetStateMachineName(void) {return(GetName());}
    void SetDebugOn(bool InDebugOnOff) { m_debugOn = InDebugOnOff; }
    void ResetStateMachine() { m_currentState = m_states.front(); }
    void SetConstructed() {m_constructed = true; if(m_parallelStateMachine != NULL) {m_parallelStateMachine->SetConstructed();}}

    void DoEntry()
    {
        TRACE_PRINTF("StateMachine::DoEntry()");
        m_entry->Call();
        ResetStateMachine();
    }

    void DoExit()
    {
        TRACE_PRINTF("StateMachine::DoExit()");
        m_exit->Call();
    }

private:
    //search state list for state name stateName.
    State* GetState(const char *stateName);
    //list of states.
    std::vector<State*> m_states;
    //queue of events to be processed
    std::queue<int> m_events;
    //the state we are in.
    State* m_currentState;
    StateMachine* m_parallelStateMachine;
    int m_numStates;
    bool m_debugOn;
    const char *m_stateMachineName;
    bool m_constructed;
};

}

#endif /*STATEMACHINE_H_*/
