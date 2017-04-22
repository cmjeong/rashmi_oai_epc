///////////////////////////////////////////////////////////////////////////////
//
// CliApplication.h
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliEvents.h"

using namespace std;

CliAppEvent::CliAppEvent (CliAppEventType eventType) : Queueable(OTHER), m_eventType(eventType)
{
    ENTER();
    EXIT();
}

CliAppEvent::~CliAppEvent ()
{
    ENTER();
    EXIT();
}


CliAppNewKeyEvent::CliAppNewKeyEvent(u8 c) : CliAppEvent(CLI_EVENT_NEW_CHAR), m_char(c)
{
    ENTER();
    EXIT();
}

CliAppNewKeyEvent::~CliAppNewKeyEvent()
{
    ENTER();
    EXIT();
}

CliAppWholeCmdEvent::CliAppWholeCmdEvent(const string& wholeCmd) :
    CliAppEvent(CLI_EVENT_WHOLE_CMD),
    m_wholeCmd(wholeCmd)
{
    ENTER();
    EXIT();
}

CliAppWholeCmdEvent::~CliAppWholeCmdEvent()
{
    ENTER();
    EXIT();
}

CliAppCmdCompleteEvent::CliAppCmdCompleteEvent(int cmdStatus) : CliAppEvent(CLI_EVENT_CMD_COMPLETE), m_status(cmdStatus)
{
    ENTER();
    EXIT();
}

CliAppCmdCompleteEvent::~CliAppCmdCompleteEvent()
{
    ENTER();
    EXIT();
}


