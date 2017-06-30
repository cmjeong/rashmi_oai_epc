///////////////////////////////////////////////////////////////////////////////
//
// NasPayloadMessage.h
//
// Message for carrying 'orrible NASAppPayload structures, for backwards
// compatibility until we get rid of NASConnections entirely.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NasPayloadMessage_h_
#define __NasPayloadMessage_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

#include <System3Way.h>
#include <NASAppPayload.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class NasPayloadMessage : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    NasPayloadMessage(const NASAppPayload& payloadMsg);
    NasPayloadMessage();
    virtual ~NasPayloadMessage();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_NAS_PAYLOAD_MSG; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    u8* GetPayloadData() const { return m_payloadData; }
    NASAppPayload* GetNasAppPayload() const { return (NASAppPayload*)m_payloadData; }
    u32 GetPayloadDataLength() const { return m_payloadDataLen; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    // Ensure objects of this type can't be copied.
    NasPayloadMessage(const NasPayloadMessage&);
    NasPayloadMessage& operator=(const NasPayloadMessage&);

    u8*                           m_payloadData;
    u32                           m_payloadDataLen;

};

#endif
