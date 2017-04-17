///////////////////////////////////////////////////////////////////////////////
//
// NlmCoscCnf.h
//
// Message for confirming completion of a NLM COSC, to freq-sync module.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NlmCoscCnf_h_
#define __NlmCoscCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

enum eNlmCoscResult
{
    NLM_COSC_FAILED = 0,
    NLM_COSC_SUCCESSFUL 
} ;

class NlmCoscCnf : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    NlmCoscCnf(eNlmCoscResult coscResult, u16 coscArfcn);
    NlmCoscCnf();
    virtual ~NlmCoscCnf();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_NLM_COSC_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters
     */
    eNlmCoscResult GetNlmCoscResult() const { return m_coscResult; }
    u16  GetNlmCoscArfcn() const { return m_coscArfcn; }

private:
    eNlmCoscResult m_coscResult;
    u16            m_coscArfcn;
};

#endif // __NlmCoscCnf_h_
