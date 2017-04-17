#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069DeleteObject_fsm.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

using namespace tr069;

namespace tr069
{

/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
DeleteObjectFsm::DeleteObjectFsm(
DeleteObjectFsmInterface & interfaceClass,
    bool traceEnabled,
    const char * name
    ) :
    mInterface(interfaceClass),
    mFsmTraceEnabled(traceEnabled),
    mName(name),
    mState(NULL),
    mIdle(*this ),
    mDeleteObjectInProgress(*this ),
    mfsmEventQueue(),
    mFsmInjectInProgress(false),
    mEventCounter(0)
   {
      // Initial State
      mIdle.Entry();

      if(NULL != mState)
      {
         while( !mState->RunToCompletion() )
         {
            continue;
         }
      }
   }

/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
DeleteObjectFsm::~DeleteObjectFsm()
{
    RSYS_ASSERT_PRINTF(!mFsmInjectInProgress, "DeleteObjectFsm deleted while event-inject in progress.");

    mfsmEventQueue.clear();
    mCurrentStateTransitionExitsList.clear();
}

/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
void DeleteObjectFsm::InjectDeleteObject(shared_ptr<RpcDeleteObject> event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_shared_ptr_LT_RpcDeleteObject_GT_(event));
    Enqueue( DeleteObjectFsm::FSM_EVENT_DeleteObject, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
void DeleteObjectFsm::InjectMibDeleteObjectCnf(shared_ptr<MibDeleteObjectCnf> event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_shared_ptr_LT_MibDeleteObjectCnf_GT_(event));
    Enqueue( DeleteObjectFsm::FSM_EVENT_MibDeleteObjectCnf, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
void DeleteObjectFsm::Enqueue( EventId eventId, shared_ptr<FsmEvent> fsmEvent )
{
    RSYS_ASSERT(eventId < NUMBER_OF_INJECTABLE_EVENTS);

    // Reentrancy Protection is NOT intended to make thread-safe
    shared_ptr<QueuedFsmEvent>  qEvent(new QueuedFsmEvent(eventId, fsmEvent));
    mfsmEventQueue.push_back(qEvent);

    if(!mFsmInjectInProgress)
    {
        mFsmInjectInProgress = true;

        list< shared_ptr<QueuedFsmEvent> >::iterator event = mfsmEventQueue.begin();

        while( event != mfsmEventQueue.end() )
        {
            RSYS_ASSERT(*event);
            RSYS_ASSERT(mState);
EventId queuedEventId = (*event)->mId;

            RSYS_ASSERT(queuedEventId < NUMBER_OF_INJECTABLE_EVENTS);

            if( !mState->DeferEvent( queuedEventId ) )
            {
                ++mEventCounter;

                if(mFsmTraceEnabled) { TRACE_PRINTF("%s.%u: %s <--(%s)-- ", mName.c_str(), mEventCounter, mState->mName.c_str(), mEventName[queuedEventId] ); }

                mState->Inject(queuedEventId, (*event)->mFsmEvent);

                while( !mState->RunToCompletion() )
                {
                    continue;
                }

                mfsmEventQueue.erase(event);
                event = mfsmEventQueue.begin();
            }
            else
            {
                if(mFsmTraceEnabled) { TRACE_PRINTF("%s.-: %s (%s deferred)", mName.c_str(), mState->mName.c_str(), mEventName[queuedEventId] ); };
                event++;
            }
        }

        mFsmInjectInProgress = false;
    }
    else
    {
        if(mFsmTraceEnabled) { TRACE_PRINTF("%s.-: (%s enqueued)", mName.c_str(), mEventName[eventId] ); }
    }
}

/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
const char * DeleteObjectFsm::mEventName[NUMBER_OF_INJECTABLE_EVENTS] =
{
    "DeleteObject",
    "MibDeleteObjectCnf",
};

/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
void DeleteObjectFsm::SimpleState::Inject(
    EventId eventId,
    shared_ptr<FsmEvent> fsmEvent
    )
{
    RSYS_ASSERT(eventId < NUMBER_OF_INJECTABLE_EVENTS);

    switch(eventId)
    {
        case DeleteObjectFsm::FSM_EVENT_DeleteObject:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_shared_ptr_LT_RpcDeleteObject_GT_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_shared_ptr_LT_RpcDeleteObject_GT_> event = dynamic_pointer_cast<FsmEvent_shared_ptr_LT_RpcDeleteObject_GT_>(fsmEvent);
            InjectDeleteObject(event->mEvent);
        }
        break;

        case DeleteObjectFsm::FSM_EVENT_MibDeleteObjectCnf:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_shared_ptr_LT_MibDeleteObjectCnf_GT_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_shared_ptr_LT_MibDeleteObjectCnf_GT_> event = dynamic_pointer_cast<FsmEvent_shared_ptr_LT_MibDeleteObjectCnf_GT_>(fsmEvent);
            InjectMibDeleteObjectCnf(event->mEvent);
        }
        break;

        default:
            RSYS_ASSERT(false);
            break;
    }
}

/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
void DeleteObjectFsm::Idle::InjectDeleteObject(
    shared_ptr<RpcDeleteObject> event
    )
{
    {
mFsm.mState->Exit();
        mFsm.TracePoint( "Action SendDeleteMibObjectReq" );

        switch( mFsm.mInterface.SendDeleteMibObjectReq(event))
        {
            case DeleteObjectFsmActionSendDeleteMibObjectReq::FSM_ACTION_SUCCESS:
            {
                mFsm.TracePoint( "SendDeleteMibObjectReq=SUCCESS" );

                mFsm.mDeleteObjectInProgress.Entry();
            }
            break;

            case DeleteObjectFsmActionSendDeleteMibObjectReq::FSM_ACTION_DELETE_OBJECT_NOT_SUPPORTED:
            {
                mFsm.TracePoint( "SendDeleteMibObjectReq=DELETE_OBJECT_NOT_SUPPORTED" );

                mFsm.mIdle.Entry();
            }
            return;

            case DeleteObjectFsmActionSendDeleteMibObjectReq::FSM_ACTION_MAX_ENTRIES_EXCEEDED:
            {
                mFsm.TracePoint( "SendDeleteMibObjectReq=MAX_ENTRIES_EXCEEDED" );

                mFsm.mIdle.Entry();
            }
            return;
        }

    }
}

// Event MibDeleteObjectCnf not handled in state Idle

// State Idle has no deferred events.

// Event DeleteObject deferred in state DeleteObjectInProgress

/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
void DeleteObjectFsm::DeleteObjectInProgress::InjectMibDeleteObjectCnf(
    shared_ptr<MibDeleteObjectCnf> event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.TracePoint( "Action SendDeleteObjectResponse" );

        mFsm.mInterface.SendDeleteObjectResponse(event);

        mFsm.mIdle.Entry();
    }
}

/*** WARNING: Code AUTO-GENERATED from Tr069DeleteObject.fsm. Do not edit! ***/
bool DeleteObjectFsm::DeleteObjectInProgress::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case DeleteObjectFsm::FSM_EVENT_DeleteObject:
            return true;


        default:
            return false;
    }
}

} // -namespace-
