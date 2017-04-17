///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBOutOfSyncInd.cpp 28310 2010-07-16 15:27:29Z mmcternan $
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

#include "CPhyNodeBOutOfSyncInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBOutOfSyncInd::CPhyNodeBOutOfSyncInd(const CphyNodeBOutOfSyncInd *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBOutOfSyncInd::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBOutOfSyncInd_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBOutOfSyncInd::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBOutOfSyncInd_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBOutOfSyncInd::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBOutOfSyncInd = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBOutOfSyncInd::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBOutOfSyncInd " << endl;
    stream << "{  ue=" << (u16)m_Struct.ue << endl;
    stream << "}" << endl;

    return(stream.str());
}


string CPhyNodeBOutOfSyncInd::ToBriefString() const
{
    ostringstream stream;

    stream << "ue=" << (u16)m_Struct.ue;

    return(stream.str());
}

extern "C"
{


s32 CphyNodeBOutOfSyncInd_Serialise(const CphyNodeBOutOfSyncInd *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBOutOfSyncInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBOutOfSyncInd));
    return sizeof(CphyNodeBOutOfSyncInd);
}


s32 CphyNodeBOutOfSyncInd_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBOutOfSyncInd *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBOutOfSyncInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBOutOfSyncInd));

    return sizeof(CphyNodeBOutOfSyncInd);
}

}

// END OF FILE
