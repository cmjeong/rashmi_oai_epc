///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// audio_relay.h
//
// Shared messaging between the cs-user-plane application, controlling audio
// send + receive between layer 1 FIFO's and some remote gateway.
//
// Copyright ? 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __audio_relay_h_
#define __audio_relay_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <arpa/inet.h>

#include "iu_user_plane.h"
#include "fifo_messages.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

typedef enum enumAudioPathMessageType
{
	CREATE_ROUTE		= 0x10,
	CREATE_ROUTE_ACK	= 0x11,
	CREATE_ROUTE_NACK	= 0x12,
	MODIFY_ROUTE 		= 0x13,
	MODIFY_ROUTE_ACK	= 0x14,
	MODIFY_ROUTE_NACK	= 0x15,
	DELETE_ROUTE 		= 0x16,
	DELETE_ROUTE_ACK	= 0x17,
	DELETE_ROUTE_NACK	= 0x18,
	RESET_USER_PLANE    = 0x20,
	
	INVALID_AUDIO_PATH_MSG_TYPE = 0xff

}AudioPathMessageType;

typedef struct structAudioPathMessage
{
	// Indicates whether this message is intended to create
	// a new audio route, modify an existing route, or tear
	// down an already established route.
	AudioPathMessageType messageType;

	// When running in an IU network, the CREATE_ROUTE populates this 
	// element with the parameters obtained from the RANAP signalling.
	IuUserPlane iuUserPlane;

	// The port which cs-user-plane is receiving audio packets on
	// for this call.
	u16 localPort;

	// The port which cs-user-plane is sending audio packets to
	// for this call.
	u16 remotePort;

	// The IP address of the destination for the audio packets
	// sent from cs-user-plane.
	char remoteDestination [18];

	// In IU mode, if the user plane could not be established, return
	// a fault code to nas-iu for relay to the switch.
	//u32 nackCause;

}AudioPathMessage;

//#define AUDIO_PATH_MSG_BUFFER_SIZE			sizeof (AudioPathMessage)

//#define MEDIA_USER_CMD_PORT 		7150

// Cache the size of the sockaddr 'cos I'm getting sick typing it in >:-)
static const int sockAddrSize = sizeof (struct sockaddr_in);


#endif

