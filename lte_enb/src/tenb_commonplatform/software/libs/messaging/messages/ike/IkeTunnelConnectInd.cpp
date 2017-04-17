///////////////////////////////////////////////////////////////////////////////
//
// IkeTunnelConnectInd
//
// Copyright radisys
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>
#include <arpa/inet.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IkeTunnelConnectInd.h"

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace threeway;

s32 IkeTunnelConnectInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u8 * start = data;
    u8 ipType;
    bool isIpv6 =m_tunnelAddr.CheckIfIPv6();
    if (8 <= dataMaxBytes)
    {
        SerialiseIt(m_id, data);
        if(isIpv6)
        {
           u16 ipAddr[8];
           bool isAddrSet =m_tunnelAddr.ipv6.Get(ipAddr);
           ipType = 1;
           SerialiseIt(ipType,data);
           for(int i=0;(i<8)&&isAddrSet;i++)
           {
               SerialiseIt(ipAddr[i], data);
           }
        }
        else
        {
           ipType = 0;
           SerialiseIt(ipType,data);
           SerialiseIt(m_tunnelAddr.ipv4.Get(),data);
        }
    }

    RETURN(data - start);
}

bool IkeTunnelConnectInd::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    bool decode = (8 <= dataLen);

    if (decode)
    {
        u8 ipType;
        DeSerialiseIt(m_id, data);
        DeSerialiseIt(ipType, data);

       if(ipType == 1)
       {
           u16 addr[8];
           for(int i=0;i<8;i++)
           {
                 DeSerialiseIt(addr[i],data);
           }
           m_tunnelAddr.ipv6.Set(addr);
           m_tunnelAddr.Set(m_tunnelAddr.ipv6.ToString());
       }
       else
       {
          u32 ta;
          DeSerialiseIt(ta,data);
          m_tunnelAddr.ipv4.Set(ta);
          m_tunnelAddr.Set(m_tunnelAddr.ipv4.ToString());
       }
    }

    RETURN(decode);
}

string IkeTunnelConnectInd::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "IkeTunnelConnectInd: " << stream << " id=" << m_id << " tunnelAddr=" << m_tunnelAddr.Get();

    RETURN(stream.str());
}
