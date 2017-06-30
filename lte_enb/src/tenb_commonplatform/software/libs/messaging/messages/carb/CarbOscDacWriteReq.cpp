///////////////////////////////////////////////////////////////////////////////
//
// $Id: CarbOscDacWriteReq.cpp 28331 2010-07-17 15:25:20Z mmcternan $
//
// See header file for documentation.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CarbOscDacWriteReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////


CarbOscDacWriteReq::CarbOscDacWriteReq(u16 dacValue) :
    m_dacValue(dacValue)
{
}


s32 CarbOscDacWriteReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    if (dataMaxBytes < 2)
        return -1;

    U16ToBigEndianByteArray(m_dacValue, &data[0]);

    return 2;
}

bool CarbOscDacWriteReq::DeSerialise(const u8* data, u32 dataLen)
{
    if (dataLen >= 2)
    {
        m_dacValue = BigEndianByteArrayToU16(&data[0]);

        return true;
    }

    return false;
}


string CarbOscDacWriteReq::ToString() const
{
    ostringstream stream;

    stream << "CarbOscDacWriteReq " << endl;
    stream << "{ dacValue   = " << m_dacValue << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CarbOscDacWriteReq::ToBriefString() const
{
    ostringstream stream;

    stream << "dacValue=" << m_dacValue;;

    return(stream.str());
}

// END OF FILE
