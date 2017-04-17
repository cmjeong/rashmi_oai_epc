///////////////////////////////////////////////////////////////////////////////
//
// NASPhoneNumber.cpp
//
// Helper class taking the various different flavours of phone number and
// giving us one, consistent and reliable mechanism for searching, storing,
// displaying, etc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
//CODE_CLEANUP
#if 0
#include <NASTrace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASPhoneNumber.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Class: NASPhoneNumber
// Desc : Helper class taking the various different flavours of phone
//        number and giving us one, consistent and reliable mechanism for
//        searching, storing, displaying, etc.
///////////////////////////////////////////////////////////////////////////////
NASPhoneNumber::NASPhoneNumber () :
	m_numberOfDigits (0),
	m_phoneNumber(),
	m_phoneNumberAsString()
{
	NAS_ENTER ();

    m_phoneNumberAsString[0] = '\0';

    NAS_EXIT ();
}

NASPhoneNumber::NASPhoneNumber (const c_TBCDArray &encodixNumber) :
    m_numberOfDigits (0),
    m_phoneNumber(),
    m_phoneNumberAsString()
{
	NAS_ENTER ();

    m_phoneNumberAsString[0] = '\0';

	if (encodixNumber.items < MAX_E164_DIGITS)
	{
		u8 tempNumber[MAX_E164_DIGITS] = {0};

		m_numberOfDigits = (u8) encodixNumber.items;
		for (s32 i=0;i<encodixNumber.items;i++)
			tempNumber[i] = (u8) encodixNumber.data[i];

		PerformNumberTranslation (
			tempNumber,
			m_numberOfDigits,
			m_phoneNumber,
			m_numberOfDigits);
	}
	else
	{
		NAS_TRACE (
			"Encodix Error: Trying To Build Long Number",
			(u32) encodixNumber.items);
	}//end if

	NAS_EXIT ();
}

NASPhoneNumber::NASPhoneNumber (const u8 digitArray [], u8 digitCount) :
    m_numberOfDigits (0),
    m_phoneNumber(),
    m_phoneNumberAsString()
{
	NAS_ENTER ();
	CopyPhoneNumber (digitArray, digitCount);
	NAS_EXIT ();
}

void NASPhoneNumber::CopyPhoneNumber (const u8 digitArray [], u8 digitCount)
{
	NAS_ENTER ();

	m_numberOfDigits = 0;
	memset (m_phoneNumber, '\0', sizeof (m_phoneNumber));
    memset (m_phoneNumberAsString, '\0', sizeof (m_phoneNumberAsString));

	if (digitCount < MAX_E164_DIGITS)
	{
		PerformNumberTranslation (
			digitArray,
			digitCount,
			m_phoneNumber,
			m_numberOfDigits);
	}
	else
	{
		NAS_TRACE (
			"NASPhoneNumber Error: Trying To Build Long Number",
			(u32) digitCount);
	}//end if

	NAS_EXIT ();
}

NASPhoneNumber::NASPhoneNumber (const NASPhoneNumber &copy)
{
	NAS_ENTER ();

	m_numberOfDigits = copy.m_numberOfDigits;
	memcpy (m_phoneNumber, copy.m_phoneNumber, sizeof (m_phoneNumber));
    m_phoneNumberAsString[0] = '\0';

	NAS_EXIT ();
}

NASPhoneNumber::~NASPhoneNumber ()
{
	NAS_ENTER ();
	NAS_EXIT ();
}

const u8 *NASPhoneNumber::GetMSISDNDigits (u8 &numberOfDigits) const
{
	NAS_ENTER ();
	numberOfDigits = m_numberOfDigits;
	NAS_RETURN (m_phoneNumber);
}

void NASPhoneNumber::PerformNumberTranslation (const u8 originalNumber [], u8 orgNumberLength, u8 translatedNumber [], u8 &transNumberLength) const
{
	NAS_ENTER ();

	transNumberLength = 0;
	for (u8 digitCount = 0;digitCount < orgNumberLength;digitCount++)
	{
		switch (originalNumber[digitCount])
		{
		case '+':
			{
				translatedNumber[transNumberLength++] = '0';
				translatedNumber[transNumberLength++] = '1';
			}
			break;

		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			{
				translatedNumber[transNumberLength++] = originalNumber[digitCount];
			}
			break;

		default:
			{
				NAS_TRACE (
					"PerformNumberTranslation Received Unhandled Character",
					(u32) originalNumber[digitCount]);
			}
		}//end switch

	}//end for

	NAS_EXIT ();
}

bool NASPhoneNumber::operator== (const NASPhoneNumber &rhs) const
{
	NAS_ENTER ();

	RSYS_ASSERT(m_numberOfDigits <= sizeof(m_phoneNumber));
    RSYS_ASSERT(rhs.m_numberOfDigits <= sizeof(rhs.m_phoneNumber));

	if (m_numberOfDigits == rhs.m_numberOfDigits)
	{
		for (u8 i=0;i<m_numberOfDigits;i++)
		{
			if (m_phoneNumber[i] != rhs.m_phoneNumber[i])
			{
				NAS_RETURN (false);
			}//end if
		}//end for
	}
	else
	{
		NAS_RETURN (false);
	}//end if

	// If we make it to here, all of the comparitors have returned
	// true so the number is a match.
	NAS_RETURN (true);
}

bool NASPhoneNumber::operator!= (const NASPhoneNumber &rhs) const
{
	NAS_ENTER ();
	bool ne = ! (*this == rhs);
	NAS_RETURN (ne);
}

const char *NASPhoneNumber::GetString () const
{
	NAS_ENTER ();

	RSYS_ASSERT(m_numberOfDigits <= MAX_E164_DIGITS);

	// We only build it on demand, as a slight performance improvement.
	if (strlen (m_phoneNumberAsString) == 0)
	{
		if (m_numberOfDigits > 0)
		{
			// Standard Char-To-Int conversion in ASCII is 48 element offset.
		    u8 i;
			for (i = 0; i < m_numberOfDigits; i++)
			{
				m_phoneNumberAsString[i] = m_phoneNumber[i] + 48;
			}
			m_phoneNumberAsString[i] = 0;
		}
		else
		{
			strcat (m_phoneNumberAsString, "Unknown MSISDN");
		}//end if
	}//end if

	NAS_RETURN (m_phoneNumberAsString);
}
#endif /*0*/
