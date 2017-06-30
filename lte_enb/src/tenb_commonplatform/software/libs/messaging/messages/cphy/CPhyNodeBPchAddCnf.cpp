///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBPchAddCnf.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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
#include "CPhyNodeBPchAddCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBPchAddCnf::CPhyNodeBPchAddCnf(const CphyNodeBPchAddCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBPchAddCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBPchAddCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBPchAddCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBPchAddCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBPchAddCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBPchAddCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBPchAddCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBPchAddCnf " << endl;
    stream << "{ status   = " << CphyL1StatusToString(m_Struct.status) << endl;
    if(m_Struct.sfnOffset == CPHY_NODEB_PCH_SET_FILL)
    {
        stream << "  sfnOffset=CPHY_NODEB_PCH_SET_FILL" << endl;
    }
    else
    {
        stream << "  sfnOffset=" << m_Struct.sfnOffset << endl;
    }
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBPchAddCnf::ToBriefString() const
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

l1status_t CPhyNodeBPchAddCnf::GetStatus() const
{
    return m_Struct.status;
}

extern "C"
{


s32 CphyNodeBPchAddCnf_Serialise(const CphyNodeBPchAddCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBPchAddCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBPchAddCnf));
    return sizeof(CphyNodeBPchAddCnf);
}


s32 CphyNodeBPchAddCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBPchAddCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBPchAddCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBPchAddCnf));

    return sizeof(CphyNodeBPchAddCnf);
}

}

// END OF FILE
