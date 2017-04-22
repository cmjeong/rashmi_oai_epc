///////////////////////////////////////////////////////////////////////////////
//
// NASTransport_RedHat.cpp
//
// Connectionless UDP Datagram transmission class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>

#include <system/StringUtils.h>
#include <comms/networking.h>

#include <lib-system/NASTrace.h>
#include <LinuxControlPipe.h>
#include <NASString.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASTransport_RedHat.h"
#include "NASSocketException.h"
#include "NASMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// We will enforce a 100 MilliSecond intercal between consecutive transmit
// attempts on the UDP socket.  Let's not stress the MS implementation too
// much, eh...
static const u32 MAX_SEND_FREQUENCY = 100;

///////////////////////////////////////////////////////////////////////////////
// Class: NASTransport_RedHat
//
// Connectionless data transfer.
//
///////////////////////////////////////////////////////////////////////////////
NASTransport_RedHat::NASTransport_RedHat (u16 recPortNumber, u16 sendPortNumber, const char *destinationAddr) :
	NASTransport_Common (recPortNumber, sendPortNumber, destinationAddr),
	m_notificationPipe()
{
}

NASTransport_RedHat::~NASTransport_RedHat()
{
}

void NASTransport_RedHat::AttachNotificationPipe (PIPE_HANDLE pipeHandle)
{
	NAS_ENTER ();
	m_notificationPipe = pipeHandle;
	NAS_EXIT ();
}

void NASTransport_RedHat::StartThread(u32 threadStackSize)
{
    // Open the UDP socket ready for send / receive of datagrams, then start
    // the thread up.
	NAS_TRACE ("NASTransport_RedHat Starting... RecvPort Is", (u32) m_recPortNumber);
	NAS_TRACE ("             Starting... SendPort Is", (u32) m_sendPortNumber);

    // Make sure we allow more than one user to bind to the port so
    // the MSC + BSC can run on the same machine.
    static char sockOpt[] = "SO_REUSEADDR";
    bool reuseAddr = true;
    int bindReturn, sockResult;
    struct sockaddr_in localAddress = {0};

	m_nasTransport = socket (PF_INET, SOCK_DGRAM, 0);
    if (m_nasTransport == INVALID_SOCKET)
    {
		TRACE_PRINTF ("Failed socket() call - Aborting...\n");
		exit (1);
    }//end if

    localAddress.sin_family = PF_INET;
    localAddress.sin_port = htons (m_recPortNumber);
    localAddress.sin_addr.s_addr = INADDR_ANY;

    // OK, attempt to bind to the port so we can receive as well as send.
    bindReturn = bind (m_nasTransport, (struct sockaddr *) &localAddress, sizeof(localAddress));
    if (bindReturn == SOCKET_ERROR)
    {
		TRACE_PRINTF ("Failed bind() call - Aborting...\n");
		exit (1);
    }//end if

    sockResult = setsockopt(
        m_nasTransport,
        SOL_SOCKET,
        reuseAddr,
        sockOpt,
        sizeof(sockOpt));

    if (sockResult == SOCKET_ERROR)
    {
		TRACE_PRINTF ("Failed SO_REUSEADDR call - Warning Only...\n");
    }//end if

	// Get base implementation to start the thread now.
    Thread::StartThread (threadStackSize);
}

//***************************************************************************
//
// Method: NASTransport_RedHat::StopThread
//
// Returns: void
//
//***************************************************************************
void NASTransport_RedHat::StopThread()
{
    Thread::StopThread ();

	if (m_nasTransport != INVALID_SOCKET)
	{
		NAS_TRACE("NASTransport_RedHat Stopping... RecvPort Is", (u32) m_recPortNumber);
		NAS_TRACE("             Stopping... SendPort Is", (u32) m_sendPortNumber);

		m_transportState = NAS_TRANSPORT_STOPPING;

		::shutdown (m_nasTransport, SHUT_RDWR);
		::close (m_nasTransport);

		m_nasTransport = INVALID_SOCKET;
	}//end if

	m_transportState = NAS_TRANSPORT_IDLE;
}

