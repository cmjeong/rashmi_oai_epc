///////////////////////////////////////////////////////////////////////////////
//
// BCDAddress.cpp
//
// Helper functions that handle the BCDAddress structure.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <System3Way.h>
#include <lib-system/NASTrace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "BCDAddress.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

bool BCDCompare (const BCDAddress &lhs, const BCDAddress &rhs)
{
	NAS_ENTER ();

    // Preconditions.
	RSYS_ASSERT(lhs.addressLength <= sizeof(lhs.bcdDigit));
    RSYS_ASSERT(rhs.addressLength <= sizeof(rhs.bcdDigit));

	NAS_TRACE ("BCDCompare [lhs]", lhs);
	NAS_TRACE ("BCDCompare [rhs]", rhs);

	bool addressIsTheSame = true;
	if (lhs.addressLength > 0)
	{
		if (&lhs == &rhs)
		{
			addressIsTheSame = true;
		}
		else if (lhs.addressLength == rhs.addressLength)
		{
			// Don't forget the -1 for the typeOfAddress byte.
			for (u8 i=0;i<lhs.addressLength - 1;i++)
			{
				if (lhs.bcdDigit[i] != rhs.bcdDigit[i])
				{
					addressIsTheSame = false;
					break;
				}//end if
			}//end for
		}
		else
		{
			addressIsTheSame = false;
		}//end if
	}
	else
	{
		addressIsTheSame = false;
	}//end if

	NAS_RETURN (addressIsTheSame);
}

void BCDToString (const BCDAddress &bcdAddress, char *bcdString)
{
	NAS_ENTER ();

	// Preconditions.
	RSYS_ASSERT(bcdAddress.addressLength <= sizeof(bcdAddress.bcdDigit));

	NAS_TRACE ("BCDToString Converting", bcdAddress);

	u8 digitCount = 0, nextDigit = 0;
	for (u8 i=0; i < bcdAddress.addressLength; i++)
	{
		nextDigit = bcdAddress.bcdDigit[i] & 0x0f;
		bcdString[digitCount++] = (char) (nextDigit + 48);

		nextDigit = ((bcdAddress.bcdDigit[i] & 0xf0) >> 4);
		if (nextDigit != 0x0f)
			bcdString[digitCount++] = (char) (nextDigit + 48);
	}//end for

	NAS_TRACE ("Converted String Is", bcdString);

	NAS_EXIT ();
}

void StringToBCD (const char *numberString, BCDAddress &bcdAddress)
{
	NAS_ENTER ();

    // Preconditions.
	RSYS_ASSERT(numberString != NULL);

	NAS_TRACE ("StringToBCD Converting", numberString);

	bcdAddress.addressLength = 0;
	bcdAddress.typeOfAddress = 0;
	size_t strLen = strlen (numberString);

	for (size_t i = 0; i < strLen; i += 2)
	{
	    // Check for out-of-bounds.
	    RSYS_ASSERT(bcdAddress.addressLength < sizeof(bcdAddress.bcdDigit));

		bcdAddress.bcdDigit[bcdAddress.addressLength] = numberString[i] - 48;

		// Even or odd number of digits?
		bcdAddress.bcdDigit[bcdAddress.addressLength++] |=
				i + 1 < strLen ? (numberString[i+1] - 48) << 4 : 0xf0;
	}//end for

	NAS_TRACE ("Converted BCD", bcdAddress);
	NAS_EXIT ();
}


