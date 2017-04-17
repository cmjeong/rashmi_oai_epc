///////////////////////////////////////////////////////////////////////////////
//
// SerialisedData.h
//
// SerialisedData is a helper class used to pass the "raw" data received
// from a Messenger up to the user application, where it can be DeSerialised.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SerialisedData_h_
#define __SerialisedData_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>
#include <system/Queueable.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

// Maximum length of serialised message.
static const u32 MESSENGER_MAX_SERIALISED_PACKET_LEN = 65535;
static const u32 MESSENGER_SERIALISED_PACKET_HEADER_LEN = 12 ;
static const u32 MESSENGER_MAX_SERIALISED_PACKET_PAYLOAD_LEN = MESSENGER_MAX_SERIALISED_PACKET_LEN -
                                                               MESSENGER_SERIALISED_PACKET_HEADER_LEN ;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class SerialisedData : public Queueable
{
public:
    SerialisedData(u32 serialisationId, const u8* serialData, u32 dataLength);

    virtual ~SerialisedData();

    const u8* GetSerialData() const { return m_serialData; }
    u32 GetSerialDataLength() const { return m_serialDataLength; }
    u32 GetSerialisationId() const { return m_serialisationId; }

    virtual std::string ToString() const;

private:
    // Ensure objects of this type can't be copied.
    SerialisedData(const SerialisedData&);
    SerialisedData& operator=(const SerialisedData&);

    u32 m_serialisationId;
    u8* m_serialData;
    u32 m_serialDataLength;
};


} // namespace threeway

#endif
