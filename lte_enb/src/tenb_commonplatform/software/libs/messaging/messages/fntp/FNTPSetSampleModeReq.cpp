///////////////////////////////////////////////////////////////////////////////
//
// FNTPSetSampleModeReq.cpp
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
#include "FNTPSetSampleModeReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// FNTPSetSampleModeReq Class Functions
///////////////////////////////////////////////////////////////////////////////

FNTPSetSampleModeReq::FNTPSetSampleModeReq(tSampleMode sampleMode)
:m_sampleMode(sampleMode)
{

}

FNTPSetSampleModeReq::~FNTPSetSampleModeReq()
{

}

s32  FNTPSetSampleModeReq::Serialise(u8* data, u32 dataMaxBytes) const
{
ENTER();
s32 retVal;
    if(dataMaxBytes >= MESSAGE_DATA_LEN)
    {
        memcpy(data,&m_sampleMode, MESSAGE_DATA_LEN);
        retVal = MESSAGE_DATA_LEN;
    }
    else
    {
        TRACE_PRINTF("Serialise error len = %" PRIu32, dataMaxBytes);
        retVal = -1;
    }

RETURN(retVal);
}

bool FNTPSetSampleModeReq::DeSerialise(const u8* data, u32 dataLen)
{
ENTER();
bool retVal;
    if(dataLen <= MESSAGE_DATA_LEN)
    {
        memcpy(&m_sampleMode,data, MESSAGE_DATA_LEN);
        retVal = true;
    }
    else
    {
        TRACE_PRINTF("de Serialise error len = %" PRIu32, dataLen);
        retVal = false;
    }

RETURN(retVal);
}

 /**
  * Convert to string for debug.
  */
string FNTPSetSampleModeReq::ToString() const
{
    ostringstream stream;

    stream << "FNTPSetSampleModeReq " << endl;
    switch(m_sampleMode)
    {
    case FAST_CONVERGENCE:
        stream << "FAST_CONVERGENCE,  " << m_sampleMode << endl;
        break;
    case LONG_TERM:
        stream << "LONG_TERM,  " << m_sampleMode << endl;
        break;
    }

    return(stream.str());
}
