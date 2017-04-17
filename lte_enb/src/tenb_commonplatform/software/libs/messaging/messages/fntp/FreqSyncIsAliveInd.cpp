///////////////////////////////////////////////////////////////////////////////
//
// $Id: FreqSyncIsAliveInd.cpp
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
#include <system/Trace.h>
#include <string.h> // for memcpy

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "FreqSyncIsAliveInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// FreqSyncGetFrequencyOffsetInd Class Functions
///////////////////////////////////////////////////////////////////////////////

s32  FreqSyncIsAliveInd::Serialise(u8* data, u32 dataMaxBytes) const
{
ENTER();
s32 retVal;
    if(dataMaxBytes >= MESSAGE_DATA_LEN)
    {
        memcpy(data,&m_isAlive, sizeof(m_isAlive));
        retVal = MESSAGE_DATA_LEN;
    }
    else
    {
        retVal = -1;
    }

RETURN(retVal);
}

bool FreqSyncIsAliveInd::DeSerialise(const u8* data, u32 dataLen)
{
ENTER();
bool retVal;
        if(dataLen <= MESSAGE_DATA_LEN)
        {
            memcpy(&m_isAlive,data, sizeof(m_isAlive));
            retVal = true;
        }
        else
        {
            retVal = false;
        }

RETURN(retVal);
}

string FreqSyncIsAliveInd::ToString() const
{
    ostringstream stream;

    stream << "FreqSyncIsAliveInd " << endl;
    stream << "{ success = " << (u16)m_isAlive << endl;

    return(stream.str());
}
