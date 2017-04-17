///////////////////////////////////////////////////////////////////////////////
//
// CliInput.h
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliInput_h_
#define __CliInput_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <istream>
#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <system/SelectorInterfaces.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "CliUserInput.h"

using namespace boost;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Local Constants
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

class CliInput
{
public:
    CliInput() {}
    virtual ~CliInput() {}

    virtual void StartCommandLineInputThread(){};
    virtual void StopCommandLineInputThread(){};
    virtual void GetNextCommand( const string & prompt ) = 0;

    void HandleCommand( string & command );

private:
};

class CliInputStdin : public CliInput, public SelectorCallBackInterface
{
public:
    CliInputStdin( SelectorRegisterInterface&sri ) :
        m_sri(sri)
    {
        sri.RegisterFD(STDIN_FILENO,*this);
    }
    virtual ~CliInputStdin();

    virtual void GetNextCommand( const string & prompt );

private:
    void SelectCallBack();
    SelectorRegisterInterface & m_sri;
};

class CliInputStdinInteractive : public CliInput
{
public:
    CliInputStdinInteractive() :
            m_waitingForNextCommand(false),
            m_failedReadsSinceLastKeyPress(0)
    {}
    virtual ~CliInputStdinInteractive();

    virtual void StartCommandLineInputThread();
    virtual void StopCommandLineInputThread();
    virtual void GetNextCommand( const string & prompt );

    u32 GetPollRepeatTimeout();
    void HandleInteractiveInput();
private:
    void GetNextCommandWithInteractiveInput();
    bool GetNextKeyPress( unsigned char & c );
    UserInput   m_userInput;
    string      m_prompt;
    bool        m_waitingForNextCommand;
    u32         m_failedReadsSinceLastKeyPress;
};

class CliInputApplicationArgument : public CliInput
{
public:
    CliInputApplicationArgument( string & argument ) :
        m_argument(argument)
    {
        TRACE_PRINTF("CommandLine arg=%s",m_argument.c_str());
    }
    virtual ~CliInputApplicationArgument() {}

    virtual void GetNextCommand( const string & prompt );

private:
    string m_argument;
};


#endif
