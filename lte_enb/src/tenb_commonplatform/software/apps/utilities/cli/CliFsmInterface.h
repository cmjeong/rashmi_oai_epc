///////////////////////////////////////////////////////////////////////////////
//
// CliFsmInterface.h
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliFsmInterface_h_
#define __CliFsmInterface_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>

#include <system/Trace.h>
#include <system/Serialisable.h>
#include <system/TimerEngine.h>

#include "Cli_fsm_interface.h"
#include "CliInput.h"

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Local Constants
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

class CliFsmInterface : public CommandLineFsmInterface
{
public:
    CliFsmInterface( shared_ptr<CliInput> input ) :
        m_input(input),
        m_timerId(NULL_TIMER) {}
    virtual ~CliFsmInterface() {}

    // Actions
    virtual void FeedbackStopReason(shared_ptr<std::string>);
    virtual void FeedbackTimeout(void*);
    virtual void FeedbackProgress(shared_ptr<CliExecuteCmdProgressInd>);
    virtual void FeedbackResponse(shared_ptr<CliExecuteCmdInd>);
    virtual void FeedbackCommandRejected(shared_ptr<CliCommand>);
    virtual void SendCommandReq(shared_ptr<CliCommand>);

    // Entry/Exit
    virtual void AwaitCommandEntry();
    virtual void AwaitCommandExit();
    virtual void UserIoThreadRunningEntry();
    virtual void UserIoThreadRunningExit();
    virtual void CommandInProgressEntry();
    virtual void CommandInProgressExit();
    virtual void QuittingEntry();

    // Guard Conditions
    virtual bool QueryQuitCommanded(shared_ptr<CliCommand>);
    virtual bool QueryCommandEmpty(shared_ptr<CliCommand>);
    virtual bool CommandLineParser(shared_ptr<CliCommand>);

    bool MatchedTimerHandle( TimerHandle timerId)
    {
        return timerId == m_timerId;
    }

    virtual const string & GetPrompt() = 0;

private:
    static const u32 commandTimelimit = 30;

    shared_ptr<CliInput> m_input;
    TimerHandle m_timerId;
};




#endif
