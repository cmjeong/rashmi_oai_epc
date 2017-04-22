///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBTxEnableCnf.cpp 28310 2010-07-16 15:27:29Z mmcternan $
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

#include "CPhyNodeBTxEnableCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBTxEnableCnf::CPhyNodeBTxEnableCnf(const CphyNodeBTxEnableCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBTxEnableCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBTxEnableCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBTxEnableCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBTxEnableCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBTxEnableCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBTxEnableCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBTxEnableCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBTxEnableCnf " << endl;
    stream << "{ status= " << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBTxEnableCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status= " << CphyL1StatusToString(m_Struct.status) << endl;

    return(stream.str());
}

l1status_t CPhyNodeBTxEnableCnf::GetStatus() const
{
    return m_Struct.status;
}

extern "C"
{


s32 CphyNodeBTxEnableCnf_Serialise(const CphyNodeBTxEnableCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBTxEnableCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBTxEnableCnf));
    return sizeof(CphyNodeBTxEnableCnf);
}


s32 CphyNodeBTxEnableCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBTxEnableCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBTxEnableCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBTxEnableCnf));

    return sizeof(CphyNodeBTxEnableCnf);
}

}

// END OF FILE
