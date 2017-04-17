///////////////////////////////////////////////////////////////////////////////
//
// RemScanCnf.cpp
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
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "RemScanCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

RemScanCnf::RemScanCnf() :
m_remResult(REM_SCAN_RESULT_FAILED)
{
    ENTER();
    EXIT();
}

RemScanCnf::RemScanCnf(eRemScanResult remResult) :
m_remResult(remResult)
{
    ENTER();
    EXIT();
}

RemScanCnf::~RemScanCnf()
{
    ENTER();
    EXIT();
}

s32 RemScanCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 4);

    const u8 * const dataStart = data;

    SerialiseIt((u8)m_remResult, data);

    RETURN(data - dataStart);
}

bool RemScanCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen < 1)
        RETURN(false);

    DeSerialiseIt((u8&)m_remResult, data);

    RETURN(true);
}

string RemScanCnf::ToString() const
{
    ENTER();

    ostringstream stream;
    string remResultString;

    switch (m_remResult)
    {
        case REM_SCAN_RESULT_NOT_YET_PERFORMED :
            remResultString = "Rem scan not yet performed";
            break;
        case REM_SCAN_RESULT_FAILED :
            remResultString = "Rem scan failed";
            break;
        case REM_SCAN_RESULT_PASSED :
            remResultString = "Rem scan passed";
            break;
        case REM_SCAN_RESULT_INTERRUPTED :
            remResultString = "Rem scan result interrupted";
            break;
    }

    stream << "rem result=" << remResultString;

    RETURN(stream.str());
}
