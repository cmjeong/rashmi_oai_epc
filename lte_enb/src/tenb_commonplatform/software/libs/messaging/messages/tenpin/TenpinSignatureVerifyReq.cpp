///////////////////////////////////////////////////////////////////////////////
//
// TenpinSignatureVerifyReq.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
// THE FORMAT OF THE MESSAGE IMPLEMENTED BY THIS CLASS MUST NOT BE CHANGED.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinSignatureVerifyReq.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

s32 TenpinSignatureVerifyReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    u8 * start = data;

    SerialiseIt(m_type, data);
    SerialiseIt(m_inputFilename, data);
    SerialiseIt(m_outputFilename, data);

    return (data - start);
}

bool TenpinSignatureVerifyReq::DeSerialise(const u8* data, u32 dataLen)
{
    DeSerialiseIt(m_type, data, 4096);
    DeSerialiseIt(m_inputFilename, data, 4096);
    DeSerialiseIt(m_outputFilename, data, 4096);

    return true;
}

std::string TenpinSignatureVerifyReq::ToString() const
{
    ostringstream stream;

    stream << "TenpinSignatureVerifyReq: ";
    stream << "type=" << m_type << ",";
    stream << "inputFilename=" << m_inputFilename << ",";
    stream << "outputFilename=" << m_outputFilename << ",";

    return stream.str();
}
