///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASObject.cpp
//
// If you want to keep track of some object in the NAS system, then derive
// it from here.  Information about creation, deletion and usage will then
// be logged using the NASTrace engine.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <NASTrace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASObject.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: NASObject
// Desc : Generic information is stored here that we can use to debug
//        object creation + deletion.
///////////////////////////////////////////////////////////////////////////////
NASObject::NASObject ()
{
	// Intentionally no NAS_ macros in here.  We will put explicit
	// function calls into this debug class as we need them.

	// Defaulted constructor to threeway::TimeWrap will obtain the current time.
}

NASObject::~NASObject ()
{
	m_deletionTime = time (0);

	// Debug call to record object lifespan here?
}

void NASObject::UpdateCreateTime ()
{
	NAS_ENTER ();
	m_creationTime.Touch ();
	NAS_EXIT ();
}

void NASObject::ClearTheScreen ()
{
	// This magic clears the console window!
	puts ("\33[H\33[2J");
}

const threeway::TimeWrap &NASObject::GetCreateTime () const
{
	return m_creationTime;
}

