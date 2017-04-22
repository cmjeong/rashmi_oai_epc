///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmFindCellCnf.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemGsmFindCellCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemGsmFindCellCnf::CPhyRemGsmFindCellCnf(const CphyRemGsmFindCellCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemGsmFindCellCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemGsmFindCellCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemGsmFindCellCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemGsmFindCellCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemGsmFindCellCnf::GetStruct(CphyMessageData *const msg)
{
    msg->remGsmFindCellCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemGsmFindCellCnf::ToString() const
{
    u8 i;
    ostringstream stream;

    stream << "CPhyRemGsmFindCellCnf " << endl;
    stream << "{ status=" <<         CphyL1StatusToString(m_Struct.status) << endl;
    stream << "  nbrCount=" <<         (u16)m_Struct.nbrCount << endl;
    for(i = 0; i < m_Struct.nbrCount; i++)
    {
       stream << " Nbr Details :"  << (u16)(i + 1) << endl;
       stream << "  arfcn="        <<   (u16)m_Struct.nbrList[i].arfcn << endl;
       stream << "  bsic="         <<   (u16)m_Struct.nbrList[i].bsic << endl;
       stream << "  freqOffsetHz=" <<   (s16)m_Struct.nbrList[i].freqOffsetHz << "Hz" << endl;
       stream << "  dacValue="     <<   (u16)m_Struct.nbrList[i].dacValue << endl;
       stream << "  rssi="         <<   (s16)m_Struct.nbrList[i].rssi << endl;
       stream << "  lac[0]="       <<   (u16) m_Struct.nbrList[i].lac[0] << endl;
       stream << "  lac[1]="       <<   (u16) m_Struct.nbrList[i].lac[1] << endl;
       stream << "  rac="          <<   (u16) m_Struct.nbrList[i].rac << endl;
       stream << "###########################"   << endl;
    }
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemGsmFindCellCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" << CphyL1StatusToString(m_Struct.status)
           << " arfcn=" << (u16)m_Struct.nbrList[0].arfcn;
    if(m_Struct.status == L1_SOK)
        stream << " bsic=" <<  (u16)m_Struct.nbrList[0].bsic;

    return(stream.str());
}

extern "C"
{


s32 CphyRemGsmFindCellCnf_Serialise(const CphyRemGsmFindCellCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmFindCellCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemGsmFindCellCnf));
    return sizeof(CphyRemGsmFindCellCnf);
}


s32 CphyRemGsmFindCellCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmFindCellCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmFindCellCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemGsmFindCellCnf));
    return sizeof(CphyRemGsmFindCellCnf);
}

}

// END OF FILE
