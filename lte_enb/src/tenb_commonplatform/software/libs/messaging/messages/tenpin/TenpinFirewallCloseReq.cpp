///////////////////////////////////////////////////////////////////////////////
//
// TenpinFirewallCloseReq.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
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

#include "TenpinFirewallCloseReq.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

s32 TenpinFirewallCloseReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u8 * start = data;

    // serialised as token, count, sequence of values (sequence length count)

    u32 count = m_handles.size();

    if ((4 * (2 + count)) <= dataMaxBytes)
    {
        SerialiseIt(m_token, data);
        SerialiseIt(count, data);

        for (FirewallHandles::const_iterator it = m_handles.begin(); it != m_handles.end(); it++)
        {
            SerialiseIt(*it, data);
        }
    }

    RETURN(data - start);
}

bool TenpinFirewallCloseReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    bool decode = (8 <= dataLen);

    if (decode)
    {
        u32 count;

        DeSerialiseIt(m_token, data);
        DeSerialiseIt(count, data);

        decode = ((4 * (2 + count)) <= dataLen);

        if (decode)
        {
            for (u32 i = 0; i < count; i++)
            {
                u32 handle;

                DeSerialiseIt(handle, data);

                m_handles.push_back(handle);
            }
        }
    }

    RETURN(decode);
}

std::string TenpinFirewallCloseReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "TenpinFirewallCloseReq: token=" << m_token << " ";

    for (FirewallHandles::const_iterator it = m_handles.begin(); it != m_handles.end(); it++)
    {
        stream << *it << ",";
    }

    RETURN(stream.str());
}
