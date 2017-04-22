///////////////////////////////////////////////////////////////////////////////
//
// MessagingConnectionConf.h
//
// Message to confirm a messaging connection has been setup successfully.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessagingConnectionConf_h_
#define __MessagingConnectionConf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <ConnectionIdentifier.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MessagingConnectionConf : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    MessagingConnectionConf(MessagingConnectionIdentifier localId, MessagingConnectionIdentifier remoteId);
    MessagingConnectionConf();
    virtual ~MessagingConnectionConf();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_COM_CONNECTION_CONF; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    MessagingConnectionIdentifier GetSourceConnectionId() const { return m_sourceConnId; }
    MessagingConnectionIdentifier GetDestConnectionId() const { return m_destConnId; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    MessagingConnectionIdentifier m_sourceConnId;
    MessagingConnectionIdentifier m_destConnId;

};

#endif
