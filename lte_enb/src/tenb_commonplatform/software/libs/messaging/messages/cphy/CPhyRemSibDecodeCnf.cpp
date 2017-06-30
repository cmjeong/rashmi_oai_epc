///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemSibDecodeCnf.cpp 15300 2009-06-29 11:38:31Z dallwright $
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

#include "CPhyRemSibDecodeCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemSibDecodeCnf::CPhyRemSibDecodeCnf(const CphyRemSibDecodeCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemSibDecodeCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemSibDecodeCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemSibDecodeCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemSibDecodeCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemSibDecodeCnf::GetStruct(CphyMessageData *const msg)
{
    msg->remSibDecodeCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemSibDecodeCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemSibDecodeCnf " << endl;
    stream << "{ status= " << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "  psc= " << (u16)m_Struct.psc[0] << endl;
    stream << "}" << endl;

    return(stream.str());
}


extern "C"
{


s32 CphyRemSibDecodeCnf_Serialise(const CphyRemSibDecodeCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemSibDecodeCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemSibDecodeCnf));
    return sizeof(CphyRemSibDecodeCnf);
}


s32 CphyRemSibDecodeCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemSibDecodeCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemSibDecodeCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemSibDecodeCnf));
    return sizeof(CphyRemSibDecodeCnf);
}

}

// END OF FILE
