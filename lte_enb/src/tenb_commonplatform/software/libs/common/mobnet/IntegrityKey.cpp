///////////////////////////////////////////////////////////////////////////////
//
// IntegrityKey.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <system/Trace.h>
#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IntegrityKey.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

IntegrityKey::IntegrityKey ()
{
	ENTER ();
	bzero (m_integrityKey, sizeof (m_integrityKey));
	EXIT ();
}

IntegrityKey::IntegrityKey (const u8 *ik)
{
	ENTER ();
	bzero (m_integrityKey, sizeof (m_integrityKey));
	memcpy (m_integrityKey, ik, sizeof (m_integrityKey));
	EXIT ();
}

IntegrityKey::~IntegrityKey ()
{
	ENTER ();
	EXIT ();
}

IntegrityKey& IntegrityKey::operator= (const u8 *ik)
{
	ENTER ();

	bzero (m_integrityKey, sizeof (m_integrityKey));
	memcpy (m_integrityKey, ik, sizeof (m_integrityKey));

	RETURN(*this);
}

std::string IntegrityKey::ToString () const
{
	ENTER ();

	char tempString [256];
	snprintf (tempString, sizeof(tempString), "\
0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X \
0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X",
	m_integrityKey[0],
	m_integrityKey[1],
	m_integrityKey[2],
	m_integrityKey[3],
	m_integrityKey[4],
	m_integrityKey[5],
	m_integrityKey[6],
	m_integrityKey[7],
	m_integrityKey[8],
	m_integrityKey[9],
	m_integrityKey[10],
	m_integrityKey[11],
	m_integrityKey[12],
	m_integrityKey[13],
	m_integrityKey[14],
	m_integrityKey[15]);

	std::string hexString = tempString;
	RETURN (hexString);
}

