///////////////////////////////////////////////////////////////////////////////
//
// test_fsm.h
//
// Autogenerated from test.fsm
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __test_fsm_h_
#define __test_fsm_h_
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <list>
#include <deque>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "test_fsm_interface.h"

using namespace testing;

namespace testing
{

/*** WARNING: Code AUTO-GENERATED from test.fsm. Do not edit! ***/
class TestFsm
{
public:

    TestFsm(
        TestFsmInterface & interfaceClass,
        bool traceEnabled = false,
        const char * name = "TestFsm"
        );
    virtual ~TestFsm();

    void InjectAlpha(shared_ptr<threeway::Queueable> event);
    void InjectBeta(shared_ptr<threeway::Queueable> event);
    void InjectGamma(void* event);
    void InjectDelta(shared_ptr<threeway::Queueable> event);
    std::string ToString() const
    {
        std::string returnedString(mName);

        if(mState)
        {
            returnedString += ".";
            returnedString += mState->mName;
        }

        return returnedString;
    }

    void Rename( const std::string & newName)
    {
        if(mFsmTraceEnabled)
        {
        	TRACE_PRINTF("%s.-: Renamed to %s", mName.c_str(), newName.c_str() );
        }
        mName = newName;
    }

    void SetFsmTraceEnable( bool traceEnable = true ) { mFsmTraceEnabled = traceEnable; }

    void TracePoint( const char * s )
    {
        if(mFsmTraceEnabled)
        {
        	TRACE_PRINTF("%s.%u: %s", mName.c_str(), mEventCounter, s );
        }
    }

private:
    typedef enum EventId_tag
    {
        FSM_EVENT_Alpha,
        FSM_EVENT_Beta,
        FSM_EVENT_Gamma,
        FSM_EVENT_Delta,
        NUMBER_OF_INJECTABLE_EVENTS
    } EventId;

    typedef enum EventType_tag
    {
        FSM_EVENT_TYPE_void_STAR_,
        FSM_EVENT_TYPE_shared_ptr_LT_threeway_COLON__COLON_Queueable_GT_,
        NUMBER_OF_EVENT_TYPES
    } EventType;

    class FsmEvent
    {
    public:
        FsmEvent( EventType eventType ) :
            mEventType(eventType) {}
        virtual ~FsmEvent(){}

        EventType mEventType;
    };

    class FsmEvent_void_STAR_ : public FsmEvent
    {
    public:
        FsmEvent_void_STAR_( void* event ) :
            FsmEvent(FSM_EVENT_TYPE_void_STAR_),
            mEvent(event) {}
        ~FsmEvent_void_STAR_() {}
    	void* mEvent;
    };

    class FsmEvent_shared_ptr_LT_threeway_COLON__COLON_Queueable_GT_ : public FsmEvent
    {
    public:
        FsmEvent_shared_ptr_LT_threeway_COLON__COLON_Queueable_GT_( shared_ptr<threeway::Queueable> event ) :
            FsmEvent(FSM_EVENT_TYPE_shared_ptr_LT_threeway_COLON__COLON_Queueable_GT_),
            mEvent(event) {}
        ~FsmEvent_shared_ptr_LT_threeway_COLON__COLON_Queueable_GT_() {}
    	shared_ptr<threeway::Queueable> mEvent;
    };

    void Enqueue( EventId eventId, shared_ptr<FsmEvent> fsmEvent );

    class State;
    typedef std::deque< State * > StateHistory;

    class State
    {
    public:
        State(TestFsm & fsm, const char * name ) :
            mFsm(fsm),
            mName(name){}
        virtual ~State(){}

        virtual void Inject( EventId eventId, shared_ptr<FsmEvent> fsmData ) { RSYS_ASSERT_PRINTF(false,"Cannot inject in state %s.", mName.c_str()); }
        virtual bool RunToCompletion() { RSYS_ASSERT_PRINTF(false,"RunToCompletion failure in state %s.", mName.c_str()); return false; };
        virtual bool DeferEvent( EventId ) const { RSYS_ASSERT_PRINTF(false,"Cannot defer in state %s.", mName.c_str()); return false; }

