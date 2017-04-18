///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASTextFile.h
//
// Generic text configuration file reader.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASTextFile_h_
#define __NASTextFile_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include <limits.h>

#include "3waytypes.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

typedef std::map < std::string, std::string > ParameterMap;

u8 HexCharToU8 (char inChar);
char U8ToHexChar (u8 inByte);

///////////////////////////////////////////////////////////////////////////////
// Class: NASTextFile
// Desc : Read the configuration file, and provide accessors so the
//        various application parameters can be retrieved.
///////////////////////////////////////////////////////////////////////////////
class NASTextFile
{
public:
	// Construction / destruction.
	NASTextFile (const char *fileDir, const char *fileName);
	virtual ~NASTextFile ();

	// Might want to change the directory to read the file from if it
	// wasn't available at object create time.
	void SetDirectoryName (const char *fileDir);

	// Read the configuration file, which at this time is just a plain
	// text file.  Will throw an exception and shutdown the calling
	// application for safety.
	void ReadNASTextFile ();

	// Accessors for the parameters: should be safe to use the NAS_TRACE
	// macros for these.

	// Accessor to retrieve a given parameter.  Returns NULL if it cannot
	// be found.
	const char *GetStringParameter (const char *paramName, const char *paramDefault = "") const;
	u32 GetU32Parameter (const char *paramName, u32 paramDefault = UINT_MAX) const;

	// Debug output method.
	void ShowParameters () const;

	// Split a string into two parts (left hand + right hand side) based
	// upon the split charater provided.  It's in a string because that's
	// what ::strstr is expecting.
	static void SplitString (const char *src, const char *splitStr, char *lhs, char *rhs);

	// Remove leading + trailing spaces from the input string.
	static void TidyString (char *src);

private:


	// Find the parameter based on the name, then convert to native data
	// type and populate configuration structure.
	void InterpretParameter (char *paramName, char *paramValue);

protected:

	// All of the parameters loaded by a call to ReadNASTextFile.
	// The accessor function does the decode of the native type.
	ParameterMap m_parameterMap;

private:

	// Name of the file to read.
	char m_fileName[MAX_PATH];

	// Directory in which the file exists.
	char m_fileDir[MAX_PATH];
};

#endif
