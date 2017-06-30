///////////////////////////////////////////////////////////////////////////////
//
// $Id: FNTPInitReq.cpp
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
#include "FNTPInitReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// FNTPInitReq Class Functions
///////////////////////////////////////////////////////////////////////////////




s32  FNTPInitReq::Serialise(u8* data, u32 dataMaxBytes) const
{
ENTER();
s32 retVal;
    if(dataMaxBytes >= MESSAGE_DATA_LEN)
    {
        memcpy(data,&m_dummy, MESSAGE_DATA_LEN);
        retVal = MESSAGE_DATA_LEN;
    }
    else
    {
        retVal = -1;
    }

RETURN(retVal);
}

bool FNTPInitReq::DeSerialise(const u8* data, u32 dataLen)
{
ENTER();
bool retVal;
        if(dataLen <= MESSAGE_DATA_LEN)
        {
            memcpy(&m_dummy,data, MESSAGE_DATA_LEN);
            retVal = true;
        }
        else
        {
            retVal = false;
        }

RETURN(retVal);
}

string FNTPInitReq::ToString() const
{
    ostringstream stream;

    stream << "FNTPInitCnf " << endl;
    //stream << "{ success = " << (u16)m_success << endl;

    return(stream.str());
}