        virtual void Entry()
        {
            RSYS_ASSERT( mFsm.mState == GetSuperstate() );

            UpdateHistoryUponEntry();

            if(mFsm.mFsmTraceEnabled) { TRACE_PRINTF("%s.%u: %s (entry) ", mFsm.mName.c_str(), mFsm.mEventCounter, mName.c_str() ); }

            InterfaceEntryMethod();

            mFsm.mState = this;
        }

        virtual void Exit()
        {
            RSYS_ASSERT( mFsm.mState == this);

            UpdateHistoryUponExit();

            if(mFsm.mFsmTraceEnabled) { TRACE_PRINTF("%s.%u: %s (exit) ", mFsm.mName.c_str(), mFsm.mEventCounter, mName.c_str() ); }

            InterfaceExitMethod();

            mFsm.mState =  GetSuperstate();
        }

        TestFsm& mFsm;
        std::string mName;
        virtual State * GetSuperstate() const { return NULL; }
        virtual void  InterfaceEntryMethod() {}
        virtual void  InterfaceExitMethod() {}
        virtual void  UpdateHistoryUponExit() { mFsm.mCurrentStateTransitionExitsList.push_front( mFsm.mState ); }
        virtual void  UpdateHistoryUponEntry() { mFsm.mCurrentStateTransitionExitsList.clear(); }
    };

    class SimpleState : public State
    {
    public:
        SimpleState(TestFsm & fsm, const char * name) :
            State(fsm, name){}
        virtual ~SimpleState(){}

        void Inject( EventId eventId, shared_ptr<FsmEvent> fsmData );
        virtual bool RunToCompletion() { return true; }

        virtual bool DeferEvent( EventId ) const { return false; }
        virtual void InjectAlpha( shared_ptr<threeway::Queueable> eventData) { EventConsumed(FSM_EVENT_Alpha); }
        virtual void InjectBeta( shared_ptr<threeway::Queueable> eventData) { EventConsumed(FSM_EVENT_Beta); }
        virtual void InjectGamma( void* eventData) { EventConsumed(FSM_EVENT_Gamma); }
        virtual void InjectDelta( shared_ptr<threeway::Queueable> eventData) { EventConsumed(FSM_EVENT_Delta); }

    private:
        void EventConsumed( EventId queuedEventId )
        {
            if(mFsm.mFsmTraceEnabled) { TRACE_PRINTF("%s.%u: %s consumed %s", mFsm.mName.c_str(), mFsm.mEventCounter, mName.c_str(), mEventName[queuedEventId] ); }
        }
    };

    class Inactive : public SimpleState
    {
    public:
        Inactive(TestFsm & fsm) :
            SimpleState(fsm, "Inactive") {}
        virtual ~Inactive(){}

        void InterfaceEntryMethod( void ) { mFsm.mInterface.InactiveEntry();}
        void InterfaceExitMethod( void ) {  mFsm.mInterface.InactiveExit();}
        bool DeferEvent( EventId ) const ;
        virtual void InjectAlpha( shared_ptr<threeway::Queueable> eventData);
        virtual void InjectBeta( shared_ptr<threeway::Queueable> eventData);
        virtual void InjectGamma( void* eventData);
    };

    class Starting : public SimpleState
    {
    public:
        Starting(TestFsm & fsm) :
            SimpleState(fsm, "Starting") {}
        virtual ~Starting(){}

        void InterfaceEntryMethod( void ) { mFsm.mInterface.StartingEntry();}
        bool DeferEvent( EventId ) const ;
        State * GetSuperstate() const { return &mFsm.mActive; }
        virtual void InjectBeta( shared_ptr<threeway::Queueable> eventData);
        virtual void InjectGamma( void* eventData);
        virtual void InjectDelta( shared_ptr<threeway::Queueable> eventData);
    };

