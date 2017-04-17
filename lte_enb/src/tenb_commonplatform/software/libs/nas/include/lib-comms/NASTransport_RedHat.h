///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASTransport_RedHat.h
//
// Connectionless message transfer using UDP.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASTransport_RedHat_h_
#define __NASTransport_RedHat_h_


///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <lib-system/LinuxControlPipe.h>

#include "NASTransport_Common.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class NASMessage;
class NASString;

///////////////////////////////////////////////////////////////////////////////
// Class: NASTransport_RedHat
// Desc : Manage packing user data into a simple structure and sending it
//        to the specified address using UDP.
///////////////////////////////////////////////////////////////////////////////
class NASTransport_RedHat : public NASTransport_Common
{
public:
	// Construction / destruction.
	NASTransport_RedHat (u16 recPortNumber, u16 sendPortNumber, const char *destinationAddr);
	virtual ~NASTransport_RedHat ();

	// Perform custom socket operations before starting the transport thread.
	virtual void StartThread (u32 threadStackSize);

	// Perform custom socket operations before stopping the transport thread.
	virtual void StopThread ();

	// Message sending functions.
	void SendMessage (const NASMessage& message) const;
	void Send (const u8 *msgData, u16 msgLength) const;
	void Send (const u8 *msgData, u16 msgLength, const char *destinationAddress) const;

	// Make sure the NASTransport object has the handle of the notification pipe
	// so data events can be passed to some controlling thread.
	void AttachNotificationPipe (PIPE_HANDLE pipeHandle);

private:

	// Implementation of the Win32 socket receive code and thread procedure.
	u32 ThreadProcedure ();

protected:

	// When data is added to the message queue (declared in the base class), we post a
	// notification to a (hopefully listening) parent thread to get the received
	// data handled.
	PIPE_HANDLE m_notificationPipe;
};

#endif

