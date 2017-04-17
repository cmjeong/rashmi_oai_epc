///////////////////////////////////////////////////////////////////////////////
//
// PlmnId.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <iomanip>
#include <system/Trace.h>
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "PlmnId.h"

using namespace std;
using namespace threeway;

namespace rsysmob
{

#define PLMNID_REGEX \
    ERE_START \
    ERE_PLMNID \
    ERE_END

Regex PlmnId::s_plmnIdRegex( PLMNID_REGEX );

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

PlmnId::PlmnId() :
    m_mcc(0xffff),
    m_mnc(0xffff),
    m_isSet(false),
    m_isTwoDigitMnc(false)
{
}

PlmnId::PlmnId(u16 mcc, u16 mnc, bool isTwoDigitMnc) :
    m_mcc(mcc),
    m_mnc(mnc),
    m_isSet(true),
    m_isTwoDigitMnc(isTwoDigitMnc)
{
    RSYS_ASSERT_PRINTF(mcc <= 999, "MCC=%"PRIu16, mcc);
    RSYS_ASSERT_PRINTF(mnc <= 999, "MNC=%"PRIu16, mnc);
}

PlmnId::~PlmnId()
{
}

bool PlmnId::Validate(const string & plmnIdString )
{
    bool valid = s_plmnIdRegex.Compare(plmnIdString.c_str());

    if(!valid)
    {
        TRACE_PRINTF("PlmnId validation failure (%s).", plmnIdString.c_str());
    }

    return valid;
}

u16 PlmnId::GetMcc() const
{
    RSYS_ASSERT(m_isSet);

    return m_mcc;
}

u16 PlmnId::GetMnc( bool * isTwoDigit ) const
{
    RSYS_ASSERT(m_isSet);
    if(isTwoDigit)
    {
        *isTwoDigit = m_isTwoDigitMnc;
    }
    return m_mnc;
}

void PlmnId::Set( const string & plmnIdString )
{
    RSYS_ASSERT_PRINTF(Validate(plmnIdString),  "PlmnId::Set(%s) failed validation.", plmnIdString.c_str());

    stringstream mcc;
    mcc << plmnIdString.substr(0, 3);
    stringstream mnc;
    mnc << plmnIdString.substr(3);

    mcc >> m_mcc;
    mnc >> m_mnc;

    m_isTwoDigitMnc = (2 == mnc.str().length());

    m_isSet = true;
}

string PlmnId::Get() const
{
    RSYS_ASSERT(m_isSet);

    ostringstream stream;

    u8 mccBcd[3];
    U16ToBCD(m_mcc, 3, mccBcd, sizeof(mccBcd));

    u8 mncBcd[3];
    U16ToBCD(m_mnc, 3, mncBcd, sizeof(mncBcd));

    stream << setfill('0')
           << std::setw(3) << m_mcc
           << std::setw(m_isTwoDigitMnc?2:3) << m_mnc;

    return stream.str();
}

void PlmnId::SetFromBcdEncoded(const u8* encodedBcd)
{
    u8 mcc1, mcc2, mcc3, mnc1, mnc2, mnc3;

    mcc1 = encodedBcd[0] & 0x0f;
    mcc2 = encodedBcd[0] >> 4;

    mcc3 = encodedBcd[1] & 0x0f;
    mnc3 = encodedBcd[1] >> 4;

    mnc1 = encodedBcd[2] & 0x0f;
    mnc2 = encodedBcd[2] >> 4;

    m_mcc = 100 * mcc1 + 10 * mcc2 + mcc3;
    m_mnc = 10 * mnc1 + mnc2;
	
	m_isTwoDigitMnc = true;
    if (mnc3 != 0xf) 
	{
        m_mnc = 10 * m_mnc + mnc3;
		m_isTwoDigitMnc = false;
    }

	m_isSet = true;
}

void PlmnId::SetFrom25469BcdEncoded(const u8* encodedBcd)
{
    u8 mcc1, mcc2, mcc3, mnc1, mnc2, mnc3;

    mcc1 = encodedBcd[0] & 0x0f;
    mcc2 = encodedBcd[0] >> 4;

    mcc3 = encodedBcd[1] & 0x0f;
    mnc1 = encodedBcd[1] >> 4; // filler incase of two digit MNC

    mnc2 = encodedBcd[2] & 0x0f;
    mnc3 = encodedBcd[2] >> 4;

    m_mcc = 100 * mcc1 + 10 * mcc2 + mcc3;
	if(mnc1 != 0xf)
	{
		m_mnc = 100 * mnc1 + 10 * mnc2 + mnc3;	
		m_isTwoDigitMnc = false;
	}
	else
	{
		m_mnc = 10 * mnc2 + mnc3;	
		m_isTwoDigitMnc = true;
	}

	m_isSet = true;

}

void PlmnId::GetAsBcdEncoded(u8* encodedBcd) const
{
    RSYS_ASSERT(m_isSet);

    u8 mccBcd[3];
    u8 mncBcd[3];

    U16ToBCD(m_mcc, 3, mccBcd, sizeof(mccBcd));
    U16ToBCD(m_mnc, 3, mncBcd, sizeof(mncBcd));

    encodedBcd[0] = (mccBcd[1] << 4) + (mccBcd[0] & 0x0f);

    bool twoDigitMnc = m_isTwoDigitMnc;

    if(twoDigitMnc && (mncBcd[0] != 0))
    {
        TRACE_MSG_LEV(TRACE_WARNING, "Two digit MNC requested but MSDigit is non-zero.  Will encode as 3 digit.");
        twoDigitMnc = false;
    }

    if(twoDigitMnc)
    {
        encodedBcd[1] = 0xf0 + (mccBcd[2] & 0x0f);
        encodedBcd[2] = (mncBcd[2] << 4) + (mncBcd[1] & 0x0f);
    }
    else
    {
        encodedBcd[1] = (mncBcd[2] << 4) + (mccBcd[2] & 0x0f);
        encodedBcd[2] = (mncBcd[1] << 4) + (mncBcd[0] & 0x0f);
    }
}

void PlmnId::GetAs25469BcdEncoded(u8* encodedBcd) const
{
    RSYS_ASSERT(m_isSet);

    u8 mccBcd[3];
    u8 mncBcd[3];

    U16ToBCD(m_mcc, 3, mccBcd, sizeof(mccBcd));
    U16ToBCD(m_mnc, 3, mncBcd, sizeof(mncBcd));

    encodedBcd[0] = (mccBcd[1] << 4) + (mccBcd[0] & 0x0f);

    if(m_isTwoDigitMnc)
    {
        if(mncBcd[0] == 0)
        {
            mncBcd[0] = 0x0f; // Filler digit
        }
        else
        {
            TRACE_MSG_LEV(TRACE_WARNING, "Two digit MNC requested but MSDigit is non-zero.  Will encode as 3 digit.");
        }
    }

    encodedBcd[1] = (mncBcd[0] << 4) + (mccBcd[2] & 0x0f);
    encodedBcd[2] = (mncBcd[2] << 4) + (mncBcd[1] & 0x0f);
}

bool PlmnId::operator==(const PlmnId& rhs) const
{
    if(m_isSet != rhs.m_isSet)
    {
        return false;
    }

    return ((m_isTwoDigitMnc == rhs.m_isTwoDigitMnc) && (m_mcc == rhs.m_mcc) && (m_mnc == rhs.m_mnc));
}

string PlmnId::ToString() const
{
    ostringstream stream;

    if(m_isSet)
    {
        u8 mccBcd[3];
        U16ToBCD(m_mcc, 3, mccBcd, sizeof(mccBcd));

        u8 mncBcd[3];
        U16ToBCD(m_mnc, 3, mncBcd, sizeof(mncBcd));

        stream << setfill('0')
               << "MCC=" << std::setw(3) << m_mcc << ", "
               << "MNC=" << std::setw(m_isTwoDigitMnc?2:3) << m_mnc;
    }
    else
    {
        stream << "PLMN ID NOT SET";
    }

    return stream.str();
}

}
