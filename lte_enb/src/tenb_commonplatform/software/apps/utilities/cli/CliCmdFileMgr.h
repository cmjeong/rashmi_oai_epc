///////////////////////////////////////////////////////////////////////////////
//
// CliCmdFile.h
//
// Class representing file based CLI commands.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliCmdFileMgr_h_
#define __CliCmdFileMgr_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <set>
#include <string>
#include <string.h>

#include "CliCmdFile.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

class CliCmdFileMgr
{
private:
    CliCmdFileMgr();

public:
    ~CliCmdFileMgr(){}
    static CliCmdFileMgr & GetInstance();
    static CliCmdFileMgr * s_instance;

    void GetMatchingCommands( const string & filter, set<string> & matches );

    void ListAllMatchingCommands( set<string> & allMatchingCommands, const string & partialCommand );
    void ListAllNamespaces( set<string> & allNamespaces );

private:
    map< string, CliCmdFile > m_commands;
    set< string > m_allCommands;

};
#endif /* __CliTypes_h_ */
