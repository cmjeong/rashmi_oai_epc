///////////////////////////////////////////////////////////////////////////////
//
// MessagingReleaseConf.h
//
// Message to confirm the successful release of a messaging connection.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessagingReleaseConf_h_
#define __MessagingReleaseConf_h_

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

class MessagingReleaseConf : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    MessagingReleaseConf(MessagingConnectionIdentifier localId, MessagingConnectionIdentifier remoteId);
    MessagingReleaseConf();
    virtual ~MessagingReleaseConf();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_COM_RELEASE_CONF; }
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
