///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBStatInd.cpp 15300 2009-06-29 11:38:31Z dallwright $
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

#include "CPhyNodeBStatInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBStatInd::CPhyNodeBStatInd(const CphyNodeBStatInd *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBStatInd::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBStatInd_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBStatInd::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBStatInd_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBStatInd::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBStatInd = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBStatInd::ToString() const
{
    ostringstream stream;
    u16           t;

    stream << "CPhyNodeBStatInd " << endl;
    stream << "{ frameCount    =" << m_Struct.frameCount  << endl;
    stream << "  prachErr      =" << m_Struct.prachErr  << endl;
    stream << "  prachCount    =" << m_Struct.prachCount  << endl;
    stream << "  berErr        =" << m_Struct.berErr  << endl;
    stream << "  berCount      =" << m_Struct.berCount  << endl;

    for(t = 0; t < NUM_CPHY_STAT_CHAN_DCH; t++)
    {
        stream << "  bler" << (u16)t << " err/data =" << m_Struct.blerErr[t] << "/" << m_Struct.blerCount[t] << endl;
    }

    stream << "  hsdpaAck      =" << m_Struct.hsdpaAck << endl;
    stream << "  hsdpaNack     =" << m_Struct.hsdpaNack << endl;
    stream << "  hsdpaBufAck   =" << m_Struct.hsdpaBufAck << endl;
    stream << "  hsdpaBufNack  =" << m_Struct.hsdpaBufNack << endl;
    stream << "  hsdpaBufEmpty =" << m_Struct.hsdpaBufEmpty << endl;
    stream << "}" << endl;

    return(stream.str());
}

extern "C"
{


s32 CphyNodeBStatInd_Serialise(const CphyNodeBStatInd *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBStatInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBStatInd));
    return sizeof(CphyNodeBStatInd);
}


s32 CphyNodeBStatInd_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBStatInd *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBStatInd))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBStatInd));

    return sizeof(CphyNodeBStatInd);
}

}

// END OF FILE
