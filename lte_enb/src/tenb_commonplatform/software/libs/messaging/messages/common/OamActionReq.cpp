///////////////////////////////////////////////////////////////////////////////
//
// OamActionReq
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
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "OamActionReq.h"

using namespace threeway;
using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////
s32 OamActionReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    if(dataMaxBytes >= 8)
    {
        U32ToBigEndianByteArray(m_action, &data[0]);
        U32ToBigEndianByteArray(m_data, &data[4]);
        RETURN(8);
    }
    RETURN(-1);
}

bool OamActionReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen >= 8)
    {
        m_action = (OamAction)BigEndianByteArrayToU32(&data[0]);
        m_data   = (OamAction)BigEndianByteArrayToU32(&data[4]);
        RETURN(true);
    }
    RETURN(FALSE);
}

string OamActionReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "action=" << (u32)m_action << " data=" << m_data;
    RETURN(stream.str());
}
