///////////////////////////////////////////////////////////////////////////////
//
// See header file for documentation.
//
// Copyright � 3 Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <netinet/ip.h>
#include <sstream>

#include "IpTrace.h"
#include "IPv4Address.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

void IpTrace::TraceIpPacket(std::ostringstream& trace, const u8 *ipPacket, u32 ipPacketLen)
{
    // IP header:
    //          1st(MSB)                   2nd                      3rd                      4th
    // | 7  6  5  4  3  2  1  0 | 7  6  5  4  3  2  1  0 | 7  6  5  4  3  2  1  0 | 7  6  5  4  3  2  1  0 |
    // |  Version   |   IHL     | data[0]
    // |          TOS           | data[1]
    // |                 Total length                    | data[2-3]
    // |                 Identification                  | data[4-5]
    // | Flags  |           Fragment offset              | data[6-7]
    // |           TTL          |        Protocol        | data[8-9]
    // |                Header checksum                  | data[10-11]
    // |                                        Source IP address                                          | data[12-15]
    // |                                      Destination IP address                                       | data[16-19]
    // |                                      Options and padding :::                                      | data[20+]

    // TCP header:
    //          1st(MSB)                   2nd                      3rd                      4th
    // | 7  6  5  4  3  2  1  0 | 7  6  5  4  3  2  1  0 | 7  6  5  4  3  2  1  0 | 7  6  5  4  3  2  1  0 |
    // |                  Source Port                    |                 Destination Port                | 0-1,2-3
    // |                                           Sequence Number                                         | 4-7
    // |                                        Acknowledgement Number                                     | 8-11
    // | DataOffset | reserv |  ECN    |  Control Bits   |                      Window                     | 12,13,14-15
    // |                   Checksum                      |                  Urgent Pointer                 | 16-17,18-19
    // |                                      Options and padding :::                                      | 20+

    // Get lengths
    u8 headerLen = (ipPacket[0] & 0x0f) * 4; // IHL field * 4
    u16 totalLen = ((u16)(ipPacket[2]) << 8) + ipPacket[3];

    // Grab destination addresses for sending packet on.
    IPv4Address dstIpAddress;
    dstIpAddress.SetDigits(ipPacket[16], ipPacket[17], ipPacket[18], ipPacket[19]);
    IPv4Address srcIpAddress;
    srcIpAddress.SetDigits(ipPacket[12], ipPacket[13], ipPacket[14], ipPacket[15]);

    // Extract protocol type from ipPacket - ICMP, UDP or TCP.
    u8 ipProtocol = ipPacket[9];

    switch(ipProtocol)
    {
        case IPPROTO_ICMP:
            trace << "ICMP: ";
            break;
        case IPPROTO_UDP:
            trace << "UDP: ";
            break;
        case IPPROTO_TCP:
            trace << "TCP: ";
            break;
        default:
            trace << "Protocol=" << (u32)ipProtocol << ": ";
            break;
    }

    trace << "Len=" << totalLen << ", Src=" << srcIpAddress.ToString() <<
                ", Dst=" << dstIpAddress.ToString();

    if((ipProtocol == IPPROTO_UDP) || (ipProtocol == IPPROTO_TCP))
    {
        // Get UDP/TCP header information.
        const u8 *skipIpHeader = &ipPacket[headerLen];
        u16 dstPort = (((u16)skipIpHeader[2]) << 8) + skipIpHeader[3];
        u16 srcPort = (((u16)skipIpHeader[0]) << 8) + skipIpHeader[1];

        trace << ", SrcPort=" << (u32)srcPort << ", DstPort=" << (u32)dstPort;
        if(ipProtocol == IPPROTO_UDP)
        {
            u16 udpLen = (((u16)skipIpHeader[4]) << 8) + skipIpHeader[5];
            u16 udpChecksum = (((u16)skipIpHeader[6]) << 8) + skipIpHeader[7];

            trace << ", UdpLen=" << (u32)udpLen << ", UdpChecksum=" << udpChecksum << "(" << std::hex << udpChecksum << std::dec << ")";
        }

        if(ipProtocol == IPPROTO_TCP)
        {
            u8 controlBits = skipIpHeader[13] & 0x3f;
            if(controlBits & 0x20)
                trace << ", URG";
            if(controlBits & 0x10)
                trace << ", ACK";
            if(controlBits & 0x08)
                trace << ", PSH";
            if(controlBits & 0x04)
                trace << ", RST";
            if(controlBits & 0x02)
                trace << ", SYN";
            if(controlBits & 0x01)
                trace << ", FIN";
        }
    }
}

}
