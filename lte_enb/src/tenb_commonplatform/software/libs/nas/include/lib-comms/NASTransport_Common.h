///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASTransport_Common.h
//
// Connectionless message transfer using UDP.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASTransport_Common_h_
#define __NASTransport_Common_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Thread.h>
#include "NASMessages.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class NASMessage;

// Longest string permitted for an IP Address xxx.xxx.xxx.xxx\0
#define MAX_IPSTRING 16

enum NASTransportState
{
	NAS_TRANSPORT_IDLE,
	NAS_TRANSPORT_STARTING,
	NAS_TRANSPORT_STARTED,
	NAS_TRANSPORT_STOPPING,
};

///////////////////////////////////////////////////////////////////////////////
// Class: NASTransport_Common
// Desc : Manage packing user data into a simple structure and sending it
//        to the specified address using UDP.
///////////////////////////////////////////////////////////////////////////////
class NASTransport_Common : public threeway::Thread  
{
public:
	NASTransport_Common (u16 recPortNumber, u16 sendPortNumber, const char *destinationAddr);
	virtual ~NASTransport_Common ();

	/**
	 * Get a message of the received messages queue.
	 */
	NASMessage *Pop();

    /**
     * Accessors for the port numbers and IP addresses this client is using.
     */
	void SetPorts (u16 sendPort, u16 rcvPort);
    void SetRecPortNumber(u16 portNumber);
    u16 GetRecPortNumber() const;
	void SetAppAddress (const char *ipAddress);
	const char *GetAppAddress () const;


protected:
	// Protected implementation attributes used by derived client socket classes.

	// Socket for sending / receiving datagrams.
	SOCKET m_nasTransport;

	// Queue of received messages from the remote end.
	NASMessages m_nasMessages;

    // Mutex to protect access to m_nasMessages.
    Mutex m_messagesMutex; 

	// The status of this connection.
	NASTransportState m_transportState;

	// Port number to try and connect on.
	u16 m_recPortNumber;
	u16 m_sendPortNumber;

	// Remote address to transmit to.
	char m_destinationAddr[MAX_IPSTRING];
    
private:

	// I have a problem here, that I _think_ is related to the Windows socket
	// implementation.  If you call the API ::sendto VERY rapidly (for instance,
	// a tight loop that sends multiple messages), the ::sento can fail silently.
	// The return is NOT SOCKET_ERROR, yet the message does not arrive at the
	// destination.  I can't see how to detect this failure when it occurs, so 
	// prevention is the way to go here.  I timestamp outgoing messages, and 
	// limit the Tx rate to 10 Hertz.  I suspect that this problem will vanish
	// on porting to to the embedded environment, but this will suffice for now.
	mutable u32 m_lastSendTime;
};

#endif

