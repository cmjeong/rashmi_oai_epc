///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// LIB24008Util.h
//
// Structure decodes, comparitors, etc. for the Encodix library.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LIB24008Util_h_
#define __LIB24008Util_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include "lib-system/NASString.h"
#include "ed_c.h"

typedef enum enumLACUnits
{
	DECIMAL_DIGITS,
	HEX_DIGITS
}LACUnits;

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

// Please, user code: supply long enough text buffers for the ToStr functions!

void LIB24008LocationAreaToStr (const c_LocationAreaId &lai, NASString& mccStr, NASString& mncStr, NASString& lacStr, LACUnits lacUnits = DECIMAL_DIGITS);
void LIB24008LocationAreaToStr (const c_LocationAreaId &lai, NASString& textBuffer);
void LIB24008MobileIdToStr (const c_MobileId &id, NASString& textBuffer);
std::string LIB24008MobileIdToStr (const c_MobileId &id);

// Private implementation of a comparitor for the c_MobileId structure.
enum CompareIdentityResult
{
	IDENTITY_IS_THE_SAME,
	IDENTITY_IS_DIFFERENT
};

// Compare two mobile identity structures for equality.
CompareIdentityResult CompareMobileIdentity (const c_MobileId &id1, const c_MobileId &id2);

// Convert a string MSISDN to the Encodix format.
void StringToEncodix (const char *numberString, c_TBCDArray &encodixNumber);

#endif
