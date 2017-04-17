///////////////////////////////////////////////////////////////////////////////
//
// SubscriberImsi.cpp
//
// See header file for documentation.
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
#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SubscriberImsi.h"

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: SubscriberImsi
// Desc : Allow various operations on the subscriber identity.
///////////////////////////////////////////////////////////////////////////////
SubscriberImsi::SubscriberImsi ()
{
        m_imsiString.clear(); 
}

SubscriberImsi::SubscriberImsi (const c_MobileId &mobileIdentity)
{
        int i;

        m_imsiString.clear(); 
	NAS_TRACE ("SubsciberImsi Initialising With", mobileIdentity);
	if (mobileIdentity.IdentityType != MI_IMSI)
	{
		NAS_MSG ("SubsciberImsi Error: Provided Identity Is Not An IMSI");
	}
	else
	{
		for (i=0;i<mobileIdentity.IdentityDigit.items;i++)
                {
			m_imsiString[i] = (u8)mobileIdentity.IdentityDigit.data[i];
                }

		TRACE("Copied Out IMSI", m_imsiString);
	}//end if

}

SubscriberImsi::SubscriberImsi (const SubscriberImsi &copy)
{
        m_imsiString.clear();
        m_imsiString = copy.m_imsiString;
 
	TRACE("Copy Contructor Copied", m_imsiString);
}

SubscriberImsi::~SubscriberImsi ()
{
}

SubscriberImsi& SubscriberImsi::operator= (const SubscriberImsi &rhs)
{
    ENTER();

    if(this == &rhs)
    {
        RETURN(*this);
    }

        m_imsiString.clear();
        m_imsiString = rhs.m_imsiString;

	TRACE("Assignment From SI Copied", m_imsiString);

	RETURN(*this);

}

SubscriberImsi& SubscriberImsi::operator= (const c_MobileId &rhs)
{
    ENTER();

        int i;
	NAS_TRACE ("Assignment From MobileId Initialising With", rhs);
	if (rhs.IdentityType != MI_IMSI)
	{
		NAS_MSG ("SubsciberImsi Error: Provided Identity Is Not An IMSI");
	}
	else
	{
                m_imsiString.clear();
 
		for (i=0;i<rhs.IdentityDigit.items;i++)
                {
			m_imsiString[i] = (u8)rhs.IdentityDigit.data[i];
                }

		TRACE("Copied Out IMSI", m_imsiString);
	}//end if

	RETURN(*this);

}

bool SubscriberImsi::operator== (const SubscriberImsi &rhs) const
{
        return ( m_imsiString.compare(rhs.m_imsiString) ) == 0; 
}

bool SubscriberImsi::operator!= (const SubscriberImsi &rhs) const
{
    return(!operator==(rhs));
}

const char *SubscriberImsi::c_str () const
{
	return m_imsiString.c_str();
}
#endif /*0*/
