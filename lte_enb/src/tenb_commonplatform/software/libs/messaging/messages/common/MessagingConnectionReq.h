///////////////////////////////////////////////////////////////////////////////
//
// MessagingConnectionReq.h
//
// Message for requesting a new messaging connection.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessagingConnectionReq_h_
#define __MessagingConnectionReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <ConnectionIdentifier.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MessagingConnectionReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    /**
     * IMPORTANT NOTE: the ctor will NOT copy the payload so this message MUST
     * be sent (ie Serialised) before the payload msg is destroyed.
     */
    MessagingConnectionReq(MessagingConnectionIdentifier localId, threeway::Serialisable& payloadMsg);
    MessagingConnectionReq();
    virtual ~MessagingConnectionReq();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_COM_CONNECTION_REQ; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    MessagingConnectionIdentifier GetSourceConnectionId() const { return m_sourceConnId; }
    u8* GetPayloadData() const { return m_payloadData; }
    u32 GetPayloadDataLength() const { return m_payloadDataLen; }
    u32 GetPayloadSerialisationId() const { return m_serialisationId; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    // Ensure objects of this type can't be copied.
    MessagingConnectionReq(const MessagingConnectionReq&);
    MessagingConnectionReq& operator=(const MessagingConnectionReq&);

    MessagingConnectionIdentifier m_sourceConnId;
    // for Serialise - do not delete, this class is temporary and doesn't 'own' the message
    threeway::Serialisable*       m_payloadMsg;
    // for DeSerialise
    u8*                           m_payloadData;
    u32                           m_payloadDataLen;
    u32                           m_serialisationId;

};

#endif
