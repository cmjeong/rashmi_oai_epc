///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmBcchDecodeInd.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemGsmBcchDecodeInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemGsmBcchDecodeInd::CPhyRemGsmBcchDecodeInd(const CphyRemGsmBcchDecodeInd *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemGsmBcchDecodeInd::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemGsmBcchDecodeInd_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemGsmBcchDecodeInd::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemGsmBcchDecodeInd_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemGsmBcchDecodeInd::GetStruct(CphyMessageData *const msg)
{
    msg->remGsmBcchDecodeInd = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemGsmBcchDecodeInd::ToString() const
{
    ostringstream stream;

    u16 t, blk;

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CPhyRemGsmBcchDecodeInd " << endl;
    stream << "{ status=" <<        CphyL1StatusToString(m_Struct.status) << endl;
    stream << "  arfcn=" <<         (u16)m_Struct.arfcn << endl;
    stream << "  bsic=" <<          (u16)m_Struct.bsic << endl;
    stream << "  numBlk=" <<        (u32)(m_Struct.numBlk) << endl;

    for(blk = 0; blk < m_Struct.numBlk; blk++)
    {
        stream << "  transport block (" << (u32)(m_Struct.numBlk) <<") = {" << endl;
        stream << "  crcPass=" <<       (u16)(m_Struct.bchInfo[blk].crcPass) << endl;        
        stream << "  data = { ";
        stream << std::hex;
        for(t = 0; t < BCCH_GSM_BLOCK_SIZE_BYTES; t++)
        {
            if(t != 0)
            {
                stream << ", ";
                if((t % 8) == 0)
                {
                    stream << endl << "           ";
                }
            }
            stream << std::setw(2) << std::setfill('0') << (u16)(m_Struct.bchInfo[blk].data[t]);
        }
        stream << "}" << endl;    
        stream << "}end_tr_blk" << endl << endl;
    }
    
    stream << "}" << endl;

    return(stream.str());
}



string CPhyRemGsmBcchDecodeInd::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" <<  CphyL1StatusToString(m_Struct.status)
           << " arfcn=" << m_Struct.arfcn;
    if(m_Struct.status == L1_SOK)
    {
        stream << " bsic=" << (u16)(m_Struct.bsic);
    }

    return(stream.str());
}

extern "C"
{


s32 CphyRemGsmBcchDecodeInd_Serialise(const CphyRemGsmBcchDecodeInd *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmBcchDecodeInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemGsmBcchDecodeInd));
    return sizeof(CphyRemGsmBcchDecodeInd);
}


s32 CphyRemGsmBcchDecodeInd_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmBcchDecodeInd *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmBcchDecodeInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemGsmBcchDecodeInd));
    return sizeof(CphyRemGsmBcchDecodeInd);
}

}

// END OF FILE
