///////////////////////////////////////////////////////////////////////////////
//
// $Id: FNTPGetFrequencyOffsetReq.cpp 3068 2007-11-22 11:59:25Z mm $
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
#include "FNTPGetFrequencyOffsetReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// FNTPGetFrequencyOffsetReq Class Functions
///////////////////////////////////////////////////////////////////////////////

FNTPGetFrequencyOffsetReq::FNTPGetFrequencyOffsetReq(u32 requiredAccuracyppb)
:m_requiredAccuracyppb(requiredAccuracyppb)
{

}

FNTPGetFrequencyOffsetReq::~FNTPGetFrequencyOffsetReq()
{

}

s32  FNTPGetFrequencyOffsetReq::Serialise(u8* data, u32 dataMaxBytes) const
{
ENTER();
s32 retVal;
    if(dataMaxBytes >= MESSAGE_DATA_LEN)
    {
        memcpy(data,&m_requiredAccuracyppb, MESSAGE_DATA_LEN);
        retVal = MESSAGE_DATA_LEN;
    }
    else
    {
        retVal = -1;
    }

RETURN(retVal);
}

bool FNTPGetFrequencyOffsetReq::DeSerialise(const u8* data, u32 dataLen)
{
ENTER();
bool retVal;
    if(dataLen <= MESSAGE_DATA_LEN)
    {
        memcpy(&m_requiredAccuracyppb,data, MESSAGE_DATA_LEN);
        retVal = true;
    }
    else
    {
        retVal = false;
    }

RETURN(retVal);
}

string FNTPGetFrequencyOffsetReq::ToString() const
{
    ostringstream stream;

    stream << "FNTPGetFrequencyOffsetReq " << endl;
    stream << "{ required accuracy (ppb) = " << m_requiredAccuracyppb << endl;

    return(stream.str());
}
