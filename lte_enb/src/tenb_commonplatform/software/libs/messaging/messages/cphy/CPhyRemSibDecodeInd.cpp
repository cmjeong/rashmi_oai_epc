///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemSibDecodeInd.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemSibDecodeInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemSibDecodeInd::CPhyRemSibDecodeInd(const CphyRemSibDecodeInd *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemSibDecodeInd::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemSibDecodeInd_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemSibDecodeInd::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemSibDecodeInd_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemSibDecodeInd::GetStruct(CphyMessageData *const msg)
{
    msg->remSibDecodeInd = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemSibDecodeInd::ToString() const
{
    ostringstream stream;
    u8            t, blk;

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CPhyRemSibDecodeInd " << endl;
    stream << "{ status= " << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "  psc= " << (u16)m_Struct.psc << endl;

    //stream << "  ecn0= " << (m_Struct.ecn0 / 8.0f) << endl;
    //stream << "  rscp= " << (m_Struct.rscp / 8.0f) << endl;
    stream << "  numBlk=" << (u32)(m_Struct.numBlk) << endl;

    for(blk = 0; blk < m_Struct.numBlk; blk++)
    {
        stream << "  transport block (" << (u32)(m_Struct.numBlk) <<") = {" << endl;
        stream << "  crcPass=" <<       (u16)(m_Struct.bchInfo[blk].crcPass) << endl;        

        stream << "  data = { ";
        stream << std::hex;
        for(t = 0; t < BCH_TRCH_BLOCK_SIZE_BYTES; t++)
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
        stream << " }" << endl;
        stream << "}end_tr_blk" << endl << endl;        
    }
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemSibDecodeInd::ToBriefString() const
{
    ostringstream stream;

    stream << "status= " << CphyL1StatusToString(m_Struct.status)
           << "psc= " << (u16)m_Struct.psc
           << "numBlk =" << (u16)m_Struct.numBlk << endl;

    return(stream.str());
}

extern "C"
{


s32 CphyRemSibDecodeInd_Serialise(const CphyRemSibDecodeInd *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemSibDecodeInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemSibDecodeInd));
    return sizeof(CphyRemSibDecodeInd);
}


s32 CphyRemSibDecodeInd_Deserialise(const u8 *buffer, u32 maxLen, CphyRemSibDecodeInd *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemSibDecodeInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemSibDecodeInd));
    return sizeof(CphyRemSibDecodeInd);
}

}

// END OF FILE
