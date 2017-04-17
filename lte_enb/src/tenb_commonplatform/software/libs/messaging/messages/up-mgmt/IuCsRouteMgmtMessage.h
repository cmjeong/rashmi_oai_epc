///////////////////////////////////////////////////////////////////////////////
//
// IuCsRouteMgmtMessage
//
// Carries a CS route management message.  E.g. create route, delete route...
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IuCsRouteMgmtMessage_h_
#define __IuCsRouteMgmtMessage_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <comms/IPv4Address.h>
#include <comms/IPv4Endpoint.h>
#include <media/audio_relay.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

// New Cs User Plane messaging
class IuCsRouteMgmtMessage : public threeway::Serialisable
{
public:
    // Need a default constructor for decoding received messages...
    IuCsRouteMgmtMessage (AudioPathMessageType msgType = INVALID_AUDIO_PATH_MSG_TYPE);
    virtual ~IuCsRouteMgmtMessage();

    void Reset ();

    // This populates an Iu User Plane structure with sensible
    // values so the Sip build can pretend to initialise Iu Up.
    static void BuildAudioDebugIuUserPlane (IuUserPlane &userPlaneConf);
    static void BuildVideoDebugIuUserPlane (IuUserPlane &userPlaneConf);

	/**
	 * Get / Set
	 */
    void SetIuUserPlaneParameters (const IuUserPlane &iuUserPlane);
    void SetMediaDestinationAddress (const threeway::IPv4Address &destAddress, u16 destPort);
    void SetMediaLocalAddress (const threeway::IPv4Address &localAddress, u16 localPort);
    void SetDchNumber (u8 allocatedDchNumber);

    AudioPathMessageType GetMessageType () const { return m_messageType; }
    const IPv4Endpoint &GetDestinationMediaAddress () const { return m_mediaRemoteAddress; }
    const IPv4Endpoint &GetLocalMediaAddress () const { return m_mediaLocalAddress; }
    const IuUserPlane &GetIuUserPlaneParameters () const { return m_iuUserPlane; }
    u8 GetDchNumber () const { return m_zeroBasedDchNumber; }

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_IU_CS_ROUTE_MGMT; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Return string representation for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    // minimum message size expected (excluding RESET which is a special case)
    static const u32 MIN_ROUTE_MGMT_MESSAGE_SIZE = 24;

    // One of CREATE / MODIFY / DELETE / RESET.
    AudioPathMessageType m_messageType;

    // Parameters extracted from RANAP RAB ASSIGNMENT REQUEST.
    IuUserPlane m_iuUserPlane;

    // IP Addr:IP Port in Core Network to SEND media to.
    IPv4Endpoint m_mediaRemoteAddress;

    // IP Addr:IP Port in FAP to listen for RECEIVE  media.
    IPv4Endpoint m_mediaLocalAddress;

	// The zero based Dch number allocated in Rrc during Rab establishment.
    u8 m_zeroBasedDchNumber;
};


#endif
