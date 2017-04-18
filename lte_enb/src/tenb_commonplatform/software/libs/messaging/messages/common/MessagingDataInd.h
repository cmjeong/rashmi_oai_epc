///////////////////////////////////////////////////////////////////////////////
//
// MessagingDataInd.h
//
// Message for sending data on a messaging connection.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessagingDataInd_h_
#define __MessagingDataInd_h_

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

class MessagingDataInd : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    /**
     * IMPORTANT NOTE: the ctor will NOT copy the payload so this message MUST
     * be sent (ie Serialised) before the payload msg is destroyed.
     * OR call Clone() to copy the data (e.g. if you want to put this class on a queue).
     *
     */
    MessagingDataInd(MessagingConnectionIdentifier localId, MessagingConnectionIdentifier remoteId, threeway::Serialisable& payloadMsg);
    MessagingDataInd();
    virtual ~MessagingDataInd();

    /**
     * Clone the payload data into memory owned by this class.
     * Returns true if successfull.
     */
    bool Clone();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_COM_DATA_IND; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    MessagingConnectionIdentifier GetSourceConnectionId() const { return m_sourceConnId; }
    MessagingConnectionIdentifier GetDestConnectionId() const { return m_destConnId; }
    u8* GetPayloadData() const { return m_payloadData; }
    u32 GetPayloadDataLength() const { return m_payloadDataLen; }
    u32 GetPayloadSerialisationId() const { return m_serialisationId; }

    void SetSourceConnectionId(MessagingConnectionIdentifier localId) { m_sourceConnId = localId; }
    void SetDestConnectionId(MessagingConnectionIdentifier remoteId) { m_destConnId = remoteId; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    // Ensure objects of this type can't be copied.
    MessagingDataInd(const MessagingDataInd&);
    MessagingDataInd& operator=(const MessagingDataInd&);

    MessagingConnectionIdentifier m_sourceConnId;
    MessagingConnectionIdentifier m_destConnId;
    // for Serialise
    threeway::Serialisable*       m_payloadMsg;
    // for DeSerialise or Cloned data
    u8*                           m_payloadData;
    u32                           m_payloadDataLen;
    u32                           m_serialisationId;
    bool                          m_hasClonedData;
};

#endif
