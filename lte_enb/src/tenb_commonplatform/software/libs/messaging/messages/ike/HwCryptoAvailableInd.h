///////////////////////////////////////////////////////////////////////////////
//
// HwCryptoAvailableInd.h
//
// Copyright radisys
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __HwCryptoAvailableInd_h_
#define __HwCryptoAvailableInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway {

class HwCryptoAvailableInd : public threeway::Serialisable
{
public:
    HwCryptoAvailableInd(bool available) : m_available(available) {}
    HwCryptoAvailableInd() : m_available(false) {}
    virtual ~HwCryptoAvailableInd() {}

    // Implement Serialisable
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_HW_CRYPTO_AVAILABLE_IND; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    bool GetAvailable() const { return m_available; }

    virtual std::string ToString() const;

private:
    bool m_available;
};

}; // namespace

#endif
