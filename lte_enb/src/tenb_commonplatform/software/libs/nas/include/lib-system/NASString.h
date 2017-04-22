///////////////////////////////////////////////////////////////////////////////
//
// NASString.h
//
// Implement a generic string handling class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASString_h_
#define __NASString_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/TimeWrap.h>
#include <BCDAddress.h>

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////

// The maximum length permitted for a string is 16,000 characters.
#define MAX_NAS_STRING	16000

///////////////////////////////////////////////////////////////////////////////
// Class: NASString
// Desc : Wrapper for character array strings.
///////////////////////////////////////////////////////////////////////////////
class NASString
{
public:
	// Construction / destruction.  Note bufferLength *must not* exceed
    // MAX_NAS_STRING, the ctor will truncate to this max size.
	NASString (u16 bufferLength = 128);
	NASString (const NASString &copy);
	NASString (const char *copy);
	NASString (const threeway::TimeWrap &theTime, bool includeMicrosecs = true);
	NASString (const BCDAddress &bcdAddress, bool includeTypeOfAddress = false);
	virtual ~NASString ();

	NASString& operator= (const NASString &rhs);
	NASString& operator= (const char *rhs);
	bool operator== (const char *rhs) const;
	bool operator!= (const char *rhs) const;

	// Now if you use these for snprintf, make sure you have enough
	// space allocated in the bufferLength.
	// ALWAYS USE snprintf to avoid scribbling off into space...
	operator const char *() const;
	operator char *();

	// And if you _set_ the length of the string using one of the
	// accessors above, call this to get the internal lengths correct.
	void CalculateLength ();

	// GetLength returns the textual length of the string (ie strlen)
    u16 GetLength () const;
    // GetSize returns the size of the allocated buffer
    u16 GetSize () const;
    // GetSizeRemaining returns the difference between GetSize and
    // GetLength or 0 if something has gone wrong!
    u16 GetSizeRemaining () const;

	bool IsEmpty () const;
	void Empty ();
	void TrimSpaces ();

private:

	void Clear ();
	void Copy (const NASString &rhs);

private:

	// The buffer containing the string.  Dynamically allocated in the
	// constructor.
	char *m_charArray;

	// Number of characters in the string above.
	u16 m_stringLength;

	// Number of characters allocated to the m_charArray.
	u16 m_bufferLength;
};

#endif
