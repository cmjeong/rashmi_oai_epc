///////////////////////////////////////////////////////////////////////////////
//
// FNTPSetSampleModeCnf.cpp
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
#include "FNTPSetSampleModeCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// FNTPSetSampleModeCnf Class Functions
///////////////////////////////////////////////////////////////////////////////




s32  FNTPSetSampleModeCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
ENTER();
s32 retVal;
    if(dataMaxBytes >= MESSAGE_DATA_LEN)
    {
        memcpy(data,&m_success, MESSAGE_DATA_LEN);
        retVal = MESSAGE_DATA_LEN;
    }
    else
    {
        TRACE_PRINTF("Serialise error len = %" PRIu32, dataMaxBytes);
        retVal = -1;
    }

RETURN(retVal);
}

bool FNTPSetSampleModeCnf::DeSerialise(const u8* data, u32 dataLen)
{
ENTER();
bool retVal;
        if(dataLen <= MESSAGE_DATA_LEN)
        {
            memcpy(&m_success,data, MESSAGE_DATA_LEN);
            retVal = true;
        }
        else
        {
            TRACE_PRINTF("de Serialise error len = %" PRIu32, dataLen);
            retVal = false;
        }

RETURN(retVal);
}

string FNTPSetSampleModeCnf::ToString() const
{
    ostringstream stream;

    stream << "FNTPSetSampleModeCnf " << endl;
    stream << "{ success = " << (u16)m_success << endl;

    return(stream.str());
}
