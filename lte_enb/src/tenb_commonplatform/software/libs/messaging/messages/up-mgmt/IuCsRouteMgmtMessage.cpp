///////////////////////////////////////////////////////////////////////////////
//
// IuCsRouteMgmtMessage.cpp
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
#include <iomanip>

#include <system/Trace.h>
#include <system/NumberConversions.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IuCsRouteMgmtMessage.h"

using std::setfill;
using std::setw;

using namespace std;
using namespace threeway;

IuCsRouteMgmtMessage::IuCsRouteMgmtMessage(AudioPathMessageType msgType) :
    m_messageType (msgType)
{
    ENTER();
    Reset ();
    EXIT();
}

IuCsRouteMgmtMessage::~IuCsRouteMgmtMessage()
{
    ENTER();
    EXIT();
}

void IuCsRouteMgmtMessage::Reset ()
{
    // Ensure all member vars initialised to something safe.
    bzero (&m_iuUserPlane, sizeof (IuUserPlane));
    m_mediaRemoteAddress.m_ipAddr.Clear ();
    m_mediaRemoteAddress.m_ipPort = 0xffff;
    m_mediaLocalAddress.m_ipAddr.Clear ();
    m_mediaLocalAddress.m_ipPort = 0xffff;
    m_zeroBasedDchNumber = 0xff;
}

void IuCsRouteMgmtMessage::BuildAudioDebugIuUserPlane (IuUserPlane &userPlaneConf)
{
    bzero (&userPlaneConf, sizeof (IuUserPlane));

    userPlaneConf.iuModeVersionBitmap = 0x0003;
    userPlaneConf.iuUpMode = IU_UP_SUPPORT_MODE;
    userPlaneConf.iuDataPduType = IU_UP_DATA_PDU_TYPE_1;

    userPlaneConf.sduParameterCount = 3;
    userPlaneConf.sduParameters[0].numberOfSduSubFlows = 10;
    userPlaneConf.sduParameters[1].numberOfSduSubFlows = 10;
    userPlaneConf.sduParameters[2].numberOfSduSubFlows = 10;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[0] = 0x51;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[0] = 0x67;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[0] = 0x3C;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[1] = 0x41;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[1] = 0x63;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[1] = 0x28;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[2] = 0x4B;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[2] = 0x54;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[2] = 0x00;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[3] = 0x3D;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[3] = 0x57;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[3] = 0x00;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[4] = 0x3A;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[4] = 0x4C;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[4] = 0x00;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[5] = 0x37;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[5] = 0x3F;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[5] = 0x00;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[6] = 0x31;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[6] = 0x36;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[6] = 0x00;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[7] = 0x2A;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[7] = 0x35;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[7] = 0x00;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[8] = 0x27;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[8] = 0x00;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[8] = 0x00;

    userPlaneConf.sduParameters[0].sduSubFlowSizes[9] = 0x00;
    userPlaneConf.sduParameters[1].sduSubFlowSizes[9] = 0x00;
    userPlaneConf.sduParameters[2].sduSubFlowSizes[9] = 0x00;
}

void IuCsRouteMgmtMessage::BuildVideoDebugIuUserPlane (IuUserPlane &userPlaneConf)
{
    bzero (&userPlaneConf, sizeof (IuUserPlane));
    userPlaneConf.iuUpMode = IU_UP_TRANSPARENT_MODE;
}

void IuCsRouteMgmtMessage::SetIuUserPlaneParameters (const IuUserPlane &iuUserPlane)
{
    ENTER ();
    memcpy (&m_iuUserPlane, &iuUserPlane, sizeof (IuUserPlane));
    EXIT ();
}

void IuCsRouteMgmtMessage::SetMediaDestinationAddress (const threeway::IPv4Address &destAddress, u16 destPort)
{
    ENTER ();
    m_mediaRemoteAddress.m_ipAddr.Set (destAddress.Get ());
    m_mediaRemoteAddress.m_ipPort = destPort;
    EXIT ();
}

void IuCsRouteMgmtMessage::SetMediaLocalAddress (const threeway::IPv4Address &localAddress, u16 localPort)
{
    ENTER ();
    m_mediaLocalAddress.m_ipAddr.Set (localAddress.Get ());
    m_mediaLocalAddress.m_ipPort = localPort;
    EXIT ();
}

