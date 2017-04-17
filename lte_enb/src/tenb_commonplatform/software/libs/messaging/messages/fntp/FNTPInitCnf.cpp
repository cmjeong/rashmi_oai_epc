///////////////////////////////////////////////////////////////////////////////
//
// $Id: FNTPInitCnf.cpp
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
#include "FNTPInitCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// FNTPInitCnf Class Functions
///////////////////////////////////////////////////////////////////////////////




s32  FNTPInitCnf::Serialise(u8* data, u32 dataMaxBytes) const
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
        retVal = -1;
    }

RETURN(retVal);
}

bool FNTPInitCnf::DeSerialise(const u8* data, u32 dataLen)
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
            retVal = false;
        }

RETURN(retVal);
}

string FNTPInitCnf::ToString() const
{
    ostringstream stream;

    stream << "FNTPInitCnff " << endl;
    stream << "{ success = " << (u16)m_success << endl;

    return(stream.str());
}
