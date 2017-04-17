///////////////////////////////////////////////////////////////////////////////
//
// CliEvents.h
//
// Internal events used by CliApp
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliEvents_h_
#define __CliEvents_h_

#include <string>
#include <string.h>
#include <system/ThreadWithQueue.h>

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/*
 * Base class for events specific to CliApp
 */
class CliAppEvent : public Queueable
{
public:
	typedef enum CliAppEventTypeTag
	{
	    CLI_EVENT_NEW_CHAR,
	    CLI_EVENT_WHOLE_CMD,
        CLI_EVENT_CMD_COMPLETE,
        CLI_EVENT_CMD_REQ,
	    NUM_CLI_EVENT_TYPES
	} CliAppEventType;

    CliAppEvent (CliAppEventType eventType);
    virtual ~CliAppEvent ();

public:
    CliAppEventType GetCliAppEventType() { return m_eventType; } ;

private:
    CliAppEventType m_eventType ;
};



/*
 * New Char event
 */
class CliAppNewKeyEvent : public CliAppEvent
{
public:
    CliAppNewKeyEvent(u8 c);
    virtual ~CliAppNewKeyEvent();

public:
    u8 GetChar() { return m_char; } ;

private:
    u8 m_char ;
};


/**
 * Whole command event used to pass a whole command into
 * the main processing loop.  E.g. when received over UDP.
 */
class CliAppWholeCmdEvent : public CliAppEvent
{
public:
    CliAppWholeCmdEvent(const std::string& wholeCmd);
    virtual ~CliAppWholeCmdEvent();

public:
    std::string GetWholeCmd() { return m_wholeCmd; }

private:
    std::string m_wholeCmd ;
};


/*
 * Command Completion Event
 */
class CliAppCmdCompleteEvent : public CliAppEvent
{
public:
    CliAppCmdCompleteEvent(int cmdStatus);
    virtual ~CliAppCmdCompleteEvent();

public:
    int GetCmdStatus() { return m_status; }

private:
    int m_status ;
};

class CliAppCmdRequestEvent : public CliAppEvent
{
public:
    CliAppCmdRequestEvent( const string & prompt ) :
        CliAppEvent(CLI_EVENT_CMD_REQ),
        m_prompt(prompt)
    {}

    virtual ~CliAppCmdRequestEvent()
    {}

    const string & GetPrompt() { return m_prompt; }

private:
    string m_prompt;
};

#endif
