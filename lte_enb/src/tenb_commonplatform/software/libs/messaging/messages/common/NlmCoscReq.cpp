///////////////////////////////////////////////////////////////////////////////
//
// NlmCoscReq.cpp
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
#include <system/NumberConversions.h>
#include <system/SerialisationUtils.h>
#include <system/UmtsBands.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NlmCoscReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

NlmCoscReq::NlmCoscReq(CoscArfcnList &arfcnList) :
    m_coscArfcnList(arfcnList)
{
}

NlmCoscReq::NlmCoscReq()
{
}

NlmCoscReq::~NlmCoscReq()
{
}

s32 NlmCoscReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    // Complex message... fairly arbitrary test but should be plenty.  We validate this below.
    // This is more maintainable than trying to calculate the exact space requirement.
    // Vineet: need to change the size
    static const u32 MAX_SERIALISED_BYTES = 2000;
    RSYS_ASSERT(dataMaxBytes >= MAX_SERIALISED_BYTES);

    u8 * pOrigData = data;
    u8 i;

    for(i = 0; i < sizeof(m_coscArfcnList.arfcn) / sizeof(m_coscArfcnList.arfcn[0]); i++)
    {
        SerialiseIt(m_coscArfcnList.arfcn[i], data);
    }
    SerialiseIt(m_coscArfcnList.numArfcns, data);

    RSYS_ASSERT((u32)(data - pOrigData) <= MAX_SERIALISED_BYTES);
    return (data - pOrigData);
}

bool NlmCoscReq::DeSerialise(const u8* data, u32 dataLen)
{
    u8 i;

    const u8 *pOrigData = data;

    for(i = 0; i < sizeof(m_coscArfcnList.arfcn) / sizeof(m_coscArfcnList.arfcn[0]); i++)
    {
        DeSerialiseIt(m_coscArfcnList.arfcn[i], data);
    }
    DeSerialiseIt(m_coscArfcnList.numArfcns, data);

    //need to do a whole load of validation here
    if(m_coscArfcnList.numArfcns > 3)
    {
        m_coscArfcnList.numArfcns = 3;
    }
    TRACE_PRINTF("Data=%x pOrigData=%x dataLen=%d\n", (unsigned int)data, (unsigned int)pOrigData, dataLen);

    return true;
}

/* 0.9_patch2 */
string NlmCoscReq::ToString() const
{
    ostringstream stream;

    stream << "NlmCoscReq\n{ " << endl;
    stream << " NumArfcns: { " << (u16)m_coscArfcnList.numArfcns << endl;
    for (u32 i = 0; i < NUM_ARFCNS; i++)
    {
        stream << " " << (u16)m_coscArfcnList.arfcn[i] << endl;
    }
    stream << " }\n";

    return stream.str();
}
