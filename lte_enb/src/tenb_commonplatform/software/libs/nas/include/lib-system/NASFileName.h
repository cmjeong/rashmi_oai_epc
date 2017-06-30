///////////////////////////////////////////////////////////////////////////////
//
// NASFileName.h
//
// Wrapper for file names using character arrays and MAX_PATH, to prevent
// repeated calls to memset and snprintf, etc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASFileName_h_
#define __NASFileName_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/TimeWrap.h>

///////////////////////////////////////////////////////////////////////////////
// Class: NASFileName
// Desc : Wrapper for character array file names.
///////////////////////////////////////////////////////////////////////////////
class NASFileName
{
public:
	// Construction / destruction.
	NASFileName ();
	NASFileName (const char *formatStr, ...);
	NASFileName (const char *fileDir, const char *nameStub, const threeway::TimeWrap &nasTime);
	NASFileName (const NASFileName &copy);
	virtual ~NASFileName ();

	// Create a file with the current date and time appended to the path name.
	const char *BuildDatedFile (const char *fileName);

	// Retrieve a formatted text string with the time_t.
	const char *GetFileName () const;

private:

	// Raw character array holding file + path information.
	char m_pathName[MAX_PATH];
};

#endif
