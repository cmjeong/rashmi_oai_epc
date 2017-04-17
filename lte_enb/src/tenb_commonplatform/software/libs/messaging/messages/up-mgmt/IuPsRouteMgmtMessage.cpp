///////////////////////////////////////////////////////////////////////////////
//
// IuPsRouteMgmtMessage.cpp
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
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IuPsRouteMgmtMessage.h"

using namespace std;
using namespace threeway;

std::string IuPsRouteMgmtMessage::PsUpMessageTypeToString (IuPsRouteMgmtMessageType messageType)
{
    ENTER();
    switch(messageType)
    {
    case IU_PS_CREATE_ROUTE_REQ:
        RETURN ("CREATE-ROUTE-REQ");
        break;
    case IU_PS_CREATE_ROUTE_CNF:
        RETURN ("CREATE-ROUTE-CNF");
        break;
    case IU_PS_DELETE_ROUTE_REQ:
        RETURN ("DELETE-ROUTE-REQ");
        break;
    case IU_PS_DELETE_ROUTE_CNF:
        RETURN ("DELETE-ROUTE-CNF");
        break;
    case IU_PS_DELETE_ROUTE_IND:
        RETURN ("DELETE-ROUTE-IND");
        break;
    case IU_PS_SUSPEND_ROUTE_REQ:
        RETURN ("IU-PS-SUSPEND-ROUTE-REQ");
        break;
    case IU_PS_SUSPEND_ROUTE_CNF:
        RETURN ("IU-PS-SUSPEND-ROUTE-CNF");
        break;
    case IU_PS_RESUME_ROUTE_IND:
        RETURN ("IU-PS-RESUME-ROUTE-IND");
        break;
    case IU_PS_RESUME_ROUTE_REQ:
        RETURN ("IU-PS-RESUME-ROUTE-REQ");
        break;
    case IU_PS_RESUME_ROUTE_CNF:
        RETURN ("IU-PS-RESUME-ROUTE-CNF");
        break;
    case IU_PS_RESUME_ROUTE_FAIL:
        RETURN ("IU-PS-RESUME-ROUTE-FAIL");
        break;
    case IU_PS_RESET_USER_PLANE:
        RETURN ("IU-PS-RESET-USER-PLANE");
        break;
    case IU_PS_INVALID_MSG:
        RETURN ("IuPsRouteMgmtMessage - INVALID MESSAGE TYPE");
        break;
    }
    RETURN ("IuPsRouteMgmtMessage - ENUM OUT OF RANGE");
}

std::string IuPsRouteMgmtMessage::BearerTypeToString(IuPsBearerType bearerType)
{
    ENTER();

    switch(bearerType)
    {
        case IU_PS_BEARER_CHANNEL_1:
            RETURN("CHAN #1");
            break;
        case IU_PS_BEARER_UNDEFINED:
            RETURN("UndefinedPsBearer");
            break;
    };

    RETURN("UnknownPsBearer");
}

std::string IuPsRouteMgmtMessage::TosToString(TOSVal tosValue)
{
    ENTER();

    switch(tosValue)
    {
        case QOS_NONE:
            RETURN("QOS_NONE (0)");
            break;
        case QOS_CLASS_A:
            RETURN("QOS_CLASS_A (0x04)");
            break;
        case QOS_CLASS_B:
            RETURN("QOS_CLASS_B (0xb8 / EF)");
            break;
        case QOS_CLASS_C:
            RETURN("QOS_CLASS_C (0x0C)");
            break;
        case QOS_CLASS_D:
            RETURN("QOS_CLASS_D (0x10)");
            break;
        case QOS_CLASS_E:
            RETURN("QOS_CLASS_E (0x14)");
            break;
        case QOS_CLASS_F:
            RETURN("QOS_CLASS_F (0x18)");
            break;
    };

    RETURN("UnknownTOSValue");
}

IuPsRouteMgmtMessage::IuPsRouteMgmtMessage(IuPsRouteMgmtMessageType messageType) :
    m_uRnti(0),
    m_messageType(messageType),
    m_remotePort(0),
    m_localIpAddress( "0.0.0.0" ),
    m_psUserPlaneNumber(IU_PS_DATA_STREAM_ID_UNDEFINED),
    m_tunnelEndpointId(0),
    m_tunnelEndpointIdSet(false),
    m_bearerType(IU_PS_BEARER_UNDEFINED),
    m_tos(QOS_NONE)
{
    ENTER();
    EXIT();
}

IuPsRouteMgmtMessage::IuPsRouteMgmtMessage() :
    m_uRnti(0),
    m_messageType(IU_PS_INVALID_MSG),
    m_remotePort(0),
    m_localIpAddress( "0.0.0.0" ),
    m_psUserPlaneNumber(IU_PS_DATA_STREAM_ID_UNDEFINED),
    m_tunnelEndpointId(0),
    m_tunnelEndpointIdSet(false),
    m_bearerType(IU_PS_BEARER_UNDEFINED),
    m_tos(QOS_NONE)
{
    ENTER();

    EXIT();
}

