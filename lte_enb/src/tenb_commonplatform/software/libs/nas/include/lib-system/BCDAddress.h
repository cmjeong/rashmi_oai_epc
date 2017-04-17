///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// BCDAddress.h
//
// Wrapper structure for managing binary coded decimal values.  Also stores
// the associated TypeOfAddress field as it describes the type of the number.
//
// Copyright ? 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __BCDAddress_h_
#define __BCDAddress_h_

typedef struct structBCDAddress
{
	// Length is the number of digits / 2 remember, as we have BCD values.
	u8 addressLength;

	// Describes the decoding rules to apply for this type of number.
	u8 typeOfAddress;

	// The binary coded decimal digits.
	u8 bcdDigit[26];
}BCDAddress;

bool BCDCompare (const BCDAddress &lhs, const BCDAddress &rhs);
void BCDToString (const BCDAddress &bcdAddress, char *bcdString);
void StringToBCD (const char *numberString, BCDAddress &bcdAddress);

#endif
