///////////////////////////////////////////////////////////////////////////////
//
// KpiReadCnf.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "KpiReadCnf.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

KpiReadCnf::KpiReadCnf() :
    m_kpiMeasurementSet(0)
{
    ENTER();
    EXIT();
}

KpiReadCnf::KpiReadCnf(u8 kpiMeasurementSet, const KpiGroup& kpiGroup) :
    m_kpiMeasurementSet(kpiMeasurementSet),
    m_kpiGroup(kpiGroup)
{
    ENTER();
    EXIT();
}

s32 KpiReadCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Serialise all the members.
    u8* serialisedData = data;

    // The KpiGroup knows how to serialise itself.
    serialisedData += m_kpiGroup.Serialise(data, dataMaxBytes);

    // Check we've still got room for extra members.
    RSYS_ASSERT(dataMaxBytes >= (u32)((serialisedData - data) + 1 /* measurement set */));

    SerialiseIt(m_kpiMeasurementSet, serialisedData);

    RETURN(serialisedData - data);
}

bool KpiReadCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    RSYS_ASSERT(dataLen > 0);

    // Hmmm, DeSerialise doesn't tell us how much data it consumed...
    // Perhaps it should.  In the meantime, we know the measurement set
    // is the last byte in the data.

    bool success = m_kpiGroup.DeSerialise(data, dataLen-1); // -1 to ignore the kpiMeasurementSet byte.
    RSYS_ASSERT(success); // In this case, we are not reading from flash so deserialise should always succeed.

    m_kpiMeasurementSet = data[dataLen-1];

    RETURN(true);
}

std::string KpiReadCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "set=" << (u32)m_kpiMeasurementSet << ": " << m_kpiGroup.ToString();

    RETURN(stream.str());
}
