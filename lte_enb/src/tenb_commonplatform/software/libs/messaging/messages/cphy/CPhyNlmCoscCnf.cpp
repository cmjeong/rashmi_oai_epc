///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNlmCoscCnf.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNlmCoscCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNlmCoscCnf::CPhyNlmCoscCnf(const CphyNlmCoscCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyNlmCoscCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNlmCoscCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNlmCoscCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNlmCoscCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNlmCoscCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nlmCoscCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyNlmCoscCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyNlmCoscCnf " << endl;
    stream << "{ status=" <<         CphyL1StatusToString(m_Struct.status) << endl;
    stream << "  arfcn=" <<          (u16)m_Struct.arfcn << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNlmCoscCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" << CphyL1StatusToString(m_Struct.status)
           << " arfcn=" << (u16)m_Struct.arfcn;

    return(stream.str());
}

extern "C"
{


s32 CphyNlmCoscCnf_Serialise(const CphyNlmCoscCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNlmCoscCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNlmCoscCnf));
    return sizeof(CphyNlmCoscCnf);
}


s32 CphyNlmCoscCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNlmCoscCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNlmCoscCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNlmCoscCnf));
    return sizeof(CphyNlmCoscCnf);
}

}

// END OF FILE