    class Running : public SimpleState
    {
    public:
        Running(TestFsm & fsm) :
            SimpleState(fsm, "Running") {}
        virtual ~Running(){}

        bool DeferEvent( EventId ) const ;
        State * GetSuperstate() const { return &mFsm.mActive; }
        virtual void InjectBeta( shared_ptr<threeway::Queueable> eventData);
        virtual void InjectGamma( void* eventData);
        virtual void InjectDelta( shared_ptr<threeway::Queueable> eventData);
    };

    class Stopping : public SimpleState
    {
    public:
        Stopping(TestFsm & fsm) :
            SimpleState(fsm, "Stopping") {}
        virtual ~Stopping(){}

        bool DeferEvent( EventId ) const ;
        State * GetSuperstate() const { return &mFsm.mActive; }
        virtual void InjectBeta( shared_ptr<threeway::Queueable> eventData);
        virtual void InjectGamma( void* eventData);
        virtual void InjectDelta( shared_ptr<threeway::Queueable> eventData);
    };

    class Superstate : public State
    {
    public:
        Superstate(TestFsm & fsm, const char * name) :
            State(fsm, name)
        { }
        virtual ~Superstate()
        { }
    };

    class SuperstateWithInitialState : public Superstate
    {
    public:
        SuperstateWithInitialState(TestFsm & fsm, const char * name) :
            Superstate(fsm, name) {}
        virtual ~SuperstateWithInitialState() {}

        virtual bool RunToCompletion() = 0;
    };

    class Active : public Superstate
    {
    public:
        Active(TestFsm & fsm) :
            Superstate(fsm, "Active") {}
        virtual ~Active(){}

    void InterfaceEntryMethod( void ) { mFsm.mInterface.ActiveEntry();}

    private:
    };

    class ExitPoint : public State
    {
    public:
        ExitPoint(TestFsm & fsm, const char * name) :
            State(fsm, name) {}
        virtual ~ExitPoint(){}
        virtual void Entry() = 0;
        virtual void Exit()
        {
            RSYS_ASSERT( mFsm.mState == this);

            if(mFsm.mFsmTraceEnabled) { TRACE_PRINTF("%s.%u: %s (exit) ", mFsm.mName.c_str(), mFsm.mEventCounter, mName.c_str() ); }

            mFsm.mState =  GetSuperstate();
        }
        virtual void  UpdateHistoryUponExit() {}
        virtual void  UpdateHistoryUponEntry() {}
    };

    class GoInactive : public ExitPoint
    {
    public:
        GoInactive(TestFsm & fsm) :
            ExitPoint(fsm, "GoInactive") {}
        virtual ~GoInactive(){}

        void Entry(); 

    private:
        State * GetSuperstate() const { return &mFsm.mActive; }
    };

    class QueuedFsmEvent
    {
    public:
        QueuedFsmEvent( EventId eventId, shared_ptr<FsmEvent> fsmEvent) :
            mId(eventId),
            mFsmEvent(fsmEvent){}
        ~QueuedFsmEvent(){}

        EventId mId;
        shared_ptr<FsmEvent> mFsmEvent;
    };

    TestFsmInterface & mInterface;
    bool mFsmTraceEnabled;
    std::string mName;
    State * mState;
    Active mActive;
    Inactive mInactive;
    Starting mStarting;
    Running mRunning;
    Stopping mStopping;
    GoInactive mGoInactive;
    std::list< shared_ptr<QueuedFsmEvent> > mfsmEventQueue;
    bool mFsmInjectInProgress;
    unsigned mEventCounter;
    StateHistory mCurrentStateTransitionExitsList;
    static const char * mEventName[NUMBER_OF_INJECTABLE_EVENTS];

};

} // -namespace-

#endif // __test_fsm_interface_h_
