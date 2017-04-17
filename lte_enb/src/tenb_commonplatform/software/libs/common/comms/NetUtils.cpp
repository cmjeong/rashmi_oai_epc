///////////////////////////////////////////////////////////////////////////////
//
// NetUtils.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>

#include <system/Trace.h>
#include <system/StringUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NetUtils.h"
#include "IPv4Address.h"
#include "MacAddress.h"
#include "networking.h"


namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

void NetUtils::GetLocalIpAddress(IPv4Address& localIpAddress)
{
    ENTER();

    localIpAddress.Clear();

    do
    {
        // Use the SIOCGIFCONF ioctl call to iterate through the network interfaces
        static const unsigned long kMaxAddrBufferSize = 2048;

        char* ifReqIter = NULL;
        struct ifconf ifc;
        struct ifreq* ifr;
        char buffer[kMaxAddrBufferSize];

        int tempSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if(tempSocket == -1)
        {
            break;
        }

        ifc.ifc_len = kMaxAddrBufferSize;
        ifc.ifc_buf = buffer;

        int err = ioctl(tempSocket, SIOCGIFCONF, (char*)&ifc);
        if (err == -1)
        {
            close(tempSocket);
            break;
        }

        close(tempSocket);
        tempSocket = -1;

        for (ifReqIter = buffer; ifReqIter < (buffer + ifc.ifc_len);)
        {
            ifr = (struct ifreq*)ifReqIter;
            ifReqIter += sizeof(ifr->ifr_name) + 0;
            switch (ifr->ifr_addr.sa_family)
            {
                case AF_INET:
                    ifReqIter += sizeof(struct sockaddr_in);
                    break;
                default:
                    ifReqIter += sizeof(struct sockaddr);
                    break;
            }

            // Only count interfaces in the AF_INET family.
            // And don't count localhost, loopback interfaces.
            if ((ifr->ifr_addr.sa_family == AF_INET) && (strncmp(ifr->ifr_name, "lo", 2) != 0))
            {
                struct sockaddr_in* addrPtr = (struct sockaddr_in*)&ifr->ifr_addr;
                localIpAddress.Set(addrPtr->sin_addr);
                break;
            }
        }

    } while (0);

    EXIT();
}

bool NetUtils::GetMacAddress(const char * interface, MacAddress& macAddress)
{
    ENTER();

    RSYS_ASSERT(interface != NULL);
    RSYS_ASSERT(strlen(interface) > 0);

    int sock;
    struct ifreq iface;

    macAddress.Clear();

    strncpysafe(iface.ifr_name, interface, sizeof(iface.ifr_name));

    // Open a socket
    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        RETURN(false);
    }
    else
    {
        // Get the interface hardware address
        if((ioctl(sock, SIOCGIFHWADDR, &iface)) < 0)
        {
	    close(sock);
            perror("ioctl SIOCGIFHWADDR");
            RETURN(false);
        }
        else
        {
            macAddress.Set(iface.ifr_hwaddr.sa_data[0] & 0xff,
                           iface.ifr_hwaddr.sa_data[1] & 0xff,
                           iface.ifr_hwaddr.sa_data[2] & 0xff,
                           iface.ifr_hwaddr.sa_data[3] & 0xff,
                           iface.ifr_hwaddr.sa_data[4] & 0xff,
                           iface.ifr_hwaddr.sa_data[5] & 0xff);
        }
    }
    close(sock);
    RETURN(true);
}

}
