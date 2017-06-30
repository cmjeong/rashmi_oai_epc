///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// LinuxControlPipe.h
//
//
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LinuxControlPipe_h_
#define __LinuxControlPipe_h_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <Radisys.h>

// For similar reasons, use a PIPE_HANDLE type to distinguish this type of file
// descriptor in the code.  I didn't use PIPE in case it clashes with a system
// definition.
typedef int PIPE_HANDLE;

// The handle to use when reading a ControlPipeMessage out of
// the pipe.
extern PIPE_HANDLE ControlPipe_ReadHandle;

// The handle to use when writing a ControlPipeMessage into
// the pipe.
extern PIPE_HANDLE ControlPipe_WriteHandle;

// Maximum number of characters (including NULL) that can be in
// a user command line request.
#define MAXIMUM_CLI_REQUEST_LENGTH      33

typedef struct structCLIPipeMessage
{
    // The IP Address of the machine which sent this request: the response
    // will be sent there.
    struct sockaddr remoteIpAddress;

    // We are implementing a simple CLI Over UDP so we can remotely
    // check the health of the applications: this will hold the
    // command entered by the user.  32 characters should be more
    // than sufficient!
    char cliRequest [MAXIMUM_CLI_REQUEST_LENGTH];

}CLIPipeMessage;

// This is the message payload sent on the control pipe.
typedef struct structControlPipeMessage
{
    // At the moment, the only reason as thread has for posting
    // notification in here is that there is data available for the
    // main thread, be it a timer expiry or data received event.

    // So all we need, for now, is the source thread handle.
    u32 threadHandle;

    // And for the case of the user invoked CLI functions, the details
    // of the request.
    CLIPipeMessage cliMessage;

}ControlPipeMessage;


// Get the pipe started: the handles above are not valid unless
// this call is succesful.
void OpenControlPipe ();

// Don't leak the pipe handles!  Call this at application shutdown.
void CloseControlPipe ();

#endif
