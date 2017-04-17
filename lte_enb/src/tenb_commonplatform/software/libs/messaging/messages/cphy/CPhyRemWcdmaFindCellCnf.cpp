///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaFindCellCnf.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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
#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyRemWcdmaFindCellCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemWcdmaFindCellCnf::CPhyRemWcdmaFindCellCnf(const CphyRemWcdmaFindCellCnf *cStruct)
{
    m_Struct = *cStruct;
}

s32 CPhyRemWcdmaFindCellCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemWcdmaFindCellCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemWcdmaFindCellCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemWcdmaFindCellCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemWcdmaFindCellCnf::GetStruct(CphyMessageData *const msg)
{
    msg->remWcdmaFindCellCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemWcdmaFindCellCnf::ToString() const
{
    ostringstream stream;
    u8            n;
    //KS
    u8            i;
    u8            k=0;
    //TODO: Modify the code to accomodate all the members
    //After modification of the code it can report upto 32 neighbor cells
    //RSYS_ASSERT(m_Struct.nbrList[0].nCells <= CPHY_REM_FIND_CELL_CNF_MAX_REM_FOUND_CELLS);
    RSYS_ASSERT(m_Struct.nbrList[0].nCells <= CPHY_REM_FIND_CELL_CNF_MAX_WCDMA_NBRS);

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CphyRemWcdmaFindCellCnf"                                          << endl;
    for(i = 0; i < m_Struct.nbrCount ;i++)
    {
      stream << "{ status="               << CphyL1StatusToString(m_Struct.status) << endl;
      stream << "  nCells="               << (u16)m_Struct.nbrList[i].nCells                  << endl;
      stream << "  frequency="            <<      m_Struct.nbrList[i].frequency               << endl;
      stream << "  band="                 << UmtsBandIdToString(m_Struct.nbrList[i].band)     << endl;
      stream << "  rssi="                 << (m_Struct.nbrList[i].rssi / 8.0f) << "dBm"       << endl;
      while(m_Struct.nbrList[i].psc[k])
      k++;
    
      for(n = 0; n < k; n++)
      {
        stream << "  { psc=" <<  m_Struct.nbrList[i].psc[n] <<
                  "    ecn0="<< (m_Struct.nbrList[i].ecn0[n] / 8.0f) << "dB" <<
                  "    rscp="<< (m_Struct.nbrList[i].rscp[n] / 8.0f) << "dBm" <<
                  "  }"      <<endl;
      }
      k = 0;
      stream << "}" << endl;
    }
    return(stream.str());
}


string CPhyRemWcdmaFindCellCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" << CphyL1StatusToString(m_Struct.status)
           << " nCells=" << (u16)m_Struct.nbrList[0].nCells << endl;

    return(stream.str());
}

extern "C"
{


s32 CphyRemWcdmaFindCellCnf_Serialise(const CphyRemWcdmaFindCellCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaFindCellCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemWcdmaFindCellCnf));
    return sizeof(CphyRemWcdmaFindCellCnf);
}


s32 CphyRemWcdmaFindCellCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemWcdmaFindCellCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaFindCellCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemWcdmaFindCellCnf));

    return sizeof(CphyRemWcdmaFindCellCnf);
}

}

// END OF FILE