void IuCsRouteMgmtMessage::SetDchNumber (u8 allocatedDchNumber)
{
    ENTER ();
    m_zeroBasedDchNumber = allocatedDchNumber;
    EXIT ();
}

s32 IuCsRouteMgmtMessage::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_iuUserPlane.sduParameterCount <= MAX_RAB_SUBFLOWS);

    u32 messageSize = 0;
    U32ToBigEndianByteArray ((u32)m_messageType, &data[messageSize]);
    messageSize += 4;

    U32ToBigEndianByteArray(m_mediaRemoteAddress.m_ipAddr.Get(), &data[messageSize]);
    messageSize += 4;

    U16ToBigEndianByteArray(m_mediaRemoteAddress.m_ipPort, &data[messageSize]);
    messageSize +=2;

    U32ToBigEndianByteArray(m_mediaLocalAddress.m_ipAddr.Get(), &data[messageSize]);
    messageSize += 4;

    U16ToBigEndianByteArray(m_mediaLocalAddress.m_ipPort, &data[messageSize]);
    messageSize +=2;

    data[messageSize] = m_zeroBasedDchNumber;
    messageSize++;

    U16ToBigEndianByteArray(m_iuUserPlane.maxSduSize, &data[messageSize]);
    messageSize +=2;

    U16ToBigEndianByteArray(m_iuUserPlane.iuModeVersionBitmap, &data[messageSize]);
    messageSize +=2;

    U16ToBigEndianByteArray(m_iuUserPlane.iuDataPduType, &data[messageSize]);
    messageSize ++;

    data[messageSize] = m_iuUserPlane.iuUpMode;
    messageSize++;

    data[messageSize] = m_iuUserPlane.sduParameterCount;
    messageSize++;

    for (u8 i=0;i<m_iuUserPlane.sduParameterCount;i++)
    {
        data[messageSize++] = m_iuUserPlane.sduParameters[i].numberOfSduSubFlows;

        // Check indexing into sduSubFlowSizes[].
        RSYS_ASSERT(m_iuUserPlane.sduParameters[i].numberOfSduSubFlows <= MAX_RAB_SUBFLOW_COMBINATIONS);
        for (u8 j=0;j<m_iuUserPlane.sduParameters[i].numberOfSduSubFlows;j++)
        {
            U16ToBigEndianByteArray(m_iuUserPlane.sduParameters[i].sduSubFlowSizes[j], &data[messageSize]);
            messageSize +=2;
        }
    }

    RETURN(messageSize);
}

bool IuCsRouteMgmtMessage::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    Reset ();

    u32 messageSize = 0;
    m_messageType = (AudioPathMessageType) BigEndianByteArrayToU32 (&data[messageSize]);
    messageSize += 4;

    TRACE ("Received Msg In CS User Plane", (u32)m_messageType);
    if(dataLen >= MIN_ROUTE_MGMT_MESSAGE_SIZE)
    {
        m_mediaRemoteAddress.m_ipAddr.Set(BigEndianByteArrayToU32(&data[messageSize]));
        messageSize += 4;

        m_mediaRemoteAddress.m_ipPort = BigEndianByteArrayToU16 (&data[messageSize]);
        messageSize += 2;

        m_mediaLocalAddress.m_ipAddr.Set(BigEndianByteArrayToU32(&data[messageSize]));
        messageSize += 4;

        m_mediaLocalAddress.m_ipPort = BigEndianByteArrayToU16 (&data[messageSize]);
        messageSize += 2;

        m_zeroBasedDchNumber = data[messageSize];
        messageSize++;

        m_iuUserPlane.maxSduSize = BigEndianByteArrayToU16 (&data[messageSize]);
        messageSize += 2;

        m_iuUserPlane.iuModeVersionBitmap = BigEndianByteArrayToU16 (&data[messageSize]);
        messageSize += 2;

        m_iuUserPlane.iuDataPduType = (IuUpDataPduType) data[messageSize];
        messageSize ++;

        m_iuUserPlane.iuUpMode = (IuUpMode) data [messageSize];
        messageSize++;

        m_iuUserPlane.sduParameterCount = data [messageSize];
        messageSize++;

        // Check array bounds.
        RSYS_ASSERT(m_iuUserPlane.sduParameterCount <= MAX_RAB_SUBFLOWS);

        u8 i = 0, j = 0;
        for (i=0; i < m_iuUserPlane.sduParameterCount; i++)
        {
            if ((messageSize + 5 + (m_iuUserPlane.sduParameters[i].numberOfSduSubFlows * 2)) > dataLen)
            {
                TRACE_MSG ("Failed to DeSerialise, not enough data for sdu params");
                RETURN(false);
            }

            m_iuUserPlane.sduParameters[i].numberOfSduSubFlows = data[messageSize++];

            // Check array bounds.
            RSYS_ASSERT(m_iuUserPlane.sduParameters[i].numberOfSduSubFlows <= MAX_RAB_SUBFLOW_COMBINATIONS);
            for (j=0;j<m_iuUserPlane.sduParameters[i].numberOfSduSubFlows;j++)
            {
                m_iuUserPlane.sduParameters[i].sduSubFlowSizes[j] = BigEndianByteArrayToU16 (&data[messageSize]);
                messageSize += 2;
            }
        }
        RETURN (true);
    }

    RETURN(false);
}

