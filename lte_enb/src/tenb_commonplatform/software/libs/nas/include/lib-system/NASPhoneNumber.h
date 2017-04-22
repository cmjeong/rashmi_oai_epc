///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASPhoneNumber.h
//
// Helper class taking the various different flavours of phone number and
// giving us one, consistent and reliable mechanism for searching, storing,
// displaying, etc.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASPhoneNumber_h_
#define __NASPhoneNumber_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <System3Way.h>
#include <ed_c.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: NASPhoneNumber
// Desc : Helper class taking the various different flavours of phone
//        number and giving us one, consistent and reliable mechanism for
//        searching, storing, displaying, etc.
///////////////////////////////////////////////////////////////////////////////
class NASPhoneNumber
{
public:
	// Construction / destruction.
	NASPhoneNumber ();
	NASPhoneNumber (const c_TBCDArray &encodixNumber);
	NASPhoneNumber (const u8 digitArray [], u8 digitCount);
	NASPhoneNumber (const NASPhoneNumber &copy);
	virtual ~NASPhoneNumber ();

	// Second phase copy constructure in case we need to assign after instantiation.
	void CopyPhoneNumber (const u8 digitArray [], u8 digitCount);

	// Overloaded comparison operators.
	bool operator== (const NASPhoneNumber &rhs) const;
	bool operator!= (const NASPhoneNumber &rhs) const;

	// Get the source digit information out of the object.
	const u8 *GetMSISDNDigits (u8 &numberOfDigits) const;

	// Used for debug display nad informative tracing, presumably.
	const char *GetString () const;

	// Take the input number and (possibly) expand: this includes operations
	// such as replacing +44 with the international operator code (which might
	// be our local international operator and valid).
	void PerformNumberTranslation (const u8 originalNumber [], u8 orgNumberLength, u8 translatedNumber [], u8 &transNumberLength) const;

private:

	// After all conversions and pratting around is finished in the
	// constructors, this will be a plain old digit array.
	// 24.008 says this is limited to 13 Octets, but doesn't mention
	// whether these are 13 BCD Octets or 1 Digit per Octet.  Assume the
	// former for safety.
	u8 m_phoneNumber[MAX_E164_DIGITS];
	u8 m_numberOfDigits;

	// We build a text string with the digits for debug output.  Note we
	// are MAX + 1 as we need an extra space for the NULL terminator.  We
	// are mutable so the first call to the (const) GetString can
	// populate the character array.
	mutable char m_phoneNumberAsString[MAX_E164_DIGITS + 1];
};

#endif

