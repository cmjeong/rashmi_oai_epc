///////////////////////////////////////////////////////////////////////////////
//
// TenpinSignatureVerifyCnf.h
//
// Copyright radisys Limited
//
// THE FORMAT OF THE MESSAGE IMPLEMENTED BY THIS CLASS MUST NOT BE CHANGED.
// THIS AND OTHER IMPLEMENTATIONS RELY ON THE FOLLOWING FORMAT:
//
// BYTES    NAME    VALUE
// 0-3      result  32 bit unsigned integer in network byte order
//                  where: 0 = failure; any other value = success
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinSignatureVerifyCnf_h_
#define __TenpinSignatureVerifyCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TenpinSignatureVerifyCnf : public threeway::Serialisable
{
public:
    TenpinSignatureVerifyCnf() : m_result(0) {};
    TenpinSignatureVerifyCnf(u32 result) : m_result(result) {};
    virtual ~TenpinSignatureVerifyCnf() {};

    // Implement Serialisable

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_TENPIN_SIGNATURE_VERIFY_CNF; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    void SetResult(u32 result) { m_result = result; }
    u32 GetResult(void) const { return m_result; }

private:
    u32 m_result;
};

#endif
