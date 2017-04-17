///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBConfigCnf.cpp 28310 2010-07-16 15:27:29Z mmcternan $
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

#include "CPhyNodeBConfigCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBConfigCnf::CPhyNodeBConfigCnf(const CphyNodeBConfigCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBConfigCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBConfigCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBConfigCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBConfigCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBConfigCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBConfigCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBConfigCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBConfigCnf " << endl;
    stream << "{ status= " << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBConfigCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status= " << CphyL1StatusToString(m_Struct.status);

    return(stream.str());
}

l1status_t CPhyNodeBConfigCnf::GetStatus() const
{
    return m_Struct.status;
}

extern "C"
{

s32 CphyNodeBConfigCnf_Serialise(const CphyNodeBConfigCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBConfigCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBConfigCnf));
    return sizeof(CphyNodeBConfigCnf);
}


s32 CphyNodeBConfigCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBConfigCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBConfigCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBConfigCnf));

    return sizeof(CphyNodeBConfigCnf);
}

}

// END OF FILE
