///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyHwConfigReq.cpp 28310 2010-07-16 15:27:29Z mmcternan $
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

#include "CPhyHwConfigReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyHwConfigReq::CPhyHwConfigReq(const CphyHwConfigReq *msg)
{
    m_Struct = *msg;
}

s32 CPhyHwConfigReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyHwConfigReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyHwConfigReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyHwConfigReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyHwConfigReq::GetStruct(CphyMessageData *const msg)
{
    msg->hwConfigReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyHwConfigReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyHwConfigReq " << endl;
    stream << "{ hwType= " << (u16)m_Struct.hwType << endl;
    stream << "  hwRevision=" << (u16)m_Struct.hwRevision << endl;
    stream << "  hwModLevel=" << (u16)m_Struct.hwModLevel << endl;
    stream << "  afcDacValue=" << m_Struct.afcDacValue << endl;
    stream << "  afcDacSlopePpt=" << m_Struct.afcDacSlopePpt << endl;
    stream << "  txPowerAmpGaindB=" << m_Struct.txPowerAmpGaindB << endl;
    stream << "  allowDefaultCal=" << (m_Struct.allowDefaultCal ? "yes" : "no") << endl;
    stream << "}" << endl;

    return(stream.str());
}


string CPhyHwConfigReq::ToBriefString() const
{
    ostringstream stream;

    stream << "hw=" << (u16)m_Struct.hwType << "/"
                    << (u16)m_Struct.hwRevision << "/"
                    << (u16)m_Struct.hwModLevel;

    return(stream.str());
}

extern "C"
{


s32 CphyHwConfigReq_Serialise(const CphyHwConfigReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyHwConfigReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyHwConfigReq));
    return sizeof(CphyHwConfigReq);
}


s32 CphyHwConfigReq_Deserialise(const u8 *buffer, u32 maxLen, CphyHwConfigReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyHwConfigReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyHwConfigReq));

    return sizeof(CphyHwConfigReq);
}

}

// END OF FILE
