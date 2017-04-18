///////////////////////////////////////////////////////////////////////////////
//
// Exception.cpp
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
#include <stdarg.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Exception.h"
#include "Trace.h"

namespace threeway
{

Exception::Exception (const char *fileId, u32 lineNum, const char* format_p, ...) :
	m_lineNumber (lineNum)
{
	ENTER();

	static char s_buffer[1024] = { '\0', };

    va_list args;
    va_start (args, format_p);
    vsnprintf (s_buffer, sizeof(s_buffer), format_p, args);
    va_end (args);

    const char* filename_p = strrchr (fileId, '\\');
    if (filename_p)
    {
        filename_p++;
    }
    else
    {
        filename_p = fileId;
    }//end if

	snprintf (m_fileId, sizeof(m_fileId), "%s", fileId);
	snprintf (m_exDesc, sizeof(m_exDesc), "%s:%u:%s\n", filename_p, lineNum, s_buffer);

	EXIT();
}

Exception::Exception (const char *fileId, u32 lineNum) :
	m_lineNumber(lineNum)
{
	ENTER();

    const char* filename_p = strrchr (fileId, '\\');
    if (filename_p)
    {
        filename_p++;
    }
    else
    {
        filename_p = fileId;
    }//end if

	snprintf (m_fileId, sizeof(m_fileId), "%s", fileId);
	snprintf (m_exDesc, sizeof(m_exDesc), "%s:%u\n", filename_p, lineNum);

	EXIT();
}

Exception::~Exception ()
{
	ENTER();
	EXIT();
}

const char* Exception::what (void) const
{
    return m_exDesc;
}

const char *Exception::getFileId() const
{
	return m_fileId;
}

u32 Exception::getLineNumber() const
{
	return m_lineNumber;
}

}
