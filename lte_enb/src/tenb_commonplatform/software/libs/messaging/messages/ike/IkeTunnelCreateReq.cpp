///////////////////////////////////////////////////////////////////////////////
//
// IkeTunnelCreateReq
//
// Copyright radisys
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

#include "IkeTunnelCreateReq.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;
using namespace std;

s32 IkeTunnelCreateReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u8 * start = data;

    if (4 <= dataMaxBytes)
    {
        SerialiseIt(m_destAddr.ToString(), data);
    }
    if (4 <= dataMaxBytes)
    {
        SerialiseIt(m_authMethod, data);
    }

    RETURN(data - start);
}

bool IkeTunnelCreateReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    bool decode = (4 <= dataLen);

    if (decode)
    {
        string da;

        DeSerialiseIt(da, data,Fqdn::MaxLength);

        m_destAddr.Set(da);
    }

    if (decode)
    {
        string da;

        DeSerialiseIt(da, data,Fqdn::MaxLength);

        m_authMethod = da;
    }

    RETURN(decode);
}

string IkeTunnelCreateReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "IkeTunnelCreateReq:" << " destAddr=" << m_destAddr.ToString() << "authMethod=" << m_authMethod;

    RETURN(stream.str());
}
