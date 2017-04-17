///////////////////////////////////////////////////////////////////////////////
//
// IuPsRouteMgmtMessage
//
// Carries a PS route management message.  E.g. create route, delete route...
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IuPsRouteMgmtMessage_h_
#define __IuPsRouteMgmtMessage_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <comms/IPv4Address.h>
#include <comms/TOSValues.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IuPsRouteMgmtMessage : public threeway::Serialisable
{
public:
    // Message types.
    enum IuPsRouteMgmtMessageType
    {
        IU_PS_CREATE_ROUTE_REQ = 0,
        IU_PS_CREATE_ROUTE_CNF,
        IU_PS_DELETE_ROUTE_REQ,
        IU_PS_DELETE_ROUTE_CNF,
        IU_PS_DELETE_ROUTE_IND,
        // CELL PCH Management
        // Enter CELL PCH from CELL DCH...
        IU_PS_SUSPEND_ROUTE_REQ,
        IU_PS_SUSPEND_ROUTE_CNF,
        // Enter CELL DCH from CELL PCH...
        IU_PS_RESUME_ROUTE_IND,
        IU_PS_RESUME_ROUTE_REQ,
        IU_PS_RESUME_ROUTE_CNF,
        IU_PS_RESUME_ROUTE_FAIL,

		IU_PS_RESET_USER_PLANE,

		IU_PS_INVALID_MSG = 0xff
    };

    enum IuPsBearerType
    {
        IU_PS_BEARER_CHANNEL_1 = 0,
        IU_PS_BEARER_UNDEFINED
    };

    static std::string PsUpMessageTypeToString (IuPsRouteMgmtMessageType messageType);
    static std::string BearerTypeToString(IuPsBearerType bearerType);
    static std::string TosToString(TOSVal tosVal);

    // Null data stream ID.
    static const u32 IU_PS_DATA_STREAM_ID_UNDEFINED = 0xffffffff;

    /**
     * Construction / destruction.
     */
    IuPsRouteMgmtMessage(IuPsRouteMgmtMessageType messageType);
    IuPsRouteMgmtMessage();
    virtual ~IuPsRouteMgmtMessage();

    /**
     * Getters / setters.
     */
    void SetMessageType(IuPsRouteMgmtMessageType messageType) { m_messageType = messageType; };
    IuPsRouteMgmtMessageType GetMessageType() const { return m_messageType; };

    void SetRemoteIpAddress(threeway::IPv4Address& remoteIpAddress) { m_remoteIpAddress = remoteIpAddress; };
    const threeway::IPv4Address& GetRemoteIpAddress() const { return m_remoteIpAddress; };

    void SetRemotePort(u16 remotePort) { m_remotePort = remotePort; };
    u16 GetRemotePort() const { return m_remotePort; };

    void SetLocalIpAddress(threeway::IPv4Address& localIpAddress) { m_localIpAddress = localIpAddress; };
    const threeway::IPv4Address& GetLocalIpAddress() const { return m_localIpAddress; };

    void SetPsUserPlaneId(u32 psUserPlaneNumber) { m_psUserPlaneNumber = psUserPlaneNumber; };
    u32 GetPsUserPlaneId() const { return m_psUserPlaneNumber; };

    void SetTunnelEndpointId(u32 tunnelEndpointId) { m_tunnelEndpointId = tunnelEndpointId; m_tunnelEndpointIdSet = true; };
    bool GetTunnelEndpointIdIsSet() const { return m_tunnelEndpointIdSet; };
    u32 GetTunnelEndpointId() const { return m_tunnelEndpointId; };

    void SetBearerType(IuPsBearerType bearerType) { m_bearerType = bearerType; };
    IuPsBearerType GetBearerType() const { return m_bearerType; };

    void SetUrnti (u32 uRnti) { m_uRnti = uRnti; }
    u32 GetUrnti () const { return m_uRnti; }

    void SetTos(TOSVal tos) { m_tos = tos; };
    TOSVal GetTos() const { return m_tos; };

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_IU_PS_ROUTE_MGMT; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Return string representation for debug.
     */
    virtual std::string ToString() const;

private:
    static const u32 SERIALISATION_NUM_BYTES = 29;

    u32                         m_uRnti;
    IuPsRouteMgmtMessageType    m_messageType;
    threeway::IPv4Address       m_remoteIpAddress;
    u16                         m_remotePort;
    threeway::IPv4Address       m_localIpAddress;
    u32                         m_psUserPlaneNumber;
    u32                         m_tunnelEndpointId;
    bool                        m_tunnelEndpointIdSet;
    IuPsBearerType              m_bearerType;
    TOSVal                      m_tos;
};

#endif