IuPsRouteMgmtMessage::~IuPsRouteMgmtMessage()
{
    ENTER();
    EXIT();
}

s32 IuPsRouteMgmtMessage::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Show me the bytes on the wire...
    //
    //  m_uRnti (4 bytes; comprises SRNC + SRNTI)
    //  m_messageType (4 bytes, big endian)
    //  m_remoteIpAddress (4 bytes, MSDigit first)
    //  m_remotePort (2 bytes, big endian)
    //  m_psUserPlaneNumber (4 bytes, big endian)
    //  m_tunnelEndpointId (4 bytes, big endian)
    //  m_tunnelEndpointIdSet (1 byte, 0-not set, 1-set)
    //  m_bearerType (1 byte)

    if(dataMaxBytes >= SERIALISATION_NUM_BYTES)
    {
        u32 messageSize = 0;
        U32ToBigEndianByteArray((u32)m_uRnti, &(data[messageSize]));
        messageSize+=4;
        U32ToBigEndianByteArray((u32)m_messageType, &(data[messageSize]));
        messageSize+=4;
        U32ToBigEndianByteArray(m_remoteIpAddress.Get(), &(data[messageSize]));
        messageSize+=4;
        U16ToBigEndianByteArray(m_remotePort, &(data[messageSize]));
        messageSize+=2;
        U32ToBigEndianByteArray(m_localIpAddress.Get(), &(data[messageSize]));
        messageSize+=4;
        U32ToBigEndianByteArray(m_psUserPlaneNumber, &(data[messageSize]));
        messageSize+=4;
        U32ToBigEndianByteArray(m_tunnelEndpointId, &(data[messageSize]));
        messageSize+=4;
        data[messageSize] = m_tunnelEndpointIdSet ? 1 : 0;
        messageSize++;
        data[messageSize] = (u8)m_bearerType;
        messageSize++;
        data[messageSize] = (u8)m_tos;
        messageSize++;

        RETURN(messageSize);
    }

    RETURN(-1);
}

bool IuPsRouteMgmtMessage::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen == SERIALISATION_NUM_BYTES)
    {
        u32 messageSize = 0;
        m_uRnti = BigEndianByteArrayToU32(&(data[messageSize]));
        messageSize+=4;
        m_messageType = (IuPsRouteMgmtMessageType)BigEndianByteArrayToU32(&(data[messageSize]));
        messageSize+=4;
        m_remoteIpAddress.Set(BigEndianByteArrayToU32(&(data[messageSize])));
        messageSize+=4;
        m_remotePort = BigEndianByteArrayToU16(&(data[messageSize]));
        messageSize+=2;
        m_localIpAddress.Set(BigEndianByteArrayToU32(&(data[messageSize])));
        messageSize+=4;
        m_psUserPlaneNumber = BigEndianByteArrayToU32(&(data[messageSize]));
        messageSize+=4;
        m_tunnelEndpointId = BigEndianByteArrayToU32(&(data[messageSize]));
        messageSize+=4;
        m_tunnelEndpointIdSet = (data[messageSize] != 0);
        messageSize++;
        m_bearerType = (IuPsBearerType)data[messageSize];
        messageSize++;
        m_tos = (TOSVal) data[messageSize];
        messageSize++;
        RETURN(true);
    }

    RETURN(false);
}

string IuPsRouteMgmtMessage::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << PsUpMessageTypeToString (m_messageType) << ", uRnti=" << m_uRnti;

    if((m_remoteIpAddress.IsSet()) && (m_remoteIpAddress.Get() != 0)) // IsSet() always true after deserialisation so check for zero too.
    {
        stream << ", remoteIpAddress=" << m_remoteIpAddress.ToString();
    }

    if(m_remotePort != 0)
    {
        stream << ", remotePort=" << m_remotePort;
    }

    if((m_localIpAddress.IsSet()) && (m_localIpAddress.Get() != 0)) // IsSet() always true after deserialisation so check for zero too.
    {
        stream << ", localIpAddress=" << m_localIpAddress.ToString();
    }

    stream << ", tunnelEndpointId=";
    if(m_tunnelEndpointIdSet)
    {
        stream << m_tunnelEndpointId;
    }
    else
    {
        stream << "NOT SET";
    }

    if(m_bearerType != IU_PS_BEARER_UNDEFINED)
    {
        stream << ", bearerType=" << BearerTypeToString(m_bearerType);
    }

    if(m_tos != QOS_NONE)
    {
        stream << ", TOS=" << TosToString(m_tos);
    }

    RETURN(stream.str());
}
