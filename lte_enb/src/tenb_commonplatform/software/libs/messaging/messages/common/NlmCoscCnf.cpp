///////////////////////////////////////////////////////////////////////////////
//
// NlmCoscCnf.cpp
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

#include "NlmCoscCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

NlmCoscCnf::NlmCoscCnf() :
m_coscResult(NLM_COSC_FAILED)
{
    ENTER();
    EXIT();
}

NlmCoscCnf::NlmCoscCnf(eNlmCoscResult coscResult, u16 coscArfcn) :
m_coscResult(coscResult),
m_coscArfcn(coscArfcn)
{
    ENTER();
    EXIT();
}

NlmCoscCnf::~NlmCoscCnf()
{
    ENTER();
    EXIT();
}

s32 NlmCoscCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 4);

    const u8 * const dataStart = data;

    SerialiseIt((u8)m_coscResult, data);
    SerialiseIt((u16)m_coscArfcn, data);

    RETURN(data - dataStart);
}

bool NlmCoscCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen < 1)
        RETURN(false);

    DeSerialiseIt((u8&)m_coscResult, data);
    DeSerialiseIt((u16&)m_coscArfcn, data);

    RETURN(true);
}

string NlmCoscCnf::ToString() const
{
    ENTER();

    ostringstream stream;
    string coscResultString;

    switch (m_coscResult)
    {
        case NLM_COSC_FAILED :
            coscResultString = "COSC failed";
            break;
        case NLM_COSC_SUCCESSFUL :
            coscResultString = "COSC successful";
            break;
    }

    stream << "NLM cosc result=" << coscResultString;
    stream << "NLM cosc freq =" << m_coscArfcn;

    RETURN(stream.str());
}
