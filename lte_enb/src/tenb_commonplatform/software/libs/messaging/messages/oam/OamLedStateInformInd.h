///////////////////////////////////////////////////////////////////////////////
//
// OamLedStateInformInd.h
//
// OamLedStateInformInd message it is used to notify about LED status change.
// The consumer at the moment is Service API, which has to notify remote entities
// who are subscribed to this event, about any LED change.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __OamLedStateInformInd_h_
#define __OamLedStateInformInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

#include "LedInfo.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
namespace threeway
{

class OamLedStateInformInd: public threeway::Serialisable
{
public:

    OamLedStateInformInd();

    OamLedStateInformInd(u32, LedColour, LedPattern);

    ~OamLedStateInformInd() {};

    /* From Serialisable */
    virtual u32 GetSerialisationId() const
            { return SERIALISATION_ID_OAM_LED_STATE_INFORM; };

    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;

    virtual bool DeSerialise(const u8* data, u32 dataLen);

    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

    u32 GetLedId() const
            { return m_ledId; };

    LedColour GetLedColour() const
            { return m_ledColour; };

    LedPattern GetLedPattern() const
            { return m_ledPattern; };

protected:

private:
    u32         m_ledId;
    LedColour   m_ledColour;
    LedPattern  m_ledPattern;
};

}

#endif
