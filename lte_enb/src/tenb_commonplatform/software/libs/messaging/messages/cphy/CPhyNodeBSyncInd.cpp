///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBSyncInd.cpp 28310 2010-07-16 15:27:29Z mmcternan $
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

#include "CPhyNodeBSyncInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBSyncInd::CPhyNodeBSyncInd(const CphyNodeBSyncInd *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBSyncInd::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBSyncInd_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBSyncInd::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBSyncInd_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBSyncInd::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBSyncInd = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBSyncInd::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBSyncInd " << endl;
    stream << "{  ue=" << (u16)m_Struct.ue << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBSyncInd::ToBriefString() const
{
    ostringstream stream;

    stream << "ue=" << (u16)m_Struct.ue;

    return(stream.str());
}
extern "C"
{


s32 CphyNodeBSyncInd_Serialise(const CphyNodeBSyncInd *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBSyncInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBSyncInd));
    return sizeof(CphyNodeBSyncInd);
}


s32 CphyNodeBSyncInd_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBSyncInd *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBSyncInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBSyncInd));

    return sizeof(CphyNodeBSyncInd);
}

}

// END OF FILE
