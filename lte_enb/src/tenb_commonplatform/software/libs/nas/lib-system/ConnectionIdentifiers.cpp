///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// ConnectionIdentifiers.cpp
//
// Build an STL container holding a range of Connection Numbers that can
// be used by some part of the system.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <System3Way.h>
#include <NASTrace.h>
#include <string.h>
#include <limits.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "lib-system/ConnectionIdentifiers.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Class: ConnectionIdentifiers
// Desc : Manage an array of connection numbers, allocation, release etc.
///////////////////////////////////////////////////////////////////////////////
ConnectionIdentifiers::ConnectionIdentifiers (u32 firstConnectionId, u32 lastConnectionId) :
	m_availableCount (lastConnectionId - firstConnectionId + 1) // +1 as the boundaries are included in available range.
{
	NAS_ENTER();
	for (u32 i=firstConnectionId;i<=lastConnectionId;i++)
		m_availableNumbers.insert (std::make_pair (i, ConnectionId_Available));
	//end for
	NAS_EXIT();
}

ConnectionIdentifiers::ConnectionIdentifiers (const NumberList &numberList)
{
	NAS_ENTER ();
	SetConnectionIdentifiers (numberList);
	NAS_EXIT ();
}

ConnectionIdentifiers::ConnectionIdentifiers () :
	m_availableCount (0)
{
	NAS_ENTER ();
	NAS_EXIT ();
}

void ConnectionIdentifiers::SetConnectionIdentifiers (const NumberList &numberList)
{
	NAS_ENTER ();
	m_availableCount = numberList.size ();
	NumberList::const_iterator numberIter = numberList.begin ();
	while (numberIter != numberList.end ())
		m_availableNumbers.insert (std::make_pair (*numberIter++, ConnectionId_Available));
	NAS_EXIT ();
}

ConnectionIdentifiers::~ConnectionIdentifiers ()
{
	NAS_ENTER();
	NAS_EXIT();
}

u32 ConnectionIdentifiers::AllocateConnectionId ()
{
	NAS_ENTER();

	ConnectionNumbers::iterator idIter = m_availableNumbers.begin ();
	while (idIter != m_availableNumbers.end ())
	{
		if (idIter->second == ConnectionId_Available)
		{
			--m_availableCount;
			idIter->second = ConnectionId_InUse;
			NAS_RETURN(idIter->first);
		}//end if

		idIter++;
	}//end while

	NAS_RETURN(UINT_MAX);
}

void ConnectionIdentifiers::FreeConnectionId (u32 connectionId)
{
	NAS_ENTER();
	ConnectionNumbers::iterator idIter = m_availableNumbers.find (connectionId);
	if (idIter != m_availableNumbers.end ())
	{
		++m_availableCount;
		idIter->second = ConnectionId_Available;
	}//end if
	NAS_EXIT();
}

void ConnectionIdentifiers::FreeAllConnectionIds ()
{
	NAS_ENTER();

	ConnectionNumbers::iterator idIter = m_availableNumbers.begin ();
	while (idIter != m_availableNumbers.end ())
		idIter++->second = ConnectionId_Available;

	m_availableCount = m_availableNumbers.size ();
	NAS_EXIT();
}

u32 ConnectionIdentifiers::GetAvailableIdCount () const
{
	NAS_ENTER();
	NAS_RETURN(m_availableCount);
}

void ConnectionIdentifiers::GetString (std::string &idString) const
{
	NAS_ENTER ();

	char tempString [64];
	ConnectionNumbers::const_iterator idIter = m_availableNumbers.begin ();
	while (idIter != m_availableNumbers.end ())
	{
		bzero (tempString, sizeof (tempString));
		snprintf (tempString, sizeof(tempString), "[%" PRIu32 ":%s] ", idIter->first, idIter->second == ConnectionId_Available ? "FREE" : "USED");
		idString += tempString;
		idIter++;
	}//end while

	NAS_EXIT ();
}


