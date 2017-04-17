///////////////////////////////////////////////////////////////////////////////
//
// ConfigurationFile.h
//
// Generic text configuration file reader (ported from NASTextFile).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ConfigurationFile_h_
#define __ConfigurationFile_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <vector>
#include <string>
#include <limits.h>

#include <Radisys.h>

using namespace std;

typedef map < string, string > ParameterMap;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * ConfigurationFile
 *
 * Read the configuration file, and provide accessors so the various
 * application parameters can be retrieved.
 */
class ConfigurationFile
{
public:
	/**
	 * Construction / destruction.
	 * This class will look for fileName in the current directory.
	 * If not found it will try altDirectory - if supplied.
	 */
    ConfigurationFile() {}
    ConfigurationFile (const string& fileName, const string& altDirectory);
	virtual ~ConfigurationFile ();

	/**
	 * Check if file exists.
	 */
	bool FileExists() const;

	// Read the configuration file, which at this time is just a plain
	// text file.  Will throw an exception and shutdown the calling
	// application for safety.
	void ReadConfigurationFile ();

	// Accessors for the parameters: should be safe to use the NAS_TRACE
	// macros for these.
	/***
	 * This is used to export a list of keys so that the caller doesn't need to know about
	 * the keys beforehand and can iterate through them and copy them over into the new IniNvStore format.
	 */
    std::vector<std::string> GetParameters() const;

	// Accessor to retrieve a given parameter.  Returns NULL if it cannot
	// be found.
	const char *GetStringParameter (const char *paramName, const char *paramDefault = "") const;
	u32 GetU32Parameter (const char *paramName, u32 paramDefault = UINT_MAX) const;
    s32 GetS32Parameter (const char *paramName, s32 paramDefault = INT_MAX) const;

	// Split a string into two parts (left hand + right hand side) based
	// upon the split charater provided.  It's in a string because that's
	// what ::strstr is expecting.
	static void SplitString (const char *src, const char *splitStr, char *lhs, char *rhs);

	// This does a split looking for the split character at the _end_ of the string
	// and counting back.  Uses strrchr
	static void ReverseSplitString (const char *src, char splitChar, char *lhs, char *rhs);

	// Remove leading + trailing spaces from the input string.
	static void TidyString (char *src);

    // Get info for debug.
    virtual string ToString() const;

protected:
	// All of the parameters loaded by a call to ReadConfigurationFile.
	// The accessor function does the decode of the native type.
	ParameterMap m_parameterMap;

private:
    // The maximum length of a line (in characters) in the config file.
    // Need an extra couple because we have 512 visible characters, plus the
    // carriage return / line feed pair.  Plus an additional terminating
    // NULL character.
    static const u32 TEXT_BUFFER_SIZE = 515;

    /**
     * Get path + file name, first in current dir then in alt dir.
     */
    std::string GetFullPath() const;

    // Find the parameter based on the name, then convert to native data
    // type and populate configuration structure.
    void InterpretParameter (char *paramName, char *paramValue);

    // TODO - move these to some utils class...
    u8 HexCharToU8 (char inChar);
    char U8ToHexChar(u8 inByte);

	// Name of the file to read.
	string m_fileName;

	// Alternative directory to look for file (other than current directory).
	string m_altDirectory;
};

}

#endif
