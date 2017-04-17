///////////////////////////////////////////////////////////////////////////////
//
// SubscriberImsi.h
//
// Wrapper for the IMSI Identity.  Allow us to use equality operators that
// in turn allow us to use Stl containers.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SubscriberImsi_h_
#define __SubscriberImsi_h_


///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include "ed_c.h"
#include "Layer3Constants.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: SubscriberImsi
// Desc : Allow various operations on the subscriber identity.
///////////////////////////////////////////////////////////////////////////////
class SubscriberImsi
{
public:
	// Construction / destruction.
	SubscriberImsi ();
	SubscriberImsi (const c_MobileId &mobileIdentity);
	SubscriberImsi (const SubscriberImsi &copy);
	virtual ~SubscriberImsi ();

	// Note we don't provide less than / greater than as these are
	// fairly meaningless concepts with regards to an IMSI.  A side
	// effect of this is we cannot use this as the 'first' argument
	// in an Stl map.
	SubscriberImsi& operator= (const SubscriberImsi &rhs);
	SubscriberImsi& operator= (const c_MobileId &rhs);
	bool operator== (const SubscriberImsi &rhs) const;
	bool operator!= (const SubscriberImsi &rhs) const;

	const char *c_str () const;

private:
        mutable std::string m_imsiString;
};

#endif
