///////////////////////////////////////////////////////////////////////////////
//
// GsmRemScanCnf.cpp
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
#include <string>
#include <string.h> // for memcpy

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "GsmRemScanCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

GsmRemScanCnf::~GsmRemScanCnf()
{
    ENTER();
    EXIT();
}

s32 GsmRemScanCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    memcpy((void*)data,(const void*)&m_scanCompletedSuccessfully,sizeof(m_scanCompletedSuccessfully));

    RETURN(sizeof(m_scanCompletedSuccessfully));
}

bool GsmRemScanCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    memcpy((void*)&m_scanCompletedSuccessfully,(const void*)data,sizeof(m_scanCompletedSuccessfully));

    RETURN(true);
}

std::string GsmRemScanCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "GsmRemScanCnf =" << (u32)m_scanCompletedSuccessfully << endl;

    RETURN(stream.str());
}
