///////////////////////////////////////////////////////////////////////////////
//
// CPhyNodeBSibMessage.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <iomanip>
#include <system/SerialisationIds.h>
#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNodeBSibMessage.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBSibMessage::CPhyNodeBSibMessage() :
  m_sibNumber(0),
  m_sibLen(0),
  m_blockNum(0),
  m_sibRep(0),
  m_sibPos(0)
{
    memset(m_messageData, 0, sizeof(m_messageData));
}

//constructor to generate it from the raw SIB data
CPhyNodeBSibMessage::CPhyNodeBSibMessage(u32 sibNumber, u16 sibRep, u16 sibPos, u32 blockNum, const u8 *messageData, u32 sibLen) :
  m_sibNumber(sibNumber),
  m_sibLen(sibLen),
  m_blockNum(blockNum),
  m_sibRep(sibRep),
  m_sibPos(sibPos)
{
    RSYS_ASSERT(sibLen <= sizeof(m_messageData));

    // Test segmentation implementation limits in L1
    RSYS_ASSERT((blockNum == 0) ||
                (sibNumber == 5 && blockNum < 3) ||
                (sibNumber == 11 && blockNum < 16));

    memcpy(m_messageData, messageData, sibLen);
}

s32 CPhyNodeBSibMessage::Serialise(u8 *data, u32 dataMaxBytes) const
{
    // Preconditions.
    RSYS_ASSERT(m_sibLen <= sizeof(m_messageData));

    if (dataMaxBytes >= sizeof(m_messageData) + 7)
    {
        data[0] = m_sibNumber;
        data[1] = m_sibLen;
        data[2] = m_blockNum;
        data[3] = m_sibRep >> 8;
        data[4] = m_sibRep;
        data[5] = m_sibPos >> 8;
        data[6] = m_sibPos;
        memcpy(&data[7], m_messageData, m_sibLen);
        return m_sibLen + 7;
    }
    return -1;
}

bool CPhyNodeBSibMessage::DeSerialise(const u8* data, u32 dataLen)
{
    bool ok = false;

    /* Check it has enough bytes for the expected header */
    if(dataLen >= 7)
    {
        m_sibNumber = data[0];
        m_sibLen = data[1];
        m_blockNum = data[2];
        m_sibRep = (data[3] << 8) | data[4];
        m_sibPos = (data[5] << 8) | data[6];

        /* Check there are enough bytes in the message for the payload */
        if(m_sibLen <= sizeof(m_messageData) && dataLen >= (unsigned)(m_sibLen + 7))
        {
            memcpy(m_messageData, &data[7], m_sibLen);
            ok = true;
        }
    }

    return ok;
}

u32 CPhyNodeBSibMessage::GetSerialisationId() const
{
    return SERIALISATION_ID_CPHY_NODEB_SIB_MESSAGE;
}

string CPhyNodeBSibMessage::ToString() const
{
    ostringstream stream;
    u8            t;

    // Preconditions.
    RSYS_ASSERT(m_sibLen <= sizeof(m_messageData));

    // NOTE : If you modify the output of this function you will also have to
    //        modify the loggen perl script 'extract_sib_info.pl', which decodes sibs
    //        offline, as this script will be broken by any changes made here.

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CPhyNodeBSibMessage: sibNumber=" << (u16)m_sibNumber << ", sibRep=" << (u16)m_sibRep
           << ", sibPos=" << (u16)m_sibPos << ", blockNum=" << (u16)m_blockNum << endl;
    stream << "  data = { ";
    stream << std::hex;
    for(t = 0; t < m_sibLen; t++)
    {
        if(t != 0)
        {
            stream << ", ";
            if((t % 8) == 0)
            {
                stream << endl << "           ";
            }
        }
        stream << std::setw(2) << std::setfill('0') << (u16)(m_messageData[t]);
    }
    stream << " }" << endl;

    return(stream.str());
}

string CPhyNodeBSibMessage::ToBriefString() const
{
    ostringstream stream;
    stream << "num=" << (u16)m_sibNumber << ", rep=" << (u16)m_sibRep
           << ", pos=" << (u16)m_sibPos << ", block=" << (u16)m_blockNum;
    return(stream.str());
}
