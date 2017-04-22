///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNlmCoscReq.cpp 28519 2012-03-21 14:39:46Z mmcternan $
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

#include "CPhyNlmCoscReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNlmCoscReq::CPhyNlmCoscReq(const CphyNlmCoscReq *msg)
{
    m_Struct = *msg;
}

s32 CPhyNlmCoscReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNlmCoscReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNlmCoscReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNlmCoscReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

CPhyNlmCoscReq::CPhyNlmCoscReq(uint8_t nmbArfcns, uarfcn_t arfcn[MAX_GSM_FREQS_FOR_NLM_COSC])
{
    u8 i = 0;

    memset(&m_Struct, 0, sizeof(m_Struct));

    m_Struct.nmbArfcns   = nmbArfcns;

    if(nmbArfcns > sizeof(m_Struct.arfcn))
    {
        nmbArfcns = sizeof(m_Struct.arfcn);
    }
    
    if(nmbArfcns <= MAX_GSM_FREQS_FOR_NLM_COSC)
    {
       for(i =0; i < nmbArfcns; i++)
       {
          m_Struct.arfcn[i] = arfcn[i];
       }
    }
}

CPhyNlmCoscReq::CPhyNlmCoscReq()
{
   memset(&m_Struct, 0, sizeof(m_Struct));
}

u32 CPhyNlmCoscReq::GetStruct(CphyMessageData *const msg)
{
    msg->nlmCoscReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNlmCoscReq::ToString() const
{
    u8 i = 0;
    ostringstream stream;

    stream << "CPhyNlmCoscReq " << endl;
    stream << "{ nmbArfcns = " << (u16)m_Struct.nmbArfcns << endl;

    for(i = 0; i < m_Struct.nmbArfcns; i++)
    {
       stream << "{ arfcn = " << (u16)m_Struct.arfcn[i] << endl;
    }

    stream << "}" << endl;

    return(stream.str());
}

string CPhyNlmCoscReq::ToBriefString() const
{
    ostringstream stream;

    stream << "nmbArfcns = " << (u16)m_Struct.nmbArfcns;

    return(stream.str());
}

extern "C"
{


s32 CphyNlmCoscReq_Serialise(const CphyNlmCoscReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNlmCoscReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNlmCoscReq));
    return sizeof(CphyNlmCoscReq);
}


s32 CphyNlmCoscReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNlmCoscReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNlmCoscReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNlmCoscReq));
    return sizeof(CphyNlmCoscReq);
}

}

// END OF FILE
