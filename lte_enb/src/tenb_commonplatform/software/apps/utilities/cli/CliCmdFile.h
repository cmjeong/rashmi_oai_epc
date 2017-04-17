///////////////////////////////////////////////////////////////////////////////
//
// CliCmdFile.h
//
// Class representing file based CLI commands.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliCmdFile_h_
#define __CliCmdFile_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <set>
#include <string>
#include <string.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////
class CliCmdFile
{
public:
    CliCmdFile( const char * filename);
    ~CliCmdFile(){}

    bool found() {return m_found;}
    MessagingEntity GetMessagingEntity() { return m_entity;}
    u8 GetMinArgs() { return m_minArgs; }
    u8 GetMaxArgs() { return m_maxArgs; }
    const string & GetGroup() { return m_group; }
    const string & GetShortDescription() { return m_shortDesc; }
    const string & GetHelp() { return m_help; }

private:
    bool m_found;

    MessagingEntity m_entity;
    string m_cmdName;
    u8 m_minArgs;
    u8 m_maxArgs;
    string m_group;
    string m_shortDesc;
    string m_help;
} ;

#endif /* __CliTypes_h_ */
