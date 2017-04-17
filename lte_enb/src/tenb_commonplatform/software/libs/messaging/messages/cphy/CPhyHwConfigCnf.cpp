///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyHwConfigCnf.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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
#include <string.h> // for memcpy

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyHwConfigCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyHwConfigCnf::CPhyHwConfigCnf(const CphyHwConfigCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyHwConfigCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyHwConfigCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyHwConfigCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyHwConfigCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyHwConfigCnf::GetStruct(CphyMessageData *const msg)
{
    msg->hwConfigCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyHwConfigCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyHwConfigCnf " << endl;
    stream << "{ status= " << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyHwConfigCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" << CphyL1StatusToString(m_Struct.status);

    return(stream.str());
}

l1status_t CPhyHwConfigCnf::GetStatus() const
{
    return m_Struct.status;
}

extern "C"
{


s32 CphyHwConfigCnf_Serialise(const CphyHwConfigCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyHwConfigCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyHwConfigCnf));
    return sizeof(CphyHwConfigCnf);
}


s32 CphyHwConfigCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyHwConfigCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyHwConfigCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyHwConfigCnf));

    return sizeof(CphyHwConfigCnf);
}

}

// END OF FILE
