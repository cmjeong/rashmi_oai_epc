///////////////////////////////////////////////////////////////////////////////
//
// $Id: FNTPGetFrequencyOffsetCnf.cpp
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
#include "FNTPGetFrequencyOffsetCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// FNTPGetFrequencyOffsetCnf Class Functions
///////////////////////////////////////////////////////////////////////////////


FNTPGetFrequencyOffsetCnf::FNTPGetFrequencyOffsetCnf(s32 frequencyOffsetppb)
:m_frequencyOffsetppb(frequencyOffsetppb)
{

}

FNTPGetFrequencyOffsetCnf::~FNTPGetFrequencyOffsetCnf()
{

}

s32  FNTPGetFrequencyOffsetCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
ENTER();
s32 retVal;
    if(dataMaxBytes >= MESSAGE_DATA_LEN)
    {
        memcpy(data,&m_frequencyOffsetppb, MESSAGE_DATA_LEN);
        retVal = MESSAGE_DATA_LEN;
    }
    else
    {
        retVal = -1;
    }

RETURN(retVal);
}

bool FNTPGetFrequencyOffsetCnf::DeSerialise(const u8* data, u32 dataLen)
{
ENTER();
bool retVal;
        if(dataLen <= MESSAGE_DATA_LEN)
        {
            memcpy(&m_frequencyOffsetppb,data, MESSAGE_DATA_LEN);
            retVal = true;
        }
        else
        {
            retVal = false;
        }

RETURN(retVal);
}

string FNTPGetFrequencyOffsetCnf::ToString() const
{
    ostringstream stream;

    stream << "FNTPGetFrequencyOffsetCnf " << endl;
    stream << "{ frequency offset (ppb) = " << m_frequencyOffsetppb << endl;

    return(stream.str());
}
