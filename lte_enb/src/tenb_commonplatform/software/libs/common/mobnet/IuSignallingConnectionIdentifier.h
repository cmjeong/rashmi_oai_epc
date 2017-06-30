///////////////////////////////////////////////////////////////////////////////
//
// Iu_SignallingConnectionIdentifier.h
//
// Encapsulate the 24 bit (that's right, 24...) value.  Actually, it's 23
// bits, as the MSBit is reserved as a direction bit.  Nice.
//
// Copyright ? 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Iu_SignallingConnectionIdentifier_h_
#define __Iu_SignallingConnectionIdentifier_h_

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

class Iu_SignallingConnectionIdentifier
{
public:

	typedef enum enumIdAssignedBy
	{
		ID_ASSIGNED_BY_CN = 0x00800000,
		ID_ASSIGNED_BY_RNC = 0x00000000
	}IdAssignedBy;

	static const s32 IU_SIGNALLING_CONNECTION_ID_UNDEFINED = 0xff000000;
    static const u32 IU_SIGNALLING_CONNECTION_ID_MASK = 0x00ffffff;

public:
	Iu_SignallingConnectionIdentifier ();
	Iu_SignallingConnectionIdentifier (const Iu_SignallingConnectionIdentifier &copy);
	Iu_SignallingConnectionIdentifier (u32 id, IdAssignedBy idOwner);
	Iu_SignallingConnectionIdentifier (u32 idWithOwner);
	virtual ~Iu_SignallingConnectionIdentifier ();

	// The idBuff is expected to be a u8[3] for this call.  It's the format wanted
	// by the RANAP message builders...
	void GetId (u8 *idBuff) const;

	// Prefix increment operator...
	Iu_SignallingConnectionIdentifier &operator++ ();
	// Postfix increment operator...
	Iu_SignallingConnectionIdentifier operator++ (int);
	// Comparitor...
	bool operator== (const Iu_SignallingConnectionIdentifier &rhs) const;

	s32 GetID () const { return m_id; }
	void SetId (u32 idNumber, IdAssignedBy idOwner);

	std::string ToString (bool hexPlease = false) const;

private:

private:

	s32 m_id;
};

#endif
