///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemSibDecodeComplete.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemSibDecodeComplete.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemSibDecodeComplete::CPhyRemSibDecodeComplete(const CphyRemSibDecodeComplete *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemSibDecodeComplete::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemSibDecodeComplete_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemSibDecodeComplete::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemSibDecodeComplete_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemSibDecodeComplete::GetStruct(CphyMessageData *const msg)
{
    msg->remSibDecodeComplete = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemSibDecodeComplete::ToString() const
{
    ostringstream stream;
    u8            count;

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CPhyRemSibDecodeComplete " << endl;
    stream << "{ status= " << CphyL1StatusToString(m_Struct.status) << endl;
    for(count = 0; count < m_Struct.count; count++)
    {
       stream << " Cell details :"        <<  (u16)(count + 1)                             << endl;
       stream << "  psc= "                <<  (u16)m_Struct.sibDecodeInfo[count].psc           << endl;
       stream << "  plmnType= "           <<  (u16)m_Struct.sibDecodeInfo[count].plmnType      << endl;
       stream << "  plmnId:mcc[0]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mcc[0] << endl;
       stream << "  plmnId:mcc[1]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mcc[1] << endl;
       stream << "  plmnId:mcc[2]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mcc[2] << endl;
       stream << "  plmnId:mnc[0]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mnc[0] << endl;
       stream << "  plmnId:mnc[1]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mnc[1] << endl;
       stream << "  plmnId:mnc[2]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mnc[2] << endl;
       stream << "  lac[0]= "             <<  (u16)m_Struct.sibDecodeInfo[count].lac[0]        << endl;
       stream << "  lac[1]= "             <<  (u16)m_Struct.sibDecodeInfo[count].lac[0]        << endl;
       stream << "  rac= "                <<  (u16)m_Struct.sibDecodeInfo[count].rac           << endl;
       stream << "  cellId= "             <<  (u32)m_Struct.sibDecodeInfo[count].cellId        << endl;
       stream << "###########################"   << endl;
    }
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemSibDecodeComplete::ToBriefString() const
{
    ostringstream stream;
    u8 count;

    stream << "status= " << CphyL1StatusToString(m_Struct.status);
    for(count = 0; count < m_Struct.count; count++)
    {
       stream << "  psc= "                << (u16)m_Struct.sibDecodeInfo[count].psc           
              << "  plmnType= "           << (u16)m_Struct.sibDecodeInfo[count].plmnType      
              << "  plmnId:mcc[0]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mcc[0] 
              << "  plmnId:mcc[1]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mcc[1] 
              << "  plmnId:mcc[2]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mcc[2] 
              << "  plmnId:mnc[0]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mnc[0] 
              << "  plmnId:mnc[1]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mnc[1] 
              << "  plmnId:mnc[2]= "      <<  (u16)m_Struct.sibDecodeInfo[count].plmnId.mnc[2] 
              << "  lac[0]= "             <<  (u16)m_Struct.sibDecodeInfo[count].lac[0]        
              << "  lac[1]= "             <<  (u16)m_Struct.sibDecodeInfo[count].lac[0]        
              << "  rac= "                <<  (u16)m_Struct.sibDecodeInfo[count].rac           
              << "  cellId= "             << (u32)m_Struct.sibDecodeInfo[count].cellId        << endl;        
    }
    stream << "}" << endl;

    return(stream.str());
}

extern "C"
{


s32 CphyRemSibDecodeComplete_Serialise(const CphyRemSibDecodeComplete *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemSibDecodeComplete))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemSibDecodeComplete));
    return sizeof(CphyRemSibDecodeComplete);
}

s32 CphyRemSibDecodeComplete_Deserialise(const u8 *buffer, u32 maxLen, CphyRemSibDecodeComplete *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemSibDecodeComplete))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemSibDecodeComplete));
    return sizeof(CphyRemSibDecodeComplete);
}

}

// END OF FILE
