///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASFileName.cpp
//
// Wrapper for file names using character arrays and MAX_PATH, to prevent
// repeated calls to memset and snprintf, etc.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <NASTrace.h>
#include <system/TimeWrap.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASFileName.h"
#include "NASString.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: NASFileName
// Desc : Wrapper for character array file names.
///////////////////////////////////////////////////////////////////////////////
NASFileName::NASFileName ()
{
	NAS_ENTER ();
	memset (m_pathName, '\0', sizeof(m_pathName));
	NAS_EXIT ();
}

NASFileName::NASFileName (const char *formatStr, ...)
{
	NAS_ENTER ();

	memset (m_pathName, '\0', sizeof(m_pathName));

	// Do normal printf-type formattting to build file
	// and path name information.
	va_list args;
	va_start (args, formatStr);
	vsnprintf (m_pathName, sizeof(m_pathName), formatStr, args);
	va_end (args);

	NAS_EXIT ();
}

NASFileName::NASFileName (const NASFileName &copy)
{
	NAS_ENTER ();
	memset (m_pathName, '\0', sizeof(m_pathName));
	memcpy (m_pathName, copy.m_pathName, sizeof(m_pathName));
	NAS_EXIT ();
}

NASFileName::NASFileName (const char *fileDir, const char *nameStub, const threeway::TimeWrap &nasTime)
{
	NAS_ENTER ();

	char tempString[MAX_PATH];

	snprintf (tempString, sizeof(tempString), "%s%s", fileDir, nameStub);
	BuildDatedFile (tempString);

	NAS_EXIT ();
}

NASFileName::~NASFileName ()
{
}

const char *NASFileName::GetFileName () const
{
	NAS_ENTER ();
	NAS_RETURN (m_pathName);
}

const char *NASFileName::BuildDatedFile (const char *fileName)
{
	NAS_ENTER ();
	NAS_TRACE ("Building Dated File From Stub", fileName);

	memset (m_pathName, '\0', MAX_PATH);

	threeway::TimeWrap timeNow;
	const threeway::TimeStructure &ts = timeNow.GetTimeStructure ();
	snprintf (
		m_pathName,
        sizeof(m_pathName),
		"%s-%02" PRIu32 "%02" PRIu32 "%02" PRIu32 "%02" PRIu32 "%02" PRIu32 "%02" PRIu32,
		fileName,
		ts.theDay,
		ts.theMonth,
		ts.theYear,
		ts.theHour,
		ts.theMinutes,
		ts.theSeconds);

	NAS_RETURN (m_pathName);
}


