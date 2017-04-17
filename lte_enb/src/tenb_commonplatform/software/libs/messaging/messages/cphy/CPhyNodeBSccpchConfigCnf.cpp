///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBSccpchConfigCnf.cpp 28310 2010-07-16 15:27:29Z mmcternan $
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
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNodeBSccpchConfigCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBSccpchConfigCnf::CPhyNodeBSccpchConfigCnf(const CphyNodeBSccpchConfigCnf *cStruct)
{
    m_Struct = *cStruct;
}

s32 CPhyNodeBSccpchConfigCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBSccpchConfigCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBSccpchConfigCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBSccpchConfigCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBSccpchConfigCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBSccpchConfigCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBSccpchConfigCnf::ToString() const
{
    ostringstream stream;

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CphyNodeBSccpchConfigCnf" << endl;
    stream << "{ status=" << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBSccpchConfigCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" << CphyL1StatusToString(m_Struct.status);

    return(stream.str());
}

extern "C"
{


s32 CphyNodeBSccpchConfigCnf_Serialise(const CphyNodeBSccpchConfigCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBSccpchConfigCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBSccpchConfigCnf));
    return sizeof(CphyNodeBSccpchConfigCnf);
}


s32 CphyNodeBSccpchConfigCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBSccpchConfigCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBSccpchConfigCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBSccpchConfigCnf));

    return sizeof(CphyNodeBSccpchConfigCnf);
}

}

// END OF FILE