//***************************************************************************
//
// Method: NASTransport_RedHat::ThreadProcedure
//
// Returns: void
//
// Description:
//     Client connection thread which will listen for messages received from
//     the server and post notification to the registered window.
//
//***************************************************************************
u32 NASTransport_RedHat::ThreadProcedure()
{
	// Need to generate the NASMessage objects and put them into the queue
	// when new data is received on the port.
	NAS_TRACE("NASTransport_RedHat ReceiveThread Started on Port", (u32) m_recPortNumber);
	m_transportState = NAS_TRANSPORT_STARTED;


	// Buffer to receive messages.
	NASMessageStructure readBuffer;

	// Message sent to parent thread when data is added to the queue.
	ControlPipeMessage cpm;
	memset (&cpm, 0, sizeof (ControlPipeMessage));
	cpm.threadHandle = (u32)GetThreadHandle ();

	/* CGM - added to fix suspected race condition during startup.
	   We rely on the fact that the apps are always going to be started and we wait
	   here forever until the handle is valid */
	while (cpm.threadHandle == 0)
	{
		sleep (1);
		cpm.threadHandle = (u32)GetThreadHandle ();
	}//end while

	while (!ThreadStopped ())
	{
		// We will continue to block until data becomes available on the socket.
		// Wake up every second to check the status of the shutdown flag.
		fd_set fdSet;
		FD_ZERO (&fdSet);
		FD_SET (m_nasTransport, &fdSet);

		// Check for shutdown once per second.
		struct timeval timeVal;
		timeVal.tv_sec = 1;
		timeVal.tv_usec = 0;

		// Select will return after 1 Second if no Read takes place, so we
		// can check the shutdown request event.
		s32 selectResult = select (m_nasTransport + 1, &fdSet, 0, 0, &timeVal);
		if (selectResult <= 0)
		{
			// A socket result that is neither unexpected, nor indicative
			// that we need to do anything: it's the inactivity timer.
			// Do nothing!

			// Programmer note: now, I don't know why, but when the application
			// is closing down, we see repeated errors on the socket
			// of type 10093 [WSA_STARTUP FAILURE].  I think it's because the
			// shutdown call has been made but this thread is still active, so
			// silently supress the exception, but exit the thread.
		}
		else
		{
			// Next read retrieves the entire packet out of the buffer.
			s32 readResult = ::recvfrom (
				m_nasTransport,
				&readBuffer,
				sizeof (NASMessageStructure),
				0,
				NULL,
				NULL);

			if (readResult > 0)
			{
				NAS_TRACE ("Data Received On Port", (u32) m_recPortNumber);
				NAS_TRACE ("Size Of Data", (u32) readResult);

				// Cast to the transport structure and instantiate message
                Thread::LockMutex(m_messagesMutex, __NAS_FUNCTION__);
				const NASMessageStructure &newStruct = readBuffer;
				m_nasMessages.push_back (new NASMessage (newStruct));
                Thread::UnlockMutex(m_messagesMutex, __NAS_FUNCTION__);

				write (m_notificationPipe, &cpm, sizeof (cpm));
			}//end if
		}//end if

        // Check stack usage for this thread.
        //CheckStackUsage();

	}//end while

	return 1;
}

//***************************************************************************
//
// Method: NASTransport::SendMessage
//
// Returns: void
//
// Description:
//     	Fire off a datagram to the specified target.
//
//***************************************************************************
void NASTransport_RedHat::SendMessage (const NASMessage& message) const
{
	if (m_nasTransport != INVALID_SOCKET)
	{
		NAS_TRACE("Sending On Port", (u32) m_sendPortNumber);

        const NASMessageStructure &nasMsg = message.GetMessage ();
        Send ((const u8 *) &nasMsg, (u16) sizeof (NASMessageStructure));
	}//end if
}

void NASTransport_RedHat::Send (const u8 *msgData, u16 msgLength) const
{
	NAS_ENTER ();
	NAS_TRACE ("No Address Specified For Send: Defaulting To", m_destinationAddr);
	Send (msgData, msgLength, m_destinationAddr);
	NAS_EXIT ();
}

void NASTransport_RedHat::Send (const u8 *msgData, u16 msgLength, const char *destinationAddress) const
{
	NAS_ENTER ();
	NAS_TRACE ("Address Specified For Send Is", destinationAddress);
	if (m_nasTransport != INVALID_SOCKET)
	{
	    struct sockaddr_in targetAddress;
	    memset(&targetAddress, 0, sizeof (struct sockaddr_in));
		targetAddress.sin_family = PF_INET;
		targetAddress.sin_port = htons (m_sendPortNumber);
		targetAddress.sin_addr.s_addr = inet_addr (destinationAddress);

		s32 sendResult = ::sendto(
            m_nasTransport,
            (const char *) msgData,
            msgLength,
            0,
            (struct sockaddr *) &targetAddress,
            sizeof (targetAddress));

		if (sendResult == SOCKET_ERROR)
		{
			NAS_MSG ("ERROR On NASMessage Transport");
		}//end if
	}//end if

	NAS_EXIT ();
}
