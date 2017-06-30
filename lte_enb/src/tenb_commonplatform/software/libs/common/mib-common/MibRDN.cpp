///////////////////////////////////////////////////////////////////////////////
//
// MibRDN.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <sstream>

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibRDN.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MibRDN::MibRDN(MibObjectClass mibObjectClass,
               u32            mibObjectInstance) :
    m_mibObjectClass(mibObjectClass),
    m_mibObjectInstance(mibObjectInstance)
{
    ENTER();

    EXIT();
}

MibRDN::~MibRDN()
{
    ENTER();

    EXIT();
}

s32 MibRDN::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= SERIALISATION_LENGTH);

    u8* serialisedData = data;

    SerialiseIt((u32)m_mibObjectClass, serialisedData);
    SerialiseIt(m_mibObjectInstance, serialisedData);

    RETURN(serialisedData - data);
}

bool MibRDN::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataLen == SERIALISATION_LENGTH);

    u32 objectClassValue;
    DeSerialiseIt(objectClassValue, data);
    m_mibObjectClass = (MibObjectClass)objectClassValue;

    DeSerialiseIt(m_mibObjectInstance, data);

    RETURN(true);
}

bool MibRDN::operator==(const MibRDN& rhs) const
{
    ENTER();

    if((m_mibObjectClass != rhs.m_mibObjectClass) ||
       (m_mibObjectInstance != rhs.m_mibObjectInstance))
    {
        RETURN(false);
    }

    RETURN(true);
}

bool MibRDN::operator!=(const MibRDN& rhs) const
{
    ENTER();
    RETURN(!(*this == rhs));
}

bool MibRDN::operator<(const MibRDN &rhs) const
{
    ENTER();

    if(m_mibObjectClass == rhs.m_mibObjectClass)
    {
        RETURN(m_mibObjectInstance < rhs.m_mibObjectInstance)
    }

    RETURN(m_mibObjectClass < rhs.m_mibObjectClass);
}

bool MibRDN::operator>(const MibRDN &rhs) const
{
    ENTER();
    RETURN(!(*this < rhs));
}

std::string MibRDN::ToString() const
{
    ENTER();

    ostringstream stream;

    const char * classAsString = MibObjectClassToString(m_mibObjectClass);
    RSYS_ASSERT(classAsString != NULL);
    RSYS_ASSERT(strlen(classAsString) > 17); // strlen("MIB_OBJECT_CLASS_");

    // Remove the prefix MIB_OBJECT_CLASS_
    stream << &classAsString[17];
    stream << '.' << m_mibObjectInstance;

    RETURN(stream.str());
}

std::ostream& operator<< (std::ostream& os, const MibRDN& s)
{
    os << s.ToString();
    return(os);
}

