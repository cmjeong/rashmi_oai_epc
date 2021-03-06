///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASTransport.cpp
//
// Connectionless UDP Datagram transmission class.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASTransport.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: NASTransport
//
// Connectionless data transfer.
//
///////////////////////////////////////////////////////////////////////////////

NASTransport::NASTransport (u16 recPortNumber, u16 sendPortNumber, const char *destinationAddr) :
	NASTransport_RedHat (recPortNumber, sendPortNumber, destinationAddr)
{
}

NASTransport::~NASTransport ()
{
}
