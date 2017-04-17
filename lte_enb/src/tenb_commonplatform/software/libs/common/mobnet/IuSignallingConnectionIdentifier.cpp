///////////////////////////////////////////////////////////////////////////////
//
// Iu_SignallingConnectionIdentifier.cpp
//
// See header file for documentation.
//
// Copyright ? 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IuSignallingConnectionIdentifier.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

Iu_SignallingConnectionIdentifier::Iu_SignallingConnectionIdentifier () :
	m_id (IU_SIGNALLING_CONNECTION_ID_UNDEFINED)
{
	ENTER ();
	EXIT ();
}

Iu_SignallingConnectionIdentifier::Iu_SignallingConnectionIdentifier (const Iu_SignallingConnectionIdentifier &copy) :
	m_id (copy.m_id)
{
	ENTER ();
	EXIT ();
}

Iu_SignallingConnectionIdentifier::Iu_SignallingConnectionIdentifier (u32 id, IdAssignedBy idOwner)
{
	ENTER ();

	// Although it's a 24 bit quantity, the top bit is used to identify the number source:
	// validate the creation values before using them!
	if (id > 0x007fffff)
	{
		TRACE_MSG ("IuSignallingConnectionIdentifier Out-Of-Range (Set To 0 Instead)");
		m_id = idOwner | 0;
	}
	else
	{
		m_id = id | idOwner;
	}//end if

	EXIT ();
}

Iu_SignallingConnectionIdentifier::Iu_SignallingConnectionIdentifier (u32 idWithOwner) :
	m_id (idWithOwner)
{
	ENTER ();
	EXIT ();
}

Iu_SignallingConnectionIdentifier Iu_SignallingConnectionIdentifier::operator++ (int)
{
	ENTER ();

	Iu_SignallingConnectionIdentifier copiedItem (*this);
	++*this;

	RETURN (copiedItem);
}

Iu_SignallingConnectionIdentifier &Iu_SignallingConnectionIdentifier::operator++ ()
{
	ENTER ();

	// Empty IDs stay empty...
	if (m_id != IU_SIGNALLING_CONNECTION_ID_UNDEFINED)
	{
		if (m_id & ID_ASSIGNED_BY_CN)
		{
			// Watch out for rollover of CN allocated IDs: would we ever increment these?
			m_id = (m_id == 0x00ffffff ? ID_ASSIGNED_BY_CN | 0 : m_id+1);
		}
		else
		{
			m_id = (m_id == 0x007fffff ? ID_ASSIGNED_BY_RNC | 0 : m_id+1);
		}//end if
	}//end if

	RETURN (*this);
}

bool Iu_SignallingConnectionIdentifier::operator== (const Iu_SignallingConnectionIdentifier &rhs) const
{
	ENTER ();
	RETURN (m_id == rhs.m_id);
}

Iu_SignallingConnectionIdentifier::~Iu_SignallingConnectionIdentifier ()
{
	ENTER ();
	EXIT ();
}

void Iu_SignallingConnectionIdentifier::SetId (u32 idNumber, IdAssignedBy idOwner)
{
	ENTER ();
	m_id = idNumber | idOwner;
	EXIT ();
}

void Iu_SignallingConnectionIdentifier::GetId (u8 *idBuff) const
{
	ENTER ();

	idBuff[0] = (m_id & 0x00ff0000) >> 16;
	idBuff[1] = (m_id & 0x0000ff00) >> 8;
	idBuff[2] = m_id & 0x000000ff;

	EXIT ();
}

std::string Iu_SignallingConnectionIdentifier::ToString (bool hexPlease) const
{
	ENTER ();

	if (m_id == IU_SIGNALLING_CONNECTION_ID_UNDEFINED)
	{
		RETURN ("\nIuSignallingConnectionIdentifier\n ---------------------------------\nEMPTY");
	}

	char tempString [256];
	if (hexPlease)
	{
		snprintf (tempString, sizeof(tempString), "\nIuSignallingConnectionIdentifier\n ---------------------------------\n\
Assigned By :%s\nValue       : 0x%06" PRIX32 "\n", m_id & ID_ASSIGNED_BY_CN ? " CN" : " RNC", m_id & 0x007fffff);
	}
	else
	{
		snprintf (tempString, sizeof(tempString), "\nIuSignallingConnectionIdentifier\n ---------------------------------\n\
Assigned By :%s\nValue       : %" PRId32 "\n", m_id & ID_ASSIGNED_BY_CN ? " CN" : " RNC", m_id & 0x007fffff);
	}//end if

	RETURN (tempString);
}

