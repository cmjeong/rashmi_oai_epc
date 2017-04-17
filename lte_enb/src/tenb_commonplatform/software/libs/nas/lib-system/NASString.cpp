///////////////////////////////////////////////////////////////////////////////
//
// NASString.cpp
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

#include <system/TimeWrap.h>
#include <system/Trace.h>
#include <system/StringUtils.h>

#include <NASTrace.h>
#include <lib-system/NASTrace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASString.h"
#include "NASTextFile.h"

///////////////////////////////////////////////////////////////////////////////
// Class: NASString
// Desc : Wrapper for character array strings.
///////////////////////////////////////////////////////////////////////////////
NASString::NASString (u16 bufferLength) :
	m_stringLength (0),
	m_bufferLength (0),
	m_charArray (NULL)
{
    if (bufferLength > MAX_NAS_STRING)
    {
        bufferLength = MAX_NAS_STRING;
    }
    if(bufferLength > 0)
    {
        m_charArray = new char [bufferLength];
        memset (m_charArray, '\0', bufferLength);
    }
	m_bufferLength = bufferLength;
}

NASString::NASString (const NASString &copy) :
	m_stringLength (0),
	m_bufferLength (0),
	m_charArray (NULL)
{
	Copy (copy);
}

NASString::NASString (const char *copy) :
	m_stringLength (0),
	m_bufferLength (0),
	m_charArray (NULL)
{
	// Don't forget +1 for the NULL terminator.
	m_stringLength = (u16) strlen (copy);
	if (m_stringLength > 0)
	{
	    if(m_stringLength > MAX_NAS_STRING - 1)
	    {
	        m_stringLength = MAX_NAS_STRING - 1;
	    }
		m_bufferLength = m_stringLength + 1;
		m_charArray = new char [m_bufferLength];

		strncpysafe (m_charArray, copy, m_bufferLength);
	}//end if
}

NASString::NASString (const threeway::TimeWrap &theTime, bool includeMicrosecs) :
	m_stringLength (0),
	m_bufferLength (0),
	m_charArray (NULL)
{
	char tempTimeStr[512];
	memset (tempTimeStr, 0, sizeof (tempTimeStr));
	theTime.GetDateStr (tempTimeStr, sizeof(tempTimeStr), includeMicrosecs);

	m_stringLength = (u16) strlen (tempTimeStr);
	if (m_stringLength > 0)
	{
	    /* The following can never occur as long as timeTempStr is smaller than MAX_NAS_STRING
	     * if(m_stringLength > MAX_NAS_STRING - 1)
         * {
         *     m_stringLength = MAX_NAS_STRING - 1;
         * }
         */
		m_bufferLength = m_stringLength + 1;
		m_charArray = new char [m_bufferLength];

		strncpysafe (m_charArray, tempTimeStr, m_bufferLength);
	}//end if
}

NASString::NASString (const BCDAddress &bcdAddress, bool includeTypeOfAddress) :
	m_stringLength (0),
	m_bufferLength (0),
	m_charArray (NULL)
{
    // Preconditions.
    RSYS_ASSERT(bcdAddress.addressLength <= sizeof(bcdAddress.bcdDigit));

	if (bcdAddress.addressLength > 0)
	{
		m_bufferLength = 64;
		m_charArray = new char [m_bufferLength];
		memset (m_charArray, '\0', m_bufferLength);

		char tempCharArray[26];
		memset (tempCharArray, '\0', sizeof (tempCharArray));
		for (u8 i=0, digitCount=0;i<bcdAddress.addressLength - 1;i++)
		{
			u8 digit1 = bcdAddress.bcdDigit[i] & 0x0f;
			u8 digit2 = (bcdAddress.bcdDigit[i] & 0xf0) >> 4;

			tempCharArray[digitCount++] = digit1 + 48;
			if (digit2 != 0x0f)
				tempCharArray[digitCount++] = digit2 + 48;
		}//end for

		if (includeTypeOfAddress)
		{
			m_stringLength = snprintf (
				m_charArray, m_bufferLength, "TypeOfAddr [0x%02X] : %s", bcdAddress.typeOfAddress, tempCharArray);
		}
		else
		{
			strncpysafe (m_charArray, tempCharArray, m_bufferLength);
		}//end if
	}//end if
}

NASString::~NASString ()
{
	Clear ();
}

void NASString::Copy (const NASString &rhs)
{
	Clear ();

	m_stringLength = rhs.m_stringLength;
	if (m_stringLength > 0)
	{
        if(m_stringLength > MAX_NAS_STRING - 1)
        {
            m_stringLength = MAX_NAS_STRING - 1;
        }
		m_bufferLength = m_stringLength + 1;
		m_charArray = new char [m_bufferLength];

		strncpysafe (m_charArray, rhs.m_charArray, m_bufferLength);
	}//end if
}

void NASString::Clear ()
{
	if (m_bufferLength > 0)
	{
		delete [] m_charArray;
		m_charArray = NULL;

		m_stringLength = 0;
		m_bufferLength = 0;
	}//end if
}

NASString& NASString::operator= (const NASString &rhs)
{
    ENTER();

    if(this == &rhs)
    {
        RETURN(*this);
    }

	if (rhs.m_stringLength > 0)
	{
		Clear ();
		Copy (rhs);
	}//end if

	RETURN(*this);
}

NASString& NASString::operator= (const char *rhs)
{
    ENTER();

	if (strlen (rhs) > 0)
	{
		Clear ();

		// Plus one for the NULL terminator...
		m_stringLength = (u16) strlen (rhs);
        if(m_stringLength > MAX_NAS_STRING - 1)
        {
            m_stringLength = MAX_NAS_STRING - 1;
        }
		m_bufferLength = m_stringLength + 1;
		m_charArray = new char [m_bufferLength];

		strncpysafe (m_charArray, rhs, m_bufferLength);
	}//end if

	RETURN(*this);
}

bool NASString::operator== (const char *rhs) const
{
	return m_stringLength > 0 ? strcasecmp (m_charArray, rhs) == 0 : false;
}

bool NASString::operator!= (const char *rhs) const
{
	return (!operator==(rhs));
}

NASString::operator const char *() const
{
	return m_charArray;
}

NASString::operator char *()
{
	return m_charArray;
}

bool NASString::IsEmpty () const
{
	return GetLength () == 0;
}

void NASString::Empty ()
{
	if (m_bufferLength > 0)
		memset (m_charArray, 0, sizeof (m_charArray));
}

void NASString::CalculateLength ()
{
	m_stringLength = strlen (m_charArray);
}

void NASString::TrimSpaces ()
{
	if (m_charArray != NULL)
		NASTextFile::TidyString (m_charArray);
}

u16 NASString::GetLength () const
{
	return m_stringLength;
}

u16 NASString::GetSize () const
{
    return m_bufferLength;
}

u16 NASString::GetSizeRemaining () const
{
    u16 remaining = m_bufferLength - m_stringLength;
    if (remaining > m_bufferLength)
    {
        // something horrible has gone wrong with the string...
        remaining = 0;
    }
    return remaining;
}

