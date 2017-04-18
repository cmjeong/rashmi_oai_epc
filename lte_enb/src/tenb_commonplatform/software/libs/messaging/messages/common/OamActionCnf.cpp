///////////////////////////////////////////////////////////////////////////////
//
// OamActionCnf
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

#include "OamActionCnf.h"

using namespace threeway;
using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////
s32 OamActionCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    if(dataMaxBytes >= 12)
    {
        U32ToBigEndianByteArray(m_entity, data);
        U32ToBigEndianByteArray(m_action, &data[4]);
        U32ToBigEndianByteArray(m_val, &data[8]);
        RETURN(12);
    }
    RETURN(-1);
}

bool OamActionCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen >= 12)
    {
        m_entity = (MessagingEntity)BigEndianByteArrayToU32(&data[0]);
        m_action = (OamAction)BigEndianByteArrayToU32(&data[4]);
        m_val = BigEndianByteArrayToU32(&data[8]);
        RETURN(true);
    }
    RETURN(false);
}

string OamActionCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "entity=" << MessagingEntityToString(m_entity) << "action=" << (u32)m_action;
    RETURN(stream.str());
}
