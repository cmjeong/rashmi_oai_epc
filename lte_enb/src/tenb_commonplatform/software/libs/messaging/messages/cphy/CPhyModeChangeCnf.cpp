///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyModeChangeCnf.cpp 28310 2010-07-16 15:27:29Z mmcternan $
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

#include "CPhyModeChangeCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyModeChangeCnf::CPhyModeChangeCnf(const CphyModeChangeCnf *cStruct)
{
    m_Struct = *cStruct;
}

s32 CPhyModeChangeCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyModeChangeCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyModeChangeCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyModeChangeCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyModeChangeCnf::GetStruct(CphyMessageData *const msg)
{
    msg->modeChangeCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyModeChangeCnf::ToString() const
{
    ostringstream stream;

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CphyModeChangeCnf" << endl;
    stream << "{ mode=" << CphyL1ModeToString(m_Struct.mode) << " status=" << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyModeChangeCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "mode=" << CphyL1ModeToString(m_Struct.mode) << " status=" << CphyL1StatusToString(m_Struct.status);

    return(stream.str());
}

extern "C"
{


s32 CphyModeChangeCnf_Serialise(const CphyModeChangeCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyModeChangeCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyModeChangeCnf));
    return sizeof(CphyModeChangeCnf);
}


s32 CphyModeChangeCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyModeChangeCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyModeChangeCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyModeChangeCnf));

    return sizeof(CphyModeChangeCnf);
}

}

// END OF FILE
