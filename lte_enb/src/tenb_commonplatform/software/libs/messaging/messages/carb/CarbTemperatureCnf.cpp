///////////////////////////////////////////////////////////////////////////////
//
// $Id: CarbTemperatureCnf.cpp 28331 2010-07-17 15:25:20Z mmcternan $
//
// See header file for documentation.
//
// Copyright (C) 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/NumberConversions.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CarbTemperatureCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CarbTemperatureCnf::CarbTemperatureCnf(s32 boardDegC, s32 radioDegC) :
    m_boardDegC(boardDegC),
    m_radioDegC(radioDegC)
{
}

CarbTemperatureCnf::CarbTemperatureCnf() :
    m_boardDegC(0),
    m_radioDegC(0)
{
}

s32 CarbTemperatureCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    if(dataMaxBytes < 8) return -1;

    U32ToBigEndianByteArray((u32)m_boardDegC, &data[0]);
    U32ToBigEndianByteArray((u32)m_radioDegC, &data[4]);

    return 8;
}

bool CarbTemperatureCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(dataLen < 8) return false;

    m_boardDegC = (s32)BigEndianByteArrayToU32(&data[0]);
    m_radioDegC = (s32)BigEndianByteArrayToU32(&data[4]);

    return true;
}


string CarbTemperatureCnf::ToString() const
{
    ostringstream stream;

    stream << "CarbTemperatureCnf { board=" << m_boardDegC << " degC"
           << ", radio=" << m_radioDegC << " degC }";

    return(stream.str());
}


string CarbTemperatureCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "board=" << m_boardDegC << " degC"
           << ", radio=" << m_radioDegC << " degC";

    return(stream.str());
}

// END OF FILE
