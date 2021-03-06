///////////////////////////////////////////////////////////////////////////////
//
// IntegrityKey.h
//
// Encapsulate the 16 byte / 128 bit integrity key in a type class, so we can
// share common operations across the NAS.
//
// Copyright ? 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IntegrityKey_h_
#define __IntegrityKey_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

class IntegrityKey
{
public:
	IntegrityKey ();
	IntegrityKey (const u8 *ik);
	virtual ~IntegrityKey ();

	const u8 *GetIK () const { return m_integrityKey; }
	IntegrityKey& operator= (const u8 *ik);

	virtual std::string ToString () const;

private:

private:

	u8 m_integrityKey [16];
};

#endif
