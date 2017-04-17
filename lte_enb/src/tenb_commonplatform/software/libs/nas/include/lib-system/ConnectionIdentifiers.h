///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// ConnectionIdentifiers.h
//
// Build an STL container holding a range of Connection Numbers that can
// be used by some part of the system.
//
// Copyright © 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ConnectionIdentifiers_h_
#define __ConnectionIdentifiers_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include <NumberList.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

enum ConnectionNumberStatus
{
	ConnectionId_Available,
	ConnectionId_InUse
};

typedef std::map <u32, ConnectionNumberStatus> ConnectionNumbers;

///////////////////////////////////////////////////////////////////////////////
// Class: ConnectionIdentifiers
// Desc : Manage an array of connection numbers, allocation, release etc.
///////////////////////////////////////////////////////////////////////////////
class ConnectionIdentifiers
{
public:
	// Construction / destruction.
	ConnectionIdentifiers (u32 firstConnectionId, u32 lastConnectionId);
	ConnectionIdentifiers (const NumberList &numberList);
	ConnectionIdentifiers ();
	virtual ~ConnectionIdentifiers ();

	void SetConnectionIdentifiers (const NumberList &numberList);

	// Accessors to allow used to allocate + release connection
	// numbers.
	u32 AllocateConnectionId ();
	void FreeConnectionId (u32 connectionId);
	void FreeAllConnectionIds ();

	// How many left for use?
	u32 GetAvailableIdCount () const;

	// Debug helper to check the status of the controlled number list.
	void GetString (std::string &idString) const;

private:

	// The stl container we maintain the connection numbers in.
	ConnectionNumbers m_availableNumbers;

	// Keep track of the number of values we have left for use
	// in the container: speeds up some of the accessors to maintain
	// this count separately.
	u32 m_availableCount;
};

#endif
