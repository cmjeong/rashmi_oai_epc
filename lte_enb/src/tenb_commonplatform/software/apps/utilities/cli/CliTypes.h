///////////////////////////////////////////////////////////////////////////////
//
// CliTypes.h
//
// Basic types for CLI app.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliTypes_h_
#define __CliTypes_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <messaging/transport/CliHandler.h>

#include "CliCmdFile.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////
typedef map<string, CliCmdFile> RegisteredCommandsMap;

typedef vector<string> StringVector ;

/*
 * Type used to consolidate "ordinary" (single byte) keypresses and escape sequences into
 * an easy to handle form!
 */
typedef enum KeyEventTypeTag
{
    NO_KEY,
    NORMAL_KEY,
    CURSOR_UP,
    CURSOR_DOWN,
    CURSOR_LEFT,
    CURSOR_RIGHT,
    DELETE,
    INSERT,
    HOME,
    END
} KeyEventType;


#endif /* __CliTypes_h_ */
