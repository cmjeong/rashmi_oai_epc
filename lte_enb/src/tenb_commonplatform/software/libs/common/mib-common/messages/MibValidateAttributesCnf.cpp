///////////////////////////////////////////////////////////////////////////////
//
// MibValidateAttributesCnf.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibValidateAttributesCnf.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibValidateAttributesCnf::MibValidateAttributesCnf(const MibDN& dn, const MibAttrValidationFailures& failures)
{
    ENTER();

    AddFailures(dn, failures);

    EXIT();
}

s32 MibValidateAttributesCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    const u8* const dataStart = data;

    // Loop through failures and serialise each DN + MibAttrValidationFailures.
    for(MibAttrValidationFailuresByDn::const_iterator iter = m_failures.begin();
        iter != m_failures.end();
        ++iter)
    {
        // For each pair, need to put lengths in too.
        // So we have:
        //   DN length in bytes (u16)
        //   DN serialised bytes
        //   Validation failures length in bytes (u16)
        //   Validation failures serialised bytes
        u8* pDnLen = data; // Record where we'll write length.
        data += 2; // Skip over length field to be filled in later.
        s32 dnLen = iter->first.Serialise(data, dataMaxBytes - (data - dataStart));
        data += dnLen; // Account for DN data just added.
        U16ToBigEndianByteArray((u16)dnLen, pDnLen); // Store length.

        u8* pFailuresLen = data; // Record where we'll write length.
        data += 2; // Skip over length field to be filled in later.
        s32 failuresLen = iter->second.Serialise(data, dataMaxBytes - (data - dataStart));
        data += failuresLen; // Account for attribute data just added.
        U16ToBigEndianByteArray((u16)failuresLen, pFailuresLen); // Store length.
    }

    RETURN(data - dataStart);
}

bool MibValidateAttributesCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    const u8* const dataStart = data;

    m_failures.clear();
    while(data < (dataStart + dataLen))
    {
        MibDN mibDn;
        MibAttrValidationFailures failures;

        // Get DN len and deserialise DN.
        u16 dnLen;
        DeSerialiseIt(dnLen, data);
        mibDn.DeSerialise(data, dnLen);
        data += dnLen;

        // Get attributes length and deserialise.
        u16 failuresLen;
        DeSerialiseIt(failuresLen, data);
        failures.DeSerialise(data, failuresLen);
        data += failuresLen;

        m_failures[mibDn] = failures;
    }

    RSYS_ASSERT(data == (dataStart + dataLen));

    RETURN(true);
}

std::string MibValidateAttributesCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    for(MibAttrValidationFailuresByDn::const_iterator iter = m_failures.begin();
        iter != m_failures.end();
        ++iter)
    {
        stream << "[" << iter->first.ToString() << ": "
               << iter->second.ToString() << "]";
    }

    RETURN(stream.str());
}

void MibValidateAttributesCnf::AddFailures(const MibDN& dn, const MibAttrValidationFailures& failures)
{
    ENTER();

    RSYS_ASSERT_PRINTF(m_failures.find(dn) == m_failures.end(), "Trying to add DN=%s but already exists", dn.ToString().c_str());

    m_failures[dn] = failures;

    EXIT();
}
