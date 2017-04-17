///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBSccpchConfigReq.cpp 28310 2010-07-16 15:27:29Z mmcternan $
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

#include "CPhyNodeBSccpchConfigReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBSccpchConfigReq::CPhyNodeBSccpchConfigReq(const CphyNodeBSccpchConfigReq *cStruct)
{
    m_Struct = *cStruct;
}

s32 CPhyNodeBSccpchConfigReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBSccpchConfigReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBSccpchConfigReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBSccpchConfigReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBSccpchConfigReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBSccpchConfigReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBSccpchConfigReq::ToString() const
{
    ostringstream stream;

    stream << setprecision(1) << setiosflags(ios::fixed);
    stream << "CphyNodeBSccpchConfigReq" << endl;
    stream << "{ Physical Channel Parameters" << endl;
    stream << "   dtxPositionFixed=" << (u16) m_Struct.phyParams.dtxPositionFixed << endl;
    stream << "   sf=" << m_Struct.phyParams.sf << endl;
    stream << "   ovsf=" << (u16) m_Struct.phyParams.ovsf << endl;
    stream << "   slotFormat=" << (u16) m_Struct.phyParams.slotFormat << endl;
    stream << "}" << endl;

    stream << "{ Transport Channel Parameters, nTrch=" << (u16) m_Struct.trchParams.nTrch << endl;
    for (u16 i=0;i<m_Struct.trchParams.nTrch;i++)
    {
        stream << "  { trch=" << i << endl;
        stream << "    { nTf=" << (u16) m_Struct.trchParams.trch[i].nTf << endl;
        stream << "    { tti=" << (u16) (m_Struct.trchParams.trch[i].tti * 10) << endl;
        stream << "    { coding=" << m_Struct.trchParams.trch[i].coding << endl;
        stream << "    { crc=" << m_Struct.trchParams.trch[i].crc << endl;
        stream << "    { rmAttr=" << (u16) m_Struct.trchParams.trch[i].rmAttr << endl;
        stream << "    { macHeaderBit=" << (u16) m_Struct.trchParams.trch[i].macHeaderBit << endl;

        for (u16 j=0;j<m_Struct.trchParams.trch[i].nTf;j++)
        {
            stream << "      { tfs=" << j << endl;
            stream << "        { blockCount=" << (u16) m_Struct.trchParams.trch[i].tfs[j].blockCount << endl;
            stream << "        { blockSize=" << m_Struct.trchParams.trch[i].tfs[j].blockSize << endl;
            stream << "      }" << endl;
        }

        stream << "    }" << endl;
        stream << "  }" << endl;
    }

    stream << "  { nTfci=" << (u16) m_Struct.trchParams.nTfci << endl;
    for (u16 i=0;i<m_Struct.trchParams.nTrch;i++)
    {
        stream << "    Trch" << i << "{ ";
        for (u16 j = 0; j < m_Struct.trchParams.nTfci; j++)
        {
            stream << (u16) m_Struct.trchParams.tfIdx[i][j];
            if (j != m_Struct.trchParams.nTfci - 1)
                stream << ", ";
        }

        stream << " }" << endl;
    }
    stream << "  }" << endl;
    stream << "}" << endl;

    stream << "{ Paging Parameters" << endl;
    stream << "  pagingCycleFrames=" << m_Struct.pagingCycleFrames << endl;
    stream << "  piPerFrame       =" << m_Struct.pagingIndicatorsPerFrame << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBSccpchConfigReq::ToBriefString() const
{
    ostringstream stream;

    stream << "drxCycle=" << m_Struct.pagingCycleFrames;

    return(stream.str());

}

extern "C"
{


s32 CphyNodeBSccpchConfigReq_Serialise(const CphyNodeBSccpchConfigReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBSccpchConfigReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBSccpchConfigReq));
    return sizeof(CphyNodeBSccpchConfigReq);
}


s32 CphyNodeBSccpchConfigReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBSccpchConfigReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBSccpchConfigReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBSccpchConfigReq));

    return sizeof(CphyNodeBSccpchConfigReq);
}

}

// END OF FILE
