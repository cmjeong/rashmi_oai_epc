///////////////////////////////////////////////////////////////////////////////
//
// NASTransport_Common.cpp
//
// Connectionless UDP Datagram transmission class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include <system/StringUtils.h>
#include <lib-system/NASTrace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASTransport_Common.h"
#include "NASSocketException.h"
#include "NASMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: NASTransport_Common
//
// Connectionless data transfer.
//
///////////////////////////////////////////////////////////////////////////////
NASTransport_Common::NASTransport_Common (u16 recPortNumber, u16 sendPortNumber, const char *destinationAddr) :
    Thread("NASTransport Thread"),
    m_recPortNumber(recPortNumber),
    m_sendPortNumber(sendPortNumber),
    m_nasTransport(INVALID_SOCKET),
	m_lastSendTime (0),
	m_transportState()
{
	// These objects _may_ be created VERY early during program execution,
	// and run until VERY late in termination.  And if thst is the
	// case, the NAS_ macros will fail with an Access Violation as this
	// object has a longer life than the NASTrace object. So, no
	// TRACE_ENTER / TRACE_EXIT macros.
	memset (m_destinationAddr, '\0', MAX_IPSTRING);
	memcpy (m_destinationAddr, destinationAddr, MAX_IPSTRING);

    Thread::InitialiseMutex(m_messagesMutex);

    SetThreadName("NASTransport");
}

NASTransport_Common::~NASTransport_Common()
{
    Thread::DestroyMutex(m_messagesMutex);
}


//***************************************************************************
//
// Method: NASTransport_Common::SetRecPortNumber
//
// Returns: void
//
// Description:
//     Set the port number to listen for incoming UDP datagrams.
//
//***************************************************************************
void NASTransport_Common::SetRecPortNumber(u16 recPortNumber)
{
    m_recPortNumber = recPortNumber;
}

void NASTransport_Common::SetPorts (u16 sendPort, u16 rcvPort)
{
	m_recPortNumber = rcvPort;
	m_sendPortNumber = sendPort;
}

//***************************************************************************
//
// Method: NASTransport_Common::GetRecPortNumber
//
// Returns: UInt32
//
// Description:
//     Get the port number to listen for incoming UDP datagrams.
//
//***************************************************************************
u16 NASTransport_Common::GetRecPortNumber() const
{
    return m_recPortNumber;
}

void NASTransport_Common::SetAppAddress (const char *ipAddress)
{
	NAS_ENTER ();

	strncpysafe (m_destinationAddr, ipAddress, sizeof (m_destinationAddr));

	NAS_EXIT ();
}

const char *NASTransport_Common::GetAppAddress () const
{
	NAS_ENTER ();
	NAS_RETURN (m_destinationAddr);
}

//***************************************************************************
//
// Method: NASTransport_Common::Pop
//
// Returns: HANDLE
//
// Description:
//     Get a message off the received messages queue.  Calling function is
//     responsible for object deletion.
//
//***************************************************************************
NASMessage *NASTransport_Common::Pop()
{
	Thread::LockMutex(m_messagesMutex, __NAS_FUNCTION__);

	if (m_nasMessages.size() > 0)
	{
		NASMessage *nasMessage = *(m_nasMessages.begin ());
		m_nasMessages.pop_front ();

        Thread::UnlockMutex(m_messagesMutex, __NAS_FUNCTION__);
		return nasMessage;
	}//end if

    Thread::UnlockMutex(m_messagesMutex, __NAS_FUNCTION__);

	return NULL;
}

