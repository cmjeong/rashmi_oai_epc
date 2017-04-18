///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCctrchCnf.cpp 8631 2008-10-16 09:55:40Z manderson $
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

#include "CPhyNodeBCctrchCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBCctrchCnf::CPhyNodeBCctrchCnf()
{
    bzero (&m_l1Status, sizeof (CphyNodeBCctrchCnf));
}

CPhyNodeBCctrchCnf::CPhyNodeBCctrchCnf(l1status_t l1Status)
{
    bzero (&m_l1Status, sizeof (CphyNodeBCctrchCnf));
    m_l1Status.status = l1Status;
}

CPhyNodeBCctrchCnf::CPhyNodeBCctrchCnf(const CPhyNodeBCctrchCnf *msg)
{
    bzero (&m_l1Status, sizeof (CphyNodeBCctrchCnf));
    memcpy (&m_l1Status, msg, sizeof (CphyNodeBCctrchCnf));
}

s32 CPhyNodeBCctrchCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CPhyNodeBCctrchCnf_Serialise(&m_l1Status, data, dataMaxBytes);
}

bool CPhyNodeBCctrchCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CPhyNodeBCctrchCnf_Deserialise(data, dataLen, &m_l1Status) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBCctrchCnf::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBCctrchCnf = &m_l1Status;

    return GetSerialisationId();
}

string CPhyNodeBCctrchCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBCctrchCnf " << endl;
    stream << "{ status   = " << CphyL1StatusToString(m_l1Status.status) << endl;
    stream << "}" << endl;

    return(stream.str());
}


l1status_t CPhyNodeBCctrchCnf::GetStatus() const
{
    return m_l1Status.status;
}

extern "C"
{


s32 CPhyNodeBCctrchCnf_Serialise(const CphyNodeBCctrchCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCctrchCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBCctrchCnf));
    return sizeof(CphyNodeBCctrchCnf);
}


s32 CPhyNodeBCctrchCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBCctrchCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCctrchCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBCctrchCnf));

    return sizeof(CphyNodeBCctrchCnf);
}

}

// END OF FILE
