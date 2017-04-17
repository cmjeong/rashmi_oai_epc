///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCctrchRemoveCnf.cpp 7696 2008-09-10 10:29:53Z manderson $
//
// See header file for documentation.
//
// Copyright radisys Ltd
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

#include "CPhyNodeBCctrchRemoveCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBCctrchRemoveCnf::CPhyNodeBCctrchRemoveCnf ()
{
    bzero (&m_cctrchRemoveCnf, sizeof (CphyNodeBCctrchRemoveCnf));
}

CPhyNodeBCctrchRemoveCnf::CPhyNodeBCctrchRemoveCnf (uint8_t ueNumber, uint32_t instanceId)
{
    bzero (&m_cctrchRemoveCnf, sizeof (CphyNodeBCctrchRemoveCnf));
    m_cctrchRemoveCnf.ue = ueNumber;
    m_cctrchRemoveCnf.instanceId = instanceId;
}

CPhyNodeBCctrchRemoveCnf::CPhyNodeBCctrchRemoveCnf(const CphyNodeBCctrchRemoveCnf &cctrchRemoveCnf)
{
    memcpy (&m_cctrchRemoveCnf, &cctrchRemoveCnf, sizeof (CphyNodeBCctrchRemoveCnf));
}

s32 CPhyNodeBCctrchRemoveCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CPhyNodeBCctrchRemoveCnf_Serialise(&m_cctrchRemoveCnf, data, dataMaxBytes);
}

bool CPhyNodeBCctrchRemoveCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CPhyNodeBCctrchRemoveCnf_Deserialise(data, dataLen, &m_cctrchRemoveCnf) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBCctrchRemoveCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBCctrchRemoveCnf = &m_cctrchRemoveCnf;

    return GetSerialisationId();
}

string CPhyNodeBCctrchRemoveCnf::ToString() const
{
    ostringstream stream;

    stream << "{ CPhyNodeBCctrchRemoveCnf" << endl;
    stream << "  Ue Number   = " << (u32) m_cctrchRemoveCnf.ue << endl;
    stream << "  Instance Id = " << m_cctrchRemoveCnf.instanceId << endl;
    stream << " }" << endl;

    return(stream.str());
}

string CPhyNodeBCctrchRemoveCnf::ToBriefString() const
{
    ostringstream stream;
    stream << "ue=" << (u32) m_cctrchRemoveCnf.ue
           << " instance=" << m_cctrchRemoveCnf.instanceId;
    return(stream.str());
}

extern "C"
{


s32 CPhyNodeBCctrchRemoveCnf_Serialise(const CphyNodeBCctrchRemoveCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCctrchRemoveCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBCctrchRemoveCnf));
    return sizeof(CphyNodeBCctrchRemoveCnf);
}


s32 CPhyNodeBCctrchRemoveCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBCctrchRemoveCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCctrchRemoveCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBCctrchRemoveCnf));
    return sizeof(CphyNodeBCctrchRemoveCnf);
}

}

// END OF FILE
