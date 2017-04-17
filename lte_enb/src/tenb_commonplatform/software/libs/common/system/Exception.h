///////////////////////////////////////////////////////////////////////////////
//
// Exception.h
//
// Generic exception class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Exception_h_
#define __Exception_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class Exception
{
public:
    Exception (const char *fileId, u32 lineNum, const char *format_p, ...) __attribute__((format(printf, 4, 5)));
	Exception (const char *fileId, u32 lineNum);
    virtual ~Exception ();

	virtual const char *what () const;
	const char *getFileId() const;
	u32 getLineNumber() const;

private:

	// Foramtted exception description.
    char m_exDesc[1024];

	// The name of the file the exception was generated in.
	char m_fileId[MAX_PATH_LENGTH];

	// And the line number which threw.
	u32 m_lineNumber;
};

}

#endif
