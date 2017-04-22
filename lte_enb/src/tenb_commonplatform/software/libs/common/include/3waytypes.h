///////////////////////////////////////////////////////////////////////////////
//
// 3waytypes.h
//
// Common type definitions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __3waytypes_h_
#define __3waytypes_h_

#include <Radisys.h>

#ifndef TRUE
#   define TRUE  1
#endif

#ifndef FALSE
#   define FALSE 0
#endif

#define FAILURE 0
#define SUCCESS 1

// Few things here from the old 3Way.h, should probably move to
// e.g. 3wayconstants.h and 3waymacros.h and include as required.
#ifndef SOCKET
typedef int SOCKET;
// Constants
#ifndef INVALID_SOCKET
static const int INVALID_SOCKET = -1;
#endif

#ifndef SOCKET_ERROR
static const int SOCKET_ERROR = -1;
#endif
#endif

#define MAX_PATH_LENGTH     256
#define MAX_PATH MAX_PATH_LENGTH

static const char FILE_SEPARATOR [] = "/";
static const char CURRENT_DIRECTORY [] = "./";

#endif
