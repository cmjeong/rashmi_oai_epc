///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// LinuxControlPipe.cpp
//
// Gobal system include file, contains types, structures, etc. commonly
// used in the application(s).
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <System3Way.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "LinuxControlPipe.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// The handle to use when reading a ControlPipeMessage out of
// the pipe.
PIPE_HANDLE ControlPipe_ReadHandle = 0;

// The handle to use when writing a ControlPipeMessage into
// the pipe.
PIPE_HANDLE ControlPipe_WriteHandle = 0;

void OpenControlPipe ()
{
	int pipeHandles[2] = { 0, 0 };

	int pipeResult = pipe (pipeHandles);
	if (pipeResult == -1)
	{
		// This is an absolutely fatal shutdown condition.  We will
		// be calling this early in program application, so nothing
		// is available to recover the situation.
		printf ("Fatal NAS Failure: The Control Pipe Failed [%u]\n", pipeResult);
		exit (-1);
	}//end if

	ControlPipe_ReadHandle = pipeHandles[0];
	ControlPipe_WriteHandle = pipeHandles[1];
}

void CloseControlPipe ()
{
	if (ControlPipe_ReadHandle != 0)
	{
		close (ControlPipe_ReadHandle);
		ControlPipe_ReadHandle = 0;
	}//end if

	if (ControlPipe_WriteHandle != 0)
	{
		close (ControlPipe_WriteHandle);
		ControlPipe_WriteHandle = 0;
	}//end if
}

unsigned GetTickCount ()
{
	struct timeval tv;
	gettimeofday (&tv, NULL);

	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

