///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmStopBcchDecodeCnf.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemGsmStopBcchDecodeCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemGsmStopBcchDecodeCnf::CPhyRemGsmStopBcchDecodeCnf(const CphyRemGsmStopBcchDecodeCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemGsmStopBcchDecodeCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemGsmStopBcchDecodeCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemGsmStopBcchDecodeCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemGsmStopBcchDecodeCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemGsmStopBcchDecodeCnf::GetStruct(CphyMessageData *const msg)
{
    msg->remGsmStopBcchDecodeCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemGsmStopBcchDecodeCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemGsmStopBcchDecodeCnf {" << endl;
    stream << "  status=" << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemGsmStopBcchDecodeCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" << CphyL1StatusToString(m_Struct.status);

    return(stream.str());
}

extern "C"
{


s32 CphyRemGsmStopBcchDecodeCnf_Serialise(const CphyRemGsmStopBcchDecodeCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmStopBcchDecodeCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemGsmStopBcchDecodeCnf));
    return sizeof(CphyRemGsmStopBcchDecodeCnf);
}


s32 CphyRemGsmStopBcchDecodeCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmStopBcchDecodeCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmStopBcchDecodeCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemGsmStopBcchDecodeCnf));
    return sizeof(CphyRemGsmStopBcchDecodeCnf);
}

}

// END OF FILE
