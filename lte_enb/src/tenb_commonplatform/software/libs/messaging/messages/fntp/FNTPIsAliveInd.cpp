///////////////////////////////////////////////////////////////////////////////
//
// FNTPIsAliveInd.cpp
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
#include <system/Trace.h>
#include <string.h> // for memcpy

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "FNTPIsAliveInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// FNTPGetFrequencyOffsetInd Class Functions
///////////////////////////////////////////////////////////////////////////////

s32  FNTPIsAliveInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();
    s32 retVal;
    u8* u8Ptr = data;

    if(dataMaxBytes >= MESSAGE_DATA_LEN)
    {
        TRACE_PRINTF("dataMaxBytes in Serialise = %" PRIu32 ", m_isAlive = %s, m_simulatorActive = %s",
                      dataMaxBytes, m_isAlive?"ALIVE":"DEAD", m_simulatorActive?"SIM-ACTIVE":"SIM-NOT-ACTIVE");
        memcpy(u8Ptr,&m_isAlive,sizeof(m_isAlive));
        u8Ptr += sizeof(m_isAlive);
        memcpy(u8Ptr,&m_simulatorActive,sizeof(m_simulatorActive));
        retVal = MESSAGE_DATA_LEN;
    }
    else
    {
        retVal = -1;
    }

    RETURN(retVal);
}

bool FNTPIsAliveInd::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();
    bool retVal;
    const u8* u8Ptr = data;

    if(dataLen <= MESSAGE_DATA_LEN)
    {
        //TRACE_HEX_MSG("FNTPIsAliveInd::DeSerialise data",data,MESSAGE_DATA_LEN);
        memcpy(&m_isAlive,u8Ptr, sizeof(m_isAlive));
        u8Ptr += sizeof(m_isAlive);
        memcpy(&m_simulatorActive,u8Ptr, sizeof(m_simulatorActive));
        retVal = true;
        //TRACE_PRINTF("dataLen in DeSerialise = %d, m_isAlive = %d, m_simulatorActive = %d",dataLen,m_isAlive,m_simulatorActive);
    }
    else
    {
        retVal = false;
    }

    RETURN(retVal);
}

string FNTPIsAliveInd::ToString() const
{
    ostringstream stream;

    stream << "FNTPIsAliveInd " << endl;
    stream << "{ success = " << (u16)m_isAlive << endl;
    stream << "{ simulator active = " << (u16)m_simulatorActive << endl;

    return(stream.str());
}
