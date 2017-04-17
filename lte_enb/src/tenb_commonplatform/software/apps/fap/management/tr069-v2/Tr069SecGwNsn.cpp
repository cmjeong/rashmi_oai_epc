///////////////////////////////////////////////////////////////////////////////
//
// <File name>
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <system/Trace.h>
#include <messaging/messages/common/OamActionReq.h>
#include <messaging/messages/ike/IkeTunnelCreateReq.h>
#include <messaging/messages/ike/IkeTunnelCreateCnf.h>
#include <messaging/messages/ike/IkeTunnelConnectInd.h>
#include <messaging/messages/ike/IkeTunnelDeleteReq.h>
#include <messaging/messages/ike/IkeTunnelDeleteCnf.h>
#include <system/AlarmEvent.h>
#include <system/Url.h>
#include <platform/FapAlarmId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace threeway;

#include "Tr069Application.h"
#include "Tr069Parameters.h"
#include "Tr069SecGwNsn.h"

using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////
namespace tr069
{


///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

Tr069SecGwNsn::Tr069SecGwNsn() :
    Tr069SecGwConnection("Tr069SecGwNsn")
 {
 }

Tr069SecGwNsn::~Tr069SecGwNsn()
{
}

void Tr069SecGwNsn::ConnectedEntry()
{
    Tr069SecGwConnection::ConnectedEntry();

    /**
     * CAN THIS GO NOW?
     *
     * If required, should probably move into CWMP FSM?
     */

    Tr069Application &app = Tr069Application::GetInstance();

    IPv4Address localIpAddr;
    app.GetMibCache().GetMibAttribute( PARAM_ID_ENB_IP_ADDR_IPV4, localIpAddr);

    MibAttributeValues attrs;

    // CR3086 rev 2 : SCTP port numbers depend on value of FAP inner IP address
    u32 sctp1stLocalPort = 2905;
    u32 sctp2ndLocalPort = 2906;
    u32 sctp1stRemotePort = 2905;
    u32 sctp2ndRemotePort = 2906;

    app.GetMibCache().GetMibAttribute(PARAM_ID_SCTP_LOCAL_PORT_1ST, sctp1stLocalPort);
    app.GetMibCache().GetMibAttribute(PARAM_ID_SCTP_LOCAL_PORT_2ND, sctp2ndLocalPort);
    app.GetMibCache().GetMibAttribute(PARAM_ID_SCTP_REMOTE_PORT_1ST, sctp1stRemotePort);
    app.GetMibCache().GetMibAttribute(PARAM_ID_SCTP_REMOTE_PORT_2ND, sctp2ndRemotePort);

    // select port based on odd or even IP address
    u8 digit0, digit1, digit2, digit3;
    localIpAddr.GetDigits(digit0, digit1, digit2, digit3);
    if (digit3 & 0x1)
    {
        TRACE_PRINTF("Odd FAP inner address detected: %s(%lu) : %lu,%lu",
                localIpAddr.ToString(), (unsigned long)localIpAddr.Get(), (unsigned long)sctp1stLocalPort, (unsigned long)sctp1stRemotePort);
        attrs.AddAttribute(PARAM_ID_IU_SCTP_LOCAL_PORT, sctp1stLocalPort);
        attrs.AddAttribute(PARAM_ID_IU_SCTP_REMOTE_PORT, sctp1stRemotePort);
    }
    else
    {
        TRACE_PRINTF("Even FAP inner address detected: %s(%lu) : %lu,%lu",
                localIpAddr.ToString(), (unsigned long)localIpAddr.Get(), (unsigned long)sctp1stLocalPort, (unsigned long)sctp1stRemotePort);
        attrs.AddAttribute(PARAM_ID_IU_SCTP_LOCAL_PORT, sctp2ndLocalPort);
        attrs.AddAttribute(PARAM_ID_IU_SCTP_REMOTE_PORT, sctp2ndRemotePort);
    }

    u32 staticCoreNetworkIpAddress;
    app.GetMibCache().GetMibAttribute(PARAM_ID_IU_STATIC_CN_IP_ADDRESS, staticCoreNetworkIpAddress );

    if(staticCoreNetworkIpAddress == 0)
    {
        Url managementServer;
        app.GetMibCache().GetMibAttribute( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), PARAM_ID_MANAGEMENT_SERVER, managementServer );

        // in the case where we received a Fgw3gInnerIpAddr in the config plan, this will be over-written with
        // that value and IU will use the FGW inner address.  If we don't get the Fgw3gInnerIpAddr in the config
        // plan, we'll default to using the FGW outer address (m_fgwIpAddress).
        attrs.AddAttribute(PARAM_ID_IU_CORE_NET_ADDRESS, managementServer.GetFqdn().ToString() );
    }


    app.GetMibCache().SetMibAttributes( MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP), attrs, ENTITY_TR069);

    Tr069SecGwConnection::ConnectedEntry();
}



}

