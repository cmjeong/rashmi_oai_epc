///////////////////////////////////////////////////////////////////////////////
//
// CliCommand.cpp
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

#include "CliApplication.h"
#include "CliCommand.h"

using namespace std;


CliCommand::CliCommand( const string & command, const string & args ) :
     m_command(command),
     m_args(args)
{
    // Look for an entity namespace in command...
    removeLeadingAndTrailingWhitespace(m_command);

    string::size_type firstspaceDelimPos = m_command.find(" ");
    string::size_type namespaceDelimPos  = m_command.find(".");
    if (namespaceDelimPos == string::npos || namespaceDelimPos > firstspaceDelimPos)
    {
        if(     (0 == m_command.compare( 0, firstspaceDelimPos, "help" )) ||
                (0 == m_command.compare( 0, firstspaceDelimPos, "namespace"))
           )
        {
            m_command.insert(0, "cli.");
        }
    }

    // Extract args into own field
    string::size_type argsDelimPos = m_command.find(" ");
    if( m_args.empty() && (argsDelimPos != string::npos))
    {
        m_args    = m_command.substr(argsDelimPos + 1);
        m_command = m_command.substr(0, argsDelimPos);
    }
    removeLeadingAndTrailingWhitespace(m_command);
    removeLeadingAndTrailingWhitespace(m_args);

    TRACE_PRINTF("CliCommand:: cmd=%s, args=%s\n",
            m_command.c_str(),
            m_args.c_str()
            );
}


const string & CliCommand::GetCommand()
{
    return m_command;
}

const string & CliCommand::GetArguments()
{
    return m_args;
}
