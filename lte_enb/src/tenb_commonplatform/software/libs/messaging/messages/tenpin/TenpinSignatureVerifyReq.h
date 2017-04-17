///////////////////////////////////////////////////////////////////////////////
//
// TenpinSignatureVerifyReq.h
//
// Copyright radisys Limited
//
// THE FORMAT OF THE MESSAGE IMPLEMENTED BY THIS CLASS MUST NOT BE CHANGED.
// THIS AND OTHER IMPLEMENTATIONS RELY ON THE FOLLOWING FORMAT:
//
// This message comprises three information elements each carrying a string
// value. Each information element is encoded using the same format. String 
// values are *not* encoded with an ASCII NUL terminator.
//
// The three strings are encoded in the order:
//      type
//      input filename
//      output filename
//
// The format of an information element is:
//
// BYTES        NAME    VALUE
// 0-1          len     16 bit unsigned integer in network byte order
// 2-(2+len)    str     string value of length 'len'
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinSignatureVerifyReq_h_
#define __TenpinSignatureVerifyReq_h_

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

using namespace std;
using namespace threeway;

class TenpinSignatureVerifyReq : public threeway::Serialisable
{
public:
    TenpinSignatureVerifyReq() {};
    virtual ~TenpinSignatureVerifyReq() {};

    // Implement Serialisable

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_TENPIN_SIGNATURE_VERIFY_REQ; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    void SetType(const char * type) { m_type.assign(type); }
    void SetInputFilename(const char * inputFilename) { m_inputFilename.assign(inputFilename); }
    void SetOutputFilename(const char * outputFilename) { m_outputFilename.assign(outputFilename); }

    const char * GetType() const { return m_type.c_str(); }
    const char * GetInputFilename() const { return m_inputFilename.c_str(); }
    const char * GetOutputFilename() const { return m_outputFilename.c_str(); }

private:
    std::string m_type;
    std::string m_inputFilename;
    std::string m_outputFilename;
};

#endif
