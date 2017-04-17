///////////////////////////////////////////////////////////////////////////////
//
// MessagingConnectionRef.h
//
// Message for refusing a messaging connection.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessagingConnectionRef_h_
#define __MessagingConnectionRef_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <ConnectionIdentifier.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MessagingConnectionRef : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    MessagingConnectionRef(MessagingConnectionIdentifier remoteId);
    MessagingConnectionRef();
    virtual ~MessagingConnectionRef();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_COM_CONNECTION_REF; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    MessagingConnectionIdentifier GetDestConnectionId() const { return m_destConnId; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    MessagingConnectionIdentifier m_destConnId;

};

#endif
