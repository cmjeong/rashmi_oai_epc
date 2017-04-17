///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBPchRemoveCnf.cpp 28647 2010-07-26 08:55:18Z mmcternan $
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

#include "CPhyNodeBPchAddReq.h"
#include "CPhyNodeBPchRemoveCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBPchRemoveCnf::CPhyNodeBPchRemoveCnf(const CphyNodeBPchRemoveCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBPchRemoveCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBPchRemoveCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBPchRemoveCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBPchRemoveCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBPchRemoveCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBPchRemoveCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBPchRemoveCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBPchRemoveCnf " << endl;
    stream << "{ status   = " << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "  sfnOffset= " << m_Struct.sfnOffset << endl;
    stream << "}" << endl;

    return(stream.str());
}


string CPhyNodeBPchRemoveCnf::ToBriefString() const
{
    ostringstream stream;

    if(m_Struct.sfnOffset == CPHY_NODEB_PCH_SET_FILL)
    {
        stream << "sfnOffset=FILL";
    }
    else
    {
        stream << "sfnOffset=" << m_Struct.sfnOffset;
    }

    stream << " status=" << CphyL1StatusToString(m_Struct.status);

    return(stream.str());
}



l1status_t CPhyNodeBPchRemoveCnf::GetStatus() const
{
    return m_Struct.status;
}

extern "C"
{


s32 CphyNodeBPchRemoveCnf_Serialise(const CphyNodeBPchRemoveCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBPchRemoveCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBPchRemoveCnf));
    return sizeof(CphyNodeBPchRemoveCnf);
}


s32 CphyNodeBPchRemoveCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBPchRemoveCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBPchRemoveCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBPchRemoveCnf));

    return sizeof(CphyNodeBPchRemoveCnf);
}

}

// END OF FILE
