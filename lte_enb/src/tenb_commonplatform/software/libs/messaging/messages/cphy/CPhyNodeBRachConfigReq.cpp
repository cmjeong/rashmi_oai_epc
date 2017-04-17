///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBRachConfigReq.cpp 19065 2009-10-21 14:41:58Z nmahasinghe $
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
#include <iomanip>
#include <string.h> // for memcpy

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNodeBRachConfigReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBRachConfigReq::CPhyNodeBRachConfigReq(const CphyNodeBRachConfigReq *cStruct)
{
    m_Struct = *cStruct;
}

s32 CPhyNodeBRachConfigReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBRachConfigReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBRachConfigReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBRachConfigReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBRachConfigReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBRachConfigReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBRachConfigReq::ToString() const
{
    ostringstream stream;

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CphyNodeBRachConfigReq" << endl;
    stream << "{ scramblingCode=" << m_Struct.scramblingCode << endl;
    stream << "  signature={";
    for(int t = 0; t < NUM_CPHY_MAX_PRACH_SIGNATURES; t++)
    {
        stream << (uint32_t) m_Struct.signature[t];
        if(t != NUM_CPHY_MAX_PRACH_SIGNATURES - 1)
        {
            stream << ", ";
        }
    }
    stream << "}" << endl;
    stream << "  pdSnrThreshold=" << (uint32_t) m_Struct.pdSnrThreshold << endl;
    stream << "}" << endl;

    return(stream.str());
}

extern "C"
{


s32 CphyNodeBRachConfigReq_Serialise(const CphyNodeBRachConfigReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBRachConfigReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBRachConfigReq));
    return sizeof(CphyNodeBRachConfigReq);
}


s32 CphyNodeBRachConfigReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBRachConfigReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBRachConfigReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBRachConfigReq));

    return sizeof(CphyNodeBRachConfigReq);
}

}

// END OF FILE
