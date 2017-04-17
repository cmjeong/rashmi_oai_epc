///////////////////////////////////////////////////////////////////////////////
//
// $Id: CphyNodeBTxDpchEnableCnf.cpp 5567 2008-05-30 11:13:47Z mm $
//
// See header file for documentation.
//
// Copyright � Radisys Ltd
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

#include "CPhyNodeBTxDpchEnableCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBTxDpchEnableCnf::CPhyNodeBTxDpchEnableCnf(const CphyNodeBTxDpchEnableCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBTxDpchEnableCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBTxDpchEnableCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBTxDpchEnableCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBTxDpchEnableCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBTxDpchEnableCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBTxDpchEnableCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBTxDpchEnableCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBTxDpchEnableCnf " << endl;
    stream << "{ status= " << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "}" << endl;

    return(stream.str());
}

l1status_t CPhyNodeBTxDpchEnableCnf::GetStatus() const
{
    return m_Struct.status;
}

extern "C"
{


s32 CphyNodeBTxDpchEnableCnf_Serialise(const CphyNodeBTxDpchEnableCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBTxDpchEnableCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBTxDpchEnableCnf));
    return sizeof(CphyNodeBTxDpchEnableCnf);
}


s32 CphyNodeBTxDpchEnableCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBTxDpchEnableCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBTxDpchEnableCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBTxDpchEnableCnf));

    return sizeof(CphyNodeBTxDpchEnableCnf);
}

}

// END OF FILE
