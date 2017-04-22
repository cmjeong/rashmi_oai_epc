///////////////////////////////////////////////////////////////////////////////
//
// TenpinFirewallOpenReq.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
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

#include "TenpinFirewallOpenReq.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

s32 TenpinFirewallOpenReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u8 * start = data;

    // serialised as token, sequence of values

    if (serialisedLen <= dataMaxBytes)
    {
        SerialiseIt(m_token, data);
        SerialiseIt(m_passIn, data);
        SerialiseIt(m_passOut, data);
        SerialiseIt(m_protocolUdp, data);
        SerialiseIt(m_broadcast, data);
        SerialiseIt(m_localAddr, data);
        SerialiseIt(m_localPort, data);
        SerialiseIt(m_remoteAddr, data);
        SerialiseIt(m_remotePort, data);
    }

    RETURN(data - start);
}

bool TenpinFirewallOpenReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    bool decode = (serialisedLen <= dataLen);

    if (decode)
    {
        DeSerialiseIt(m_token, data);
        DeSerialiseIt(m_passIn, data);
        DeSerialiseIt(m_passOut, data);
        DeSerialiseIt(m_protocolUdp, data);
        DeSerialiseIt(m_broadcast, data);
        DeSerialiseIt(m_localAddr, data,80);
        DeSerialiseIt(m_localPort, data);
        DeSerialiseIt(m_remoteAddr, data,80);
        DeSerialiseIt(m_remotePort, data);
    }

    RETURN(decode);
}

std::string TenpinFirewallOpenReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "TenpinFirewallOpenReq: token=" << m_token << " ";
    stream << "in=" << m_passIn << ",";
    stream << "out=" << m_passOut << ",";
    stream << "udp=" << m_protocolUdp << ",";
    stream << "broadcast=" << m_broadcast << ",";
    stream << "localAddr=" << m_localAddr << ",";
    stream << "localPort=" << m_localPort << ",";
    stream << "remoteAddr=" << m_remoteAddr << ",";
    stream << "remotePort=" << m_remotePort << ",";

    RETURN(stream.str());
}
