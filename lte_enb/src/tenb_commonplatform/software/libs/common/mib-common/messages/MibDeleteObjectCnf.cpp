///////////////////////////////////////////////////////////////////////////////
//
// MibDeleteObjectCnf.cpp
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

#include "MibDeleteObjectCnf.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////



s32 MibDeleteObjectCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();
    s32 serialiseResult;

    const u8 * const dataStart = data;

    RSYS_ASSERT(dataMaxBytes >= 4);
    SerialiseIt( u32(m_result), data);

    serialiseResult = MibDnMessage::Serialise( data , dataMaxBytes - (data - dataStart) );
    RSYS_ASSERT(serialiseResult >= 0);

    data += serialiseResult;

    RETURN(data - dataStart);
}

bool MibDeleteObjectCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    u32 temp;

    bool deserialiedOk = (dataLen >= 4);

    if(deserialiedOk)
    {
        DeSerialiseIt( temp, data);
        dataLen -= 4;
        m_result = MibObjectDeleteResult(temp);

        deserialiedOk = MibDnMessage::DeSerialise(data, dataLen);
    }

    RETURN(deserialiedOk);
}

std::string MibDeleteObjectCnf::ToString() const
{
    ENTER();

    ostringstream str;

    str << "Result=" << MibObjectDeleteResultToString(m_result) << ", "
        << MibDnMessage::ToString();

    RETURN(str.str());
}

MibObjectDeleteResult MibDeleteObjectCnf::GetDeleteResult() const
{
    ENTER();

    RETURN(m_result);
}