string IuCsRouteMgmtMessage::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "{ IuCsRouteMgmtMessage" << endl;
    stream << "  Type          : ";
    switch (m_messageType)
    {
    case CREATE_ROUTE:
        stream << "Create Route" << endl;
        break;
    case CREATE_ROUTE_ACK:
        stream << "Create Route Ack" << endl;
        break;
    case CREATE_ROUTE_NACK:
        stream << "Create Route NAck" << endl;
        break;
    case MODIFY_ROUTE:
        stream << "Modify Route" << endl;
        break;
    case MODIFY_ROUTE_ACK:
        stream << "Modify Route Ack" << endl;
        break;
    case MODIFY_ROUTE_NACK:
        stream << "Modify Route NAck" << endl;
        break;
    case DELETE_ROUTE:
        stream << "Delete Route" << endl;
        break;
    case DELETE_ROUTE_ACK:
        stream << "Delete Route Ack" << endl;
        break;
    case DELETE_ROUTE_NACK:
        stream << "Delete Route NAck" << endl;
        break;
    case RESET_USER_PLANE:
        stream << "Reset User Plane" << endl;
        break;
    case INVALID_AUDIO_PATH_MSG_TYPE:
        stream << "Message Type Invalid" << endl;
        stream << "}" << endl;
        RETURN (stream.str ());
    }

    if (m_messageType != RESET_USER_PLANE)
        stream << "  Dch           : " << (u32) m_zeroBasedDchNumber << endl;

    if (m_messageType == CREATE_ROUTE)
    {
        stream << "  Hbs2 Endpoint : ";
        stream << setfill(' ') << m_mediaLocalAddress.m_ipAddr.ToString () << ":";
        stream << setfill('0') << setw(4) << m_mediaLocalAddress.m_ipPort << endl;
        stream << "  Cn Endpoint   : ";
        stream << m_mediaRemoteAddress.m_ipAddr.ToString () << ":";
        stream << setfill('0') << setw(4) << m_mediaRemoteAddress.m_ipPort << endl;
    }

    stream << "}" << endl;
    RETURN(stream.str());
}


string IuCsRouteMgmtMessage::ToBriefString() const
{
    ENTER();

    ostringstream stream;

    if (m_messageType != RESET_USER_PLANE)
    {
        stream << "dch=" << (u32) m_zeroBasedDchNumber;
    }

    switch (m_messageType)
    {
    case CREATE_ROUTE:
        stream << " create";
        break;
    case CREATE_ROUTE_ACK:
        stream << " create Ack";
        break;
    case CREATE_ROUTE_NACK:
        stream << " create NAck";
        break;
    case MODIFY_ROUTE:
        stream << " modify";
        break;
    case MODIFY_ROUTE_ACK:
        stream << " modify Ack";
        break;
    case MODIFY_ROUTE_NACK:
        stream << " modify NAck";
        break;
    case DELETE_ROUTE:
        stream << " delete";
        break;
    case DELETE_ROUTE_ACK:
        stream << " delete Ack";
        break;
    case DELETE_ROUTE_NACK:
        stream << " delete NAck";
        break;
    case RESET_USER_PLANE:
        stream << " reset";
        break;
    default:
        break;
    }

    RETURN(stream.str());
}

// END OF FILE

