///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmStopBcchDecodeReq.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemGsmStopBcchDecodeReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemGsmStopBcchDecodeReq::CPhyRemGsmStopBcchDecodeReq(const CphyRemGsmStopBcchDecodeReq *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemGsmStopBcchDecodeReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemGsmStopBcchDecodeReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemGsmStopBcchDecodeReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemGsmStopBcchDecodeReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemGsmStopBcchDecodeReq::GetStruct(CphyMessageData *const msg)
{
    msg->remGsmStopBcchDecodeReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemGsmStopBcchDecodeReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemGsmStopBcchDecodeReq {" << endl;
    stream << "  dummy=" << (u16)m_Struct.dummy << endl;
    stream << "}" << endl;

    return(stream.str());
}


extern "C"
{


s32 CphyRemGsmStopBcchDecodeReq_Serialise(const CphyRemGsmStopBcchDecodeReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmStopBcchDecodeReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemGsmStopBcchDecodeReq));
    return sizeof(CphyRemGsmStopBcchDecodeReq);
}


s32 CphyRemGsmStopBcchDecodeReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmStopBcchDecodeReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmStopBcchDecodeReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemGsmStopBcchDecodeReq));
    return sizeof(CphyRemGsmStopBcchDecodeReq);
}

}

// END OF FILE
